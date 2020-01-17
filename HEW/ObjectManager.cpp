/*============================================

	[ObjectManager.cpp]
	概要：オブジェクトのゲッターを管理
	Author :　出合翔太

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
