//==============================================
//
// 3Dスクロールアクション[bg.cpp]
// Author: hiromu otake
//
//==============================================

#include "bg.h"
#include "texture.h"

//======================================================
// コンストラクタ
//======================================================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{

}

//======================================================
// デストラクタ
//======================================================
CBg::~CBg()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CBg::Init()
{
	CObject2D::SetWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT);
	CObject2D::SetTexture(1.0f);
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	CObject2D::Init();

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CBg::Uninit()
{
	CObject2D::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CBg::Update()
{
	CObject2D::Update();
}

//======================================================
// 描画処理
//======================================================
void CBg::Draw()
{
	CObject2D::Draw();
}

//=====================================================
// 背景の生成
//=====================================================
CBg* CBg::Create(CScene::MODE mode, D3DXVECTOR3 pos)
{
	CBg* pBg = new CBg;
	int nId = 0;

	if (pBg != nullptr)
	{
		switch (mode)
		{
		case CScene::MODE::MODE_TITLE:
			nId = CManager::GetTexture()->Regist("data\\Texture\\title.png");
			break;

		case CScene::MODE::MODE_TUTORIAL:
			nId = CManager::GetTexture()->Regist("data\\Texture\\game.png");
			break;

		case CScene::MODE::MODE_GAME:
			nId = CManager::GetTexture()->Regist("data\\Texture\\game.png");
			break;

		case CScene::MODE::MODE_RESULT:
			nId = CManager::GetTexture()->Regist("data\\Texture\\result001.png");
			break;

		default:
			break;
		}

		pBg->SetType(TYPE_BG);
		pBg->Init();
		pBg->SetPos(pos);
		pBg->BindTexture(CManager::GetTexture()->GetAddress(nId));
		pBg->SetUseDeath(true);
	}
	return  pBg;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBg::SetDeath()
{
	CObject::SetDeath();
}