//==============================================
//
// 3Dスクロールアクション[block.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"

class CItem :public CObjectX
{
public:
	typedef enum
	{
		ITEM_NONE = 0,
		ITEM_COIN,
		ITEM_T_JUMP,
		ITEM_T_DOUBLE_JUMP,
		ITEM_T_SHOT,
		ITEM_T_COIN,
		ITEM_T_NEEDLE,
		ITEM_T_GRAVITY,
		ITEM_T_DOOR,
		ITEM_T_GOAL,
		ITEM_MAX
	}ITEM;
	CItem(int nPriority = 3);
	~CItem();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	void Collision();
	void ItemCollisionUPDOWN(CObject* pObj);
	void ItemCollisionLEFTRIGHT(CObject* pObj);
	void SetItemType(ITEM ItemType);
	static CItem* Create(D3DXVECTOR3 pos, ITEM nType);
	void SetDeath()override;
private:
	ITEM m_ItemType;
	int m_nTextureIdx;
	bool m_bUse;
	int m_nModelIdx;
};

class CItem_T_Jump :public CItem
{
public:
	CItem_T_Jump(int nPriority = 3);
	~CItem_T_Jump();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CItem_T_Jump* Create(D3DXVECTOR3 pos, ITEM nType);
private:
};

class CItem_T_Double_Jump :public CItem
{
public:
	CItem_T_Double_Jump(int nPriority = 3);
	~CItem_T_Double_Jump();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CItem_T_Double_Jump* Create(D3DXVECTOR3 pos, ITEM nType);
private:
};

class CItem_T_Shot :public CItem
{
public:
	CItem_T_Shot(int nPriority = 3);
	~CItem_T_Shot();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CItem_T_Shot* Create(D3DXVECTOR3 pos, ITEM nType);
private:
};

class CItem_T_Coin :public CItem
{
public:
	CItem_T_Coin(int nPriority = 3);
	~CItem_T_Coin();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CItem_T_Coin* Create(D3DXVECTOR3 pos, ITEM nType);
private:
};

class CItem_T_Needle :public CItem
{
public:
	CItem_T_Needle(int nPriority = 3);
	~CItem_T_Needle();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CItem_T_Needle* Create(D3DXVECTOR3 pos, ITEM nType);
private:
};

class CItem_T_Gravity :public CItem
{
public:
	CItem_T_Gravity(int nPriority = 3);
	~CItem_T_Gravity();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CItem_T_Gravity* Create(D3DXVECTOR3 pos, ITEM nType);
private:
};

class CItem_T_Door :public CItem
{
public:
	CItem_T_Door(int nPriority = 3);
	~CItem_T_Door();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CItem_T_Door* Create(D3DXVECTOR3 pos, ITEM nType);
private:
};

class CItem_T_Goal :public CItem
{
public:
	CItem_T_Goal(int nPriority = 3);
	~CItem_T_Goal();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CItem_T_Goal* Create(D3DXVECTOR3 pos, ITEM nType);
private:
};

#pragma once
