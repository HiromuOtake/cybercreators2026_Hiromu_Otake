//==============================================
//
// ALTER_EGO[number.cpp]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "object2D.h"

class CNumber : public CObject2D
{
public:
	CNumber(int nPriority = 8);
	~CNumber();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CNumber* Create(D3DXVECTOR3 pos, float fsizeX,float fsizeY);
	void SetTexturePos(int nTexPos);
	void SetDeath()override;
private:
	int  m_nTexPos;
};

#pragma once
