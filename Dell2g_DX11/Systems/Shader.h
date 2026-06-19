#pragma once
#include <vector>
#include <map>
#include <algorithm>

class CShader
{
public:
	CShader(wstring InFile);
	~CShader();

public:
	void Draw(UINT InVertexCount, UINT IntartVertexLocation = 0);
	void DrawIndexed(UINT InIndexCount, UINT InStartIndexLocation = 0, int InBaseVertexLocation = 0);
	void DrawInstanced(UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation = 0, UINT startInstanceLocation = 0);
	void DrawIndexedInstanced(UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation = 0, INT baseVertexLocation = 0, UINT startInstanceLocation = 0);

	void Dispatch(UINT InTechnique, UINT InPass, UINT InX, UINT InY, UINT InZ);


	ID3DX11EffectVariable* Variable(string InName);
	ID3DX11EffectScalarVariable* AsScalar(string InName);
	ID3DX11EffectVectorVariable* AsVector(string InName);
	ID3DX11EffectMatrixVariable* AsMatrix(string InName);
	ID3DX11EffectStringVariable* AsString(string InName);
	ID3DX11EffectShaderResourceVariable* AsSRV(string InName);
	ID3DX11EffectRenderTargetViewVariable* AsRTV(string InName);
	ID3DX11EffectDepthStencilViewVariable* AsDSV(string InName);
	ID3DX11EffectUnorderedAccessViewVariable* AsUAV(string InName);
	ID3DX11EffectConstantBuffer* AsConstantBuffer(string InName);
	ID3DX11EffectShaderVariable* AsShader(string InName);
	ID3DX11EffectBlendVariable* AsBlend(string InName);
	ID3DX11EffectDepthStencilVariable* AsDepthStencil(string InName);
	ID3DX11EffectRasterizerVariable* AsRasterizer(string InName);
	ID3DX11EffectSamplerVariable* AsSampler(string InName);

public:
	UINT GetTechniqueNumber() { return TechniqueNumber; }
	UINT GetPassNumber() { return PassNumber; }

	void SetTechniqueByName(string InName);
	void SetTechniqueNumber(UINT InNumber) { TechniqueNumber = InNumber; }
	void SetPassNumber(UINT InNumber) { PassNumber = InNumber; }

	UINT GetTechniqueCount() { return Techniques.size(); }
	UINT GetPassCount(UINT InTechnique = 0) { return Techniques[InTechnique].Passes.size(); }

private:
	UINT TechniqueNumber = 0;
	UINT PassNumber = 0;

private:
	void CreateEffect();
	ID3D11InputLayout* CreateInputLayout(ID3DBlob* InBlob, D3DX11_EFFECT_SHADER_DESC* InDesc, vector<D3D11_SIGNATURE_PARAMETER_DESC>& InParams);

private:
	wstring File;

	ID3DX11Effect* Effect;
	D3DX11_EFFECT_DESC EffectDesc;

private:
	struct FStateBlock
	{
		ID3D11RasterizerState* RSRasterizerState;

		ID3D11BlendState* OMBlendState;
		FLOAT OMBlendFactor[4];
		UINT OMSampleMask;
		ID3D11DepthStencilState* OMDepthStencilState;
		UINT OMStencilRef;
	};
	FStateBlock* InitialStateBlock;

private:
	struct FPass
	{
		wstring Name;
		ID3DX11EffectPass* IPass;
		D3DX11_PASS_DESC Desc;

		ID3D11InputLayout* InputLayout;
		D3DX11_PASS_SHADER_DESC PassVsDesc;
		D3DX11_EFFECT_SHADER_DESC EffectVsDesc;
		vector<D3D11_SIGNATURE_PARAMETER_DESC> SignatureDescs;

		D3DX11_STATE_BLOCK_MASK StateBlockMask;
		FStateBlock* StateBlock;

		void Draw(UINT InVertexCount, UINT InStartVertexLocation = 0);
		void DrawIndexed(UINT InIndexCount, UINT InStartIndexLocation = 0, int InBaseVertexLocation = 0);
		void DrawInstanced(UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation = 0, UINT startInstanceLocation = 0);
		void DrawIndexedInstanced(UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation = 0, INT baseVertexLocation = 0, UINT startInstanceLocation = 0);

		void BeginDraw();
		void EndDraw();

		void Dispatch(UINT InX, UINT InY, UINT InZ);
	};

	struct FTechnique
	{
		string Name;
		D3DX11_TECHNIQUE_DESC Desc;
		ID3DX11EffectTechnique* ITechnique;

		vector<FPass> Passes;
	};
	vector<FTechnique> Techniques;
	map<string, UINT> TechniqueNameMap;
};

