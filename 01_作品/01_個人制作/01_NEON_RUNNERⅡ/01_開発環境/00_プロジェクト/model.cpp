//==============================================
//
// 3Dスクロールアクション[Model.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "model.h"

//==============================================
// コンストラクタ
//==============================================
CModel::CModel() : m_nNumAll(0), m_pModelList{}, m_pModelName{}
{
	for (int nCnt = 0; nCnt < m_MAXMODEL; nCnt++)
	{
		m_pModelList[nCnt].m_pMesh = {};
		m_pModelList[nCnt].m_pBuffMat = {};
		m_pModelList[nCnt].m_dwNumMat = {};
		m_pModelList[nCnt] = {};
		for (int nCntTex = 0; nCntTex < m_MAXSENTENCE; nCntTex++)
		{
			m_pModelName[nCnt][nCntTex] = {};
			m_pModelList[nCnt].m_pTexture[nCntTex] = {};
		}
	}
}

//==============================================
// デストラクタ
//==============================================
CModel::~CModel()
{

}

//==============================================
// モデル破棄
//==============================================
void CModel::Unload()
{
	for (int nCnt = 0; nCnt < m_MAXSENTENCE; nCnt++)
	{
		//モデル破棄
		if (m_pModelList[nCnt].m_pMesh != NULL)
		{
			m_pModelList[nCnt].m_pMesh->Release();
			m_pModelList[nCnt].m_pMesh = NULL;
		}
		//モデル破棄
		if (m_pModelList[nCnt].m_pBuffMat != NULL)
		{
			m_pModelList[nCnt].m_pBuffMat->Release();
			m_pModelList[nCnt].m_pBuffMat = NULL;
		}
	}
}

//==============================================
// モデル登録
//==============================================
int CModel::Regist(const char* pModelName)
{
	int nIdx = 0;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ
	D3DXMATERIAL* pMat;														//マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < m_MAXMODEL; nCnt++)
	{
		if (m_pModelList[nCnt].m_pMesh == nullptr)
		{// 登録されていなかった

			//Xファイルの読み込み
			D3DXLoadMeshFromX(pModelName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_pModelList[nCnt].m_pBuffMat,
				NULL,
				&m_pModelList[nCnt].m_dwNumMat,
				&m_pModelList[nCnt].m_pMesh);

			pMat = (D3DXMATERIAL*)m_pModelList[nCnt].m_pBuffMat->GetBufferPointer();

			for (int nCntTex = 0; nCntTex < (int)m_pModelList[nCnt].m_dwNumMat; nCntTex++)
			{
				if (pMat[nCntTex].pTextureFilename != nullptr)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntTex].pTextureFilename,
						&m_pModelList[nCnt].m_pTexture[nCntTex]);
				}
			}

			strcpy(&m_pModelName[nCnt][0], pModelName);

			nIdx = nCnt;	// ID設定
			m_nNumAll++;	// テクスチャ数
			break;
		}
		else if (strcmp(&m_pModelName[nCnt][0], pModelName) == 0)
		{// 既に生成されているテクスチャと一致した
			nIdx = nCnt;	// ID設定
			break;
		}
	}
	return nIdx;	// IDを返す
}

CModel::ModelInfo CModel::GetAddress(int nIdx)
{
	return m_pModelList[nIdx];
}

LPD3DXBUFFER CModel::GetBuffMat(int nIdx)
{
	if (m_pModelList[nIdx].m_pBuffMat != nullptr)
	{
		return m_pModelList[nIdx].m_pBuffMat;
	}
	return nullptr;
}

DWORD CModel::GetNumMat(int nIdx)
{
	if (m_pModelList[nIdx].m_dwNumMat != NULL)
	{
		return m_pModelList[nIdx].m_dwNumMat;
	}
	return NULL;
}

LPD3DXMESH CModel::GetMesh(int nIdx)
{
	if (m_pModelList[nIdx].m_pMesh != nullptr)
	{
		return m_pModelList[nIdx].m_pMesh;
	}
	return nullptr;
}

LPDIRECT3DTEXTURE9* CModel::GetTexture(int nIdx)
{
	if (m_pModelList[nIdx].m_pTexture != nullptr)
	{
		return &m_pModelList[nIdx].m_pTexture[0];
	}
	return nullptr;
}