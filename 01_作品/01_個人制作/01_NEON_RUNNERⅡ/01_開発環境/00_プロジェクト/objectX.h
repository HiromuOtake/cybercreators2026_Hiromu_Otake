//==============================================
//
//3Dスクロールアクション[objectX.h]
//Author: hiromu otake
//
//==============================================

#include "manager.h"

class CObjectX :public CObject
{
public:
	CObjectX(int nPriority = 3);
	~CObjectX();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetMove(D3DXVECTOR3 move);
	void ModelPath(std::string sPath);
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3& GetPosOld();
	D3DXVECTOR3& GetRot();
	D3DXVECTOR3& GetMove();
	D3DXVECTOR3& GetSize();
	D3DXVECTOR3& GetMin();
	D3DXVECTOR3& GetMax();
	D3DXMATRIX& GetMatrix() { return m_mtxWorld; }
	LPD3DXBUFFER& GetBuffMat() { return m_pBuffMat; }
	LPD3DXMESH& GetMesh() { return m_pMesh; }					// メッシュへのポインタ
	const DWORD& GetNumMat() { return m_dwNumMat; }			// マテリアルの数
	LPDIRECT3DTEXTURE9* GetTex() { return m_pTexture; };
	//void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh, LPDIRECT3DTEXTURE9* Texture);
	static const int m_MAXTEXTURE = 126;
	static constexpr float m_HALF_SIZE = 0.5f;			// モデルを半分のサイズ
	static constexpr float m_HALF_SIZE_LOOSE = 0.1f;			// モデルを半分のサイズ
private:
	LPDIRECT3DTEXTURE9* m_pTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;
	D3DXMATRIX m_mtxWorld;
	int m_nNumVtx;			// 頂点数
	DWORD m_sizeFVF;			// 頂点フォーマットのサイズ
	BYTE* m_pVtxBuff;			// 頂点バッファへのポインタ
	LPD3DXMESH m_pMesh;					// メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;		// マテリアルへのポインタ
	DWORD m_dwNumMat;			// マテリアルの数
};
#pragma once
