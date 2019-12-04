/*================================================

	[Scenedebug.cpp]
	Author : �o���đ�

=================================================*/

#include "SceneDebug.h"
#include "SceneManager.h"
#include "main.h"
#include "DebugCamera.h"
#include "light.h"
#include "debugproc.h"
#include "Map.h"

//# �f�o�b�O�V�[���̏����� 
void SceneDebug::Init()
{
	//LPDIRECT3DDEVICE9 pD3DDevice = GetD3DDevice();
	m_Map.Init();
	Light::Init();
	//m_Camera.Init();
	//m_Character = new Model(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_pXFileList["asset/model/dai.x"]);
	m_Character.Init(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_CharaCamera.Init();
	
	//DebugProc_Initialize();
	//m_Sprite.Init(pD3DDevice);

	
}

//# �f�o�b�O�V�[���̏I������
void SceneDebug::Uninit()
{
	m_Map.Uninit();
	Light::Uninit();
	//m_Camera.Uninit();
	m_Character.Uninit();
	m_CharaCamera.Uninit();
	//DebugProc_Finalize();
	//m_Sprite.Uninit();
}

//# �f�o�b�O�V�[���̍X�V����
void SceneDebug::Update()
{
	//m_Camera.Update();
	m_Character.Update();
	m_CharaCamera.Update();
}

//# �f�o�b�O�V�[���̕`�揈��
void SceneDebug::Draw()
{
	//DebugProc_Draw();
	m_Map.Draw();
	//m_Camera.Set();
	m_Character.Draw();
	m_CharaCamera.Set();
	//m_Sprite.Draw(TEXTURE_INDEX_QUIZSAMPLE,1024,256,0,0,0,0,1,1,1);
}
