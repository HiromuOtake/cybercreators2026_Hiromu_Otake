//==============================================
//
// ALTER_EGO[model.h]
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
		m_pModelList[nCnt].m_pMesh = nullptr;
		m_pModelList[nCnt].m_pBuffMat = nullptr;
		m_pModelList[nCnt].m_dwNumMat = 0;
		//m_pModelList[nCnt] = {};
		for (int nCntTex = 0; nCntTex < m_MAXSENTENCE; nCntTex++)
		{
			m_pModelName[nCnt][nCntTex] = {};
		}
		memset(m_pModelName[nCnt], 0, sizeof(m_pModelName[nCnt]));
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

			strcpy(&m_pModelName[nCnt][0], pModelName);

			nIdx = nCnt;	// ID設定
			break;
		}
		else if (strcmp(&m_pModelName[nCnt][0], pModelName) == 0)
		{// 既に生成されているモデルと一致した
			nIdx = nCnt;	// ID設定
			break;
		}
	}
	return nIdx;	// IDを返す
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