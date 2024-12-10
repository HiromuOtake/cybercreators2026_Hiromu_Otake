//==============================================
//
//3Dスクロールアクション[player.h]
//Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"
#include "score.h"

class CPlayer : public CObjectX
{
public:
	typedef enum
	{
		PLAYER_NONE = 0,
		PLAYER_NORMAL,
		PLAYER_DEATH,
		PLAYER_MAX,
	}TYPE;
	CPlayer(int nPriority = 3);
	~CPlayer();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	bool Collision();
	bool GravityChanger();									// 重力反転
	bool CollisionUPDOWN(bool& bIsLanding, CObject* pObj);	// 当たり判定上下
	void CollisionLEFTRIGHT(CObject* pObj);					// 当たり判定左右
	static bool& GetGravity();								// 重力の向きの情報取得
	static bool& GetGravityRotation();						// 重力のブロックの回転情報取得
	static bool& GetGoal();									// ゴール情報の取得
	static CPlayer* Create(D3DXVECTOR3 pos);				// プレイヤーの生成
	static const int m_PLAYER_LIFE = 1;						// プレイヤーの体力
	static const int m_DEATH_COUNT = 30;					// プレイヤーが復活するまでの時間
	static const int m_RESET_PLAYER_POS_X = 200;			// プレイヤーを復活させる場所(X座標)
	static const int m_RESET_PLAYER_POS_Y = -1200;			// プレイヤーを復活させる場所(Y座標)
	static constexpr float m_PLAYER_SHOT_POS = 20.0f;		// プレイヤーが弾を出す位置の補正
	static constexpr float m_PLAYER_SHOT_MOVE = 15.0f;		// プレイヤーの弾の速度
	static constexpr float m_PLAYER_ROTATION_SPEED = 0.15f;	// プレイヤーの回転の速さ
	static constexpr float m_GRAVITY_DIRECTION = 2.0f;		// 重力の強さ(向き)
	static constexpr float m_PLAYER_JUMP = 30.0f;			// プレイヤーのジャンプ力
	static constexpr float m_PLAYER_SPEED = 1.0f;			// プレイヤーのスピード
	static constexpr float m_LEFTRIGHT = 0.5f;
	CScore* GetScore();
	void SetDeath()override;
private:
	D3DXVECTOR3 m_move;
	int m_nTextureIdx;
	bool m_bIsLanding;
	bool m_bJumping;
	bool m_bIsRight;
	static bool m_bGravity;
	static bool m_bGravityRotation;
	static bool m_bUse;
	static bool m_bhalfwaypoint;
	int m_JumpCnt;
	int m_nModelIdx;
	int m_nLife;
	int m_nType;
	int m_nDeathTimer;
	CInputKeyboard* m_Keyboard;
	CInputJoyPad* m_JoyPad;
	CScore* m_pScore;
};
#pragma once