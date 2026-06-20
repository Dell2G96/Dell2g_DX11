#pragma once

#include <Windows.h>
#include <assert.h>

#include <string>
using namespace  std;

// Window SDK
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

//Effect
#include <d3dcompiler.h>
// #include "Effect/d3dx11effect.h"
// #pragma comment(lib, "Effect/Effects11d.lib")

#include <Effects11/d3dx11effect.h>
#pragma comment(lib, "Effects11.lib")

// #include "ImGui/imgui.h"
// #include "ImGui/imgui_impl_dx11.h"
// #include "ImGui/imgui_impl_win32.h"
// #pragma comment(lib, "ImGui/ImGui.lib")

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>


#include "Definitions.h"

#include "Maths/Vector2D.h"
#include "Maths/Vector.h"
#include "Maths/Vector4.h"
#include "Maths/Quaternion.h"
#include "Maths/Matrix.h"
#include "Maths/Plane.h"
#include "Maths/Math.h"

#include "Renders/Color.h"

#include "Systems/D3D.h"
#include "Systems/Shader.h"
#include "Systems/Gui.h"

#include "Buffers/VertexBuffer.h"