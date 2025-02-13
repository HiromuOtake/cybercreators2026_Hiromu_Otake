//==============================================
//
// ALTER_EGO[billboard.cpp]
// Author: hiromu otake
//
//==============================================

#include "billboard.h"
#include "manager.h"

//=====================================
// コンストラクタ
//=====================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority), m_pos{ 0.0f,0.0f,0.0f }, m_min{ 0.0f,0.0f,0.0f }, m_max{ 0.0f,0.0f,0.0f }, m_size{ 0.0f,0.0f,0.0f }
, m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pMesh(nullptr), m_pBuffMat(nullptr), m_nNumVtx(0), m_sizeFVF(0)
{

}

//=====================================
// デストラクタ
//=====================================
CBillboard::~CBillboard()
{

}

//=====================================
//ビルボードの初期設定
//=====================================
HRESULT CBillboard::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx;          //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_BILLBOARD_SIZE, m_BILLBOARD_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_BILLBOARD_SIZE, m_BILLBOARD_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_BILLBOARD_SIZE, -m_BILLBOARD_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_BILLBOARD_SIZE, -m_BILLBOARD_SIZE, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	m_size.x = m_BILLBOARD_SIZE;
	m_size.y = m_BILLBOARD_SIZE;

	return S_OK;
}

//=====================================
//プレイヤーの終了処理
//=====================================
void CBillboard::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=====================================
//プレイヤーの更新処理
//=====================================
void CBillboard::Update()
{
	
}

//=====================================
//ポリゴンの描画処理
//=====================================
void CBillboard::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;				//ビューマトリックス取得用
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);		//逆光列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//======================================================
// テクスチャ生成
//======================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//======================================================
// 位置の設定
//======================================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//======================================================
// 位置の設定
//======================================================
void CBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//======================================================
// 位置の取得
//======================================================
D3DXVECTOR3& CBillboard::GetPos()
{
	return m_pos;
}

//======================================================
// 過去の位置の取得
//======================================================
D3DXVECTOR3& CBillboard::GetPosOld()
{
	return m_posold;
}

//======================================================
// 向きの取得
//======================================================
D3DXVECTOR3& CBillboard::GetRot()
{
	return m_rot;
}

//======================================================
// 大きさの取得
//======================================================
D3DXVECTOR3& CBillboard::GetSize()
{
	return m_size;
}

//======================================================
// 最小の取得
//======================================================
D3DXVECTOR3& CBillboard::GetMin()
{
	return m_min;
}

//======================================================
// 最大の取得
//======================================================
D3DXVECTOR3& CBillboard::GetMax()
{
	return m_max;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBillboard::SetDeath()
{
	CObject::SetDeath();
}