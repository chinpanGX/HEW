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




//#	�L�����N�^�[�N���X :�@�e�N���X

class XFile;

/* �L�����N�^�[�̏����Ǘ�����N���X�@*/
class Character
{
private:
	CharacterCamera m_Camera;	//	�L�����N�^�[�ɂ���J�����̃C���X�^���X

	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 angle;
	XFile		*pmodel;

	static LPDIRECT3DDEVICE9 g_pD3DDevice;

public:
	Character();
	~Character();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


	//X�t�@�C���I�u�W�F�N�g�N���X
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


	//�`��֘A�N���X
	class CGraphic
	{
		enum DisplayMode {
			FullScreen,
			WindowMode,
		};

		DisplayMode	m_currDisplayMode;//��ʃ��[�h
		DWORD		m_backColor;//�w�i�F

	public:
		CGraphic();
		~CGraphic();

		//�����Ɣj��
		bool Create(HWND hWnd);
		void Destroy();

		void ClearAndBegin();//Draw�O�ɌĂ�
		void EndAndPresent();//Draw��ɌĂ�
	};

	//CGraphic�N���X�̐����Ɣj���͂���ōs���B
	CGraphic*	CreateGraphic(HWND hWnd);
	CGraphic*	GetGraphic();
	void		ReleaseGraphic();