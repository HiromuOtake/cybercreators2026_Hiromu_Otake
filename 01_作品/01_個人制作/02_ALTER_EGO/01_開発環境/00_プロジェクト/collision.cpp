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
	bool isXOverlap = (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF) &&
		(mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF);

	bool isZOverlap = (mainpos.z + mainsize.z * HALF > objpos.z - objsize.z * HALF) &&
		(mainpos.z - mainsize.z * HALF < objpos.z + objsize.z * HALF);



	if (isXOverlap && isZOverlap)
	{
		// 上側の当たり判定
		if (mainpos.y < objpos.y + objsize.y * HALF &&
			mainposold.y >= objpos.y + objsize.y * HALF)
		{
			// mainをobjの上に押し戻し
			mainpos.y = objpos.y + objsize.y * HALF;
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
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * HALF) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * HALF);

	if (isYOverlap)
	{
		//右側の当たり判定
		if (mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF &&
			mainposold.x - mainsize.x * HALF >= objpos.x + objsize.x * HALF)
		{
			mainpos.x = objpos.x + objsize.x * HALF + mainsize.x * HALF;
		}
		//左側の当たり判定
		else if (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF &&
			mainposold.x + mainsize.x * HALF <= objpos.x - objsize.x * HALF)
		{
			mainpos.x = objpos.x - objsize.x * HALF - mainsize.x * HALF;
		}
	}
}

//======================================================
// 矩形の当たり判定処理
//======================================================
void CCollision::CollisionHitTriggerBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// X方向およびZ方向の重なりを一度だけチェック
	bool isXOverlap = (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF) &&
		(mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF);

	bool isZOverlap = (mainpos.z + mainsize.z * HALF > objpos.z - objsize.z * HALF) &&
		(mainpos.z - mainsize.z * HALF < objpos.z + objsize.z * HALF);

	if (isXOverlap && isZOverlap)
	{
		// 上側の当たり判定
		if (mainpos.y < objpos.y + objsize.y * HALF &&
			mainposold.y >= objpos.y + objsize.y * HALF)
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
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * HALF - m_GOAL_CORRECTION) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * HALF + m_GOAL_CORRECTION);

	if (isYOverlap)
	{
		//右側の当たり判定
		if (mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF &&
			mainposold.x - mainsize.x * HALF >= objpos.x + objsize.x * HALF)
		{
			bUse = false;
		}
		//左側の当たり判定
		else if (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF &&
			mainposold.x + mainsize.x * HALF <= objpos.x - objsize.x * HALF)
		{
			bUse = false;
		}
	}
}

//======================================================
// 矩形の当たり判定処理(プレイヤーリスポーン用)
//======================================================
void CCollision::CollisionHitTriggerRespawnBoxUpDown(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// X方向およびZ方向の重なりを一度だけチェック
	bool isXOverlap = (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF) &&
		(mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF);

	bool isZOverlap = (mainpos.z + mainsize.z * HALF > objpos.z - objsize.z * HALF) &&
		(mainpos.z - mainsize.z * HALF < objpos.z + objsize.z * HALF);

	if (isXOverlap && isZOverlap)
	{
		// 上側の当たり判定
		if (mainpos.y < objpos.y + objsize.y * HALF &&
			mainposold.y >= objpos.y + objsize.y * HALF)
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
// 矩形の当たり判定処理(プレイヤーリスポーン用)
//======================================================
void CCollision::CollisionHitTriggerRespawnBoxLeftRight(D3DXVECTOR3& mainpos, D3DXVECTOR3 mainposold, D3DXVECTOR3 mainsize, D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, bool& bUse)
{
	// Y方向およびZ方向の重なりを一度だけチェック
	bool isYOverlap = (mainpos.y + mainsize.y > objpos.y - objsize.y * HALF - m_GOAL_CORRECTION) &&
		(mainpos.y + mainsize.y <= objpos.y + objsize.y * HALF + m_GOAL_CORRECTION);

	if (isYOverlap)
	{
		//右側の当たり判定
		if (mainpos.x - mainsize.x * HALF < objpos.x + objsize.x * HALF &&
			mainposold.x - mainsize.x * HALF >= objpos.x + objsize.x * HALF)
		{
			bUse = true;
		}
		//左側の当たり判定
		else if (mainpos.x + mainsize.x * HALF > objpos.x - objsize.x * HALF &&
			mainposold.x + mainsize.x * HALF <= objpos.x - objsize.x * HALF)
		{
			bUse = true;
		}
	}
}

//======================================================
// 円の当たり判定処理
//======================================================
bool CCollision::CollisionPushCircle(D3DXVECTOR3 mainpos, D3DXVECTOR3 objpos, D3DXVECTOR3 mainsize, D3DXVECTOR3 objsize)
{
	D3DXVECTOR3 MainPos = mainpos;
	D3DXVECTOR3 ObjPos = objpos;

	D3DXVECTOR3 Distance;

	//ローカルに保存された各種数値を元に自分と対象オブジェクトの間の距離を計算
	Distance = MainPos - ObjPos;

	//中心点間の距離を計算 
	float DistanceVec = sqrtf((Distance.x * Distance.x) + (Distance.y * Distance.y) + (Distance.z * Distance.z));

	// それぞれのオブジェクトのサイズを基に、衝突範囲の半径を計算 サイズのX、Z、Yを考慮し、Y軸の影響は0.5倍で調整
	float radius = (mainsize.x + objsize.x) + (mainsize.y + objsize.y) + (mainsize.z + objsize.z) * HALF;

	if (DistanceVec <= radius)
	{
		return true;
	}

	return false;
}