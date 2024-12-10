//==============================================
//
//ATG����[score.cpp]
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

// �ÓI�����o������
int CScore::m_SaveScore = 0;

//=====================================
// �R���X�g���N�^
//=====================================
CScore::CScore(int nPriority) : CObject2D(nPriority), m_pTexture(nullptr), m_nScore(0), m_pNumber{}
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CScore::~CScore()
{

}

//==============================================
//�X�R�A�̏���������
//==============================================
HRESULT CScore::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//==============================================
//�X�R�A�̏I������
//==============================================
void CScore::Uninit(void)
{
	CObject2D::Uninit();
}

//==============================================
//�X�R�A�̍X�V����
//==============================================
void CScore::Update(void)
{
	CObject2D::Update();
}

//==============================================
//�X�R�A�̕`�揈��
//==============================================
void CScore::Draw(void)
{
	CObject2D::Draw();
}

//==============================================
//�X�R�A�̐���
//==============================================
CScore* CScore::Create(float fpos, float fposX, float fposY, float fsizeX, float fsizeY)
{
	CScore* pScore = new CScore;
	
	float fData = 30.0f;

	if (pScore != nullptr)
	{//�X�R�A���g�p����Ă��Ȃ�
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
//�X�R�A�̐ݒ菈��
//==============================================
void CScore::SetScore(int nScore)
{
	int aPosTexU;      //�e���̐������i�[
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
//�X�R�A�̉��Z����
//==============================================
void CScore::AddScore(int nValue)
{
	SetScore(m_nScore + nValue);
}

//==============================================
//�X�R�A�̌��Z����
//==============================================
void CScore::SddScore(int nValue)
{
	SetScore(m_nScore - nValue);
}

//==============================================
//�X�R�A�̎擾
//==============================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//==============================================
// ���U���g�Ɏg���p�̃X�R�A��ۑ�
//==============================================
void CScore::SaveSetScore(int nScore)
{
	m_SaveScore = nScore;
}

//==============================================
// ���U���g�Ɏg���p�̃X�R�A��ۑ�
//==============================================
int CScore::GetSaveScore()
{
	return  m_SaveScore;
}

//=========================================
// ���S�t���O�ݒ菈��
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
