/*=====================================================

	[Score.h]
	Author : 出合翔太

======================================================*/

#pragma once
#include "main.h"
#include "sprite.h"


#if 0
//	クラス
class Score
{
		//<-何も書かないとアクセス指定子はprivateになる
	Sprite m_sprite;
	void Draw(float x, float y, int n);
public:
	void Draw(float x,float y,int score,int flg,bool bZero);
};
#else

//	構造体
struct Score
{
private:	//<-何も書かないとアクセス指定子はpublicになる
	Sprite m_sprite;
	void Draw(float x, float y, int n);
public:
	void Draw(float x, float y, int score, int flg, bool bZero);
};
#endif

//	■■　typedefの意味 ■■
/*

	ちなみにC言語のときはtypedefを頭につけていた。
	その理由は構造体の変数宣言のときに、「struct」というキーワードを付ける必要があったから
	これを省略するためにtypedefをつけていた

	◆◆↓typedefを使わない書き方↓◆◆
	struct Player							
	{											
		int a;								
	};

	↓頭にstructをつける
	struct Player g_player = { 10 };
	
	◆◆↓typedefを使った書き方↓◆◆
	typedef struct
	{
		int a;
	}Player;
	
	↓structのキーワードを省略
	Player g_player = { 10 };

	
	このtypedefの書き方はC言語のときに必要だったものでC++になるとtypedefの記述は必要ない。
	→typedefを書かなくても、変数の前に「struct」のキーワードをつける必要がなくなった。

	◆◆↓C++の構造体宣言↓◆◆
	struct Player
	{
		int a;
	};
		
	Player g_player = { 10 };

*/

//	■■　C++の構造体とクラスの違い ■■
/*
	構造体とクラスの違いはただ一つ。
	アクセス指定子のデフォルトが違うだけ
	クラスはprivate、構造体はpublicになる。
	つまり…
	C++なら、構造体にも関数をメンバーにできるんですねぇ

	ちなみに、C言語のとき、
	構造体の中にある変数のことをメンバーと呼んでいた。

	◆↓1年生の復習↓◆
	typedef struct
	{
		int a;←メンバー
	}Player;

	C++になったときこのメンバーに関数が追加されたので、
	変数はメンバー変数、関数はメンバー関数と使い分けて呼んでいるだけ
	なので、混乱しないように。

	struct Player
	{
		int Hensuu;		<-メンバー変数
		void Kansuu();	<-メンバー関数
	}

	以上、ちょっとした解説でした。
*/
