#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_

typedef unsigned char u8;

extern struct receive_data{  //ZigBeeÿ�ν����������õ������ṹ��
	u8 data[10];
	u8 source;
	u8 target;
}receive;

struct send_data{   //��ΪZigBeeÿ�η���������ʹ�õĽṹ��
	u8 data[99];
	u8 num;        //��num��ʾ���������ݵĸ�������������ַ��ԴĿ�˿�
	u8 addr[2];
	u8 source;
	u8 target;
};

struct parameter{    //zigbee ��������ĵ�ַ������ID�Լ��ŵ�
	u8 addr[2];
	u8 NET_ID[2];
	u8 channel;
};

void zigbee_send_data(struct send_data* send);
void zigbee_get_data(u8* pack);
void find_light(u8 *addr, u8 x, u8 y);
void send_parameter(u8 *addr, struct parameter *par);

#endif
