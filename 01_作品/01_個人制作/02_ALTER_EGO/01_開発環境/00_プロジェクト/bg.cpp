//==============================================
//
// ALTER_EGO[bg.cpp]
// Author: hiromu otake
//
//==============================================

#include "bg.h"
#include "texture.h"

//======================================================
// コンストラクタ
//======================================================
CBg::CBg(int nPriority) : CObject2D(nPriority), m_pVtxBuff(nullptr), m_pTexture(nullptr), m_nTexIdx(0), m_texScrollSpeed01(0.0f), m_texScrollSpeed02(SCREEN_WIDTH)
{

}

//======================================================
// デストラクタ
//======================================================
CBg::~CBg()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CBg::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VTX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// サイズをスクリーン全体に設定
	CObject2D::SetWidthHeight((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	// テクスチャの初期設定
	CObject2D::SetTexture(1.0f);
	// 中央に配置
	CObject2D::SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));

	CObject2D::Init();

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CBg::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject2D::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CBg::Update()
{
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// 背景1を左に移動
		m_texScrollSpeed01 -= 2.0f;
		if (m_texScrollSpeed01 <= -SCREEN_WIDTH) // 背景1が画面外に出たらリセット
		{
			m_texScrollSpeed01 = SCREEN_WIDTH;
		}

		// 背景2を左に移動
		m_texScrollSpeed02 -= 1.0f;
		if (m_texScrollSpeed02 <= -SCREEN_WIDTH) // 背景2が画面外に出たらリセット
		{
			m_texScrollSpeed02 = SCREEN_WIDTH;
		}

		// 背景1と背景2の位置を設定
		SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f + m_texScrollSpeed01, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	CObject2D::Update();
}

//======================================================
// 描画処理
//======================================================
void CBg::Draw()
{
	CObject2D::Draw();
}

void CBg::DrawTexture(int textureID, D3DXVECTOR2 position, D3DXVECTOR2 scale, float alpha)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();
	if (!pDevice) return;

	// テクスチャのアドレスを取得
	LPDIRECT3DTEXTURE9 pTexture = CManager::GetTexture()->GetAddress(textureID);
	if (!pTexture) return;

	// テクスチャの幅と高さを取得
	D3DSURFACE_DESC desc;
	if (FAILED(pTexture->GetLevelDesc(0, &desc))) return;
	float texWidth = static_cast<float>(desc.Width);
	float texHeight = static_cast<float>(desc.Height);

	// 頂点データの設定
	VTX_2D vertices[4];
	float width = texWidth * scale.x;
	float height = texHeight * scale.y;

	vertices[0] = { { position.x, position.y, 0.0f }, 1.0f, 0.0f, 0.0f, alpha };
	vertices[1] = { { position.x + width, position.y, 0.0f }, 1.0f, 1.0f, 0.0f, alpha };
	vertices[2] = { { position.x, position.y + height, 0.0f }, 1.0f, 0.0f, 1.0f, alpha };
	vertices[3] = { { position.x + width, position.y + height, 0.0f }, 1.0f, 1.0f, 1.0f, alpha };

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	pDevice->CreateVertexBuffer(sizeof(vertices), 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, &pVtxBuff, NULL);
	void* pVertices;
	pVtxBuff->Lock(0, sizeof(vertices), &pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	pVtxBuff->Unlock();

	// 投影行列設定
	D3DXMATRIX matOrtho;
	D3DXMatrixOrthoLH(&matOrtho, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	// 描画設定
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VTX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 描画後の設定復元
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pVtxBuff->Release(); // 頂点バッファを解放
}

//=====================================================
// 背景の生成
//=====================================================
CBg* CBg::Create(CScene::MODE mode)
{
	CBg* pBg = new CBg;
	
	int nId = 0;

	if (pBg != nullptr)
	{
		switch (mode)
		{
		case CScene::MODE::MODE_TITLE:
			nId = CManager::GetTexture()->Regist("data\\Texture\\titlelogo.png");
			break;

		case CScene::MODE::MODE_STAGESELECT:
			nId = CManager::GetTexture()->Regist("data\\Texture\\selectstageBG.png");
			break;

		case CScene::MODE::MODE_TUTORIAL1:
			nId = CManager::GetTexture()->Regist("data\\Texture\\tutorial01.png");
			break;

		case CScene::MODE::MODE_TUTORIAL2:
			nId = CManager::GetTexture()->Regist("data\\Texture\\tutorial02.png");
			break;

		case CScene::MODE::MODE_GAME:
			nId = CManager::GetTexture()->Regist("data\\Texture\\game001.png");
			break;

		case CScene::MODE::MODE_RESULT:
			nId = CManager::GetTexture()->Regist("data\\Texture\\result.png");
			break;

		default:
			break;
		}

		if (nId == -1)
		{
			OutputDebugStringA("テクスチャのロードに失敗しました。\n");
			delete pBg;
			return nullptr;
		}
		else
		{
			char debugMessage[256];
			sprintf(debugMessage, "テクスチャロード成功: ID = %d\n", nId);
			OutputDebugStringA(debugMessage);
		}

		pBg->SetType(TYPE_BG);
		pBg->BindTexture(CManager::GetTexture()->GetAddress(nId));
		pBg->Init();
		//pBg->SetUseDeath(true);
	}
	return  pBg;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBg::SetDeath()
{
	CObject::SetDeath();
}