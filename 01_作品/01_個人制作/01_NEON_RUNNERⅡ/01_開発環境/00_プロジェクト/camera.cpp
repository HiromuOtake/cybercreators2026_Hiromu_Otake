//==============================================
//
// 3Dスクロールアクション[camera.cpp]
// Author: hiromu otake
//
//==============================================

#include "camera.h"
#include "game.h"
#include "Tutorial.h"

// 静的メンバ初期化
D3DXVECTOR3 CCamera::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=====================================
// コンストラクタ
//=====================================
CCamera::CCamera() : m_Keyboard(nullptr)
{

}

//=====================================
// デストラクタ
//=====================================
CCamera::~CCamera()
{

}

//=====================================
// 初期設定
//=====================================
HRESULT CCamera::Init()
{
	m_Keyboard = CManager::GetKeyboard();
	m_posV = D3DXVECTOR3(0.0f, 400.0f, -400.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CCamera::Uninit()
{

}

//===============================
// 更新処理
//===============================
void CCamera::Update()
{
	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		if (CTutorial::GetPlayer() != nullptr)
		{
			m_posR = CTutorial::GetPlayer()->GetPos();
		}
	}
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (CGame::GetPlayer() != nullptr)
		{
			m_posR = CGame::GetPlayer()->GetPos();
		}
	}

	m_posV.x = m_posR.x + sinf(m_rot.y + D3DX_PI) * 1600.0f;
	m_posV.z = m_posR.z + cosf(m_rot.y + D3DX_PI) * 1600.0f;

	m_posV.y = m_posR.y;
}

//===============================
//カメラの設定処理
//===============================
void CCamera::SetCamera()
{
	D3DXVECTOR3 PosV = m_posV;
	D3DXVECTOR3 PosR = m_posR;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	CRenderer* pRenderer = CManager::GetRenderere();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,     //画面のアスペクト比 
		10.0f,											//Z値の最小値
		3000.0f);										//Z値の最大値

	//D3DXMatrixOrthoLH(&m_mtxProjection,
	//	(float)SCREEN_WIDTH,
	//	(float)SCREEN_HEIGHT,
	//	10.0f,
	//	3000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = D3DXVECTOR3(0, 0, 0);

	//if (m_nShakeTime > 0)
	//{
	//	m_nShakeTime--;
	//	adjust.x += m_fShakePower;
	//	adjust.y += m_fShakePower;

	//	adjust.x = (float)(rand()% 100 - 50) * m_fShakePower;
	//	adjust.y = (float)(rand()% 100 - 50) * m_fShakePower;

	//	PosV += adjust;
	//	PosR += adjust;
	//}

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&PosV,		//視点
		&PosR,		//注視点
		&m_vecU);	//上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//===============================
//カメラの向きの取得
//===============================
D3DXVECTOR3* CCamera::GetRot()
{
	return &m_rot;
}

////===============================
////カメラの揺れの設定
////===============================
//void CCamera::SetShake(int nShakeTime, float fShakePower)
//{
//	m_nShakeTime = nShakeTime;
//	m_fShakePower = fShakePower;
//}

//=====================================================
// フィールドの生成
//=====================================================
CCamera* CCamera::Create()
{
	CCamera* pCamera = new CCamera;

	if (pCamera != nullptr)
	{
		pCamera->Init();
	}
	return  pCamera;
}
