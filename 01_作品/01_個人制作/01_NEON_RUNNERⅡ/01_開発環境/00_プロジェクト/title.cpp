//==============================================
//
// 3D�X�N���[���A�N�V����[game.cpp]
// Author: hiromu otake
//
//==============================================

#include "title.h"
#include "bg.h"

//======================================================
// �R���X�g���N�^
//======================================================
CTitle::CTitle() : m_pTexture(nullptr), m_pVtxBuff(nullptr)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CTitle::~CTitle()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CTitle::Init()
{
	CScene::Init();

	CBg::Create(CScene::MODE::MODE_TITLE, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT* 0.5f, 0.0f));

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CTitle::Uninit()
{
	CScene::Uninit();

	CSound* pSound = CManager::GetSound();

	pSound->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);
}

//======================================================
// �X�V����
//======================================================
void CTitle::Update()
{
	CScene::Update();
}

//======================================================
// �`�揈��
//======================================================
void CTitle::Draw()
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