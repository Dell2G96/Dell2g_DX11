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

///////////////////////////////////////////////////////////////////////////////
Texture2D Map;
SamplerState Sampler;

uint Address;

SamplerState Sampler_Wrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState Sampler_Mirror
{
    AddressU = Mirror;
    AddressV = Mirror;
};

SamplerState Sampler_Clamp
{
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState Sampler_Border
{
    AddressU = Border;
    AddressV = Border;
    
    BorderColor = float4(0,0,1,1);
};

float4 PS_Address(VertexOutput input) : SV_Target
{
    if(Address == 0)
    return Map.Sample(Sampler_Wrap, input.Uv);
    
     if (Address == 1)
         return Map.Sample(Sampler_Mirror, input.Uv);
     
     if (Address == 2)
         return Map.Sample(Sampler_Border, input.Uv);
     
     if (Address == 3)
         return Map.Sample(Sampler_Clamp, input.Uv);
     
     return Map.Sample(Sampler, input.Uv);
} 

///////////////////////////////////////////////////////////////////////////////
uint Filter;

SamplerState Sampler_Point
{
    AddressU = Wrap;
    AddressV = Wrap;

    Filter = MIN_MAG_MIP_POINT;
};

SamplerState Sampler_Linear
{
    AddressU = Wrap;
    AddressV = Wrap;

    Filter = MIN_MAG_MIP_LINEAR;
};

float4 PS_Filter(VertexOutput input) : SV_Target
{
      if (Filter == 0)
          return Map.Sample(Sampler_Point, input.Uv);
      
      if (Filter == 1)
          return Map.Sample(Sampler_Linear, input.Uv);
      
      return Map.Sample(Sampler, input.Uv);
}

technique11 T_Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Address()));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Filter()));
    }
}







