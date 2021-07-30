//USB boot loader support definitions for Soprano

#ifndef __USB_BOOT_FUNCS_H__
#define __USB_BOOT_FUNCS_H__

#include "c1_bootrom.h"
#include "USB_Regs.h"
#include "USB_Structs.h"


//Truth and falsehood
#define true	1
#define false	0


//Max packet size for endpoint 0
#define EP0_MAX_PACKET_SIZE 64


//USB endpoint state enum
typedef enum
{
	USB_STATE_IDLE,		//Waiting for a request from the host controller
	USB_STATE_TX,		//Sending data to the host due to an IN request
	USB_STATE_RX,		//Receiving data from the host due to an OUT request
	USB_STATE_STALL,	//Waiting for the host to acknowledge a stall condition
	USB_STATE_STATUS	//Waiting for the host to acknowledge completion of an IN or OUT request
} eEndpointState;


//DATAEND selector enum
typedef enum
{
	USB_MORE_DATA,		//Do not set the DATAEND bit
	USB_END_DATA		//Set the DATAEND bit
} eDataEnd;

//Function prototypes
interrupt void UsbIntHandler();
void AckUsbInterrupt();
static void UsbEndpoint0StateMachine();
static eEndpointState HandleControlRequest(const sUsbRequestPacket *req);
static void CopyStringDescriptor(const sUsbStringDescriptor *strDesc, Uint16 *buffer);
void ResetUsbDriver();

void TxDataEp0(const Uint16 *data, Uint16 length8, eDataEnd dataEnd);
Uint16 RxDataEp0(Uint16 *data);
static void StallEp0();
void AckEp0(eDataEnd dataEnd);

Uint16 RxDataEp1(Uint16 *data);
void AckEp1();


#endif //__USB_BOOT_FUNCS_H__
