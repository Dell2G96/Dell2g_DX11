#include "Framework.h"
#include "Demo2.h"

void CDemo2::Initialize()
{
    Shader = new CShader(L"11_VertexColor.fx");

    Vertices = new FVertexColor[VCount];
    
    float w = 0.5f, h = 0.5f , d = 0.5f;
    
    // 버텍스 버퍼
    	//Front
	Vertices[0].Position = FVector(-w, -h, -d);
	Vertices[1].Position = FVector(-w, +h, -d);
	Vertices[2].Position = FVector(+w, -h, -d);
	Vertices[3].Position = FVector(+w, +h, -d);

	Vertices[0].Color = FColor(1, 0, 0, 1);
	Vertices[1].Color = FColor(1, 0, 0, 1);
	Vertices[2].Color = FColor(1, 0, 0, 1);
	Vertices[3].Color = FColor(1, 0, 0, 1);


	//Back
	Vertices[4].Position = FVector(-w, -h, +d);
	Vertices[5].Position = FVector(+w, -h, +d);
	Vertices[6].Position = FVector(-w, +h, +d);
	Vertices[7].Position = FVector(+w, +h, +d);

	Vertices[4].Color = FColor(0, 1, 0, 1);
	Vertices[5].Color = FColor(0, 1, 0, 1);
	Vertices[6].Color = FColor(0, 1, 0, 1);
	Vertices[7].Color = FColor(0, 1, 0, 1);


	//Top
	Vertices[8].Position = FVector(-w, +h, -d);
	Vertices[9].Position = FVector(-w, +h, +d);
	Vertices[10].Position = FVector(+w, +h, -d);
	Vertices[11].Position = FVector(+w, +h, +d);

	Vertices[8].Color = FColor(0, 0, 1, 1);
	Vertices[9].Color = FColor(0, 0, 1, 1);
	Vertices[10].Color = FColor(0, 0, 1, 1);
	Vertices[11].Color = FColor(0, 0, 1, 1);


	//Bottom
	Vertices[12].Position = FVector(-w, -h, -d);
	Vertices[13].Position = FVector(+w, -h, -d);
	Vertices[14].Position = FVector(-w, -h, +d);
	Vertices[15].Position = FVector(+w, -h, +d);

	Vertices[12].Color = FColor(1, 0, 1, 1);
	Vertices[13].Color = FColor(1, 0, 1, 1);
	Vertices[14].Color = FColor(1, 0, 1, 1);
	Vertices[15].Color = FColor(1, 0, 1, 1);


	//Left
	Vertices[16].Position = FVector(-w, -h, +d);
	Vertices[17].Position = FVector(-w, +h, +d);
	Vertices[18].Position = FVector(-w, -h, -d);
	Vertices[19].Position = FVector(-w, +h, -d);

	Vertices[16].Color = FColor(1, 1, 0, 1);
	Vertices[17].Color = FColor(1, 1, 0, 1);
	Vertices[18].Color = FColor(1, 1, 0, 1);
	Vertices[19].Color = FColor(1, 1, 0, 1);


	//Right
	Vertices[20].Position = FVector(+w, -h, -d);
	Vertices[21].Position = FVector(+w, +h, -d);
	Vertices[22].Position = FVector(+w, -h, +d);
	Vertices[23].Position = FVector(+w, +h, +d);

	Vertices[20].Color = FColor(1, 1, 1, 1);
	Vertices[21].Color = FColor(1, 1, 1, 1);
	Vertices[22].Color = FColor(1, 1, 1, 1);
	Vertices[23].Color = FColor(1, 1, 1, 1);

	VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexColor));
	
	Indices = new UINT[ICount]
    {
    	0, 1, 2, 2, 1, 3,
		4, 5, 6, 6, 5, 7,
		8, 9, 10, 10, 9, 11,
		12, 13, 14, 14, 13, 15,
		16, 17, 18, 18, 17, 19,
		20, 21, 22, 22, 21, 23,
    };
	IBuffer = new CIndexBuffer(Indices, ICount);
    World = FMatrix::Identity; //단위 행렬
}

void CDemo2::Destroy()
{
    Delete(Shader);

    DeleteArray(Vertices);
    Delete(VBuffer);

    DeleteArray(Indices);
    Delete(IBuffer);
}

void CDemo2::Tick()
{
 //    if (CMouse::Get()->Press(EMouseButton::Right))
 //    {
	//     RotationY -= Speed * CMouse::Get()->GetDelta().X * CTimer::Get()->GetDeltaTime();
 //    	
 //    	RotationY = FMath::WrapAngle(RotationY);
 //    	Radian = FMath::ToRadians(RotationY);
 //    	World = FMatrix::CreateRotationY(Radian);
 //    }
	// ImGui::Text("Radian : %f", Radian);
	// ImGui::Text("RotationY : %f", RotationY);
}

void CDemo2::Render()
{
    Shader->AsMatrix("World")->SetMatrix(World);

    FMatrix view = CContext::Get()->GetView();
    Shader->AsMatrix("View")->SetMatrix(view);

    FMatrix projection = CContext::Get()->GetProjection();
    Shader->AsMatrix("Projection")->SetMatrix(projection);
	
    VBuffer->Render();
    IBuffer->Render();

    CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Shader->SetPassNumber(0);
    Shader->DrawIndexed(ICount);
}
