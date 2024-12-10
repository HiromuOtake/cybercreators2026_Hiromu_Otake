//==============================================
//
// 3Dスクロールアクション[light.cpp]
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
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	CRenderer* pRenderer = CManager::GetRenderere();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();
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
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			break;

		case 1:
			vecDir = D3DXVECTOR3(0.2f, -1.0f, -1.0f);
			break;

		case 2:
			vecDir = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
			break;

		case 3:
			vecDir = D3DXVECTOR3(-0.2f, 0.4f, -0.4f);
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
