#pragma once
#include "uDwmBackdrop.hpp"

namespace Mwindows-titlebar-blur-customizerExt::BackdropFactory
{
	wuc::CompositionBrush GetOrCreateBackdropBrush(
		const wuc::Compositor& compositor,
		DWORD color,
		bool active,
		DWM::ACCENT_POLICY* policy = nullptr
	);
	std::chrono::steady_clock::time_point GetBackdropBrushTimeStamp();

	void Shutdown();

	void RefreshConfig();
}