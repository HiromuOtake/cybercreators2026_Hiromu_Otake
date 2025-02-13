//==============================================
//
// ALTER_EGO[fade.cpp]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "fade.h"
#include <cassert>

// �ÓI�����o������
LPDIRECT3DTEXTURE9 CFade::m_pTextureTemp = nullptr;

//======================================================
// �R���X�g���N�^
//======================================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	m_Fade = FADE_NONE;
	m_colorFade = 0.0f;
}

//======================================================
// �f�X�g���N�^
//======================================================
CFade::~CFade()
{

}

//======================================================
// �����ݒ�
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
// �I������
//======================================================
void CFade::Uninit()
{
	CObject2D::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CFade::Update()
{
	OutputDebugStringA("[CFade::Update] �X�V�J�n\n");

	char debugMsg[256];
	sprintf(debugMsg, "[CFade::Update] ���݂̃t�F�[�h���: %d\n", m_Fade);
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
				OutputDebugStringA("[CFade::Update] FADE_IN ����\n");
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
				OutputDebugStringA("[CFade::Update] FADE_OUT ����\n");
				m_colorFade = 1.0f;
				m_Fade = FADE_IN;

				OutputDebugStringA("[CFade::Update] ���[�h�ύX�����s\n");
				CManager::SetMode(m_fademode);
				return;
			}
		}
	}

	OutputDebugStringA("[CFade::Update] �X�V�I��\n");
}

//======================================================
// �`�揈��
//======================================================
void CFade::Draw()
{
	CObject2D::Draw();
}

//=====================================================
// �t�F�[�h�̐���
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
//�t�F�[�h��ʂ̐ݒ菈��
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
		MessageBox(NULL, "FADE_IN �� FADE_OUT �̂ݐݒ�ł��܂��B", "�G���[", MB_OK);
	}
	SetColor(m_colorFade);
}

//==============================================
//�t�F�[�h��ʂ̎擾
//==============================================
CFade::FADE CFade::GetFade(void)
{
	return m_Fade;
}

//==============================================
//�t�F�[�h��ʂ̐F�̎擾
//==============================================
float CFade::FadeColor(void)
{
	return m_colorFade;
}
