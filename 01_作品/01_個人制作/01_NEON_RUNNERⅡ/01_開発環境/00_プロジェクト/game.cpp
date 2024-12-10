//==============================================
//
// 3Dスクロールアクション[game.cpp]
// Author: hiromu otake
//
//==============================================

#include "game.h"
#include "player.h"
#include "field.h"
#include "block.h"
#include "item.h"
#include "billboard.h"
#include "camera.h"
#include "bg.h"
#include "score.h"
#include "sound.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

//静的メンバ初期化
CPlayer* CGame::m_pPlayer = nullptr;
CItem* CGame::m_pItem = nullptr;
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
#if 0
	CScene::Init();

	m_pCamera = CCamera::Create();

	FILE* pFile = fopen("data\\SetPosition001.txt", "r");

	CObject* pObj;

	for (int nCntHeight = 0; nCntHeight < m_BLOCK_VERTICAL; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < m_BLOCK_BESIDE; nCntWidth++)
		{
			fscanf(pFile, "%d", &m_nType[nCntWidth][nCntHeight]);

			switch (m_nType[nCntWidth][nCntHeight])
			{
			case 0:
				break;

			case 1:
				pObj = CBlock::Create(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, -nCntHeight * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NORMAL);
				break;

			case 2:
				pObj = CBlockNeedle::Create(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, -nCntHeight * BLOCK_HEIGHT, 0.0f), CBlockNeedle::BLOCK::BLOCK_NEEDLE);
				break;

			case 3:
				pObj = CBlockGravity::Create(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, -nCntHeight * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_GRAVITY);
				break;

			case 4:
				pObj = CBlockDoor::Create(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, -nCntHeight * 120.0f, 0.0f), CBlock::BLOCK::BLOCK_DOOR);
				break;

			case 5:
				pObj = CBlockButton::Create(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, -nCntHeight * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_BUTTON);
				break;

			case 11:
				pObj = CItem::Create(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, -nCntHeight * BLOCK_HEIGHT , 0.0f), CItem::ITEM::ITEM_COIN);
				break;

			case 99:
				pObj = CBlock::Create(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, -nCntHeight * BLOCK_HEIGHT + 50.0f, 0.0f), CBlock::BLOCK::BLOCK_GOAL);
				break;

			case 100:
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, -nCntHeight * BLOCK_HEIGHT, 0.0f));
				break;

				//case 14:
				//	SetItem(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, nCntHeight * BLOCK_HEIGHT, 0.0f), ITEMTYPE_THREE);
				//	break;

				//case 21:
				//	SetEnemy(D3DXVECTOR3(nCntWidth * BLOCK_WIDTH, nCntHeight * BLOCK_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_ZERO);
				//	break;
			}
		}
	}
#else
	CScene::Init();

	m_pCamera = CCamera::Create();

	CScene* pScene = CManager::GetScene();

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
		// stringstream 型に変換して、次はタブ区切りで文字列を分解していく
		std::stringstream ss_n;
		ss_n << n;

		// タブ区切りで読み込む
		std::string t;
		while (std::getline(ss_n, t, '\t'))
		{
			// stringstream 型に変換して、次は「_」区切りで分解していく
			std::stringstream ss_t;
			ss_t << t;

			// [0]: 種類, [1]: ペアのキー
			std::vector<std::string> v;

			// 「_」 区切りで読み込む
			std::string pair;
			while (std::getline(ss_t, pair, '_'))
			{
				// 末尾に追加
				v.push_back(pair);
			}

			// 種類の配列の追加
			m_nType[y][x] = std::stoi(v[0].c_str());

			// ペアが存在するか確認する
			bool bHasPair = v.size() >= 2;
			std::string key = "none";	// 存在しなかったらキーが none 。使用するときに、if(key == "none") が真だったらペアが存在しないということ
			if (bHasPair)
			{ // ペアのキーが存在したらサイズが 2 になる。通常は種類のみ入るのでサイズが 1 になる。
				key = v[1];
			}

			// キーが存在したらペアを追加するラムダ式
			auto addPair = [this](const std::string& key, CObject* object) { CObject::GetPair()[key].push_back(object); };

			// 種類ごとに配置する
			switch (m_nType[y][x])
			{
			case 0:
				break;

			case 1: {
				CBlock* pObj = CBlock::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y* BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NORMAL);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// ペアを追加
					addPair(key, pObj);
				}
			} break;

			case 2: {
				CBlock* pObj = CBlockNeedle::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NEEDLE);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// ペアを追加
					addPair(key, pObj);
				}
			} break;

			case 3: {
				CBlock* pObj = CBlockGravity::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_GRAVITY);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// ペアを追加
					addPair(key, pObj);
				}
			} break;

			case 4: {
				CBlock* pObj = CBlockDoor::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT - 60.0f, 0.0f), CBlock::BLOCK::BLOCK_DOOR);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// ペアを追加
					addPair(key, pObj);
				}
			} break;

			case 5: {
				CBlock* pObj = CBlockButton::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_BUTTON);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// ペアを追加
					addPair(key, pObj);
				}
			} break;

			case 6: {
				CBlock* pObj = CBlockNeedleDown::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NEEDLEDOWN);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// ペアを追加
					addPair(key, pObj);
				}
			} break;

			case 7: {
				CBlock* pObj = CBlockNeedleDown::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_HALFWAYPOINT);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// ペアを追加
					addPair(key, pObj);
				}
			} break;

			case 11:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_COIN);
				break;

			case 99: {
				CBlock* pObj = CBlock::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT + 50.0f, 0.0f), CBlock::BLOCK::BLOCK_GOAL);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// ペアを追加
					addPair(key, pObj);
				}
			} break;

			case 100:
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f));
				break;

			default:
				break;
			}
			x++;	// 横のカウントを加算
		}
		x = 0;	// 横のカウントをリセット
		y++;	// 縦のカウントを加算
	}
#endif

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