/**
 * FileName: MHostHelper.h
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
#pragma once
#include "framework.h"
#include "Common.h"

namespace Mwindows-titlebar-blur-customizer
{
	bool MHostGetSymbolState();

	bool MHostDownloadSymbol();

	void MHostStartProcess();

	void RunMHostProcess();

	void StopMHostProcess();

	bool LoadDWMExtensionBase(std::wstring& err, DWORD pid);

	void MHostNotify(MHostNotifyType type, LPARAM param = 0);
}