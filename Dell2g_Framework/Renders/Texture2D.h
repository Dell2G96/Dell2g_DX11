#pragma once

class CImage
{
public:
    CImage(wstring InFIle);
    ~CImage();
    
public:
    const DirectX::Image* GetImages();
    UINT GetImageCount();
    DirectX::TexMetadata* GetMetadata() {return Metadata;}

public:
    void GetPixels(vector<FColor>& OutPixels);
    
public:
    UINT GetWidth() {return Metadata->width;}
    UINT GetHeight() {return Metadata->height;}
    
    
private:
    wstring File;
    wstring Extension;
    
private:
    DirectX::TexMetadata* Metadata;
    DirectX::ScratchImage* SImage;
};

///////////////////////////////////////////////////////////////////////////////
class CTexture2D
{
public:
	CTexture2D(wstring InFile, bool bDefaultPath = true);
    CTexture2D(CShader* InShader, string InParamName, wstring InFile, bool bDefaultPath = true);
    ~CTexture2D();
    
    void Render();
public:
    operator ID3D11ShaderResourceView* ();
    
public:
    CImage* GetImage() {return Image;}
    
private:
    CImage* Image;
    ID3D11ShaderResourceView* SRV = nullptr;
    
private:
    CShader* Shader = nullptr;
    ID3DX11EffectShaderResourceVariable* sSRV;
};
