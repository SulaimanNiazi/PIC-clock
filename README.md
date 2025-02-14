# PIC Clock

This project is a firmware application designed for the PIC16F877A microcontroller to function as a clock. It displays the time on 7 segment display. The firmware is developed using the MPLAB X IDE and the XC8 compiler.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Apparatus](#apparatus)
- [Uploading to the Microcontroller](#uploading-to-the-microcontroller)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)

## Prerequisites

- MPLAB X IDE
- XC8 Compiler
- PIC16F877A Microcontroller

## Building the Project

1. Open the project in MPLAB X IDE.
2. Ensure the XC8 compiler is selected.
3. Build the project to generate the `.hex` or `.cof` file.
4. Alternatively, you can build the project using Visual Studio Code with the MPLAB extension. Set the project output file path, name, and extension using `Ctrl+Shift+P` and selecting "Edit Project Properties".

## Apparatus

Necessary components that can't be changed:

1. PIC16F877A microcontroller: To run the program.
2. LM016L LCD display: To display output.
3. Quartz Crystal and 2 1nF non-polarized capacitors.

Optional components depending on your circuit:

1. Button: For setting the time.
2. LED: To indicate the clock is running.
3. OP-47 Op-Amp: For amplifying sensory input.
4. RLY-SPNO Magnetic Relay: To provide stable 5V to CCP pin.
5. Rheostat: To adjust op-amp potential according to sensor input.
6. APDS-9002 Miniature Surface-mount Light Photo Sensor: For detecting ambient light.
7. 5 Resistors.

## Uploading to the Microcontroller

After building the project, upload the generated `.hex` or `.cof` file to the PIC16F877A microcontroller using a suitable programmer. The file can be found in either of the following paths:

1. In case of using MPLAB X IDE: [dist\default\debug\PIC_Clock.X.debug.cof](./dist/default/debug/PIC_Clock.X.debug.cof)
2. In case of using Visual Studio Code (if the file name was set as default): [out\PIC_Clock\default.hex](./out/PIC_Clock/default.hex)

## Usage

1. Connect the microcontroller and the necessary components as per the circuit diagram, it is important to note:

    - The first half of the variable `displayPort` gives the BCD output of the digit.
    - The other half of `displayPort` is for enabling the digits (from 1 to 4).
    - We can provide 25Hz 5V clock signal input, before turning PIC on, for external clock sync.

2. Power on the system.
3. The LCD will display the current time.
4. Use the button to set the time if needed.

## Troubleshooting

- Ensure all connections are secure and correct.
- Verify the microcontroller is programmed with the correct `.hex` or `.cof` file.
- Check the power supply to the microcontroller and other components.
- If the LCD does not display correctly, check the connections and contrast settings.