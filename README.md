# AVR-ArduinoTimer
An AVR based multi-interrupt handling with Latency Measurement Demo

# AVR Timer with TM1637 Display and Buzzer

## Project Overview
This project is a hardware-level demonstration of interrupt handling in AVR architecture using ARDUINO UNO R3(ATmega328p).
The timer output is shown on a TM1637 4-digit display.
When the timer is interrupted by any of the 2 interrupts, an active buzzer beeps (details in the docx file given).
This is to show the difference between AVR and ARM Cortex based architecure where ARM Cortex uses a NVIC and allows nesting of interrupts whereas AVR doesn't use them and thus do not allow masking/nesting of prioritised interrupts.
It additionally the software latency time before display 9999 or 8888 according to the interrupt.

## Components Used
- AVR Microcontroller (ARDUINO UNO R3)
- TM1637 4-digit display
- Active buzzer
- Jumper wires
- Breadboard

## How It Works
The microcontroller controls the display and updates time.
When an interrupt happens, buzzer is triggered and the display shows 9999 on high priority interrupt along with the latency and 8888 on medium priority interrupt with the latency too .

## Author
Aritra Das

## Circuit Diagram
<img width="1711" height="757" alt="Screenshot 2026-02-28 220433" src="https://github.com/user-attachments/assets/16b41ca2-7c70-421d-b274-4720bdd92b2f" />

