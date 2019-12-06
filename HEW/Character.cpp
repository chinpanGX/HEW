/*============================================

[Character.cpp]
Author :hohman yuushi

=============================================*/

#include "Character.h"
#include "Map.h"
#include "Model.h"
#include "input.h"
#include "main.h"
#include <d3dx9.h>
#include <math.h>
#include "Controller.h"
#include "CharacterCamera.h"


//	マクロ定義
#define FILELIST 1	//	読み込むファイルの数
#define	MODEL_CAR			"asset/model/ri.x"	// 読み込むモデル名
#define	VALUE_MOVE_MODEL	(0.1f)					// 移動速度
#define	RATE_MOVE_MODEL		(0.2f)					// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)		// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)					// 回転慣性係数

#define	VALUE_JUMP				(10.0f)							// ジャンプ力
#define	VALUE_GRAVITY			(0.45f)							// 重力
#define	RATE_REGIST				(0.075f)						// 抵抗係数
#define	RATE_REFRECT			(-0.90f)						// 反射係数


/*--------------------------------------------------------------
enum
---------------------------------------------------------------*/
enum PLAYER_STATE		//g_Playerの状態遷移
{
	PLAYER_WAIT,		//	待機
	PLAYER_START,		//	開始
	PLAYER_ANSWER,		//	解答
	PLAYER_JUMP,		//	ジャンプ
	PLAYER_FINISH		//	終了(着地かな)
};

/*---------------------------------------------------------------------------------
global
-----------------------------------------------------------------------------------*/
static HWND hWnd;				//メッセージ表示に使用

static int	g_LaneStatus;			//レーンステータス
static int	g_count;				//問題数カウンタ
static int	g_Q,g_A;				//正解番号格納、回答格納

static float		Speedtmp;					//SPEED一時保存


//重力で使用
static bool flag;
static double Gravity;
static double moveGravity;

LPDIRECT3DDEVICE9 Character::pDevice;
//extern std::map<std::string, XFile *>g_pXFileList;
LPDIRECT3DTEXTURE9	Character::m_pTextureModel;		//	テクスチャへのポインタ
LPD3DXMESH			Character::m_pMeshModel;		//	メッシュ情報へのポインタ
LPD3DXBUFFER		Character::m_pBuffMatModel;		//	マテリアル情報へのポインタ
DWORD				Character::m_nNumMatModel;		//	マテリアル情報の総数
//static Model g_Player;

/*-----------------------------------------
関数諸々
-----------------------------------------*/
Character::Character()
{
	m_pTextureModel = NULL;
	m_pMeshModel	= NULL;
	m_pBuffMatModel = NULL;
}


Character::~Character()
{
	
}


HRESULT Character::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	pDevice = GetD3DDevice();

	//位置・向き・移動の初期設定
	posModel = pos;
	rotModel = rot;
	rotDestModel = rot;
	moveModel = D3DXVECTOR3(0.0f, 0.0f, 0.05f);

	//重力のやつ
	Gravity = -0.0089;	//定数やねこれ
	moveGravity = 0;
	flag = false;

	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(MODEL_CAR,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel)))
	{
		return E_FAIL;
	}
	return S_OK;
#if 0
	//!	XFlieのロード処理
	// 読み込みファイル名リスト
	std::string file_name_list[] =
	{
		"asset/model/dai.x",
	};

	// XFile読み込み
	for (int i = 0; i < FILELIST; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}
#endif
	//メッセージで利用してるから
	hWnd = GetHWND();
}


void Character::Uninit()
{
	
}


void Character::Update()
{
	CharacterCamera *pCamera;
	float fDiffRotY;

	// カメラの取得
	pCamera = GetCharCam();
#if 0
	if (KeyBoard::IsPress(DIK_A))
	{
		if (KeyBoard::IsPress(DIK_UP))
		{// 左奥移動
			moveModel.x += sinf(-D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(-D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		else if (KeyBoard::IsPress(DIK_DOWN))
		{// 左手前移動
			moveModel.x += sinf(-D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(-D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		else
		{// 左移動
			moveModel.x += sinf(-D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(-D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y + D3DX_PI * 0.50f;
		}
	}
	else if (KeyBoard::IsPress(DIK_D))
	{
		if (KeyBoard::IsPress(DIK_UP))
		{// 右奥移動
			moveModel.x += sinf(D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		else if (KeyBoard::IsPress(DIK_DOWN))
		{// 右手前移動
			moveModel.x += sinf(D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		else
		{// 右移動
			moveModel.x += sinf(D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y - D3DX_PI * 0.50f;
		}
	}
	else if (KeyBoard::IsPress(DIK_W))
	{// 前移動
		moveModel.x += sinf(D3DX_PI * 1.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;
		moveModel.z -= cosf(D3DX_PI * 1.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;

		rotDestModel.y = pCamera->rot.y + D3DX_PI * 1.0f;
	}
	if (KeyBoard::IsPress(DIK_LSHIFT))
	{// 左回転
		rotDestModel.y -= VALUE_ROTATE_MODEL;
		if (rotDestModel.y < -D3DX_PI)
		{
			rotDestModel.y += D3DX_PI * 2.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_RSHIFT))
	{// 右回転
		rotDestModel.y += VALUE_ROTATE_MODEL;
		if (rotDestModel.y > D3DX_PI)
		{
			rotDestModel.y -= D3DX_PI * 2.0f;
		}
	}
#endif
	
	moveModel.x += sinf(D3DX_PI * 0.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;
	moveModel.z -= cosf(D3DX_PI * 0.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;

	rotDestModel.y = pCamera->rot.y + D3DX_PI * 0.0f;

	

	// 目的の角度までの差分
	fDiffRotY = rotDestModel.y - rotModel.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// 目的の角度まで慣性をかける
	rotModel.y += fDiffRotY * RATE_ROTATE_MODEL;
	if (rotModel.y > D3DX_PI)
	{
		rotModel.y -= D3DX_PI * 2.0f;
	}
	if (rotModel.y < -D3DX_PI)
	{
		rotModel.y += D3DX_PI * 2.0f;
	}

	/// 位置移動
	posModel.x += moveModel.x;
	posModel.z += moveModel.z;


	// 移動量に慣性をかける
	moveModel.x += (0.0f - moveModel.x) * RATE_MOVE_MODEL;
	moveModel.z += (0.0f - moveModel.z) * RATE_MOVE_MODEL;

	if (KeyBoard::IsPress(DIK_A))
	{
		posModel.x += RATE_MOVE_MODEL;
	}
	if (KeyBoard::IsPress(DIK_D))
	{
		posModel.x -= RATE_MOVE_MODEL;
	}


	//何も抵抗を考えない場合
	if (flag == true)
	{
		if (posModel.y > -100)
		{
			moveGravity += Gravity;
			moveModel.y += moveGravity;
		}
	}

	if (KeyBoard::IsPress(DIK_G))
	{
		flag = true;
	}


	
#if 0
	// 範囲チェック
	if (g_posModel.x < -310.0f)
	{
		g_posModel.x = -310.0f;
	}
	if (g_posModel.x > 310.0f)
	{
		g_posModel.x = 310.0f;
	}
	if (g_posModel.z < -310.0f)
	{
		g_posModel.z = -310.0f;
	}
	if (g_posModel.z > 310.0f)
	{
		g_posModel.z = 310.0f;
	}
#endif

	if (KeyBoard::IsPress(DIK_RETURN))
	{// リセット
		posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		moveModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotDestModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
#if 0
	p_CharCamera = GetCharCam();

	g_pD3DDevice = GetD3DDevice();
	// ワールド座標行列作成
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&rot_matrix, angle.y, angle.x, angle.z);
	D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, scale.y);

	world_matrix *= rot_matrix * trans_matrix;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (pmodel != NULL)
	{
		pmodel->Draw();
	}

	//p_CharCamera->Init = D3DXVECTOR3(position.x, position.y, position.z);
	//p_CharCamera->Init = D3DXVECTOR3(position.x, position.y, position.z);

	if (KeyBoard::IsTrigger(DIK_W))
	{
		position.y += 1.0f;
		position.z += 1.0f;
	}
#endif

}


void Character::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorldModel);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotModel.y, rotModel.x, rotModel.z);
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &mtxRot);

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, posModel.x, moveModel.y, posModel.z);
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &mtxTranslate);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldModel);
	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		//テクスチャの設定
		pDevice->SetTexture(0, m_pTextureModel);
		//描画
		m_pMeshModel->DrawSubset(nCntMat);

	}
	//マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}


