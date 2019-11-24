/*============================================

[Character.cpp]
Author :hohman yuushi

=============================================*/

#include "Character.h"
#include "Map.h"
#include "Controller.h"
#include "main.h"
#include <d3dx9.h>
#include <math.h>


/*--------------------------------------------------------------
enum
---------------------------------------------------------------*/
enum PLAYER_STATE		//Playerの状態遷移
{
	PLAYER_WAIT,		//	待機
	PLAYER_START,		//	開始
	PLAYER_ANSWER,		//	解答
	PLAYER_JUMP,		//	ジャンプ
	PLAYER_FINISH		//	終了(着地かな)
};


enum LANE_STATE			//レーンのなんかあれ
{
	LANE_START,


	LANE_SELECT,

	LANE_1,
	LANE_2,
	LANE_3,
	LANE_4,


	LANE_JUMP,

	LANE_END
};



/*---------------------------------------------------------------------------------
struct
---------------------------------------------------------------------------------*/
typedef struct
{
	D3DXVECTOR3 PPos;		//PlayerPoint(postion)
	float		P_x, P_y;	//Playerにかかる移動量
	float		Speed;		//Playerの速度
	int			Status;		//Playerの状態
}PlayerData;


/*---------------------------------------------------------------------------------
global
-----------------------------------------------------------------------------------*/
static PlayerData g_Player;		//プレイヤーデータ
static HWND hWnd;				//メッセージ表示に使用

static int	g_LaneStatus;			//レーンステータス
static int	g_count;				//問題数カウンタ
static int	g_Q,g_A;				//正解番号格納、回答格納

static float		tmp;					//SPEED一時保存
static float		radian;


/*-----------------------------------------
関数諸々
-----------------------------------------*/
Character::Character()
{
	
}


Character::~Character()
{
	
}


void Character::Init()
{
	//とりあえずここで初期化
	g_Player.PPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_Player.PVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.Speed = 0;
	g_Player.Status = PLAYER_WAIT;

	//メッセージで利用してるから
	hWnd = GetHWND();


}


void Character::Uninit()
{
	
}


void Character::Update()
{
	//Playerのステータスで判断(ステータス外の数値はエラー対応)
	switch (g_Player.Status)
	{
		//待機モーションでも垂れ流しときゃええんちゃう？
	case PLAYER_WAIT:

		//ここにモーションかな

		if (KeyBoard::IsTrigger(DIK_E))
		{
			//ステータス変更
			g_Player.Status = PLAYER_START;
		}
		break;

		
	case PLAYER_START:		//滑走開始

		if (g_Player.Speed >= 5.0f)
		{
			tmp = g_Player.Speed;

			//ここにちょっとインターバル入れればいいかな
			g_Player.Status = PLAYER_ANSWER;
		}

		//加速
		g_Player.Speed += 0.2f;

		break;

		
	case PLAYER_ANSWER:		//解答

		//SPEEDを保存して停止
		tmp = g_Player.Speed;
		g_Player.Speed = 0.0f;

	if (KeyBoard::IsTrigger(DIK_A))
	{// 左移動

	}
	else if (KeyBoard::IsTrigger(DIK_D))
	{// 右移動

	}

	//とりあえずSpaceで次へ
	if (KeyBoard::IsTrigger(DIK_SPACE))
	{
		//何回回答したか
		g_count++;

		//速度復元
		g_Player.Speed = tmp;

		if (g_Q == g_A)
		{
			g_Player.Speed *= 0.3f;
		}
		
		if (g_count >= 3)
		{
			g_Player.Status = PLAYER_JUMP;
		}
		else
		{
			g_Player.Status = PLAYER_START;
		}
	}
		break;



		case PLAYER_JUMP:		//ジャンプ

		//加速、タイミングの兼ね合いで数値を出す
		MessageBox(hWnd, "Jump処理", "JUMP", MB_OK);	//...指標(台)がないとタイミングとれなくね
		g_Player.Status = PLAYER_FINISH;

		break;

		
	case PLAYER_FINISH:		//終了

		MessageBox(hWnd, "終了処理", "END", MB_OK);

		break;


	default:
		//エラー対応
		MessageBox(hWnd, "存在しないプレイヤーステータスです", "ERROR", MB_OK);
		exit(1);

		break;
	}

	getRadian(0.0f, 0.0f, 100.0f, -1000.0f);
	//移動処理
	g_Player.PPos.x += cosf(radian)*2.0f;
	g_Player.PPos.y += sinf(radian)*2.0f;
}

void Character::Draw()
{

}


float getRadian(float X1, float Y1, float X2, float Y2)
{
	float w = X2 - X1; // cosθ
	float h = Y2 - Y1; // sinθ

	return atan2f(h, w);
}


/*
メモ代わり

float getRadian(float X1,float Y1,float X2,float Y2)
{
float w = X2 - X1; // cosθ
float h = Y2 - Y1; // sinθ

return atan2f(h,w);
}

// ターゲットの方向へ進む
m_x += cosf(radian);
m_y += sinf(radian);



上記適用可能か模索

恐らく
m_x += cosf(radian) * speed
で速度調整可能
*/
