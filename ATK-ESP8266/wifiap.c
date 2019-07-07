#include "common.h"
#include "string.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ATK-ESP8266 WIFIģ�� WIFI AP��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/4/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

char wificommnd[50] = {'A', 'T', '+', 'C', 'W', 'J', 'A', 'P', '=', '"'};
char wifiname[33] = {'w', 'i', 'f', 'i', 'n', 'a', 'm', 'e'};
char wifipsword[16] = {1, 2, 3, 4, 5, 6, 7, 8};
char *i;
unsigned char g = 100;
int atk_8266_connect_to_wifi()
{
	strcat(wificommnd, wifiname);
    strcat(wificommnd, "\",\"");
    strcat(wificommnd, wifipsword);
    strcat(wificommnd, "\"");
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);
    atk_8266_send_cmd("AT+RST", "ready", 20);
    delay_ms(500);
    while(g > 2){
        if(atk_8266_send_cmd(wificommnd, "OK", 300) == 0){
				i = "successd";
				return 0;
			}
        else g--;
    }
	i = "fail";
    return 1;
}

void get_imformation(u8 a)
{
    u8 g = 0, h;
    while(g < 20){
			if(USART3_RX_BUF[g] == ':')
					break;
			g++;
    }
		g++;
		h = g;
    for( ;USART3_RX_BUF[g] != '\0';g++){
        if(a == 2)
            wifiname[g - h] = USART3_RX_BUF[g];
        if(a == 3)
            wifipsword[g - h] = USART3_RX_BUF[g];
    }
}

//ATK-ESP8266 WIFI AP����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������
void setwifi(void)
{
    u8 g = 0, rlen, k;
    char *strx = 0, *str = "0,CONNECT";
	Show_Str_Mid(0, 40, "��������wifiģ�飬���Ե�......", 24, 240);
    atk_8266_send_cmd("AT+CWMODE=2", "OK", 200);
    atk_8266_send_cmd("AT+RST", "ready", 20);
    delay_ms(1000);
    atk_8266_send_cmd("AT+CIPMUX=1", "OK", 200);
    atk_8266_send_cmd("AT+CWSAP=\"ATK_ESP8266\",\"12345678\",6,4", "OK", 300);
    atk_8266_send_cmd("AT+CIPAP=\"192.168.4.1\"", "OK", 200);
    atk_8266_send_cmd("AT+CIPSERVER=1,8080", "ready", 20);
    Show_Str(40, 100, 50, 50, "OK", 24, 0);
    delay_ms(200);
    while(1){
        if(USART3_RX_STA&0X8000){
                g++;
            rlen = USART3_RX_STA&0X7FFF;
            USART3_RX_BUF[rlen]=0;
            LCD_Clear(WHITE);
            get_imformation(g);
	        POINT_COLOR=BLUE;
		    Show_Str(30, 130, 180,100,USART3_RX_BUF,24,1);//��ʾ���յ�������
			Show_Str(30, 330, 180 ,190, wifiname, 24, 1);
			Show_Str(30, 430, 180 ,190, wifipsword, 24, 1);
			USART3_RX_STA=0;
        }
        if(USART_RX_STA&0X8000){
          g++;
          rlen = USART_RX_STA&0X7FFF;
          USART_RX_BUF[rlen]=0;
          LCD_Clear(WHITE);
					POINT_COLOR=GREEN;
					Show_Str(30, 130, 180,100,USART_RX_BUF,24,1);//��ʾ���յ�������
					USART_RX_STA=0;
       }
			
		k = KEY_Scan(0);
        if(k)
            break;
    }
    while(atk_8266_connect_to_wifi());	
	LCD_Fill(30,50,239,50+12,WHITE);			//���֮ǰ����ʾ
	Show_Str(30,130,180,190,i,12,0); 
} 

