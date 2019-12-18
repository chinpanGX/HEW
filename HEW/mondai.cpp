// author 成



#include"main.h"

#include"mondai.h"
#include"texture.h"
#include"Controller.h"
#include"sprite.h"
#include<time.h>
#include<stdlib.h>
#include <iostream>
using namespace std;

enum Mondaienum
{
	firstMondai = 0,
	secondMondai = 1,
	thirdMondai = 2,
};

//	スタティック変数
bool	Mondai::m_flg;		//	解答フラグ

void Mondai::Update()
{
	bool m_flg = true;
	if (m_flg == true)
	{
		//	〇を拡大
		//m_Sprite.Draw();
	}
	else if (m_flg == false)
	{
		//　Xを拡大
		//m_Sprite.Draw();
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
	int m;
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
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
		//Answer(//どっちが正解);
		break;
	case 1:
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
		//m_flg = Answer(true);
		break;
	case 2:
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
		//Answer(//どっちが正解);
		break;
	}
}

void Mondai::MondaiTwo(int answer)
{
	switch (answer)
	{
	case 0:
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
		//Answer(//どっちが正解);
		break;
	case 1:
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
		//Answer(//どっちが正解);
		break;
	case 2:
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
		//Answer(//どっちが正解);
		break;
	}
}

void Mondai::MondaiThree(int answer)
{
	switch (answer)
	{
	case 0:
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
		//Answer(//どっちが正解);
		break;
	case 1:
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
		//Answer(//どっちが正解);
		break;
	case 2:
		//m_sprite.Draw()
		//m_Sprite.Draw()
		//m_Sprite.Draw()
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


