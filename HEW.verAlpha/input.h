/*==================================
	
	[input.h]
	Author : 出合翔太

==================================*/

#pragma once

//インクルードファイル
#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

//マクロ定義	
#define	NUM_KEY_MAX			(256)
//ゲームパッド用の設定値
#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX		1000			// 有効範囲の最大値
#define RANGE_MIN		-1000			// 有効範囲の最小値

//ゲームパッド（XboxとPS4）の入力のマクロ
//	緑	両方	
//!	赤　Xboxのみ
//"	青	PS4のみ	

#define LEFTSTICK_UP			0x00000001l	//	Xbox＆PS4:左スティック上(.IY<0)
#define LEFTSTICK_DOWN			0x00000002l	//	Xbox＆PS4:左スティック下(.IY>0)
#define LEFTSTICK_LEFT			0x00000004l	//	Xbox＆PS4:左スティック左(.IX<0)
#define LEFTSTICK_RIGHT			0x00000008l	//	Xbox＆PS4:左スティック右(.IX>0)
#define XboxRIGHTSTICK_UP		0x04000000l	//! Xbox:右スティック上(.lRz<16383)
#define XboxRIGHTSTICK_DOWN		0x10000000l	//! Xbox:右スティック下(.lRz>49150)
#define XboxRIGHTSTICK_LEFT		0x20000000l	//! Xbox:右スティック右(.lZ<16383)
#define XboxRIGHTSTICK_RIGHT	0x40000000l	//! Xbox:右スティック左(.lZ>49150)
#define PS4RIGHTSTICK_UP		0x00000010l	//" PS4:右スティック上(.lRz<16383)
#define PS4RIGHTSTICK_DOWN		0x00000020l	//" PS4:右スティック下(.lRz>49150)
#define PS4RIGHTSTICK_RIGHT		0x00000040l //" PS4:右スティック右(.lZ<16383)
#define PS4RIGHTSTICK_LEFT		0x00000080l //" PS4:右スティック左(.lZ>49150)
#define TRIGGER_LT				0x00000100l //! Xbox:LTトリガー(.lZ>49150)
#define TRIGGER_RT				0x00000200l //! Xbox:RTトリガー(.lZ<16383)
#define TRIGGER_L2				0x00000400l //" PS4 :L2トリガー(.lRx>10000)
#define TRIGGER_R2				0x00000800l //" PS4 :R2トリガー(.lRy>10000)
#define BUTTON_1				0x00008000l	//	Xbox:Ｙボタン	PS4：△タン(.rgbButtons[3]&0x80)
#define BUTTON_2				0x00004000l	//	Xbox:Ｘボタン	PS4：〇ボタン(.rgbButtons[2]&0x80)
#define BUTTON_3				0x00002000l	//	Xbox:Ｂボタン	PS4：×ボタン(.rgbButtons[1]&0x80)
#define BUTTON_4				0x00001000l	//	Xbox:Ａボタン	PS4：□ボタン(.rgbButtons[0]&0x80)
#define BUTTON_LB				0x00010000l	//	Xbox:LBボタン	PS4：L1ボタン(.rgbButtons[4]&0x80)
#define BUTTON_RB				0x00020000l	//	Xbox:RBボタン	PS4：R1ボタン(.rgbButtons[5]&0x80)
#define BUTTON_BACK				0x00040000l	//	Xbox:BACKボタン	PS4：OPTIONボタン(.rgbButtons[6]&0x80)
#define BUTTON_START			0x00080000l	//	XboxSTARTボタン	PS4：SHAREボタン(.rgbButtons[7]&0x80)
#define BUTTON_L3				0x00100000l	//! Xbox:L3ボタン(.rgbButtons[8]&0x80)
#define BUTTON_R3				0x00200000l	//! Xbox:R3ボタン(.rgbButtons[9]&0x80)
#define BUTTON_UP				0x00400000l	//	Xbox＆PS4:方向キー上(rgdwPOV[0] = 0)
#define BUTTON_DOWN				0x00800000l //	Xbox＆PS4:方向キー下(.rgdwPOV[0] = 18000)
#define BUTTON_LEFT				0x01000000l //	Xbox＆PS4:方向キー左(.rgdwPOV[0] = 27000)
#define BUTTON_RIGHT			0x02000000l //	Xbox＆PS4:方向キー右(.rgdwPOV[0] = 9000)
#define GAMEPADMAX				4			//	同時に接続するジョイパッドの最大数をセット

//#	Inputクラス
/* 入力情報の管理をするクラス　*/
class Input
{
private:
	//# キーボード
	static LPDIRECTINPUTDEVICE8	g_pDevKeyboard;
	static BYTE					g_aKeyState[NUM_KEY_MAX];
	static BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];
	static BYTE					g_aKeyStateRelease[NUM_KEY_MAX];

	//# ゲームパッド
	static LPDIRECTINPUTDEVICE8	g_pGamePad[GAMEPADMAX];		// パッドデバイス
	static DWORD				g_padState[GAMEPADMAX];		// パッド情報（複数対応）
	static DWORD				g_padTrigger[GAMEPADMAX];
	static int					g_padCount;					// 検出したパッドの数
public:
	//#	キーボード
	static bool KB_Init(HINSTANCE hInstance, HWND hWnd);	//キーボードの初期化処理
	static void Uninit();									//キーボードの終了処理
	static void KB_Update();								//キーボードの更新処理
	static bool KB_IsPress(int nKey);						//キーボードを押している間
	static bool KB_IsTrigger(int nKey);						//キーボードを押した瞬間
	static bool KB_IsRelease(int nKey);						//キーボードを離した瞬間
	 
	//#	ゲームパッド
	static BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);
	static bool GP_Init(HINSTANCE hInstance, HWND hWnd);	//ゲームパッドの初期化
	//static void GP_Uninit();								//ゲームパッドの終了処理
	static void GP_Update();								//ゲームパッドの更新処理
	static BOOL GP_IsPress(int padNo, DWORD button);		//ゲームパッドのボタンを押している間
	static BOOL GP_IsTrigger(int padNo, DWORD button);		//ゲームパッドのボタンを押した瞬間
};
