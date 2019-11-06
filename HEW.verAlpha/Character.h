/*============================================

	[Character.h]
	Author : 出合翔太

=============================================*/

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Model.h"

class Model;
//#	Characterクラス
/* キャラクターの情報を管理するクラス　*/
class Character
{
private:
	D3DXVECTOR3 Position;			//	位置
	Model		*pModel;			//	Model型ポインタ変数
	static LPDIRECT3DDEVICE9 g_pD3DDevice;	//	デバイス	
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	
};

