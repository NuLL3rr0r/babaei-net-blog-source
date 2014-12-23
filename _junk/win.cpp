#include <cstdio>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

using namespace std; 

DWORD ProcId = 0; // THIS IS OUR GLOBAL VARIABLE FOR THE PROC ID;

void GetProcId(const char* ProcName);

int main()
{
    char* ProcName;
    cout << "Please type the process name" << endl;
    cin >> ProcName;
    GetProcId(ProcName);
    printf("The Process ID of \" ProcName \" is %d", ProcId);
    cin.get(); // to keep console open till we press a key
    return 0;
}

void GetProcId(const char* ProcName)
{
	PROCESSENTRY32   pe32;
	HANDLE         hSnapshot = NULL;

	pe32.dwSize = sizeof( PROCESSENTRY32 );
	hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

	if( Process32First( hSnapshot, &pe32 ) )
	{
		do{
			if( strcmp( pe32.szExeFile, ProcName ) == 0 )
				break;
		}while( Process32Next( hSnapshot, &pe32 ) );
	}

	if( hSnapshot != INVALID_HANDLE_VALUE )
		CloseHandle( hSnapshot );

	ProcId = pe32.th32ProcessID;
}

int isRunning(char *pProcessName)
{
    HANDLE hSnap = INVALID_HANDLE_VALUE;
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 ProcessStruct;
    ProcessStruct.dwSize = sizeof(PROCESSENTRY32);
    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hSnap == INVALID_HANDLE_VALUE)
        return -1;
    if(Process32First(hSnap, &ProcessStruct) == FALSE)
        return -1;
    do
    {
        if(stricmp(strupr(ProcessStruct.szExeFile), pProcessName)==0)
        {
            CloseHandle( hSnap );
            return  ProcessStruct.th32ProcessID;
            break;
        }
    }
    while( Process32Next( hSnap, &ProcessStruct ) );
    CloseHandle( hSnap );
    return -1;
}

