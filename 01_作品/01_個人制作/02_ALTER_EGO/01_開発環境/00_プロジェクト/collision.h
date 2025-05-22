//======================================================
//
// ALTER_EGO [collision.h]
// Auther : ëÂí|Í§
//
//======================================================

#include "manager.h"

class CCollision
{
public:
	CCollision();
	~CCollision();
	void CollisionPushBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, D3DXVECTOR3& move, bool& blanding, int& njumpCnt);
	void CollisionPushBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize);
	void CollisionHitTriggerBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse);
	void CollisionHitTriggerBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse);
	void CollisionHitTriggerRespawnBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse);
	void CollisionHitTriggerRespawnBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse);
	bool CollisionPushCircle(D3DXVECTOR3 mainpos, D3DXVECTOR3 objpos, D3DXVECTOR3 mainsize, D3DXVECTOR3 objsize);
	static constexpr float m_GOAL_CORRECTION = 50.0f;		// ÉSÅ[ÉãÇÃîªíËÇÃï‚ê≥
private:
	bool m_bCollisionSwitch;
};

#pragma once
