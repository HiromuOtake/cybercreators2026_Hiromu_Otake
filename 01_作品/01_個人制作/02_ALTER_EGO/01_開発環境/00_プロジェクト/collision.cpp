//======================================================
//
// ALTER_EGO [collision.cpp]
// Auther : ��|�
//
//======================================================

#include "collision.h"

//======================================================
// �R���X�g���N�^
//======================================================
CCollision::CCollision()
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CCollision::~CCollision()
{

}

//======================================================
// ��`�̉����o������
//======================================================
void CCollision::CollisionPushBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, D3DXVECTOR3& move, bool& blanding, int& njumpCnt)
{
	// X���������Z�����̏d�Ȃ����x�����`�F�b�N
	bool isXOverlap = (mainpos.x + mainsize.x * m_HALF_SIZE > objpos.x - objsize.x * m_HALF_SIZE) &&
		(mainpos.x - mainsize.x * m_HALF_SIZE < objpos.x + objsize.x * m_HALF_SIZE);

	bool isZOverlap = (mainpos.z + mainsize.z * m_HALF_SIZE > objpos.z - objsize.z * m_HALF_SIZE) &&
		(mainpos.z - mainsize.z * m_HALF_SIZE < objpos.z + objsize.z * m_HALF_SIZE);

	if (isXOverlap && isZOverlap)
	{
		// �㑤�̓����蔻��
		if (mainpos.y < objpos.y + objsize.y * m_HALF_SIZE &&
			mainposold.y >= objpos.y + objsize.y * m_HALF_SIZE)
		{
			// main��obj�̏�ɉ����߂�
			mainpos.y = objpos.y + objsize.y * m_HALF_SIZE;
			move.y = 0.0f;
			blanding = true;
			njumpCnt = 0;
		}
		// �����̓����蔻��
		else if (mainpos.y + mainsize.y > objpos.y - objsize.y &&
			mainposold.y + mainsize.y <= objpos.y - objsize.y)
		{
			// main��obj�̉��ɉ����߂�
			mainpos.y = objpos.y - objsize.y - mainsize.y;
			move.y = 0.0f;
		}
	}
}

//======================================================
// ��`�̉����o������
//======================================================
void CCollision::CollisionPushBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize)
{
	// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * m_HALF_SIZE) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * m_HALF_SIZE);

	if (isYOverlap)
	{
		//�E���̓����蔻��
		if (mainpos.x - mainsize.x * m_HALF_SIZE < objpos.x + objsize.x * m_HALF_SIZE &&
			mainposold.x - mainsize.x * m_HALF_SIZE >= objpos.x + objsize.x * m_HALF_SIZE)
		{
			mainpos.x = objpos.x + objsize.x * m_HALF_SIZE + mainsize.x * m_HALF_SIZE;
		}
		//�����̓����蔻��
		else if (mainpos.x + mainsize.x * m_HALF_SIZE > objpos.x - objsize.x * m_HALF_SIZE &&
			mainposold.x + mainsize.x * m_HALF_SIZE <= objpos.x - objsize.x * m_HALF_SIZE)
		{
			mainpos.x = objpos.x - objsize.x * m_HALF_SIZE - mainsize.x * m_HALF_SIZE;
		}
	}
}

//======================================================
// ��`�̓����蔻�菈��
//======================================================
void CCollision::CollisionHitTriggerBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// X���������Z�����̏d�Ȃ����x�����`�F�b�N
	bool isXOverlap = (mainpos.x + mainsize.x * m_HALF_SIZE > objpos.x - objsize.x * m_HALF_SIZE) &&
		(mainpos.x - mainsize.x * m_HALF_SIZE < objpos.x + objsize.x * m_HALF_SIZE);

	bool isZOverlap = (mainpos.z + mainsize.z * m_HALF_SIZE > objpos.z - objsize.z * m_HALF_SIZE) &&
		(mainpos.z - mainsize.z * m_HALF_SIZE < objpos.z + objsize.z * m_HALF_SIZE);

	if (isXOverlap && isZOverlap)
	{
		// �㑤�̓����蔻��
		if (mainpos.y < objpos.y + objsize.y * m_HALF_SIZE &&
			mainposold.y >= objpos.y + objsize.y * m_HALF_SIZE)
		{
			bUse = true;
		}
		// �����̓����蔻��
		else if (mainpos.y + mainsize.y > objpos.y - objsize.y &&
			mainposold.y + mainsize.y <= objpos.y - objsize.y)
		{
			bUse = true;
		}
	}
}

//======================================================
// ��`�̓����蔻�菈��
//======================================================
void CCollision::CollisionHitTriggerBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * m_HALF_SIZE - m_GOAL_CORRECTION) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * m_HALF_SIZE + m_GOAL_CORRECTION);

	if (isYOverlap)
	{
		//�E���̓����蔻��
		if (mainpos.x - mainsize.x * m_HALF_SIZE < objpos.x + objsize.x * m_HALF_SIZE &&
			mainposold.x - mainsize.x * m_HALF_SIZE >= objpos.x + objsize.x * m_HALF_SIZE)
		{
			bUse = false;
		}
		//�����̓����蔻��
		else if (mainpos.x + mainsize.x * m_HALF_SIZE > objpos.x - objsize.x * m_HALF_SIZE &&
			mainposold.x + mainsize.x * m_HALF_SIZE <= objpos.x - objsize.x * m_HALF_SIZE)
		{
			bUse = false;
		}
	}
}