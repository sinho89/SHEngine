#pragma once

#ifdef USE_IMGUI_MODULE
#include <ixrEngine/03.Graphics/ThirdParty/imgui/imgui.h>
#include <ixrEngine/03.Graphics/ThirdParty/imgui/imconfig.h>
#include <ixrEngine/03.Graphics/ThirdParty/imgui/backends/imgui_impl_win32.h>
#include <ixrEngine/03.Graphics/ThirdParty/imgui/backends/imgui_impl_dx11.h>

	#ifdef ENGINE
	#include <ixrEngine/03.Graphics/ThirdParty/imgui/backends/imgui_impl_dx11.cpp>
	#include <ixrEngine/03.Graphics/ThirdParty/imgui/backends/imgui_impl_win32.cpp>

	#include <ixrEngine/03.Graphics/ThirdParty/imgui/imgui.cpp>
	#include <ixrEngine/03.Graphics/ThirdParty/imgui/imgui_demo.cpp>
	#include <ixrEngine/03.Graphics/ThirdParty/imgui/imgui_draw.cpp>
	#include <ixrEngine/03.Graphics/ThirdParty/imgui/imgui_tables.cpp>
	#include <ixrEngine/03.Graphics/ThirdParty/imgui/imgui_widgets.cpp>
	#endif
#endif