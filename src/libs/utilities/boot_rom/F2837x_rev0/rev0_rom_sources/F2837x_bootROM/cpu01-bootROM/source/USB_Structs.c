//USB descriptor implementations for the Soprano boot loader

#include "USB_Structs.h"

//Device descriptor for DFU
const sUsbDeviceDescriptor dfuDeviceDescriptor =
{
	USB_DTYPE_DEVICE<<8 | 2*sizeof(sUsbDeviceDescriptor),
	0x0110,
	0x00<<8 | 0xFF,
	64<<8 | 0x00,
	0x1CBE,
	0x00FF,
	0x0001,
	2<<8 | 1,
	1<<8 | 3
};

//Configuration, interface, and functional descriptors for DFU.
//The wTotalLength must be set in software based on the total
//set of descriptors sent to the host.
const sUsbConfigDescriptor dfuConfigDescriptor =
{
	USB_DTYPE_CONFIG<<8 | (2*sizeof(sUsbConfigDescriptor) - 1),
	0,
	1<<8 | 1,
	0xC0<<8 | 0,
	150
};
const sUsbInterfaceDescriptor dfuInterfaceDescriptor =
{
	USB_DTYPE_INTERFACE<<8 | (2*sizeof(sUsbInterfaceDescriptor) - 1),
	0<<8 | 0,
	0xFE<<8 | 0,
	0x02<<8 | 0x01,
	4
};
const sPrepadDfuFunctionalDescriptor dfuFunctionalDescriptor =
{
	(2*sizeof(sPrepadDfuFunctionalDescriptor) - 1)<<8 | 0,
	0x05<<8 | USB_DTYPE_DFU_FUNC,
	0xFFFF,
	1024,
	0x0110
};

//Combine the configuration, interface, and functional descriptors into a
//single block, stripping out the 16-bit alignment padding in the process.
void CombineUsbDescriptors(Uint16 *buffer)
{
	Uint16 b, d, byteLength;

	b = d = 0;
	byteLength = dfuConfigDescriptor.bDescriptorType_bLength & 0xFF;
	while (byteLength--)
	{
		__byte((int *)buffer, b) = __byte((int *)&dfuConfigDescriptor, d);
		b++; d++;
	}

	d = 0;
	byteLength = dfuInterfaceDescriptor.bDescriptorType_bLength & 0xFF;
	while (byteLength--)
	{
		__byte((int *)buffer, b) = __byte((int *)&dfuInterfaceDescriptor, d);
		b++; d++;
	}

	//Skip the first byte of padding in the functional descriptor
	d = 1;
	byteLength = dfuFunctionalDescriptor.bLength_padding >> 8;
	while (byteLength--)
	{
		__byte((int *)buffer, b) = __byte((int *)&dfuFunctionalDescriptor, d);
		b++; d++;
	}

	//Set wTotalLength
	buffer[1] = (dfuConfigDescriptor.bDescriptorType_bLength & 0xFF) +
			    (dfuInterfaceDescriptor.bDescriptorType_bLength & 0xFF) +
			    (dfuFunctionalDescriptor.bLength_padding >> 8);
}



//String descriptor strings. These are variable-length and thus cannot be
//part of a structure.
const char langID = 0x0409;	//US English
const char manufacturerString[] = "Texas Instruments";
const char productString[] = "TMS320F28x7x USB DFU Boot Loader";
const char serialString[] = "1";
const char dfuString[] = "SUPER-BOOT";

//String descriptor structures. Each consists of a header followed by a
//pointer to the actual string. The full descriptor must be constructed
//at run-time by copying the header and the string into a temporary buffer.
const sUsbStringDescriptor langDescriptor =
{
	USB_DTYPE_STRING<<8 | (2 + 2*sizeof(langID)),
	&langID
};
const sUsbStringDescriptor mfgDescriptor =
{
	USB_DTYPE_STRING<<8 | (2 + 2*sizeof(manufacturerString)),
	manufacturerString
};
const sUsbStringDescriptor prodDescriptor =
{
	USB_DTYPE_STRING<<8 | (2 + 2*sizeof(productString)),
	productString
};
const sUsbStringDescriptor serialDescriptor =
{
	USB_DTYPE_STRING<<8 | (2 + 2*sizeof(serialString)),
	serialString
};
const sUsbStringDescriptor dfuStringDescriptor =
{
	USB_DTYPE_STRING<<8 | (2 + 2*sizeof(dfuString)),
	dfuString
};

//String descriptor array. Used to provide indexing for descriptor requests.
//This needs to be a constant array of constant pointers to keep it out of
//the .cinit section.
const sUsbStringDescriptor * const stringDescriptors[] =
{
	&langDescriptor,
	&mfgDescriptor,
	&prodDescriptor,
	&serialDescriptor,
	&dfuStringDescriptor
};

