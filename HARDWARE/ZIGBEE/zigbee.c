#include "zigbee.h"

struct receive_data receive;

/*
�������ƣ�zigbee_send_data
������  �ṹ��send_data
*/
void zigbee_send_data(struct send_data* send)
{
    u8 pack[15] = {0xFE, 0x04}, g, flag = 0; //flag����ת��
    pack[1] = 0x04 + send->num;
		pack[2] = send->source;
		pack[3] = send->target;
    pack[4] = send->addr[1];
    pack[5] = send->addr[0];     //ʹ��С��ַ�˷���
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
    }                        //ƴ����Ҫ���͵İ�
    pack[6 + send->num + flag] = 0xFF;
    for(g = 0;g < 7 + send->num + flag;g++)
        printf("%c", pack[g]);  //���Ͱ�
}

/*
��������zigbee_get_data
���ܣ������ݴӽ��յ��İ�����ȡ����
���������ݰ�����
*/
void zigbee_get_data(u8* pack)
{
    int number, g, flag=0;
		u8 o_receive[99];        //�˴��Ժ���Ҫ�Ż� o_receiveֻ���������ת���Ľ����֮���ٷ���receive�ṹ����
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
������: find_light
����:   F4ͨ��ZigBee���͵�Ŀ��Ӱ岢��ָ���ĵ�
����:   addr Ŀ��ZigBee�ĵ�ַ
				x,y  Ҫ���ĵƵĺ�������
*/
void find_light(u8 *addr, u8 x, u8 y)
{
		struct send_data send;
	
		send.num = 2;
		send.source = 0x80;
		send.target = 0x80;        //������һ��������0x80�˿�
		send.addr[0] = addr[0];
		send.addr[1] = addr[1];
	
		send.data[0] = x;
		send.data[1] = y;
	
		zigbee_send_data(&send);
}

/*
������: send_parameter
����:  F4ͨ��ZigBee��F1����Ҫʹ�õ�����
				���ݸ�ʽΪ2λ��ַ 2λ����ID 1λ�ŵ�
����:  ��ַaddr
			 �ṹ��parameter
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
