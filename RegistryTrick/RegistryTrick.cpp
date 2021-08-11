#include <Windows.h>
#include "RegistryTrick.h"

int main()
{

    HMODULE hNTDLL = LoadLibrary(_T("ntdll.dll"));
    if (hNTDLL == 0) {

        _tprintf(_T("LoadLibrary(ntdll) failure\n"));
        return -1;
    }

    fZwOpenKey ZwOpenKey = (fZwOpenKey)GetProcAddress(hNTDLL, "ZwOpenKey");
    fZwClose ZwClose = (fZwClose)GetProcAddress(hNTDLL, "ZwClose");
    fRtlInitUnicodeString RtlInitUnicodeString = (fRtlInitUnicodeString)GetProcAddress(hNTDLL, "RtlInitUnicodeString");
    fZwEnumerateKey ZwEnumerateKey = (fZwEnumerateKey)GetProcAddress(hNTDLL, "ZwEnumerateKey");
    fZwQueryValueKey ZwQueryValueKey = (fZwQueryValueKey)GetProcAddress(hNTDLL, "ZwQueryValueKey");
    fZwCreateKey ZwCreateKey = (fZwCreateKey)GetProcAddress(hNTDLL, "ZwCreateKey");
    fZwSetValueKey ZwSetValueKey = (fZwSetValueKey)GetProcAddress(hNTDLL, "ZwSetValueKey");
    fZwDeleteKey ZwDeleteKey = (fZwDeleteKey)GetProcAddress(hNTDLL, "ZwDeleteKey");
    

    HANDLE hKey;
    WCHAR regPath[] = L"\\Registry\\Machine\\SOFTWARE\\a_\x00\x00MyProgram";
    DWORD dwBufferSize = sizeof(regPath) - 2;

    UNICODE_STRING uni = { dwBufferSize, dwBufferSize, (PWSTR)regPath };
    OBJECT_ATTRIBUTES ObjectAttr = { 0, };
    ObjectAttr.Length = sizeof(OBJECT_ATTRIBUTES);
    ObjectAttr.ObjectName = &uni;
    ObjectAttr.Attributes = OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE;

    // Create
    if (ZwCreateKey(&hKey, KEY_ALL_ACCESS, &ObjectAttr, NULL, NULL, NULL, NULL) == STATUS_SUCCESS) {
        _tprintf(TEXT("ZwCreateKey Success\n"));
        ZwClose(hKey);
    }
    else {
        _tprintf(TEXT("Failure\n"));
    }

    // Open
    DWORD dwStatus = ZwOpenKey(&hKey, KEY_ALL_ACCESS, &ObjectAttr);
    if (dwStatus == STATUS_SUCCESS) {
        _tprintf(TEXT("ZwOpenKey Success\n"));

        _getch();

        // Delete
        DWORD a = ZwDeleteKey(hKey);
        _tprintf(TEXT("ZwDeleteKey: %08X\n"), a);

        ZwClose(hKey);
    }
    else {
        _tprintf(TEXT("Failure\n"));
        _tprintf(TEXT("%X\n"), dwStatus);
    }



    //{
    //    BYTE SubBuffer[260] = { 0, };
    //    DWORD SubBufferSize = 260;
    //    DWORD ReturnSize = 260;
    //    DWORD dwRet = ZwEnumerateKey(hKey, 0, KeyBasicInformation, SubBuffer, SubBufferSize, &ReturnSize);
    //    printf("dwRet : %X\n", dwRet);

    //    printf("--------------------------------------------------------\n");
    //    PKEY_BASIC_INFORMATION p = (PKEY_BASIC_INFORMATION)SubBuffer;
    //    for (int i = 0; i < p->NameLength / 2; i++) {
    //        printf("\t%02X %c\n", p->Name[i], p->Name[i]);
    //    }
    //    printf("--------------------------------------------------------\n");
    //}


    //{
    //    WCHAR regPath[] = L"SOFTWARE\\WOW6432Node";

    //    HKEY hKey;
    //    DWORD bOpen = RegOpenKeyExW(HKEY_LOCAL_MACHINE, regPath, 0, 0x2001Fu, &hKey);
    //    printf("bOpen : %d\n", bOpen);

    //    wchar_t firstKey[260] = { 0, };
    //    DWORD dwLen = 260;

    //    DWORD ret = RegEnumKeyEx(hKey, 4, firstKey, &dwLen, NULL, NULL, NULL, NULL);
    //    printf("dwLen : %d\n", dwLen);
    //    for (int i = 0; i < dwLen; i++) {
    //        if (firstKey[i] == 0)
    //            printf("\\x00");
    //        else
    //            printf("%c", firstKey[i]);
    //    }

    //    RegCloseKey(hKey);
    //}



    
    return 0;
  
}
