//==============================================
//
// 3D�X�N���[���A�N�V����[player.cpp]
// Author: hiromu otake
//
//==============================================

#include "player.h"
#include "manager.h"
#include "camera.h"
#include "block.h"
#include "field.h"
#include "item.h"
#include "bullet.h"
#include "score.h"
#include "game.h"
#include "Tutorial.h"

bool CPlayer::m_bUse = true;
bool CPlayer::m_bGravity = false;
bool CPlayer::m_bGravityRotation = false;
bool CPlayer::m_bhalfwaypoint = true;

//==============================================
// �R���X�g���N�^
//==============================================
CPlayer::CPlayer(int nPriority) : CObjectX(nPriority), m_bIsLanding(false), m_bJumping(false), m_Keyboard(nullptr), m_JoyPad(nullptr), m_nModelIdx(0), m_nTextureIdx(0), m_nLife(0), m_nType(PLAYER_NONE), m_nDeathTimer(0), m_bIsRight(false)
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
	m_bIsRight = true;
	m_nType = PLAYER_NORMAL;

	m_Keyboard = CManager::GetKeyboard();
	m_JoyPad = CManager::GetJoyPad();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	
	m_nLife = m_PLAYER_LIFE;

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\stera.x");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx),
		pModel->GetTexture(m_nModelIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �I������
//==============================================
void CPlayer::Uninit()
{
	CObjectX::Uninit();
}

//==============================================
// �X�V����
//==============================================
void CPlayer::Update()
{
	CSound* pSound = CManager::GetSound();

	CBlockGravity::SetGravitySwitch(false);

	D3DXVECTOR3* pCamera = CCamera::GetRot();

	D3DXVECTOR3& pPos = CObjectX::GetPos();
	D3DXVECTOR3& pPosOld = CObjectX::GetPosOld();
	D3DXVECTOR3& pRot = CObjectX::GetRot();
	D3DXVECTOR3& pSize = CObjectX::GetSize();
	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pPosOld = pPos;

	PlayerSize.y = (float(floor(pSize.y)));

	if (m_nType == PLAYER_NORMAL)
	{
		if (m_Keyboard->GetPress(DIK_D) == true || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_RIGHT) == true)
		{
			m_move.x += sinf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;
			m_move.z += cosf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;

			if (m_bGravity == false)
			{
				pRot.z -= m_PLAYER_ROTATION_SPEED;
			}
			else
			{
				pRot.z += m_PLAYER_ROTATION_SPEED;
			}
			m_bIsRight = true;
		}
		else if (m_Keyboard->GetPress(DIK_A) == true || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_LEFT) == true)
		{
			m_move.x += sinf(pCamera->y + D3DX_PI * -m_LEFTRIGHT) * m_PLAYER_SPEED;
			m_move.z += cosf(pCamera->y + D3DX_PI * -m_LEFTRIGHT) * m_PLAYER_SPEED;

			if (m_bGravity == false)
			{
				pRot.z += m_PLAYER_ROTATION_SPEED;
			}
			else
			{
				pRot.z -= m_PLAYER_ROTATION_SPEED;
			}
			m_bIsRight = false;
		}

		if (m_Keyboard->GetTrigger(DIK_F) == true || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_X) == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);

			float move = m_PLAYER_SHOT_MOVE;

			if (m_bIsRight == false)
			{
				move *= -1.0f;
			}
			CBullet::Create(D3DXVECTOR3(pPos.x, pPos.y, pPos.z), D3DXVECTOR3(move, 0.0f, 0.0f));
			CObject::SetUseDeath(true);
		}

		if (m_bGravity == false)
		{
			if (m_bIsLanding == true)
			{
				m_move.y = 0.0f;
			}
			else
			{
				m_move.y -= m_GRAVITY_DIRECTION;
			}
		}
		else
		{
			if (m_bIsLanding == true)
			{
				m_move.y = 0.0f;
			}
			else
			{
				m_move.y += m_GRAVITY_DIRECTION;
			}
		}

		if (m_JumpCnt <= 1)
		{
			if (m_Keyboard->GetTrigger(DIK_SPACE) == true || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_A) == true)
			{
				pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_JUMP);

				if (m_bGravity == false)
				{
					m_move.y = +m_PLAYER_JUMP;
				}
				else
				{
					m_move.y = -m_PLAYER_JUMP;
				}
				m_JumpCnt++;
			}
		}
	}
	else
	{

	}

#if 0
	//�ʒu���X�V
	pPos.x += m_move.x;
	pPos.y += m_move.y;
	pPos.z += m_move.z;

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	//m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	D3DXVECTOR3 moveOld = m_move;	// �����蔻��ɂ���Ē��������O�̏��
	bool bIsLanding = false;
	bool bContinueCollisionBlock = true;	// �����蔻��𑱂���

	do
	{
		if (m_bIsLanding == false
			|| m_bJumping == true)
		{ // ���n���Ă��Ȃ��C�܂��̓W�����v���Ă���


			for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
			{// �v���C�I���e�B����
				for (int nCntObj = 0; nCntObj < m_MAXOBJECT; nCntObj++)
				{
					// ���E�̓����蔻��
					CollisionLEFTRIGHT(nCntPrio, nCntObj);

					// �㉺�̓����蔻��
					if (CollisionUPDOWN(bIsLanding, nCntPrio, nCntObj))
					{
						pPos = pPosOld;		// ���Ƃɖ߂�
						m_move = moveOld;	// ���Ƃɖ߂�
						break;
					}
				}
			}
			bContinueCollisionBlock = false;	// �����蔻��I��
		}
		else
		{
			for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
			{// �v���C�I���e�B����
				for (int nCntObj = 0; nCntObj < m_MAXOBJECT; nCntObj++)
				{
					// �㉺�̓����蔻��
					CollisionUPDOWN(bIsLanding, nCntPrio, nCntObj);
					// ���E�̓����蔻��
					CollisionLEFTRIGHT(nCntPrio, nCntObj);
					break;
				}
			}

			bContinueCollisionBlock = false;	// �����蔻��I��
		}
	} while (bContinueCollisionBlock);

	m_bIsLanding = bIsLanding;

	//m_bIsLanding = CPlayer::Collision();
#else

	pPos.z += m_move.z;

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	//m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	bool bIsLanding = false;

	//�ʒu���X�V
	pPos.x += m_move.x;

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// �v���C�I���e�B����

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			// ���E�̓����蔻��
			CollisionLEFTRIGHT(pObj);
			pObj->GetNext();
			pObj = pObj->GetNext();
		}
	}

	//�ʒu���X�V
	pPos.y += m_move.y;

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// �v���C�I���e�B����

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			// �㉺�̓����蔻��
			CollisionUPDOWN(bIsLanding, pObj);
			pObj->GetNext();
			pObj = pObj->GetNext();
		}
	}

	m_bIsLanding = bIsLanding;

#endif // 0

	if (m_nLife <= 0)
	{
		m_nType = PLAYER_DEATH;
		m_nDeathTimer++;

		if (m_nDeathTimer == m_DEATH_COUNT)
		{
			if (m_bhalfwaypoint == true)
			{
				pPos.x = m_RESET_PLAYER_POS_X;
				pPos.y = m_RESET_PLAYER_POS_Y;
			}
			else if (m_bhalfwaypoint == false)
			{
				pPos.x = 4000;
				pPos.y = -800;
			}

			m_nType = PLAYER_NORMAL;
			m_nLife = 1;
			m_nDeathTimer = 0;
			m_bGravity = false;

			if (m_pScore->GetScore() == 0)
			{

			}
			else
			{
				m_pScore->SddScore(100);
			}
		}
		return;
	}

	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		if (m_bUse == false)
		{
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_GOAL);

			CManager::SetMode(CScene::MODE::MODE_GAME);
			m_bUse = true;
			m_bGravity = false;
		}
	}
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (m_bUse == false)
		{
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_GOAL);		
			
			m_pScore->SaveSetScore(m_pScore->m_nScore);

			CManager::SetMode(CScene::MODE::MODE_RESULT);
			m_bUse = true;
			m_bGravity = false;
			m_bhalfwaypoint = true;
		}
	}
	CObjectX::Update();
}

//==============================================
// �`�揈��
//==============================================
void CPlayer::Draw()
{
	if (m_nType == PLAYER_DEATH)
	{

	}
	else
	{
		CObjectX::Draw();
	}
}

//==============================================
//�����蔻��
//==============================================
#if 0
bool CPlayer::Collision()
{
	bool bIsLanding = false;	//���n���Ă��邩�ǂ���

	D3DXVECTOR3& pPos = CObjectX::GetPos();
	D3DXVECTOR3& pPosOld = CObjectX::GetPosOld();
	D3DXVECTOR3& pSize = CObjectX::GetSize();

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(pSize.x)));
	PlayerSize.y = (float(floor(pSize.y)));
	PlayerSize.z = (float(floor(pSize.z)));

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// �v���C�I���e�B����

		CObject* pObj = CObject::GetTop(nCntPrio);

		if (pObj != nullptr)
		{// pObj��nullptr����Ȃ��Ȃ�

			CObject::TYPE type = pObj->GetType();

			if (type == CObject::TYPE::TYPE_BLOCK)
			{// type��BLOCK�Ȃ�

				CBlock* pBlock = (CBlock*)pObj;

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 pBlockMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 pBlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				// �����̈ʂ��Ȃ�����
				pBlockSize.x = (float)(floor(pBlock->GetSize().x));
				pBlockSize.y = (float)(floor(pBlock->GetSize().y));
				pBlockSize.z = (float)(floor(pBlock->GetSize().z));

				pBlockMin.x = (float)(floor(pBlock->GetMin().x));
				pBlockMin.y = (float)(floor(pBlock->GetMin().y));
				pBlockMin.z = (float)(floor(pBlock->GetMin().z));

				pBlockMax.x = (float)(floor(pBlock->GetMax().x));
				pBlockMax.y = (float)(floor(pBlock->GetMax().y));
				pBlockMax.z = (float)(floor(pBlock->GetMax().z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
						pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
						pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{// �㑤
						pPos.y = pBlockPos.y + (pBlockSize.y * m_HALF_SIZE) + (PlayerSize.y * m_HALF_SIZE);
						bIsLanding = true;
					}
					else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
						pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
						pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{// ����
						pPos.y = pBlockPos.y - (pBlockSize.y * m_HALF_SIZE) - (PlayerSize.y * m_HALF_SIZE);
						bIsLanding = true;
					}
					else if (pPos.y  < pBlockPos.y + pBlockMax.y &&
						pPos.y + PlayerSize.y  > pBlockPos.y)
					{
						////�����̓����蔻��
						//if (pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockMax.z &&
						//	pPosOld.z - PlayerSize.z * m_HALF_SIZE >= pBlockPos.z + pBlockMax.z &&
						//	pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x + pBlockMin.x &&
						//	pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockMax.x)
						//{
						//	pPos.z = pBlockPos.z + pBlockMax.z + (PlayerSize.z * m_HALF_SIZE);
						//}
						//
						////��O���̓����蔻��
						//else if (pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z + pBlockMin.z &&
						//	pPosOld.z + PlayerSize.z * m_HALF_SIZE <= pBlockPos.z + pBlockMin.z &&
						//	pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x + pBlockMin.x &&
						//	pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockMax.x)
						//{
						//	pPos.z = pBlockPos.z + pBlockMin.z - (PlayerSize.z * m_HALF_SIZE);
						//}

						//�E���̓����蔻��
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockMax.x &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockMax.x &&
							pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z + pBlockMin.z &&
							pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockMax.z)
						{
							pPos.x = pBlockPos.x + pBlockMax.x + (PlayerSize.x * m_HALF_SIZE);
						}

						//�����̓����蔻��
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x + pBlockMin.x &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x + pBlockMin.x &&
							pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z + pBlockMin.z &&
							pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockMax.z)
						{
							pPos.x = pBlockPos.x + pBlockMin.x - (PlayerSize.x * m_HALF_SIZE);
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_NEEDLE)
				{
					if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
						pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
						pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{// �㑤
						m_nLife -= 1;
					}
					else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
						pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
						pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{// ����
						m_nLife -= 1;
					}
					else if (pPos.y  < pBlockPos.y + pBlockMax.y &&
						pPos.y + PlayerSize.y  > pBlockPos.y)
					{
						//�E���̓����蔻��
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockMax.x &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockMax.x &&
							pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z + pBlockMin.z &&
							pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockMax.z)
						{
							m_nLife -= 1;
						}

						//�����̓����蔻��
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x + pBlockMin.x &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x + pBlockMin.x &&
							pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z + pBlockMin.z &&
							pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockMax.z)
						{
							m_nLife -= 1;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_GRAVITY)
				{
					if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
						pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
						pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{// �㑤
						GravityChanger();
					}
					else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
						pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
						pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{// ����
						GravityChanger();
					}
					else if (pPos.y  < pBlockPos.y + pBlockMax.y &&
						pPos.y + PlayerSize.y  > pBlockPos.y)
					{
						//�E���̓����蔻��
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockMax.x &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockMax.x &&
							pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z + pBlockMin.z &&
							pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockMax.z)
						{
							GravityChanger();
						}

						//�����̓����蔻��
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x + pBlockMin.x &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x + pBlockMin.x &&
							pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z + pBlockMin.z &&
							pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockMax.z)
						{
							GravityChanger();
						}
					}
				}
			}
		}
	}
	return bIsLanding;
}
#endif // 0

//=====================================================
// �d�͐؂�ւ�����
//=====================================================
bool CPlayer::GravityChanger()
{
	return m_bGravity = !m_bGravity;
}

//=====================================================
// �㉺�̓����蔻��
//=====================================================
bool CPlayer::CollisionUPDOWN(bool& bIsLanding, CObject* pObj)
{
	CSound* pSound = CManager::GetSound();

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

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// type��BLOCK�Ȃ�

			CBlock* pBlock = (CBlock*)pObj;

			D3DXVECTOR3 pBlockPos = pBlock->GetPos();
			D3DXVECTOR3 pBlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			CBlock::BLOCK pBlockType = pBlock->GetBlockType();

			// �����̈ʂ��Ȃ�����
			D3DXVECTOR3 BlockSize = pBlock->GetSize();
			pBlockSize.x = (float)(floor(BlockSize.x));
			pBlockSize.y = (float)(floor(BlockSize.y));
			pBlockSize.z = (float)(floor(BlockSize.z));

			if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// �㑤
					pPos.y = pBlockPos.y + (pBlockSize.y * m_HALF_SIZE) + (PlayerSize.y * m_HALF_SIZE);
					m_move.y = 0.0f;
					if (m_bGravity == false)
					{
						bIsLanding = true;
						m_bIsLanding = true;
						m_JumpCnt = 0;
					}
				}
				else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
					pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// ����
					pPos.y = pBlockPos.y - (pBlockSize.y * m_HALF_SIZE) - (PlayerSize.y * m_HALF_SIZE);
					m_move.y = 0.0f;
					if (m_bGravity == true)
					{
						bIsLanding = true;
						m_bIsLanding = true;
						m_JumpCnt = 0;
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_NEEDLE)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
				{// �㑤
					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DEATH);

					m_nLife -= 1;
				}
				else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
				{// ����
					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DEATH);

					m_nLife -= 1;
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_NEEDLEDOWN)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
				{// �㑤
					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DEATH);

					m_nLife -= 1;
				}
				else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
				{// ����
					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DEATH);

					m_nLife -= 1;
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_GRAVITY)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
				{// �㑤
					GravityChanger();
					CBlockGravity::SetGravitySwitch(true);
				}
				else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
				{// ����
					GravityChanger();
					CBlockGravity::SetGravitySwitch(true);
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_DOOR)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y &&
					pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// �㑤
					pPos.y = pBlockPos.y + (pBlockSize.y) + (PlayerSize.y * m_HALF_SIZE);
					m_move.y = 0.0f;
					bIsLanding = true;
					m_bIsLanding = true;
					m_JumpCnt = 0;
				}
				else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y &&
					pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// ����
					pPos.y = pBlockPos.y - (PlayerSize.y * m_HALF_SIZE);
					m_move.y = 0.0f;
					bIsLanding = true;
					m_bIsLanding = true;
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// �㑤
					pPos.y = pBlockPos.y + (pBlockSize.y * m_HALF_SIZE) + (PlayerSize.y * m_HALF_SIZE);
					m_move.y = 0.0f;
					if (m_bGravity == false)
					{
						bIsLanding = true;
						m_bIsLanding = true;
						m_JumpCnt = 0;
					}
				}
				else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
					pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// ����
					pPos.y = pBlockPos.y - (pBlockSize.y * m_HALF_SIZE) - (PlayerSize.y * m_HALF_SIZE);
					m_move.y = 0.0f;
					if (m_bGravity == true)
					{
						bIsLanding = true;
						m_bIsLanding = true;
						m_JumpCnt = 0;
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// �㑤
					m_bUse = false;
				}
				else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
					pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// ����
					m_bUse = false;
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_HALFWAYPOINT)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPosOld.y - PlayerSize.y * m_HALF_SIZE >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// �㑤
					m_bhalfwaypoint = false;
				}
				else if (pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
					pPosOld.y + PlayerSize.y * m_HALF_SIZE <= pBlockPos.y - pBlockSize.y * m_HALF_SIZE &&
					pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
					pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
				{// ����
					m_bhalfwaypoint = false;
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
	CSound* pSound = CManager::GetSound();

	D3DXVECTOR3& pPos = CObjectX::GetPos();
	D3DXVECTOR3& pPosOld = CObjectX::GetPosOld();
	D3DXVECTOR3& pSize = CObjectX::GetSize();

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(pSize.x)));
	PlayerSize.y = (float(floor(pSize.y)));
	PlayerSize.z = (float(floor(pSize.z)));

	//CObject* pObj = CObject::GetTop(nCntPrio);

	if (pObj != nullptr)
	{// pObj��nullptr����Ȃ��Ȃ�

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// type��BLOCK�Ȃ�

			CBlock* pBlock = (CBlock*)pObj;

			D3DXVECTOR3 pBlockPos = pBlock->GetPos();
			D3DXVECTOR3 pBlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			CBlock::BLOCK pBlockType = pBlock->GetBlockType();

			// �����̈ʂ��Ȃ�����
			D3DXVECTOR3 BlockSize = pBlock->GetSize();
			pBlockSize.x = (float)(floor(BlockSize.x));
			pBlockSize.y = (float)(floor(BlockSize.y));
			pBlockSize.z = (float)(floor(BlockSize.z));

			if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE)
				{
					////�����̓����蔻��
					//if (pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockMax.z &&
					//	pPosOld.z - PlayerSize.z * m_HALF_SIZE >= pBlockPos.z + pBlockMax.z &&
					//	pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x + pBlockMin.x &&
					//	pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockMax.x)
					//{
					//	pPos.z = pBlockPos.z + pBlockMax.z + (PlayerSize.z * m_HALF_SIZE);
					//}
					//
					////��O���̓����蔻��
					//else if (pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z + pBlockMin.z &&
					//	pPosOld.z + PlayerSize.z * m_HALF_SIZE <= pBlockPos.z + pBlockMin.z &&
					//	pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x + pBlockMin.x &&
					//	pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockMax.x)
					//{
					//	pPos.z = pBlockPos.z + pBlockMin.z - (PlayerSize.z * m_HALF_SIZE);
					//}

					//�E���̓����蔻��
					if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
						pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{
						pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (PlayerSize.x * m_HALF_SIZE);
						m_move.x = 0.0f;
					}
					//�����̓����蔻��
					else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
					{
						pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - (PlayerSize.x * m_HALF_SIZE);
						m_move.x = 0.0f;
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_NEEDLE)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE)
				{
					//�E���̓����蔻��
					if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE &&
						pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
					{
						pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DEATH);

						m_nLife -= 1;
					}
					//�����̓����蔻��
					else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
						pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE)
					{
						pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DEATH);

						m_nLife -= 1;
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_NEEDLEDOWN)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE)
				{
					//�E���̓����蔻��
					if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE &&
						pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
					{
						pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DEATH);

						m_nLife -= 1;
					}
					//�����̓����蔻��
					else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
						pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE)
					{
						pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DEATH);

						m_nLife -= 1;
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_GRAVITY)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE_LOOSE &&
					pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE_LOOSE)
				{
					//�E���̓����蔻��
					if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE &&
						pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE_LOOSE)
					{
						GravityChanger();
						CBlockGravity::SetGravitySwitch(true);
					}
					//�����̓����蔻��
					else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE &&
						pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE_LOOSE)
					{
						GravityChanger();
						CBlockGravity::SetGravitySwitch(true);
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_DOOR)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y &&
					pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y)
				{
					//�E���̓����蔻��
					if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
						pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{
						pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (PlayerSize.x * m_HALF_SIZE);
						m_move.x = 0.0f;
					}
					//�����̓����蔻��
					else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
					{
						pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - (PlayerSize.x * m_HALF_SIZE);
						m_move.x = 0.0f;
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE)
				{
					//�E���̓����蔻��
					if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
						pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
					{
						pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (PlayerSize.x * m_HALF_SIZE);
						m_move.x = 0.0f;

					}
					//�����̓����蔻��
					else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
						pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
					{
						pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - (PlayerSize.x * m_HALF_SIZE);
						m_move.x = 0.0f;
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
			{
				if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
					pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE)
				{
					//�E���̓����蔻��
					if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE - 30.0f &&
						pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE - 30.0f)
					{
						m_bUse = false;

					}
					//�����̓����蔻��
					else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE + 30.0f &&
						pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE + 30.0f)
					{
						m_bUse = false;
					}
				}
			}
			else if (pBlockType == CBlock::BLOCK::BLOCK_HALFWAYPOINT)
			{
			if (pPos.y - PlayerSize.y * m_HALF_SIZE < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
				pPos.y + PlayerSize.y * m_HALF_SIZE > pBlockPos.y - pBlockSize.y * m_HALF_SIZE)
			{
				//�E���̓����蔻��
					if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE  - 30.0f&&
						pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE- 30.0f)
					{
						m_bhalfwaypoint = false;
					}
					//�����̓����蔻��
					else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE+ 30.0f &&
						pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE+ 30.0f)
					{
						m_bhalfwaypoint = false;
					}
				}
			}
		}
	}
}

//=====================================================
// �S�[�����̎擾
//=====================================================
bool& CPlayer::GetGoal()
{
	return m_bUse;
}

//=====================================================
// �d�͂̌����̏��̎擾
//=====================================================
bool& CPlayer::GetGravity()
{
	return m_bGravity;
}

//=====================================================
// �d�͂̃u���b�N�̉�]���擾
//=====================================================
bool& CPlayer::GetGravityRotation()
{
	return m_bGravityRotation;
}

//=====================================================
// �X�R�A�̎擾
//=====================================================
CScore* CPlayer::GetScore()
{
	if (m_pScore != nullptr)
	{
		return m_pScore;
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
		pPlayer->m_pScore = CScore::Create(SCREEN_WIDTH, 35.0f, 30.0f, 40.0f, 40.0f);
	}
	return  pPlayer;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CPlayer::SetDeath()
{
	CObject::SetDeath();

	if (m_pScore != nullptr)
	{
		m_pScore->SetUseDeath(true);
		m_pScore->SetDeath();
		m_pScore = nullptr;
	}

}
