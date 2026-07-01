    #pragma once

#include <Windows.h>
#include <assert.h>

#include <string>
#include <bitset>
#include <fstream>
using namespace  std;

// 날짜 , 현재 시간 표시하기 위해서 추가
#include <ctime>
#include <iomanip>
#include <sstream>

#include <chrono>
using namespace chrono;

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

//DirectXTex
#include <DirectXTex.h>
# pragma comment(lib, DirectXTex.lib)


//json
#include <json/Json.h>
#pragma comment(lib, Jsoncpp_static.lib)



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
#include "Systems/HLSLShader.h"
#include "Systems/Gui.h"
#include "Systems/Timer.h"
#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"

#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/ConstantBuffer.h"

#include "Viewer/Camera.h"

#include "Utilities/Path.h"
#include "Utilities/String.h"
#include "Utilities/BinaryFile.h"

#include "Renders/Context.h"
#include "Renders/VertexLayout.h"
#include "Renders/Texture2D.h"
#include "Renders/SamplerState.h"
#include "Renders/Material.h"


#include "Models/MeshRenderer.h"
#include "Models/ModelMesh.h"


#include "Objects/Line3D.h"

#include "Enviornment/Landscape.h"
#include "Enviornment/Landscape-HLSL.h"
