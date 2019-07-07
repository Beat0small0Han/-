#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_

typedef unsigned char u8;

extern struct receive_data{  //ZigBee每次接收数据所用的容器结构体
	u8 data[10];
	u8 source;
	u8 target;
}receive;

struct send_data{   //作为ZigBee每次发送数据所使用的结构体
	u8 data[99];
	u8 num;        //此num表示真正的数据的个数，不包含地址和源目端口
	u8 addr[2];
	u8 source;
	u8 target;
};

struct parameter{    //zigbee 配置自身的地址，网络ID以及信道
	u8 addr[2];
	u8 NET_ID[2];
	u8 channel;
};

void zigbee_send_data(struct send_data* send);
void zigbee_get_data(u8* pack);
void find_light(u8 *addr, u8 x, u8 y);
void send_parameter(u8 *addr, struct parameter *par);

#endif
