//==============================================
//
// ALTER_EGO[game.cpp]
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
#include "pause.h"
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
	m_Keyboard = CManager::GetKeyboard();
	m_JoyPad = CManager::GetJoyPad();

	CScene::Init();

	CBg::Create(CScene::MODE::MODE_GAME);

	m_pCamera = CCamera::Create();

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);

	std::string filename = CManager::GetNextStage();

	//filename = "data\\Stage\\SetStage002.txt";

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
		}
		x = 0;
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

	pSound->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);
}

//======================================================
// 更新処理
//======================================================
void CGame::Update()
{
	m_pCamera->Update();

	CScene::Update();

	if (m_Keyboard->GetTrigger(DIK_P) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_START) == true)
	{
		CManager::SetPaused(true);
		CPause::Create();
	}
	if (m_Keyboard->GetTrigger(DIK_R) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_X) == true)
	{
		CManager::SetMode(CScene::MODE::MODE_GAME);
	}
}

//======================================================
// 描画処理
//======================================================
void CGame::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	CRenderer* pRenderer = CManager::GetRenderere();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//======================================================
// 生成処理
//======================================================
void CGame::CreateObject(int type, const std::string& key, D3DXVECTOR3 position, float rotation)
{
	CBlock* pObj_Block = nullptr;
	CItem* pObj_Itenm = nullptr;

	switch (type)
	{
	case 1:		// 通常ブロック
		pObj_Block = CBlock::Create(position, CBlock::BLOCK::BLOCK_NORMAL);
		break;

	case 2:		// トゲ(未実装)
		pObj_Block = CBlockNeedle::Create(position, CBlock::BLOCK::BLOCK_NEEDLE);
		break;

	case 4:		// ドア
		if (key == "R")
			pObj_Block = CBlockRedDoor::Create(position, CBlockRedDoor::DOOR_RED);
		else if (key == "B")
			pObj_Block = CBlockBlueDoor::Create(position, CBlockBlueDoor::DOOR_BLUE);
		else
			pObj_Block = CBlockDoor::Create(position, CBlock::BLOCK::BLOCK_DOOR,CBlockDoor::DOOR_NORMAL);
		break;

	case 5:		// ボタン
		if (key == "R")
			pObj_Block = CBlockRedButton::Create(position, CBlockRedButton::BUTTON_RED);
		else if (key == "B")
			pObj_Block = CBlockBlueButton::Create(position,CBlockBlueButton::BUTTON_BLUE);
		else
			pObj_Block = CBlockButton::Create(position, CBlock::BLOCK::BLOCK_BUTTON);
		break;

	case 11:	// アイテム
		pObj_Itenm = CItem::Create(position, CItem::ITEM::ITEM_STAR);
		break;

	case 99:	// ゴール
		pObj_Block = CBlockGoal::Create(position, CBlock::BLOCK::BLOCK_GOAL);
		break;

	default:
		break;
	}

	if (pObj_Block)
	{
		pObj_Block->SetPairKey(key.c_str());

		pObj_Block->SetRotation(rotation);

		if (key != "none")
		{
			// ペアを登録
			CObject::GetPair()[key].push_back(pObj_Block);
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