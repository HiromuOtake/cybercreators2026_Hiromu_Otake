//==============================================
//
// 3Dスクロールアクション[light.h]
// Author: hiromu otake
//
//==============================================

#ifndef  _LIGHT_H_
#define  _LIGHT_H_

#include "main.h"

class CLight
{
public:
	CLight();
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();
	static const int m_MAXLIGHT = 4;
private:
	D3DLIGHT9 m_aLight[m_MAXLIGHT];
};

#endif

