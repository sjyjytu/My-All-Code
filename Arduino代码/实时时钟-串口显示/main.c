/*******************˵��:**************************
��ʵʱʱ������ͨ�����ڷ���
--------------------------------------------------
����ս��Ƭ��������51/AVR��Сϵͳ�弰DS1302
ʵʱʱ��ģ���д
�Ա����̵�ַ: http://zsmcu.taobao.com/
QQ:284083167
�ֻ�:15016732495
**************************************************/
#include <reg52.h>
#define uchar unsigned char
#define uint  unsigned int
//DS1302���Ŷ���,�ɸ���ʵ����������޸Ķ˿ڶ���
sbit RST=P1^3;
sbit IO=P1^2;
sbit SCK=P1^1;
//DS1302��ַ����
#define ds1302_sec_add			0x80		//�����ݵ�ַ
#define ds1302_min_add			0x82		//�����ݵ�ַ
#define ds1302_hr_add			0x84		//ʱ���ݵ�ַ
#define ds1302_date_add			0x86		//�����ݵ�ַ
#define ds1302_month_add		0x88		//�����ݵ�ַ
#define ds1302_day_add			0x8a		//�������ݵ�ַ
#define ds1302_year_add			0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe
//��ʼʱ�䶨��
uchar time_buf[8] = {0x20,0x10,0x09,0x14,0x23,0x59,0x50,0x02};//��ʼʱ��
uchar readtime[14];//��ǰʱ��
uchar sec_buf=0;  //�뻺��
uchar sec_flag=0; //���־λ
//����:��ʱ1����
//��ڲ���:x
//���ڲ���:��
//˵��:����Ϊ12M
void Delay_xms(uint x)
{
  uint i,j;
  for(i=0;i<x;i++)
    for(j=0;j<112;j++);
}
//DS1302��ʼ������
void ds1302_init(void) 
{
	RST=0;			//RST���õ�
	SCK=0;			//SCK���õ�
}
//��DS1302д��һ�ֽ�����
void ds1302_write_byte(uchar addr, uchar d) 
{
	uchar i;
	RST=1;					//����DS1302����	
	//д��Ŀ���ַ��addr
	addr = addr & 0xFE;   //���λ���㣬�Ĵ���0λΪ0ʱд��Ϊ1ʱ��
	for (i = 0; i < 8; i ++) {
		if (addr & 0x01) {
			IO=1;
			}
		else {
			IO=0;
			}
		SCK=1;      //����ʱ��
		SCK=0;
		addr = addr >> 1;
		}	
	//д�����ݣ�d
	for (i = 0; i < 8; i ++) {
		if (d & 0x01) {
			IO=1;
			}
		else {
			IO=0;
			}
		SCK=1;    //����ʱ��
		SCK=0;
		d = d >> 1;
		}
	RST=0;		//ֹͣDS1302����
}

//��DS1302����һ�ֽ�����
uchar ds1302_read_byte(uchar addr) {

	uchar i,temp;	
	RST=1;					//����DS1302����
	//д��Ŀ���ַ��addr
	addr = addr | 0x01;    //���λ�øߣ��Ĵ���0λΪ0ʱд��Ϊ1ʱ��
	for (i = 0; i < 8; i ++) {
		if (addr & 0x01) {
			IO=1;
			}
		else {
			IO=0;
			}
		SCK=1;
		SCK=0;
		addr = addr >> 1;
		}	
	//������ݣ�temp
	for (i = 0; i < 8; i ++) {
		temp = temp >> 1;
		if (IO) {
			temp |= 0x80;
			}
		else {
			temp &= 0x7F;
			}
		SCK=1;
		SCK=0;
		}	
	RST=0;					//ֹͣDS1302����
	return temp;
}
//��DS302д��ʱ������
void ds1302_write_time(void) 
{
	ds1302_write_byte(ds1302_control_add,0x00);			//�ر�д���� 
	ds1302_write_byte(ds1302_sec_add,0x80);				//��ͣʱ�� 
	//ds1302_write_byte(ds1302_charger_add,0xa9);	    //������ 
	ds1302_write_byte(ds1302_year_add,time_buf[1]);		//�� 
	ds1302_write_byte(ds1302_month_add,time_buf[2]);	//�� 
	ds1302_write_byte(ds1302_date_add,time_buf[3]);		//�� 
	ds1302_write_byte(ds1302_hr_add,time_buf[4]);		//ʱ 
	ds1302_write_byte(ds1302_min_add,time_buf[5]);		//��
	ds1302_write_byte(ds1302_sec_add,time_buf[6]);		//��
	ds1302_write_byte(ds1302_day_add,time_buf[7]);		//�� 
	ds1302_write_byte(ds1302_control_add,0x80);			//��д����     
}
//��DS302����ʱ������
void ds1302_read_time(void)  
{
	time_buf[1]=ds1302_read_byte(ds1302_year_add);		//�� 
	time_buf[2]=ds1302_read_byte(ds1302_month_add);		//�� 
	time_buf[3]=ds1302_read_byte(ds1302_date_add);		//�� 
	time_buf[4]=ds1302_read_byte(ds1302_hr_add);		//ʱ 
	time_buf[5]=ds1302_read_byte(ds1302_min_add);		//�� 
	time_buf[6]=(ds1302_read_byte(ds1302_sec_add))&0x7f;//�룬������ĵ�7λ�����ⳬ��59
	time_buf[7]=ds1302_read_byte(ds1302_day_add);		//�� 	
}
//���ڳ�ʼ��(ϵͳ����Ϊ12MHz)
void Uart_init(uchar Baud_flag)
{
   TMOD = 0x20;       //T1 2
   PCON = 0x00;       //SMOD = 0
   SCON = 0x50;	      //����1 8
   switch(Baud_flag)
   {   	
    case 0x00:        //2400 11.0592M:0xf4
	  TH1=0xf3;
	  TL1=0xf3;
	break;
	case 0x01:        //4800 11.0592M:0xfa
	  TH1=0xf9;
	  TL1=0xf9;
	break;
    case 0x02:        //9600 11.0592M:0xfd
	  TH1=0xfd;
	  TL1=0xfd;
	break;
    case 0x03:        //19200 11.0592M:0xfe
      TH1=0xfd;
	  TL1=0xfd;
    break;
	default:          //Ĭ��Ϊ2400
	  TH1=0xf3;
	  TL1=0xf3;
	break;
   }
   TR1 = 1;	          //������ʱ��1								
   ES=1;              //�������ж�
   EA=1;              //�����ж�       
}
//���ڷ���
void Send_char(uchar ch)
{
 SBUF=ch; 
 while(!TI);      //�ȴ��������
 TI=0;           //���ж�
}
//������
void main(void)
{ 
 Delay_xms(50);//�ȴ�ϵͳ�ȶ�
 ds1302_init(); //DS1302��ʼ��
 Uart_init(0); //�����ʳ�ʼ��Ϊ2400
 Delay_xms(10);
 ds1302_write_time(); //д���ʼֵ
 while(1)
  { 
  ds1302_read_time();  //��ȡʱ�� 
  readtime[0]=(time_buf[0]>>4);   //�������ǧλ
  readtime[1]=(time_buf[0]&0x0F); //��������λ 
  readtime[2]=(time_buf[1]>>4);   //�������ʮλ
  readtime[3]=(time_buf[1]&0x0F); //��������λ 

  readtime[4]=(time_buf[2]>>4);   //�������ʮλ
  readtime[5]=(time_buf[2]&0x0F); //������¸�λ 

  readtime[6]=(time_buf[3]>>4);   //�������ʮλ
  readtime[7]=(time_buf[3]&0x0F); //������ո�λ 

  readtime[8]=(time_buf[4]>>4);   //�����Сʱʮλ
  readtime[9]=(time_buf[4]&0x0F); //�����Сʱ��λ 
  readtime[10]=(time_buf[5]>>4);   //���������ʮλ
  readtime[11]=(time_buf[5]&0x0F); //��������Ӹ�λ
  readtime[12]=(time_buf[6]>>4);   //���������ʮλ
  readtime[13]=(time_buf[6]&0x0F); //��������Ӹ�λ   
  if(readtime[13]!=sec_buf)       
   { 
    EA=0;
    sec_flag=0;    
	sec_buf=readtime[13];	   
    Send_char(readtime[0]+'0');//��
	Send_char(readtime[1]+'0');     
    Send_char(readtime[2]+'0');
	Send_char(readtime[3]+'0');    

	Send_char('-');

    Send_char(readtime[4]+'0');//��
	Send_char(readtime[5]+'0');

	Send_char('-');

    Send_char(readtime[6]+'0');//��
	Send_char(readtime[7]+'0');

	Send_char(' ');

	Send_char(readtime[8]+'0');//ʱ
	Send_char(readtime[9]+'0');

	Send_char(':');

	Send_char(readtime[10]+'0');//��
	Send_char(readtime[11]+'0');

	Send_char(':');

	Send_char(readtime[12]+'0');//��
	Send_char(readtime[13]+'0');

	SBUF='\n';
    while(!TI);      //�ȴ��������
    TI=0;           //���ж�
	EA=1;    	
   }
   Delay_xms(1000);
  }
}
