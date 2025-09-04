# stm32g071_uart_cli

# STM32G071 UART CLI Project

A minimal UART-based command-line interface (CLI) for STM32G071 microcontroller.  
Supports simple commands such as toggling onboard LEDs using a serial terminal.

---

## Features
- Bare-metal implementation (no HAL, no CubeMX)
- UART RX interrupt-driven input
- Command parser with easily extendable command table
- Three commands supported:
  - `led on` → Turns LED ON
  - `led off` → Turns LED OFF
  - `help` → Lists available commands

---

## Hardware Setup
- **MCU:** STM32G071RB (Nucleo board)
- **UART:** USART2 @ 19200 baud
- **LEDs:** green and blue LEDs connected to GPIO

---

## Project Structure
```
.
├── Inc
│   ├── cli.h            # CLI command definitions
│   ├── led.h           # GPIO initialization and control for led
│   ├── systick.h           # SysTick header file
│   ├── stm32g0xx.h     # STM32G0xx device header
│   └── uart.h         # USART initialization and control
├── Src
│   ├── cli.c           # CLI implementation
│   ├── led.c          # GPIO implementation for led
│   ├── main.c          # Main application logic
│   └── uart.c        # USART implementation
└── README.md           # Project documentation
```
---
## Getting Started
### Prerequisites
- STM32CubeIDE or any ARM GCC toolchain
- A serial terminal (e.g., PuTTY, RealTerm)
- STM32G071 Nucleo board
- Jumper wires for connecting LED pins if necessary

Clone the repository:
```bash
git clone

### Running the CLI
1. Open your serial terminal and connect to the appropriate COM port at 19200 baud, 8 data bits, no parity, 1 stop bit.
2. Type `led on` to turn the LED on and `led off` to turn it off.
3. Press Enter after typing each command.
4. You should see feedback in the terminal confirming the command execution.
### Example Commands
 ```
   led on
   led off
 ```
### Extending the CLI
To add more commands, modify the `cli.c` file and update the command table in `cli.h`. Implement the corresponding handler functions to define the behavior for each new command.
   ---
## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
   ---
## Contact
   Feel free to reach out if you have any questions or need further assistance!