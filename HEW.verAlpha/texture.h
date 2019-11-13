/*==================================
	
	[texture.h]
	Author : 出合翔太

==================================*/

//!	このソースコードは使わない！

#pragma once

//インクルードファイル
#include <d3d9.h>

//列挙型：テクスチャの指定
typedef enum
{
	TEXTURE_INDEX_YUKIDARUMA,
	TEXTURE_INDEX_BULLET,
	TEXTURE_INDEX_LASER,
	TEXTURE_INDEX_EXPLOSION,
	TEXTURE_INDEX_NUMBER,
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_RESULT,
	TEXTURE_INDEX_TILEMAP,
	TEXTURE_INDEX_SOUSA,
	TEXTURE_INDEX_RULE,

    TEXTURE_INDEX_MAX
}TextureIndex;

int Texture_Load();			//テクスチャのロード					
void Texture_Release();		//テクスチャのリリース
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);	//テクスチャオブジェクトを画像ファイルから読み込む関数
int Texture_GetWidth(TextureIndex index);		//テクスチャの横幅
int Texture_GetHeight(TextureIndex index);		//テクスチャの縦幅
