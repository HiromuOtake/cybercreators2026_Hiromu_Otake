//==============================================
//
//ALTER_EGO[modelparts.h]
//Author: hiromu otake
//
//==============================================

#include "objectX.h"

class CModelParts
{
public:
//==============================================
//モデルの構造体
//==============================================
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nIdx;
		int nIdxModelParent;    // 親のインデックス
	}Parts;

	static const int m_MAXTEXTURE = 126;

	typedef struct
	{
		LPD3DXBUFFER m_pBuffMat;		// マテリアルへのポインタ
		DWORD m_dwNumMat;				// マテリアルの数
		LPD3DXMESH m_pMesh;				// メッシュへのポインタ
		bool m_bUse;
	}ModelInfo;

	CModelParts();
	~CModelParts();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CModelParts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char* aModel);
	void SetParent(CModelParts* pModelParts);
	void BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh);
	int Regist(const char* pTextureName);		// モデル登録
	D3DXMATRIX GetWoarldMatrix();
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3& GetSize();
	D3DXVECTOR3& GetMin();
	D3DXVECTOR3& GetMax();
	D3DXMATRIX& GetMatrix();
	int& GetIdx();
	static const int m_MAXMODEL = 126;
	static const int m_MAXSENTENCE = 126;
	static const int m_MAX_LETTER = 496;
	static const int m_NUM_MODEL_PARTS = 15;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nIdx;
	int m_nIdxParents;
private:
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_size;
	int m_nNumVtx;			// 頂点数
	DWORD m_sizeFVF;			// 頂点フォーマットのサイズ
	BYTE* m_pVtxBuff;			// 頂点バッファへのポインタ
	LPD3DXMESH m_pMesh;					// メッシュへのポインタ
	D3DXMATRIX m_mtxWorld;
	CModelParts* m_pParent;
	ModelInfo m_pModelList[m_MAXMODEL];
	char m_pModelName[m_MAXMODEL][m_MAXSENTENCE];
	int m_nModelIdx;
	int m_nNumAll;
};

#pragma once