// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "framework.h"
#include "windows-titlebar-blur-customizer.h"
#include <minidumpapiset.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if(ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        std::thread([hModule] 
        {
        	if (!Mwindows-titlebar-blur-customizerExt::Startup())
			{
				Mwindows-titlebar-blur-customizerExt::CloseNotifyThread();
				FreeLibrary(hModule);
			}
            Mwindows-titlebar-blur-customizerExt::CreateNotifyThread();
        }).detach();
    }
    else if(ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        Mwindows-titlebar-blur-customizerExt::Shutdown();
        Mwindows-titlebar-blur-customizerExt::CloseNotifyThread();
    }
    return TRUE;
}

