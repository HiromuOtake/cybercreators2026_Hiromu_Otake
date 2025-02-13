//======================================================
//
// ALTER_EGO [manager.cpp]
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
CParticleManager* CManager::m_pParticleManager = nullptr;
int CManager::m_nMode = 0;
std::string CManager::m_nextStageFile = "";
CScene::MODE CManager::m_nextSceneMode = CScene::MODE_TITLE;
bool CManager::m_bPaused = false;
CFade* CManager::m_pFade = nullptr;

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

	// パーティクルマネージャー生成
	m_pParticleManager = new CParticleManager();
	m_pParticleManager->Init();

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
	if (m_pParticleManager != nullptr)
	{
		m_pParticleManager->Uninit();
		delete m_pParticleManager;
		m_pParticleManager = nullptr;
	}
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	CObject::DeleateProcess();
}

//======================================================
// 更新処理
//======================================================
void CManager::Update()
{
	//char debugMsg[256];

	//if (m_pFade != nullptr)
	//{
	//	sprintf(debugMsg, "[CManager::Update] m_pFade のアドレス: %p\n", m_pFade);
	//	OutputDebugStringA(debugMsg);

	//	OutputDebugStringA("[CManager::Update] m_pFade->Update() を実行します\n");
	//	m_pFade->Update();
	//	OutputDebugStringA("[CManager::Update] m_pFade->Update() 完了\n");
	//}
	//else
	//{
	//	OutputDebugStringA("[CManager::Update] m_pFade は NULL です\n");
	//}

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
	if (m_pParticleManager != nullptr)
	{
		m_pParticleManager->Update();
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
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
	if (m_pParticleManager != nullptr)
	{
		m_pParticleManager->Draw();
	}
}

//======================================================
// シーン取得
//======================================================
CFade* CManager::GetFade()
{
	return m_pFade;
}

void CManager::SetFadeInstance(CFade* fade)
{
	m_pFade = fade;
}

//======================================================
// モード設定
//======================================================
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pFade == nullptr)
	{
		OutputDebugStringA("[SetMode] m_pFade が NULL\n");
	}

	char debugMsg[256];

	sprintf(debugMsg, "[SetMode] 実行前の m_pFade: %p\n", m_pFade);
	OutputDebugStringA(debugMsg);

	OutputDebugStringA("[SetMode] オブジェクトを解放します\n");
	CObject::ReleaseAll();

	//終了処理
	if (m_pScene != nullptr)
	{
		OutputDebugStringA("[SetMode] 既存のシーンを削除します\n");
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	
	// 生成
	OutputDebugStringA("[SetMode] 新しいシーンを作成します\n");
	m_pScene = CScene::Create(mode);

	OutputDebugStringA("[SetMode] CFade を作成します\n");
	//m_pFade = CFade::Create(mode);

	sprintf(debugMsg, "[SetMode] 作成後の m_pFade: %p\n", m_pFade);
	OutputDebugStringA(debugMsg);

	SetFadeInstance(m_pFade);

	if (m_pFade != nullptr)
	{
		OutputDebugStringA("[SetMode] フェードアウトを開始します\n");
		m_pFade->SetFade(CFade::FADE_OUT, mode);
	}
}