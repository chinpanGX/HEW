// author 成

#include"main.h"
#include"mondai.h"
#include <time.h>
#include "Controller.h"

enum Mondaienum
{
	firstMondai = 0,
	secondMondai = 1,
	thirdMondai = 2,
};

//	スタティック変数
bool Mondai::m_flg;		//	解答フラグ

void Mondai::Update()
{
	if (KeyBoard::IsTrigger(DIK_A))
	{
		m_flg = true;
	}
	if (KeyBoard::IsTrigger(DIK_D))
	{
		m_flg = false;
	}
}

//	プレイヤーが呼び出す描画
void Mondai::Draw(int show)
{
	switch (show)
	{
	case firstMondai:
		Show(0);
		break;

	case secondMondai:
		Show(1);
		break;

	case thirdMondai:
		Show(2);
		break;
	}
}

//	問題の選出
void Mondai::Show(int show)
{
	int m;	//	問題選出する変数
	switch (show)
	{
	case 0:
		srand((unsigned)time(NULL));
		m = rand() % 3;
		MondaiOne(m);
		break;
	case 1:
		srand((unsigned)time(NULL));
		m = rand() % 3;
		MondaiTwo(m);
		break;
	case 2:
		srand((unsigned)time(NULL));
		m = rand() % 3;
		MondaiThree(m);
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

//	正解はどっち？
bool Mondai::Answer(bool flg)
{
	if (flg == true)
	{
		//	〇が正解
		return true;
	}
	else
	{
		//	×が正解
		return false;
	}
}

//	解答のゲッター
bool Mondai::GetAnswer()
{
	//	選んだ解答のフラグを返す
	if (m_flg == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}


