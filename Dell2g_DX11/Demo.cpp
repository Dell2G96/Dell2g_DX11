#include "Framework.h"
#include "Demo.h"

void Demo::Initialize()
{
    CContext::Get()->GetCamera()->SetPosition(FVector(0,0,-2));
    CContext::Get()->SetCameraMoveSpeed(1.0f);
    CContext::Get()->SetCameraRotaionSpeed(0.f);
    
    Shader = new CShader(L"12_Sampling.fx");
    
    // 버텍스 버퍼 설정
    Vertices = new FVertexTexture[VCount];

    Vertices[0].Position = FVector(-0.5f, -0.5f, 0.0f);
    Vertices[1].Position = FVector(-0.5f, +0.5f, 0.0f);
    Vertices[2].Position = FVector(+0.5f, -0.5f, 0.0f);
    Vertices[3].Position = FVector(+0.5f, +0.5f, 0.0f);

    Vertices[0].Uv = FVector2D(0.0f, 2.0f);
    Vertices[1].Uv = FVector2D(0.0f, 0.0f);
    Vertices[2].Uv = FVector2D(2.0f, 2.0f);
    Vertices[3].Uv = FVector2D(2.0f, 0.0f);
    
    Texture = new CTexture2D(Shader, "Map", L"../_Textures/김채원.png");
    
    VBuffer = new CVertexBuffer(Vertices,VCount, sizeof(FVertexTexture));
    
    
    // 인덱서 버퍼 설정
    Indices = new UINT[ICount]{0,1,2, 2,1,3};
    
    IBuffer = new CIndexBuffer(Indices, ICount);
    
	World = FMatrix::Identity;
}

void Demo::Destroy()
{
    Delete(Shader);
    
    DeleteArray(Vertices);
    Delete(VBuffer);
    
    DeleteArray(Indices);
    Delete(IBuffer);
    
    Delete(Texture);
    
}

void Demo::Tick()
{

#pragma region 도형 이동

    if (CKeyboard::Get()->Press(VK_RIGHT))
        World.M41 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_LEFT))
        World.M41 -= 1.0f * CTimer::Get()->GetDeltaTime();
    
    if (CKeyboard::Get()->Press(VK_UP))
        World.M43 += 1.0f * CTimer::Get()->GetDeltaTime();
    else if (CKeyboard::Get()->Press(VK_DOWN))
        World.M43 -= 1.0f * CTimer::Get()->GetDeltaTime();
#pragma endregion
    
#pragma region 마우스 위치, 델타 값
    ImGui::Text("Position : %s", CMouse::Get()->GetPosition().ToString().c_str());
    ImGui::Text("Delta : %s", CMouse::Get()->GetDelta().ToString().c_str());
#pragma endregion
    
    // Address 설정 동적으로 바꾸기
    ImGui::InputInt("Address", (int*)&Address);
    Address = FMath::Clamp<UINT>(Address, 0, 3);
}

void Demo::Render()
{
    Shader->AsMatrix("World")->SetMatrix(World);
    
    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);
    
    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
    
    Shader->AsScalar("Address")->SetInt(Address);
    

    VBuffer->Render();
    IBuffer->Render();
    Texture->Render();
    
    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetPassNumber(0);
    Shader->DrawIndexed(ICount);
}
