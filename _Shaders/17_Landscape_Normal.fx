matrix World;
matrix View;
matrix Projection;

struct VertexInput
{
    float4 Position : Position; 
    float2 Uv : Uv;
    float3 Normal : Normal;
};

struct VertexOutput
{
    float4 Position : SV_Position; 
    float2 Uv : Uv;
    float3 Normal : Normal;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position,World);
    output.Position = mul(output.Position,View);
    output.Position = mul(output.Position,Projection);
    
    output.Normal = mul(input.Normal, (float3x3) World);
    
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
float3 LightDirection = float3(1.f, 0.0f, 0.0f);
float4 PS(VertexOutput input) : SV_Target
{
    float3 normal = normalize(input.Normal);
    float NdotL = dot(normal, -LightDirection);
    
    return Map.Sample(LinearSampler, input.Uv * Tiling) * NdotL;
}

technique11 T_Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}
























