/*==================================
	
	[texture.h]
	Author : 出合翔太

==================================*/

#pragma once
#include <d3d9.h>

//列挙型：テクスチャの指定
typedef enum
{
	TEXTURE_INDEX_RESULT,
	TEXTURE_INDEX_SAMPLE,
	TEXTURE_UI,
	TEXTURE_QUIZ,
	TEXTURE_ANSWER,
	TEXTURE_NUMBER,
	TEXTURE_FRAME,
	TEXTURE_TITLE,

    TEXTURE_INDEX_MAX
}TextureIndex;

int Texture_Load();			//テクスチャのロード					
void Texture_Release();		//テクスチャのリリース
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);	//テクスチャオブジェクトを画像ファイルから読み込む関数
int Texture_GetWidth(TextureIndex index);		//テクスチャの横幅
int Texture_GetHeight(TextureIndex index);		//テクスチャの縦幅
