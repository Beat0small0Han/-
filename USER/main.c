#include "stm32f10x.h"
#include "usart1.h"
#include "usart2.h"
#include "zigbee.h"
#include "esp8266.h"
#include "led.h"
#include "key.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //ÖÐ¶Ï·Ö×é
	
	uart_init(115200);
	usart2_init(115200);
	KEY_Init();
	
	while(1);
}
