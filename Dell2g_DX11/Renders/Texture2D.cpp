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

CTexture2D::CTexture2D(wstring InFile)
    :CTexture2D(nullptr, "", InFile)
{
}

CTexture2D::CTexture2D(CShader* InShader, string InParamName, wstring InFile)
    :Shader(InShader)
{
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

CTexture2D::operator struct ID3D11ShaderResourceView*()
{
    return SRV;
}
