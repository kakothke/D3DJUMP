#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
// テスト用
#include "TestMan.h"
#include "Camera.h"
#include "Light.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// メインループ
class MainLoop
{
public:
	/// @name コンストラクタ
	//@{
	MainLoop();
	//@}

	/// @name ゲームのメインループ
	//@{
	bool loop();
	//@}

private:
	/// @name テスト用	
	//@{
	void update();
	void draw() const;
	TestMan TestMan;
	Camera mCamera;
	Light mLight;
	//@}

};

} // namespace
// EOF
