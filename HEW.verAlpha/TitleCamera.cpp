/*===========================================

	[TitleCamera.cpp]
	Author : 出合翔太

===========================================*/

#include "main.h"
#include "TitleCamera.h"

//	スタティック変数
D3DXVECTOR3			Camera::posV;
D3DXVECTOR3			Camera::posR;
D3DXVECTOR3			Camera::vecU;
D3DXMATRIX			Camera::mtxProjection;
D3DXMATRIX			Camera::mtxView;
LPDIRECT3DDEVICE9	Camera::pDevice;
D3DXVECTOR3			TitleCamera::m_Velocity;

//	初期化
void TitleCamera::Init()
{
	m_Velocity = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	移動速度の初期化
	Camera::Init();								//	基底クラス(Camera)のInit関数を呼び出す
	posV.y = -200.0f;							//	カメラの視点初期位置（Y座標）を-200に設定
}

void TitleCamera::Uninit()
{

}

//	更新処理
void TitleCamera::Update()
{
	posV.x += m_Velocity.x;	//	カメラのX座標を動かす
	if (posV.x > 100.0f)	//	100.0f地点を超えたとき
	{
		posV.x = 100.0f;	
		m_Velocity *= -1;	//	m_Velocityに-1を乗算代入　->　逆方向に移動
	}
	else if(posV.x <-100.0f)
	{
		posV.x = -100.0f;
		m_Velocity *= -1;
	}
}

void TitleCamera::Set()
{
	Camera::Set();	//	基底クラス(Camera)のSet関数を呼び出す
}
