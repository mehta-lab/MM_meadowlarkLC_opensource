//
// $History: usbdrvd.h $
//
//*****************  Version 5  *****************
//User: Andrew       Date: 9/05/02    Time: 1:55p
//Updated in $/USB_DRV/dll
//GUID now passed as a pointer.
//bRun added to download.
//
//*****************  Version 4  *****************
//User: Andrew       Date: 8/07/02    Time: 1:30p
//Updated in $/USB_DRV/dll
//Fixes for VB compatible DLL
//
//*****************  Version 3  *****************
//User: Andrew       Date: 6/05/02    Time: 12:40p
//Updated in $/USB_DRV/dll
//Added Path functions anc CyclePort.
//Fixed problem with RAM download.
//
//*****************  Version 2  *****************
//User: Andrew       Date: 3/29/02    Time: 9:48a
//Updated in $/USB_DRV/DLL
//New support for downloading .hex file.
//
//*****************  Version 1  *****************
//User: Andrew       Date: 8/01/01    Time: 1:23p
//Created in $/USB_DRV/DLL
//

#ifndef _USBDRVD_H_
#define _USBDRVD_H_


#ifdef USBDRVD_EXPORTS
#define USBDRVD_API __declspec(dllexport)
#else
#define USBDRVD_API __declspec(dllimport)
#endif

////////////////////////////////////////////////////////////////////////////////
/////////////////  Device Functions  ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C"{
#endif

//Returns number of USBDRVD devices attached
USBDRVD_API UINT USBDRVD_GetDevCount(const GUID *pUSB_GUID);

USBDRVD_API UINT USBDRVD_GetDevicePath(UINT DevNum, const GUID * pUSB_GUID, char *Dest, UINT Length);

USBDRVD_API HANDLE USBDRVD_OpenDevice(UINT DevNum, DWORD dwFlagsAndAttributes, const GUID * pUSB_GUID);

USBDRVD_API HANDLE USBDRVD_OpenDevicePath(char *Path, DWORD dwFlagsAndAttributes);

USBDRVD_API void USBDRVD_CloseDevice(HANDLE hDevice);

USBDRVD_API BOOL USBDRVD_ResetParentPort(HANDLE hDevice);

USBDRVD_API BOOL USBDRVD_GetParentPortStatus(HANDLE hDevice, ULONG *pStatus);

USBDRVD_API BOOL USBDRVD_CyclePort(HANDLE hDevice);

USBDRVD_API UINT USBDRVD_GetPipeCount(HANDLE hDevice);

typedef enum _USBDRV_PIPE_TYPE {
    PipeTypeControl,
    PipeTypeIsochronous,
    PipeTypeBulk,
    PipeTypeInterrupt
} USBDRV_PIPE_TYPE;

typedef struct _USBDRV_PIPE_INFO {
    USHORT MaximumPacketSize;  // Maximum packet size for this pipe
    UCHAR EndpointAddress;     // 8 bit USB endpoint address (includes direction)
                               // taken from endpoint descriptor
    UCHAR Interval;            // Polling interval in ms if interrupt pipe 
    
    USBDRV_PIPE_TYPE PipeType;// PipeType identifies type of transfer valid for this pipe
    
    ULONG MaximumTransferSize; // Maximum size for a single request
                               // in bytes.
} USBDRV_PIPE_INFO, *PUSBDRV_PIPE_INFO;

USBDRVD_API UINT USBDRVD_GetPipeInfo(HANDLE hDevice, ULONG PipeNum, PUSBDRV_PIPE_INFO pInfo);

USBDRVD_API BOOL USBDRVD_AbortPipe(HANDLE hDevice, ULONG Pipe);

USBDRVD_API BOOL USBDRVD_ResetPipe(HANDLE hDevice, ULONG Pipe);

typedef struct _USBDRV_DEVICE_DESCRIPTOR {
    UCHAR bLength;
    UCHAR bDescriptorType;
    USHORT bcdUSB;
    UCHAR bDeviceClass;
    UCHAR bDeviceSubClass;
    UCHAR bDeviceProtocol;
    UCHAR bMaxPacketSize0;
    USHORT idVendor;
    USHORT idProduct;
    USHORT bcdDevice;
    UCHAR iManufacturer;
    UCHAR iProduct;
    UCHAR iSerialNumber;
    UCHAR bNumConfigurations;
} USBDRV_DEVICE_DESCRIPTOR, *PUSBDRV_DEVICE_DESCRIPTOR;

USBDRVD_API UINT USBDRVD_GetDeviceDescriptor(HANDLE hDevice, PUSBDRV_DEVICE_DESCRIPTOR Device);


typedef struct _USBDRV_CONFIGURATION_DESCRIPTOR {
    UCHAR bLength;
    UCHAR bDescriptorType;
    USHORT wTotalLength;
    UCHAR bNumInterfaces;
    UCHAR bConfigurationValue;
    UCHAR iConfiguration;
    UCHAR bmAttributes;
    UCHAR MaxPower;
} USBDRV_CONFIGURATION_DESCRIPTOR, *PUSBDRV_CONFIGURATION_DESCRIPTOR;

USBDRVD_API UINT USBDRVD_GetConfigDescriptor(HANDLE hDevice, PUSBDRV_CONFIGURATION_DESCRIPTOR ConfigDesc);

typedef struct _USBDRV_INTERFACE_DESCRIPTOR {
    UCHAR bLength;
    UCHAR bDescriptorType;
    UCHAR bInterfaceNumber;
    UCHAR bAlternateSetting;
    UCHAR bNumEndpoints;
    UCHAR bInterfaceClass;
    UCHAR bInterfaceSubClass;
    UCHAR bInterfaceProtocol;
    UCHAR iInterface;
} USBDRV_INTERFACE_DESCRIPTOR, *PUSBDRV_INTERFACE_DESCRIPTOR;


USBDRVD_API UINT USBDRVD_GetInterfaceDescriptor(HANDLE hDevice, PUSBDRV_INTERFACE_DESCRIPTOR InterfaceDesc);

typedef struct _USBDRV_ENDPOINT_DESCRIPTOR {
    UCHAR bLength;
    UCHAR bDescriptorType;
    UCHAR bEndpointAddress;
    UCHAR bmAttributes;
    USHORT wMaxPacketSize;
    UCHAR bInterval;
} USBDRV_ENDPOINT_DESCRIPTOR, *PUSBDRV_ENDPOINT_DESCRIPTOR;

USBDRVD_API UINT USBDRVD_GetEndpointDescriptor(HANDLE hDevice, UCHAR Endpoint, PUSBDRV_ENDPOINT_DESCRIPTOR EndpointDesc);


typedef struct _USBDRV_STRING_DESCRIPTOR {
    UCHAR bLength;
    UCHAR bDescriptorType;
    WCHAR bString[1];
} USBDRV_STRING_DESCRIPTOR, *PUSBDRV_STRING_DESCRIPTOR;

USBDRVD_API UINT USBDRVD_GetStringDescriptorLength(HANDLE hDevice, USHORT LangID, ULONG Index);

USBDRVD_API UINT USBDRVD_GetStringDescriptor(HANDLE hDevice, USHORT LangID, ULONG Index, ULONG Length, PCHAR pString);


USBDRVD_API UINT USBDRVD_GetDriverVersion(HANDLE hDevice, ULONG *pMajor, ULONG *pMinor);

USBDRVD_API BOOL USBDRVD_SelectInterface(HANDLE hDevice, UCHAR Interface, UCHAR AlternateSetting);

USBDRVD_API ULONG USBDRVD_InterruptRead(HANDLE hDevice, ULONG Pipe, BYTE *pBuff, ULONG Count);

USBDRVD_API ULONG USBDRVD_InterruptWrite(HANDLE hDevice, ULONG Pipe, BYTE *pBuff, ULONG Count);


USBDRVD_API ULONG USBDRVD_ISORead(HANDLE hDevice);

USBDRVD_API ULONG USBDRVD_ISOWrite(HANDLE hDevice);


USBDRVD_API ULONG USBDRVD_GetLanguageIDs(HANDLE hDevice, ULONG Count, USHORT *pIDS);

USBDRVD_API ULONG USBDRVD_GetNumberOfLanguageIDs(HANDLE hDevice, USHORT *pIDS);


USBDRVD_API ULONG USBDRVD_VendorOrClassRequestOut(HANDLE hDevice, 
                                                 UCHAR Type,                           // 1=class, 2 = vendor                        
                                                 UCHAR Destination,                    // 0=device, 1=interface, 
                                                                                       // 2=endpoint, 3=other 
                                                // see the USB Specification for an explanation of the following
                                                 UCHAR Request,                        // request                                    
                                                 USHORT Value,                         // value                                      
                                                 USHORT Index,                         // index                                      
                                                 PUCHAR pData,                         // data buffer
                                                 ULONG Length);                        // length of data 

USBDRVD_API ULONG USBDRVD_VendorOrClassRequestIn(HANDLE hDevice, 
                                                 UCHAR Type,                           // 1=class, 2 = vendor                        
                                                 UCHAR Destination,                    // 0=device, 1=interface, 
                                                                                       // 2=endpoint, 3=other 
                                                // see the USB Specification for an explanation of the following
                                                 UCHAR Request,                        // request                                    
                                                 USHORT Value,                         // value                                      
                                                 USHORT Index,                         // index                                      
                                                 PUCHAR pData,                         // data buffer
                                                 ULONG Length);                        // length of data 


USBDRVD_API ULONG USBDRVD_BulkRead(HANDLE hDevice, ULONG Pipe, BYTE *pBuff, ULONG Count);

USBDRVD_API ULONG USBDRVD_BulkWrite(HANDLE hDevice, ULONG Pipe, BYTE *pBuff, ULONG Count);


enum CY_DEVICE_TYPE {
    EZUSB,
    FX2,
    SX2,
    CY_INVALID
};


USBDRVD_API int USBDRVD_EZUSBDownloadRam(const HINSTANCE hinstApp, const HWND hwndParent, 
                                         const HANDLE hDevice, enum CY_DEVICE_TYPE Type,
                                         const char * pPath, BOOLEAN bRun);

USBDRVD_API int USBDRVD_EZUSBDownloadI2C(const HINSTANCE hinstApp, const HWND hwndParent, 
                                         const HANDLE hDevice, const char * pPath);



////////////////////////////////////////////////////////////////////////////////
/////////////////  Pipe Functions  /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//Opens Pipe on device DevNum returning handle for pipe operations 
USBDRVD_API HANDLE USBDRVD_PipeOpen(UINT DevNum, UINT Pipe, DWORD dwFlagsAndAttributes, const GUID *pUSB_GUID);

USBDRVD_API HANDLE USBDRVD_PipeOpenPath(char *Path, UINT Pipe, DWORD dwFlagsAndAttributes);

//Given hPipe from prior USBDRVD_OpenPipe(), closes the pipe
USBDRVD_API void USBDRVD_PipeClose(HANDLE hPipe);

//Resets hPipe after a stall condition. (not normally needed, but provided)
USBDRVD_API BOOL USBDRVD_PipeReset(HANDLE hPipe);

//Aborts hPipe.  Any pending IRP's are cancelled
USBDRVD_API BOOL USBDRVD_PipeAbort(HANDLE hPipe);

//Writefile() wrapper
USBDRVD_API BOOL USBDRVD_PipeWrite(HANDLE hPipe, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite,
                                 LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

//Writefile() wrapper with timeout
USBDRVD_API BOOL USBDRVD_PipeWriteTimeout(HANDLE hPipe, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite,
                                 LPDWORD lpNumberOfBytesWritten, DWORD dwTimeout);

//ReadFile() wrapper
USBDRVD_API BOOL USBDRVD_PipeRead(HANDLE hPipe, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                                 LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

//ReadFile() wrapper with timeout
USBDRVD_API BOOL USBDRVD_PipeReadTimeout(HANDLE hPipe, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                                 LPDWORD lpNumberOfBytesRead, DWORD dwTimeout);


#ifdef __cplusplus
}
#endif


#endif