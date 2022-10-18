# Sardauscan

Sardauscan is a 3D laser scanner aimed to cost less than 30$

It is quite possibly the lowest-cost 3D scanner currently available.

Hardware List: 
- Arduino Nano
- 1 to 4 line lase
- a a micro geared stepper (28BYJ-48)
- Hercule HD Twist webcam

This software is written in C# and Winforms, and is based on a system of tasks and processes.

A task is an operation, such as: scan, save file, filter noise, smooth, or build mesh.

A process is simply a list of tasks.

It is possible to develop and add your own tasks via plugins.

The software will not be linked to any specific hardware.
Using plugins, one could add harware controllers for additional cameras, turn tables and lasers.
For example, if you wish to use another scanner or webcam.

Directory "Firmware" => code for the arduino
Directory "STL" the source stl and 123Design file.
Directory "Sardauscan" => the client software

The code is written in C# and Winforms and is build on Visual Basic 2010, for Windows.

the firmware needed for the Adafruit Motor Shield library can be found here:
https://github.com/adafruit/AccelStepper

# Other scanners

Since horus is aparently dead, im adding support for other scanners to the turntable. If you have any specific scanner you want to add Pm me.

# [FabScanPi](https://fabscan.org/) (WIP) 

Supported G-Codes:

- G01 [T(steps)] - Move the Turntable for number of steps (needs testing)
- M4 [R(value) G(value) B(value)] - Turn on LED Ring for given RGB-Vlaues (not yet)
- M17 - Enable Motors (needs testing)
- M18 - Disable Motors (needs testing)
- M19 - Turn On Laser 0 (needs testing)
- M20 - Turn Off Laser 0 (nneeds testing)
- M21 - Turn On Laser 1 (needs testing)
- M22 - Turn Off Laser 1 (needs testing)
- M100 - Show Help Message (needs testing)
