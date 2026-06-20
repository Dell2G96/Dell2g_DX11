struct VertexInput
{
    float4 Position : Position;
    uint VertexID : SV_VertexID;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float4 Color : Color;
};


VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = input.Position;
    
    if(input.VertexID ==0)
    output.Color = float4(1,0,0,1);
    if(input.VertexID ==1)
        output.Color = float4(0,0,1,1);
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    return input.Color;
}

technique11 T_Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}
