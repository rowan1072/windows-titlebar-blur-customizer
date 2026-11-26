/**
 * FileName: windows-titlebar-blur-customizer.h
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
#include "Common/CommonDef.h"

namespace Mwindows-titlebar-blur-customizerExt
{
	bool Startup();
	void Shutdown();
	void Refresh(bool reload = true);
	void RefreshAccentColor(COLORREF color);

	void CreateNotifyThread();
	void CloseNotifyThread();
}