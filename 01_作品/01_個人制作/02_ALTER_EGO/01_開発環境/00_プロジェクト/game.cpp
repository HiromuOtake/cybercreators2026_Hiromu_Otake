//==============================================
//
// 3Dスクロールアクション[game.cpp]
// Author: hiromu otake
//
//==============================================

#include "game.h"
#include "player.h"
#include "clone.h"
#include "field.h"
#include "block.h"
#include "item.h"
#include "billboard.h"
#include "camera.h"
#include "bg.h"
#include "sound.h"
#include "modelparts.h"
#include "character.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

//静的メンバ初期化
CPlayer* CGame::m_pPlayer = nullptr;
CCamera* CGame::m_pCamera = nullptr;

//======================================================
// コンストラクタ
//======================================================
CGame::CGame() : m_nType{}
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
CGame::~CGame()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CGame::Init()
{
	CScene::Init();

	m_pCamera = CCamera::Create();

	//CScene* pScene = CManager::GetScene();

	std::string filename;

	filename = "data\\SetStage001.txt";

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
			std::string key = (v.size() > 1) ? v[1] : "none";
			float rotation = (v.size() > 2) ? std::stof(v[2]) : 0.0f;  // 3つ目の要素を回転情報として取得

			if (type == 100)
			{
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f));
			}
			else
			{
				CreateObject(type, key, D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), rotation);
			}
			x++;
		}	x = 0;
		y++;
	}
	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CGame::Uninit()
{
	m_pCamera->Uninit();
	delete m_pCamera;
	m_pCamera = nullptr;

	m_pPlayer->SetUseDeath(true);
	m_pPlayer->SetDeath();
	m_pPlayer = nullptr;

	CScene::Uninit();

	CSound* pSound = CManager::GetSound();

	pSound->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);
}

//======================================================
// 更新処理
//======================================================
void CGame::Update()
{
	m_pCamera->Update();

	CScene::Update();
}

//======================================================
// 描画処理
//======================================================
void CGame::Draw()
{
	CScene::Draw();
}

//======================================================
// 生成処理
//======================================================
void CGame::CreateObject(int type, const std::string& key, D3DXVECTOR3 position, float rotation)
{
	CBlock* pObj = nullptr;

	switch (type)
	{
	case 1:
		pObj = CBlock::Create(position, CBlock::BLOCK::BLOCK_NORMAL);
		break;
	case 4:
		pObj = CBlockDoor::Create(position, CBlock::BLOCK::BLOCK_DOOR);
		break;
	case 5:
		pObj = CBlockButton::Create(position, CBlock::BLOCK::BLOCK_BUTTON);
		break;
	case 99:
		pObj = CBlockGoal::Create(position, CBlock::BLOCK::BLOCK_GOAL);
		break;
	default:
		break;
	}

	if (pObj)
	{
		pObj->SetPairKey(key.c_str());

		pObj->SetRotation(rotation);

		if (key != "none")
		{
			// ペアを登録
			CObject::GetPair()[key].push_back(pObj);
		}
	}
}

//======================================================
// プレイヤーの取得
//======================================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//======================================================
// カメラ取得
//======================================================
CCamera* CGame::GetCamera()
{
	return m_pCamera;
}