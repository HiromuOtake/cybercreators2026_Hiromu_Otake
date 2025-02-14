//==============================================
//
// ALTER_EGO[player.cpp]
// Author: hiromu otake
//
//==============================================

#include "player.h"
#include "camera.h"
#include "block.h"
#include "game.h"

bool CPlayer::m_bUse = true;

//==============================================
// �R���X�g���N�^
//==============================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority), m_max{ 0.0f,0.0f,0.0f }, m_min{ 0.0f,0.0f,0.0f }, m_move{ 0.0f,0.0f,0.0f }
, m_bIsLanding(false), m_bJumping(false), m_IsRight(false), m_bCloneActive(false), m_bUseItem(false), m_pCloneCircle(nullptr), m_pClone(nullptr),m_pItem(nullptr), m_Keyboard(nullptr), m_JoyPad(nullptr), m_pModelParts{}
, m_nModelIdx(0), m_nTextureIdx(0), m_nLife(0), m_nType(PLAYER_NONE), m_nDeathTimer(0), m_nJumpCnt(0), m_nRandomAction(0), m_nTitleJump(0)
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CPlayer::~CPlayer()
{

}

//==============================================
// �����ݒ�
//==============================================
HRESULT CPlayer::Init()
{
	m_IsRight = true;
	m_nType = PLAYER_NORMAL;

	m_Keyboard = CManager::GetKeyboard();
	m_JoyPad = CManager::GetJoyPad();
	
	m_nLife = m_PLAYER_LIFE;

	int nCnt = 0;

	CCharacter::Init();

	CCharacter::LoadMotion(&nCnt);

	// �T�C�Y�v�Z�p�̏�����
	m_min = { FLT_MAX, FLT_MAX, FLT_MAX };
	m_max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

	for (int nCount = 0; nCount < m_NUM_MODEL_PARTS; nCount++)
	{
		D3DXVECTOR3& Partspos = CCharacter::GetModelParts(nCount)->GetPos();
		D3DXVECTOR3& pPos = CCharacter::GetPos();

		D3DXVECTOR3 pWoarldPos = Partspos + pPos;

		if (pWoarldPos.x < m_min.x)
		{
			m_min.x = pWoarldPos.x;
		}
		else if (pWoarldPos.x > m_max.x)
		{
			m_max.x = pWoarldPos.x;
		}

		if (pWoarldPos.y < m_min.y)
		{
			m_min.y = pWoarldPos.y;
		}
		else if (pWoarldPos.y > m_max.y)
		{
			m_max.y = pWoarldPos.y;
		}

		if (pWoarldPos.z < m_min.z)
		{
			m_min.z = pWoarldPos.z;
		}
		else if (pWoarldPos.z > m_max.z)
		{
			m_max.z = pWoarldPos.z;
		}
		m_size = m_max - m_min;
	}
	return S_OK;
}

//==============================================
// �I������
//==============================================
void CPlayer::Uninit()
{
	if (m_pClone != nullptr)
	{
		m_pClone->Uninit();
		m_pClone = nullptr;
	}

	CCharacter::Uninit();
}

//==============================================
// �X�V����
//==============================================
void CPlayer::Update()
{
	CSound* pSound = CManager::GetSound();

	if (CManager::IsPaused())
	{
		return;
	}
	else
	{
		if (m_pCloneCircle != nullptr)
		{
			// �N���[���I�𒆂̑���
			HandleCloneSelection();				// �N���[���I���̏���
			if (CManager::IsPaused())
			{
				if (m_pCloneCircle != nullptr)
				{
					m_pCloneCircle->Update();			// �N���[���ʒu�X�V
				}
			}
		}
		else
		{
			// �ʏ펞�̃v���C���[����
			PlayerMovement();
		}
	}
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (!CManager::IsPaused())
		{
			// K�L�[�ŃN���[���I�����J�n
			if (m_Keyboard->GetTrigger(DIK_K) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_X))
			{
				m_bCloneActive = !m_bCloneActive;	// �\���؂�ւ�
				if (m_bCloneActive)
				{
					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SPAWNSIRCLE);
					m_pCloneCircle = m_pCloneCircle->Create(GetPos()); 		// �`����ėL����
					m_pCloneCircle->Activate();
					if (m_pClone != nullptr)
					{
						m_pClone->SetStopClone(true);
						m_pClone->SetDeath();
						m_pClone = nullptr;
					}
				}
				else if (!m_bCloneActive)
				{
					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DELETECIRCLE);
					m_pCloneCircle->SetDeath();		// ���\�[�X�̉��
					m_pCloneCircle = nullptr;
					CManager::SetPaused(false);		// �|�[�Y����

					if (m_pClone != nullptr)
					{
						m_pClone->SetStopClone(false);
					}
				}
			}
		}
	}
}

//==============================================
// �N���[���I������
//==============================================
void CPlayer::HandleCloneSelection() 
{
	CSound* pSound = CManager::GetSound();

	// �ړ��L�[�Ə\���L�[�őI���ʒu��ύX
	if (m_Keyboard->GetTrigger(DIK_W) ||m_Keyboard->GetTrigger(DIK_UP) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_UP) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(0);  // ��
	}
	else if (m_Keyboard->GetTrigger(DIK_S) ||m_Keyboard->GetTrigger(DIK_DOWN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_DOWN) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(1);  // ��
	}
	else if (m_Keyboard->GetTrigger(DIK_D) ||m_Keyboard->GetTrigger(DIK_RIGHT) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_RIGHT) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(2);  // �E
	}
	else if (m_Keyboard->GetTrigger(DIK_A) ||m_Keyboard->GetTrigger(DIK_LEFT) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_LEFT) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(3);  // ��
	}

	// Enter�L�[�ŃN���[������
	if ((m_Keyboard->GetTrigger(DIK_RETURN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_A) == true))
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DELETECIRCLE);

		GenerateClone();
		m_bCloneActive = false;
		m_pCloneCircle->SetDeath();		// ���\�[�X�̉��
		m_pCloneCircle = nullptr;

		if (m_pClone != nullptr)
		{
			m_pClone->SetStopClone(false);
		}
	}
}

//==============================================
// �N���[����������
//==============================================
void CPlayer::GenerateClone() 
{
	D3DXVECTOR3 clonePos = m_pCloneCircle->GetSelectedPosition();
	m_pClone = CClone::Create(clonePos);  // �N���[���𐶐�
}

//==============================================
// �ʏ�X�V����
//==============================================
void CPlayer::PlayerMovement()
{
	CSound* pSound = CManager::GetSound();

	D3DXVECTOR3* pCamera = CCamera::GetRot();

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
	D3DXVECTOR3& pRot = CCharacter::GetRot();

	pPosOld = pPos;

	if (CManager::GetMode() == CScene::MODE_TITLE)
	{
		TitlePlayerMovement();
	}
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (m_nType == PLAYER_NORMAL)
		{
			if (m_Keyboard->GetPress(DIK_D) == true || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_RIGHT) == true)
			{
				SetMotion(MOTION_MOVE);

				m_move.x += sinf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;
				m_move.z += cosf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;

				pRot.y = pCamera->y + D3DX_PI * -0.5f;
			}
			else if (m_Keyboard->GetPress(DIK_A) == true || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_LEFT) == true)
			{
				SetMotion(MOTION_MOVE);

				m_move.x += sinf(pCamera->y + D3DX_PI * -m_LEFTRIGHT) * m_PLAYER_SPEED;
				m_move.z += cosf(pCamera->y + D3DX_PI * -m_LEFTRIGHT) * m_PLAYER_SPEED;

				pRot.y = pCamera->y + D3DX_PI * +0.5f;
			}
			else
			{
				SetMotion(MOTION_NEUTRAL);
			}

			if (m_nJumpCnt <= 0)
			{
				if (m_Keyboard->GetTrigger(DIK_SPACE) == true || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_A) == true)
				{
					m_move.y = +m_PLAYER_JUMP;
					m_nJumpCnt++;

					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_JUMP);
				}
			}
		}
	}

	m_move.y -= 1.0f;

	//�ʒu���X�V
	pPos.z += m_move.z;

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	//m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	bool bLanding = false;

	pPos.x += m_move.x;


	for (int nCntPrio = 0; nCntPrio < 15; nCntPrio++)
	{// �v���C�I���e�B����

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			if (IsBadReadPtr(pObj, sizeof(CObject)))
			{
				break;
			}

			// �㉺�̓����蔻��
			CollisionLEFTRIGHT(pObj);
			pObj = pObj->GetNext();
		}
	}

	pPos.y += m_move.y;

	for (int nCntPrio = 0; nCntPrio < 15; nCntPrio++)
	{// �v���C�I���e�B����

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			if (IsBadReadPtr(pObj, sizeof(CObject)))
			{
				break;
			}

			// ���E�̓����蔻��
			CollisionUPDOWN(bLanding, pObj);
			pObj = pObj->GetNext();
		}
	}

	m_bIsLanding = bLanding;

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (m_bUse == false)
		{
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_GOAL);

			CManager::SetMode(CScene::MODE::MODE_RESULT);
			m_bUse = true;
		}
	}

	//if (m_bUseItem == true)
	//{
	//	m_pItem->SetDeath();
	//}

	CCharacter::PlayerMotion();

	CCharacter::Update();
}

//==============================================
// �^�C�g���ł̃v���C���[����
//==============================================
void CPlayer::TitlePlayerMovement()
{
	D3DXVECTOR3* pCamera = CCamera::GetRot();

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pRot = CCharacter::GetRot();

	if (m_nType == PLAYER_NORMAL)
	{
		SetMotion(MOTION_MOVE);

		m_move.x += sinf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;
		m_move.z += cosf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;

		pRot.y = pCamera->y + D3DX_PI * -0.5f;

		m_nTitleJump++;

		//if (m_nRandomAction == 1) // �����_���l��1�̏ꍇ�A�W�����v�����s
		{
			if (m_nJumpCnt <= 0)
			{
				if (m_nTitleJump > 30)
				{
					m_move.y = +m_PLAYER_JUMP;
					m_nJumpCnt++;

					m_nTitleJump = 0;
				}
			}
		}
		if (pPos.x > 2500)
		{
			//// �����_���V�[�h�ݒ�i�K�v�ɉ����āj
			//srand(static_cast<unsigned int>(time(nullptr)));

			//// �����_���A�N�V��������x��������
			//m_nRandomAction = rand() % 2; // 0 �܂��� 1 �������_���ɐݒ�

			pPos.x = -100;
			pPos.y = -600;
		}
	}
}

//==============================================
// �`�揈��
//==============================================
void CPlayer::Draw()
{
	// �N���[���I�𒆂ɕ`��
	if (m_pCloneCircle != nullptr)
	{
		m_pCloneCircle->Draw();
	}

	if (m_nType == PLAYER_DEATH)
	{

	}
	else
	{
		CCharacter::Draw();
	}
}

//=====================================================
// �㉺�̓����蔻��
//=====================================================
bool CPlayer::CollisionUPDOWN(bool& bIsLanding, CObject* pObj)
{
	// ���f���p�[�c�̃��[���h���W���擾
	//D3DXVECTOR3 pPos = { CCharacter::GetModelParts(1)->GetWoarldMatrix()._41 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._42 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._43 };

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	// �v���C���[�̉ߋ��̍��W���擾
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
	// ���f���p�[�c�̃T�C�Y���擾
	D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	//D3DXVECTOR3 PartsPosOld = pPosOld + pPos;

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(m_size.x)));
	PlayerSize.y = (float(floor(m_size.y)));
	PlayerSize.z = (float(floor(m_size.z)));

	if (pObj != nullptr)
	{// pObj��nullptr����Ȃ��Ȃ�

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// type��BLOCK�Ȃ�

			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
			if (pBlock != nullptr)
			{
				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = pBlock->GetMin();
				D3DXVECTOR3 pBlockMax = pBlock->GetMax();
				D3DXVECTOR3 pBlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// �����̈ʂ��Ȃ�����
				D3DXVECTOR3 BlockSize = pBlock->GetSize();
				pBlockSize.x = (float)(floor(BlockSize.x));
				pBlockSize.y = (float)(floor(BlockSize.y));
				pBlockSize.z = (float)(floor(BlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					m_pCollision->CollisionPushBoxUpDown(pPos, pPosOld, PlayerSize, pBlockPos, pBlockSize, m_move, bIsLanding, m_nJumpCnt);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_DOOR)
				{
					CBlockDoor* pDoor = dynamic_cast<CBlockDoor*>(pObj);
					if (pDoor && pDoor->IsOpen())
					{
						// �����J���Ă���ꍇ�͓����蔻����X�L�b�v
						return false;
					}
					m_pCollision->CollisionPushBoxUpDown(pPos, pPosOld, PlayerSize, pBlockPos, pBlockSize, m_move, bIsLanding, m_nJumpCnt);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					m_pCollision->CollisionPushBoxUpDown(pPos, pPosOld, PlayerSize, pBlockPos, pBlockSize, m_move, bIsLanding, m_nJumpCnt);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
				{
					m_pCollision->CollisionHitTriggerBoxUpDown(pPos, pPosOld, PlayerSize, pBlockPos, pBlockSize, m_bUse);
				}
			}
		}
		if (type == CObject::TYPE::TYPE_ITEM)
		{// type��BLOCK�Ȃ�

			CItem* pItem = dynamic_cast<CItem*>(pObj);
			if (pItem != nullptr)
			{
				CItem::ITEM pItemType = pItem->GetItemType();

				D3DXVECTOR3 pItemPos = pItem->GetPos();
				D3DXVECTOR3 pItemMin = pItem->GetMin();
				D3DXVECTOR3 pItemMax = pItem->GetMax();
				D3DXVECTOR3 pItemSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// �����̈ʂ��Ȃ�����
				D3DXVECTOR3 ItemSize = pItem->GetSize();
				pItemSize.x = (float)(floor(ItemSize.x));
				pItemSize.y = (float)(floor(ItemSize.y));
				pItemSize.z = (float)(floor(ItemSize.z));

				if (pItemType == CItem::ITEM::ITEM_STAR)
				{
					m_pCollision->CollisionHitTriggerBoxUpDown(pPos, pPosOld, PlayerSize, pItemPos, pItemSize, m_bUseItem);
				}
			}
		}
	}
	return bIsLanding;
}

//=====================================================
// ���E�̓����蔻��
//=====================================================
void CPlayer::CollisionLEFTRIGHT(CObject* pObj)
{
	//D3DXVECTOR3 pPos = { CCharacter::GetModelParts(1)->GetWoarldMatrix()._41 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._42 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._43 };
	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();

	//D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(m_size.x)));
	PlayerSize.y = (float(floor(m_size.y)));
	PlayerSize.z = (float(floor(m_size.z)));

	if (pObj != nullptr)
	{// pObj��nullptr����Ȃ��Ȃ�

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// type��BLOCK�Ȃ�


			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
			if (pBlock != nullptr)
			{
				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = pBlock->GetMin();
				D3DXVECTOR3 pBlockMax = pBlock->GetMax();
				D3DXVECTOR3 pBlockSize = pBlock->GetSize();

				// �����̈ʂ��Ȃ�����
				D3DXVECTOR3 BlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				BlockSize.x = (float)(floor(pBlockSize.x));
				BlockSize.y = (float)(floor(pBlockSize.y));
				BlockSize.z = (float)(floor(pBlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					m_pCollision->CollisionPushBoxLeftRight(pPos, pPosOld, PlayerSize, pBlockPos, BlockSize);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_DOOR)
				{
					CBlockDoor* pDoor = dynamic_cast<CBlockDoor*>(pObj);
					if (pDoor && pDoor->IsOpen())
					{
						// �����J���Ă���ꍇ�͓����蔻����X�L�b�v
						return;
					}

					m_pCollision->CollisionPushBoxLeftRight(pPos, pPosOld, PlayerSize, pBlockPos, BlockSize);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					m_pCollision->CollisionPushBoxLeftRight(pPos, pPosOld, PlayerSize, pBlockPos, BlockSize);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
				{
					m_pCollision->CollisionHitTriggerBoxLeftRight(pPos, pPosOld, PlayerSize, pBlockPos, BlockSize, m_bUse);
				}
			}
		}
		if (type == CObject::TYPE::TYPE_ITEM)
		{// type��ITEM�Ȃ�

			CItem* pItem = dynamic_cast<CItem*>(pObj);
			if (pItem != nullptr)
			{
				CItem::ITEM pItemType = pItem->GetItemType();

				D3DXVECTOR3 pItemPos = pItem->GetPos();
				D3DXVECTOR3 pItemSize = pItem->GetSize();

				// �����̈ʂ��Ȃ�����
				D3DXVECTOR3 ItemSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				ItemSize.x = (float)(floor(pItemSize.x));
				ItemSize.y = (float)(floor(pItemSize.y));
				ItemSize.z = (float)(floor(pItemSize.z));

				if (pItemType == CItem::ITEM::ITEM_STAR)
				{
					m_pCollision->CollisionHitTriggerBoxLeftRight(pPos, pPosOld, PlayerSize, pItemPos, ItemSize, m_bUseItem);
				}
			}
		}
	}
}

//=====================================================
// ���f���̐���
//=====================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->SetType(TYPE_PLAYER);
		pPlayer->Init();
		pPlayer->SetPos(pos);
	}
	return  pPlayer;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CPlayer::SetDeath()
{
	CObject::SetDeath();
}