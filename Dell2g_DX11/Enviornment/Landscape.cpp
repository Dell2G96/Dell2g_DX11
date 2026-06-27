#include "Framework.h"
#include "Landscape.h"

CLandscape::CLandscape()
{
    Shader = new CShader(L"14_Landscape.fx");
    
    HeightMap = new CTexture2D(L"Landscape/Height256x256.png");
    
    CreateVertexData();
    CreateIndexedData();
    CreateBuffer();
    
    World = FMatrix::Identity;
    
	Texture = new CTexture2D(Shader, "Map", L"Checker.png");
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
}

void CLandscape::Render()
{
	
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
	Vertices = new FVertexTexture[VCount];
	
	for (UINT z = 0; z < Height; z++)
	{
		for (UINT x = 0; x < Width; x++)
		{
			UINT index = Width * z + x;
			
			Vertices[index].Position.X = (float)x;
			//Vertices[index].Position.Y = pixels[index].R * MaxHeight;
			Vertices[index].Position.Y = -0.1f;
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

void CLandscape::CreateBuffer()
{
	VBuffer = new CVertexBuffer(Vertices, VCount, sizeof(FVertexTexture));
	IBuffer= new CIndexBuffer(Indices, ICount);
}






















