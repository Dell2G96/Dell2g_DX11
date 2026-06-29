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
    float3 oPosition : Position1; 
    float2 Uv : Uv;
    float3 Normal : Normal;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    
    output.oPosition = input.Position.xyz;
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
float MaxHeight;
float LowRatio;
float HighRatio;

float4 GetWeights(float height)
{
    float low = MaxHeight * LowRatio;
    float high = MaxHeight * HighRatio;
    
    float4 weights = 0;
    if(height < low)
    {
        weights.y = height / low;
        weights.x = 1.0f - weights.y;
    }
    else if(height < high)
    {
        weights.z = (height - low) / (high - low);
        weights.y = 1.0f - weights.z;
    }
    else
    {
        weights.w = (height - high) / (MaxHeight - high);
        weights.z = 1.0f - weights.w;
    }
    
    return weights;
}

///////////////////////////////////////////////////////////////////////////////
float GentleAngle;
float SteepAngle;

float GetSlopeFactor(float normalY)
{
    if(normalY < GentleAngle)
        return 0.0f;
        
    else if ( normalY < SteepAngle)
        return (normalY - GentleAngle) / (SteepAngle - GentleAngle);
        
    return 1.0f;
}
///////////////////////////////////////////////////////////////////////////////
float2 Tiling;
float3 LightDirection = float3(1.f, 0.0f, 0.0f);

Texture2D Maps[5];
float4 PS(VertexOutput input) : SV_Target
{
    float4 weights = GetWeights(input.oPosition.y);
    //return weights;
    
    float4 colors[4];
    for(int i = 0; i < 4; i++)
        colors[i] = Maps[i].Sample(LinearSampler, input.Uv * Tiling) * weights[i];
    
    //return colors[0];
    
    float4 color = colors[0] + colors[1] + colors[2] + colors[3];
    //return color;
    
    float3 normal = normalize(input.Normal);
    float slope = GetSlopeFactor(normal.y);
    // return float4(slope, 0,0,1);
    
    float4 slopeColor = Maps[4].Sample(LinearSampler, input.Uv * Tiling);
    //return lerp(slopeColor, color, slope);
    
    float NdotL = dot(normal, -LightDirection);
    return lerp(slopeColor, color, slope) * NdotL;
}

technique11 T_Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}
























