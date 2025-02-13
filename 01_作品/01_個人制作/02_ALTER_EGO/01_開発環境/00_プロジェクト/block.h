//==============================================
//
// ALTER_EGO[block.h]
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
	// ボタンの状態
	enum class ButtonState
	{
		RED_ENABLED,
		BLUE_ENABLED
	};
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
	void SetBlockType(BLOCK BlockType);
	void SetPairKey(const char* pairKey) { m_pairKey = pairKey; }
	BLOCK GetBlockType();
	const std::string& GetPairKey() const { return m_pairKey; }
	static CBlock* Create(D3DXVECTOR3 pos, BLOCK nType);
	void Draw()override;
	ButtonState GetCurrentState() const { return currentButtonState; }
	void SetDeath()override;
	BLOCK m_BlockType;
private:
	ButtonState currentButtonState = ButtonState::RED_ENABLED;
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
	enum BUTTON_COLOR
	{
		BUTTON_NORMAL,
		BUTTON_RED,
		BUTTON_BLUE,
	};
	CBlockButton(int nPriority = 3);
	~CBlockButton();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockButton* Create(D3DXVECTOR3 pos, BLOCK nType, BUTTON_COLOR color = BUTTON_NORMAL);
	void SetColor(BUTTON_COLOR color) { m_Color = color; }
	void ResetMaterial();
	BUTTON_COLOR GetColor() const { return m_Color; }	// ボタンの色を取得
	void SetDeath()override;
	bool& GetOpenDoor(); // 扉を開く状態を取得
	static BUTTON_COLOR m_LastPressedButton;
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool m_bColliderActive;		// 当たり判定が有効かどうか
	bool m_bResetPending;  // ボタンがリセットを待っている状態かどうか
	bool m_bPressedOnce;
	BUTTON_COLOR m_Color;  // スイッチの色
	D3DMATERIAL9 m_OriginalMaterial;
	D3DMATERIAL9 m_Material;
	bool IsCollisionPlayer(CPlayer* player);
	bool IsCollisionClone(CClone* clone);
	void SetMatColor(D3DMATERIAL9* pMat, int nMatIdx) override;
};

// 赤いボタン
class CBlockRedButton : public CBlockButton
{
public:
	CBlockRedButton(int nPriority = 3);
	~CBlockRedButton();
	HRESULT Init()override;
	static CBlockRedButton* Create(D3DXVECTOR3 pos, BUTTON_COLOR color);
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool m_bColliderActive;		// 当たり判定が有効かどうか
	BUTTON_COLOR m_Color;			// スイッチの色
};

// 青いボタン
class CBlockBlueButton : public CBlockButton
{
public:
	CBlockBlueButton(int nPriority = 3);
	~CBlockBlueButton();
	HRESULT Init()override;
	static CBlockBlueButton* Create(D3DXVECTOR3 pos, BUTTON_COLOR color);
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool m_bColliderActive;		// 当たり判定が有効かどうか
	BUTTON_COLOR m_Color;			// スイッチの色
};

class CBlockDoor :public CBlock
{
public:
	enum DOOR_COLOR
	{
		DOOR_NORMAL,
		DOOR_RED,
		DOOR_BLUE,
	};
	CBlockDoor(int nPriority = 3, DOOR_COLOR color = DOOR_NORMAL);
	~CBlockDoor();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockDoor* Create(D3DXVECTOR3 pos, BLOCK nType, DOOR_COLOR color);
	void SetColor(DOOR_COLOR color) { m_Color = color; }
	DOOR_COLOR GetColor() const { return m_Color; }
	bool IsOpen() const { return m_bOpen; }
	void OpenAndClose(bool open);			// 扉を開閉する処理
	void SetDeath()override;
private:
	int m_nModelIdx;
	int m_nTexIdx;
	int m_Timer;
	float m_deleteDoor;
	bool m_isOpen = false; // ドアの状態を保持
	bool m_bOpen;				// 扉が開いているかの状態
	bool m_bColliderActive;		// 当たり判定が有効かどうか
	bool m_bVisible;  // 扉の表示・非表示を制御するフラグ
	DOOR_COLOR m_Color;			// ドアの色
	CInputKeyboard* m_Keyboard;
};

// 赤いドア
class CBlockRedDoor : public CBlockDoor
{
public:
	CBlockRedDoor(int nPriority = 3);
	~CBlockRedDoor();
	HRESULT Init()override;
	static CBlockRedDoor* Create(D3DXVECTOR3 pos, DOOR_COLOR color);
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool m_bColliderActive;
	DOOR_COLOR m_color;			// ドアの色
};

// 青いドア
class CBlockBlueDoor : public CBlockDoor
{
public:
	CBlockBlueDoor(int nPriority = 3);
	~CBlockBlueDoor();
	HRESULT Init()override;
	static CBlockBlueDoor* Create(D3DXVECTOR3 pos, DOOR_COLOR color);
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;		
	bool m_bColliderActive;

	DOOR_COLOR m_color;			// ドアの色
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
	float m_fGoalRot;
	int m_nModelIdx;
	int m_nTexIdx;
};

#pragma once
