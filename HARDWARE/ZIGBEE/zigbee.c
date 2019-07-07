#include "zigbee.h"

struct receive_data receive;

/*
函数名称：zigbee_send_data
参数：  结构体send_data
*/
void zigbee_send_data(struct send_data* send)
{
    u8 pack[15] = {0xFE, 0x04}, g, flag = 0; //flag用于转义
    pack[1] = 0x04 + send->num;
		pack[2] = send->source;
		pack[3] = send->target;
    pack[4] = send->addr[1];
    pack[5] = send->addr[0];     //使用小地址端发送
    for(g = 0;g < send->num;g++){
        pack[6 + g + flag] = send->data[g];
        if(send->data[g] == 0xFE){
            flag++;
            pack[6 + g + flag] = 0xFC;
        }
        if(send->data[g] == 0xFF){
            flag++;
            pack[6 + g] = 0xFE;
            pack[6 + g + flag] = 0xFD;
        }
    }                        //拼出将要发送的包
    pack[6 + send->num + flag] = 0xFF;
    for(g = 0;g < 7 + send->num + flag;g++)
        printf("%c", pack[g]);  //发送包
}

/*
函数名：zigbee_get_data
功能：将数据从接收到的包中提取出来
参数：数据包数组
*/
void zigbee_get_data(u8* pack)
{
    int number, g, flag=0;
		u8 o_receive[99];        //此处以后需要优化 o_receive只是用来存放转义后的结果，之后再放入receive结构体中
    number = pack[1];
    for(g = 0; g < number; g++){
			if(pack[2 + g] == 0xFE){
				o_receive[g - flag]=pack[3 + g] + 2;
				flag++;
				g++;
			}
			else{
				o_receive[g - flag]=pack[2 + g];
			}
    }
		
		receive.source = o_receive[0];
		receive.source = o_receive[1];
		
		for(g = 4; g < number - 4; g++)
				receive.data[g - 4] = o_receive[g];
}

/*
函数名: find_light
功能:   F4通过ZigBee发送到目标从板并亮指定的灯
参数:   addr 目标ZigBee的地址
				x,y  要亮的灯的横纵坐标
*/
void find_light(u8 *addr, u8 x, u8 y)
{
		struct send_data send;
	
		send.num = 2;
		send.source = 0x80;
		send.target = 0x80;        //亮灯这一个功能用0x80端口
		send.addr[0] = addr[0];
		send.addr[1] = addr[1];
	
		send.data[0] = x;
		send.data[1] = y;
	
		zigbee_send_data(&send);
}

/*
函数名: send_parameter
功能:  F4通过ZigBee向F1发送要使用的配置
				数据格式为2位地址 2位网络ID 1位信道
参数:  地址addr
			 结构体parameter
*/
void send_parameter(u8 *addr, struct parameter *par)
{
		struct send_data send;
		
		send.num = 5;
		send.source = 0x90;
		send.source = 0x90;
		send.addr[0] = addr[0];
		send.addr[1] = addr[1];
	
		send.data[0] = par->addr[0];
		send.data[1] = par->addr[1];
		send.data[2] = par->NET_ID[0];
		send.data[3] = par->NET_ID[1];
		send.data[4] = par->channel;
	
		zigbee_send_data(&send);
}
