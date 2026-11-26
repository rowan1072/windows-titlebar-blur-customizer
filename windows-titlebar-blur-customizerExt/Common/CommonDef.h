/**
 * FileName: CommonDef.h
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
#include "HookDef.h"

namespace Mwindows-titlebar-blur-customizerExt::CommonDef
{
	extern ConfigData g_configData;
	extern DWM::CWindowList* g_windowList;
	extern thread_local HWND g_window;
	extern COLORREF g_accentColor;
}