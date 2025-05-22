//==============================================
//
// ALTER_EGO[item.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"

// �}�N����`
#define ITEM_WIDTH		(100.0f)
#define ITEM_HEIGHT		(100.0f)

class CItem : public CObjectX
{
public:
	enum ITEM
	{
		ITEM_NONE = 0,
		ITEM_STAR,
		ITEM_MAX
	};
	CItem(int nPriority = 3);
	~CItem();
	HRESULT Init() override;
	void Uninit() override;
	virtual void Update() override;
	void SetItemType(ITEM ItemType);
	ITEM GetItemType();
	static CItem* Create(D3DXVECTOR3 pos, ITEM nType);
	void Draw()override;
	void SetDeath()override;
	ITEM m_ItemType;
	static const int m_NONE_TEX = 1;
	static constexpr float m_ITEM_ROT = 0.05f;
private:
	int m_nModelIdx;
	int m_nTexIdx;
	int m_nTimer;
	float m_fItemRotation;
	bool m_bOpen;
	D3DXVECTOR3 m_move;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_matWorld;
	CInputKeyboard* m_Keyboard;
};

#pragma once
