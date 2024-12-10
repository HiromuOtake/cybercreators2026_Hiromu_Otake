//==============================================
//
// 3D�X�N���[���A�N�V����[game.cpp]
// Author: hiromu otake
//
//==============================================

#include "result.h"
#include "bg.h"

//======================================================
// �R���X�g���N�^
//======================================================
CResult::CResult() : m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pScore(nullptr)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CResult::~CResult()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CResult::Init()
{
	CScene::Init();


	if (m_pScore == nullptr)
	{
		m_pScore = CScore::Create(1100, 80.0f, 385.0f, 100.0f, 100.0f);
	}

	m_pScore->SetScore(m_pScore->GetSaveScore());

	CBg::Create(CScene::MODE::MODE_RESULT, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CResult::Uninit()
{
	CSound* pSound = CManager::GetSound();

	pSound->StopAllSound();

	CScene::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CResult::Update()
{
	CScene::Update();
}

//======================================================
// �`�揈��
//======================================================
void CResult::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	CRenderer* pRenderer = CManager::GetRenderere();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}