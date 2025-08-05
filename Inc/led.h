/**
 * @file led.h
 * @brief header file for led initialization, led on and led off functions
 *
 */
#ifndef LED_H_
#define LED_H_

#include "stm32g071xx.h"

/**
 * @fn void led_init()
 * @brief This function initialize the red and blue leds
 *
 */
void led_init();

/**
 * @fn void red_led_on()
 * @brief This function will turn on red led which is
 * representing heating mode
 *
 */
void green_led_on();

/**
 * @fn void red_led_off()
 * @brief This function will turn off red led indicating heating is off
 *
 */
void green_led_off();

/**
 * @fn void blue_led_on()
 * @brief This function will turn on blue led indicating cooling mode is on
 *
 */
void blue_led_on();

/**
 * @fn void blue_led_off()
 * @brief  This function will turn off blue led indicating cooling is off
 *
 */
void blue_led_off();


#endif /* LED_H_ */
