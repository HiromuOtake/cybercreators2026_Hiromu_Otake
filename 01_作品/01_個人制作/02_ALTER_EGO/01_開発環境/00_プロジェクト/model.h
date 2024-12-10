//==============================================
//
// 3Dスクロールアクション[model.h]
// Author: hiromu otake
//
//==============================================

#include "main.h"

class CModel
{
public:
	static const int m_MAXTEXTURE = 126;
	typedef struct
	{
		LPD3DXBUFFER m_pBuffMat;		// マテリアルへのポインタ
		DWORD m_dwNumMat;				// マテリアルの数
		LPD3DXMESH m_pMesh;				// メッシュへのポインタ
		LPDIRECT3DTEXTURE9 m_pTexture[m_MAXTEXTURE];
	}ModelInfo;
	CModel();
	~CModel();
	void Unload();								// モデル破棄
	int Regist(const char* pTextureName);		// モデル登録
	ModelInfo GetAddress(int nIdx);	// モデル取得
	LPD3DXBUFFER GetBuffMat(int nIdx);
	DWORD GetNumMat(int nIdx);
	LPD3DXMESH GetMesh(int nIdx);
	LPDIRECT3DTEXTURE9* GetTexture(int nIdx);
	static const int m_MAXMODEL = 126;
	static const int m_MAXSENTENCE = 126;
private:
	ModelInfo m_pModelList[m_MAXMODEL];
	char m_pModelName[m_MAXMODEL][m_MAXSENTENCE];
	int m_nNumAll;
};

#pragma once

