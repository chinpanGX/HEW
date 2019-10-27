/*=======================================

	[main.cpp]
	Author : 出合翔太

========================================*/

//インクルードファイル
#include "main.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "field.h"		//1枚ポリゴン
#include "debugproc.h"	//デバッグ表示用
#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

//プラグマコメント：リンカーにライブラリファイルを指定
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")


//	定数定義
#define CLASS_NAME     "GameWindow"       // ウインドウクラスの名前
#define WINDOW_CAPTION "ゲームウィンドウ" // ウィンドウの名前


//   グローバル変数宣言
static	HWND g_hWnd;            // ウィンドウハンドル
bool	g_bDispDebug = true;	// デバッグ表示ON/OFF


//	プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ(コールバック関数)
static bool WindowInit(HINSTANCE hInstance, int nCmdShow);		//ウィンドウ関数
static bool Initialize(HINSTANCE hInst);	// ゲームの初期化
static void Finalize();					// ゲームの終了処理
static void Update();					// ゲームの更新処理
static void Draw();						// ゲームの描画関数


//　メイン関数：エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 使用しない一時変数を明示
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//表示するウィンドウの定義、登録、表示
	if (!WindowInit(hInstance, nCmdShow))		// InitApp関数を呼び出し、
	return false;								// 正常に終了すれば次にメッセージループへ

	// ゲームの初期化
	Initialize(hInstance);

	//DWORD型…unsigned lond型（符号なし）
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;	//初期値を0にすることを忘れないように（FPSを取得したときゴミが混ざること防ぐため）

	// Windowsゲーム用メインループ
	MSG msg = {}; 
	while (WM_QUIT != msg.message)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// メッセージがある場合はメッセージ処理を優先
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			dwCurrentTime = timeGetTime();
		
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			//!	1フレームごとに実行（垂直同期を待たない）60FPSに固定　-> モニターによって実行速度の変化を防ぐ
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// ゲームの終了処理
	Finalize();

	return (int)msg.wParam;
}

// ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
	//キーを押したとき
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)//ESCキー 
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSEメッセージの送信
		}
		break;

	//カーソルの設定
	case WM_SETCURSOR:
		SetCursor(NULL);
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd); // 指定のウィンドウにWM_DESTROYメッセージを送る
		return 0; // DefWindowProc関数にメッセージを流さず終了することによって何もなかったことにする

	case WM_DESTROY: // ウィンドウの破棄メッセージ
		PostQuitMessage(0); // WM_QUITメッセージの送信
		return 0;
	};

	// 通常メッセージ処理はこの関数に任せる
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
	

//ウィンドウ関数
static bool WindowInit(HINSTANCE hInstance, int nCmdShow)
{
	// ウィンドウクラス構造体
	WNDCLASSEX wc;

	// ウィンドウクラスを定義する
	wc.cbSize = sizeof(WNDCLASSEX);						// WNDCLASSEX構造体のサイズを設定
	wc.style = NULL;									// ウィンドウスタイル（デフォルト）
	wc.lpfnWndProc = WndProc;							// ウィンドウプロシージャの指定
	wc.cbClsExtra = 0;									// 通常は使わない（０にしておく）
	wc.cbWndExtra = 0;									// 通常は使わない（０にしておく）
	wc.lpszClassName = CLASS_NAME;						// クラス名の設定
	wc.hInstance = hInstance;							// インスタンスハンドルの指定
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	// ウインドウのクライアント領域の背景色を設定
	wc.hIcon = NULL;									// ラージアイコン（なし）
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// カーソルスタイル
	wc.lpszMenuName = NULL;								// メニュー（なし）
	wc.hIconSm = NULL;									// スモールアイコン（なし）

	// ウィンドウクラスの登録
	if (!RegisterClassEx(&wc)) return false;

	//ウィンドウを生成する
	if (WINMODE)//TRUEのとき
	{
		//"	ウィンドウモード
		g_hWnd = CreateWindow
		(
			CLASS_NAME,             // ウィンドウクラスの名前
			WINDOW_CAPTION,         // ウィンドウタイトル
			WS_OVERLAPPEDWINDOW,    // ウィンドウスタイル
			0,                      // ウィンドウの左角Ｘ座標
			0,                      // ウィンドウの左角Ｙ座標
			CW_USEDEFAULT,          // ウィンドウの幅
			CW_USEDEFAULT,          // ウィンドウの高さ
			NULL,                   // 親ウィンドウ（なし）
			NULL,                   // メニュー（なし）
			hInstance,              // このプログラムのインスタンスのハンドル
			NULL                    // 追加引数（なし）
		);

		RECT wRect, cRect;  // ウィンドウ全体の矩形、クライアント領域の矩形
		int ww, wh;         // ウィンドウ全体の幅、高さ
		int cw, ch;         // クライアント領域の幅、高さ

		// ウィンドウ全体の幅・高さを計算
		GetWindowRect(g_hWnd, &wRect);
		ww = wRect.right - wRect.left;
		wh = wRect.bottom - wRect.top;
		// クライアント領域の幅・高さを計算
		GetClientRect(g_hWnd, &cRect);
		cw = cRect.right - cRect.left;
		ch = cRect.bottom - cRect.top;
		// クライアント領域以外に必要なサイズを計算
		ww = ww - cw;
		wh = wh - ch;
		// ウィンドウ全体に必要なサイズを計算
		ww = SCREEN_WIDTH + ww;
		wh = SCREEN_HEIGHT + wh;

		// 計算した幅と高さをウィンドウに設定
		SetWindowPos(g_hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);
	}
	else//FALSEのとき
	{
		//"	フルスクリーンモード
		g_hWnd = CreateWindow
		(
			CLASS_NAME,             // ウィンドウクラスの名前
			WINDOW_CAPTION,         // ウィンドウタイトル
			WS_VISIBLE | WS_POPUP,  // ウィンドウスタイル
			0,                      // ウィンドウの左角Ｘ座標
			0,                      // ウィンドウの左角Ｙ座標
			SCREEN_WIDTH,           // ウィンドウの幅
			SCREEN_HEIGHT,          // ウィンドウの高さ
			NULL,                   // 親ウィンドウ（なし）
			NULL,                   // メニュー（なし）
			hInstance,              // このプログラムのインスタンスのハンドル
			NULL                    // 追加引数（なし）
		);
	}

	ShowWindow(g_hWnd, nCmdShow); // ウィンドウを表示
	ValidateRect(g_hWnd, 0);      // WM_PAINTが呼ばれないようにする
	UpdateWindow(g_hWnd);         // ウィンドウの更新

	return true;              // InitApp関数の正常終了
}

//　初期化処理関数
bool Initialize(HINSTANCE hInst)
{
	//シードの初期化
	srand((unsigned int)time(NULL));

	// ゲームの初期化(Direct3Dの初期化)
	if (!D3D_Initialize(g_hWnd)){
		// ゲームの初期化に失敗した
		return false;
	}
	// キーボードの初期化
	if (!Input::KB_Init(hInst, g_hWnd))
	{
		return false;
	}
	//	ゲームポッドの初期化
	if (!Input::GP_Init(hInst, g_hWnd))
	{
		return false;
	}

	//全テクスチャファイルのロード
	Texture_Load();

	// デバッグ表示処理 
	DebugProc_Initialize();

	// カメラの初期化処理
	Camera_Initialize();

	// ライトの初期化処理
	Light_Initialize();

	// 地面の初期化処理
	Field_Initialize();

	return true;
}

//　終了処理関数
void Finalize(void)
{
	// カメラの終了処理
	Camera_Finalize();

	// ライトの終了処理
	Light_Finalize();

	// 地面の終了処理
	Field_Finalize();

	// テクスチャの解放
	Texture_Release();

	// DirectInputの終了処理
	Input::Uninit();

	// ゲームの終了処理(Direct3Dの終了処理)
	D3D_Finalize();
}

// 更新処理関数
void Update(void)
{
	//キーボードの状態を更新する
	Input::KB_Update();

	//ゲームパッドの状態を更新する
	Input::GP_Update();

	// カメラの更新処理
	Camera_Update();

	// ライトの更新処理
	Light_Update();

	// 地面の更新処理
	Field_Update();

}

// 描画処理関数
void Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = GetD3DDevice();

	// 画面のクリア
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(50, 50, 50, 255), 1.0f, 0);

	// 描画バッチ命令の開始
	pD3DDevice->BeginScene();


	// カメラの設定
	Camera_SetCamera();

	// 地面の描画処理
	Field_Draw();

	// デバッグ表示の描画処理
	if (g_bDispDebug)
	{
		DebugProc_Draw();
	}

	// 描画バッチ命令の終了
	pD3DDevice->EndScene();

	// バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定による）
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//ウィンドウハンドルのゲッター
HWND GetHWND()
{
	return g_hWnd;
}


double frand() 
{
	return (double)rand() / RAND_MAX;
}
