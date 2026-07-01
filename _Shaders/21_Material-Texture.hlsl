cbuffer CB_Frame : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

struct MaterialDesc
{
    float4 Diffuse;
    float2 Tiling;
    float HasDiffuseMap;
    float Padding;
};

cbuffer CB_Material : register(b1)
{
    MaterialDesc MaterialData;
};

cbuffer CB_Light : register(b2)
{
    float3 LightDirection;
    float LightPadding;
};

Texture2D DiffuseMap : register(t0);
SamplerState LinearSampler : register(s0);

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

    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.Uv = input.Uv;
    output.Normal = mul(input.Normal, (float3x3)World);

    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    float3 normal = normalize(input.Normal);
    float NdotL = saturate(dot(normal, -LightDirection));

    float4 diffuseMap = float4(1.0f, 1.0f, 1.0f, 1.0f);
    if (MaterialData.HasDiffuseMap > 0.5f)
        diffuseMap = DiffuseMap.Sample(LinearSampler, input.Uv * MaterialData.Tiling);

    return MaterialData.Diffuse * diffuseMap * NdotL;
}
