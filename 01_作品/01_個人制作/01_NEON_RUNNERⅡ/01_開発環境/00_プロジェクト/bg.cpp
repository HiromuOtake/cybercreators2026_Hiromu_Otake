//==============================================
//
// 3D�X�N���[���A�N�V����[bg.cpp]
// Author: hiromu otake
//
//==============================================

#include "bg.h"
#include "texture.h"

//======================================================
// �R���X�g���N�^
//======================================================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CBg::~CBg()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CBg::Init()
{
	CObject2D::SetWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT);
	CObject2D::SetTexture(1.0f);
	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	CObject2D::Init();

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CBg::Uninit()
{
	CObject2D::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CBg::Update()
{
	CObject2D::Update();
}

//======================================================
// �`�揈��
//======================================================
void CBg::Draw()
{
	CObject2D::Draw();
}

//=====================================================
// �w�i�̐���
//=====================================================
CBg* CBg::Create(CScene::MODE mode, D3DXVECTOR3 pos)
{
	CBg* pBg = new CBg;
	int nId = 0;

	if (pBg != nullptr)
	{
		switch (mode)
		{
		case CScene::MODE::MODE_TITLE:
			nId = CManager::GetTexture()->Regist("data\\Texture\\title.png");
			break;

		case CScene::MODE::MODE_TUTORIAL:
			nId = CManager::GetTexture()->Regist("data\\Texture\\game.png");
			break;

		case CScene::MODE::MODE_GAME:
			nId = CManager::GetTexture()->Regist("data\\Texture\\game.png");
			break;

		case CScene::MODE::MODE_RESULT:
			nId = CManager::GetTexture()->Regist("data\\Texture\\result001.png");
			break;

		default:
			break;
		}

		pBg->SetType(TYPE_BG);
		pBg->Init();
		pBg->SetPos(pos);
		pBg->BindTexture(CManager::GetTexture()->GetAddress(nId));
		pBg->SetUseDeath(true);
	}
	return  pBg;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBg::SetDeath()
{
	CObject::SetDeath();
}