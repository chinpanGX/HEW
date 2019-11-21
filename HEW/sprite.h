/*==================================
	
	[sprite.h]
	Author : 出合翔太

=================================*/

//!	このソースコードは使わない！

#pragma once

//インクルードファイル
#include <d3d9.h>
#include "texture.h"

//SPRITEクラス
class SPRITE
{
public:
	//メンバ関数
	static void SetColor(D3DCOLOR color);		
	static void Draw(TextureIndex texture_index, float dx, float dy);
	static void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);
	static void Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation);
};