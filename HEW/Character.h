/*=================================================

	[Character.h]
	Author : 出合翔太

=================================================*/

#pragma once
#include "main.h"
#include "CharacterCamera.h"
#include "Field.h"

///	<summary>
///	プレイヤーのステートマシンを管理する
/// </summary>
enum PlayerState
{
	PLAYER_INIT,		//	初期化
	PLAYER_MOVE,		//	移動
	PlAYER_ANSWERSTAY,	//	解答まち
	PLAYER_ANSWER,		//	解答
	PLAYER_JUMP,		//	ジャンプ
	PLAYER_END			//	終了
};

///	<summary>
///	問題文の描画、解答選択などのステートマシンを管理 
///	</summary>
enum AnswerStayState
{
	ANSWER_DROW,
	ANSWER_SELECT,
};

///	<summary>
///	キャラクターの管理をするクラス
/// </summary>
class Character
{
public:
	static LPDIRECT3DTEXTURE9	m_pTexture;	//	テクスチャへのポインタ
	static LPD3DXMESH			m_pMesh;	//	メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat;	//	マテリアル情報へのポインタ
	static DWORD				m_nNumMat;	//	マテリアル情報の総数
	static D3DXMATRIX			m_mtxWorld;	//	ワールドマトリックス
	static int					m_count;	//	問題数のカウンター
	LPDIRECT3DDEVICE9			m_pDevice;	//	デバイス
	D3DXVECTOR3					m_position;	//	現在の位置
	D3DXVECTOR3					m_rotation;	//	現在の向き
	D3DXVECTOR3					m_rotDest;	//	目的の向き
	D3DXVECTOR3					m_scale;	//	モデルの大きさ
	D3DXVECTOR3					m_velocity;	//	移動量
	float						m_grivity;	//	重力
	int							m_score;	
	/// <summary>
	///	プレイヤーに関するステート用メンバー変数
	///	</summary>
	PlayerState					m_PlayerState;	
	///	<summary>
	///	解答まち中に回すステート用変数
	///	</summary>
	AnswerStayState				m_AnsawerStayState;
	CharacterCamera				*m_pCamera;
public:
	///	<summary>
	///	初期化処理
	/// </summary>
	/// <return> 初期位置、初期向き </return>
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit();								
	void Update();								
	void Draw();								
	
	//	ゲッター
	D3DXVECTOR3	GetPos();	///	<return> m_position </return>
	D3DXVECTOR3	GetRot();	///	<return> m_rotation </return>
	D3DXVECTOR3	GetMove();	///	<return> m_velocity </return>
	D3DXMATRIX	GetMat();	///	<return> m_mtxworld </return>
	LPD3DXMESH	GetMesh();	///	<return> m_pMesh </return>
	int			Score();	///	<return> m_score </return

private:
	//	ステート関数
	void InitState();			//	初期化
	void MoveState();			//	スタート
	void AnswerstayState();		//	解答まち
	void AnswerState();			//	解答
	void JumpState();			//	ジャンプ
	void EndState();			//	終了
};

