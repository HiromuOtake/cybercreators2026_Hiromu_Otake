//==============================================
//
//ALTER_EGO[objectX.h]
//Author: hiromu otake
//
//==============================================

#include "manager.h"

class CObjectX : public CObject
{
protected:
	float m_fRotation;
public:
	CObjectX(int nPriority = 3);
	~CObjectX();
	HRESULT Init()override;
	void Uninit()override;
	virtual void Update()override;
	void Draw()override;
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetScale(D3DXVECTOR3 scale);
	void SetMove(D3DXVECTOR3 move);
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetRotation(float rotation) { m_fRotation = rotation; }  // 回転を設定
	float GetRotation() const { return m_fRotation; }
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3& GetPosOld();
	D3DXVECTOR3& GetRot();
	D3DXVECTOR3& GetMove();
	D3DXVECTOR3& GetSize();
	D3DXVECTOR3& GetMin();
	D3DXVECTOR3& GetMax();
	D3DXMATRIX& GetMatrix();
	LPD3DXBUFFER& GetBuffMat();
	LPD3DXMESH& GetMesh();									// メッシュへのポインタ
	const DWORD& GetNumMat();								// マテリアルの数
	void BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh);
	static const int m_MAXTEXTURE = 126;
	static constexpr float m_HALF_SIZE = 0.5f;			// モデルを半分のサイズ
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	virtual void SetMatColor(D3DMATERIAL9* pMat,int nMatIdx);

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;
	D3DXMATRIX m_mtxWorld;
	int m_nNumVtx;				// 頂点数
	DWORD m_sizeFVF;			// 頂点フォーマットのサイズ
	BYTE* m_pVtxBuff;			// 頂点バッファへのポインタ
	LPD3DXMESH m_pMesh;			// メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;	// マテリアルへのポインタ
	DWORD m_dwNumMat;			// マテリアルの数
};
#pragma once
