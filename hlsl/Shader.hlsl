//-------------------------------------------------------------------------------------------------
/// �����p�}�g���N�X
float4x4 gMatrix;
/// �J���[���
float4 gColor;

//-------------------------------------------------------------------------------------------------
/// ���_�V�F�[�_
void VertexShaderFunction(float3 inPos : POSITION, out float4 outPos : POSITION, out float4 outColor : COLOR0)
{
	// ���W�ϊ�(���[�J�����W�Ɗ|�����킹)
    outPos = mul(float4(inPos, 1.0f), gMatrix);

	// ���_�̐F�̌���(���̂܂܎g�p)
    outColor = gColor;
}

//-------------------------------------------------------------------------------------------------
/// �s�N�Z���V�F�[�_
void PixelShaderFunction(float4 inColor : COLOR0, out float4 outColor : COLOR0)
{
	// �F�����̂܂܎g�p
    outColor = inColor;
}

//-------------------------------------------------------------------------------------------------
/// �e�N�j�b�N�錾
technique StandardDraw
{
    pass normal
    {
        vertexShader = compile vs_3_0 VertexShaderFunction();
        pixelShader = compile ps_3_0 PixelShaderFunction();
    }
}

// EOF
