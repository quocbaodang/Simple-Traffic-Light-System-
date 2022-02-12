#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "lcd16x2.h"

#define LED7SEG_A   GPIO_Pin_0
#define LED7SEG_B   GPIO_Pin_1
#define LED7SEG_C   GPIO_Pin_2
#define LED7SEG_D   GPIO_Pin_3
#define LED7SEG_E   GPIO_Pin_4
#define LED7SEG_F   GPIO_Pin_5
#define LED7SEG_G   GPIO_Pin_6
#define LED7SEG_DP  GPIO_Pin_7

#define LED1        GPIO_Pin_1
#define LED2        GPIO_Pin_3

#define LED_Do        GPIO_Pin_4
#define LED_Vang      GPIO_Pin_5
#define LED_Xanh      GPIO_Pin_6

#define LED_Do1        GPIO_Pin_7
#define LED_Vang1     GPIO_Pin_8
#define LED_Xanh1     GPIO_Pin_9

#define PORT_LED7SEG_CODE GPIOA
#define PORT_LED          GPIOB

#define PORT_LED7SEG_CODE_CLOCK     RCC_APB2Periph_GPIOA
#define PORT_LED_CLOCK              RCC_APB2Periph_GPIOB

uint16_t LED7SEG[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void Clock_Config(void);

int main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    
  /*enble clock for GPIOC*/
  RCC_APB2PeriphClockCmd(PORT_LED7SEG_CODE_CLOCK | PORT_LED_CLOCK, ENABLE);
    
  /*Configuration GPIO pin*/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin  = LED7SEG_A|LED7SEG_B|LED7SEG_C|LED7SEG_D|LED7SEG_E|LED7SEG_F|LED7SEG_G|LED7SEG_A|LED7SEG_DP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PORT_LED7SEG_CODE, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin  = LED1 | LED2;
  GPIO_Init(PORT_LED, &GPIO_InitStructure); 

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin  = LED_Do | LED_Vang | LED_Xanh | LED_Do1 | LED_Vang1 | LED_Xanh1 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(PORT_LED, &GPIO_InitStructure);  
	
	DelayInit();
	lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
		
	GPIO_SetBits(PORT_LED, LED_Do); 
  GPIO_SetBits(PORT_LED, LED_Vang); 
	GPIO_SetBits(PORT_LED, LED_Xanh);
	GPIO_SetBits(PORT_LED, LED_Do1); 
  GPIO_SetBits(PORT_LED, LED_Vang1); 
	GPIO_SetBits(PORT_LED, LED_Xanh1);
	
	lcd16x2_put_custom_char(2, 0, 0);
	lcd16x2_puts("TN Vi xu ly");
	lcd16x2_put_custom_char(1, 1, 0);
	lcd16x2_puts("Den giao thong");
	
 while(1){

	int i, j;
  for(i = 20; i > 3; i--){
			GPIO_ResetBits(PORT_LED, LED_Do);
			GPIO_ResetBits(PORT_LED, LED_Xanh1);
      for(j = 0; j < 24; j++){
          GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i/10]);
          GPIO_SetBits(PORT_LED, LED1);  // LED1 = 1 
          DelayMs(10);
          GPIO_ResetBits(PORT_LED, LED1); //LED1 = 0
						
          GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i%10]);
          GPIO_SetBits(PORT_LED, LED2); //LED2 = 1
          DelayMs(10);
          GPIO_ResetBits(PORT_LED, LED2); //L7S2 = 0
        }
   }
	GPIO_SetBits(PORT_LED, LED_Xanh1);
	GPIO_SetBits(PORT_LED, LED_Do);
				
	for(i = 3; i >= 0; i--){
			GPIO_ResetBits(PORT_LED, LED_Vang);
			GPIO_ResetBits(PORT_LED, LED_Vang1);
      for(j = 0; j < 24; j++){
          GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i/10]);
          GPIO_SetBits(PORT_LED, LED1);  // LED1 = 1 
          DelayMs(10);
          GPIO_ResetBits(PORT_LED, LED1); //LED1 = 0
					
          GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i%10]);
          GPIO_SetBits(PORT_LED, LED2); //LED2 = 1
          DelayMs(10);
          GPIO_ResetBits(PORT_LED, LED2); //L7S2 = 0
       }
  }
	GPIO_SetBits(PORT_LED, LED_Vang);
	GPIO_SetBits(PORT_LED, LED_Vang1);
				
	for(i = 20; i > 3; i--){
		 GPIO_ResetBits(PORT_LED, LED_Xanh);
		 GPIO_ResetBits(PORT_LED, LED_Do1); 
     for(j = 0; j < 24; j++){
			 
				GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i/10]);
				GPIO_SetBits(PORT_LED, LED1);  // LED1 = 1 
        DelayMs(10);
        GPIO_ResetBits(PORT_LED, LED1); //LED1 = 0
						
        GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i%10]);
        GPIO_SetBits(PORT_LED, LED2); //LED2 = 1
        DelayMs(10);
        GPIO_ResetBits(PORT_LED, LED2); //L7S2 = 0
       }
    }
				
				GPIO_SetBits(PORT_LED, LED_Xanh); 
			  GPIO_SetBits(PORT_LED, LED_Do1); 
				
		for(i = 3; i >= 0; i--){
				GPIO_ResetBits(PORT_LED, LED_Vang);
				GPIO_ResetBits(PORT_LED, LED_Vang1);
        for(j = 0; j < 24; j++){
            GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i/10]);
            GPIO_SetBits(PORT_LED, LED1);  // LED1 = 1 
            DelayMs(10);
            GPIO_ResetBits(PORT_LED, LED1); //LED1 = 0
						
            GPIO_Write(PORT_LED7SEG_CODE, LED7SEG[i%10]);
            GPIO_SetBits(PORT_LED, LED2); //LED2 = 1
            DelayMs(10);
            GPIO_ResetBits(PORT_LED, LED2); //L7S2 = 0
         }
    }
		GPIO_SetBits(PORT_LED, LED_Vang);
		GPIO_SetBits(PORT_LED, LED_Vang1);
				
    }
		
	}
	


