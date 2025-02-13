//==============================================
//
// ALTER_EGO[fade.cpp]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "fade.h"
#include <cassert>

// 静的メンバ初期化
LPDIRECT3DTEXTURE9 CFade::m_pTextureTemp = nullptr;

//======================================================
// コンストラクタ
//======================================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	m_Fade = FADE_NONE;
	m_colorFade = 0.0f;
}

//======================================================
// デストラクタ
//======================================================
CFade::~CFade()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CFade::Init()
{
	CObject2D::SetWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT);

	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	CObject2D::Init();

	m_Fade = FADE_NONE;

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CFade::Uninit()
{
	CObject2D::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CFade::Update()
{
	OutputDebugStringA("[CFade::Update] 更新開始\n");

	char debugMsg[256];
	sprintf(debugMsg, "[CFade::Update] 現在のフェード状態: %d\n", m_Fade);
	OutputDebugStringA(debugMsg);

	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			OutputDebugStringA("[CFade::Update] FADE_IN\n");
			m_colorFade -= 0.03f;
			CObject2D::SetColor(m_colorFade);

			sprintf(debugMsg, "[CFade::Update] m_colorFade: %.2f\n", m_colorFade);
			OutputDebugStringA(debugMsg);

			if (m_colorFade <= 0.0f)
			{
				OutputDebugStringA("[CFade::Update] FADE_IN 完了\n");
				m_colorFade = 0.0f;
				m_Fade = FADE_NONE;
				SetDeath();
				CManager::SetFadeInstance(nullptr);
			}
		}
		else if (m_Fade == FADE_OUT)
		{
			OutputDebugStringA("[CFade::Update] FADE_OUT\n");
			m_colorFade += 0.03f;
			CObject2D::SetColor(m_colorFade);

			sprintf(debugMsg, "[CFade::Update] m_colorFade: %.2f\n", m_colorFade);
			OutputDebugStringA(debugMsg);

			if (m_colorFade >= 1.0f)
			{
				OutputDebugStringA("[CFade::Update] FADE_OUT 完了\n");
				m_colorFade = 1.0f;
				m_Fade = FADE_IN;

				OutputDebugStringA("[CFade::Update] モード変更を実行\n");
				CManager::SetMode(m_fademode);
				return;
			}
		}
	}

	OutputDebugStringA("[CFade::Update] 更新終了\n");
}

//======================================================
// 描画処理
//======================================================
void CFade::Draw()
{
	CObject2D::Draw();
}

//=====================================================
// フェードの生成
//=====================================================
CFade* CFade::Create(CScene::MODE mode)
{
	CFade* pFade = new CFade;

	if (pFade != nullptr)
	{
		pFade->SetType(TYPE_FIELD);
		pFade->Init();
		//pFade->SetUseDeath(true);
	}
	return  pFade;
}

//==============================================
//フェード画面の設定処理
//==============================================
void CFade::SetFade(FADE fade, CScene::MODE modeNext)
{
	m_fademode = modeNext;
	m_Fade = fade;

	if (fade == FADE::FADE_IN)
	{
		m_colorFade = 1.0f;
	}
	else if(fade == FADE::FADE_OUT)
	{
		m_colorFade = 0.0f;
	}
	else
	{
		MessageBox(NULL, "FADE_IN か FADE_OUT のみ設定できます。", "エラー", MB_OK);
	}
	SetColor(m_colorFade);
}

//==============================================
//フェード画面の取得
//==============================================
CFade::FADE CFade::GetFade(void)
{
	return m_Fade;
}

//==============================================
//フェード画面の色の取得
//==============================================
float CFade::FadeColor(void)
{
	return m_colorFade;
}
