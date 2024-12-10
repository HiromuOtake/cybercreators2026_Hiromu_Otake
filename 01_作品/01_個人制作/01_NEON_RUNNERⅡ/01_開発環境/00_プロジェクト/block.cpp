//==============================================
//
// 3Dスクロールアクション[block.cpp]
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
// コンストラクタ
//==============================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority), m_BlockType(BLOCK_NONE), m_Keyboard(nullptr), m_pVtxBuff(nullptr), m_nModelIdx(0), m_nTextureIdx(0), m_move{ 0.0f,0.0f,0.0f }, m_nTimer(0), m_bOpen(false)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockNeedle::CBlockNeedle(int nPriority) : CBlock(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockNeedleDown::CBlockNeedleDown(int nPriority) : CBlock(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockGravity::CBlockGravity(int nPriority) : CBlock(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockButton::CBlockButton(int nPriority) : CBlock(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockDoor::CBlockDoor(int nPriority) : CBlock(nPriority)
{
	m_Timer = 0;
}

//==============================================
// デストラクタ
//==============================================
CBlock::~CBlock()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockNeedle::~CBlockNeedle()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockNeedleDown::~CBlockNeedleDown()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockGravity::~CBlockGravity()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockButton::~CBlockButton()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockDoor::~CBlockDoor()
{

}

//==============================================
// 初期設定
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
// 初期設定
//==============================================
HRESULT CBlockNeedle::Init()
{
	CBlock::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockNeedleDown::Init()
{
	CBlock::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockGravity::Init()
{
	CBlock::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockButton::Init()
{
	CBlock::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockDoor::Init()
{
	CBlock::Init();

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CBlock::Uninit()
{
	CObjectX::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockNeedle::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockNeedleDown::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockGravity::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockButton::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockDoor::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 更新処理
//==============================================
void CBlock::Update()
{
	D3DXVECTOR3& pPos = CObjectX::GetPos();

	pPos.z += m_move.z;

	//移動量を更新(減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//位置を更新
	pPos.x += m_move.x;

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// プライオリティ分回す
		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			// 左右の当たり判定
			BlockCollisionLEFTRIGHT(pObj);
			pObj->GetNext();
			pObj = pObj->GetNext();
		}
	}

	//位置を更新
	pPos.y += m_move.y;

	m_move.y += (0.0f - m_move.y) * 0.1f;

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// プライオリティ分回す
		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			// 上下の当たり判定
			BlockCollisionUPDOWN(pObj);
			pObj->GetNext();
			pObj = pObj->GetNext();
		}
	}

	CObjectX::Update();
}

//==============================================
// 更新処理
//==============================================
void CBlockNeedle::Update()
{
	CBlock::Update();
}

//==============================================
// 更新処理
//==============================================
void CBlockNeedleDown::Update()
{
	CBlock::Update();
}

//==============================================
// 更新処理
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
// 更新処理
//==============================================
void CBlockButton::Update()
{
	CBlock::Update();
}

//==============================================
// 更新処理
//==============================================
void CBlockDoor::Update()
{
	bool bOpenDoor = false;

#if 0
	// 最大数が不明なのでWhileを使用
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->GetNext();
		if (CBlock* pBlock = dynamic_cast<CBlock*>(pObj))
		{ // ブロッククラスにダウンキャスト
			std::string a = pBlock->GetPairKey();
			std::string b = GetPairKey();

			if (pBlock->GetPairKey() == GetPairKey() && GetPairKey() != "none")
			{ // ペアのキーが一致した
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
	// キーの取得
	const std::string& key = GetPairKey();
	if (key != "none")
	{ // キーが存在する
		for (const auto& object : CObject::GetPair()[key])
		{
			if (object == nullptr)
			{ // 空だった
				continue;
			}

			if (this == object)
			{ // 自分自身だった
				continue;
			}

			CBlock* block = dynamic_cast<CBlock*>(object);
			if (block == nullptr)
			{ // 空だった
				continue;
			}

			// ドアが開いているフラグが真だった
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
		// m_Time * move = 200.0f であること！
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
// 描画処理
//==============================================
void CBlock::Draw()
{
	CObjectX::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockNeedle::Draw()
{
	CBlock::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockNeedleDown::Draw()
{
	CBlock::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockGravity::Draw()
{
	CBlock::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockButton::Draw()
{
	CBlock::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockDoor::Draw()
{
	CBlock::Draw();
}

//=====================================================
// 上下の当たり判定
//=====================================================
void CBlock::BlockCollisionUPDOWN(CObject* pObj)
{
	//bool bIsLanding = false;	//着地しているかどうか

	D3DXVECTOR3& pPos = CObjectX::GetPos();
	D3DXVECTOR3& pPosOld = CObjectX::GetPosOld();
	D3DXVECTOR3& pSize = CObjectX::GetSize();

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(pSize.x)));
	PlayerSize.y = (float(floor(pSize.y)));
	PlayerSize.z = (float(floor(pSize.z)));

	if (pObj != nullptr)
	{// pObjがnullptrじゃないなら

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BULLET)
		{// typeがBLOCKなら

			CBullet* pBullet = (CBullet*)pObj;

			D3DXVECTOR3& pBulletPos = pBullet->GetPos();
			D3DXVECTOR3 pBulletPosOld = pBullet->GetPosOld();
			D3DXVECTOR3 pBulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 少数の位を省く処理
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
				{// 上側
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 下側
					pBullet->SetUse(true);
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_NEEDLE)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 上側
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 下側
					pBullet->SetUse(true);
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_GRAVITY)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 上側
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 下側
					pBullet->SetUse(true);
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_DOOR)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 上側
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y - PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 下側
					pBullet->SetUse(true);
				}
			}
			else if (m_BlockType == BLOCK::BLOCK_BUTTON)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y - pBulletSize.y * m_HALF_SIZE >= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 上側
					m_bOpen = true;
					pBullet->SetUse(true);
				}
				else if (pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE <= pPos.y + PlayerSize.y * m_HALF_SIZE &&
					pBulletPos.x + pBulletSize.x * m_HALF_SIZE > pPos.x - PlayerSize.x * m_HALF_SIZE &&
					pBulletPos.x - pBulletSize.x * m_HALF_SIZE < pPos.x + PlayerSize.x * m_HALF_SIZE)
				{// 下側
					m_bOpen = true;
					pBullet->SetUse(true);
				}
			}
		}
	}
}

//=====================================================
// 左右の当たり判定
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
	{// pObjがnullptrじゃないなら

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BULLET)
		{// typeがBLOCKなら

			CBullet* pBullet = (CBullet*)pObj;

			D3DXVECTOR3 pBulletPos = pBullet->GetPos();
			D3DXVECTOR3 pBulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 少数の位を省く処理
			D3DXVECTOR3 BulletSize = pBullet->GetSize();
			pBulletSize.x = (float)(floor(BulletSize.x));
			pBulletSize.y = (float)(floor(BulletSize.y));
			pBulletSize.z = (float)(floor(BulletSize.z));

			if (m_BlockType == BLOCK::BLOCK_NORMAL)
			{
				if (pBulletPos.y - pBulletSize.y * m_HALF_SIZE < pPos.y + BlockSize.y * m_HALF_SIZE &&
					pBulletPos.y + pBulletSize.y * m_HALF_SIZE > pPos.y - BlockSize.y * m_HALF_SIZE)
				{
					//左右の当たり判定
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
					//左右の当たり判定
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
					//左右の当たり判定
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
					//左右の当たり判定
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
					//左右の当たり判定
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
// ブロックのタイプ設定処理
//==============================================
void CBlock::SetBlockType(BLOCK BlockType)
{
	m_BlockType = BlockType;
}

//==============================================
// ブロックのタイプ取得処理
//==============================================
CBlock::BLOCK CBlock::GetBlockType()
{
	return m_BlockType;
}

//==============================================
// ブロックのタイプ取得処理
//==============================================
bool &CBlock::GetOpenDoor()
{
	return m_bOpen;
}

//==============================================
// ブロックのタイプ取得処理
//==============================================
bool &CBlockGravity::GetGravitySwitch()
{
	return m_GravitySwitch;
}

//==============================================
// 重力の回転方向の設定
//==============================================
void CBlockGravity::SetGravitySwitch(bool GravitySwitch)
{
	m_GravitySwitch = GravitySwitch;
}

//=====================================================
// モデルの生成
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
// モデルの生成
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
// モデルの生成
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
// モデルの生成
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
// モデルの生成
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
// モデルの生成
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
// 死亡フラグ設定処理
//=========================================
void CBlock::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockNeedle::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockNeedleDown::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockGravity::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockButton::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockDoor::SetDeath()
{
	CObject::SetDeath();
}