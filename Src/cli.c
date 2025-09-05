#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "uart.h"
#include "led.h"
#include "w25qxx.h"

typedef void (*command_func_t)(char *args);

typedef struct
{
	const char *name;
	command_func_t handler;
	const char *help;
} command_t;

static void cmd_help(char *args);
static void cmd_led(char *args);
static void cmd_read_id(char *args);

command_t commands[] = {
	{"led", cmd_led, "Control the LED: led <on|off>"},
	{"help", cmd_help, "Show this help message"},
	{"flash", cmd_read_id, "Read JEDEC ID from W25Qxx flash"},
	{NULL, NULL, NULL} // Sentinel to mark the end of the array
};

static void cmd_help(char *args)
{
	printf("Available commands:\n\r");
	for (int i = 0; commands[i].name != NULL; i++)
	{
		printf("  %s - %s\n\r", commands[i].name, commands[i].help);
	}
}

static void cmd_led(char *args)
{
	char *saveptr;
	char *action = strtok_r(args, " ", &saveptr); //first token after "led"

	if (args == NULL)
	{
		printf("Usage: led <on|off>\n\r");
		return;
	}

	if (action == NULL)
	{
		printf("Usage: led <on|off>\n\r");
		return;
	}

	if (strncmp(action, "on", 2) == 0)
	{
		green_led_on();
		printf("LED is ON\n\r");
	}
	else if (strncmp(action, "off", 3) == 0)
	{
		green_led_off();
		printf("LED is OFF\n\r");
	}
	else
	{
		printf("Invalid action. Use 'led on' or 'led off'.\n\r");
	}

}

static void cmd_read_id(char *args)
{
	w25qxx_jedec_id_t id = w25qxx_read_jedec_id();


	// Placeholder for reading JEDEC ID
	printf("JEDEC ID: Manufacturer: 0x%02X, Memory Type: 0x%02X, Capacity: 0x%02X\n\r",
	       id.manufacturer_id, id.memory_type, id.capacity);
}

void process_command(char *cmd)
{
	char *saveptr;
	char *token = strtok_r(cmd, " ", &saveptr);

	if (token == NULL)
	{
		return;
	}

	for (int i = 0; commands[i].name != NULL; i++)
	{
		if (strncmp(token, commands[i].name, strlen(commands[i].name)) == 0)
		{
			char *args = strtok_r(NULL, "", &saveptr); // Get the rest of the command as arguments
			commands[i].handler(args);
			return;
		}
	}

	printf("Unknown command: %s\n\r", token);
}
