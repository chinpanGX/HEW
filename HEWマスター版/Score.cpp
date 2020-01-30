/*=====================================================

	[Score.cpp]
	Author : �o���đ�

=====================================================*/

#include "Score.h"

//	�v���g�^�C�v�錾
void Draw(float x, float y, int n);

void Score_Draw(float x, float y, int score, int flg)
{
	// �J���X�g�p�̍ő吔�l�����
	int count_stop_score = 1;
	for (int i = 0; i < flg; i++)
	{
		count_stop_score *= 10;
	}

	//�ő�l�̕␳����
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

