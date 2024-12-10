//==============================================
//
// 3Dスクロールアクション[number.cpp]
// Author: hiromu otake
//
//==============================================

#include "number.h"
#include "texture.h"

//======================================================
// コンストラクタ
//======================================================
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{

}

//======================================================
// デストラクタ
//======================================================
CNumber::~CNumber()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CNumber::Init()
{
	int nId = 0;

	CObject2D::SetTexture(0.1f);

	nId = CManager::GetTexture()->Regist("data\\Texture\\number4.png");

	BindTexture(CManager::GetTexture()->GetAddress(nId));

	CObject2D::Init();

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CNumber::Uninit()
{
	CObject2D::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CNumber::Update()
{

	VERTEX_2D* pVtx;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CObject2D::GetBuffer();

	CObject2D::Update();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * m_nTexPos), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * m_nTexPos), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * m_nTexPos), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * m_nTexPos), 1.0f);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Unlock();

}

//======================================================
// 描画処理
//======================================================
void CNumber::Draw()
{
	CObject2D::Draw();
}

//======================================================
// テクスチャ座標の設定
//======================================================
void CNumber::SetTexturePos(int nTexPos)
{
	m_nTexPos = nTexPos;
}


//=====================================================
// 背景の生成
//=====================================================
CNumber* CNumber::Create(D3DXVECTOR3 pos, float fsizeX, float fsizeY)
{
	CNumber* pNumber = new CNumber;

	if (pNumber != nullptr)
	{
		pNumber->SetPos(pos);
		pNumber->SetWidthHeight(fsizeX, fsizeY);
		pNumber->Init();
		pNumber->SetUseDeath(true);
	}
	return  pNumber;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CNumber::SetDeath()
{
	CObject::SetDeath();
}

