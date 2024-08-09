#include<lpc17xx.h>
#define s LPC_SC
#define u LPC_UART0
void pll()
{
s->SCS=(1<<5);
while(s->SCS & (1<<6)==0);
s->CLKSRCSEL=(1<<0);
s->PLL0CON=(1<<0);
s->PLL0CFG=14;
s->PLL0FEED=0xAA;
s->PLL0FEED=0x55;
s->CCLKCFG=5;
while(s->PLL0STAT&(1<<26)==0);
s->PLL0CON|=(1<<1);
s->PLL0FEED=0xAA;
s->PLL0FEED=0x55;
}
void basic_inituart0()
{
//1.power on the UART0--PCONP--3rd bit(1)
//2.Frequency
//3.pins TXD0,RXD0
LPC_PINCON->PINSEL0=(1<<4)|(1<<6);
u->LCR=(1<<0)|(1<<1)|(1<<7);---WORD LENGTH,DLAB=1
u->DLL=98;
u->DLM=0;
u->LCR&=~(1<<7);
}
int main()
{
pll();
basic_inituart0();


//transmit the data
while((u->LSR & (1<<5))==0);//check if THR is empty
u->THR='a';//load the data to be transmitted through UART
while(1);
}
