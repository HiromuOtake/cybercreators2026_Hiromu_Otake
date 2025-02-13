//==============================================
//
// ALTER_EGO[texture.h]
// Author: hiromu otake
//
//==============================================

#include "main.h"

class CTexture
{
public:
	CTexture();
	~CTexture();
	void Unload();								// テクスチャ破棄
	int Regist(const char* pTextureName);		// テクスチャ登録
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	// テクスチャ取得
	static const int m_MAXTEXTURE = 126;
	static const int m_MAXSENTENCE = 126;
private:
	LPDIRECT3DTEXTURE9 m_pTextureList[m_MAXTEXTURE];
	char m_pTextureName[m_MAXTEXTURE][m_MAXSENTENCE];
	int m_nNumAll;
	static LPD3DXBUFFER m_pBuffMat;		// マテリアルへのポインタ
	static DWORD m_dwNumMat;			// マテリアルの数
};

#pragma once

