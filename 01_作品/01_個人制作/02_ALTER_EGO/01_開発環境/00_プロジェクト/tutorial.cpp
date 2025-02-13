//==============================================
//
// ALTER_EGO[tutorial.cpp]
// Author: hiromu otake
//
//==============================================

#include "tutorial.h"
#include "bg.h"

//======================================================
// コンストラクタ
//======================================================
CTutorial::CTutorial() : m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pNumber(nullptr)
{

}

//======================================================
// デストラクタ
//======================================================
CTutorial::~CTutorial()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CTutorial::Init()
{
	CScene::Init();

	CBg::Create(CScene::MODE::MODE_TUTORIAL1);

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CTutorial::Uninit()
{
	CScene::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CTutorial::Update()
{
	CScene::Update();
}

//======================================================
// 描画処理
//======================================================
void CTutorial::Draw()
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