//==============================================
//
// ALTER_EGO[pause.cpp]
// Author: hiromu otake
//
//==============================================

#include "pause.h"
#include "game.h"
#include <sstream>
#include <iomanip>

//======================================================
// コンストラクタ
//======================================================
CPause::CPause(int nPriority) : CObject2D(nPriority), m_pTexture(nullptr), m_pVtxBuff(nullptr), m_Keyboard(nullptr), m_JoyPad(nullptr),
m_nTexIdx(0), m_nSelectPause(0), m_nPauseBGTex(0), m_pPauseOptions{}
{

}

//======================================================
// デストラクタ
//======================================================
CPause::~CPause()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CPause::Init()
{
	m_Keyboard = CManager::GetKeyboard();
	m_JoyPad = CManager::GetJoyPad();

    LPDIRECT3DTEXTURE9 pTex;

    pTex = CManager::GetTexture()->GetAddress(CManager::GetTexture()->Regist("data\\Texture\\000.png"));

    m_nTexIdx = CObject2D::Create(pTex, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f , -1.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 0.5);

    pTex = CManager::GetTexture()->GetAddress(CManager::GetTexture()->Regist("data\\Texture\\pauseBG.png"));

    m_nPauseBGTex = CObject2D::Create(pTex, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, -1.0f), SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.75f, 1.0f, 1.0f);

    float fInitialPointY = 380.0f;

    for (int i = 0; i < 3; i++, fInitialPointY += 75.0f)
    {
        std::ostringstream filename;
        filename << "data\\Texture\\pause" << std::setfill('0') << std::setw(2) << (i + 1) << ".png";
        pTex = CManager::GetTexture()->GetAddress(CManager::GetTexture()->Regist(filename.str().c_str()));

        float alpha = (i == m_nSelectPause) ? 1.0f : 0.5f;

        m_pPauseOptions[i] = CObject2D::Create(pTex, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, fInitialPointY, 0.0f), 400.0f, 60.0f, 1.0f, alpha);
    }

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CPause::Uninit()
{
    for (int i = 0; i < 3; i++)
    {
        if (m_pPauseOptions[i] != nullptr)
        {
            m_pPauseOptions[i]->SetDeath();
            m_pPauseOptions[i] = nullptr;
        }
    }

    if (m_nTexIdx != nullptr)
    {
        m_nTexIdx->SetDeath();
        m_nTexIdx = nullptr;
    }

    if (m_nPauseBGTex != nullptr)
    {
        m_nPauseBGTex->SetDeath();
        m_nPauseBGTex = nullptr;
    }

    CObject2D::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CPause::Update()
{

    // アルファ値を更新
    for (int i = 0; i < 3; i++)
    {
        float alpha = (i == m_nSelectPause) ? 1.0f : 0.5f;

        if (m_pPauseOptions[i] != nullptr)
        {
            m_pPauseOptions[i]->SetColor(alpha);
        }
    }
}

//======================================================
// 描画処理
//======================================================
void CPause::Draw()
{

}

//=================================
// 入力処理
//=================================
void CPause::SelectPause(CGame* game)
{
    // 上下キー入力
    if (m_Keyboard->GetTrigger(DIK_W) || m_Keyboard->GetTrigger(DIK_UP) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_UP) == true)
    {
        m_nSelectPause = (m_nSelectPause - 1 + 3) % 3; // 上へ移動（3 枚ループ）
    }
    else if (m_Keyboard->GetTrigger(DIK_S) || m_Keyboard->GetTrigger(DIK_DOWN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_DOWN) == true)
    {
        m_nSelectPause = (m_nSelectPause + 1) % 3; // 下へ移動（3 枚ループ）
    }

    // 決定キー入力
    if (m_Keyboard->GetTrigger(DIK_RETURN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_A) == true)
    {
        if (m_nSelectPause == 0)
        {
            game->SetPauseSwitch(false);
            //SetDeath();
        }
        else if (m_nSelectPause == 1)
        {
            CManager::SetMode(CScene::MODE::MODE_GAME);
        }
        else if (m_nSelectPause == 2)
        {
            game->SetQuit(true);
            //CManager::SetMode(CScene::MODE::MODE_STAGESELECT);
        }
        CManager::SetPaused(false);
    }
}

//======================================================
// ポーズ画面の生成処理
//======================================================
CPause* CPause::Create()
{
    CPause* pPause = new CPause;

    if (pPause != nullptr)
    {
        pPause->Init();
       // pPause->SetUseDeath(true);
    }
    return  pPause;

}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CPause::SetDeath()
{
    Uninit(); // すべてのポーズ用テクスチャを削除
    CObject::SetDeath();
}
