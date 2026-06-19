#include "Framework.h"
#include "Shader.h"

CShader::CShader(wstring InFile)
	: File(L"../_Shaders/" + InFile)
{
	InitialStateBlock = new FStateBlock();
	{
		CD3D::Get()->GetDeviceContext()->RSGetState(&InitialStateBlock->RSRasterizerState);
		CD3D::Get()->GetDeviceContext()->OMGetBlendState(&InitialStateBlock->OMBlendState, InitialStateBlock->OMBlendFactor, &InitialStateBlock->OMSampleMask);
		CD3D::Get()->GetDeviceContext()->OMGetDepthStencilState(&InitialStateBlock->OMDepthStencilState, &InitialStateBlock->OMStencilRef);
	}

	CreateEffect();
}

CShader::~CShader()
{
	for (FTechnique& temp : Techniques)
	{
		for (FPass& pass : temp.Passes)
		{
			Release(pass.InputLayout);
		}
	}

	Delete(InitialStateBlock);
	Release(Effect);
}

void CShader::CreateEffect()
{
	ID3DBlob* fxBlob = nullptr;

	HRESULT hr;
	
	ID3DBlob* error = nullptr;
	INT flag = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_PACK_MATRIX_ROW_MAJOR;

	hr = D3DCompileFromFile(File.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, nullptr, "fx_5_0", flag, 0, &fxBlob, &error);
	if (FAILED(hr))
	{
		if (error != nullptr)
		{
			string str = (const char*)error->GetBufferPointer();
			MessageBoxA(nullptr, str.c_str(), "Shader Error", MB_OK);
		}

		assert(false && "Fx File not found");
	}
	

	hr = D3DX11CreateEffectFromMemory(fxBlob->GetBufferPointer(), fxBlob->GetBufferSize(), 0, CD3D::Get()->GetDevice(), &Effect);
	Check(hr);


	Effect->GetDesc(&EffectDesc);
	for (UINT t = 0; t < EffectDesc.Techniques; t++)
	{
		FTechnique technique;
		technique.ITechnique = Effect->GetTechniqueByIndex(t);
		technique.ITechnique->GetDesc(&technique.Desc);

		technique.Name = string(technique.Desc.Name);
		TechniqueNameMap[technique.Name] = t;

		for (UINT p = 0; p < technique.Desc.Passes; p++)
		{
			FPass pass;
			pass.IPass = technique.ITechnique->GetPassByIndex(p);
			pass.IPass->GetDesc(&pass.Desc);
			pass.IPass->GetVertexShaderDesc(&pass.PassVsDesc);
			pass.PassVsDesc.pShaderVariable->GetShaderDesc(pass.PassVsDesc.ShaderIndex, &pass.EffectVsDesc);

			for (UINT s = 0; s < pass.EffectVsDesc.NumInputSignatureEntries; s++)
			{
				D3D11_SIGNATURE_PARAMETER_DESC desc;

				HRESULT hr = pass.PassVsDesc.pShaderVariable->GetInputSignatureElementDesc(pass.PassVsDesc.ShaderIndex, s, &desc);
				Check(hr);

				pass.SignatureDescs.push_back(desc);
			}

			pass.InputLayout = CreateInputLayout(fxBlob, &pass.EffectVsDesc, pass.SignatureDescs);
			pass.StateBlock = InitialStateBlock;

			technique.Passes.push_back(pass);
		}

		Techniques.push_back(technique);
	}

	for (UINT i = 0; i < EffectDesc.ConstantBuffers; i++)
	{
		ID3DX11EffectConstantBuffer* iBuffer;
		iBuffer = Effect->GetConstantBufferByIndex(i);

		D3DX11_EFFECT_VARIABLE_DESC vDesc;
		iBuffer->GetDesc(&vDesc);
	}

	for (UINT i = 0; i < EffectDesc.GlobalVariables; i++)
	{
		ID3DX11EffectVariable* iVariable;
		iVariable = Effect->GetVariableByIndex(i);

		D3DX11_EFFECT_VARIABLE_DESC vDesc;
		iVariable->GetDesc(&vDesc);
	}

	Release(fxBlob);
}

ID3D11InputLayout* CShader::CreateInputLayout(ID3DBlob* InBlob, D3DX11_EFFECT_SHADER_DESC* InDesc, vector<D3D11_SIGNATURE_PARAMETER_DESC>& InParams)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (D3D11_SIGNATURE_PARAMETER_DESC& paramDesc : InParams)
	{
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		string name = paramDesc.SemanticName;
		transform(name.begin(), name.end(), name.begin(), toupper);

		if (name == "POSITION")
			elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;


		if ((name.substr(0, 3) == "SV_") == false)
			inputLayoutDesc.push_back(elementDesc);
	}


	const void* pCode = InDesc->pBytecode;
	UINT pCodeSize = InDesc->BytecodeLength;

	if (inputLayoutDesc.size() > 0)
	{
		ID3D11InputLayout* inputLayout = nullptr;
		HRESULT hr = CD3D::Get()->GetDevice()->CreateInputLayout
		(
			&inputLayoutDesc[0]
			, inputLayoutDesc.size()
			, pCode
			, pCodeSize
			, &inputLayout
		);
		Check(hr);

		return inputLayout;
	}

	return nullptr;
}

void CShader::SetTechniqueByName(string InName)
{
	auto iter = TechniqueNameMap.find(InName);
	assert(iter != TechniqueNameMap.end());

	SetTechniqueNumber(iter->second);
}

void CShader::FPass::Draw(UINT InVertexCount, UINT IntartVertexLocation)
{
	BeginDraw();
	{
		CD3D::Get()->GetDeviceContext()->Draw(InVertexCount, IntartVertexLocation);
	}
	EndDraw();
}

void CShader::FPass::DrawIndexed(UINT InIndexCount, UINT InStartIndexLocation, int InBaseVertexLocation)
{
	BeginDraw();
	{
		CD3D::Get()->GetDeviceContext()->DrawIndexed(InIndexCount, InStartIndexLocation, InBaseVertexLocation);
	}
	EndDraw();
}

void CShader::FPass::DrawInstanced(UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation, UINT startInstanceLocation)
{
	BeginDraw();
	{
		CD3D::Get()->GetDeviceContext()->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation);
	}
	EndDraw();
}

void CShader::FPass::DrawIndexedInstanced(UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation)
{
	BeginDraw();
	{
		CD3D::Get()->GetDeviceContext()->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startIndexLocation);
	}
	EndDraw();
}

void CShader::FPass::BeginDraw()
{
	IPass->ComputeStateBlockMask(&StateBlockMask);

	CD3D::Get()->GetDeviceContext()->IASetInputLayout(InputLayout);
	IPass->Apply(0, CD3D::Get()->GetDeviceContext());
}

void CShader::FPass::EndDraw()
{
	if (StateBlockMask.RSRasterizerState == 1)
		CD3D::Get()->GetDeviceContext()->RSSetState(StateBlock->RSRasterizerState);

	if (StateBlockMask.OMDepthStencilState == 1)
		CD3D::Get()->GetDeviceContext()->OMSetDepthStencilState(StateBlock->OMDepthStencilState, StateBlock->OMStencilRef);

	if (StateBlockMask.OMBlendState == 1)
		CD3D::Get()->GetDeviceContext()->OMSetBlendState(StateBlock->OMBlendState, StateBlock->OMBlendFactor, StateBlock->OMSampleMask);

	CD3D::Get()->GetDeviceContext()->HSSetShader(nullptr, nullptr, 0);
	CD3D::Get()->GetDeviceContext()->DSSetShader(nullptr, nullptr, 0);
	CD3D::Get()->GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);
}

void CShader::FPass::Dispatch(UINT InX, UINT InY, UINT InZ)
{
	IPass->Apply(0, CD3D::Get()->GetDeviceContext());
	CD3D::Get()->GetDeviceContext()->Dispatch(InX, InY, InZ);


	ID3D11ShaderResourceView* null[1] = { 0 };
	CD3D::Get()->GetDeviceContext()->CSSetShaderResources(0, 1, null);

	ID3D11UnorderedAccessView* nullUav[1] = { 0 };
	CD3D::Get()->GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, nullUav, nullptr);

	CD3D::Get()->GetDeviceContext()->CSSetShader(nullptr, nullptr, 0);
}

void CShader::Draw(UINT InVertexCount, UINT InStartVertexLocation)
{
	Techniques[TechniqueNumber].Passes[PassNumber].Draw(InVertexCount, InStartVertexLocation);
}

void CShader::DrawIndexed(UINT InIndexCount, UINT InStartIndexLocation, int InBaseVertexLocation)
{
	Techniques[TechniqueNumber].Passes[PassNumber].DrawIndexed(InIndexCount, InStartIndexLocation, InBaseVertexLocation);
}

void CShader::DrawInstanced(UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation, UINT startInstanceLocation)
{
	Techniques[TechniqueNumber].Passes[PassNumber].DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation);
}

void CShader::DrawIndexedInstanced(UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation)
{
	Techniques[TechniqueNumber].Passes[PassNumber].DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
}

void CShader::Dispatch(UINT InTechnique, UINT InPass, UINT InX, UINT InY, UINT InZ)
{
	Techniques[TechniqueNumber].Passes[PassNumber].Dispatch(InX, InY, InZ);
}

ID3DX11EffectVariable* CShader::Variable(string InName)
{
	return Effect->GetVariableByName(InName.c_str());
}

ID3DX11EffectScalarVariable* CShader::AsScalar(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsScalar();
}

ID3DX11EffectVectorVariable* CShader::AsVector(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsVector();
}

ID3DX11EffectMatrixVariable* CShader::AsMatrix(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsMatrix();
}

ID3DX11EffectStringVariable* CShader::AsString(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsString();
}

ID3DX11EffectShaderResourceVariable* CShader::AsSRV(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsShaderResource();
}

ID3DX11EffectRenderTargetViewVariable* CShader::AsRTV(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsRenderTargetView();
}

ID3DX11EffectDepthStencilViewVariable* CShader::AsDSV(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsDepthStencilView();
}

ID3DX11EffectConstantBuffer* CShader::AsConstantBuffer(string InName)
{
	return Effect->GetConstantBufferByName(InName.c_str());
}

ID3DX11EffectShaderVariable* CShader::AsShader(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsShader();
}

ID3DX11EffectBlendVariable* CShader::AsBlend(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsBlend();
}

ID3DX11EffectDepthStencilVariable* CShader::AsDepthStencil(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsDepthStencil();
}

ID3DX11EffectRasterizerVariable* CShader::AsRasterizer(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsRasterizer();
}

ID3DX11EffectSamplerVariable* CShader::AsSampler(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsSampler();
}

ID3DX11EffectUnorderedAccessViewVariable* CShader::AsUAV(string InName)
{
	return Effect->GetVariableByName(InName.c_str())->AsUnorderedAccessView();
}

