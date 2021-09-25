#include "running.hpp"
#include <Windows.h>
#include <stdio.h>

bool running() {
    //Make sure at most one instance of the tool is running
    HANDLE hMutexOneInstance(::CreateMutex(NULL, TRUE, (LPCWSTR)L"{BA99CF5E-B29A-425C-A07C-51B6525571AD}"));
    bool bAlreadyRunning((::GetLastError() == ERROR_ALREADY_EXISTS));
    if (hMutexOneInstance == NULL || bAlreadyRunning)
    {
        if (hMutexOneInstance)
        {
            ::ReleaseMutex(hMutexOneInstance);
            ::CloseHandle(hMutexOneInstance);
        }
        return true;
    }
    return false;
}
