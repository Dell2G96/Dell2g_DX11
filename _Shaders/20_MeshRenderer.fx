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


float3 LightDirection = float3(1.f, 0.0f, 0.0f);
float4 PS(VertexOutput input) : SV_Target
{
    float3 normal = normalize(input.Normal);
    float NdotL = dot(normal, -LightDirection);
    
    return float4(1,1,1,1) * NdotL;
}

technique11 T_Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}
























