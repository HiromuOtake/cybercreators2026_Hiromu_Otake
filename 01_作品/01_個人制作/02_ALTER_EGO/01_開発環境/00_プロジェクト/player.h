//==============================================
//
//ALTER_EGO[player.h]
//Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"
#include "modelparts.h"
#include "character.h"
#include "clone.h"
#include "cloneCircle.h"
#include "collision.h"
#include "item.h"

class CPlayer : public CCharacter
{
public:
	enum TYPE
	{
		PLAYER_NONE = 0,
		PLAYER_NORMAL,
		PLAYER_DEATH,
		PLAYER_MAX,
	};
	CPlayer(int nPriority = 3);
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void PlayerMovement();									// プレイヤーの通常処理
	void GenerateClone();									// クローン生成処理
	void HandleCloneSelection();							// クローン選択処理
	void TitlePlayerMovement();								// タイトルでのプレイヤー処理
	bool CollisionUPDOWN(bool& bLanding, CObject* pObj);	// 当たり判定上下
	void CollisionLEFTRIGHT(CObject* pObj);					// 当たり判定左右
	static bool& GetGoal() { return m_bUse; }				// ゴール情報の取得
	bool GetCloneActive() { return m_bCloneActive; }		// クローンサークルの状態の取得
	static CPlayer* Create(D3DXVECTOR3 pos);				// プレイヤーの生成
	void SetDeath()override;
	static const int m_PLAYER_LIFE = 1;						// プレイヤーの体力
	static const int m_DEATH_COUNT = 30;					// プレイヤーが復活するまでの時間
	static const int m_RESET_PLAYER_POS_X = 200;			// プレイヤーを復活させる場所(X座標)
	static const int m_RESET_PLAYER_POS_Y = -1200;			// プレイヤーを復活させる場所(Y座標)
	static constexpr float m_PLAYER_SHOT_POS = 20.0f;		// プレイヤーが弾を出す位置の補正
	static constexpr float m_PLAYER_SHOT_MOVE = 15.0f;		// プレイヤーの弾の速度
	static constexpr float m_PLAYER_ROTATION_SPEED = 0.15f;	// プレイヤーの回転の速さ
	static constexpr float m_PLAYER_JUMP = 22.5f;			// プレイヤーのジャンプ力
	static constexpr float m_PLAYER_SPEED = 1.0f;			// プレイヤーのスピード
	static constexpr float m_LEFTRIGHT = 0.5f;
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_size;
	bool m_bIsLanding;
	bool m_bJumping;
	bool m_IsRight;
	bool m_bCloneActive;
	bool m_bUseItem;
	static bool m_bUse;
	static bool m_bhalfwaypoint;
	int m_nTextureIdx;
	int m_nJumpCnt;
	int m_nModelIdx;
	int m_nLife;
	int m_nType;
	int m_nDeathTimer;
	int m_nRandomAction; // 0: 走るのみ, 1: 走りながらジャンプ
	int m_nTitleJump;
	CCloneCircle* m_pCloneCircle;  // CloneCircle のインスタンス
	CInputKeyboard* m_Keyboard;
	CInputJoyPad* m_JoyPad;
	CModelParts* m_pModelParts[15];
	CClone* m_pClone;
	CItem* m_pItem;
	CCollision* m_pCollision;
};

#pragma once