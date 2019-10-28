/*=====================================================

	[BeseScene.h]
	Author : 出合翔太

======================================================*/

#pragma once
#include "main.h"

//#	BaseSceneクラス : 親クラス
class BaseScene
{
public:
	virtual ~BaseScene() {};
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
