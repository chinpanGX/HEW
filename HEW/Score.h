/*=====================================================

	[Score.h]
	Author : �o���đ�

======================================================*/

#pragma once
#include "main.h"
#include "sprite.h"

class Score
{
private:
	Sprite m_sprite;
	void Draw(float x, float y, int n);
public:
	void Draw(float x,float y,int score,int flg,bool bZero);
};
