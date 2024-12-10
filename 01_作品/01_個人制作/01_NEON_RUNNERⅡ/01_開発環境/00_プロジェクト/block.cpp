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
#include "player.h"

bool CBlockGravity::m_GravitySwitch = false;

//==============================================
// �R���X�g���N�^
//==============================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority), m_BlockType(BLOCK_NONE), m_Keyboard(nullptr), m_pVtxBuff(nullptr), m_nModelIdx(0), m_nTextureIdx(0), m_move{ 0.0f,0.0f,0.0f }, m_nTimer(0), m_bOpen(false)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockNeedle::CBlockNeedle(int nPriority) : CBlock(nPriority)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockNeedleDown::CBlockNeedleDown(int nPriority) : CBlock(nPriority)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockGravity::CBlockGravity(int nPriority) : CBlock(nPriority)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockButton::CBlockButton(int nPriority) : CBlock(nPriority)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockDoor::CBlockDoor(int nPriority) : CBlock(nPriority)
{
	m_Timer = 0;
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
CBlockNeedleDown::~CBlockNeedleDown()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockGravity::~CBlockGravity()
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
// �����ݒ�
//==============================================
HRESULT CBlock::Init()
{
	SetType(TYPE_BLOCK);

	m_Keyboard = CManager::GetKeyboard();

	CModel* pModel = CManager::GetModel();

	if (m_BlockType == BLOCK::BLOCK_NORMAL)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonblock.x");
	}
	else if (m_BlockType == BLOCK::BLOCK_NEEDLE)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonneedle.x");
	}
	else if (m_BlockType == BLOCK::BLOCK_NEEDLEDOWN)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonneedledown.x");
	}
	else if (m_BlockType == BLOCK::BLOCK_GRAVITY)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\gravityblock.x");
	}
	else if (m_BlockType == BLOCK::BLOCK_DOOR)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neondoor.x");
	}
	else if (m_BlockType == BLOCK::BLOCK_BUTTON)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\switch.x");
	}
	else if (m_BlockType == BLOCK::BLOCK_GOAL)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\goal.x");
	}
	else if (m_BlockType == BLOCK::BLOCK_HALFWAYPOINT)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\halfway_point.x");
	}

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx),
		pModel->GetTexture(m_nModelIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockNeedle::Init()
{
	CBlock::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockNeedleDown::Init()
{
	CBlock::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockGravity::Init()
{
	CBlock::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockButton::Init()
{
	CBlock::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockDoor::Init()
{
	CBlock::Init();

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

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
void CBlockNeedleDown::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockGravity::Uninit()
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
// �X�V����
//==============================================
void CBlock::Update()
{
	D3DXVECTOR3& pPos = CObjectX::GetPos();

	pPos.z += m_move.z;

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//�ʒu���X�V
	pPos.x += m_move.x;

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// �v���C�I���e�B����
		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			// ���E�̓����蔻��
			BlockCollisionLEFTRIGHT(pObj);
			pObj->GetNext();
			pObj = pObj->GetNext();
		}
	}

	//�ʒu���X�V
	pPos.y += m_move.y;

	m_move.y += (0.0f - m_move.y) * 0.1f;

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// �v���C�I���e�B����
		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			// �㉺�̓����蔻��
			BlockCollisionUPDOWN(pObj);
			pObj->GetNext();
			pObj = pObj->GetNext();
		}
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
void CBlockNeedleDown::Update()
{
	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockGravity::Update()
{
	bool& bGravity = CPlayer::GetGravity();

	if (m_GravitySwitch == true)
	{
		m_GravityChage = true;
	}

	if (m_GravityChage == true)
	{
		m_GravityTimer++;
		GetRot() += D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 30);

		if (m_GravityTimer == 30)
		{
			m_GravityTimer = 0;
			m_GravityChage = false;
		}
	}

	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockButton::Update()
{
	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockDoor::Update()
{
	bool bOpenDoor = false;

#if 0
	// �ő吔���s���Ȃ̂�While���g�p
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->GetNext();
		if (CBlock* pBlock = dynamic_cast<CBlock*>(pObj))
		{ // �u���b�N�N���X�Ƀ_�E���L���X�g
			std::string a = pBlock->GetPairKey();
			std::string b = GetPairKey();

			if (pBlock->GetPairKey() == GetPairKey() && GetPairKey() != "none")
			{ // �y�A�̃L�[����v����
				if (pBlock->GetOpenDoor())
				{
					bOpenDoor = true;
					break;
				}
			}
		}

		pObj = pNext;
	}
#else
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

			CBlock* block = dynamic_cast<CBlock*>(object);
			if (block == nullptr)
			{ // �󂾂���
				continue;
			}

			// �h�A���J���Ă���t���O���^������
			bOpenDoor = block->GetOpenDoor();
			break;
		}
	}
#endif

	if (bOpenDoor == true)
	{
#if 0
		D3DXVECTOR3& pMove = GetMove();

		pMove.y += 10.0f;

		m_Timer++;

		if (m_Timer >= 65)
		{
			pMove.y = 0.0f;
		}
#endif
		// m_Time * move = 200.0f �ł��邱�ƁI
		m_Timer++;
		if (m_Timer <= 20)
		{
			float move = 10.0f;
			GetPos() += D3DXVECTOR3(0.0f, move, 0.0f);
		}
	}

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
void CBlockNeedleDown::Draw()
{
	CBlock::Draw();
}

//==============================================
// �`�揈��
//==============================================
void CBlockGravity::Draw()
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

//=====================================================
// �㉺�̓����蔻��
//=====================================================
void CBlock::BlockCollisionUPDOWN(CObject* pObj)
{
	//bool bIsLanding = false;	//���n���Ă��邩�ǂ���

	D3DXVECTOR3& pPos = CObjectX::GetPos();
	D3DXVECTOR3& pPosOld = CObjectX::GetPosOld();
	D3DXVECTOR3& pSize = CObjectX::GetSize();

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(pSize.x)));
	PlayerSize.y = (float(floor(pSize.y)));
	PlayerSize.z = (float(floor(pSize.z)));

	if (pObj != nullptr)
	{// pObj��nullptr����Ȃ��Ȃ�

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BULLET)
		{// type��BLOCK�Ȃ�

			CBullet* pBullet = (CBullet*)pObj;

			D3DXVECTOR3& pBulletPos = pBullet->GetPos();
			D3DXVECTOR3 pBulletPosOld = pBullet->GetPosOld();
			D3DXVECTOR3 pBulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �����̈ʂ��Ȃ�����
			D3DXVECTOR3 BulletSize = pBullet->GetSize();
			pBulletSize.x = (float)(floor(BulletSize.x));
			pBulletSize.y = (float)(floor(BulletSize.y));
			pBulletSize.z = (float)(floor(BulletSize.z));

			if (m_BlockType == BLOCK::BLOCK_NORMAL)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// �㑤
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// ����
					pBullet->SetUse(true);
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_NEEDLE)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// �㑤
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// ����
					pBullet->SetUse(true);
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_GRAVITY)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// �㑤
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// ����
					pBullet->SetUse(true);
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_DOOR)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// �㑤
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// ����
					pBullet->SetUse(true);
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_BUTTON)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// �㑤
					m_bOpen = true;
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// ����
					m_bOpen = true;
					pBullet->SetUse(true);
				}
			}
		}
	}
}

//=====================================================
// ���E�̓����蔻��
//=====================================================
void CBlock::BlockCollisionLEFTRIGHT(CObject* pObj)
{
	CSound* pSound = CManager::GetSound();


	D3DXVECTOR3& pPos = CObjectX::GetPos();
	D3DXVECTOR3& pSize = CObjectX::GetSize();

	D3DXVECTOR3 BlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	BlockSize.x = (float(floor(pSize.x)));
	BlockSize.y = (float(floor(pSize.y)));
	BlockSize.z = (float(floor(pSize.z)));

	if (pObj != nullptr)
	{// pObj��nullptr����Ȃ��Ȃ�

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BULLET)
		{// type��BLOCK�Ȃ�

			CBullet* pBullet = (CBullet*)pObj;

			D3DXVECTOR3 pBulletPos = pBullet->GetPos();
			D3DXVECTOR3 pBulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �����̈ʂ��Ȃ�����
			D3DXVECTOR3 BulletSize = pBullet->GetSize();
			pBulletSize.x = (float)(floor(BulletSize.x));
			pBulletSize.y = (float)(floor(BulletSize.y));
			pBulletSize.z = (float)(floor(BulletSize.z));

			if (m_BlockType == BLOCK::BLOCK_NORMAL)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + BlockSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - BlockSize.y * m_HALF_SIZE)
				{
					//���E�̓����蔻��
					if (pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + BlockSize.x * m_HALF_SIZE &&
						pBulletPos.x + pBulletSize.x * m_HALF_SIZE >= pPos.x - BlockSize.x * m_HALF_SIZE)
					{
						pBullet->SetUse(true);
					}
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_NEEDLE)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + BlockSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - BlockSize.y * m_HALF_SIZE)
				{
					//���E�̓����蔻��
					if (pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + BlockSize.x * m_HALF_SIZE &&
						pBulletPos.x + pBulletSize.x * m_HALF_SIZE >= pPos.x - BlockSize.x * m_HALF_SIZE)
					{
						pBullet->SetUse(true);
					}
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_GRAVITY)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + BlockSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - BlockSize.y * m_HALF_SIZE)
				{
					//���E�̓����蔻��
					if (pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + BlockSize.x * m_HALF_SIZE &&
						pBulletPos.x + pBulletSize.x * m_HALF_SIZE >= pPos.x - BlockSize.x * m_HALF_SIZE)
					{
						pBullet->SetUse(true);
					}
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_DOOR)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + BlockSize.y &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y)
				{
					//���E�̓����蔻��
					if (pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + BlockSize.x * m_HALF_SIZE &&
						pBulletPos.x + pBulletSize.x * m_HALF_SIZE >= pPos.x - BlockSize.x * m_HALF_SIZE)
					{
						pBullet->SetUse(true);
					}
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_BUTTON)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + BlockSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - BlockSize.y * m_HALF_SIZE)
				{
					//���E�̓����蔻��
					if (pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + BlockSize.x * m_HALF_SIZE &&
						pBulletPos.x + pBulletSize.x * m_HALF_SIZE >= pPos.x - BlockSize.x * m_HALF_SIZE)
					{
						pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_BUTON);
						m_bOpen = true;
						pBullet->SetUse(true);
					}
				}
			}
		}
	}
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

//==============================================
// �u���b�N�̃^�C�v�擾����
//==============================================
bool &CBlock::GetOpenDoor()
{
	return m_bOpen;
}

//==============================================
// �u���b�N�̃^�C�v�擾����
//==============================================
bool &CBlockGravity::GetGravitySwitch()
{
	return m_GravitySwitch;
}

//==============================================
// �d�͂̉�]�����̐ݒ�
//==============================================
void CBlockGravity::SetGravitySwitch(bool GravitySwitch)
{
	m_GravitySwitch = GravitySwitch;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlock* CBlock::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlock* pBlock = new CBlock();

	if (pBlock != nullptr)
	{
		pBlock->m_BlockType = nType;
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
CBlockNeedleDown* CBlockNeedleDown::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockNeedleDown* pBlockNeedleDown = new CBlockNeedleDown();

	if (pBlockNeedleDown != nullptr)
	{
		pBlockNeedleDown->SetBlockType(nType);
		pBlockNeedleDown->Init();
		pBlockNeedleDown->SetPos(pos);
		pBlockNeedleDown->SetUseDeath(true);
	}
	return  pBlockNeedleDown;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockGravity* CBlockGravity::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockGravity* pBlockGravity = new CBlockGravity();

	if (pBlockGravity != nullptr)
	{
		pBlockGravity->SetBlockType(nType);
		pBlockGravity->Init();
		pBlockGravity->SetPos(pos);
		pBlockGravity->SetUseDeath(true);
	}
	return  pBlockGravity;
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
void CBlockNeedleDown::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockGravity::SetDeath()
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