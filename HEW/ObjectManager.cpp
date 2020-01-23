/*============================================

	[ObjectManager.cpp]
	�T�v�F�I�u�W�F�N�g�̃Q�b�^�[���Ǘ�
	Author :�@�o���đ�

============================================*/

#include "ObjectManager.h"

Character * ObjectManager::SetCharacter()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->SetCharacter();
}

Field * ObjectManager::SetField()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->SetField();
}

Camera * ObjectManager::SetCamera()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->SetCamera();
}
