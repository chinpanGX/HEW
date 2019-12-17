/*=====================================

	[BillBoard.h]
	

======================================*/

#pragma once

#include "main.h"
#include "texture.h"

HRESULT BillBoard_Init();
void BillBoard_Uninit();
void BillBoard_Draw(TextureIndex texture_index,D3DXVECTOR3 mtxPos , D3DXVECTOR3 mtxScl);