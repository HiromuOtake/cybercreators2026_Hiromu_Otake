//==============================================
//
//ATG制作[score.cpp]
//Author: hiromu otake
//
//==============================================


#include "main.h"
#include "player.h"
#include "input.h"
#include "score.h"
#include "title.h"
#include "game.h"
#include "result.h"

// 静的メンバ初期化
int CScore::m_SaveScore = 0;

//=====================================
// コンストラクタ
//=====================================
CScore::CScore(int nPriority) : CObject2D(nPriority), m_pTexture(nullptr), m_nScore(0), m_pNumber{}
{

}

//=====================================
// デストラクタ
//=====================================
CScore::~CScore()
{

}

//==============================================
//スコアの初期化処理
//==============================================
HRESULT CScore::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//==============================================
//スコアの終了処理
//==============================================
void CScore::Uninit(void)
{
	CObject2D::Uninit();
}

//==============================================
//スコアの更新処理
//==============================================
void CScore::Update(void)
{
	CObject2D::Update();
}

//==============================================
//スコアの描画処理
//==============================================
void CScore::Draw(void)
{
	CObject2D::Draw();
}

//==============================================
//スコアの生成
//==============================================
CScore* CScore::Create(float fpos, float fposX, float fposY, float fsizeX, float fsizeY)
{
	CScore* pScore = new CScore;
	
	float fData = 30.0f;

	if (pScore != nullptr)
	{//スコアが使用されていない
		pScore->Init();
		for (int i = 0; i < m_MAX_SCORE; i++)
		{
			pScore->m_pNumber[i] = CNumber::Create(D3DXVECTOR3(fpos - fData - fposX * i, fposY, 0.0f), fsizeX, fsizeY);
		}
		pScore->SetUseDeath(false);
	}
	return  pScore;
}

//==============================================
//スコアの設定処理
//==============================================
void CScore::SetScore(int nScore)
{
	int aPosTexU;      //各桁の数字を格納
	m_nScore = nScore;
	int nTemp = m_nScore;
	int nCntScore;

	for (nCntScore = 0; nCntScore < m_MAX_SCORE; nCntScore++)
	{
		aPosTexU = (nTemp % 10);
		nTemp /= 10;
		m_pNumber[nCntScore]->SetTexturePos(aPosTexU);
	}
}

//==============================================
//スコアの加算処理
//==============================================
void CScore::AddScore(int nValue)
{
	SetScore(m_nScore + nValue);
}

//==============================================
//スコアの減算処理
//==============================================
void CScore::SddScore(int nValue)
{
	SetScore(m_nScore - nValue);
}

//==============================================
//スコアの取得
//==============================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//==============================================
// リザルトに使う用のスコアを保存
//==============================================
void CScore::SaveSetScore(int nScore)
{
	m_SaveScore = nScore;
}

//==============================================
// リザルトに使う用のスコアを保存
//==============================================
int CScore::GetSaveScore()
{
	return  m_SaveScore;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CScore::SetDeath()
{
	CObject::SetDeath();

	for (int nCnt = 0; nCnt < m_MAX_SCORE; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->SetUseDeath(true);
			m_pNumber[nCnt]->SetDeath();
			m_pNumber[nCnt] = nullptr;
		}
	}
}
