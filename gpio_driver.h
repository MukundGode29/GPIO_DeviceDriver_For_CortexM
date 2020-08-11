#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f446xx.h"

/************************************************************/
/*                                                          */
/*           1. GPIO Register bit Defination MACROS         */
/*                                                          */
/************************************************************/

//GPIO mode setting values

#define GPIO_PIN_INPUT_MODE                    ((uint32_t)0x00)
#define GPIO_PIN_OUTPUT_MODE                   ((uint32_t)0x01)
#define GPIO_PIN_ALTERNATE_FUNCTION_MODE       ((uint32_t)0x02)

//GPIO output type setting
#define GPIO_PIN_OUTPUT_PULLUP                 ((uint32_t)0x00)
#define GPIO_PIN_OUTPUT_OPEN_DRAIN             ((uint32_t)0x01)

//GPIO output speed setting
#define GPIO_SPEED_LOW                         ((uint32_t)0x00)
#define GPIO_SPEED_MEDIUM                      ((uint32_t)0x00)
#define GPIO_SPEED_HIGH                        ((uint32_t)0x02)
#define GPIO_SPEED_VERY_HIGH                   ((uint32_t)0x03)

//GPIO pull up/down setting
#define GPIO_PIN_NO_PULL_PUSH                  ((uint32_t)0x00)
#define GPIO_PIN_PULL_UP                       ((uint32_t)0x01)
#define GPIO_PIN_PULL_DOWN                     ((uint32_t)0x02)


//gpio port address

#define GPIO_PORT_A GPIOA 
#define GPIO_PORT_B GPIOB
#define GPIO_PORT_C GPIOC
#define GPIO_PORT_D GPIOD
#define GPIO_PORT_E GPIOE
#define GPIO_PORT_F GPIOF
#define GPIO_PORT_G GPIOG
#define GPIO_PORT_H GPIOH


// MACROS to Enable Clock for differnebt GPIO ports in RCC register

#define _HAL_RCC_GPIOA_CLK_ENABLE()      (RCC->AHB1ENR |=  (1 << 0) )
#define _HAL_RCC_GPIOB_CLK_ENABLE()      (RCC->AHB1ENR |=  (1 << 1) )
#define _HAL_RCC_GPIOC_CLK_ENABLE()      (RCC->AHB1ENR |=  (1 << 2) )
#define _HAL_RCC_GPIOD_CLK_ENABLE()      (RCC->AHB1ENR |=  (1 << 3) )
#define _HAL_RCC_GPIOE_CLK_ENABLE()      (RCC->AHB1ENR |=  (1 << 4) )
#define _HAL_RCC_GPIOF_CLK_ENABLE()      (RCC->AHB1ENR |=  (1 << 5) )
#define _HAL_RCC_GPIOG_CLK_ENABLE()      (RCC->AHB1ENR |=  (1 << 6) )
#define _HAL_RCC_GPIOH_CLK_ENABLE()      (RCC->AHB1ENR |=  (1 << 7) )


/************************************************************************/
/*                                                                      */
/*              Data structure fr GPIO pin INITIALIZATION               */
/*                                                                      */
/************************************************************************/

/**
*  @brief GPIO pin confriguration structure
*         This structure will be filled and passed to driver by the application 
*         initialize the gpio pin
*/

typedef struct
	{
		uint32_t pin;  //Specifies gpio pin to be configure
		
		uint32_t mode;  //Specifies operating mode for selected pin 
		
		uint32_t op_type;  //Specifies the output type for selected pin
		
		uint32_t pull;  //Specfies the pull up or pull down
		
		uint32_t speed;  //Specifies the speed for selected pin
		
		uint32_t alternate;  //Specifies the alternate function value

}gpio_pin_conf_t;
	
typedef enum
	{
		INT_RISING_EDGE,
		INT_FALLING_EDGE,
		INT_RISING_FALLING_EDGE,
		
}int_edge_sel_t;
	

/************************************************************************/
/*                                                                      */
/*              Driver exposed APIs                                     */
/*                                                                      */
/************************************************************************/


 
static void hal_gpio_configure_pin_mode(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t mode);

static void hal_gpio_configure_op_mode(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t mode);

static void hal_gpio_configure_speed_mode(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t mode);

static void hal_gpio_configure_pupd_mode(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t pupd);

static void hal_gpio_configure_pin_alternate_function(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t alt_fun);

void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf);

uint8_t hal_gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no);

void hal_gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t val);

void hal_gpio_configure_interrupt(uint16_t pin_no, int_edge_sel_t edge_sel);

void hal_gpio_interrupt_enable(uint16_t pin_no, IRQn_Type irq_no);

void hal_gpio_clear_interrupt(uint16_t pin_no);




#endif  