/*=====================================================

	[BeseScene.h]
	Author : 出合翔太

======================================================*/

#pragma once

//インクルードファイル
#include "main.h"

class BeseScene
{
public:
	virtual ~BeseScene() {};
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
