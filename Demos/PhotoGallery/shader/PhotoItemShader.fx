// Basic Shader

struct SVSInput {
    float4 vPos     : POSITION;
    float2 vUV      : TEXCOORD0;
    float4 vColor   : COLOR;
};

struct SPSInput {
    float4 vPos     : POSITION;
    float2 vUV      : TEXCOORD2;
    float4 vColor   : COLOR;
};

#define SVSOutput        SPSInput

struct SVSInput_NoTex {
    float4 vPos        : POSITION;
    float4 vColor    : COLOR;
};

struct SPSInput_NoTex {
    float4 vPos        : POSITION;
    float4 vColor    : COLOR;
};

#define SVSOutput_NoTex    SPSInput_NoTex

/////////////////////////////////////////////////////////////

float4x4 g_mL2W;
float4x4 g_mW2C;

texture tex;

sampler sTex = sampler_state
{
    Texture = tex;
};

// x : scale x
// y : scale y
// z : height factor
// w : alpha factor
float4 g_Params;

/////////////////////////////////////////////////////////////

SVSOutput mainVS(SVSInput In)
{
    SVSOutput Out = (SVSOutput)0;

    float4 pos = In.vPos;
    pos.xy *= g_Params.xy;

    pos.y += g_Params.z;

    Out.vPos = mul(pos, g_mL2W);
    Out.vPos = mul(Out.vPos, g_mW2C);

    Out.vUV = In.vUV;

    Out.vColor = In.vColor;
    Out.vColor.a *= g_Params.a;
    
    return Out;
}

float4 mainPS(SPSInput In) : COLOR
{
    float4 vOut = tex2D(sTex, In.vUV);

    vOut.rgb *= In.vColor.rgb;
    vOut.a *= In.vColor.a;

    return vOut;
}

////////////////////////////////////////////////

SVSOutput_NoTex mainVS_NoTex(SVSInput_NoTex In)
{
    SVSOutput_NoTex Out = (SVSOutput_NoTex)0;

    float4 pos = In.vPos;
    pos.xy *= g_Params.xy;

    pos.y += g_Params.z;

    Out.vPos = mul(pos, g_mL2W);
    Out.vPos = mul(Out.vPos, g_mW2C);

    Out.vColor = In.vColor;
    Out.vColor.a *= g_Params.a;

    return Out;
}

float4 mainPS_NoTex(SPSInput_NoTex In)    : COLOR
{
    float4 vOut = In.vColor;

    return vOut;
}

/////////////////////////////////////////////////////////////

technique PhotoItemShader
{
    pass P0
    {
        VertexShader = compile vs_2_0 mainVS();
        PixelShader = compile ps_2_0 mainPS();
    }
}

technique PhotoItemShader_NoTex
{
    pass P0
    {
        VertexShader = compile vs_2_0 mainVS_NoTex();
        PixelShader = compile ps_2_0 mainPS_NoTex();
    }
}
