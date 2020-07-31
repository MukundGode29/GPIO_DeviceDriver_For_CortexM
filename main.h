#ifndef __LED_H
#define __LED_H


#include "gpio_driver.h"

#define GPIOA_PIN_5   5

#define LED_BLUE      GPIOA_PIN_5

#define GPIOC_PIN_13    13
#define USER_BUTTON     GPIOC_PIN_13

void led_init(void);

void led_turn_on( GPIO_TypeDef *GPIOx, uint16_t pin);

void led_turn_off( GPIO_TypeDef *GPIOx, uint16_t pin);

void led_turn_toggle( GPIO_TypeDef *GPIOx, uint16_t pin);

void EXTI9_5_IRQHandler(void);


#endif