//==============================================
//
// ALTER_EGO[light.cpp]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "light.h"
#include "input.h"

//====================================
// コンストラクタ
//====================================
CLight::CLight()
{
	// ライト情報のクリア
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));
}

//====================================
// デストラクタ
//====================================
CLight::~CLight()
{

}

//=====================================
// 初期設定
//=====================================
HRESULT CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();

	D3DXVECTOR3 vecDir;			//設定用ベクトル

	for (int nCntLight = 0; nCntLight < m_MAXLIGHT; nCntLight++)
	{
		//ライトの種類を設定
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ライトの方向を設定
		switch (nCntLight)
		{
		case 0:
			vecDir = D3DXVECTOR3(m_LIGHT_X_0, -m_LIGHT_Y_0, m_LIGHT_Z_0);
			break;

		case 1:
			vecDir = D3DXVECTOR3(m_LIGHT_X_1, -m_LIGHT_Y_1, -m_LIGHT_Z_1);
			break;

		case 2:
			vecDir = D3DXVECTOR3(m_LIGHT_X_2, m_LIGHT_Y_2, m_LIGHT_Z_2);
			break;

		case 3:
			vecDir = D3DXVECTOR3(-m_LIGHT_X_3, m_LIGHT_Y_3, -m_LIGHT_Z_3);
			break;

		default:
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);          //ベクトルを正規化する
		m_aLight[nCntLight].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);

	}
	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CLight::Uninit()
{

}

//=====================================
// 更新処理
//=====================================
void CLight::Update()
{

}
