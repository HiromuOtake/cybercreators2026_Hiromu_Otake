//==============================================
//
// 3Dスクロールアクション[billboard.h]
// Author: hiromu otake
//
//==============================================

#include "main.h"
#include "object.h"

#ifndef  _BILLBOARD_H_          //このマクロ定義がされていなかったら
#define  _BILLBOARD_H_          //２重インクルード防止のマクロ定義

class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = 4);
	~CBillboard();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3& GetPosOld();
	D3DXVECTOR3& GetRot();
	D3DXVECTOR3& GetSize();
	D3DXVECTOR3& GetMin();
	D3DXVECTOR3& GetMax();
	void SetDeath()override;
	static constexpr float m_BILLBOARD_SIZE = 20.0f;
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;
	int m_nNumVtx;						// 頂点数
	DWORD m_sizeFVF;					// 頂点フォーマットのサイズ
	LPD3DXMESH m_pMesh;					// メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;			// マテリアルへのポインタ
};

#endif 