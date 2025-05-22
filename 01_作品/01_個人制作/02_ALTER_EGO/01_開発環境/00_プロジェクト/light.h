//==============================================
//
// ALTER_EGO[light.h]
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
	static constexpr float m_LIGHT_X_0 = 0.2f;		// 0番目のライトの位置(X)
	static constexpr float m_LIGHT_Y_0 = 0.8f;		// 0番目のライトの位置(Y)
	static constexpr float m_LIGHT_Z_0 = 0.4f;		// 0番目のライトの位置(Z)

	static constexpr float m_LIGHT_X_1 = 0.2f;		// 1番目のライトの位置(X)
	static constexpr float m_LIGHT_Y_1 = 1.0f;		// 1番目のライトの位置(Y)
	static constexpr float m_LIGHT_Z_1 = 1.0f;		// 1番目のライトの位置(Z)

	static constexpr float m_LIGHT_X_2 = 0.0f;		// 2番目のライトの位置(X)
	static constexpr float m_LIGHT_Y_2 = 1.0f;		// 2番目のライトの位置(Y)
	static constexpr float m_LIGHT_Z_2 = 1.0f;		// 2番目のライトの位置(Z)

	static constexpr float m_LIGHT_X_3 = 0.2f;		// 3番目のライトの位置(X)
	static constexpr float m_LIGHT_Y_3 = 0.4f;		// 3番目のライトの位置(Y)
	static constexpr float m_LIGHT_Z_3 = 0.4f;		// 3番目のライトの位置(Z)
private:
	D3DLIGHT9 m_aLight[m_MAXLIGHT];
};

#endif

