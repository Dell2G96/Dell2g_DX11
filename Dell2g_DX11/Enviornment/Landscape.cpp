#include "Framework.h"

#include "Landscape.h"

CLandscape::CLandscape()
{
    Shader = new CShader(L"17_Landscape_Normal.fx");
    
    HeightMap = new CTexture2D(L"Landscape/Height256x256.png");
    
    CreateVertexData();
    CreateIndexedData();
	CreateNormalVector();
    CreateBuffer();
    
    World = FMatrix::Identity;
    
	Texture = new CTexture2D(Shader, "Map", L"Brix.png");
	Line3D = new CLine3D(Width * Height);
}

CLandscape::~CLandscape()
{
	Delete(Shader);
	Delete(HeightMap);

	DeleteArray(Vertices);
	DeleteArray(Indices);

	Delete(VBuffer);
	Delete(IBuffer);

	Delete(Texture);
	Delete(Line3D);
}

void CLandscape::Tick()
{
	Shader->AsMatrix("World")->SetMatrix(World);
	
	FMatrix view =CContext::Get()->GetView();
	Shader->AsMatrix("View")->SetMatrix(view);
	
	FMatrix projection =CContext::Get()->GetProjection();
	Shader->AsMatrix("Projection")->SetMatrix(projection);
	
	ImGui::InputFloat("Tiling - X", &Tiling.X, 1.0f);
	ImGui::InputFloat("Tiling - Y", &Tiling.Y, 1.0f);
	Shader->AsVector("Tiling")->SetFloatVector(Tiling);
	
	ImGui::SliderFloat3("LightDirection", LightDirection, -1.0f, +1.0f);
	Shader->AsVector("LightDirection")->SetFloatVector(LightDirection);

	for (UINT z = 0; z < Height; z++)
	{
		for (UINT x = 0; x < Width ; x++)
		{
			UINT index = Width * z + x;
			
			FVector position = Vertices[index].Position;
			FVector normal = Vertices[index].Normal;
			Line3D->Add(position, position + normal, FColor::Blue);
		}
	}
	Line3D->Tick();
}

void CLandscape::Render()
{
	Line3D->Render();
	VBuffer->Render();
	IBuffer->Render();
	
	CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	Texture->Render();
	Shader->SetPassNumber(Pass);
	Shader->DrawIndexed(ICount);
	
}

void CLandscape::CreateVertexData()
{
	vector<FColor> pixels;
	HeightMap->GetImage()->GetPixels(pixels);
	
	Width = HeightMap->GetImage()->GetWidth();
	Height = HeightMap->GetImage()->GetHeight();
	
	VCount = Width * Height;
	Vertices = new FVertexTextureNormal[VCount];
	
	for (UINT z = 0; z < Height; z++)
	{
		for (UINT x = 0; x < Width; x++)
		{
			UINT index = Width * z + x;
			
			Vertices[index].Position.X = (float)x;
			Vertices[index].Position.Y = pixels[index].R * MaxHeight;
			//Vertices[index].Position.Y = -0.1f; // 평평한 버전
			Vertices[index].Position.Z = (float)z;
			
			Vertices[index].Uv.X = (float)x / (float)Width;
			Vertices[index].Uv.Y = (float)z / (float)Height;
		}
	}
}

void CLandscape::CreateIndexedData()
{
	ICount = (Width -1) * (Height -1) * 6;
	Indices = new UINT[ICount];
	
	UINT index = 0;
	for (UINT z = 0; z < Height -1 ; z++)
	{
		for (UINT x = 0; x < Width - 1; x ++)
		{
			Indices[index + 0] = Width * z +x;
			Indices[index + 1] = Width * (z+1) +x;
			Indices[index + 2] = Width * z +(x+1);
			
			Indices[index + 3] = Width * z +(x+1);
			Indices[index + 4] = Width * (z+1) +x;
			Indices[index + 5] = Width * (z + 1) + (x+1);
			index += 6;
		}
	}
}

void CLandscape::CreateNormalVector()
{
	for (UINT i = 0; i < ICount / 3; i++)
	{
		UINT index0 = Indices[i * 3 + 0]; // 정점 위치 : 0    
		UINT index1 = Indices[i * 3 + 1]; // 정점 위치 : 256
		UINT index2 = Indices[i * 3 + 2]; // 정점 위치 : 1
		
		FVertexTerrain& v0 = Vertices[index0];
		FVertexTerrain& v1 = Vertices[index1];
		FVertexTerrain& v2 = Vertices[index2];
		
		FVector e1 = v1.Position - v0.Position;
		FVector e2 = v2.Position - v0.Position;
		
		FVector normal = FVector::Cross(e1, e2);
		
		v0.Normal += normal;
		v1.Normal += normal;
		v2.Normal += normal;
	}
	for (UINT i = 0; i< VCount; i++)
		Vertices[i].Normal = FVector::Normalize(Vertices[i].Normal);
}

void CLandscape::CreateBuffer()
{
	VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTerrain));
	IBuffer= new CIndexBuffer(Indices, ICount);
}






















