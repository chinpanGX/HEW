/*=================================================

	[Character.h]
	Author : 出合翔太

=================================================*/

#pragma once
#include "main.h"
#include "Model.h"
#include "XFile.h"

//	プレイヤーのステートマシン管理変数
enum PlayerState
{
	PLAYER_INIT,		//	初期化
	PLAYER_STRAT,		//	スタート
	PlAYER_ANSWERSTAY,	//	解答まち
	PLAYER_ANSWER,		//	解答
	PLAYER_JUMP,		//	ジャンプ
	PLAYER_END			//	終了
};

class Character
{
private:
	static LPDIRECT3DTEXTURE9	m_pTexture;	//	テクスチャへのポインタ
	static LPD3DXMESH			m_pMesh;	//	メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat;	//	マテリアル情報へのポインタ
	static DWORD				m_nNumMat;	//	マテリアル情報の総数
	static D3DXMATRIX			m_mtxWorld;	//	ワールドマトリックス
	LPDIRECT3DDEVICE9			m_pDevice;	//	デバイス
	D3DXVECTOR3					m_position;	//	現在の位置
	D3DXVECTOR3					m_rotation;	//	現在の向き
	D3DXVECTOR3					m_rotDest;	//	目的の向き
	D3DXVECTOR3					m_velocity;	//	移動量
	int							m_count;	//	問題数のカウンター
	float						m_gravity;	//	重力	
	PlayerState					m_state;	//	ステート変数
	XFile						m_XFile;
	Model						m_Model;

public:
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//	初期化処理
	void Uninit();									//	終了処理
	void Update();									//	更新処理
	void Draw();									//	描画処理
	//	ゲッター
	D3DXVECTOR3	GetPos();							
	D3DXVECTOR3	GetRot();
	D3DXVECTOR3	GetMove();
	D3DXMATRIX	GetMat();
	LPD3DXMESH	GetMesh();
private:
	//	ステート関数
	void Strat();								//	スタート
	void Answerstay();							//	解答まち
	void Answer();								//	解答
	void Jump();								//	ジャンプ
	void End();									//	終了
};

