//======================================================
//
// 3Dスクロールアクション [object2D.h]
// Auther : 大竹熙
//
//======================================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"
#include <cassert>

class CObject2D : public CObject
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	//頂点座標
		float rhw;			//座標変換用係数(1.0で固定)
		D3DCOLOR col;		//頂点カラー
		D3DXVECTOR2 tex;	//テクスチャ座標
	}VERTEX_2D;
	CObject2D(int nPriority = 1);
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetPos(D3DXVECTOR3 pos);
	void SetWidthHeight(float fWidth, float fHeight);
	void SetColor(float fColor);
	void SetTexture(float fTexture);
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3* GetPosOld();
	D3DXVECTOR3* GetRot();
	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;						//頂点座標
	D3DXVECTOR3 m_posold;					//頂点座標
	D3DXVECTOR3 m_rot;						//向き
	D3DXVECTOR3 m_move;						//移動
	float m_fLengthPlayer;				//対角線の長さ
	float m_fAnglePlayer;				//対角線の角度
	float m_fWidth;
	float m_fHeight;
	float m_colorFade;					// 色
	float m_fTexture;
};

#endif // !_OBJECT2D_H_
#pragma once
