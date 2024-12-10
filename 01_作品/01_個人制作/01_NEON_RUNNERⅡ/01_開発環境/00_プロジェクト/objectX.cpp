//==============================================
//
// 3Dスクロールアクション[objectX.cpp]
// Author: hiromu otake
//
//==============================================

#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "block.h"


 //==============================================
// コンストラクタ
//==============================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority), m_pos{ 0.0f,0.0f,0.0f }, m_posold{ 0.0f,0.0f,0.0f }, m_rot{ 0.0f,0.0f,0.0f }, m_move{ 0.0f,0.0f,0.0f },
m_min{ 0.0f,0.0f,0.0f },m_max{ 0.0f,0.0f,0.0f }, m_size{0.0f,0.0f,0.0f}, m_pMesh(nullptr), m_dwNumMat(NULL), m_pBuffMat(nullptr), m_pTexture(nullptr), m_nNumVtx(0), m_pVtxBuff(nullptr), m_sizeFVF(0)
{

}

//==============================================
// デストラクタ
//==============================================
CObjectX::~CObjectX()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CObjectX::Init()
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	CRenderer* pRenderer = CManager::GetRenderere();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点数の取得
	m_nNumVtx = m_pMesh->GetNumVertices();
	//頂点フォーマットのサイズを取得
	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);

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
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CObjectX::Uninit()
{

}

//==============================================
// 更新処理
//==============================================
void CObjectX::Update()
{

}

//==============================================
// 描画処理
//==============================================
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;							//デバイスへのポインタ
	CRenderer* pRenderer = CManager::GetRenderere();
	pDevice = pRenderer->GetDevice();					//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス
	D3DMATERIAL9 matDef;								//現在のマテリアル保存用
	D3DXMATERIAL* pMat;									//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを返す
	pDevice->SetMaterial(&matDef);

	//LPDIRECT3DDEVICE9 pDevice;							//デバイスへのポインタ
	//CRenderer* pRenderer = CManager::GetRenderere();
	//pDevice = pRenderer->GetDevice();					//デバイスの取得
	//
	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	//
	//D3DXMATRIX mtxRot, mtxTrans, mtxScale;						//計算用マトリックス
	//D3DMATERIAL9 matDef;								//現在のマテリアル保存用
	//D3DXMATERIAL* pMat;									//マテリアルデータへのポインタ
	//
	//D3DXMATRIX& matrix = GetMatrix();
	//D3DXVECTOR3& rot = GetRot();
	//D3DXVECTOR3& pos = GetPos();
	//
	////ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&matrix);
	//
	//static constexpr float SCALE = 1.0f;
	//
	//// スケールを反映
	//D3DXMatrixScaling(&mtxScale, SCALE, SCALE, SCALE);
	//D3DXMatrixMultiply(&matrix, &matrix, &mtxScale);
	//
	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//======================================================
// 位置の設定
//======================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//======================================================
// 位置の設定
//======================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//======================================================
// 位置の設定
//======================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

////==============================================
//// モデルの一括管理
////==============================================
//void CObjectX::ModelPath(std::string sPath)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ
//	D3DXMATERIAL* pMat;														//マテリアルデータへのポインタ
//
//	//Xファイルの読み込み
//	D3DXLoadMeshFromX(sPath.c_str(),
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&m_pBuffMat,
//		NULL,
//		&m_dwNumMat,
//		&m_pMesh);
//
//	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
//	{
//		if (pMat[nCnt].pTextureFilename != nullptr)
//		{
//			//テクスチャの読み込み
//			D3DXCreateTextureFromFile(pDevice,
//				pMat[nCnt].pTextureFilename,
//				&m_pTexture[nCnt]);
//		}
//	}
//}

////======================================================
//// テクスチャ生成
////======================================================
//void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
//{
//	m_pTexture = pTex;
//}

//======================================================
// テクスチャ生成
//======================================================
void CObjectX::BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh, LPDIRECT3DTEXTURE9* Texture)
{
	m_pBuffMat = BuffMat;
	m_dwNumMat = dwNumMat;
	m_pMesh = Mesh;
	m_pTexture = Texture;
}

//======================================================
// 位置の取得
//======================================================
D3DXVECTOR3& CObjectX::GetPos()
{
	return m_pos;
}

//======================================================
// 過去の位置の取得
//======================================================
D3DXVECTOR3& CObjectX::GetPosOld()
{
	return m_posold;
}

//======================================================
// 向きの取得
//======================================================
D3DXVECTOR3& CObjectX::GetRot()
{
	return m_rot;
}

//======================================================
// 移動の取得
//======================================================
D3DXVECTOR3& CObjectX::GetMove()
{
	return m_move;
}

//======================================================
// 大きさの取得
//======================================================
D3DXVECTOR3& CObjectX::GetSize()
{
	return m_size;
}

//======================================================
// 最小の取得
//======================================================
D3DXVECTOR3& CObjectX::GetMin()
{
	return m_min;
}

//======================================================
// 最大の取得
//======================================================
D3DXVECTOR3& CObjectX::GetMax()
{
	return m_max;
}