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

#include "Buffers/VertexBuffer.h"