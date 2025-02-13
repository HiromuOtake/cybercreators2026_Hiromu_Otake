//======================================================
//
// ALTER_EGO [collision.cpp]
// Auther : 大竹熙
//
//======================================================

#include "collision.h"

//======================================================
// コンストラクタ
//======================================================
CCollision::CCollision()
{

}

//======================================================
// デストラクタ
//======================================================
CCollision::~CCollision()
{

}

//======================================================
// 矩形の押し出し処理
//======================================================
void CCollision::CollisionPushBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, D3DXVECTOR3& move, bool& blanding, int& njumpCnt)
{
	// X方向およびZ方向の重なりを一度だけチェック
	bool isXOverlap = (mainpos.x + mainsize.x * m_HALF_SIZE > objpos.x - objsize.x * m_HALF_SIZE) &&
		(mainpos.x - mainsize.x * m_HALF_SIZE < objpos.x + objsize.x * m_HALF_SIZE);

	bool isZOverlap = (mainpos.z + mainsize.z * m_HALF_SIZE > objpos.z - objsize.z * m_HALF_SIZE) &&
		(mainpos.z - mainsize.z * m_HALF_SIZE < objpos.z + objsize.z * m_HALF_SIZE);

	if (isXOverlap && isZOverlap)
	{
		// 上側の当たり判定
		if (mainpos.y < objpos.y + objsize.y * m_HALF_SIZE &&
			mainposold.y >= objpos.y + objsize.y * m_HALF_SIZE)
		{
			// mainをobjの上に押し戻し
			mainpos.y = objpos.y + objsize.y * m_HALF_SIZE;
			move.y = 0.0f;
			blanding = true;
			njumpCnt = 0;
		}
		// 下側の当たり判定
		else if (mainpos.y + mainsize.y > objpos.y - objsize.y &&
			mainposold.y + mainsize.y <= objpos.y - objsize.y)
		{
			// mainをobjの下に押し戻し
			mainpos.y = objpos.y - objsize.y - mainsize.y;
			move.y = 0.0f;
		}
	}
}

//======================================================
// 矩形の押し出し処理
//======================================================
void CCollision::CollisionPushBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize)
{
	// Y方向およびZ方向の重なりを一度だけチェック
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * m_HALF_SIZE) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * m_HALF_SIZE);

	if (isYOverlap)
	{
		//右側の当たり判定
		if (mainpos.x - mainsize.x * m_HALF_SIZE < objpos.x + objsize.x * m_HALF_SIZE &&
			mainposold.x - mainsize.x * m_HALF_SIZE >= objpos.x + objsize.x * m_HALF_SIZE)
		{
			mainpos.x = objpos.x + objsize.x * m_HALF_SIZE + mainsize.x * m_HALF_SIZE;
		}
		//左側の当たり判定
		else if (mainpos.x + mainsize.x * m_HALF_SIZE > objpos.x - objsize.x * m_HALF_SIZE &&
			mainposold.x + mainsize.x * m_HALF_SIZE <= objpos.x - objsize.x * m_HALF_SIZE)
		{
			mainpos.x = objpos.x - objsize.x * m_HALF_SIZE - mainsize.x * m_HALF_SIZE;
		}
	}
}

//======================================================
// 矩形の当たり判定処理
//======================================================
void CCollision::CollisionHitTriggerBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// X方向およびZ方向の重なりを一度だけチェック
	bool isXOverlap = (mainpos.x + mainsize.x * m_HALF_SIZE > objpos.x - objsize.x * m_HALF_SIZE) &&
		(mainpos.x - mainsize.x * m_HALF_SIZE < objpos.x + objsize.x * m_HALF_SIZE);

	bool isZOverlap = (mainpos.z + mainsize.z * m_HALF_SIZE > objpos.z - objsize.z * m_HALF_SIZE) &&
		(mainpos.z - mainsize.z * m_HALF_SIZE < objpos.z + objsize.z * m_HALF_SIZE);

	if (isXOverlap && isZOverlap)
	{
		// 上側の当たり判定
		if (mainpos.y < objpos.y + objsize.y * m_HALF_SIZE &&
			mainposold.y >= objpos.y + objsize.y * m_HALF_SIZE)
		{
			bUse = true;
		}
		// 下側の当たり判定
		else if (mainpos.y + mainsize.y > objpos.y - objsize.y &&
			mainposold.y + mainsize.y <= objpos.y - objsize.y)
		{
			bUse = true;
		}
	}
}

//======================================================
// 矩形の当たり判定処理
//======================================================
void CCollision::CollisionHitTriggerBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// Y方向およびZ方向の重なりを一度だけチェック
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * m_HALF_SIZE - m_GOAL_CORRECTION) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * m_HALF_SIZE + m_GOAL_CORRECTION);

	if (isYOverlap)
	{
		//右側の当たり判定
		if (mainpos.x - mainsize.x * m_HALF_SIZE < objpos.x + objsize.x * m_HALF_SIZE &&
			mainposold.x - mainsize.x * m_HALF_SIZE >= objpos.x + objsize.x * m_HALF_SIZE)
		{
			bUse = false;
		}
		//左側の当たり判定
		else if (mainpos.x + mainsize.x * m_HALF_SIZE > objpos.x - objsize.x * m_HALF_SIZE &&
			mainposold.x + mainsize.x * m_HALF_SIZE <= objpos.x - objsize.x * m_HALF_SIZE)
		{
			bUse = false;
		}
	}
}