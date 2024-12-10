////==============================================
////
//// 3Dスクロールアクション[bullet.cpp]
//// Author: hiromu otake
////
////==============================================
//
//#include "particle.h"
//
//// 静的メンバ初期化
//LPDIRECT3DTEXTURE9 CParticle::m_pTextureTemp = nullptr;
//
////==============================================
//// コンストラクタ
////==============================================
//CParticle::CParticle() : m_bUse(false), m_nLife(m_MAXLIFE), m_move{ 0.0f,0.0f,0.0f }, m_size(1.0f), m_speed(1.0f), m_color{ 1.0f, 1.0f, 1.0f, 1.0f }, m_pTexture(nullptr), m_pVtxBuff(nullptr)
//{
//
//}
//
////==============================================
//// デストラクタ
////==============================================
//CParticle::~CParticle()
//{
//
//}
//
////==============================================
//// 初期設定
////==============================================
//HRESULT CParticle::Init()
//{
//	CBillboard::Init();
//
//	CParticle::Load();
//
//	return S_OK;
//}
//
////==============================================
//// 終了処理
////==============================================
//void CParticle::Uninit()
//{
//	CBillboard::Uninit();
//
//	CObject::SetUseDeath(true);
//}
//
////==============================================
//// 更新処理
////==============================================
//void CParticle::Update()
//{
//	D3DXVECTOR3& pPos = CBillboard::GetPos();
//
//	//位置を更新
//	pPos += m_move;
//
//	if (m_nLife > 0)
//	{
//		m_nLife--;
//	}
//	if (m_nLife <= 0 || m_bUse == true)
//	{
//		Uninit();
//		CObject::SetDeath();
//		return;
//	}
//
//	CBillboard::Update();
//}
//
////==============================================
//// 描画処理
////==============================================
//void CParticle::Draw()
//{
//	if (m_pTextureTemp == nullptr)
//	{
//		return;  // テクスチャが読み込まれていない場合は描画しない
//	}
//
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ
//
//	//αブレンディングを加算合成に設定
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//
//	// 色の設定
//	pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b, m_color.a));
//
//	CBillboard::Draw();
//
//	//αブレンディングをもとに戻す
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	////Zの比較方法変更
//	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
//	////Zのバッファに書き込む
//	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//}
//
////=====================================================
//// 弾の設定処理(使ってるかいないか)
////=====================================================
//void CParticle::SetUse(bool bUse)
//{
//	m_bUse = bUse;
//}
//
////=====================================================
//// パーティクルの生成関数
////=====================================================
//CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size, float speed, D3DXCOLOR color)
//{
//	CParticle* pParticle = new CParticle;
//
//	if (pParticle != nullptr)
//	{
//		pParticle->Init();
//		pParticle->SetPos(pos);
//		pParticle->m_move = move * speed;
//		pParticle->SetSize(size);
//		pParticle->SetColor(color);
//		pParticle->SetUseDeath(true);
//	}
//
//	return pParticle;
//}
////======================================================
//// テクスチャの設定
////======================================================
//HRESULT CParticle::Load()
//{
//	if (m_pTextureTemp == nullptr)
//	{
//		LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
//
//		CRenderer* pRenderer = CManager::GetRenderere();
//
//		//デバイスの取得
//		pDevice = pRenderer->GetDevice();
//
//		//テクスチャの読み込み
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\Texture\\effect000.jpg",
//			&m_pTextureTemp);
//	}
//	return S_OK;
//}
//
////======================================================
//// テクスチャの破棄
////======================================================
//void CParticle::Unload()
//{
//	//テクスチャを破棄
//	if (m_pTextureTemp != NULL)
//	{
//		m_pTextureTemp->Release();
//		m_pTextureTemp = NULL;
//	}
//}
//
////======================================================
//// 移動量の取得
////======================================================
//D3DXVECTOR3* CParticle::GetMove()
//{
//	return &m_move;
//}
//
////=========================================
//// パーティクルの大きさを設定
////=========================================
//void CParticle::SetSize(float size)
//{
//	m_size = size;
//}
//
////=========================================
//// パーティクルの速さを設定
////=========================================
//void CParticle::SetSpeed(float speed)
//{
//	m_speed = speed;
//}
//
////=========================================
//// パーティクルの色を設定
////=========================================
//void CParticle::SetColor(D3DXCOLOR color)
//{
//	m_color = color;
//}
//
////=========================================
//// 死亡フラグ設定処理
////=========================================
//void CParticle::SetDeath()
//{
//	CObject::SetDeath();
//}
