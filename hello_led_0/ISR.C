
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "BasicTyp.h"
#include "common.h"
#include "USB.h"
#include "HAL4D13.h"
#include "isr.h"
#include "iso.h"
#include "mainloop.h"
#include "usb_irq.h"


// ************************************************************************
//  Public static data
// ************************************************************************

extern D13FLAGS bD13flags;
extern USBCHECK_DEVICE_STATES bUSBCheck_Device_State;
extern CONTROL_XFER ControlData;

//extern unsigned short ioSize, ioCount;


// ************************************************************************
//  ISR Subroutine
// ************************************************************************
void usb_isr(void)
{
	disable();

	Hal4D13_LockDevice(0);
	fn_usb_isr();

	enable();
}

void fn_usb_isr(void)
{
	ULONG   i_st;

	bD13flags.bits.At_IRQL1 = 1;

	i_st = Hal4D13_ReadInterruptRegister();

	if(i_st != 0) 
	{
		if(i_st & D13REG_INTSRC_BUSRESET)
			Isr_BusReset();
		else if(i_st & D13REG_INTSRC_SUSPEND)
			Isr_SuspendChange();
		else if(i_st & D13REG_INTSRC_EOT)
			Isr_DmaEot();
		else if(i_st & (D13REG_INTSRC_SOF|D13REG_INTSRC_PSEUDO_SOF))
			Isr_SOF();
		else if(i_st & D13REG_INTSRC_SHORT_PACKET)
			Isr_SHORT_PACKET();
		else if(i_st & D13REG_INTSRC_RESUME)
		{
			printf("RESUME\n");
			Hal4D13_LockDevice(0);
		}

		else 
		{
			if(i_st & D13REG_INTSRC_EP0OUT)  
				Isr_Ep00RxDone();
			if(i_st & D13REG_INTSRC_EP0IN)
				Isr_Ep00TxDone();
			if(i_st & D13REG_INTSRC_EP03)
				Isr_Ep03Done();
			if(i_st & D13REG_INTSRC_EP04)
				Isr_Ep04Done();
			if(i_st & D13REG_INTSRC_EP05)
				Isr_Ep05Done();
			if(i_st & D13REG_INTSRC_EP06)
				Isr_Ep06Done();
		}
	}

	bD13flags.bits.At_IRQL1 = 0;
}

void Isr_BusReset(void)
{
	printf("BUS RESET\n");
	bD13flags.bits.DCP_state = 0x00;
	bD13flags.bits.dma_disable=0x00;

	bUSBCheck_Device_State.State_bits.DEVICE_DEFAULT_STATE = 1;
	bUSBCheck_Device_State.State_bits.DEVICE_ADDRESS_STATE = 0;
	bUSBCheck_Device_State.State_bits.DEVICE_CONFIGURATION_STATE = 0;
	config_endpoint();
}

void Isr_SuspendChange(void)
{
	bD13flags.bits.suspend=1;
}

void Isr_SHORT_PACKET(void)
{
	printf("SHORT PACKET INTERRUPT\n");
}

void Isr_DmaEot(void)
{
	bD13flags.bits.dma_disable =0;

	if(bD13flags.bits.dma_state == DMA_PENDING)
		bD13flags.bits.setup_dma = 1;
	else
		bD13flags.bits.dma_state = DMA_IDLE;
	printf("EOT reached!!!\n");
	if(bD13flags.bits.verbose==1)
		printf("dma_counter = %x\n", Hal4D13_GetDMACounter());
	printf("\n");		
}


void Isr_SOF(void)
{

}

void Isr_Ep00RxDone(void)
{
	UCHAR       ep_last, i;

	ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0_CONTROL_OUT); /* Clear interrupt flag */

	if (ep_last & D13REG_EPSTS_SETUP)
	{
		if(bD13flags.bits.DCP_state == USBFSM4DCP_REQUESTPROC)
		{
			ControlData.Abort = 1;
			bD13flags.bits.DCP_state = USBFSM4DCP_SETUPPROC;
		}
		else
			bD13flags.bits.DCP_state = USBFSM4DCP_SETUPPROC;
	}
	else /* not a setup packet, just a Data Out Packet */
	{
		switch (bD13flags.bits.DCP_state)
		{
		case USBFSM4DCP_DATAOUT:

			i =	Hal4D13_ReadEndpoint(EPINDEX4EP0_CONTROL_OUT, ControlData.dataBuffer + ControlData.wCount,
				EP0_PACKET_SIZE);

			ControlData.wCount += i;
			if( i != EP0_PACKET_SIZE || ControlData.wCount >= ControlData.wLength)
			{
				bD13flags.bits.DCP_state = USBFSM4DCP_REQUESTPROC;

			}
			break;
		case USBFSM4DCP_HANDSHAKE:

			bD13flags.bits.DCP_state = USBFSM4DCP_IDLE;
			break;

		case USBFSM4DCP_STALL:		break;

		case USBFSM4DCP_SETUPPROC:	break;

		case USBFSM4DCP_REQUESTPROC:break;

		case USBFSM4DCP_DATAIN:		break;

		default:
			printf("Fatal Error: Isr_Ep0RxDone ReadLastTranactionStatus=%x\n",ep_last);
			bD13flags.bits.DCP_state = USBFSM4DCP_STALL;
			Hal4D13_StallEP0InControlWrite();
			break;
		}
	}
	return ;
}

void Isr_Ep00TxDone(void)
{
	short i = ControlData.wLength - ControlData.wCount;
	UCHAR ep_last;


	Hal4D13_ReadInterruptRegister();
	ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0_CONTROL_IN); /* Clear interrupt flag */

	switch (bD13flags.bits.DCP_state)
	{
	case USBFSM4DCP_HANDSHAKE:
		break;
	case USBFSM4DCP_DATAIN:
		if( i >= EP0_PACKET_SIZE)
		{
			Hal4D13_WriteEndpoint(EPINDEX4EP0_CONTROL_IN,ControlData.Addr.pData + ControlData.wCount, EP0_PACKET_SIZE);
			ControlData.wCount += EP0_PACKET_SIZE;

			// State remains at USBFSM4DCP_DATAIN

		}
		else if( i != 0)
		{
			Hal4D13_WriteEndpoint(1, ControlData.Addr.pData + ControlData.wCount, i);
			ControlData.wCount += i;

			bD13flags.bits.DCP_state = USBFSM4DCP_HANDSHAKE;
			LowerIRQL();

		}
		else if (i == 0)
		{
			Hal4D13_SingleTransmitEP0(0, 0);
			bD13flags.bits.DCP_state = USBFSM4DCP_HANDSHAKE;
		}
		break;
	case USBFSM4DCP_REQUESTPROC: break;
	case USBFSM4DCP_IDLE:		break;
	case USBFSM4DCP_SETUPPROC:	break;
	case USBFSM4DCP_STALL:		break;
	case USBFSM4DCP_DATAOUT:	break;
	default:
		printf("Fatal Error: Isr_Ep0TxDone Unexpected FSMState=%x\n",bD13flags.bits.DCP_state);
		bD13flags.bits.DCP_state = USBFSM4DCP_STALL;
//		printf("bD13flags.bits.DCP_state = x%hx\n", bD13flags.bits.DCP_state);
		Hal4D13_StallEP0InControlRead();
		break;
	}
}


void Isr_Ep01Done(void)
{
/*	 
	UCHAR  c;
	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP01); 
*/
}


void Isr_Ep02Done(void)
{
/*	 
	HAR  c;
	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP02); 
*/

}


void Isr_Ep03Done(void)
{
  UCHAR       ep_last;
  ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP03); /* Clear interrupt flag*/
/*
	UCHAR	   ep_last, DoubleBuff=1;
	UCHAR len;
	USHORT far *fp;
	USHORT seg, off;

	ep_last = (UCHAR)Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP03); // Clear interrupt flag

	// Check for Double Buffer Condition
	if((ep_last & 0x60) == 0x60)
			DoubleBuff = 2;
	else
			DoubleBuff = 1;

	if (!(ep_last & (D13REG_EPSTS_DBF0|D13REG_EPSTS_DBF1)) || (ep_last & 0x80))
	{
		printf("ep_last = %x, \n", ep_last);
		return ;
	}
	else //Data Out Packet
	{
		while(DoubleBuff)
		{
			if (ioCount <= ioSize)
			{
				//  Initialise the pointer
				seg = (ioBuffer + ioCount)>>4;
				off = (ioBuffer + ioCount)&0xf;
				fp = MK_FP(seg, off);

				//  Determine the Transfer length
				if((ioSize-ioCount) >64)
					len = 64;
				else
				{
					len = ioSize - ioCount;
					if(bD13flags.bits.dma_state == DMA_PENDING)
						bD13flags.bits.setup_dma = 1;
					else
						bD13flags.bits.dma_state = DMA_IDLE;
				}
				//  Read in Data from Endpoint, and update the ioCount
				ioCount += Hal4D13_ReadBulkEndpoint(EPINDEX4EP03, fp, len);
			}
			else
			{
				Hal4D13_ClearBuffer(EPINDEX4EP03);
				if(bD13flags.bits.dma_state == DMA_PENDING)
					bD13flags.bits.setup_dma = 1;
				else
					bD13flags.bits.dma_state = DMA_IDLE;
			}
			DoubleBuff --;

			if(DoubleBuff ==  1)
				ep_last = (UCHAR)Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP03); // Clear interrupt flag
		}
	}
*/
}


void Isr_Ep04Done(void)
{
  UCHAR       ep_last;
  ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP04); /* Clear interrupt flag*/
/*
	USHORT len;
	USHORT far *fp;
	USHORT seg, off;
	UCHAR		DoubleBuff=0;
	UCHAR       ep_last;

	ep_last = (UCHAR)Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP04); // Clear interrupt flag

	if((ep_last & (D13REG_EPSTS_DBF0|D13REG_EPSTS_DBF1)) == 0x00)
		DoubleBuff = 2;
	else
		DoubleBuff = 1;

	if((ep_last & (D13REG_EPSTS_DBF0|D13REG_EPSTS_DBF1)) == 0x60)
	{
		//  BUFFER IS NOT EMPTY
		printf("ep_last = %x, \n", ep_last);
		return ;
	}
	else //  Data IN Packet
	{
		while(DoubleBuff)
		{
			// Initialise the pointer
			seg = (ioBuffer + ioCount)>>4;
			off = (ioBuffer + ioCount)&0xf;
			fp = MK_FP(seg, off);

			// Determine the Transfer length
			if(ioSize >= ioCount)
				len = ioSize - ioCount;

			if(len > 64)
			{
				ioCount += Hal4D13_WriteBulkEndpoint(EPINDEX4EP04, fp, 64);
				bD13flags.bits.dma_state = DMA_IDLE;
			}
			else if(len >= 1)
			{
					ioCount += Hal4D13_WriteBulkEndpoint(EPINDEX4EP04, fp, len);
					bD13flags.bits.dma_state = DMA_IN_DONE;
			}

			DoubleBuff--;
			if(DoubleBuff == 1)
				ep_last = (UCHAR)Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP04); // Clear interrupt flag
		}
	}
*/
}

void Isr_Ep05Done(void)
{
	UCHAR   ep_last, DoubleBuff=1;
	USHORT	ISO_Buffer[512], len;

	ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP05); // Clear interrupt flag

	if((ep_last & (D13REG_EPSTS_DBF0|D13REG_EPSTS_DBF1)) == 0x00)
		DoubleBuff = 2;
	else
		DoubleBuff = 1;

	if (ep_last | D13REG_EPSTS_DBF0|D13REG_EPSTS_DBF1)
	{
		return ;
	}

	else //Data Out Packet
	{

		if((ep_last & 0x60) != 0x00)
		{

		   if(DoubleBuff == 2)
		   {
				while(DoubleBuff)
				{
					len = Hal4D13_ReadISOEndpoint(EPINDEX4EP05, ISO_Buffer, 512);
					Hal4D13_WriteISOEndpoint(EPINDEX4EP06, ISO_Buffer, len);
					DoubleBuff--;
					ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP05); // Clear interrupt flag
				}
		   }
		   else
		   {
				len = Hal4D13_ReadISOEndpoint(EPINDEX4EP05, ISO_Buffer, 512);
				Hal4D13_WriteISOEndpoint(EPINDEX4EP06, ISO_Buffer, len);

		   }

		}
	}
}

void Isr_Ep06Done(void)
{
	UCHAR       ep_last;
	ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP06); /* Clear interrupt flag*/
}


void Isr_Ep07Done(void)
{

//	UCHAR  c;
//	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP07); /* Clear interrupt flag */

}
void Isr_Ep08Done(void)
{
//	UCHAR  c;
//	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP08); /* Clear interrupt flag */
}
void Isr_Ep09Done(void)
{
//	UCHAR  c;
//	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP09); /* Clear interrupt flag */
}
void Isr_Ep0ADone(void)
{
//	UCHAR  c;
//	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0A); /* Clear interrupt flag */
}
void Isr_Ep0BDone(void)
{
//	UCHAR  c;
//	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0B); /* Clear interrupt flag */
}
void Isr_Ep0CDone(void)
{
//	UCHAR  c;
//	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0C); /* Clear interrupt flag */
}
void Isr_Ep0DDone(void)
{
//	UCHAR  c;
//	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0D); /* Clear interrupt flag */
}
void Isr_Ep0EDone(void)
{
//	UCHAR  c;
//	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0E); /* Clear interrupt flag */
}

//*********************************************************************
// supporting Functions
//*********************************************************************



