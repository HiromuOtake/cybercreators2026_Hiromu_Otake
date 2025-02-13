//==============================================
//
// ALTER_EGO[bg.cpp]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "object2D.h"
#include <d3dx9.h>

// 頂点フォーマット
struct VTX_2D
{
	D3DXVECTOR3 pos; // 座標
	float rhw;       // 投影座標変換
	float tu, tv;    // テクスチャ座標
	float color;     // 透明度または色
};

class CBg : public CObject2D
{
public:
	CBg(int nPriority = 0);
	~CBg();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static void DrawTexture(int textureID, D3DXVECTOR2 position, D3DXVECTOR2 scale = { 1.0f, 1.0f }, float alpha = 1.0f);
	static CBg* Create(CScene::MODE mode);
	void SetDeath()override;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャ
	D3DXMATRIX m_mtxWorld;
	int m_nTexIdx;
	float m_texScrollSpeed01;
	float m_texScrollSpeed02;
};

#pragma once
