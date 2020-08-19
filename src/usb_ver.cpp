/************************************************************************
*
*                               Meadowlark Optics
*                               Copyright (2006-2013)
*
* File name: usb_ver.cpp
*
* Description: This file contains sample source code that will initialize
*              a USB connection to a Meadowlark Optics D3050, send a
*              ver:? command and read the status response.
*
************************************************************************/
#include <iostream.h>
#include <windows.h>
#include "usbdrvd.h"

void main()
{
#define  flagsandattrs  0x40000000

BYTE ver_cmd [] = {'v', 'e', 'r', ':', '?', '\n'};
BYTE status [64];

HANDLE dev1, pipe0, pipe1;

UINT devcnt, i;
UINT USB_PID;

GUID  theGUID;

theGUID.Data1 = 0xa22b5b8b;
theGUID.Data2 = 0xc670;
theGUID.Data3 = 0x4198;
theGUID.Data4 [0] = 0x93;
theGUID.Data4 [1] = 0x85;
theGUID.Data4 [2] = 0xaa;
theGUID.Data4 [3] = 0xba;
theGUID.Data4 [4] = 0x9d;
theGUID.Data4 [5] = 0xfc;
theGUID.Data4 [6] = 0x7d;
theGUID.Data4 [7] = 0x2b;

USB_PID = 0x139C

devcnt = USBDRVD_GetDevCount (USB_PID);

if (devcnt == 0)
   {
	cout<<"No Meadowlark Optics USB Devices Present."<<endl;
   }
else
	{
	/* open device and pipes */
	dev1 = USBDRVD_OpenDevice (1, flagsandattrs, USB_PID);
	pipe0 = USBDRVD_PipeOpen (1, 0, flagsandattrs, &theGUID);
	pipe1 = USBDRVD_PipeOpen (1, 1, flagsandattrs, &theGUID);

	/* send ver:? command */
	USBDRVD_BulkWrite (dev1, 1, ver_cmd, sizeof (ver_cmd));

   /* read status response */
	USBDRVD_BulkRead (dev1, 0, status, sizeof (status));

   cout<<endl;

   /* output status until a <CR> is found */
   for (i = 0; status[i] != 0xd; i++)
      {
      cout<<status[i];
      }

   cout<<endl;

	/* close device and pipes */
	USBDRVD_PipeClose (pipe0);
	USBDRVD_PipeClose (pipe1);
	USBDRVD_CloseDevice (dev1);
	}
}
