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
	bool isXOverlap = (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF) &&
		(mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF);

	bool isZOverlap = (mainpos.z + mainsize.z * HALF > objpos.z - objsize.z * HALF) &&
		(mainpos.z - mainsize.z * HALF < objpos.z + objsize.z * HALF);



	if (isXOverlap && isZOverlap)
	{
		// �㑤�̓����蔻��
		if (mainpos.y < objpos.y + objsize.y * HALF &&
			mainposold.y >= objpos.y + objsize.y * HALF)
		{
			// main��obj�̏�ɉ����߂�
			mainpos.y = objpos.y + objsize.y * HALF;
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
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * HALF) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * HALF);

	if (isYOverlap)
	{
		//�E���̓����蔻��
		if (mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF &&
			mainposold.x - mainsize.x * HALF >= objpos.x + objsize.x * HALF)
		{
			mainpos.x = objpos.x + objsize.x * HALF + mainsize.x * HALF;
		}
		//�����̓����蔻��
		else if (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF &&
			mainposold.x + mainsize.x * HALF <= objpos.x - objsize.x * HALF)
		{
			mainpos.x = objpos.x - objsize.x * HALF - mainsize.x * HALF;
		}
	}
}

//======================================================
// ��`�̓����蔻�菈��
//======================================================
void CCollision::CollisionHitTriggerBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// X���������Z�����̏d�Ȃ����x�����`�F�b�N
	bool isXOverlap = (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF) &&
		(mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF);

	bool isZOverlap = (mainpos.z + mainsize.z * HALF > objpos.z - objsize.z * HALF) &&
		(mainpos.z - mainsize.z * HALF < objpos.z + objsize.z * HALF);

	if (isXOverlap && isZOverlap)
	{
		// �㑤�̓����蔻��
		if (mainpos.y < objpos.y + objsize.y * HALF &&
			mainposold.y >= objpos.y + objsize.y * HALF)
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
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * HALF - m_GOAL_CORRECTION) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * HALF + m_GOAL_CORRECTION);

	if (isYOverlap)
	{
		//�E���̓����蔻��
		if (mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF &&
			mainposold.x - mainsize.x * HALF >= objpos.x + objsize.x * HALF)
		{
			bUse = false;
		}
		//�����̓����蔻��
		else if (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF &&
			mainposold.x + mainsize.x * HALF <= objpos.x - objsize.x * HALF)
		{
			bUse = false;
		}
	}
}

//======================================================
// ��`�̓����蔻�菈��(�v���C���[���X�|�[���p)
//======================================================
void CCollision::CollisionHitTriggerRespawnBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// X���������Z�����̏d�Ȃ����x�����`�F�b�N
	bool isXOverlap = (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF) &&
		(mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF);

	bool isZOverlap = (mainpos.z + mainsize.z * HALF > objpos.z - objsize.z * HALF) &&
		(mainpos.z - mainsize.z * HALF < objpos.z + objsize.z * HALF);

	if (isXOverlap && isZOverlap)
	{
		// �㑤�̓����蔻��
		if (mainpos.y < objpos.y + objsize.y * HALF &&
			mainposold.y >= objpos.y + objsize.y * HALF)
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
// ��`�̓����蔻�菈��(�v���C���[���X�|�[���p)
//======================================================
void CCollision::CollisionHitTriggerRespawnBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * HALF - m_GOAL_CORRECTION) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * HALF + m_GOAL_CORRECTION);

	if (isYOverlap)
	{
		//�E���̓����蔻��
		if (mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF &&
			mainposold.x - mainsize.x * HALF >= objpos.x + objsize.x * HALF)
		{
			bUse = true;
		}
		//�����̓����蔻��
		else if (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF &&
			mainposold.x + mainsize.x * HALF <= objpos.x - objsize.x * HALF)
		{
			bUse = true;
		}
	}
}

//======================================================
// �~�̓����蔻�菈��
//======================================================
bool CCollision::CollisionPushCircle(D3DXVECTOR3 mainpos, D3DXVECTOR3 objpos, D3DXVECTOR3 mainsize, D3DXVECTOR3 objsize)
{
	D3DXVECTOR3 MainPos = mainpos;
	D3DXVECTOR3 ObjPos = objpos;

	D3DXVECTOR3 Distance;

	//���[�J���ɕۑ����ꂽ�e�퐔�l�����Ɏ����ƑΏۃI�u�W�F�N�g�̊Ԃ̋������v�Z
	Distance = MainPos - ObjPos;

	//���S�_�Ԃ̋������v�Z 
	float DistanceVec = sqrtf((Distance.x * Distance.x) + (Distance.y * Distance.y) + (Distance.z * Distance.z));

	// ���ꂼ��̃I�u�W�F�N�g�̃T�C�Y����ɁA�Փ˔͈͂̔��a���v�Z �T�C�Y��X�AZ�AY���l�����AY���̉e����0.5�{�Œ���
	float radius = (mainsize.x + objsize.x) + (mainsize.y + objsize.y) + (mainsize.z + objsize.z) * HALF;

	if (DistanceVec <= radius)
	{
		return true;
	}

	return false;
}