/*===========================================================
	
	[Drawer.h]
	Author : 出合翔太

============================================================*/

#pragma once
#include "Model.h"

//#	Drawerクラス
/* モデルを描画するクラス */
class Drawer: public Model
{
private:
	D3DXVECTOR3	position;
	D3DXVECTOR3	scale;
	D3DXVECTOR3	angle;
	Model *pmodel;

public:
	Drawer(D3DXVECTOR3	position,D3DXVECTOR3 scale,D3DXVECTOR3 angle,Model *pmodel) :position(position), scale(scale), angle(angle), pmodel(pmodel){}
	void Draw();
};

