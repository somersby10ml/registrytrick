#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

#pragma comment(lib, "advapi32.lib")
#include <aclapi.h>
#include <tchar.h>

//#include <winternl.h>

#define STATUS_SUCCESS                      0x00000000L
#define OBJ_KERNEL_HANDLE                   0x00000200L
#define OBJ_CASE_INSENSITIVE                0x00000040L



//NTSYSAPI NTSTATUS ZwOpenKey(
//    PHANDLE            KeyHandle,
//    ACCESS_MASK        DesiredAccess,
//    POBJECT_ATTRIBUTES ObjectAttributes
//);

typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataLength;
    UCHAR Data[1];
} KEY_VALUE_PARTIAL_INFORMATION, * PKEY_VALUE_PARTIAL_INFORMATION;

typedef struct _KEY_BASIC_INFORMATION {
    LARGE_INTEGER LastWriteTime;
    ULONG         TitleIndex;
    ULONG         NameLength;
    WCHAR         Name[1];
} KEY_BASIC_INFORMATION, * PKEY_BASIC_INFORMATION;

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG           Length;
    HANDLE          RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG           Attributes;
    PVOID           SecurityDescriptor;
    PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;

typedef enum _KEY_INFORMATION_CLASS {
    KeyBasicInformation,
    KeyNodeInformation,
    KeyFullInformation,
    KeyNameInformation,
    KeyCachedInformation,
    KeyFlagsInformation,
    KeyVirtualizationInformation,
    KeyHandleTagsInformation,
    KeyTrustInformation,
    KeyLayerInformation,
    MaxKeyInfoClass
} KEY_INFORMATION_CLASS;

typedef DWORD(WINAPI* fZwOpenKey)(PHANDLE KeyHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes);
typedef DWORD(WINAPI* fZwEnumerateKey)(
    HANDLE                KeyHandle,
    ULONG                 Index,
    KEY_INFORMATION_CLASS KeyInformationClass,
    PVOID                 KeyInformation,
    ULONG                 Length,
    PULONG                ResultLength
    );



typedef struct _KEY_VALUE_BASIC_INFORMATION {
    ULONG TitleIndex;
    ULONG Type;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_VALUE_BASIC_INFORMATION, * PKEY_VALUE_BASIC_INFORMATION;

typedef DWORD(WINAPI* fZwClose)(HANDLE Handle);
typedef DWORD(WINAPI* fRtlInitUnicodeString)(PUNICODE_STRING DestinationString, PCWSTR SourceString);

typedef enum _KEY_VALUE_INFORMATION_CLASS {
    KeyValueBasicInformation,
    KeyValueFullInformation,
    KeyValuePartialInformation,
    KeyValueFullInformationAlign64,
    KeyValuePartialInformationAlign64,
    KeyValueLayerInformation,
    MaxKeyValueInfoClass
} KEY_VALUE_INFORMATION_CLASS;

typedef DWORD(WINAPI* fZwQueryValueKey)(
    HANDLE                      KeyHandle,
    PUNICODE_STRING             ValueName,
    KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    PVOID                       KeyValueInformation,
    ULONG                       Length,
    PULONG                      ResultLength
);


typedef DWORD(WINAPI* fZwCreateKey)(
    PHANDLE            KeyHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    ULONG              TitleIndex,
    PUNICODE_STRING    Class,
    ULONG              CreateOptions,
    PULONG             Disposition
);

typedef DWORD(WINAPI* fZwSetValueKey)(
    HANDLE          KeyHandle,
    PUNICODE_STRING ValueName,
    ULONG           TitleIndex,
    ULONG           Type,
    PVOID           Data,
    ULONG           DataSize
);


typedef DWORD(WINAPI* fZwDeleteKey)(
    HANDLE KeyHandle
);


