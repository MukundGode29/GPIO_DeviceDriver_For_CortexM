
#include "main.h"


int main (void)
{
	
	uint32_t i;
	led_init();
	
	_HAL_RCC_GPIOC_CLK_ENABLE();
	
	hal_gpio_configure_interrupt(USER_BUTTON, INT_FALLING_EDGE);
	
	hal_gpio_interrupt_enable(USER_BUTTON, EXTI9_5_IRQn);
	
	
	
	while(1)
	{
	 led_turn_on(GPIOA, LED_BLUE);
		
	 for(i = 0; i < 500000; i++);
		
		led_turn_off(GPIOA, LED_BLUE);
		
		for(i = 0; i < 500000; i++);
	}

 return 0;
	 
}

void led_init(void)
{
 gpio_pin_conf_t led_pin_conf;

 //Enable clock for GPIOC port 
	_HAL_RCC_GPIOA_CLK_ENABLE(); 
	
	led_pin_conf.pin = LED_BLUE;
	led_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
	led_pin_conf.op_type = GPIO_PIN_OUTPUT_PULLUP;
	led_pin_conf.speed = GPIO_SPEED_MEDIUM;
	led_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	
}

void led_turn_on( GPIO_TypeDef *GPIOx, uint16_t pin)
{
 hal_gpio_write_pin(GPIOx, pin, 1);
}

void led_turn_off( GPIO_TypeDef *GPIOx, uint16_t pin)
{
 hal_gpio_write_pin(GPIOx, pin, 0);
}

void led_turn_toggle( GPIO_TypeDef *GPIOx, uint16_t pin)
{
 if(hal_gpio_read_pin(GPIOx,pin))
 {
 hal_gpio_write_pin(GPIOx, pin, 0);
 }
 else
 {
  hal_gpio_write_pin(GPIOx, pin, 1);
 } 
}

void EXTI9_5_IRQHandler(void)
{
	hal_gpio_clear_interrupt(USER_BUTTON);
	led_turn_toggle(GPIOA, LED_BLUE);

}

