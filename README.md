# stm32g071_uart_cli

# STM32G071 UART CLI Project

A minimal UART-based command-line interface (CLI) for STM32G071 microcontroller.  
Supports simple commands such as toggling onboard LEDs using a serial terminal.

---

## Features
- Bare-metal implementation (no HAL, no CubeMX)
- UART RX interrupt-driven input
- Command parser with easily extendable command table
- Two commands supported:
  - `led on` → Turns LED ON
  - `led off` → Turns LED OFF

---

## Hardware Setup
- **MCU:** STM32G071RB (Nucleo board)
- **UART:** USART2 @ 19200 baud
- **LEDs:** green and blue LEDs connected to GPIO

---

## Project Structure
