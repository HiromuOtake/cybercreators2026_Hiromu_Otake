//==============================================
//
// 3D�X�N���[���A�N�V����[camera.cpp]
// Author: hiromu otake
//
//==============================================

#include "camera.h"
#include "game.h"
#include "Tutorial.h"

// �ÓI�����o������
D3DXVECTOR3 CCamera::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=====================================
// �R���X�g���N�^
//=====================================
CCamera::CCamera() : m_Keyboard(nullptr)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CCamera::~CCamera()
{

}

//=====================================
// �����ݒ�
//=====================================
HRESULT CCamera::Init()
{
	m_Keyboard = CManager::GetKeyboard();
	m_posV = D3DXVECTOR3(0.0f, 400.0f, -400.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//=====================================
// �I������
//=====================================
void CCamera::Uninit()
{

}

//===============================
// �X�V����
//===============================
void CCamera::Update()
{
	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		if (CTutorial::GetPlayer() != nullptr)
		{
			m_posR = CTutorial::GetPlayer()->GetPos();
		}
	}
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (CGame::GetPlayer() != nullptr)
		{
			m_posR = CGame::GetPlayer()->GetPos();
		}
	}

	m_posV.x = m_posR.x + sinf(m_rot.y + D3DX_PI) * 1600.0f;
	m_posV.z = m_posR.z + cosf(m_rot.y + D3DX_PI) * 1600.0f;

	m_posV.y = m_posR.y;
}

//===============================
//�J�����̐ݒ菈��
//===============================
void CCamera::SetCamera()
{
	D3DXVECTOR3 PosV = m_posV;
	D3DXVECTOR3 PosR = m_posR;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	CRenderer* pRenderer = CManager::GetRenderere();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,     //��ʂ̃A�X�y�N�g�� 
		10.0f,											//Z�l�̍ŏ��l
		3000.0f);										//Z�l�̍ő�l

	//D3DXMatrixOrthoLH(&m_mtxProjection,
	//	(float)SCREEN_WIDTH,
	//	(float)SCREEN_HEIGHT,
	//	10.0f,
	//	3000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = D3DXVECTOR3(0, 0, 0);

	//if (m_nShakeTime > 0)
	//{
	//	m_nShakeTime--;
	//	adjust.x += m_fShakePower;
	//	adjust.y += m_fShakePower;

	//	adjust.x = (float)(rand()% 100 - 50) * m_fShakePower;
	//	adjust.y = (float)(rand()% 100 - 50) * m_fShakePower;

	//	PosV += adjust;
	//	PosR += adjust;
	//}

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&PosV,		//���_
		&PosR,		//�����_
		&m_vecU);	//������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//===============================
//�J�����̌����̎擾
//===============================
D3DXVECTOR3* CCamera::GetRot()
{
	return &m_rot;
}

////===============================
////�J�����̗h��̐ݒ�
////===============================
//void CCamera::SetShake(int nShakeTime, float fShakePower)
//{
//	m_nShakeTime = nShakeTime;
//	m_fShakePower = fShakePower;
//}

//=====================================================
// �t�B�[���h�̐���
//=====================================================
CCamera* CCamera::Create()
{
	CCamera* pCamera = new CCamera;

	if (pCamera != nullptr)
	{
		pCamera->Init();
	}
	return  pCamera;
}
