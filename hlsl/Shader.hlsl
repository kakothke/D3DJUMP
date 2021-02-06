//-------------------------------------------------------------------------------------------------
/// 合成用マトリクス
float4x4 gMatrix;
/// カラー情報
float4 gColor;

//-------------------------------------------------------------------------------------------------
/// 頂点シェーダ
void VertexShaderFunction(float3 inPos : POSITION, out float4 outPos : POSITION, out float4 outColor : COLOR0)
{
	// 座標変換(ローカル座標と掛け合わせ)
    outPos = mul(float4(inPos, 1.0f), gMatrix);

	// 頂点の色の決定(そのまま使用)
    outColor = gColor;
}

//-------------------------------------------------------------------------------------------------
/// ピクセルシェーダ
void PixelShaderFunction(float4 inColor : COLOR0, out float4 outColor : COLOR0)
{
	// 色をそのまま使用
    outColor = inColor;
}

//-------------------------------------------------------------------------------------------------
/// テクニック宣言
technique StandardDraw
{
    pass normal
    {
        vertexShader = compile vs_3_0 VertexShaderFunction();
        pixelShader = compile ps_3_0 PixelShaderFunction();
    }
}

// EOF
