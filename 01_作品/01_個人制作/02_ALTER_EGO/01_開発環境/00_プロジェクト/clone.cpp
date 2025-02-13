//==============================================
//
// ALTER_EGO[clone.cpp]
// Author: hiromu otake
//
//==============================================

#include "clone.h"
#include "manager.h"
#include "camera.h"
#include "block.h"
#include "field.h"
#include "item.h"
#include "bullet.h"
#include "game.h"
#include "Tutorial.h"
#include "character.h"

bool CClone::m_bUse = true;

//==============================================
// コンストラクタ
//==============================================
CClone::CClone(int nPriority) : CCharacter(nPriority), m_bLanding(false), m_bJumping(false), m_bStopClone(false), m_Keyboard(nullptr), m_JoyPad(nullptr), m_pModelParts{}
, m_nModelIdx(0), m_nTextureIdx(0), m_nLife(0), m_nType(PLAYER_NONE), m_nDeathTimer(0), m_nJumpCnt(0)
{

}

//==============================================
// デストラクタ
//==============================================
CClone::~CClone()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CClone::Init()
{
	m_nType = PLAYER_NORMAL;

	m_Keyboard = CManager::GetKeyboard();
	m_JoyPad = CManager::GetJoyPad();

	m_nLife = m_CLONE_LIFE;

	int nCnt = 0;

	CCharacter::Init();

	CCharacter::LoadMotion(&nCnt);

	// サイズ計算用の初期化
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
// 終了処理
//==============================================
void CClone::Uninit()
{
	CCharacter::Uninit();
}

//==============================================
// 更新処理
//==============================================
void CClone::Update()
{
	if (CManager::IsPaused())
	{
		if (m_Keyboard->GetTrigger(DIK_RETURN) || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_B) == true)
		{
			CManager::SetPaused(false); // ポーズ解除
		}

		return;
	}

	if (m_bStopClone == true)
	{
		if (m_Keyboard->GetTrigger(DIK_RETURN) || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_B) == true)
		{
			CManager::SetPaused(false); // ポーズ解除
		}
	}
	else if(m_bStopClone == false)
	{
		D3DXVECTOR3* pCamera = CCamera::GetRot();
		D3DXVECTOR3& pPos = CCharacter::GetPos();
		D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
		D3DXVECTOR3& pRot = CCharacter::GetRot();

		pPosOld = pPos;

		if (m_nType == PLAYER_NORMAL)
		{

			if (m_Keyboard->GetPress(DIK_D) == true || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_RIGHT) == true)
			{
				SetMotion(MOTION_MOVE);

				m_move.x += sinf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_CLONE_SPEED;
				m_move.z += cosf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_CLONE_SPEED;

				pRot.y = pCamera->y + D3DX_PI * -0.5f;
			}
			else if (m_Keyboard->GetPress(DIK_A) == true || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_LEFT) == true)
			{
				SetMotion(MOTION_MOVE);

				m_move.x += sinf(pCamera->y + D3DX_PI * -m_LEFTRIGHT) * m_CLONE_SPEED;
				m_move.z += cosf(pCamera->y + D3DX_PI * -m_LEFTRIGHT) * m_CLONE_SPEED;

				pRot.y = pCamera->y + D3DX_PI * +0.5f;
			}
			else
			{
				CCharacter::SetMotion(MOTION_NEUTRAL);
			}

			if (m_nJumpCnt <= 0)
			{
				if (m_Keyboard->GetTrigger(DIK_SPACE) == true || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_A) == true)
				{
					m_move.y = +m_CLONE_JUMP;
					m_nJumpCnt++;

					CSound* pSound = CManager::GetSound();

					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_JUMP);
				}
			}
		}

		m_move.y -= 1.0f;

		//位置を更新
		pPos.z += m_move.z;

		//移動量を更新(減衰させる)
		m_move.x += (0.0f - m_move.x) * 0.1f;
		//m_move.y += (0.0f - m_move.y) * 0.1f;
		m_move.z += (0.0f - m_move.z) * 0.1f;

		bool bIsLanding = false;

		pPos.x += m_move.x;

		for (int nCntPrio = 0; nCntPrio < 15; nCntPrio++)
		{// プライオリティ分回す

			CObject* pObj = CObject::GetTop(nCntPrio);

			while (pObj != nullptr)
			{
				if (IsBadReadPtr(pObj, sizeof(CObject)))
				{
					break;
				}

				// 左右の当たり判定
				CollisionLEFTRIGHT(pObj);
				pObj = pObj->GetNext();
			}
		}

		pPos.y += m_move.y;

		for (int nCntPrio = 0; nCntPrio < 15; nCntPrio++)
		{// プライオリティ分回す

			CObject* pObj = CObject::GetTop(nCntPrio);

			while (pObj != nullptr)
			{
				if (IsBadReadPtr(pObj, sizeof(CObject)))
				{
					break;
				}

				// 上下の当たり判定
				CollisionUPDOWN(bIsLanding, pObj);
				pObj = pObj->GetNext();
			}
		}

		m_bLanding = bIsLanding;

		CCharacter::PlayerMotion();

		CCharacter::Update();
	}
}

//==============================================
// 描画処理
//==============================================
void CClone::Draw()
{
	if (m_nType == PLAYER_DEATH)
	{

	}
	else
	{
		CCharacter::Draw();
	}
}

//=====================================================
// 上下の当たり判定
//=====================================================
bool CClone::CollisionUPDOWN(bool& bIsLanding, CObject* pObj)
{
	// モデルパーツのワールド座標を取得
	//D3DXVECTOR3 pPos = { CCharacter::GetModelParts(1)->GetWoarldMatrix()._41 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._42 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._43 };

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	// プレイヤーの過去の座標を取得
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
	// モデルパーツのサイズを取得
	D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	//D3DXVECTOR3 PartsPosOld = pPosOld + pPos;

	D3DXVECTOR3 CloneSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CloneSize.x = (float(floor(m_size.x)));
	CloneSize.y = (float(floor(m_size.y)));
	CloneSize.z = (float(floor(m_size.z)));

	if (pObj != nullptr)
	{// pObjがnullptrじゃないなら

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// typeがBLOCKなら

			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
			if (pBlock != nullptr)
			{
				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = pBlock->GetMin();
				D3DXVECTOR3 pBlockMax = pBlock->GetMax();
				D3DXVECTOR3 pBlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// 少数の位を省く処理
				D3DXVECTOR3 BlockSize = pBlock->GetSize();
				pBlockSize.x = (float)(floor(BlockSize.x));
				pBlockSize.y = (float)(floor(BlockSize.y));
				pBlockSize.z = (float)(floor(BlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					m_pCollision->CollisionPushBoxUpDown(pPos, pPosOld, CloneSize, pBlockPos, pBlockSize, m_move, bIsLanding, m_nJumpCnt);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_DOOR)
				{
					CBlockDoor* pDoor = dynamic_cast<CBlockDoor*>(pObj);
					if (pDoor && pDoor->IsOpen())
					{
						// 扉が開いている場合は当たり判定をスキップ
						return false;
					}
					m_pCollision->CollisionPushBoxUpDown(pPos, pPosOld, CloneSize, pBlockPos, pBlockSize, m_move, bIsLanding, m_nJumpCnt);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					m_pCollision->CollisionPushBoxUpDown(pPos, pPosOld, CloneSize, pBlockPos, pBlockSize, m_move, bIsLanding, m_nJumpCnt);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
				{
					m_pCollision->CollisionHitTriggerBoxUpDown(pPos, pPosOld, CloneSize, pBlockPos, pBlockSize, m_bUse);
				}
			}
		}
	}
	return bIsLanding;
}

//=====================================================
// 左右の当たり判定
//=====================================================
void CClone::CollisionLEFTRIGHT(CObject* pObj)
{
	//D3DXVECTOR3 pPos = { CCharacter::GetModelParts(1)->GetWoarldMatrix()._41 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._42 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._43 };
	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();

	//D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	D3DXVECTOR3 CloneSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CloneSize.x = (float(floor(m_size.x)));
	CloneSize.y = (float(floor(m_size.y)));
	CloneSize.z = (float(floor(m_size.z)));

	if (pObj != nullptr)
	{// pObjがnullptrじゃないなら

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// typeがBLOCKなら


			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
			if (pBlock != nullptr)
			{
				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = pBlock->GetMin();
				D3DXVECTOR3 pBlockMax = pBlock->GetMax();
				D3DXVECTOR3 pBlockSize = pBlock->GetSize();

				// 少数の位を省く処理
				D3DXVECTOR3 BlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				BlockSize.x = (float)(floor(pBlockSize.x));
				BlockSize.y = (float)(floor(pBlockSize.y));
				BlockSize.z = (float)(floor(pBlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					m_pCollision->CollisionPushBoxLeftRight(pPos, pPosOld, CloneSize, pBlockPos, BlockSize);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_DOOR)
				{
					CBlockDoor* pDoor = dynamic_cast<CBlockDoor*>(pObj);
					if (pDoor && pDoor->IsOpen())
					{
						// 扉が開いている場合は当たり判定をスキップ
						return;
					}

					m_pCollision->CollisionPushBoxLeftRight(pPos, pPosOld, CloneSize, pBlockPos, BlockSize);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					m_pCollision->CollisionPushBoxLeftRight(pPos, pPosOld, CloneSize, pBlockPos, BlockSize);
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
				{
					m_pCollision->CollisionHitTriggerBoxLeftRight(pPos, pPosOld, CloneSize, pBlockPos, BlockSize, m_bUse);
				}
			}
		}
	}
}

//=====================================================
// モデルの生成
//=====================================================
CClone* CClone::Create(D3DXVECTOR3 pos)
{
	CClone* pClone = new CClone;

	if (pClone != nullptr)
	{
		pClone->SetType(TYPE_CLONE);
		pClone->Init();
		pClone->SetPos(pos);
		pClone->SetUseDeath(true);
	}
	return  pClone;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CClone::SetDeath()
{
	CObject::SetDeath();
}
