#pragma once


#define ulong unsigned long
#define ulonglong unsigned long long
#define longlong long long
#define ULONG unsigned long
#define ULONGLONG unsigned long long
#define ushort unsigned short
#define USHORT unsigned short
#define uchar unsigned char

typedef struct _UNICODE_STRING
{
	unsigned short Length;
	unsigned short MaxLength;
	unsigned long Pad;
	wchar_t* Buffer;
}UNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
  ULONGLONG           Length;
  HANDLE          RootDirectory;
  _UNICODE_STRING* ObjectName;
  ULONGLONG           Attributes;
  PVOID           SecurityDescriptor;
  PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK {
  union {
    int Status;
    void*    Pointer;
  } DUMMYUNIONNAME;
  ulonglong Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;


#define OBJ_CASE_INSENSITIVE 0x40


#define FILE_OPEN 0x1

#define 	FILE_DIRECTORY_FILE   0x00000001
#define 	FILE_WRITE_THROUGH   0x00000002
#define 	FILE_SEQUENTIAL_ONLY   0x00000004
#define 	FILE_NO_INTERMEDIATE_BUFFERING   0x00000008
#define 	FILE_SYNCHRONOUS_IO_ALERT   0x00000010
#define 	FILE_SYNCHRONOUS_IO_NONALERT   0x00000020
#define 	FILE_NON_DIRECTORY_FILE   0x00000040
#define 	FILE_CREATE_TREE_CONNECTION   0x00000080
#define 	FILE_COMPLETE_IF_OPLOCKED   0x00000100
#define 	FILE_NO_EA_KNOWLEDGE   0x00000200
#define 	FILE_OPEN_FOR_RECOVERY   0x00000400
#define 	FILE_RANDOM_ACCESS   0x00000800
#define 	FILE_DELETE_ON_CLOSE   0x00001000
#define 	FILE_OPEN_BY_FILE_ID   0x00002000
#define 	FILE_OPEN_FOR_BACKUP_INTENT   0x00004000
#define 	FILE_NO_COMPRESSION   0x00008000
#define 	FILE_OPEN_REQUIRING_OPLOCK   0x00010000
#define 	FILE_DISALLOW_EXCLUSIVE   0x00020000
#define 	FILE_SESSION_AWARE   0x00040000
#define 	FILE_RESERVE_OPFILTER   0x00100000
#define 	FILE_OPEN_REPARSE_POINT   0x00200000
#define 	FILE_OPEN_NO_RECALL   0x00400000
#define 	FILE_OPEN_FOR_FREE_SPACE_QUERY   0x00800000



extern "C"
{
	int ZwCreateFile(HANDLE* pFileHandle,
					ulong DesiredAccess, 
					_OBJECT_ATTRIBUTES* ObjectAttributes, 
					void* IoStatusBlock, 
					_LARGE_INTEGER* AllocationSize, 
					ulonglong FileAttributes,
					ulonglong ShareAccess, 
					ulonglong CreateDisposition, 
					ulonglong CreateOptions, 
					void* EaBuffer, 
					ulonglong EaLength);


	ulonglong ZwDeviceIoControlFile(HANDLE FileHandle,
								HANDLE Event, 
								void* ApcRoutine, 
								void* ApcContext, 
								_IO_STATUS_BLOCK* IoStatusBlock, 
								ulonglong IoControlCode, 
								void* InputBuffer, 
								ulonglong InputBufferLength, 
								void* OutputBuffer, 
								ulonglong OutputBufferLength);
}