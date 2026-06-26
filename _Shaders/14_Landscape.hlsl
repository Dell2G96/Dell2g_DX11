cbuffer CB_World : register(b0)
{
    matrix World;
};

cbuffer CB_ViewProjection : register(b1)
{
    matrix View;
    matrix Projection;
};

cbuffer CB_Tiling : register(b2)
{
    float2 Tiling;
    float2 TilingPadding;
};

Texture2D Map : register(t0);
SamplerState LinearSampler : register(s0);

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

float4 PS(VertexOutput input) : SV_Target
{
    return Map.Sample(LinearSampler, input.Uv * Tiling);
}
