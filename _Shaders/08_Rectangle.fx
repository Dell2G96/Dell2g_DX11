struct VertexInput
{
    float4 Position : Position;
};

struct VertexOutput
{
    float4 Position : SV_Position;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = input.Position;

    return output;
}

float4 PS_Red(VertexOutput input) : SV_Target
{
    return float4(1, 0, 0, 1);
}

float4 PS_Green(VertexOutput input) : SV_Target
{
    return float4(0, 1, 0, 1);
}

float4 PS_Blue(VertexOutput input) : SV_Target
{
    return float4(0, 0, 1, 1);
}

float4 PS_White(VertexOutput input) : SV_Target
{
    return float4(1, 1, 1, 1);
}

float4 Color;
float4 PS_Color(VertexOutput input) : SV_Target
{
    return Color;
}

technique11 T_Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Red()));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Green()));
    }

    pass P2
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Blue()));
    }

    pass P3
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_White()));
    }

    pass P4
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Color()));
    }
}


RasterizerState FillMode_Wireframe
{
    FillMode = Wireframe;
};

technique11 T_Render_Wireframe
{
    pass P0
    {
        SetRasterizerState(FillMode_Wireframe);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Red()));
    }

    pass P1
    {
        SetRasterizerState(FillMode_Wireframe);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Green()));
    }

    pass P2
    {
        SetRasterizerState(FillMode_Wireframe);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Blue()));
    }

    pass P3
    {
        SetRasterizerState(FillMode_Wireframe);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_White()));
    }

    pass P4
    {
        SetRasterizerState(FillMode_Wireframe);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Color()));
    }
}