//==============================================
//
// ALTER_EGO[tutorial.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "number.h"

class CTutorial : public CScene
{
public:
	CTutorial();							// コンストラクタ
	~CTutorial()override;					// デストラクタ
	HRESULT Init()override;				// 初期設定
	void Uninit()override;				// 終了処理
	void Update()override;				// 更新処理
	void Draw()override;				// 描画処理
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	//CNumber* m_pNumber;
};

#pragma once
