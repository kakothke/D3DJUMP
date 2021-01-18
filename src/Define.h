#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// ��`
class Define
{
public:
    /// @name �E�B���h�E�ݒ�
    //@{
    /// �E�B���h�E�T�C�Y��
    const static int WindowWidth = 1280;
    /// �E�B���h�E�T�C�Y�c
    const static int WindowHeight = 720;
    /// �E�B���h�E��
    const static LPCWSTR WindowName;
    //@}

    /// @name DirectX�ݒ�
    //@{
    /// �t���X�N���[��
    const static bool FullScreenMode = false;
    /// ��ʃN���A�F
    const static D3DCOLOR ClearColor;
    //@}

    /// @name �Q�[���ݒ�
    //@{
    /// �Œ肷��fps
    const static int Fps = 60;
    //@}

};

} // namespace
// EOF
