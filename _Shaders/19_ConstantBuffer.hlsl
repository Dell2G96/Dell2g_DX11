cbuffer CB_Frame : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

struct LandscapeDesc
{
    float3 LightDirection;
    float MaxHeight;

    float LowRatio;
    float HighRatio;
    float GentleAngle;
    float SteepAngle;

    float2 Tiling;
    float2 Padding;
};

cbuffer CB_Landscape : register(b1)
{
    LandscapeDesc LandscapeData;
};

Texture2D Maps[5] : register(t0);
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
    float3 oPosition : Position1;
    float2 Uv : Uv;
    float3 Normal : Normal;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    output.oPosition = input.Position.xyz;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.Normal = mul(input.Normal, (float3x3)World);
    output.Uv = input.Uv;

    return output;
}

float4 GetWeights(float height)
{
    float low = LandscapeData.MaxHeight * LandscapeData.LowRatio;
    float high = LandscapeData.MaxHeight * LandscapeData.HighRatio;

    float4 weights = 0;
    if (height < low)
    {
        weights.y = height / low;
        weights.x = 1.0f - weights.y;
    }
    else if (height < high)
    {
        weights.z = (height - low) / (high - low);
        weights.y = 1.0f - weights.z;
    }
    else
    {
        weights.w = (height - high) / (LandscapeData.MaxHeight - high);
        weights.z = 1.0f - weights.w;
    }

    return weights;
}

float GetSlopeFactor(float normalY)
{
    if (normalY < LandscapeData.GentleAngle)
        return 0.0f;

    if (normalY < LandscapeData.SteepAngle)
        return (normalY - LandscapeData.GentleAngle) / (LandscapeData.SteepAngle - LandscapeData.GentleAngle);

    return 1.0f;
}

float4 PS(VertexOutput input) : SV_Target
{
    float4 weights = GetWeights(input.oPosition.y);

    float4 colors[4];
    [unroll]
    for (int i = 0; i < 4; i++)
        colors[i] = Maps[i].Sample(LinearSampler, input.Uv * LandscapeData.Tiling) * weights[i];

    float4 color = colors[0] + colors[1] + colors[2] + colors[3];

    float3 normal = normalize(input.Normal);
    float slope = GetSlopeFactor(normal.y);
    float4 slopeColor = Maps[4].Sample(LinearSampler, input.Uv * LandscapeData.Tiling);

    float NdotL = dot(normal, -LandscapeData.LightDirection);

    return lerp(slopeColor, color, slope) * NdotL;
}
