/*============================================

	[Character.h]
	Author : 

=============================================*/

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Model.h"

//#	Characterクラス
/* キャラクターの情報を管理するクラス　*/
class Character
{
private:
	static Model *Actor[1];
	D3DXVECTOR3	position;					//	位置
	D3DXVECTOR3	scale;						//	大きさ
	D3DXVECTOR3	angle;						//	回転
	D3DXVECTOR3 Velocity;					//	速度
	XFile *pmodel;							//	XFile型ポインタ変数
	static LPDIRECT3DDEVICE9 g_pD3DDevice;	//	デバイス
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};

