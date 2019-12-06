/*============================================

[Character.h]
Author : hohman yuushi

=============================================*/

#pragma once
#include "main.h"
#include "CharacterCamera.h"
#include "Model.h"
#include <d3d9types.h>
#include <d3dx9tex.h>




//#	キャラクタークラス :　親クラス

class XFile;

/* キャラクターの情報を管理するクラス　*/
class Character
{
private:
	//CharacterCamera m_Camera;	//	キャラクターにつけるカメラのインスタンス
	static LPDIRECT3DTEXTURE9	m_pTextureModel;	// テクスチャへのポインタ
	static LPD3DXMESH			m_pMeshModel;		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMatModel;	// マテリアル情報へのポインタ
	static DWORD				m_nNumMatModel;		// マテリアル情報の総数
	static LPDIRECT3DDEVICE9	pDevice;
	static float				m_Velocity;
	D3DXMATRIX			mtxWorldModel;		// ワールドマトリックス
	D3DXVECTOR3			posModel;			// 現在の位置
	D3DXVECTOR3			rotModel;			// 現在の向き
	D3DXVECTOR3			rotDestModel;		// 目的の向き
public:
	D3DXVECTOR3			moveModel;			// 移動量
	

public:
	Character();
	~Character();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit();
	void Update();
	void Draw();
};


/*
	//Xファイルオブジェクトクラス
	class XFileObject
	{
		LPD3DXMESH	m_pMesh;
		DWORD		m_dwNumMaterials;

		LPDIRECT3DTEXTURE9*	m_ppTextures;
		D3DMATERIAL9*		m_pMatrs;

	public:
		XFileObject()
		{
			m_pMesh = NULL;
			m_dwNumMaterials = 0;
			m_ppTextures = NULL;
			m_pMatrs = NULL;

		}

		bool LoadXFile(LPCWSTR file);
		void Render();

		void Release();
	};
*/

	//描画関連クラス
	class CGraphic
	{
		enum DisplayMode {
			FullScreen,
			WindowMode,
		};

		DisplayMode	m_currDisplayMode;//画面モード
		DWORD		m_backColor;//背景色

	public:
		CGraphic();
		~CGraphic();

		//生成と破棄
		bool Create(HWND hWnd);
		void Destroy();

		void ClearAndBegin();//Draw前に呼ぶ
		void EndAndPresent();//Draw後に呼ぶ
	};


	//CGraphicクラスの生成と破棄はこれで行う。
	CGraphic*	CreateGraphic(HWND hWnd);
	CGraphic*	GetGraphic();
	void		ReleaseGraphic();