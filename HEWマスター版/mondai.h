
//成


#pragma once
#include "main.h"
#include "sprite.h"

class Mondai
{
private:
	Sprite	m_Sprite;	
	static bool	m_flg;				//	解答フラグ
	static bool dr_flag1; //描画のフラグ
	static bool dr_flag2;
public:
	void Update();
	void Draw(int snow);			//	プレイヤーで呼び出す描画
	static bool GetAnswer();		//	フラグのゲッター
private:
	void Show(int show);			//	問題文の選出
	void MondaiOne(int answer);		//	１問目の描画
	void MondaiTwo(int answer);		//	２問目の描画
	void MondaiThree(int answer);	//	３問目の描画
	static bool Answer(bool flg);	//	正解はどっち？の判別
};
