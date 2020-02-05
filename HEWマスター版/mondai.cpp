#include"main.h"
#include"mondai.h"
#include <time.h>
#include "Controller.h"
#include "SceneGame.h"
#include "Sound.h"

//	マクロ定義
#define QUEST_MAX	3

//	グローバル変数
int		quest[QUEST_MAX];
int		count;
int		score;

const bool	toi[9] = { true,false,false,true,false,true,true,true,false };

//	スタティック変数
bool Mondai::m_flg;		//	解答フラグ
bool Mondai::dr_flag1 = false;
bool Mondai::dr_flag2 = false;

void Mondai::Init()
{
	for (int i = 0; i < QUEST_MAX; i++)
	{
		quest[i] = rand() % QUEST_MAX;
	}
	count = 0;
	score = 0;
}

void Mondai::Update()
{
	if (KeyBoard::IsTrigger(DIK_LEFTARROW) || GamePad::IsTrigger(0, BUTTON_LEFT))
	{
		m_flg = false;
	}
	if (KeyBoard::IsTrigger(DIK_RIGHTARROW) || GamePad::IsTrigger(0, BUTTON_RIGHT))
	{
		m_flg = true;
	}

	if (KeyBoard::IsTrigger(DIK_SPACE) || (GamePad::IsTrigger(0, BUTTON_2)))
	{
		Sound::Play(S_SE_DECISION);
		if (Answer(toi[(QUEST_MAX*count) + quest[count]], m_flg) == true)
		{
			Sound::Play(S_SE_CORRECT);
			score++;
		}
		else
		{
			Sound::Play(S_SE_INCORRECT);
		}
		count++;
	}
}
//	プレイヤーが呼び出す描画
void Mondai::Draw(int show)
{
	switch (show)
	{
	case MONDAI_1st:
		Show(MONDAI_1st);
		break;

	case MONDAI_2nd:
		Show(MONDAI_2nd);
		break;

	case MONDAI_3rd:
		Show(MONDAI_3rd);
		break;
	}
	
}


//	問題の選出
void Mondai::Show(int show)
{
	switch (show)
	{
	case 0:
		MondaiOne(quest[0]);
		break;
	case 1:
		MondaiTwo(quest[1]);
		break;
	case 2:
		MondaiThree(quest[2]);
		break;
	}
}

//	
void Mondai::MondaiOne(int answer)
{
	switch (answer)
	{
	case 0:

		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 0.0f, 0.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);
		//DrawAnser(false, 300.0f, 0.0f);
		//DrawAnser(true, 935.0f, 0.0f);
		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 0.0f, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 0.0f, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);
		//Answer(//どっちが正解);
		break;
	case 1:
		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 2134.0f, 0.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 1067.0f, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 1067.0f, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);
		//m_flg = true;
		break;
	case 2:
		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 4268.0f, 0.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 1067.0f * 2, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 1067.0f * 2, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);
		//Answer(//どっちが正解);
		break;
	}
}

void Mondai::MondaiTwo(int answer)
{
	switch (answer)
	{
	case 0:
		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 0.0f, 534.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 1067.0f * 3, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 1067.0f * 3, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);
		//Answer(//どっちが正解);
		break;
	case 1:
		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 2134.0f, 534.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 1067.0f * 4, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 1067.0f * 4, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);
		//Answer(//どっちが正解);
		break;
	case 2:
		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 4268.0f, 534.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 1067.0f * 5, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 1067.0f * 5, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);
		//Answer(//どっちが正解);
		break;
	}
}

void Mondai::MondaiThree(int answer)
{
	switch (answer)
	{
	case 0:
		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 0.0f, 1068.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 1067.0f * 6, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 1067.0f * 6, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		//Answer(//どっちが正解);
		break;
	case 1:
		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 2134.0f, 1068.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 1067.0f * 7, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 1067.0f * 7, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);
		//Answer(//どっちが正解);
		break;
	case 2:
		m_Sprite.Draw(TEXTURE_QUIZ, 100.0f, 0.0f, 4268.0f, 1068.0f, 2134.0f, 534.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 300.0f, 435.0f, 0.0f, 1067.0f * 8, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);

		m_Sprite.Draw(TEXTURE_ANSWER, 975.0f, 435.0f, 1070.0f, 1067.0f * 8, 1070.0f, 1067.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f);


		//Answer(//どっちが正解);
		break;
	}
}

//	正解の場合trueを返す
bool Mondai::Answer(bool question, bool answer)
{
	if (question == answer)
	{
		return true;
	}
	else if (question != answer)
	{
		return false;
	}
}

int GetScore()
{
	return score;
}