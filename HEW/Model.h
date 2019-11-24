/*===========================================================

	[Model.h]
	Author : 出合翔太

============================================================*/

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "XFile.h"

//#	Modelクラス : XFileクラスの派生クラス
/* モデルを描画するクラス */
class XFile;

class Model
{
private:
	D3DXVECTOR3	position;					//	位置
	D3DXVECTOR3	scale;						//	大きさ
	D3DXVECTOR3	angle;						//	回転
	XFile *pmodel;							//	XFile型ポインタ変数
	static LPDIRECT3DDEVICE9 g_pD3DDevice;	//	デバイス

public:
	Model(D3DXVECTOR3 position, D3DXVECTOR3 scale, D3DXVECTOR3 angle, XFile *pmodel) :position(position), scale(scale), angle(angle), pmodel(pmodel) {}	//	コンストラクタ：変数の初期値
	void Draw();	//	描画処理
};


