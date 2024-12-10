//==============================================
//
// 3Dスクロールアクション[objectX.cpp]
// Author: hiromu otake
//
//==============================================

#include "item.h"
#include "camera.h"
#include "texture.h"
#include "player.h"
#include "game.h"
#include "Tutorial.h"

//==============================================
// コンストラクタ
//==============================================
CItem::CItem(int nPriority) : CObjectX(nPriority), m_ItemType(ITEM_NONE), m_bUse(true), m_nModelIdx(0), m_nTextureIdx(0)
{

}

//==============================================
// コンストラクタ
//==============================================
CItem_T_Jump::CItem_T_Jump(int nPriority) : CItem(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CItem_T_Double_Jump::CItem_T_Double_Jump(int nPriority) : CItem(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CItem_T_Shot::CItem_T_Shot(int nPriority) : CItem(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CItem_T_Coin::CItem_T_Coin(int nPriority) : CItem(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CItem_T_Needle::CItem_T_Needle(int nPriority) : CItem(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CItem_T_Gravity::CItem_T_Gravity(int nPriority) : CItem(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CItem_T_Door::CItem_T_Door(int nPriority) : CItem(nPriority)
{

}

//==============================================
// コンストラクタ
//==============================================
CItem_T_Goal::CItem_T_Goal(int nPriority) : CItem(nPriority)
{

}

//==============================================
// デストラクタ
//==============================================
CItem::~CItem()
{

}

//==============================================
// デストラクタ
//==============================================
CItem_T_Jump::~CItem_T_Jump()
{

}

//==============================================
// デストラクタ
//==============================================
CItem_T_Double_Jump::~CItem_T_Double_Jump()
{

}

//==============================================
// デストラクタ
//==============================================
CItem_T_Shot::~CItem_T_Shot()
{

}

//==============================================
// デストラクタ
//==============================================
CItem_T_Coin::~CItem_T_Coin()
{

}

//==============================================
// デストラクタ
//==============================================
CItem_T_Needle::~CItem_T_Needle()
{

}

//==============================================
// デストラクタ
//==============================================
CItem_T_Gravity::~CItem_T_Gravity()
{

}

//==============================================
// デストラクタ
//==============================================
CItem_T_Door::~CItem_T_Door()
{

}

//==============================================
// デストラクタ
//==============================================
CItem_T_Goal::~CItem_T_Goal()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CItem::Init()
{
	CModel* pModel = CManager::GetModel();

	if (m_ItemType == ITEM::ITEM_COIN)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\coin.x");
	}
	else if (m_ItemType == ITEM::ITEM_T_JUMP)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\T_Jump.x");
	}
	else if (m_ItemType == ITEM::ITEM_T_DOUBLE_JUMP)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\T_DoubleJump.x");
	}
	else if (m_ItemType == ITEM::ITEM_T_SHOT)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\T_Shot.x");
	}
	else if (m_ItemType == ITEM::ITEM_T_COIN)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\T_Coin.x");
	}
	else if (m_ItemType == ITEM::ITEM_T_NEEDLE)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\T_Needle.x");
	}
	else if (m_ItemType == ITEM::ITEM_T_GRAVITY)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\T_Gravity.x");
	}
	else if (m_ItemType == ITEM::ITEM_T_DOOR)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\T_Door.x");
	}
	else if (m_ItemType == ITEM::ITEM_T_GOAL)
	{
		m_nModelIdx = pModel->Regist("data\\MODEL\\x\\T_Goal.x");
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
HRESULT CItem_T_Jump::Init()
{
	CItem::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CItem_T_Double_Jump::Init()
{
	CItem::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CItem_T_Shot::Init()
{
	CItem::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CItem_T_Coin::Init()
{
	CItem::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CItem_T_Needle::Init()
{
	CItem::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CItem_T_Gravity::Init()
{
	CItem::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CItem_T_Door::Init()
{
	CItem::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CItem_T_Goal::Init()
{
	CItem::Init();

	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CItem::Uninit()
{
	CObjectX::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CItem_T_Jump::Uninit()
{
	CItem::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CItem_T_Double_Jump::Uninit()
{
	CItem::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CItem_T_Shot::Uninit()
{
	CItem::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CItem_T_Coin::Uninit()
{
	CItem::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CItem_T_Needle::Uninit()
{
	CItem::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CItem_T_Gravity::Uninit()
{
	CItem::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CItem_T_Door::Uninit()
{
	CItem::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CItem_T_Goal::Uninit()
{
	CItem::Uninit();
}

//==============================================
// 更新処理
//==============================================
void CItem::Update()
{
	CSound* pSound = CManager::GetSound();

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// プライオリティ分回す

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			// 左右の当たり判定
			ItemCollisionLEFTRIGHT(pObj);
			pObj->GetNext();
			pObj = pObj->GetNext();
		}
	}

	for (int nCntPrio = 0; nCntPrio < m_MAXPRIORITY; nCntPrio++)
	{// プライオリティ分回す

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			// 上下の当たり判定
			ItemCollisionUPDOWN(pObj);
			pObj->GetNext();
			pObj = pObj->GetNext();
		}
	}

	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		if (m_bUse == false)
		{
			if (CTutorial::GetPlayer()->GetScore() != nullptr)
			{
				pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_COIN);

				CTutorial::GetPlayer()->GetScore()->AddScore(100);
				SetDeath();
			}
		}
	}
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (m_bUse == false)
		{
			if (CGame::GetPlayer()->GetScore() != nullptr)
			{
				pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_COIN);

				CGame::GetPlayer()->GetScore()->AddScore(100);
				SetDeath();
			}
		}
	}
	CObjectX::Update();
}

//==============================================
// 更新処理
//==============================================
void CItem_T_Jump::Update()
{
	CItem::Update();
}

//==============================================
// 更新処理
//==============================================
void CItem_T_Double_Jump::Update()
{
	CItem::Update();
}

//==============================================
// 更新処理
//==============================================
void CItem_T_Shot::Update()
{
	CItem::Update();
}

//==============================================
// 更新処理
//==============================================
void CItem_T_Coin::Update()
{
	CItem::Update();
}

//==============================================
// 更新処理
//==============================================
void CItem_T_Needle::Update()
{
	CItem::Update();
}

//==============================================
// 更新処理
//==============================================
void CItem_T_Gravity::Update()
{
	CItem::Update();
}

//==============================================
// 更新処理
//==============================================
void CItem_T_Door::Update()
{
	CItem::Update();
}

//==============================================
// 更新処理
//==============================================
void CItem_T_Goal::Update()
{
	CItem::Update();
}

//==============================================
// 描画処理
//==============================================
void CItem::Draw()
{
	CObjectX::Draw();
}

//==============================================
// 描画処理
//==============================================
void CItem_T_Jump::Draw()
{
	CItem::Draw();
}

//==============================================
// 描画処理
//==============================================
void CItem_T_Double_Jump::Draw()
{
	CItem::Draw();
}

//==============================================
// 描画処理
//==============================================
void CItem_T_Shot::Draw()
{
	CItem::Draw();
}

//==============================================
// 描画処理
//==============================================
void CItem_T_Coin::Draw()
{
	CItem::Draw();
}

//==============================================
// 描画処理
//==============================================
void CItem_T_Needle::Draw()
{
	CItem::Draw();
}

//==============================================
// 描画処理
//==============================================
void CItem_T_Gravity::Draw()
{
	CItem::Draw();
}

//==============================================
// 描画処理
//==============================================
void CItem_T_Door::Draw()
{
	CItem::Draw();
}

//==============================================
// 描画処理
//==============================================
void CItem_T_Goal::Draw()
{
	CItem::Draw();
}

//=====================================================
// 上下の当たり判定
//=====================================================
void CItem::ItemCollisionUPDOWN(CObject* pObj)
{
	//bool bIsLanding = false;	//着地しているかどうか

	D3DXVECTOR3& pPos = CObjectX::GetPos();
	D3DXVECTOR3& pPosOld = CObjectX::GetPosOld();
	D3DXVECTOR3& pSize = CObjectX::GetSize();

	D3DXVECTOR3 ItemSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	ItemSize.x = (float(floor(pSize.x)));
	ItemSize.y = (float(floor(pSize.y)));
	ItemSize.z = (float(floor(pSize.z)));

	if (pObj != nullptr)
	{// pObjがnullptrじゃないなら

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_PLAYER)
		{// typeがPLAYERなら

			CPlayer* pPlayer = (CPlayer*)pObj;

			D3DXVECTOR3 pPlayerPos = pPlayer->GetPos();
			D3DXVECTOR3 pPlayerPosOld = pPlayer->GetPosOld();
			D3DXVECTOR3 pPlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 少数の位を省く処理
			D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
			pPlayerSize.x = (float)(floor(PlayerSize.x));
			pPlayerSize.y = (float)(floor(PlayerSize.y));
			pPlayerSize.z = (float)(floor(PlayerSize.z));

			if (m_ItemType == ITEM::ITEM_COIN)
			{
				if (pPlayerPos.y - pPlayerSize.y * m_HALF_SIZE < pPos.y + ItemSize.y * m_HALF_SIZE &&
					pPlayerPosOld.y - pPlayerSize.y * m_HALF_SIZE >= pPos.y + ItemSize.y * m_HALF_SIZE &&
					pPlayerPos.x + pPlayerSize.x * m_HALF_SIZE > pPos.x - ItemSize.x * m_HALF_SIZE &&
					pPlayerPos.x - pPlayerSize.x * m_HALF_SIZE < pPos.x + ItemSize.x * m_HALF_SIZE)
				{// 上側
					m_bUse = false;
				}
				else if (pPlayerPos.y + pPlayerSize.y * m_HALF_SIZE > pPos.y - ItemSize.y * m_HALF_SIZE &&
					pPlayerPosOld.y + pPlayerSize.y * m_HALF_SIZE <= pPos.y - ItemSize.y * m_HALF_SIZE &&
					pPlayerPos.x + pPlayerSize.x * m_HALF_SIZE > pPos.x - ItemSize.x * m_HALF_SIZE &&
					pPlayerPos.x - pPlayerSize.x * m_HALF_SIZE < pPos.x + ItemSize.x * m_HALF_SIZE)
				{// 下側
					m_bUse = false;
				}
			}
			else
			{

			}
		}
	}
}

//=====================================================
// 左右の当たり判定
//=====================================================
void CItem::ItemCollisionLEFTRIGHT(CObject* pObj)
{
	D3DXVECTOR3& pPos = CObjectX::GetPos();
	D3DXVECTOR3& pPosOld = CObjectX::GetPosOld();
	D3DXVECTOR3& pSize = CObjectX::GetSize();

	D3DXVECTOR3 ItemSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	ItemSize.x = (float(floor(pSize.x)));
	ItemSize.y = (float(floor(pSize.y)));
	ItemSize.z = (float(floor(pSize.z)));

	if (pObj != nullptr)
	{// pObjがnullptrじゃないなら

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_PLAYER)
		{// typeがPLAYERなら

			CPlayer* pPlayer = (CPlayer*)pObj;

			D3DXVECTOR3 pPlayerPos = pPlayer->GetPos();
			D3DXVECTOR3 pPlayerPosOld = pPlayer->GetPosOld();
			D3DXVECTOR3 pPlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 少数の位を省く処理
			D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
			pPlayerSize.x = (float)(floor(PlayerSize.x));
			pPlayerSize.y = (float)(floor(PlayerSize.y));
			pPlayerSize.z = (float)(floor(PlayerSize.z));

			if (m_ItemType == ITEM::ITEM_COIN)
			{
				if (pPlayerPos.y - pPlayerSize.y * m_HALF_SIZE < pPos.y + ItemSize.y * m_HALF_SIZE &&
					pPlayerPos.y + pPlayerSize.y * m_HALF_SIZE > pPos.y - ItemSize.y * m_HALF_SIZE)
				{
					//右側の当たり判定
					if (pPlayerPos.x - pPlayerSize.x * m_HALF_SIZE < pPos.x + ItemSize.x * m_HALF_SIZE &&
						pPlayerPosOld.x - pPlayerSize.x * m_HALF_SIZE >= pPos.x + ItemSize.x * m_HALF_SIZE)
					{
						m_bUse = false;
					}
					//左側の当たり判定
					else if (pPlayerPos.x + pPlayerSize.x * m_HALF_SIZE > pPos.x - ItemSize.x * m_HALF_SIZE &&
						pPlayerPosOld.x + pPlayerSize.x * m_HALF_SIZE <= pPos.x - ItemSize.x * m_HALF_SIZE)
					{
						m_bUse = false;
					}
				}
			}
			else
			{
				
			}
		}
	}
}

//==============================================
// ブロックのタイプ設定処理
//==============================================
void CItem::SetItemType(ITEM ItemType)
{
	m_ItemType = ItemType;
}

//=====================================================
// モデルの生成
//=====================================================
CItem* CItem::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem* pItem = new CItem;

	if (pItem != nullptr)
	{
		pItem->SetItemType(nType);
		pItem->Init();
		pItem->SetPos(pos);
		pItem->SetUseDeath(true);
	}
	return  pItem;
}

//=====================================================
// モデルの生成
//=====================================================
CItem_T_Jump* CItem_T_Jump::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem_T_Jump* pItem_T_Jump = new CItem_T_Jump;

	if (pItem_T_Jump != nullptr)
	{
		pItem_T_Jump->SetItemType(nType);
		pItem_T_Jump->Init();
		pItem_T_Jump->SetPos(pos);
		pItem_T_Jump->SetUseDeath(true);
	}
	return  pItem_T_Jump;
}

//=====================================================
// モデルの生成
//=====================================================
CItem_T_Double_Jump* CItem_T_Double_Jump::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem_T_Double_Jump* pItem_T_Double_Jump = new CItem_T_Double_Jump;

	if (pItem_T_Double_Jump != nullptr)
	{
		pItem_T_Double_Jump->SetItemType(nType);
		pItem_T_Double_Jump->Init();
		pItem_T_Double_Jump->SetPos(pos);
		pItem_T_Double_Jump->SetUseDeath(true);
	}
	return  pItem_T_Double_Jump;
}

//=====================================================
// モデルの生成
//=====================================================
CItem_T_Shot* CItem_T_Shot::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem_T_Shot* pItem_T_Shot = new CItem_T_Shot;

	if (pItem_T_Shot != nullptr)
	{
		pItem_T_Shot->SetItemType(nType);
		pItem_T_Shot->Init();
		pItem_T_Shot->SetPos(pos);
		pItem_T_Shot->SetUseDeath(true);
	}
	return  pItem_T_Shot;
}

//=====================================================
// モデルの生成
//=====================================================
CItem_T_Coin* CItem_T_Coin::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem_T_Coin* pItem_T_Coin = new CItem_T_Coin;

	if (pItem_T_Coin != nullptr)
	{
		pItem_T_Coin->SetItemType(nType);
		pItem_T_Coin->Init();
		pItem_T_Coin->SetPos(pos);
		pItem_T_Coin->SetUseDeath(true);
	}
	return  pItem_T_Coin;
}

//=====================================================
// モデルの生成
//=====================================================
CItem_T_Needle* CItem_T_Needle::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem_T_Needle* pItem_T_Needle = new CItem_T_Needle;

	if (pItem_T_Needle != nullptr)
	{
		pItem_T_Needle->SetItemType(nType);
		pItem_T_Needle->Init();
		pItem_T_Needle->SetPos(pos);
		pItem_T_Needle->SetUseDeath(true);
	}
	return  pItem_T_Needle;
}

//=====================================================
// モデルの生成
//=====================================================
CItem_T_Gravity* CItem_T_Gravity::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem_T_Gravity* pItem_T_Gravity = new CItem_T_Gravity;

	if (pItem_T_Gravity != nullptr)
	{
		pItem_T_Gravity->SetItemType(nType);
		pItem_T_Gravity->Init();
		pItem_T_Gravity->SetPos(pos);
		pItem_T_Gravity->SetUseDeath(true);
	}
	return  pItem_T_Gravity;
}

//=====================================================
// モデルの生成
//=====================================================
CItem_T_Door* CItem_T_Door::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem_T_Door* pItem_T_Door = new CItem_T_Door;

	if (pItem_T_Door != nullptr)
	{
		pItem_T_Door->SetItemType(nType);
		pItem_T_Door->Init();
		pItem_T_Door->SetPos(pos);
		pItem_T_Door->SetUseDeath(true);
	}
	return  pItem_T_Door;
}

//=====================================================
// モデルの生成
//=====================================================
CItem_T_Goal* CItem_T_Goal::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem_T_Goal* pItem_T_Goal = new CItem_T_Goal;

	if (pItem_T_Goal != nullptr)
	{
		pItem_T_Goal->SetItemType(nType);
		pItem_T_Goal->Init();
		pItem_T_Goal->SetPos(pos);
		pItem_T_Goal->SetUseDeath(true);
	}
	return  pItem_T_Goal;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CItem::SetDeath()
{
	CObject::SetDeath();
}
