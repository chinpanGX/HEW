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

/* キャラクターの情報を管理するクラス　*/
class Character
{
private:
	CharacterCamera m_Camera;	//	キャラクターにつけるカメラのインスタンス
public:
	Character();
	~Character();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


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