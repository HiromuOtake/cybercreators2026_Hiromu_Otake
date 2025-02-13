//==============================================
//
//ALTER_EGO[modelparts.cpp]
//Author: hiromu otake
//
//==============================================

#include "modelparts.h"
#include "model.h"
#include "manager.h"
#include "objectX.h"

//==============================================
// コンストラクタ
//==============================================
CModelParts::CModelParts() : m_pos{ 0.0f,0.0f,0.0f }, m_rot{ 0.0f,0.0f,0.0f },m_min{ 0.0f,0.0f,0.0f }, m_max{ 0.0f,0.0f,0.0f }, m_size{ 0.0f,0.0f,0.0f }
, m_pParent(nullptr), m_pMesh(nullptr), m_pVtxBuff(nullptr), m_nNumVtx(0), m_sizeFVF(0), m_nIdx(0), m_nIdxParents(0), m_nModelIdx(0), m_nNumAll(0), m_pModelList{}, m_pModelName{}
{

}

//==============================================
// デストラクタ
//==============================================
CModelParts::~CModelParts()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CModelParts::Init()
{
	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CModelParts::Uninit()
{
	delete this;
}

//==============================================
// 更新処理
//==============================================
void CModelParts::Update()
{

}

//==============================================
// 描画処理
//==============================================
void CModelParts::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;							//デバイスへのポインタ
	CRenderer* pRenderer = CManager::GetRenderere();
	pDevice = pRenderer->GetDevice();					//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス
	D3DMATERIAL9 matDef;								//現在のマテリアル保存用
	D3DXMATERIAL* pMat;									//マテリアルデータへのポインタ

	D3DXMATRIX mtxParent;								// 親の行列を取得する

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		// 親のワールド変換行列を取得
		mtxParent = m_pParent->GetWoarldMatrix();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pModelList->m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModelList->m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, nullptr);

		//モデル(パーツ)の描画
		m_pModelList->m_pMesh->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
}

//======================================================
// テクスチャ生成
//======================================================
void CModelParts::BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh)
{
	m_pModelList->m_pBuffMat = BuffMat;
	m_pModelList->m_dwNumMat = dwNumMat;
	m_pModelList->m_pMesh = Mesh;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	CRenderer* pRenderer = CManager::GetRenderere();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点数の取得
	m_nNumVtx = Mesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	m_sizeFVF = D3DXGetFVFVertexSize(Mesh->GetFVF());

	//頂点バッファのロック
	Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;

		if (vtx.x < m_min.x)
		{
			m_min.x = vtx.x;
		}
		else if (vtx.x > m_max.x)
		{
			m_max.x = vtx.x;
		}

		if (vtx.y < m_min.y)
		{
			m_min.y = vtx.y;
		}
		else if (vtx.y > m_max.y)
		{
			m_max.y = vtx.y;
		}

		if (vtx.z < m_min.z)
		{
			m_min.z = vtx.z;
		}
		else if (vtx.z > m_max.z)
		{
			m_max.z = vtx.z;
		}

		//頂点フォーマットのサイズ分のポインタを進める
		m_pVtxBuff += m_sizeFVF;
	}

	m_size = m_max - m_min;

	//頂点バッファのアンロック
	Mesh->UnlockVertexBuffer();

}

//==============================================
// モデル登録
//==============================================
int CModelParts::Regist(const char* pModelName)
{
	int nIdx = 0;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ

	for (int nCnt = 0; nCnt < m_NUM_MODEL_PARTS; nCnt++)
	{
		if (m_pModelList[nCnt].m_bUse == true)
		{
			continue;
		}

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

			m_pModelList[nCnt].m_bUse = true;
			break;
		}
	}
	return nIdx;	// IDを返す
}

//=====================================
// モデルパーツの生成
//=====================================
CModelParts* CModelParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char* aModel)
{
	CModelParts* pModelParts = new CModelParts;

	pModelParts->Init();

	pModelParts->m_pos = pos;
	pModelParts->m_rot = rot;

	CModel* pModel = CManager::GetModel();

	pModelParts->BindModel(pModel->GetBuffMat(pModel->Regist(aModel)),
		pModel->GetNumMat(pModel->Regist(aModel)),
		pModel->GetMesh(pModel->Regist(aModel)));

	return pModelParts;
}

//=====================================
// 親の設定
//=====================================
void CModelParts::SetParent(CModelParts* pModelParts)
{
	if (m_pParent == nullptr)
	{
		m_pParent = pModelParts;
	}
}

//=====================================
// 親のワールドマトリックスを取得
//=====================================
D3DXMATRIX CModelParts::GetWoarldMatrix()
{
	return m_mtxWorld;
}

//======================================================
// 大きさの取得
//======================================================
D3DXVECTOR3& CModelParts::GetPos()
{
	return m_pos;
}

//======================================================
// 大きさの取得
//======================================================
D3DXVECTOR3& CModelParts::GetSize()
{
	return m_size;
}

//======================================================
// 最小の取得
//======================================================
D3DXVECTOR3& CModelParts::GetMin()
{
	return m_min;
}

//======================================================
// 最大の取得
//======================================================
D3DXVECTOR3& CModelParts::GetMax()
{
	return m_max;
}

//======================================================
// パーツ数
//======================================================
int& CModelParts::GetIdx()
{
	return m_nIdx;
}
