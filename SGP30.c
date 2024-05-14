#include "allh.h"


//I2C��ʼ�ź�
void I2CStart(void)
{
  SDA = 1;                            //������ʼ�����������ź� 
  SCL = 1;
  _DELAY_US(50);                    //��ʼ��������ʱ�����4.7us,��ʱ 
  SDA = 0;                            //������ʼ�ź�
  _DELAY_US(50);                    //��ʼ��������ʱ�����4��s 
  SCL = 0;                            //ǯסI2C���ߣ�׼�����ͻ�������� 
  _DELAY_US(50);
}

//I2Cֹͣ�ź�
void I2CStop(void)
{
  SDA = 0;                        //���ͽ��������������ź� 
  SCL = 0;
  _DELAY_US(50);
  SCL = 1;                        //���ͽ���������ʱ���ź� 
  _DELAY_US(50);                //������������ʱ�����4��s 
  SDA = 1;                        //����I2C���߽����ź� 
  _DELAY_US(50);
}

//I2Cдһ���ֽ����ݣ�����ACK����NACK
u8 I2C_Write_Byte(u8 Write_Byte)  //Sendbyte
{
  u8 i;
  SCL=0;
  _DELAY_US(10);
  for(i=0; i<8; i++)            //Ҫ���͵����ݳ���Ϊ8λ 
  {
    if(Write_Byte&0x80)   //�жϷ���λ 
    {
      SDA = 1;
    }
    else
    {
      SDA = 0;
    }
    _DELAY_US(5);
    SCL=1;                //���SDA�ȶ�������SCL���������أ��ӻ���⵽��������ݲ���
    _DELAY_US(5);         //��֤ʱ�Ӹߵ�ƽ���ڴ���4��s 
    SCL=0;
    _DELAY_US(5);
    Write_Byte <<= 1;
  }
  _DELAY_US(1);
  SDA = 1;                      //8λ��������ͷ������ߣ�׼������Ӧ��λ-ZLG
  _DELAY_US(40);
  SCL = 1;                      //MCU��֪SHT2X���ݷ�����ϣ��ȴ��ӻ���Ӧ���ź�
  _DELAY_US(40);
  /*�������ж�I2C���߽���Ӧ��Ӧ���ź���ACK����NACK*/
  if(SDA==1)                                   //SDAΪ�ߣ��յ�NACK
  {
		_DELAY_US(40);
    SCL=0;
    return NACK;
  }
  else                                         //SDAΪ�ͣ��յ�ACK
  {
		_DELAY_US(40);
    SCL=0;
    return ACK;

  }
}

//I2C��һ���ֽ����ݣ���ڲ������ڿ���Ӧ��״̬��ACK����NACK
u8 I2C_Read_Byte(u8 AckValue)//receivebyte
{
  u8 i,RDByte=0;
  SCL=0;                                   //��ʱ����Ϊ�ͣ�׼����������λ 
  _DELAY_US(40);
  SDA = 1;                                 //�ͷ�����,��������Ϊ���뷽ʽ 
  for (i=0; i<8; i++)
  {
    SCL = 1;                          //SCL�ߵ�ƽ�ڼ䣬�ɼ�SDA�źţ�����Ϊ��Ч���� //��ʱ����Ϊ��ʹ��������������Ч 
    _DELAY_US(20);
    RDByte <<= 1;                  //��λ
    if(SDA==1)                           //������ȡ����
    {
      RDByte |= 0x01;
    }
    else
    {
      RDByte &= 0xfe;
    }
    _DELAY_US(10);
    SCL = 0;                             //�½��أ��ӻ�������һλֵ
    _DELAY_US(60);
  }
  /*������I2C���߷���Ӧ���ź�ACK����NACK*/
  SDA = AckValue;                      //Ӧ��״̬
  _DELAY_US(30);
  SCL = 1;
  _DELAY_US(50);                  //ʱ�ӵ͵�ƽ���ڴ���4��s 
  SCL = 0;                                  //��ʱ���ߣ�ǯסI2C�����Ա�������� 
  _DELAY_US(150);
  return RDByte;
}

//��ʼ��IIC�ӿ�
void SGP30_Init(void)
{
  SGP30_Write(0x20,0x03);
//	SGP30_ad_write(0x20,0x61);
//	SGP30_ad_write(0x01,0x00);
}

void SGP30_Write(u8 a, u8 b)
{
  I2CStart();
  I2C_Write_Byte(SGP30_write); //����������ַ+дָ��
  I2C_Write_Byte(a);		//���Ϳ����ֽ�
  I2C_Write_Byte(b);
  I2CStop();
  _DELAY_MS(100);
}

unsigned long SGP30_Read(void)
{
  unsigned long dat;
  int crc;
  I2CStart();
  I2C_Write_Byte(SGP30_read); //����������ַ+��ָ��
  dat = I2C_Read_Byte(ACK);
  dat <<= 8;
  dat += I2C_Read_Byte(ACK);
  crc = I2C_Read_Byte(ACK); //check���ݣ���ȥ
  crc = crc;             //�������������棬�����п���
  dat <<= 8;
  dat += I2C_Read_Byte(ACK);
  dat <<= 8;
  dat += I2C_Read_Byte(NACK);
  I2CStop();
  return(dat);
}
