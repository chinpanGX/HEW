/*============================================

	[ObjectManager.h]	
	概要：オブジェクトのゲッターを管理
	Author :　出合翔太

============================================*/

#pragma once
#include "SceneManager.h"
#include "SceneGame.h"

class ObjectManager
{
public:
	static Character* SetCharacter();	//	キャラクターオブジェクトのゲッター
	static Field* SetField();			//	マップオブジェクトのゲッター
	static Camera* SetCamera();			//	カメラオブジェクトのゲッター
};

