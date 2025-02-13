//==============================================
//
// ALTER_EGO[tutorial2.cpp]
// Author: hiromu otake
//
//==============================================

#include "tutorial2.h"
#include "bg.h"

//======================================================
// コンストラクタ
//======================================================
CTutorial2::CTutorial2() : m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pNumber(nullptr)
{

}

//======================================================
// デストラクタ
//======================================================
CTutorial2::~CTutorial2()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CTutorial2::Init()
{
	CScene::Init();

	CBg::Create(CScene::MODE::MODE_TUTORIAL2);

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CTutorial2::Uninit()
{
	CSound* pSound = CManager::GetSound();

	pSound->StopAllSound();

	CScene::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CTutorial2::Update()
{
	CScene::Update();
}

//======================================================
// 描画処理
//======================================================
void CTutorial2::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	CRenderer* pRenderer = CManager::GetRenderere();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}