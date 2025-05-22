//==============================================
//
// ALTER_EGO[light.cpp]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "light.h"
#include "input.h"

//====================================
// �R���X�g���N�^
//====================================
CLight::CLight()
{
	// ���C�g���̃N���A
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));
}

//====================================
// �f�X�g���N�^
//====================================
CLight::~CLight()
{

}

//=====================================
// �����ݒ�
//=====================================
HRESULT CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();

	D3DXVECTOR3 vecDir;			//�ݒ�p�x�N�g��

	for (int nCntLight = 0; nCntLight < m_MAXLIGHT; nCntLight++)
	{
		//���C�g�̎�ނ�ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		switch (nCntLight)
		{
		case 0:
			vecDir = D3DXVECTOR3(m_LIGHT_X_0, -m_LIGHT_Y_0, m_LIGHT_Z_0);
			break;

		case 1:
			vecDir = D3DXVECTOR3(m_LIGHT_X_1, -m_LIGHT_Y_1, -m_LIGHT_Z_1);
			break;

		case 2:
			vecDir = D3DXVECTOR3(m_LIGHT_X_2, m_LIGHT_Y_2, m_LIGHT_Z_2);
			break;

		case 3:
			vecDir = D3DXVECTOR3(-m_LIGHT_X_3, m_LIGHT_Y_3, -m_LIGHT_Z_3);
			break;

		default:
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);          //�x�N�g���𐳋K������
		m_aLight[nCntLight].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);

	}
	return S_OK;
}

//=====================================
// �I������
//=====================================
void CLight::Uninit()
{

}

//=====================================
// �X�V����
//=====================================
void CLight::Update()
{

}
