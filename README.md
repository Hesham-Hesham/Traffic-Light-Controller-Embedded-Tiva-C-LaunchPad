#  Traffic Light Control System - Tiva C LaunchPad

## Objective
This project comprises of a traffic light control system that manages two car traffic lights (North-South and East-West) and two pedestrian traffic lights, one for each car traffic light. The system is equipped with two push buttons for pedestrians to press and safely cross the street.
<br></br>
The project leverages the TM4C123GH6PM LaunchPad evaluation kit which is based on the Arm Cortex-M4F microcontroller. This system is also designed based on a layered architecture model with configurable drivers 
 for maxiumum efficiency and modular functionality.

---

## Working Video

You can watch the project working irl [Here !](https://drive.google.com/file/d/15a2oQPOUUbti-yfZZS-AmDD-GLCu69gS/view?usp=sharing)

---
## Table of Contents

- [Working Video](#working-video)
- [System Features](#system-features)
- [Requirements](#requirements)
- [Drivers Requirements](#drivers-requirements)
- [Software Features](#software-features)
- [Components](#components)
- [Electric Circuit](#electric-circuit)
- [Usage](#usage)

---
## System Features

Interrupt Handling: The system can handle interruptions caused by pedestrian crossings without disrupting the overall traffic flow.
1. Pedestrian Crossing:
- Push Button Activation: Pedestrian lights are activated by push buttons. Pressing the button interrupts the active car traffic light and initiates the pedestrian crossing phase.
- Time Management: Pedestrian lights remain Green for 2 seconds, allowing safe crossing. After this period, they turn Red, and the interrupted car traffic light resumes its sequence.

2. Delayed Crossing:
- Intelligent Delay: If the pedestrian button is pressed within 1 second of the end of the pedestrian crossing period, the system intelligently delays the pedestrian request, ensuring synchronization with the traffic light sequence.

## Requirements

For the full detailed system sequence and components requirements, check [The Project requirements file](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/blob/main/Requirements.pdf).

## Drivers Requirements

### HAL
- LEDs Driver
- Push Buttons Driver
- Delay Driver

### MCAL

- External Interrupts Driver
- GPIO Driver
- Systick Timer Driver


### Layered Architecture

![Layered architecture](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/e01206d3-8be0-4051-98c4-0b5483aed2e1)

### Drivers Initialization

They're intialized with the sequence presented in this diagram:

![1](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/52899d06-bf46-469d-a301-2b5151ae4d1c)




## Software Features

### Configurable Drivers
- All HAL and MCAL drivers are configurable using configuration structures as well as preprocessor configurations.
> Preprocessor configurations example:

```
    #define TRAFFIC_NUMBER_OF_LED			6
    
    #define TRAFFIC_NORTH_PORT_ID			PORTB_ID
    #define TRAFFIC_NORTH_RED_PIN_ID 		PIN5_ID
    #define TRAFFIC_NORTH_YELLOW_PIN_ID 	PIN4_ID
    #define TRAFFIC_NORTH_GREEN_PIN_ID		PIN6_ID
```
<br/><br/>

> Configuration structures example:

```
typedef struct{
	SYSTICK_clockSource			clockSRC;
	SYSTICK_interruptEnable		interruptState;
	SYSTICK_enableSystick		systickState;
}SYSTICK_ConfigType;
```
---

```
typedef struct{
	uint8 								priority;
	uint8								port_num;
	uint8								pin_num;
	EXTERNAL_INTERRUPTS_interruptSense 	interrupt_senstivity;
	EXTERNAL_INTERRUPTS_edges			edges;		
	EXTERNAL_INTERRUPTS_event			event;
	
}EXTERNAL_INTERRUPTS_ConfigType;
```
<br/><br/>

### Maintainability
- The layers are empty of magic numbers and arbitration to improve the readability of the code and make it easier to modify in the future.
```
#define SYSTICK_CTRL_REG_ENABLE_BIT		0
#define SYSTICK_CTRL_REG_INTEN_BIT		1
```
```
#define MAX_PRIORITY_VALUE				7
```

<br/><br/>

- Modifying registers in the code is done using masks which ensures that only the desired bit/bits is/are modified in the register.
```
#define PRIn_INTF_MASK					0x00E00000
#define PRIn_INTF_PRIORITY_START_BIT	21

#define ICR_FLAG_BIT					5
```


### Special Pins Protection

- By looking at the datasheet we can see that some of the pins have alternative/special functions: 
![GPIO with special pins](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/f01709c9-8cce-4111-a197-9fd100feb774)
>So to protect these pins from accidently being initialized or used as GPIO after being initialized or used as something else in another driver, a special-pins-preprocessor-guard was added:
```
#define ENABLE_SPECIAL_PINS_PROTECTION		FALSE
```
<br/><br/>
> to make sure the pin is not initialized as GPIO in the init function in the GPIO driver:
```
#if (ENABLE_SPECIAL_PINS_PROTECTION == FALSE)
			if(pin_num==7){
				GPIO_PORTD_LOCK_REG   = 0x4C4F434B;   /* Unlock the GPIO_PORTD_CR_REG */
				SET_BIT(GPIO_PORTD_CR_REG,pin_num);
			}
#endif
```
~ The above code means: Avoid initializing pin 7 of PORTD if protection is enabled (if it's not unlocked or commited it won't be initialized).

----
- The most cruical special pins are the JTAG pins in port C since writing on them locks the TivaC board and makes it unusable till it gets unlocked again using a special software app, thus another specific guard was added to make sure that JTAG pins are protected special-pins-preprocessor-guard was added: 
```
#define ENABLE_JTAG_PINS_PROTECTION			TRUE
```
<br/><br/>
> to make sure the pin that JTAG pins are not written on unless intended:
```
#if (ENABLE_JTAG_PINS_PROTECTION == TRUE)
			//AVOID WRITING ON JTAG PINS TO AVOID MAKING THE LAUNCHPAD LOCKED
				break;
#endif
```

## Components


1. **Tiva C LaunchPad Evaluation Kit:**
   - To be used for its GPIO pins, timers, and interrupt capabilities.

2. **LEDs:**
   - Red, yellow, and green LEDs for both car traffic lights (2 sets) + Red and green LEDs for pedestrian traffic lights (2 sets).

3. **Push Buttons:**
   - Two push buttons for pedestrian crossings, one for each direction.

4. **Resistors:**
   - Current-limiting resistors for the LEDs to prevent them from burning out.

5. **Power Supply:**
   - A stable DC power supply for the LEDs.

6. **BC549 Transistors:**  
    - Used as gates for the LED current. (Check the electric circuit section).

7. **Voltage Regulator:**
    - To provide a stable 5V to the systems.



## Electric Circuit

### Circuit Diagram

![Last Loaded Traffic light control](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/b383800d-270e-4bf8-b5a7-79c10fec0888)


### BC549 Transistors
- After checking the datasheet of the Tiva C LaunchPad Evaluation Kit, we can see that the high level voltage is 2.4 V which is not enough to drive the LED.

![max v 2 4](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/19be1cef-9de8-4b79-92d4-0a494c7bfc8b)


- Thus we can use a transistor as a gate to operate the led and that transistor wil be controlled using the GPIO pin.

![transistor circuit](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/635a42d2-8123-4310-b5b7-c37f4abeb55f)

- Calculating for a BC549 Transistor, we can deduce these resistor values for the circuit:

![resistor values](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/d1abf116-8a19-4e7e-b9a0-5d68e98ba9dc)


### Push buttons

- The Pull-Up resistor configuration was used in hardware connection as well as software PUSH_BUTTONS driver confiuration:

![pull up](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/75b88aa9-00cc-4d15-84d6-978a22e2d9b2)


<br/><br/>

### Real Photos
![1](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/d724eeeb-30c4-4b3b-9429-3cc3cc87bd19)

![2](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/1e2a31ae-d0b3-425c-89ab-70e364179616)

![3](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/e43d6c73-d469-48da-9804-4779cd6eb718)

![4](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/assets/91581641/eccc245f-4435-4480-bda9-0ba59c9e2280)

---


## Usage
- ### Hardware target
    In order to run the code on a real hardware target (ARmega32), follow these steps:
1. **Setup**: Connect the components as per the circuit diagram.
2. **Compile**: Use an appropriate compiler to compile the provided source code.
3. **Program**: Program the Tiva C LaunchPad with the compiled binary.
4. **Run**: Power up the circuit. The traffic sequence will start immediately.
5. **User Interaction**: You can press any of the two pedestrian push buttons and the interrupt sequence will occur stopping the incoming traffic and allowing pedestrians to pass.



- ### Simulation
1. **Setup**: Connect the components as per the circuit diagram.
2. **Compile**: Use an appropriate compiler to compile the provided source code.
3. **Run**: Run the compiled binary on the simulator of an appropiate IDE (e.g., IAR Embedded Workbench).
4. **User Interaction**: You can change the values of the registers and use breakpoints while debugging to notice the changes that occur in the system.
<br/><br/>

---
##### Acknoledgement
- Some of the screenshots are taken from the "Interfacing an LED with TIVA C Series LaunchPad" video made by [Mechatronics Engineer Youtube Channel](https://www.youtube.com/@mechatronicsengineer1979).

- Registers mapping file "tm4c123gh6pm_registers.h" was made by engineer mohamed tarek.
