/**
 * FileName: winmain.cpp
 *
 * Copyright (C) 2024 Maplespe
 *
 * This file is part of MToolBox and windows-titlebar-blur-customizer.
 * windows-titlebar-blur-customizer is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3
 * of the License, or any later version.
 *
 * windows-titlebar-blur-customizer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with Foobar.
 * If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
*/
#include "framework.h"
#include "UIManager.h"
#include "MainWindow.h"
#include "Helper/Helper.h"
#include "MHostHelper.h"
#include "Extend/ColorDisplay.h"
#include <Knownfolders.h>
#include <Shlobj.h>
#include <minidumpapiset.h>
#include "Helper/wil.h"

using namespace Mui;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

#ifndef _DEBUG
	if (!Mwindows-titlebar-blur-customizer::IsRunasAdmin())
		return 0;
#endif

	auto [locale, parentLocale] = Mwindows-titlebar-blur-customizer::GetSystemLocaleAndParent();

	if (!Mwindows-titlebar-blur-customizer::LoadLanguageFileList() 
		|| (!Mwindows-titlebar-blur-customizer::LoadBaseLanguageString(locale) && !Mwindows-titlebar-blur-customizer::LoadBaseLanguageString(parentLocale)
		&& !Mwindows-titlebar-blur-customizer::LoadBaseLanguageString(L"en-US")))
	{
		MessageBoxW(nullptr, L"初始化失败: 没有有效的语言文件 (Initialization failed: No valid language file).", L"error", MB_ICONERROR);
		return 0;
	}

	PWSTR shfolder = nullptr;
	if (SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &shfolder) == S_OK)
	{
		std::wstring path = shfolder;
		CoTaskMemFree(shfolder);
		std::wstring curpath = Mwindows-titlebar-blur-customizer::Utils::GetCurrentDir();
		if (curpath.length() >= path.length() && curpath.substr(0, path.length()) == path)
		{
			MessageBoxW(nullptr,
				Helper::M_ReplaceString(Mwindows-titlebar-blur-customizer::GetBaseLanguageString(L"initfail0"), L"{path}", curpath).c_str(),
				L"Warning", MB_ICONWARNING | MB_TOPMOST);
			return false;
		}
	}

	if(lpCmdLine && _wcsicmp(lpCmdLine, L"runhost") == 0)
	{
		HANDLE hObject = CreateMutexW(nullptr, FALSE, L"_windows-titlebar-blur-customizer_host_");
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CloseHandle(hObject);
			return 0;
		}
		if (hObject)
			ReleaseMutex(hObject);

		Mwindows-titlebar-blur-customizer::MHostStartProcess();

		return 0;
	}

	HANDLE hObject = CreateMutexW(nullptr, FALSE, L"_windows-titlebar-blur-customizer_");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hObject);
		return 0;
	}
	if (hObject)
		ReleaseMutex(hObject);

	//初始化界面库 全局仅有一个MiaoUI类
	MiaoUI engine;
	std::wstring err;
	if (!engine.InitEngine(err, MiaoUI::Render::Gdiplus))
	{
		MessageBoxW(nullptr, (Mwindows-titlebar-blur-customizer::GetBaseLanguageString(L"inituifail0") + err).c_str(), L"error", MB_ICONERROR);
		return 0;
	}

	auto context = engine.CreateWindowCtx({ 0,0,500,730 }, MiaoUI::MWindowType::NoTitleBar,
		L"windows-titlebar-blur-customizer " + Mwindows-titlebar-blur-customizer::g_vernum, true, true, 0);
	if(!context)
	{
		MessageBoxW(nullptr, Mwindows-titlebar-blur-customizer::GetBaseLanguageString(L"inituifail1").c_str(), L"error", MB_ICONERROR);
		return 0;
	}

	ColorDisplay::Register();

	context->SetEventCallback(Mwindows-titlebar-blur-customizer::MainWindow_EventProc);
	context->SetEventSourceCallback(Mwindows-titlebar-blur-customizer::MainWindow_SrcEventProc);
	if(!context->InitWindow(Mwindows-titlebar-blur-customizer::MainWindow_InitWindow, false))
	{
		delete context;
		MessageBoxW(nullptr, Mwindows-titlebar-blur-customizer::GetBaseLanguageString(L"inituifail2").c_str(), L"error", MB_ICONERROR);
		return 0;
	}

	Mwindows-titlebar-blur-customizer::ClearBaseLanguage();

	//context->Base()->ShowDebugRect(true);
	context->Base()->CenterWindow();
	context->Base()->ShowWindow(true);


	context->EventLoop();

	Mwindows-titlebar-blur-customizer::MainWindow_Destroy();
	engine.UnInitEngine();

	return 0;
}
