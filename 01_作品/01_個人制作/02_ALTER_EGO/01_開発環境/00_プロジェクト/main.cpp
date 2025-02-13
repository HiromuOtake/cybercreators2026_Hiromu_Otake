//======================================================
//
// ALTER_EGO [main.cpp]
// Auther : 大竹熙
//
//======================================================

#include "main.h"
#include "manager.h"

// グローバル変数
CManager* g_pManager = nullptr;
int g_nCntFPS = 0;
bool g_isFullscreen = false;			// ウィンドウを切り替えるためのフラグ
RECT g_windowRect;

//=================
//メイン関数
//=================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef FIND_MEM_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),								//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,										//ウィンドウのスタイル
		WindowProc,										//ウィンドウプロシージャ
		0,												// 0 にする(通常は使用しない)
		0,												//上と同じ
		hInstance,										//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),					//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),						//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),						//クライアント領域の背景色
		NULL,											//メニューバー
		CLASS_NAME,										//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),					//ファイルのアイコン
	};

	HWND hWnd;			//ウィンドウハンドル(識別子)
	MSG  msg;			//メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//画面サイズの構造体

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,			//拡張ウィンドウスタイル
		CLASS_NAME,						//ウィンドウクラスの名前
		WINDOW_NAME,					//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,			//ウィンドウスタイル
		CW_USEDEFAULT,					//ウィンドウの左上X座標
		CW_USEDEFAULT,					//ウィンドウの左上Y座標
		(rect.right - rect.left),		//ウィンドウの幅
		(rect.bottom - rect.top),		//ウィンドウの高さ
		NULL,							//親ウィンドウのハンドル
		NULL,							//メニューハンドルまたはウィンドウID
		hInstance,						//インスタンスハンドル
		NULL);							//ウィンドウ作成データ

	// 生成＆初期化
	g_pManager = new CManager();		// レンダラー生成
	g_pManager->Init(hInstance, hWnd, TRUE);

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);			//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);					//クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);		//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);		//ウィンドウプロシージへメッセージを送出
			}
		}
		else
		{//DorectXの処理
			//更新処理
			g_pManager->Update();
			//描画処理
			g_pManager->Draw();
		}
	}
	//終了処理
	g_pManager->Uninit();
	delete g_pManager;


	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//======================================
//ウィンドウプロシージャ
//======================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;   //返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:			//ウィンドウ破壊
		//WM_OUIT メッセージを送る
		PostQuitMessage(0);
		break;

	case WM_CLOSE:				//閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			//ウィンドウを破壊する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;			//0を返さないと終了してしまう
		}
		break;

	case WM_KEYDOWN:			//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:			//[ESK]キーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウを破壊する
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);		//既定の処理を返す
}

//=========================================
// ウィンドウをフルスクリーンに変える処理
//=========================================
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}