cbuffer CB_World : register(b0)
{
    matrix World;
};

cbuffer CB_ViewProjection : register(b1)
{
    matrix View;
    matrix Projection;
};

cbuffer CB_Color : register(b2)
{
    float4 Color0;
    float4 Color1;
};

cbuffer CB_Tiling : register(b3)
{
    float2 Tiling;
    float2 TilingPadding;
};

SamplerState LinearSampler : register(s0);
Texture2D Maps[4] : register(t0);

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

float4 PS_Lerp(VertexOutput input) : SV_Target
{
    return lerp(Color0, Color1, input.Uv.x);
}

float4 PS_SmoothStep(VertexOutput input) : SV_Target
{
    return lerp(Color0, Color1, smoothstep(0, 1, input.Uv.x));
}

float4 PS_Step(VertexOutput input) : SV_Target
{
    return lerp(Color0, Color1, step(input.Uv.x, 0.75));
}

float4 PS_Lerp_UV(VertexOutput input) : SV_Target
{
    float4 color0 = Maps[0].Sample(LinearSampler, input.Uv);
    float4 color1 = Maps[1].Sample(LinearSampler, input.Uv);

    return lerp(color0, color1, input.Uv.x);
}

float4 PS_Lerp_UV2(VertexOutput input) : SV_Target
{
    float4 color0 = Maps[0].Sample(LinearSampler, input.Uv);
    float4 color1 = Maps[1].Sample(LinearSampler, input.Uv);
    float4 factor = Maps[2].Sample(LinearSampler, input.Uv);

    return lerp(color0, color1, factor);
}

float4 PS_Lerp_Tiling(VertexOutput input) : SV_Target
{
    float4 color0 = Maps[0].Sample(LinearSampler, input.Uv);
    float4 color1 = Maps[1].Sample(LinearSampler, input.Uv);
    float4 factor = Maps[3].Sample(LinearSampler, input.Uv * Tiling);

    return lerp(color0, color1, factor);
}
