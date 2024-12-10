//==============================================
//
// 3Dスクロールアクション[game.cpp]
// Author: hiromu otake
//
//==============================================

#include "title.h"
#include "bg.h"

//======================================================
// コンストラクタ
//======================================================
CTitle::CTitle() : m_pTexture(nullptr), m_pVtxBuff(nullptr)
{

}

//======================================================
// デストラクタ
//======================================================
CTitle::~CTitle()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CTitle::Init()
{
	CScene::Init();

	CBg::Create(CScene::MODE::MODE_TITLE, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT* 0.5f, 0.0f));

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CTitle::Uninit()
{
	CScene::Uninit();

	CSound* pSound = CManager::GetSound();

	pSound->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);
}

//======================================================
// 更新処理
//======================================================
void CTitle::Update()
{
	CScene::Update();
}

//======================================================
// 描画処理
//======================================================
void CTitle::Draw()
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