matrix World;
matrix View;
matrix Projection;

struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Uv = input.Uv;
    
    return output;
}
///////////////////////////////////////////////////////////////////////////////
SamplerState LinearSampler
{
    AddressU = Wrap;
    AddressV = Wrap;
    
    Filter = MIN_MAG_MIP_LINEAR;
};
///////////////////////////////////////////////////////////////////////////////

Texture2D Map;
float2 Tiling;
float4 PS(VertexOutput input) : SV_Target
{
    return Map.Sample(LinearSampler, input.Uv * Tiling);
}

technique11 T_Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}
















