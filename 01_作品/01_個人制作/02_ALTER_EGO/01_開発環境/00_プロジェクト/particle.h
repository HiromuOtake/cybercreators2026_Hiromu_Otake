////==============================================
////
//// 3Dスクロールアクション[bullet.h]
//// Author: hiromu otake
////
////==============================================
//
//#ifndef _BULLET_H_
//#define _BULLET_H_
//
//#include <d3dx9.h>
//#include "manager.h"
//#include "billboard.h"
//
//class CParticle : public CBillboard
//{
//public:
//	CParticle();
//	~CParticle();
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size, float speed, D3DXCOLOR color);
//	static HRESULT Load();
//	static void Unload();
//	void SetUse(bool bUse);
//	void SetSize(float size);
//	void SetSpeed(float speed);
//	void SetColor(D3DXCOLOR color);
//	D3DXVECTOR3* GetMove();
//	void SetDeath()override;
//	static const int m_MAXLIFE = 60;
//	int m_nLife;							// 弾の持続時間
//private:
//	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
//	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
//	D3DXVECTOR3 m_pos;						// 頂点座標
//	D3DXVECTOR3 m_rot;						// 向き
//	D3DXVECTOR3 m_move;						// 移動量
//	D3DXMATRIX m_mtxWorld;
//	D3DXCOLOR m_color;						// パーティクルの色
//	float m_size;							// パーティクルの大きさ
//	float m_speed;							// パーティクルの速さ
//	bool m_bUse;							// 弾を使ってるかいないか
//};
//
//#endif 