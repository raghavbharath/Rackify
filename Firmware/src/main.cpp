#include "Arduino.h"
#include "motor.h"
#include "SPI.h"
#include "rfid.h"
#include "Wifi.h"

const char* ssid = "NJIoT";
const char* password = "mythings";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Time vars
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000; // milliseconds 

bool usingWebLock;

// RFID reader
RFID rfid(5, 4);
String rfidCard;
String rfidCardTest;

// Worm motors
motor motor(32, 33, false);

bool open_;
bool moving_;

long waitTime_;
long startTime_;

//Buzzer and LED
int buzzer = 25;

void startWaiting(long wait) {
  startTime_ = millis();
  waitTime_ = wait;
  moving_ = true;
}

void updateMotor() {
  if (moving_ && millis() > startTime_ + waitTime_) {
    motor.drive(0);
    open_ = !open_;
    moving_ = false;
  }
}

bool closeLatch() {
  if (open_ && !moving_) {
    motor.drive(255);
    startWaiting(15000);
    return true;
  }
  return false;
}

bool openLatch() {
  if (!open_ && !moving_) {
    motor.drive(-255);
    startWaiting(15000);
    return true;
  }
  return false;
}

long buzzStartTime;

void buzz() {
  if (millis() > buzzStartTime + 250) {
    //tone(buzzer, 2000);
    ledcWriteTone(0, 2000);
    buzzStartTime = millis();
  }
}

void updateBuzzer() {
  if (millis() > buzzStartTime + 200) {
    //noTone(buzzer);
    ledcWriteTone(0, 0);
  }
}

void setup() {
  open_ = true;
  moving_ = false;
  usingWebLock = false;

  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  SPI.begin();
  rfid.init();

  //pinMode(buzzer, OUTPUT);
  ledcAttachPin(buzzer, 0);
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port

    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();

      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;

        /* if the byte is a newline character
           if the current line is blank, you got two newline characters in a row.
           that's the end of the client HTTP request, so send a response: */

        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            /* HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
               and a content-type so the client knows what's coming, then a blank line: */
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Handle HTTP Requests
            if (!moving_) {
              if (header.indexOf("/lock") >= 0) { // --> Locking Mechanism 
                Serial.println("Engaging locking mechansim");

                // Call method to engage locking mech
                if (closeLatch()) {
                  usingWebLock = true;
                  buzz();
                }
              } else if (header.indexOf("/unlock") >= 0) { // --> Unlocking Mechanism 
                  Serial.println("Engaging unlocking mechanism");

                  // Call method to enage unlocking mech
                  if (usingWebLock && openLatch()) {
                    usingWebLock = false;
                    buzz();
                  }
                  else {
                    buzz();
                    while (millis() < buzzStartTime + 300) {
                      updateBuzzer();
                    }
                    buzz();
                  }
              }
            }
            
            // The HTTP response ends with another blank line
            client.println();

            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  /* if you got anything else but a carriage return 
                                    character, add it to the end of the currentLine */
          currentLine += c;         
        }
      }

      updateMotor();
      updateBuzzer();
    }

    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

  if (open_ && !moving_)
  {
    if (rfid.isCard()) {
      if (rfid.readCardSerial()) {
        rfidCardTest = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
        //setColor(0, 1, 0);
        //delay(1000);
        //setColor(0,0,0);
        closeLatch();
        buzz();
      }
    }
  }
  
  else if (!moving_) {
    if (rfid.isCard())
    {
      if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      
        if (rfidCard.equals(rfidCardTest))
        {
          Serial.println("Unlocked");
          // setColor(0, 1, 0);
          // delay(1000);
          // setColor(0,0,0);
          if (usingWebLock) {
            buzz();
          }
          else {
            openLatch();
            buzz();
          }
        }
        else
        {
          Serial.println("Locked - Try again");
          // setColor(1, 0, 0);
          // delay(1000);
          // setColor(0,0,0);
          buzz();
        }
      }
    }
  }

  rfid.halt();

  updateMotor();
  updateBuzzer();

  delay(5);
}