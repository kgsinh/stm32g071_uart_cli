/**
 * @file systick.h
 * @brief This header file has functions to generate delay
 *
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/**
 * @fn void systickDelayus(int)
 * @brief This function will generate delay in microseconds
 * using systick
 *
 * @param delay Delay value in us
 */
void systickDelayus(int delay);

/**
 * @fn void systickDelayms(int)
 * @brief This function will generate delay in milliseconds
 * using systick
 *
 * @param delay Delay value in ms
 */
void systickDelayms(int delay);


#endif /* SYSTICK_H_ */
