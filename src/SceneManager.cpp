#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SceneManager::SceneManager()
{
	// �e�X�g�V�[�����v�b�V��
	mSceneStack.push(std::make_shared<TestScene>(this));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
SceneManager::~SceneManager()
{
	// �X�^�b�N��S���|�b�v����(�X�^�b�N����ɂ���)
	while (!mSceneStack.empty()) {
		mSceneStack.pop();
	}
}

//-------------------------------------------------------------------------------------------------
/// ����
void SceneManager::run() const
{
	Direct3D9::getInst()->drawStart();

	if (!mSceneStack.empty()) {
		mSceneStack.top()->update();
		mSceneStack.top()->draw();
	}

	Direct3D9::getInst()->drawEnd();
}

//-------------------------------------------------------------------------------------------------
/// �V�[���J��
/// @param aSceneList �؂�ւ���V�[�����w�肷��\����
void SceneManager::onSceneChanged(const SceneList aSceneList)
{
	switch (aSceneList) {
	case SceneList::POP:
		// ���݂̃V�[�����|�b�v����
		mSceneStack.pop();
		break;
	case SceneList::Test:
		mSceneStack.push(std::make_shared<TestScene>(this));
		break;
	case SceneList::Title:
		//mSceneStack.push(std::make_shared<TitleScene>(this));
		break;
	case SceneList::Game:
		//mSceneStack.push(std::make_shared<GameScene>(this));
		break;
	default:
		// �G���[���b�Z�[�W
		MessageBox(NULL, TEXT("���݂��Ȃ��V�[����ǂݍ������Ƃ��܂����B"), TEXT("SCENE_ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
