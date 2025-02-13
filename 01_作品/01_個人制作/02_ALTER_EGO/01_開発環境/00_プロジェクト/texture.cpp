//==============================================
//
// ALTER_EGO[texture.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "texture.h"

// 静的メンバ初期化
LPD3DXBUFFER CTexture::m_pBuffMat = nullptr;
DWORD CTexture::m_dwNumMat = 0;

//==============================================
// コンストラクタ
//==============================================
CTexture::CTexture() : m_pTextureList{}, m_pTextureName{}, m_nNumAll(0)
{
	for (int nCntTex = 0; nCntTex < m_MAXSENTENCE; nCntTex++)
	{
		for (int nCnt = 0; nCnt < m_MAXTEXTURE; nCnt++)
		{
			m_pTextureList[nCnt] = {};
			m_pTextureName[nCnt][nCntTex] = {};
			m_nNumAll = 0;
		}
	}
}

//==============================================
// デストラクタ
//==============================================
CTexture::~CTexture()
{

}

//==============================================
// テクスチャの破棄
//==============================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < m_MAXSENTENCE; nCnt++)
	{
		//テクスチャを破棄
		if (m_pTextureList[nCnt] != NULL)
		{
			m_pTextureList[nCnt]->Release();
			m_pTextureList[nCnt] = NULL;
		}
	}
}

//==============================================
// テクスチャの登録
//==============================================
int CTexture::Regist(const char* pTextureName)
{
	int nIdx = 0;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ

	for (int nCnt = 0; nCnt < m_MAXTEXTURE; nCnt++)
	{
		if (m_pTextureList[nCnt] == nullptr)
		{// 登録されていなかった

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pTextureName,
				&m_pTextureList[nCnt]);

			strcpy(&m_pTextureName[nCnt][0], pTextureName);

			nIdx = nCnt;	// ID設定
			m_nNumAll++;	// テクスチャ数
			break;
		}
		else if (strcmp(&m_pTextureName[nCnt][0], pTextureName) == 0)
		{// 既に生成されているテクスチャと一致した
			nIdx = nCnt;	// ID設定
			break;
		}
	}
	return nIdx;	// IDを返す
}

LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx <= -1)
	{
		return nullptr;
	}
	else
	{
		return m_pTextureList[nIdx];
	}
}