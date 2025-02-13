//======================================================
//
// ALTER_EGO [collision.h]
// Auther : ��|�
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
	static constexpr float m_HALF_SIZE = 0.5f;			// ���f���𔼕��̃T�C�Y
	static constexpr float m_GOAL_CORRECTION = 50.0f;		// �S�[���̔���̕␳
private:
	bool m_bCollisionSwitch;
};

#pragma once
