#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"
#include "SceneManager.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ゲーム全体
class Game
{
public:
	/// @name コンストラクタ
	//@{
	Game();
	//@}

	/// @name ゲームのメインループ
	//@{
	bool mainLoop();
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	SceneManager mSceneManager;
	Fps mFps;
	//@}

};

} // namespace
// EOF
