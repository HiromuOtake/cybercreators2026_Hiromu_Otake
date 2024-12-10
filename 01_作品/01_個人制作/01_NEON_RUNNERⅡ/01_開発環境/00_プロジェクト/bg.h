//==============================================
//
// 3Dスクロールアクション[bg.cpp]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "object2D.h"

class CBg : public CObject2D
{
public:
	CBg(int nPriority = 0);
	~CBg();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CBg* Create(CScene::MODE mode, D3DXVECTOR3 pos);
	void SetDeath()override;
private:
};

#pragma once
