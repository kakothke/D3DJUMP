#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <list>

#pragma comment(lib,"winmm.lib")

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// fpsを制御する
class Fps
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Fps();
	~Fps();
	//@}

	/// fpsを調整する
	void adjust();
	/// 現在のfpsを描画する
	void draw() const;

private:
	/// name プライベートメンバ変数
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
