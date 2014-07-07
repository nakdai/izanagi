// Phong Shader

#define USE_REFLECTION

struct SVSInput {
    float4 vPos     : POSITION;
    float3 vNormal  : NORMAL;
    float4 vColor   : COLOR;
};

struct SPSInput {
    float4 vPos     : POSITION;
    float3 vNormal  : TEXCOORD0;    // 法線
    float3 vHalf    : TEXCOORD1;    // ハーフベクトル
    float4 ambient  : COLOR0;
};

#define SVSOutput        SPSInput

struct SPSOutput {
    float4 ambient  : COLOR0;
    float4 diffspec : COLOR1;
};

/////////////////////////////////////////////////////////////

float4x4 g_mL2W;
float4x4 g_mW2C;
float4 g_vEye;

// マテリアル
float4 g_vMtrlDiffuse;
float4 g_vMtrlAmbient;
float4 g_vMtrlSpecular;

// ライト
float4 g_vLitParallelDir;
float4 g_vLitParallelColor;
float4 g_vLitAmbientColor;

/////////////////////////////////////////////////////////////

SVSOutput mainVS(SVSInput In)
{
    SVSOutput Out = (SVSOutput)0;

    // 視点への方向ベクトル（ローカル座標）
    float3 vV = normalize(g_vEye - In.vPos).xyz;
    
    Out.vPos = mul(In.vPos, g_mL2W);
    Out.vPos = mul(Out.vPos, g_mW2C);
    
    Out.vNormal = normalize(In.vNormal);

    // Ambient
    Out.ambient = g_vMtrlAmbient * g_vLitAmbientColor;

    // NOTE
    // ローカル座標での計算なので
    // ライトの方向ベクトルはCPU側でローカル座標に変換されていること

    Out.vHalf = normalize(-g_vLitParallelDir.xyz + vV);
    
    return Out;
}

SPSOutput mainPS(SPSInput In)
{
    // 頂点シェーダでAmbientについては計算済み
    SPSOutput vOut = (SPSOutput)0;

    vOut.ambient = In.ambient;
    vOut.ambient.a = 1.0f;
    
    // いるのか・・・
    float3 vN = normalize(In.vNormal);
    float3 vH = normalize(In.vHalf);
    float3 vL = -g_vLitParallelDir.xyz;
    
    // Diffuse = Md * ��(C * max(N・L, 0))
    vOut.diffspec.rgb += g_vMtrlDiffuse.rgb * g_vLitParallelColor.rgb * max(0.0f, dot(vN, vL));
    
    // Specular = Ms * ��(C * pow(max(N・H, 0), m))
    vOut.diffspec.rgb += g_vMtrlSpecular.rgb * g_vLitParallelColor.rgb * pow(max(0.0f, dot(vN, vH)), max(g_vMtrlSpecular.w, 0.00001f));

    vOut.diffspec.a = 1.0f;
    
    return vOut;
}

/////////////////////////////////////////////////////////////

technique Phong
{
    pass P0
    {
        VertexShader = compile vs_3_0 mainVS();
        PixelShader = compile ps_3_0 mainPS();
    }
}
