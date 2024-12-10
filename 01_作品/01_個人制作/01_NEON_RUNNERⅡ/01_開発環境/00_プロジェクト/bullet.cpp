//==============================================
//
// 3Dスクロールアクション[bullet.cpp]
// Author: hiromu otake
//
//==============================================

#include "bullet.h"

// 静的メンバ初期化
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = nullptr;

//==============================================
// コンストラクタ
//==============================================
CBullet::CBullet() : m_bUse(false), m_nLife(m_MAXLIFE), m_move{ 0.0f,0.0f,0.0f }, m_pTexture(nullptr), m_pVtxBuff(nullptr)
{

}

//==============================================
// デストラクタ
//==============================================
CBullet::~CBullet()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CBullet::Init()
{
	CBillboard::Init();

	CBullet::Load();

	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CBullet::Uninit()
{
	CBillboard::Uninit();

	CObject::SetUseDeath(true);
}

//==============================================
// 更新処理
//==============================================
void CBullet::Update()
{
	D3DXVECTOR3& pPos = CBillboard::GetPos();

	//位置を更新
	pPos += m_move;

	if (m_nLife > 0)
	{
		m_nLife--;
	}
	if (m_nLife <= 0 || m_bUse == true)
	{
		Uninit();
		CObject::SetDeath();
		return;
	}

	CBillboard::Update();
}

//==============================================
// 描画処理
//==============================================
void CBullet::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 5);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CBillboard::Draw();

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	////Zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	////Zのバッファに書き込む
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//=====================================================
// 弾の設定処理(使ってるかいないか)
//=====================================================
void CBullet::SetUse(bool bUse)
{
	m_bUse = bUse;
}

//=====================================================
// フィールドの生成
//=====================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet* pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		pBullet->SetType(TYPE_BULLET);
		pBullet->Init();
		pBullet->SetPos(pos);
		pBullet->BindTexture(m_pTextureTemp);
		pBullet->m_move = move;
		pBullet->SetUseDeath(true);
	}
	return  pBullet;
}

//======================================================
// テクスチャの設定
//======================================================
HRESULT CBullet::Load()
{
	if (m_pTextureTemp == nullptr)
	{
		LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

		CRenderer* pRenderer = CManager::GetRenderere();

		//デバイスの取得
		pDevice = pRenderer->GetDevice();

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\Texture\\bullet000.png",
			&m_pTextureTemp);
	}
	return S_OK;
}

//======================================================
// テクスチャの破棄
//======================================================
void CBullet::Unload()
{
	//テクスチャを破棄
	if (m_pTextureTemp != NULL)
	{
		m_pTextureTemp->Release();
		m_pTextureTemp = NULL;
	}
}

//======================================================
// 移動量の取得
//======================================================
D3DXVECTOR3* CBullet::GetMove()
{
	return &m_move;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBullet::SetDeath()
{
	CObject::SetDeath();
}
