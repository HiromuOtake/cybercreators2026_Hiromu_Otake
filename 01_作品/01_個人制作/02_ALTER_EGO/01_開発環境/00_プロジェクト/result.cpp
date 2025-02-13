//==============================================
//
// ALTER_EGO[result.cpp]
// Author: hiromu otake
//
//==============================================

#include "result.h"
#include "bg.h"

//======================================================
// コンストラクタ
//======================================================
CResult::CResult() : m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pNumber(nullptr)
{

}

//======================================================
// デストラクタ
//======================================================
CResult::~CResult()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CResult::Init()
{
	CScene::Init();

	CBg::Create(CScene::MODE::MODE_RESULT);

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CResult::Uninit()
{
	CSound* pSound = CManager::GetSound();

	pSound->StopAllSound();

	CScene::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CResult::Update()
{
	CScene::Update();
}

//======================================================
// 描画処理
//======================================================
void CResult::Draw()
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