## Rackify 🚲

A prototype bike racking system allowing users to pay to access bike racks distributed across major cities via a mobile application or pre-paid card. 
Achieved 3rd place overall at NJIT’s spring 2024 IEEE Hardware Hackathon, winning a $500 cash prize.

Team Members: Raghav Bharath, Burhan Naveed, Matthew Levine, Prabhav Sharma, Tanush Tammanagoudar

## Project Status ✔

We were inspired to create this smart bike lock by the many bikes and scooters used by college students at NJIT and Newark. We believe that the future for smart cities is micro-mobility devices like bikes and scooters that can be very energy efficient and take up very little space.

Our smart lock is a contactless solution that aims to improve the experience of bike and scooter users. Instead of needing to carry locks around everywhere, the lock would be built directly into the rack. The system can work with any RFID card, and we also developed a web server that can remotely operate the device. When one person scans to lock their device, only their card can unlock it. This is an effortless and intuitive experience for the user, working just like any regular contactless door or payment system.

Mechanically, the system works via a worm gear ring that runs along V-groove guides. The ring has a cutout that allows a bike wheel or scooter post to fit in place, and then, when it rotates, it closes off the opening.

In software, we use an RFID scanner and store the ID of whatever card is used to lock it, and then check for that card when unlocking. We also incorporated a buzzer to add feedback so users know that their card is scanning. Finally, we developed a basic website to show how this could be implemented on a larger scale with GPS locations and remote operations.

Software Accomplishments: 
- Transferring mock HTML mobile app to React Native for demoing on Expo.
- Adding user Authentication with Appwrite.
- Handling rack occupation data in Appwrite.

Tools Used: SolidWorks CAD and Autodesk Fusion360 (Worm gear traversing V-groove guides), ESP32, JavaScript, C++, FastAPI backend, PlatformIo, LL2390D H-Bridge Chip, IRF510 MOSFET


## Project Demos 🎥

<ul>
    <li><a href="https://youtube.com/shorts/kciRXnAHQvI?feature=share">RFID Scanner Demo</a></li>
    <li><a href="https://youtube.com/shorts/CIawxQrrBTk?feature=share">App Demo</a></li>
  </ul>

## Project Photos 📸

![cad](https://github.com/BurhanNaveed0/Rackify/assets/81490717/ec92e03d-b6af-4a6b-8e18-d42a7be41182)

![cad2](https://github.com/BurhanNaveed0/Rackify/assets/81490717/c0512520-198d-45a0-8594-70b5868ea8bf)

![IMG_7626](https://github.com/BurhanNaveed0/Rackify/assets/81490717/81264308-35d3-4b13-9a9d-3d455c6e9af8)

## Event Highlights 🎉

![DSC_7644-min](https://github.com/BurhanNaveed0/Rackify/assets/81490717/def80458-15e6-4a25-8e8e-b95c818062e5)

![DSC_7452-min](https://github.com/BurhanNaveed0/Rackify/assets/81490717/7fe86e3b-9379-43f5-bee7-2b496c41b2ac)

## Reflection 📝

### What was the context for this project?
Rackify was a 24-hour project built during the NJIT IEEE Spring 2024 Hardware Hackathon. The project aimed to create a working prototype of a system to make life easier in an Urban setting. If we weren't going to invent an entirely new city infrastructure system, we wanted to advance some already existing component of it, and we found a smart bike lock project to be the most practical and useful design for Newark's environment. Some resources we used were electronic parts (DC Motors, Stepper Motors, RFID Scanners, Resistors, Transistors, etc.), microcontrollers (ESP32 and the Arduino), and makerspace tools (3D Printers, Laser Cutting Machines, etc.)

### What did your group set out to build? What was the planning process like?
We designed a prototype for a bike racking system that could be distributed throughout any city with users being able to pay for a rack via mobile app or with a pre-paid card. Upon deciding on the idea, we split up our crew of 5 into teams working on different sectors of the prototype based on their experience, with the group being split into mechanical, hardware, and software subteams. The mech sub-team was responsible for CADing the locking mechanism, 3D printing the gears, laser cutting the wood frame, and finally putting together the materials. The electrical subteam was responsible for picking the correct parts to direct power to each subunit of the locking mechanisms (motors, power sources, etc.), creating schematics for the motor control unit and the RFID scanner, and working with the mech team to assemble all electronics onto the bike lock. Lastly, the software subteam was responsible for coding the firmware to control the RFID scanner and the locking mechanism motors. On top of this, they also programmed the web server hosted on the ESP32 chip, as well as a mobile app for users to be able to remotely access the bike rack via their mobile devices. Overall, the planning process went pretty smoothly, and the splitting of the group was effective in making sure the project was completed within the time window provided. 

### How was this project a learning experience for your group?
This project was an excellent learning experience for all team members. Team members worked to put their prior Engineering/CS knowledge to the task in their respective areas, working fast in a high-stress environment with the deadline approaching within 24 hours. They also moved between subteams, gaining experience not only in their specialty but also in other areas they had never tried in (Software subteam helping with CADing, Electrical Subteam helping with writing firmware, etc.) The biggest learning experience, however, was with networking and marketing our product to the judges. Throughout the day, team members connected with other students and IEEE board members, exchanging progress reports on projects and helping each other out during technical difficulties. In the last 10 minutes of the hacking period, the team collaborated to create videos and project descriptions to submit on DevPost. After selection for the top 10, the team presented in front of qualified judges with only 5 minutes to present the project. The presentation forced us to talk about our project on the fly and work on our confidence despite having very minimal sleep from the night before. 

### What were some setbacks during development?
Despite completing our project within the allotted timeframe and winning 3rd place, it is safe so that production was not seamless. While individual sections of the project were completed on time and efficiently, the combination of sections was not. For one, the RFID scanner, despite working correctly in an isolated environment, was not working when attached to the locking mechanism, indicating that the re-assembly of the scanner electronics was done incorrectly. Secondly, the motor, which theoretically should have been able to power the ring gear used to engage the lock, was not doing so properly. Lastly, on the software side of things, the HTTP request sent from the app to the bike rack was not always being received due to the NJIT network's inbound request restrictions.

### What technologies were used?
The main element powering the hardware side of the project was the ESP32 Microcontroller. This microcontroller was an extremely important asset to our project as it allowed us to power our electronics with its GPIO capabilities as well as handle HTTP requests through its onboard WiFi chip. On the firmware side of things, the C++ Arduino Framework was used with the PlatformIO IDE to allow for quick and easy development for the board and easy access to countless pre-made drivers for parts like the RFID scanner and the stepper motor. For the mobile application portion of the project, due to the small amount of time left, a simple HTML mock application was created rather than a full-fledged React Native app, as it was easy to set up and get running for proof of concept. 

Resources: Electronic parts (DC Motors, Stepper Motors, RFID Scanners, Resistors, Transistors, etc.), Microcontrollers (ESP32 and the Arduino), and Makerspace tools (3D Printers, Laser Cutting Machines, etc.)
