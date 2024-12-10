//==============================================
//
// 3Dスクロールアクション[tutorial.cpp]
// Author: hiromu otake
//
//==============================================

#include "tutorial.h"
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
CPlayer* CTutorial::m_pPlayer = nullptr;
CItem* CTutorial::m_pItem = nullptr;
CCamera* CTutorial::m_pCamera = nullptr;

//======================================================
// コンストラクタ
//======================================================
CTutorial::CTutorial() : m_nType{}
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
CTutorial::~CTutorial()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CTutorial::Init()
{
	CScene::Init();

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	m_pCamera = CCamera::Create();

	CScene* pScene = CManager::GetScene();

	std::string filename;

	filename = "data\\TutorialStage.txt";

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
				CBlock* pObj = CBlock::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NORMAL);
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

			case 11:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_COIN);
				break;

			case 21:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_T_JUMP);
				break;

			case 22:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_T_DOUBLE_JUMP);
				break;

			case 23:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_T_SHOT);
				break;

			case 24:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_T_COIN);
				break;

			case 25:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_T_NEEDLE);
				break;

			case 26:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_T_GRAVITY);
				break;

			case 27:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_T_DOOR);
				break;

			case 28:
				CItem::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CItem::ITEM::ITEM_T_GOAL);
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
	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CTutorial::Uninit()
{
	m_pCamera->Uninit();
	delete m_pCamera;
	m_pCamera = nullptr;

	m_pPlayer->SetUseDeath(true);
	m_pPlayer->SetDeath();
	m_pPlayer = nullptr;

	CScene::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CTutorial::Update()
{
	m_pCamera->Update();

	CScene::Update();
}

//======================================================
// 描画処理
//======================================================
void CTutorial::Draw()
{
	CScene::Draw();
}

//======================================================
// プレイヤーの取得
//======================================================
CPlayer* CTutorial::GetPlayer()
{
	return m_pPlayer;
}

//======================================================
// カメラ取得
//======================================================
CCamera* CTutorial::GetCamera()
{
	return m_pCamera;
}