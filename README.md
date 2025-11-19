# STM32G071 UART CLI

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Platform](https://img.shields.io/badge/platform-STM32G071-green.svg)](https://www.st.com/en/microcontrollers-microprocessors/stm32g071rb.html)
[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

A bare-metal UART command-line interface (CLI) implementation for the STM32G071RB microcontroller with support for GPIO control and SPI flash memory operations.

## Overview

This project demonstrates a minimal yet functional CLI system built directly on STM32G071 hardware without using HAL libraries or CubeMX code generation. It features interrupt-driven UART communication, an extensible command parser, and peripheral control capabilities.

### Key Features

- **Bare-Metal Implementation**: Direct register-level programming without HAL dependencies
- **UART Interface**: Interrupt-driven USART2 communication at 19200 baud
- **Command Parser**: Modular and easily extensible command table architecture
- **GPIO Control**: LED manipulation for visual feedback
- **SPI Flash Support**: W25Qxx flash memory interface with JEDEC ID reading
- **Low Resource Usage**: Minimal memory footprint suitable for embedded applications

## Hardware Requirements

| Component | Specification |
|-----------|--------------|
| **Microcontroller** | STM32G071RB (Nucleo-G071RB board) |
| **UART Interface** | USART2 @ 19200 baud, 8N1 |
| **LEDs** | Green and Blue LEDs (GPIO-controlled) |
| **Flash Memory** | W25Qxx SPI Flash (optional) |
| **Serial Terminal** | Any terminal emulator (PuTTY, Tera Term, etc.) |

## Software Requirements

- **Toolchain**: ARM GCC toolchain or STM32CubeIDE
- **Debugger**: ST-LINK (integrated on Nucleo board)
- **Terminal**: Serial terminal application supporting 19200 baud

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/kgsinh/stm32g071_uart_cli.git
cd stm32g071_uart_cli
```

### 2. Build the Project

#### Using STM32CubeIDE

1. Import the project: `File > Open Projects from File System`
2. Select the project directory
3. Build the project: `Project > Build Project` or press `Ctrl+B`

#### Using Command Line (ARM GCC)

```bash
# Ensure arm-none-eabi-gcc is in your PATH
make clean
make all
```

### 3. Flash the Firmware

#### Using STM32CubeIDE

1. Connect the Nucleo board via USB
2. Click `Run > Debug` or press `F11`
3. The firmware will be flashed and execution will start

#### Using st-flash (Command Line)

```bash
st-flash write build/output.bin 0x08000000
```

### 4. Connect Serial Terminal

1. Identify the COM port (check Device Manager on Windows or `/dev/ttyACM*` on Linux)
2. Configure terminal settings:
   - **Baud Rate**: 19200
   - **Data Bits**: 8
   - **Parity**: None
   - **Stop Bits**: 1
   - **Flow Control**: None
3. Open the connection

## Usage

Upon successful connection, you should see:

```
UART CLI Ready. Type 'help' for commands.
```

### Available Commands

| Command | Description | Usage Example |
|---------|-------------|---------------|
| `help` | Display list of available commands | `help` |
| `led on` | Turn the green LED on | `led on` |
| `led off` | Turn the green LED off | `led off` |
| `flash` | Read JEDEC ID from W25Qxx SPI flash | `flash` |

### Example Session

```
> help
Available commands:
  led - Control the LED: led <on|off>
  help - Show this help message
  flash - Read JEDEC ID from W25Qxx flash

> led on
LED is ON

> led off
LED is OFF

> flash
JEDEC ID: Manufacturer: 0xEF, Memory Type: 0x40, Capacity: 0x18
```

## Project Structure

```
stm32g071_uart_cli/
├── Inc/                        # Header files
│   ├── cli.h                   # CLI interface definitions
│   ├── led.h                   # LED control functions
│   ├── spi.h                   # SPI peripheral interface
│   ├── systick.h               # SysTick timer
│   ├── uart.h                  # UART communication
│   └── w25qxx.h                # W25Qxx flash memory driver
├── Src/                        # Source files
│   ├── cli.c                   # Command parser implementation
│   ├── led.c                   # LED control implementation
│   ├── main.c                  # Main application entry point
│   ├── spi.c                   # SPI driver implementation
│   ├── syscalls.c              # System call stubs
│   ├── sysmem.c                # Memory management
│   ├── systick.c               # SysTick implementation
│   ├── uart.c                  # UART driver implementation
│   └── w25qxx.c                # W25Qxx flash driver
├── Startup/                    # Startup code
│   └── startup_stm32g071rbtx.s # Assembly startup file
├── STM32G071RBTX_FLASH.ld      # Linker script
├── .cproject                   # Eclipse CDT project file
├── .project                    # Eclipse project file
├── 01_UART_CLI.launch          # Debug configuration
├── LICENSE                     # Apache 2.0 license
└── README.md                   # This file
```

## Architecture

### UART Communication

The UART module uses interrupt-driven reception:
- **USART2_IRQHandler**: Processes incoming characters
- **Command Buffer**: Accumulates characters until newline (`\r` or `\n`)
- **Main Loop**: Polls for complete commands and dispatches to parser

### Command Processing

1. User types command and presses Enter
2. ISR buffers the complete command
3. Main loop detects command ready flag
4. Command parser tokenizes input
5. Matching handler function is executed
6. Response is sent back via UART

### CLI Extension

To add new commands:

1. **Define handler function** in `Src/cli.c`:
```c
static void cmd_newcommand(char *args) {
    // Implementation
    printf("New command executed\n\r");
}
```

2. **Add to command table** in `Src/cli.c`:
```c
command_t commands[] = {
    {"newcommand", cmd_newcommand, "Description of new command"},
    // ... existing commands
};
```

3. **Rebuild and flash** the firmware

## Technical Specifications

### Memory Layout

- **Flash**: 128 KB (0x08000000 - 0x0801FFFF)
- **SRAM**: 36 KB (0x20000000 - 0x20008FFF)

### Peripheral Configuration

- **USART2**: Asynchronous mode, 19200 baud, RX interrupt enabled
- **SPI1**: Master mode for W25Qxx flash communication
- **GPIO**: Output pins for LED control
- **SysTick**: System timer for delays and timing

## Troubleshooting

### No Output in Terminal

- Verify correct COM port selection
- Check baud rate (must be 19200)
- Ensure USB cable is connected properly
- Try resetting the board

### Commands Not Responding

- Check for proper command termination (press Enter)
- Verify serial terminal sends CR or LF
- Monitor for buffer overflow (commands > 128 characters)

### Build Errors

- Ensure ARM GCC toolchain is properly installed
- Check that all source files are included in build
- Verify linker script path is correct

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-feature`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/new-feature`)
5. Open a Pull Request

Please ensure your code follows the existing style and includes appropriate documentation.

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- STMicroelectronics for the STM32G0 series documentation
- ARM for the Cortex-M0+ architecture reference
- The embedded systems community for inspiration and best practices

## Author

**kgsinh**
- GitHub: [@kgsinh](https://github.com/kgsinh)

## References

- [STM32G071RB Datasheet](https://www.st.com/resource/en/datasheet/stm32g071rb.pdf)
- [STM32G0 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0444-stm32g0x0-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [W25Qxx Flash Memory Datasheet](https://www.winbond.com/hq/product/code-storage-flash-memory/serial-nor-flash/)

---

**Note**: This is a learning/demonstration project. For production use, consider implementing additional error handling, input validation, and security measures.
