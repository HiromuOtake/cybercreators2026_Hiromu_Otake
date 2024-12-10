////==============================================
////
//// 3Dスクロールアクション[fade.cpp]
//// Author: hiromu otake
////
////==============================================
//
//#include "manager.h"
//#include "fade.h"
//#include <cassert>
//
//// 静的メンバ初期化
//LPDIRECT3DTEXTURE9 CFade::m_pTextureTemp = nullptr;
//
////======================================================
//// コンストラクタ
////======================================================
//CFade::CFade(int nPriority) : CObject2D(nPriority)
//{
//	m_Fade = FADE_NONE;
//	m_colorFade = 0.0f;
//}
//
////======================================================
//// デストラクタ
////======================================================
//CFade::~CFade()
//{
//
//}
//
////======================================================
//// 初期設定
////======================================================
//HRESULT CFade::Init()
//{
//	CObject2D::SetWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
//
//	CObject2D::Init();
//
//	m_Fade = FADE_NONE;
//
//	return S_OK;
//}
//
////======================================================
//// 終了処理
////======================================================
//void CFade::Uninit()
//{
//
//}
//
////======================================================
//// 更新処理
////======================================================
//void CFade::Update()
//{
//	if (m_Fade != FADE_NONE)
//	{
//		if (m_Fade == FADE_IN)
//		{//フェードイン状態
//			m_colorFade -= 0.03f;          //ポリゴンを透明にしていく
//			CObject2D::SetColor(m_colorFade);
//
//			if (m_colorFade <= 0.0f)
//			{
//				m_colorFade = 0.0f;
//				CObject2D::SetColor(m_colorFade);
//				m_Fade = FADE_NONE;     //何もしていない状態に
//				SetDeath();
//				SetUseDeath(false);
//			}
//		}
//
//		else if (m_Fade == FADE_OUT)
//		{//フェードアウト状態
//			m_colorFade += 0.03f;          //ポリゴンを不透明にしていく
//			CObject2D::SetColor(m_colorFade);
//
//			if (m_colorFade >= 1.0f)
//			{
//				m_colorFade = 1.0f;
//				CObject2D::SetColor(m_colorFade);
//				m_Fade = FADE_IN;      //フェードイン状態に
//
//				//モード設定(次の画面に移行)
//				CManager::SetMode(m_fademode);
//				return;
//			}
//		}
//	}
//
//	//CObject2D::Update();
//}
//
////======================================================
//// 描画処理
////======================================================
//void CFade::Draw()
//{
//	CObject2D::Draw();
//}
//
////=====================================================
//// フェードの生成
////=====================================================
//CFade* CFade::Create(CScene::MODE mode)
//{
//	CFade* pFade = new CFade;
//
//	if (pFade != nullptr)
//	{
//		pFade->SetType(TYPE_FIELD);
//		pFade->Init();
//	}
//	return  pFade;
//}
//
////==============================================
////フェード画面の設定処理
////==============================================
//void CFade::SetFade(FADE fade, CScene::MODE modeNext)
//{
//	m_fademode = modeNext;
//	m_Fade = fade;
//
//	if (fade == FADE::FADE_IN)
//	{
//		m_colorFade = 1.0f;
//	}
//	else if(fade == FADE::FADE_OUT)
//	{
//		m_colorFade = 0.0f;
//	}
//	else
//	{
//		assert(false && "インかアウトで設定してください");
//	}
//	SetColor(m_colorFade);
//}
//
////==============================================
////フェード画面の取得
////==============================================
//CFade::FADE CFade::GetFade(void)
//{
//	return m_Fade;
//}
//
////==============================================
////フェード画面の色の取得
////==============================================
//float CFade::FadeColor(void)
//{
//	return m_colorFade;
//}
