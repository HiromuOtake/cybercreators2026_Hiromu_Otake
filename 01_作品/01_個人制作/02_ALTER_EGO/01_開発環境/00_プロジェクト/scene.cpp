//==============================================
//
// ALTER_EGO[scene.cpp]
// Author: hiromu otake
//
//==============================================

#include "scene.h"
#include "title.h"
#include "stageselect.h"
#include "tutorial.h"
#include "tutorial2.h"
#include "game.h"
#include "result.h"

//======================================================
// コンストラクタ
//======================================================
CScene::CScene() : m_Mode(MODE_NONE)
{
	
}

//======================================================
// デストラクタ
//======================================================
CScene::~CScene()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CScene::Init()
{
	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CScene::Uninit()
{
	//CObject::ReleaseAll();
}

//======================================================
// 更新処理
//======================================================
void CScene::Update()
{

}

//======================================================
// 描画処理
//======================================================
void CScene::Draw()
{

}

//=====================================================
// シーンの生成
//=====================================================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;

	if (pScene == nullptr)
	{
		switch (mode)
		{
		case MODE_TITLE:
			pScene = new CTitle;
			break;

		case MODE_STAGESELECT:
			pScene = new CStageSelect;
			break;

		case MODE_TUTORIAL1:
			pScene = new CTutorial;
			break;

		case MODE_TUTORIAL2:
			pScene = new CTutorial2;
			break;

		case MODE_GAME:
			pScene = new CGame;
			break;

		case MODE_RESULT:
			pScene = new CResult;
			break;
		
		default:
			assert(false);
			break;
		}
	}

	pScene->m_Mode = mode;
	pScene->Init();
	return  pScene;
}

CScene::MODE CScene::GetMode()
{
	return m_Mode;
}