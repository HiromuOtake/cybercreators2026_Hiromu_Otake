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
#include "collision.h"

class CClone : public CCharacter
{
public:
	typedef enum
	{
		PLAYER_NONE = 0,
		PLAYER_NORMAL,
		PLAYER_DEATH,
		PLAYER_MAX,
	}TYPE;
	CClone(int nPriority = 3);
	~CClone()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	bool CollisionUPDOWN(bool& bIsLanding, CObject* pObj);					// 当たり判定上下
	void CollisionLEFTRIGHT(CObject* pObj);									// 当たり判定左右
	static bool& GetGoal() { return m_bUse; }								// ゴール情報の取得
	void SetStopClone(bool bStopClone) { m_bStopClone = bStopClone; }		// クローンの動きON/OFFスイッチ
	static CClone* Create(D3DXVECTOR3 pos);									// クローンの生成
	static const int m_CLONE_LIFE = 1;										// クローンの体力
	static const int m_DEATH_COUNT = 30;									// クローンが復活するまでの時間
	static const int m_RESET_CLONE_POS_X = 200;								// クローンを復活させる場所(X座標)
	static const int m_RESET_CLONE_POS_Y = -1200;							// クローンを復活させる場所(Y座標)
	static constexpr float m_CLONE_SHOT_POS = 20.0f;						// クローンが弾を出す位置の補正
	static constexpr float m_CLONE_SHOT_MOVE = 15.0f;						// クローンの弾の速度
	static constexpr float m_CLONE_ROTATION_SPEED = 0.15f;					// クローンの回転の速さ
	static constexpr float m_CLONE_JUMP = 22.5f;							// クローンのジャンプ力
	static constexpr float m_CLONE_SPEED = 1.0f;							// クローンのスピード
	static constexpr float m_LEFTRIGHT = 0.5f;
	void SetDeath()override;
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_size;
	int m_nTextureIdx;
	bool m_bLanding;
	bool m_bJumping;
	bool m_bStopClone;
	static bool m_bUse;
	static bool m_bhalfwaypoint;
	int m_nJumpCnt;
	int m_nModelIdx;
	int m_nLife;
	int m_nType;
	int m_nDeathTimer;
	CInputKeyboard* m_Keyboard;
	CInputJoyPad* m_JoyPad;
	CModelParts* m_pModelParts[15];
	CCollision* m_pCollision;
};

#pragma once