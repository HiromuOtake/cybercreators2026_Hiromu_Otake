//==============================================
//
// ALTER_EGO[item.cpp]
// Author: hiromu otake
//
//==============================================

#include "item.h"
#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "texture.h"
#include "model.h"
#include "particlemanager.h"
#include <random>

//==============================================
// コンストラクタ
//==============================================
CItem::CItem(int nPriority) : CObjectX(nPriority), m_ItemType(ITEM_NONE), m_Keyboard(nullptr), m_pVtxBuff(nullptr), m_bOpen(false)
, m_nModelIdx(0), m_nTimer(0), m_nTexIdx(0), m_move{ 0.0f,0.0f,0.0f }
{

}

//==============================================
// デストラクタ
//==============================================
CItem::~CItem()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CItem::Init()
{
	SetType(TYPE_ITEM);

	m_Keyboard = CManager::GetKeyboard();

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\Item.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

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
// 更新処理
//==============================================
void CItem::Update()
{
	// 回転行列を適用
	if (m_fRotation != 0.0f)
	{
		D3DXMATRIX matRotation;
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(m_fRotation));  // Y軸回転

		// ワールド行列に回転を適用
		D3DXMatrixMultiply(&m_matWorld, &matRotation, &m_matWorld);
	}

	m_fItemRotation += 0.05f;

	CObjectX::SetRot(D3DXVECTOR3(0.0f, m_fItemRotation, 0.0f));

	CObjectX::Update();
}

//==============================================
// 描画処理
//==============================================
void CItem::Draw()
{
	CObjectX::Draw();
}

//==============================================
// ブロックのタイプ設定処理
//==============================================
void CItem::SetItemType(ITEM ItemType)
{
	m_ItemType = ItemType;
}

//==============================================
// ブロックのタイプ取得処理
//==============================================
CItem::ITEM CItem::GetItemType()
{
	return m_ItemType;
}

//=====================================================
// モデルの生成
//=====================================================
CItem* CItem::Create(D3DXVECTOR3 pos, ITEM nType)
{
	CItem* pItem = new CItem();

	if (pItem != nullptr)
	{
		pItem->SetItemType(nType);
		pItem->Init();
		pItem->SetPos(pos);
		pItem->SetUseDeath(true);
	}
	return  pItem;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CItem::SetDeath()
{
	CObject::SetDeath();
}
