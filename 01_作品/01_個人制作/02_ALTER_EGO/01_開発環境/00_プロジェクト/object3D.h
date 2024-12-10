//======================================================
//
// 3Dスクロールアクション [object3D.h]
// Auther : 大竹熙
//
//======================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;						//頂点座標
	D3DXVECTOR3 m_rot;						//向き
	D3DXMATRIX m_mtxWorld;
};

#endif // !_OBJECT3D_H_
#pragma once
