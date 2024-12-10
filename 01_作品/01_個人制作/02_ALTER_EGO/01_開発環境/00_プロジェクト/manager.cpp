//======================================================
//
// 3Dスクロールアクション [manager.cpp]
// Auther : 大竹熙
//
//======================================================

#include "manager.h"
#include "item.h"
#include "player.h"
#include "particlemanager.h"

// 静的メンバ初期化
CRenderer* CManager::m_pRnderer = nullptr;
CInputKeyboard* CManager::m_pKeyboard = nullptr;
CInputJoyPad* CManager::m_pJoyPad = nullptr;
CLight* CManager::m_pLight = nullptr;
CTexture* CManager::m_pTexture = nullptr;
CModel* CManager::m_pModel = nullptr;
CScene* CManager::m_pScene = nullptr;
CSound* CManager::m_pSound = nullptr;
//CParticleManager* CManager::m_pParticleManager = nullptr;
int CManager::m_nMode = 0;
bool CManager::m_bPaused = false;
//CFade* CManager::m_pFade = nullptr;

//======================================================
// コンストラクタ
//======================================================
CManager::CManager()
{
	
}

//======================================================
// デストラクタ
//======================================================
CManager::~CManager()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーの生成
	m_pRnderer = new CRenderer();
	m_pRnderer->Init(hWnd, bWindow);

	// キーボードの生成
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd);

	// ゲームパッドの生成
	m_pJoyPad = new CInputJoyPad();
	m_pJoyPad->Init(hInstance, hWnd);

	// ライト生成
	m_pLight = new CLight();
	m_pLight->Init();

	// テクスチャ生成
	m_pTexture = new CTexture();

	// モデル生成
	m_pModel = new CModel();

	// サウンド生成
	m_pSound = new CSound();
	m_pSound->Init(hWnd);

	//// パーティクルマネージャー生成
	//m_pParticleManager = new CParticleManager();
	//m_pParticleManager->Init();

	// 生成
	m_pScene = CScene::Create(CScene::MODE::MODE_TITLE);

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CManager::Uninit ()
{
	CObject::ReleaseAll();	// 全オブジェクトの解放

	if (m_pRnderer != nullptr)
	{
		m_pRnderer->Uninit();
		delete m_pRnderer;
		m_pRnderer = nullptr;
	}
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}
	if (m_pJoyPad != nullptr)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	if (m_pModel != nullptr)
	{
		m_pModel->Unload();
		delete m_pModel;
		m_pModel = nullptr;
	}
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
	//if (m_pParticleManager != nullptr)
	//{
	//	m_pParticleManager->Uninit();
	//	delete m_pParticleManager;
	//	m_pParticleManager = nullptr;
	//}

	CObject::DeleateProcess();

	//if (m_pFade != nullptr)
	//{
	//	m_pFade->Uninit();
	//	delete m_pFade;
	//	m_pFade = nullptr;
	//}
}

//======================================================
// 更新処理
//======================================================
void CManager::Update()
{
	m_nMode = (int)m_pScene->GetMode();

	if (m_pRnderer != nullptr)
	{
		m_pRnderer->Update();
	}
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}
	if (m_pJoyPad != nullptr)
	{
		m_pJoyPad->Update();
	}
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
	//if (m_pParticleManager != nullptr)
	//{
	//	m_pParticleManager->Update();
	//}

	if (m_pKeyboard->GetTrigger(DIK_K) || m_pJoyPad->GetJoyPadTrigger(CInput::JOYKEY_X) == true)
	{
		CManager::SetPaused(true); // ポーズを有効に
	}

	bool& pPlayer = CPlayer::GetGoal();

	if (m_nMode == (int)CScene::MODE::MODE_GAME)
	{
		return;
	}
	else
	{
		if (m_pKeyboard->GetTrigger(DIK_RETURN) == true || pPlayer == false || (m_pJoyPad->GetJoyPadTrigger(CInput::JOYKEY_START) == true ))
		{
			m_nMode++;

			if (m_nMode >= (int)CScene::MODE::MODE_MAX)
			{
				m_nMode = 1;
			}
			SetMode(static_cast<CScene::MODE>(m_nMode));
		}
	}
}

//======================================================
// 描画処理
//======================================================
void CManager::Draw()
{
	if (m_pRnderer != nullptr)
	{
		m_pRnderer->Draw();
	}
	//if (m_pParticleManager != nullptr)
	//{
	//	m_pParticleManager->Draw();
	//}
}

//======================================================
// レンダラー取得
//======================================================
CRenderer* CManager::GetRenderere()
{
	return m_pRnderer;
}

//======================================================
// キーボード取得
//======================================================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//======================================================
// ゲームパッド取得
//======================================================
CInputJoyPad* CManager::GetJoyPad()
{
	return m_pJoyPad;
}

//======================================================
// ライト取得
//======================================================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//======================================================
// テクスチャ取得
//======================================================
CTexture* CManager::GetTexture()
{
	return m_pTexture;
}

//======================================================
// モデル取得
//======================================================
CModel* CManager::GetModel()
{
	return m_pModel;
}

//======================================================
// シーン取得
//======================================================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//======================================================
// シーン取得
//======================================================
CSound* CManager::GetSound()
{
	return m_pSound;
}

//======================================================
// モード取得
//======================================================
int& CManager::GetMode()
{
	return m_nMode;
}

////======================================================
//// パーティクルマネージャー取得
////======================================================
//CParticleManager* CManager::GetParticleManager()
//{
//	return m_pParticleManager;
//}

////======================================================
//// シーン取得
////======================================================
//CFade* CManager::GetFade()
//{
//	return /*m_pFade*/nullptr;
//}

//======================================================
// モード設定
//======================================================
void CManager::SetMode(CScene::MODE mode)
{
	//if (m_pFade == nullptr)
	//{
	//	// 生成
	//	//m_pFade = CFade::Create(mode);
	//}

	CObject::ReleaseAll();

	//終了処理
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	
	//m_pFade->SetFade(CFade::FADE::FADE_IN, mode);

	// 生成
	m_pScene = CScene::Create(mode);

	// 生成
	//CFade::Create(mode)->SetFade(CFade::FADE::FADE_IN, mode);
}