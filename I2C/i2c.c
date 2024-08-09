#include<lpc17xx.h>
void PLL()
{
LPC_SC->SCS=(1<<5);
while(((LPC_SC->SCS)&(1<<6))!=(1<<6));
LPC_SC->CLKSRCSEL=(1<<0);
LPC_SC->PLL0CON=(1<<0);
LPC_SC->PLL0CFG=(14<<0)|(0<<16);
LPC_SC->PLL0FEED=0XAA ;
LPC_SC->PLL0FEED=0X55 ;
while(((LPC_SC->PLL0STAT)&(1<<26))!=(1<<26));
LPC_SC->CCLKCFG=(5<<0);
LPC_SC->PLL0CON|=(1<<1);
LPC_SC->PLL0FEED=0XAA ;
LPC_SC->PLL0FEED=0X55 ;
}
void i2cinitial()
{
LPC_SC->PCONP|=(1<<26);//it is optaional
LPC_PINCON->PINSEL0 |=(1<<21)|(1<<23);//selecting mode for the pin sda and scl	
LPC_PINCON->PINMODE_OD0=(1<<10)|(1<<11);//
LPC_PINCON->PINMODE0=(1<<21)|(1<<23);//neither pullup or pulldown 
LPC_SC->PCLKSEL1=(1<<21);//clk/2--->60mhz/2--30mhz 
LPC_I2C2->I2SCLL=150;
LPC_I2C2->I2SCLH=150;
}
int main()
{
PLL();//called the pll programme
i2cinitial();//called the initialization
LPC_I2C2->I2CONSET=(1<<6)|(1<<5);//
while((LPC_I2C2->I2STAT)!=(0X08));
LPC_I2C2->I2CONCLR=(1<<3)|(1<<5);
LPC_I2C2->I2DAT=0XF0;
while((LPC_I2C2->I2STAT)!=(0X18));
LPC_I2C2->I2CONCLR=(1<<3);
LPC_I2C2->I2DAT='A';
while((LPC_I2C2->I2STAT)!=(0X28));
LPC_I2C2->I2CONCLR=(1<<3);
LPC_I2C2->I2CONSET=(1<<4);
LPC_I2C2->I2CONCLR=(0XFF);
while(1);
}
