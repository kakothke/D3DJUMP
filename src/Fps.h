#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <list>

#pragma comment(lib,"winmm.lib")

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// fps�𐧌䂷��
class Fps
{
public:
	/// @name �R���X�g���N�^
	//@{
	Fps();
	//@}

	/// fps�𒲐�����
	void adjust();
	/// ���݂�fps��`�悷��
	void draw() const;

private:
	/// name �v���C�x�[�g�����o�ϐ�
	//@{
	LARGE_INTEGER mTimeStart;
	LARGE_INTEGER mTimeEnd;
	LARGE_INTEGER mTimeFreq;
	const float mMinFrameTime;
	float mFps = 0;
	float mFrameTime = 0;
	//@}

};

} // namespace
// EOF
