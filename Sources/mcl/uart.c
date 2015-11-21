#include "uart.h"

#define UART_OUTGOING_QUEUE_SIZE	128
#define UART_INCOMING_QUEUE_SIZE	128

static CircBuffer 	UART_OUTGOING_QUEUE;
static CircBuffer 	UART_INCOMING_QUEUE;
static uint8_t		UART_OUTGOING_QUEUE_Storage[UART_OUTGOING_QUEUE_SIZE];
static uint8_t		UART_INCOMING_QUEUE_Storage[UART_INCOMING_QUEUE_SIZE];

UART_RETVAL UartBufferInit			(CircBuffer *CB,uint16_t Size,uint8_t * Storage);
UART_RETVAL UartBufferEnqueue		(CircBuffer *CB,uint8_t byte);
UART_RETVAL UartBufferDequeue		(CircBuffer *CB,uint8_t *byte);
uint16_t 	UartBufferBytesInQueue	(CircBuffer *CB); 

/*******************************************************************************
* Function Name: UartInit
********************************************************************************
*	Summary:
*		Initialize the Uart peripheral
*
* 	Parameters:
*		baudrate	->	baudrate to be set
*
* 	Returns:
*  		UART_RETVAL
*
*******************************************************************************/
UART_RETVAL UartInit(UART_BAUDRATE baud)
{
    uint32_t sysclk;
	uint8_t i;
	uint32_t calculated_baud = 0;
	uint32_t baud_diff = 0;
	uint32_t osr_val = 0;
	uint32_t sbr_val, uart0clk;
	uint32_t baud_rate;
	uint32_t reg_temp = 0;
	uint32_t temp = 0;
	
    sysclk=CORE_CLOCK/2/1000;			//PERIPHERAL CLK
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	UartBufferInit(&UART_OUTGOING_QUEUE,UART_OUTGOING_QUEUE_SIZE,UART_OUTGOING_QUEUE_Storage);
	UartBufferInit(&UART_INCOMING_QUEUE,UART_INCOMING_QUEUE_SIZE,UART_INCOMING_QUEUE_Storage);
	
	PORTA_PCR1 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK;   
	PORTA_PCR2 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK;  
	
	//Select PLL/2 Clock
	SIM_SOPT2 &= ~(3<<26);
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); 
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
    // Disable UART0 before changing registers
    UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
    // Verify that a valid clock value has been passed to the function 
    if ((sysclk > 50000) || (sysclk < 32))
    {
        sysclk = 0;
        reg_temp = SIM_SOPT2;
        reg_temp &= ~SIM_SOPT2_UART0SRC_MASK;
        reg_temp |= SIM_SOPT2_UART0SRC(0);
        SIM_SOPT2 = reg_temp;
        return UART_BADCLOCK;
    }
    baud_rate = baud;
    uart0clk = sysclk * 1000;
    i = 4;
    sbr_val = (uint32_t)(uart0clk/(baud_rate * i));
    calculated_baud = (uart0clk / (i * sbr_val));
    if (calculated_baud > baud_rate)
    {
        baud_diff = calculated_baud - baud_rate;
    }
    else
    {
        baud_diff = baud_rate - calculated_baud;
    }
    osr_val = i;
    // Select the best OSR value
    for (i = 5; i <= 32; i++)
    {
        sbr_val = (uint32_t)(uart0clk/(baud_rate * i));
        calculated_baud = (uart0clk / (i * sbr_val));
        if (calculated_baud > baud_rate)
        {	
            temp = calculated_baud - baud_rate;
        }
        else
        {
        	temp = baud_rate - calculated_baud;
        }
        if (temp <= baud_diff)
        {
            baud_diff = temp;
            osr_val = i; 
        }
    }
    if (baud_diff < ((baud_rate / 100) * 3))
    {
        // If the OSR is between 4x and 8x then both
        // edge sampling MUST be turned on.  
        if ((osr_val >3) && (osr_val < 9))
            UART0_C5|= UART0_C5_BOTHEDGE_MASK;
        // Setup OSR value 
        reg_temp = UART0_C4;
        reg_temp &= ~UART0_C4_OSR_MASK;
        reg_temp |= UART0_C4_OSR(osr_val-1);
        // Write reg_temp to C4 register
        UART0_C4 = reg_temp;
        reg_temp = (reg_temp & UART0_C4_OSR_MASK) + 1;
        sbr_val = (uint32_t)((uart0clk)/(baud_rate * (reg_temp)));
         /* Save off the current value of the uartx_BDH except for the SBR field */
        reg_temp = UART0_BDH & ~(UART0_BDH_SBR(0x1F));
        UART0_BDH = reg_temp |  UART0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
        UART0_BDL = (uint8_t)(sbr_val & UART0_BDL_SBR_MASK);
        /* Enable receiver and transmitter */
        UART0_C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK );
    }
    else
	{
    	return UART_BADBAUD;
	}					
//    //Enable recieve interrupts
//	UART0_C2 |= UART_C2_RIE_MASK;
//	enable_irq(INT_UART0-16);
	return UART_OK;	
}

/*******************************************************************************
* Function Name: UartPutByte
********************************************************************************
*	Summary:
*		Write a byte into the TX buffer
*
* 	Parameters:
*		byte	->	byte to be write
*
* 	Returns:
*  		UART_RETVAL
*
*******************************************************************************/
UART_RETVAL UartPutByte(uint8_t byte)
{
	UART_RETVAL ret;
	
	ret=UartBufferEnqueue(&UART_OUTGOING_QUEUE,byte);	
	if(ret==UART_OK)
	{
		UART0_C2 |= UART_C2_TIE_MASK;
	}
	return ret;
}


/*******************************************************************************
* Function Name: UartGetByte
********************************************************************************
*	Summary:
*		Read a byte from the RX buffer
*
* 	Parameters:
*		byte	->	byte to be write
*
* 	Returns:
*  		UART_RETVAL
*
*******************************************************************************/
UART_RETVAL UartGetByte(uint8_t *byte)
{
	UART_RETVAL ret;
	
	if(UartBufferBytesInQueue(&UART_INCOMING_QUEUE)<1)
    {
        return UART_BUFFER_NOENDATA;
    } 
	ret=UartBufferDequeue(&UART_INCOMING_QUEUE,byte);	
	return ret;
}

