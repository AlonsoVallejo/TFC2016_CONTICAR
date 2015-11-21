#ifndef UART_H_
#define UART_H_

#include "stdtypedef.h"
#include "derivative.h"
#include "CrystalClock.h"
typedef struct {
    
	uint16_t ReadPtr;
    uint16_t WritePtr;
    uint16_t QueueSize;
    uint8_t *QueueStorage;
    
} CircBuffer;

typedef enum uart_baudrate
{
	UART_BAUDRATE_4800		=	4800,
	UART_BAUDRATE_9600		=	9600,
	UART_BAUDRATE_19200		= 	19200,
	UART_BAUDRATE_38400		=	38400,	
	UART_BAUDRATE_57600		=	57600,
	UART_BAUDRATE_115200	=	115200
}UART_BAUDRATE;

typedef enum uart_retval
{
	UART_OK = 0,
	UART_BADBAUD,
	UART_BADCLOCK,
	UART_BUFFER_EMPTY,
	UART_BUFFER_FULL,
	UART_BUFFER_NOSPACE,		//not enough space for the requested operation
	UART_BUFFER_NOENDATA,
	UART_BUFFER_NOSTR
}UART_RETVAL;

UART_RETVAL	UartInit		(UART_BAUDRATE baud);
UART_RETVAL UartPutByte		(uint8_t byte);
UART_RETVAL UartGetByte		(uint8_t *byte);

		
#endif /* UART_H_ */
