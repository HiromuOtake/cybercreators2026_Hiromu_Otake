//==============================================
//
// 3D�X�N���[���A�N�V����[block.cpp]
// Author: hiromu otake
//
//==============================================

#include "block.h"
#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "particlemanager.h"
#include <random>

//==============================================
// �R���X�g���N�^
//==============================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority), m_BlockType(BLOCK_NONE), m_Keyboard(nullptr), m_pVtxBuff(nullptr), m_bOpen(false)
, m_nModelIdx(0), m_nTimer(0), m_nTexIdx(0), m_move{ 0.0f,0.0f,0.0f }
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockNeedle::CBlockNeedle(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockButton::CBlockButton(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0), m_bOpen(false)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockDoor::CBlockDoor(int nPriority) : CBlock(nPriority), m_deleteDoor(1.0f), m_nModelIdx(0), m_nTexIdx(0), m_Keyboard(nullptr), m_pPlayer(nullptr)
{
	m_Timer = 0;
}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockGoal::CBlockGoal(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlock::~CBlock()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockNeedle::~CBlockNeedle()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockButton::~CBlockButton()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockDoor::~CBlockDoor()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockGoal::~CBlockGoal()
{

}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlock::Init()
{
	SetType(TYPE_BLOCK);

	m_Keyboard = CManager::GetKeyboard();

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonblock.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\neonblock.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockNeedle::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonneedle.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\needle.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockButton::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\switch.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockDoor::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\door.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockGoal::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\goal.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\potal3.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �I������
//==============================================
void CBlock::Uninit()
{
	CObjectX::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockNeedle::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockButton::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockDoor::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockGoal::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �X�V����
//==============================================
void CBlock::Update()
{
	// ��]�s���K�p
	if (m_fRotation != 0.0f)
	{
		D3DXMATRIX matRotation;
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(m_fRotation));  // Y����]

		// ���[���h�s��ɉ�]��K�p
		D3DXMatrixMultiply(&m_matWorld, &matRotation, &m_matWorld);
	}

	CObjectX::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockNeedle::Update()
{
	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockButton::Update()
{
	std::random_device seed;
	std::mt19937 random(seed());
	int nMin = 1;
	int nMax = 4;
	float a = 1.0f;
	float b = 1.0f;

	std::uniform_int_distribution<> number(nMin, nMax);

	if (number(random) == 1)
	{
		a = 1.0f;
	}
	if (number(random) == 2)
	{
		b = 1.0f;
	}
	if (number(random) == 3)
	{
		a = -1.0f;
	}
	if (number(random) == 4)
	{
		b = -1.0f;
	}

	D3DXVECTOR3 pos = CBlockButton::GetPos();
	//CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(a, b, 0.0f));

	// �{�^����������Ă��邩�𔻒�
	bool bPressed = false;

	// ���胍�W�b�N�i�����Ń{�^����������Ă��邩�ǂ������v�Z�j
	for (const auto& object : CObject::GetAllObjects())
	{
		if (object->GetType() == TYPE_PLAYER)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(object);
			if (player != nullptr)
			{
				// �Փ˔���i�ȗ��\�j
				if (IsCollisionPlayer(player))
				{
					bPressed = true;
					break;
				}
			}

			CClone* clone = dynamic_cast<CClone*>(object);
			if (clone != nullptr)
			{
				// �Փ˔���i�ȗ��\�j
				if (IsCollisionClone(clone))
				{
					bPressed = true;
					break;
				}
			}
		}
	}

	if (m_bOpen != true)
	{
		// �{�^���̏�Ԃ��X�V
		m_bOpen = bPressed;
	}

	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockDoor::Update()
{
	//CSound* pSound = CManager::GetSound();

	bool bOpenDoor = false;

	// �L�[�̎擾
	const std::string& key = GetPairKey();
	if (key != "none")
	{ // �L�[�����݂���
		for (const auto& object : CObject::GetPair()[key])
		{
			if (object == nullptr)
			{ // �󂾂���
				continue;
			}

			if (this == object)
			{ // �������g������
				continue;
			}

			if (CBlockButton* button = dynamic_cast<CBlockButton*>(object))
			{
				if (button->GetOpenDoor())
				{
					//pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_BUTON);

					bOpenDoor = true;
					break;
				}
			}
		}
	}

	if (bOpenDoor == true)
	{
		m_deleteDoor--;

		CBlockDoor::SetScale(D3DXVECTOR3(m_deleteDoor, m_deleteDoor, m_deleteDoor));

		m_Timer++;
		if (m_Timer >= 20)
		{
			Uninit();
			CObject::SetDeath();
		}
	}
	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockGoal::Update()
{
	CBlock::Update();
}

//==============================================
// �`�揈��
//==============================================
void CBlock::Draw()
{
	CObjectX::Draw();
}

//==============================================
// �`�揈��
//==============================================
void CBlockNeedle::Draw()
{
	CBlock::Draw();
}

//==============================================
// �`�揈��
//==============================================
void CBlockButton::Draw()
{
	CBlock::Draw();
}

//==============================================
// �`�揈��
//==============================================
void CBlockDoor::Draw()
{
	CBlock::Draw();
}

//==============================================
// �`�揈��
//==============================================
void CBlockGoal::Draw()
{
	CBlock::Draw();
}

//==============================================
// �{�^���ƃv���C���[�̓����蔻��
//==============================================
bool CBlockButton::IsCollisionPlayer(CPlayer* player)
{
	D3DXVECTOR3 playerPos = player->GetPos();        // �v���C���[�̃��[���h���W
	D3DXVECTOR3 buttonPos = GetPos();                // �{�^���̃��[���h���W

	//// �p�[�e�B�N���}�l�[�W���[�̃C���X�^���X���擾
	//CParticleManager* pParticleManager = CManager::GetParticleManager();

	//// �p�[�e�B�N���𔭐�������
	//pParticleManager->EmitParticles(buttonPos, 50, 2.0f, 1.5f, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	// �v���C���[�ƃ{�^���̑��Έʒu���v�Z
	D3DXVECTOR3 relativePos = playerPos - buttonPos;

	// �{�^���̉�]�s����쐬�i�t��]�j
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(-m_fRotation));  // �t��]�Ń��[�J�����W�ɖ߂�

	// ���Έʒu���{�^���̃��[�J�����W�n�ɕϊ�
	D3DXVECTOR3 transformedPos;
	D3DXVec3TransformCoord(&transformedPos, &relativePos, &matRotationZ);

	// �{�^���̃T�C�Y���擾
	D3DXVECTOR3 buttonSize = GetSize();

	// �I�t�Z�b�g�l�̐ݒ�iX����Z���͏����߁AY���͂��̂܂܁j
	const float offsetXZ = 10.0;  // X����Z���̃I�t�Z�b�g�l�i�����蔻����k���j
	const float offsetY = 20.0f;   // Y���̃I�t�Z�b�g�i�K�v�Ȃ�������j

	// �ϊ���̍��W���g���ē����蔻����s��
	bool isOnTop = (transformedPos.y > 0.0f + offsetY && transformedPos.y < buttonSize.y - offsetY);

	// X����Z���͈͓̔��ɂ��邩�𔻒�i�I�t�Z�b�g��K�p�j
	return (transformedPos.x > -buttonSize.x + offsetXZ &&
		transformedPos.x < buttonSize.x - offsetXZ &&
		transformedPos.z > -buttonSize.z + offsetXZ &&
		transformedPos.z < buttonSize.z - offsetXZ &&
		isOnTop);
}

//==============================================
// �{�^���ƃN���[���̓����蔻��
//==============================================
bool CBlockButton::IsCollisionClone(CClone* clone)
{
	D3DXVECTOR3 clonePos = clone->GetPos();        // �v���C���[�̃��[���h���W
	D3DXVECTOR3 buttonPos = GetPos();                // �{�^���̃��[���h���W

	// �v���C���[�ƃ{�^���̑��Έʒu���v�Z
	D3DXVECTOR3 relativePos = clonePos - buttonPos;

	// �{�^���̉�]�s����쐬�i�t��]�j
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(-m_fRotation));  // �t��]�Ń��[�J�����W�ɖ߂�

	// ���Έʒu���{�^���̃��[�J�����W�n�ɕϊ�
	D3DXVECTOR3 transformedPos;
	D3DXVec3TransformCoord(&transformedPos, &relativePos, &matRotationZ);

	// �{�^���̃T�C�Y���擾
	D3DXVECTOR3 buttonSize = GetSize();

	// �I�t�Z�b�g�l�̐ݒ�iX����Z���͏����߁AY���͂��̂܂܁j
	const float offsetXZ = 20.0;  // X����Z���̃I�t�Z�b�g�l�i�����蔻����k���j
	const float offsetY = 20.0f;   // Y���̃I�t�Z�b�g�i�K�v�Ȃ�������j

	// �ϊ���̍��W���g���ē����蔻����s��
	bool isOnTop = (transformedPos.y > 0.0f + offsetY && transformedPos.y < buttonSize.y - offsetY);

	// X����Z���͈͓̔��ɂ��邩�𔻒�i�I�t�Z�b�g��K�p�j
	return (transformedPos.x > -buttonSize.x + offsetXZ &&
		transformedPos.x < buttonSize.x - offsetXZ &&
		transformedPos.z > -buttonSize.z + offsetXZ &&
		transformedPos.z < buttonSize.z - offsetXZ &&
		isOnTop);
}

//==============================================
// �u���b�N�̃^�C�v�ݒ菈��
//==============================================
void CBlock::SetBlockType(BLOCK BlockType)
{
	m_BlockType = BlockType;
}

//==============================================
// �u���b�N�̃^�C�v�擾����
//==============================================
CBlock::BLOCK CBlock::GetBlockType()
{
	return m_BlockType;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlock* CBlock::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlock* pBlock = new CBlock();

	if (pBlock != nullptr)
	{
		pBlock->SetBlockType(nType);
		pBlock->Init();
		pBlock->SetPos(pos);
		pBlock->SetUseDeath(true);
	}
	return  pBlock;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockNeedle* CBlockNeedle::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockNeedle* pBlockNeedle = new CBlockNeedle();

	if (pBlockNeedle != nullptr)
	{
		pBlockNeedle->SetBlockType(nType);
		pBlockNeedle->Init();
		pBlockNeedle->SetPos(pos);
		pBlockNeedle->SetUseDeath(true);
	}
	return  pBlockNeedle;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockButton* CBlockButton::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockButton* pBlockButton = new CBlockButton();

	if (pBlockButton != nullptr)
	{
		pBlockButton->SetBlockType(nType);
		pBlockButton->Init();
		pBlockButton->SetPos(pos);
		pBlockButton->SetUseDeath(true);
	}
	return  pBlockButton;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockDoor* CBlockDoor::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockDoor* pBlockDoor = new CBlockDoor();

	if (pBlockDoor != nullptr)
	{
		pBlockDoor->SetBlockType(nType);
		pBlockDoor->Init();
		pBlockDoor->SetPos(pos);
		pBlockDoor->SetUseDeath(true);
	}
	return  pBlockDoor;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockGoal* CBlockGoal::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockGoal* pBlockGial = new CBlockGoal();

	if (pBlockGial != nullptr)
	{
		pBlockGial->SetBlockType(nType);
		pBlockGial->Init();
		pBlockGial->SetPos(pos);
		pBlockGial->SetUseDeath(true);
	}
	return  pBlockGial;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlock::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockNeedle::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockButton::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockDoor::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockGoal::SetDeath()
{
	CObject::SetDeath();
}

//==============================================
// ���̏�Ԏ擾����
//==============================================
bool& CBlockButton::GetOpenDoor()
{
	return m_bOpen;
}

//==============================================
// �{�^���̃}�e���A���J���[�ύX����
//==============================================
void CBlockButton::SetMatColor(D3DMATERIAL9* pMat, int nMatIdx)
{
	pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 1.0f;

	if (m_bOpen == true)
	{
		if (nMatIdx == 2)
		{
			pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 0.5f;
		}
	}
	else if(m_bOpen == false)
	{
		if (nMatIdx == 2)
		{
			pMat->Diffuse.g = pMat->Diffuse.b = 0.0f;
		}
	}
}