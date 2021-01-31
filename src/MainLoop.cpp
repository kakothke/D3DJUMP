#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"
#include "Define.h"
#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
MainLoop::MainLoop()
{
	Mesh::getInst()->initialize();
	Mesh::getInst()->load(MeshList::TestMan);
}

//-------------------------------------------------------------------------------------------------
/// アプリケーションのメインループ
/// @return falseを返すとメインループを抜けてアプリケーションが終了する
bool MainLoop::loop()
{
	update();
	draw();
	return true;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void MainLoop::update()
{
	mCamera.SetupWorldMatrix();
	mLight.update();
	TestMan.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void MainLoop::draw() const
{
	// Zバッファとバックバッファをクリア
	Direct3D9::getInst()->device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Define::ClearColor, 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(Direct3D9::getInst()->device()->BeginScene())) {
		// テストメッシュを描画
		mLight.draw();
		TestMan.draw();

		// 描画終了
		Direct3D9::getInst()->device()->EndScene();
	}

	// バックバッファを表画面に描画
	Direct3D9::getInst()->device()->Present(NULL, NULL, NULL, NULL);
}

} // namespace
// EOF
