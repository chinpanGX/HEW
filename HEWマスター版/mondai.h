#pragma once
#include "main.h"
#include "sprite.h"

enum MONDAI_NUM
{
	MONDAI_1,
	MONDAI_2,
	MONDAI_3,
	MONDAI_4,
	MONDAI_5,
	MONDAI_6,
	MONDAI_7,
	MONDAI_8,
	MONDAI_9,
	MONDAI_END,
};

int	 GetScore();

class Mondai
{
private:
	Sprite	m_Sprite;	
	MONDAI_NUM m_State;
	static bool	m_flg;	  //解答フラグ
	static bool dr_flag1; //描画のフラグ
	static bool dr_flag2;
	void MondaiDraw(int answer);		//	問の描画

public:
	void Init();
	void Update();
	void Draw(int State);			//	プレイヤーで呼び出す描画
	static bool Answer(bool question, bool answer);		//	フラグのゲッター

};
