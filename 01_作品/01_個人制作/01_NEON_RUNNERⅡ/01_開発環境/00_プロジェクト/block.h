//==============================================
//
// 3Dスクロールアクション[block.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"

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
		BLOCK_NEEDLEDOWN,
		BLOCK_GRAVITY,
		BLOCK_DOOR,
		BLOCK_BUTTON,
		BLOCK_GOAL,
		BLOCK_HALFWAYPOINT,
		BLOCK_MAX
	}BLOCK;
	CBlock(int nPriority = 3);
	~CBlock();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw()override;
	void BlockCollisionUPDOWN(CObject* pObj);
	void BlockCollisionLEFTRIGHT(CObject* pObj);
	void SetBlockType(BLOCK BlockType);
	void SetPairKey(const char* pairKey) { m_pairKey = pairKey; }
	BLOCK GetBlockType();
	bool& GetOpenDoor();
	const std::string& GetPairKey() const { return m_pairKey; }
	static CBlock* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
private:
	int m_nModelIdx;
	int m_nTextureIdx;
	int m_nTimer;
	bool m_bOpen;
	D3DXVECTOR3 m_move;
	BLOCK m_BlockType;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //頂点バッファへのポインタ
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
};

class CBlockNeedleDown : public CBlock
{
public:
	CBlockNeedleDown(int nPriority = 3);
	~CBlockNeedleDown();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockNeedleDown* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
private:
};

class CBlockGravity : public CBlock
{
public:
	CBlockGravity(int nPriority = 3);
	~CBlockGravity();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static bool& GetGravitySwitch();
	static void SetGravitySwitch(bool GravitySwitch);
	static void SetAllGravityBlockTrue();
	static CBlockGravity* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
private:
	int m_GravityTimer;
	bool m_GravityChage;
	static bool m_GravitySwitch;
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
private:
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
	int m_Timer;
	CInputKeyboard* m_Keyboard;
};

#pragma once

