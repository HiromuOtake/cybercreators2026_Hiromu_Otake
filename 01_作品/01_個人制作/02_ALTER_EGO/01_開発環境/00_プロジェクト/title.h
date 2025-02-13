//==============================================
//
// ALTER_EGO[title.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "object3D.h"
#include "bg.h"
#include "player.h"
#include "camera.h"

class CTitle : public CScene
{
public:
	CTitle();							// コンストラクタ
	~CTitle()override;					// デストラクタ
	HRESULT Init()override;				// 初期設定
	void Uninit()override;				// 終了処理
	void Update()override;				// 更新処理
	void Draw()override;				// 描画処理
	static CCamera* GetCamera();
	static const int m_BLOCK_BESIDE = 30;
	static const int m_BLOCK_VERTICAL = 15;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	int m_nType[m_BLOCK_BESIDE][m_BLOCK_VERTICAL];
	CBg* m_pBg;
	static CPlayer* m_pPlayer;
	static CCamera* m_pCamera;
};

#pragma once
