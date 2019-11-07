/*===========================================================

	[Model.h]
	Author : 出合翔太

============================================================*/

#pragma once
#include "XFile.h"

//#	Modelクラス : 親クラス->XFileクラス
/* モデルを描画するクラス */
class Model : public XFile
{
private:
	D3DXVECTOR3	position;					//	位置
	D3DXVECTOR3	scale;						//	大きさ
	D3DXVECTOR3	angle;						//	回転
	XFile *pmodel;							//	XFile型ポインタ変数
	static LPDIRECT3DDEVICE9 g_pD3DDevice;	//	デバイス

public:
	Model(D3DXVECTOR3	position, D3DXVECTOR3 scale, D3DXVECTOR3 angle, XFile *pmodel) :position(position), scale(scale), angle(angle), pmodel(pmodel) {}
	void Unload();
	void Draw();
};


