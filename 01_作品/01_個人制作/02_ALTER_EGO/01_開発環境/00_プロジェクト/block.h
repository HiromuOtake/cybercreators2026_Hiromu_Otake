//==============================================
//
// 3Dスクロールアクション[block.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"
#include "player.h"
#include "clone.h"
#include <iostream>

// マクロ定義
#define BLOCK_WIDTH			(100.0f)
#define BLOCK_HEIGHT		(100.0f)

class CBlock : public CObjectX
{
public:
	typedef enum
	{
		BLOCK_NONE = 0,
		BLOCK_NORMAL,
		BLOCK_NEEDLE,
		BLOCK_DOOR,
		BLOCK_BUTTON,
		BLOCK_GOAL,
		BLOCK_MAX
	}BLOCK;
	CBlock(int nPriority = 3);
	~CBlock();
	HRESULT Init() override;
	void Uninit() override;
	virtual void Update() override;
	void Draw()override;
	void SetBlockType(BLOCK BlockType);
	void SetPairKey(const char* pairKey) { m_pairKey = pairKey; }
	BLOCK GetBlockType();
	const std::string& GetPairKey() const { return m_pairKey; }
	static CBlock* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
	BLOCK m_BlockType;
private:
	int m_nModelIdx;
	int m_nTexIdx;
	int m_nTimer;
	bool m_bOpen;
	D3DXVECTOR3 m_move;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //頂点バッファへのポインタ
	D3DXMATRIX m_matWorld;
	CInputKeyboard* m_Keyboard;
	std::string m_pairKey;	// ペアのキー
};

class CBlockNeedle : public CBlock
{
public:
	CBlockNeedle(int nPriority = 3);
	~CBlockNeedle();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockNeedle* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
private:
	int m_nModelIdx;
	int m_nTexIdx;
};

class CBlockButton : public CBlock
{
public:
	CBlockButton(int nPriority = 3);
	~CBlockButton();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockButton* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
	bool& GetOpenDoor(); // ボタンの状態を取得
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool IsCollisionPlayer(CPlayer* player);
	bool IsCollisionClone(CClone* clone);
	void SetMatColor(D3DMATERIAL9* pMat, int nMatIdx) override;
};

class CBlockDoor :public CBlock
{
public:
	CBlockDoor(int nPriority = 3);
	~CBlockDoor();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockDoor* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
private:
	int m_nModelIdx;
	int m_nTexIdx;
	int m_Timer;
	float m_deleteDoor;
	CInputKeyboard* m_Keyboard;
	CPlayer* m_pPlayer;
};

class CBlockGoal : public CBlock
{
public:
	CBlockGoal(int nPriority = 0);
	~CBlockGoal();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockGoal* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
private:
	int m_nModelIdx;
	int m_nTexIdx;
};

#pragma once

