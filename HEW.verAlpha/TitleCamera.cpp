/*===========================================

	[TitleCamera.cpp]
	Author : o‡ãÄ‘¾

===========================================*/

#include "main.h"
#include "TitleCamera.h"

D3DXVECTOR3			Camera::posV;
D3DXVECTOR3			Camera::posR;
D3DXVECTOR3			Camera::vecU;
D3DXMATRIX			Camera::mtxProjection;
D3DXMATRIX			Camera::mtxView;
LPDIRECT3DDEVICE9	Camera::pDevice;

TitleCamera::TitleCamera()
{

}

TitleCamera::~TitleCamera()
{

}

void TitleCamera::Init()
{
	Camera::Init();
}

void TitleCamera::Uninit()
{

}

void TitleCamera::Update()
{
	D3DXVECTOR3 Velocity(1.0,1.0,1.0);
	posV.x += Velocity.x;
	if (posV.x > 100.0f)
	{
		posV.x = 100.0f;
		Velocity *= -1;
	}
	else if(posV.x <-100.0f)
	{
		posV.x = -100.0f;
		Velocity *= -1;
	}
}

void TitleCamera::Set()
{
	Camera::Set();
}
