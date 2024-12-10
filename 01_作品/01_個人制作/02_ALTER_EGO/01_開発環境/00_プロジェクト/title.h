//==============================================
//
// 3Dスクロールアクション[title.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "object3D.h"

class CTitle : public CScene
{
public:
	// 画面の種類
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;
	CTitle();							// コンストラクタ
	~CTitle()override;					// デストラクタ
	HRESULT Init()override;				// 初期設定
	void Uninit()override;				// 終了処理
	void Update()override;				// 更新処理
	void Draw()override;				// 描画処理
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
};

#pragma once
