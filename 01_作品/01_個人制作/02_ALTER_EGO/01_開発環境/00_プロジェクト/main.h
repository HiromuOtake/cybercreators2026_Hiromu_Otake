//======================================================
//
// ALTER_EGO [main.h]
// Auther : 大竹熙
//
//======================================================

#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION  (0x0800)     //ビルド時の警告対処用マクロ

#include "d3dx9.h"
#include "dinput.h"						//入力処理に必要
#include"xaudio2.h"                       //サウンド処理に必要
#include "Xinput.h"						//ジョイパッド処理に必要

//ライブラリのリンク 
#pragma comment(lib,"d3d9.lib")			//描画処理に必要
#pragma comment(lib,"d3dx9.lib")		//[ d3d9.;ib ]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")         //システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必要
#pragma comment(lib,"xinput.lib")		//ジョイパッドの処理に必要
#pragma comment(lib,"winmm.lib")		//ランダムに必要

//マクロ定義
#define SCREEN_WIDTH        (1280)       //ウィンドウの幅
#define SCREEN_HEIGHT       (720)        //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)	// 頂点フォーマットの定義
#define CLASS_NAME          "WindowClass"          //ウィンドウクラスの名前
#define WINDOW_NAME         "ALTER EGO"              //ウィンドウの名前(キャプションに表示)

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#if 0
#define FIND_MEM_LEAKS
#endif
#endif // _DEBUG

#ifdef FIND_MEM_LEAKS
#define new new (_NORMAL_BLOCK , __FILE__, __LINE__)
#else
#define new new
#endif // FIND_MEM_LEAKS

// stl

//==============================================
// 3Dポリゴン構造体
//==============================================
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
};

//==============================================
// 2Dポリゴン構造体
//==============================================
struct VERTEX_2D
{
	D3DXVECTOR3 pos;     //頂点座標
	float rhw;           //座標変換用係数(1.0で固定)
	D3DCOLOR col;        //頂点カラー
	D3DXVECTOR2 tex;     //テクスチャ座標
};

// 頂点フォーマットを定義するための構造体
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;  // 頂点の位置
	D3DXVECTOR2 texCoord;  // テクスチャ座標
};

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ToggleFullscreen(HWND hWnd);	// ウィンドウをフルスクリーンにする

#endif // !_MAIN_H_
#pragma once