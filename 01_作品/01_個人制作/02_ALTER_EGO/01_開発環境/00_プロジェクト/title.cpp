//==============================================
//
// ALTER_EGO[title.cpp]
// Author: hiromu otake
//
//==============================================

#include "title.h"
#include "bg.h"
#include "block.h"
#include <sstream>
#include <fstream>

//静的メンバ初期化
CPlayer* CTitle::m_pPlayer = nullptr;
CCamera* CTitle::m_pCamera = nullptr;

//======================================================
// コンストラクタ
//======================================================
CTitle::CTitle() : m_pBg(nullptr), m_nType{}
{
	for (int nCntBeside = 0; nCntBeside < m_BLOCK_BESIDE; nCntBeside++)
	{
		for (int nCntVertical = 0; nCntVertical < m_BLOCK_VERTICAL; nCntVertical++)
		{
			m_nType[nCntBeside][nCntVertical] = {};
		}
	}
}

//======================================================
// デストラクタ
//======================================================
CTitle::~CTitle()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CTitle::Init()
{
	CScene::Init();

	// 背景を作成
	m_pBg = CBg::Create(CScene::MODE::MODE_TITLE);	
	assert(m_pBg && "背景の作成に失敗しました！");

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	m_pCamera = CCamera::Create();

	std::string filename;

	filename = "data\\Stage\\SetStageTitle.txt";

	std::ifstream ifs(filename);
	if (!ifs)
	{
		assert(false && "ステージファイルを開けませんでした！");
		return E_FAIL;
	}
	int x = 0, y = 0;	// 横、縦

	// 横 1 行読み取る (改行コードまで読み込む)
	std::string n;
	while (std::getline(ifs, n, '\n'))
	{
		std::stringstream ss_n(n);
		std::string t;

		while (std::getline(ss_n, t, '\t'))
		{
			std::stringstream ss_t(t);
			std::vector<std::string> v;
			std::string pair;

			// 「_」 区切りで読み込む
			while (std::getline(ss_t, pair, '_'))
			{
				v.push_back(pair);
			}

			int type = std::stoi(v[0]);

			if (type == 100)
			{
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f));
			}
			else if (type == 1)
			{
				CBlock::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NORMAL);
			}
			else
			{

			}
			x++;
		}
		x = 0;
		y++;
	}
	return S_OK;

}

//======================================================
// 終了処理
//======================================================
void CTitle::Uninit()
{
	CSound* pSound = CManager::GetSound();

	pSound->StopAllSound();

	m_pCamera->Uninit();
	delete m_pCamera;
	m_pCamera = nullptr;

	m_pPlayer->SetUseDeath(true);
	m_pPlayer->SetDeath();
	m_pPlayer = nullptr;

	// 背景の解放
	if (m_pBg)
	{
		m_pBg->SetDeath();
		m_pBg = nullptr;
	}

	CScene::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CTitle::Update()
{
	m_pCamera->Update();

	CScene::Update();
}

//======================================================
// 描画処理
//======================================================
void CTitle::Draw()
{
	//LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//CRenderer* pRenderer = CManager::GetRenderere();

	////デバイスの取得
	//pDevice = pRenderer->GetDevice();

	////頂点バッファをデータストリームに設定
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	////頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	////テクスチャの設定
	//pDevice->SetTexture(0, m_pTexture);

	////ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//======================================================
// カメラ取得
//======================================================
CCamera* CTitle::GetCamera()
{
	return m_pCamera;
}