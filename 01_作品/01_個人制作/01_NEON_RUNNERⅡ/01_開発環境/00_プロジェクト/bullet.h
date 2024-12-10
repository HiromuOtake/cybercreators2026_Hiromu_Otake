//==============================================
//
// 3Dスクロールアクション[bullet.h]
// Author: hiromu otake
//
//==============================================

#ifndef _BULLET_H_
#define _BULLET_H_

#include "manager.h"
#include "billboard.h"

class CBullet : public CBillboard
{
public:
	CBullet();
	~CBullet();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	static HRESULT Load();
	static void Unload();
	void SetUse(bool bUse);
	D3DXVECTOR3* GetMove();
	void SetDeath()override;
	static const int m_MAXLIFE = 60;
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;						// 頂点座標
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_move;						// 移動量
	D3DXMATRIX m_mtxWorld;
	int m_nLife;							// 弾の持続時間
	bool m_bUse;							// 弾を使ってるかいないか
};

#endif 