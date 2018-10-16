//------------------------------------------------------------------------------
/// @file
/// @brief    メイン
/// @author   ys
///
/// @copyright  Copyright 2016 矢伝翔平

//------------------------------------------------------------------------------

#include "DxLib.h"

#include "Keyboard.hpp"
#include "SceneMng.hpp"

#include <memory>


static int FrameStartTime;
static int FPS_60 = 1000 / 60;
static bool isFullSc = false;
static bool isPlay = true;


// @brief	60fpsを保たせる処理
static void FPSMng();

// @brief	ウィンドウ初期設定
static void Initialize();

// @brief	いつでも受け付ける設定
static void DynamicConfig();


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Initialize();
	std::unique_ptr<SceneMng>	sceneMng(new SceneMng);

	// ゲーム--------------------------------------------------------------------------------------
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && isPlay)
	{
		FPSMng();
		Keyboard_Update();										// キー入力状況更新
		DynamicConfig();
		sceneMng->Update();
		sceneMng->Draw();
	}
	DxLib_End();												// ＤＸライブラリ使用の終了処理
	return 0;
}


void FPSMng()
{
	while (GetNowCount() - FrameStartTime < FPS_60) {}		// 1/60 秒まで待つ
	FrameStartTime = GetNowCount();							// 現在のカウントを保存
}


void Initialize()
{
	SetGraphMode(850, 650, 32), ChangeWindowMode(TRUE), DxLib_Init();							// ウィンドウ初期設定(VGA),DxLib起動
	SetDrawScreen(DX_SCREEN_BACK);																// 裏画面処理
	SetMainWindowText("演習");																	// タイトルを設定
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);											// 画面モード変更後、素材メモリをリセットしない
	SetWaitVSyncFlag(FALSE);																	// 垂直同期信号を待たない
	FrameStartTime = GetNowCount();																// 開始時間を設定
}


void DynamicConfig()
{
	// メインループを抜ける
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)	isPlay = false;
}
// EOF
