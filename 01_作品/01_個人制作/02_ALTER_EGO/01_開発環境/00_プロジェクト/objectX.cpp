//==============================================
//
// ALTER_EGO[objectX.cpp]
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
m_min{ 0.0f,0.0f,0.0f }, m_max{ 0.0f,0.0f,0.0f }, m_size{ 0.0f,0.0f,0.0f }, m_scale{ 1.0f, 1.0f, 1.0f },
m_pMesh(nullptr), m_dwNumMat(NULL), m_pBuffMat(nullptr), m_pTexture(nullptr), m_pVtxBuff(nullptr), m_nNumVtx(0), m_sizeFVF(0), m_fRotation(0.0f)
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
	D3DXMATRIX mtxScale, mtxRotationY, mtxRot, mtxTrans;

	// ワールド行列の初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// Y軸回転を反映
	if (m_fRotation != 0.0f)
	{
		D3DXMatrixRotationZ(&mtxRotationY, D3DXToRadian(m_fRotation));
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotationY);
	}

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//==============================================
// 描画処理
//==============================================
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();		// 計算用マトリックス
	D3DMATERIAL9 matDef;													// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;														// マテリアルデータへのポインタ
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの色の設定
		SetMatColor(&pMat[nCntMat].MatD3D, nCntMat);

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
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
// スケールの設定
//======================================================
void CObjectX::SetScale(D3DXVECTOR3 scale)
{
	m_scale = scale;
}

//======================================================
// 位置の設定
//======================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//======================================================
// マテリアルの色の設定
//======================================================
void CObjectX::SetMatColor(D3DMATERIAL9* pMat,int nMatIdx)
{

}

//======================================================
// テクスチャ生成
//======================================================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//======================================================
// テクスチャ生成
//======================================================
void CObjectX::BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh)
{
	m_pBuffMat = BuffMat;
	m_dwNumMat = dwNumMat;
	m_pMesh = Mesh;
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

//======================================================
// ワールドマトリックスの取得
//======================================================
D3DXMATRIX& CObjectX::GetMatrix()
{ 
	return m_mtxWorld;
}

//======================================================
// マテリアルへのポインタの取得
//======================================================
LPD3DXBUFFER& CObjectX::GetBuffMat()
{ 
	return m_pBuffMat;
}

//======================================================
// メッシュへのポインタの取得
//======================================================
LPD3DXMESH& CObjectX::GetMesh()
{ 
	return m_pMesh;
}

//======================================================
// マテリアルの数の取得
//======================================================
const DWORD& CObjectX::GetNumMat()
{ 
	return m_dwNumMat;
}