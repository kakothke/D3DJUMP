#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"
#include "SceneManager.h"

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
	/// シーン管理
	SceneManager mSceneManager;
	//@}

};

} // namespace
// EOF
