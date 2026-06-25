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

float4 Color0;
float4 Color1;

float4 PS_Lerp(VertexOutput input) : SV_Target
{
    return lerp(Color0, Color1, input.Uv.x);
}

float4 PS_SmoothStep(VertexOutput input) : SV_Target
{
    return lerp(Color0, Color1, smoothstep(0, 1,input.Uv.x ));
}

float4 PS_Step(VertexOutput input) : SV_Target
{
    return lerp(Color0, Color1, step(input.Uv.x, 0.75));
}

technique11 T_Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Lerp()));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_SmoothStep()));
    }

    pass P2
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Step()));
    }
}

///////////////////////////////////////////////////////////////////////////////

SamplerState LinearSampler
{
    AddressU = Wrap;
    AddressV = Wrap;

    Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D Maps[4];

float4 PS_Lerp_UV(VertexOutput input) :SV_Target
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

float2 Tiling;
float4 PS_Lerp_Tiling(VertexOutput input) : SV_Target
{
    float4 color0 = Maps[0].Sample(LinearSampler, input.Uv);
    float4 color1 = Maps[1].Sample(LinearSampler, input.Uv);
    float4 factor = Maps[3].Sample(LinearSampler, input.Uv * Tiling);
    
    return lerp(color0, color1, factor);
}

technique11 T_Render2
{
     pass P0
     {
         SetVertexShader(CompileShader(vs_5_0, VS()));
         SetPixelShader(CompileShader(ps_5_0, PS_Lerp_UV()));
     }
    
     pass P1
     {
         SetVertexShader(CompileShader(vs_5_0, VS()));
         SetPixelShader(CompileShader(ps_5_0, PS_Lerp_UV2()));
     }
    
     pass P2
     {
         SetVertexShader(CompileShader(vs_5_0, VS()));
         SetPixelShader(CompileShader(ps_5_0, PS_Lerp_Tiling()));
     }
}





















