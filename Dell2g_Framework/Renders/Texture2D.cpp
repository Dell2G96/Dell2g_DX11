#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;

CImage::CImage(wstring InFIle)
{
    Metadata = new TexMetadata();
    SImage = new ScratchImage();
    
    Extension = CPath::GetExtension(File);
    
    HRESULT hr = GetMetadataFromWICFile(InFIle.c_str(), WIC_FLAGS_NONE, *Metadata);
    Check(hr);
    
    hr = LoadFromWICFile(InFIle.c_str(), WIC_FLAGS_NONE, Metadata, *SImage);
    Check(hr);
}

CImage::~CImage()
{
    Delete(SImage);
    Delete(Metadata);
}

const DirectX::Image* CImage::GetImages()
{
    if (SImage == nullptr)
        return nullptr;
    return SImage->GetImages();
}

UINT CImage::GetImageCount()
{
    if (SImage == nullptr)
        return 0;

    return SImage->GetImageCount();
}

void CImage::GetPixels(vector<FColor>& OutPixels)
{
    DXGI_FORMAT format = Metadata->format;
    
    const Image* image = SImage->GetImage(0,0,0);
    assert(image != nullptr);
    
    UINT count = 0;
    for (UINT y = 0; y < image->height; y++)
    {
        BYTE* row = image->pixels + (y * image->rowPitch);
        
        for (UINT x = 0; x < image->width; x++)
        {
            BYTE* pixel = row + x * 4;
            
            float r = *(pixel + 0) / 256.0f;
            float g = *(pixel + 1) / 256.0f;
            float b = *(pixel + 2) / 256.0f;
            float a = *(pixel + 3) / 256.0f;
            
            OutPixels.push_back(FColor(r, g, b, a));
        }
    }
}

CTexture2D::CTexture2D(wstring InFile, bool bDefaultPath)
    :CTexture2D(nullptr, "", InFile, bDefaultPath)
{
}

CTexture2D::CTexture2D(CShader* InShader, string InParamName, wstring InFile, bool bDefaultPath)
    :Shader(InShader)
{
    if (bDefaultPath)
        InFile = L"../_Textures/" + InFile;
    
    Image = new CImage(InFile);
    
    HRESULT hr = CreateShaderResourceView(CD3D::Get()->GetDevice(), Image->GetImages(), Image->GetImageCount(), *Image->GetMetadata(), &SRV);
    Check(hr);
    
    if (Shader != nullptr)
        sSRV = Shader->AsSRV(InParamName);
}

CTexture2D::~CTexture2D()
{
    Delete(Image);
    Release(SRV);
}

void CTexture2D::Render()
{
    if (Shader == nullptr)
        return;
    
    sSRV->SetResource(SRV);
}

void CTexture2D::BindToPS(UINT InSlot)
{
    CD3D::Get()->GetDeviceContext()->PSSetShaderResources(InSlot, 1, &SRV);
}

CTexture2D::operator struct ID3D11ShaderResourceView*()
{
    return SRV;
}
