/*=====================================================

	[Score.h]
	Author : èoçá„ƒëæ

======================================================*/

#pragma once
#include "main.h"
#include "sprite.h"
class Score
{
	Sprite m_sprite;
	void Draw(float x, float y, int n);
public:
	void Draw(float x,float y,int score,int flg,bool bZero);
};

