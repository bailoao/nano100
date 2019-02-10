
#include <stdio.h>
#include "Nano100Series.h"
#include "dis.h"

#define LED0	PE5
#define LED1	PB11
#define BEEP0	PD6
#define BEEP1	PD7
//define P3TX	PB1
//define P3RX	PB0


void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

		/* Enable  HIRC */
		CLK_EnableXtalRC(CLK_PWRCTL_HIRC_EN_Msk);
	
		/* Waiting for clock ready */
		CLK_WaitClockReady(CLK_CLKSTATUS_HIRC_STB_Msk);
	
		CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_HCLK_CLK_DIVIDER(1));
	
	
//    /* Enable external 12MHz HXT */
//    CLK_EnableXtalRC(CLK_PWRCTL_HXT_EN_Msk);
//    CLK_EnablePLL(CLK_PLLCTL_PLL_SRC_HIRC, 96000000);
//    /* Waiting for clock ready */
//    CLK_WaitClockReady(CLK_CLKSTATUS_HXT_STB_Msk | CLK_CLKSTATUS_PLL_STB_Msk);

//    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_PLL, CLK_HCLK_CLK_DIVIDER(3));
	
		/*  Set HCLK frequency 42MHz */
//		CLK_SetCoreClock(42000000);
	
    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HIRC, CLK_UART_CLK_DIVIDER(1));
    
		// SC clock is 4MHz
		CLK_SetModuleClock(SC0_MODULE, CLK_CLKSEL2_SC_S_HIRC, CLK_SC0_CLK_DIVIDER(3)); 
		
		/* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
		CLK_EnableModuleClock(SC0_MODULE);
	
		/* Update System Core Clock ,calculate SystemCoreClock.*/
    SystemCoreClockUpdate();
		
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PA multi-function pins for UART0 RXD and TXD */
//    SYS->PA_H_MFP &= ~( SYS_PA_H_MFP_PA15_MFP_Msk | SYS_PA_H_MFP_PA14_MFP_Msk);
//    SYS->PA_H_MFP |= (SYS_PA_H_MFP_PA15_MFP_UART0_TX|SYS_PA_H_MFP_PA14_MFP_UART0_RX);
    SYS->PB_L_MFP &= ~( SYS_PB_L_MFP_PB0_MFP_Msk | SYS_PB_L_MFP_PB1_MFP_Msk);
    SYS->PB_L_MFP |= (SYS_PB_L_MFP_PB1_MFP_UART0_TX|SYS_PB_L_MFP_PB0_MFP_UART0_RX);

		 //* Set PA.8 ~ PA.11 and //PB.4 for SC0 interface */
    SYS->PA_H_MFP &= ~(SYS_PA_H_MFP_PA8_MFP_Msk |
                       SYS_PA_H_MFP_PA9_MFP_Msk |
                       SYS_PA_H_MFP_PA10_MFP_Msk |
                       SYS_PA_H_MFP_PA11_MFP_Msk);
    //SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB4_MFP_Msk;

    SYS->PA_H_MFP |= (SYS_PA_H_MFP_PA8_MFP_SC0_CLK |
                      SYS_PA_H_MFP_PA9_MFP_SC0_DAT |
                      SYS_PA_H_MFP_PA10_MFP_SC0_PWR |
                      SYS_PA_H_MFP_PA11_MFP_SC0_RST);
		//SYS->PB_L_MFP |= SYS_PB_L_MFP_PB4_MFP_SC0_CD;

    /* Lock protected registers */
    SYS_LockReg();
		
		return;
}



void UART0_Init(void)
{
    /* Reset IP */
    SYS_ResetModule(UART0_RST);
    UART0->BAUD = 0x67;              /* Baud Rate:115200  OSC:12MHz */
    UART0->TLCTL = 0x03;             /* Character len is 8 bits */
	
		return;
}

void GPIO_Init(void){
	
	//led 0 and 1
	GPIO_SetMode(PE, BIT5, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PB, BIT11, GPIO_PMD_OUTPUT);
	
	GPIO_SetMode(PA, BIT7|BIT6|BIT5|BIT4|BIT3, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PC, BIT7, GPIO_PMD_OUTPUT);
	
	//GPIO_SetMode(PD, BIT7|BIT6, GPIO_PMD_OUTPUT);
	
	LED0 = 0;//PE5 = 0;//power on led
	LED1 = 1;//PB11
	
	//lcd control
	PA3 =1;PA4=1;PA5=1;PA6=1;PA7=1;PC7=1;
	//beep
	//BEEP0 = 0; BEEP1 = 0;

	return;
}


/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main (void)
{
    /* Init System, IP clock and multi-function I/O */
    SYS_Init(); //In the end of SYS_Init() will issue SYS_LockReg() to lock protected register. If user want to write protected register, please issue SYS_UnlockReg() to unlock protected register.

		GPIO_Init();
	
    /* Init UART for printf */
		UART0_Init();
	
		/*Init LCD ST7576*/
		LCD_Init();
		LCD_Fill(0x00);
	
//		SC_Open(SC0, SC_PIN_STATE_LOW, SC_PIN_STATE_HIGH);
//    NVIC_EnableIRQ(SC0_IRQn);

    SC0->IER = SC_IER_CD_IE_Msk;
	
		
		char cpu[16];
		sprintf(cpu,"CPU @ %dHz\n", SystemCoreClock);
		LCD_setPos(0,0);
		LCD_String(cpu,16);
		
		
    /* Waiting for interrupts */
    while (1){
			
			//LCD_Fill(0x00);
			PB11 = 1;
			LCD_Delay(30000);
			
			printf("\n\nCPU @ %dHz\n", SystemCoreClock);
			
			LCD_setPos(0,2);
			LCD_String("ABC_LCD0123456789",17);
			LCD_setPos(0,3);
			LCD_String("abcdefg hijklmn +-*%=",21);

			PB11 = 0;
			LCD_Delay(30000);
			
		};

}


