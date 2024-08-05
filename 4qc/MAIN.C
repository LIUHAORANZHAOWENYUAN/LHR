#include <STC8G.H>
#include "intrins.H"
unsigned char P90;
unsigned char AA;
unsigned char BB;
unsigned char QD;
sbit A1=P1^0;//YH	  
sbit A2=P1^1;//YH
sbit A3=P1^6;//YQ
sbit A4=P1^7;//YQ
sbit A5=P3^7;//ZQ
sbit A6=P3^6;//ZQ
sbit A7=P3^5;//ZH
sbit A8=P3^4;//ZH
sbit A01=P3^3;//ZB
sbit A00=P3^2;//YB

void QJ() 
{
A1=0;A2=1;
A3=1;A4=0;
A5=1;A6=0;
A7=0;A8=1;
}

void Z1()
{
A1=0;A2=1;
A3=1;A4=0;
A5=0;A6=1;
A7=1;A8=0;
}

void Y1()
{
A1=1;A2=0;
A3=0;A4=1;
A5=1;A6=0;
A7=0;A8=1;
}

void TZ()
{
A1=0;A2=0;
A3=0;A4=0;
A5=0;A6=0;
A7=0;A8=0;
}

void Delay1000ms()		//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 61;
	j = 225;
	k = 62;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay50ms()		//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 4;
	j = 12;
	k = 50;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Timer0_Init(void)		//20毫秒@12.000MHz
{
	EA=1;
	ET0=1;
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xE0;				//设置定时初始值
	TH0 = 0xB1;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

void INT_INIT()
{
EA = 1; //总中断开关
EX0 = 1; //允许响应外部中断 0
EX1 = 1; //允许响应外部中断 1
IE0 = 0; //设外部中断 0 为低电平触发
IE1 = 0; //设外部中断 1 为低电平触发
}

void main()
{
P1M0=0X00;P1M1=0X00; //定义I/O口状态
P3M0=0X00;P3M1=0X00; //定义I/O口状态
INT_INIT();
Timer0_Init();
Z1();
P90=0;
while(1)
{	
	QJ();
	AA=0;				  
	for(BB=0;BB<11;BB++)
	{
	Delay1000ms();
	AA++;
	}
}
}
	void QQ1()interrupt 2
	{	
	if(A01==1)
	{
	Z1();
	IE1=1;
	}
	}
	void QQ0()interrupt 0
	{
	if(A00==1)
	{
	Y1();
	IE0=1;
	}
	}		
void AWM()interrupt 1
{
	TL0=0xC0;				//设置定时初始值
	TH0=0xE0;				//设置定时初始值
	P90++;
	if(P90<AA) QJ();
	else TZ(); 
	if(P90=11)P90=0;
}


