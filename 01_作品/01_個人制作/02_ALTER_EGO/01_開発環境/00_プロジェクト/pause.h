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
	static CPause* Create();				// ポーズ画面生成
	void SetDeath()override;
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