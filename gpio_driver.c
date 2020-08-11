
#include "gpio_driver.h"



/************************************************************************/
/*                                                                      */
/*              Static Helper Function                                  */
/*                                                                      */
/************************************************************************/

/**
* @brief   Configure the mode of a pin : input, 
	*/
	
static void hal_gpio_configure_pin_mode(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t mode)
{
	GPIOx->MODER |= (mode << (2 * pin_no));

}

static void hal_gpio_configure_op_mode(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t mode)
{
  GPIOx->OTYPER |= (mode << pin_no);	

}

static void hal_gpio_configure_speed_mode(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t mode)
{
  GPIOx->OSPEEDR |= (mode << (2 * pin_no));
}

static void hal_gpio_configure_pupd_mode(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t pupd)
{
 GPIOx->PUPDR  |= (pupd << (2 * pin_no));
	
}

static void hal_gpio_configure_pin_alternate_function(GPIO_TypeDef *GPIOx, uint32_t pin_no, uint32_t alt_fun)
{
 if(pin_no <= 7)
 {
  GPIOx->AFR[0] |= (alt_fun << (4 * pin_no));
 }
 else
 {
  GPIOx->AFR[1] |= (alt_fun << (((pin_no % 8) * 4 )));
 }

	 
}


/************************************************************************************/

void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf)
{
	hal_gpio_configure_pin_mode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->mode);
  hal_gpio_configure_op_mode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->op_type);
	hal_gpio_configure_pupd_mode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->pull);
	hal_gpio_configure_speed_mode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->speed);
	hal_gpio_configure_pin_alternate_function(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->alternate);
}

uint8_t hal_gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no)
{
 uint8_t value;
	
	value = ((GPIOx->IDR >> pin_no) & 0x00000001);
  return value;
}

void hal_gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t val)
{
  if(val)
	{
	 GPIOx->ODR |= (1 << pin_no);
	}
	else 
	{
	 GPIOx->ODR &= ~(1 << pin_no);
	}
}

void hal_gpio_configure_interrupt(uint16_t pin_no, int_edge_sel_t edge_sel)
{
	if( edge_sel == INT_RISING_EDGE )
	{
		EXTI->RTSR |= 1 << pin_no;
	
	}
	else if( edge_sel == INT_FALLING_EDGE )
	{
		EXTI->FTSR |= 1 << pin_no;
	
	}
	else if (edge_sel == INT_RISING_FALLING_EDGE)
	{
		EXTI->RTSR |= 1 << pin_no;
		EXTI->FTSR |= 1 << pin_no;
		
	}

}

void hal_gpio_interrupt_enable(uint16_t pin_no, IRQn_Type irq_no)
{
	EXTI->IMR |= 1 << pin_no;
	NVIC_EnableIRQ(irq_no);
}

void hal_gpio_clear_interrupt(uint16_t pin_no)
{
	if(EXTI->PR &(1 << pin_no))
	{
		EXTI->PR |= 1 << pin_no;
	}

}


