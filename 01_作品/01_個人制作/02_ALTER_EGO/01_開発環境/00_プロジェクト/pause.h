//==============================================
//
// ALTER_EGO[pause.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "object2D.h"

class CGame;

class CPause : public CObject2D
{
public:
	CPause(int nPriority = 0);
	~CPause();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SelectPause(CGame* game);
	static CPause* Create();							// ポーズ画面生成
	void SetDeath()override;
	static const int m_MAX_PAUSE = 3;
	static constexpr float m_PAUSE_UI_WIDTH = 400.0f;	// ポーズUIのサイズ(横)
	static constexpr float m_PAUSE_UI_HEIGHT = 60.0f;	// ポーズUIのサイズ(縦)
	static constexpr float m_INITIAL_POINT = 300.0f;	// ポーズUIの初期位置
	static constexpr float m_SHIFT = 75.0f;				// ポーズUIをずらす
	static constexpr float m_PAUSE_BG_Z = 1.0f;			// ポーズBGのZの位置
	static constexpr float m_PAUSE_CORRECTION = 0.75f;	// ポーズの位置の補正
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	CInputKeyboard* m_Keyboard;
	CInputJoyPad* m_JoyPad;
	CObject2D* m_pPauseOptions[3];			// 各ポーズオプションのCObject2Dオブジェクト
	CObject2D* m_nTexIdx;					// テクスチャID
	CObject2D* m_nPauseBGTex;				// ポーズの背景用テクスチャ
	int m_nSelectPause;						// 選択中のポーズメニュー番号
};

#pragma once