/*=====================================================

	[Score.cpp]
	Author : 出合翔太

=====================================================*/

#include "Score.h"

//	プロトタイプ宣言
void Draw(float x, float y, int n);

void Score_Draw(float x, float y, int score, int flg)
{
	// カンスト用の最大数値を作る
	int count_stop_score = 1;
	for (int i = 0; i < flg; i++)
	{
		count_stop_score *= 10;
	}

	//最大値の補正処理
	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}

	for (int i = 0; i < flg; i++)
	{

		int n = score % 10;
		score /= 10;
		Draw(x + 32 * (flg - (i + 1)), y, n);
	}
}

void Draw(float x, float y, int n)
{
	Sprite m_sprite;
	if (n < 0 || n > 9) return;
	m_sprite.Draw(TEXTURE_NUMBER, x, y,32 * n, 0, 32, 32,32,32,3.0f,3.0f,0.0f);
}

