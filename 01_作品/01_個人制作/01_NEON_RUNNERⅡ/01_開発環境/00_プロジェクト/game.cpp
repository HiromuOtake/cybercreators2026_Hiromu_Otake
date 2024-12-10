//==============================================
//
// 3D�X�N���[���A�N�V����[game.cpp]
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

//�ÓI�����o������
CPlayer* CGame::m_pPlayer = nullptr;
CItem* CGame::m_pItem = nullptr;
CCamera* CGame::m_pCamera = nullptr;

//======================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//======================================================
CGame::~CGame()
{

}

//======================================================
// �����ݒ�
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
		assert(false && "�X�e�[�W�t�@�C�����J���܂���ł����I");
		return E_FAIL;
	}
	int x = 0, y = 0;	// ���A�c

	// �� 1 �s�ǂݎ�� (���s�R�[�h�܂œǂݍ���)
	std::string n;
	while (std::getline(ifs, n, '\n'))
	{
		// stringstream �^�ɕϊ����āA���̓^�u��؂�ŕ�����𕪉����Ă���
		std::stringstream ss_n;
		ss_n << n;

		// �^�u��؂�œǂݍ���
		std::string t;
		while (std::getline(ss_n, t, '\t'))
		{
			// stringstream �^�ɕϊ����āA���́u_�v��؂�ŕ������Ă���
			std::stringstream ss_t;
			ss_t << t;

			// [0]: ���, [1]: �y�A�̃L�[
			std::vector<std::string> v;

			// �u_�v ��؂�œǂݍ���
			std::string pair;
			while (std::getline(ss_t, pair, '_'))
			{
				// �����ɒǉ�
				v.push_back(pair);
			}

			// ��ނ̔z��̒ǉ�
			m_nType[y][x] = std::stoi(v[0].c_str());

			// �y�A�����݂��邩�m�F����
			bool bHasPair = v.size() >= 2;
			std::string key = "none";	// ���݂��Ȃ�������L�[�� none �B�g�p����Ƃ��ɁAif(key == "none") ���^��������y�A�����݂��Ȃ��Ƃ�������
			if (bHasPair)
			{ // �y�A�̃L�[�����݂�����T�C�Y�� 2 �ɂȂ�B�ʏ�͎�ނ̂ݓ���̂ŃT�C�Y�� 1 �ɂȂ�B
				key = v[1];
			}

			// �L�[�����݂�����y�A��ǉ����郉���_��
			auto addPair = [this](const std::string& key, CObject* object) { CObject::GetPair()[key].push_back(object); };

			// ��ނ��Ƃɔz�u����
			switch (m_nType[y][x])
			{
			case 0:
				break;

			case 1: {
				CBlock* pObj = CBlock::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y* BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NORMAL);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// �y�A��ǉ�
					addPair(key, pObj);
				}
			} break;

			case 2: {
				CBlock* pObj = CBlockNeedle::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NEEDLE);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// �y�A��ǉ�
					addPair(key, pObj);
				}
			} break;

			case 3: {
				CBlock* pObj = CBlockGravity::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_GRAVITY);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// �y�A��ǉ�
					addPair(key, pObj);
				}
			} break;

			case 4: {
				CBlock* pObj = CBlockDoor::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT - 60.0f, 0.0f), CBlock::BLOCK::BLOCK_DOOR);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// �y�A��ǉ�
					addPair(key, pObj);
				}
			} break;

			case 5: {
				CBlock* pObj = CBlockButton::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_BUTTON);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// �y�A��ǉ�
					addPair(key, pObj);
				}
			} break;

			case 6: {
				CBlock* pObj = CBlockNeedleDown::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NEEDLEDOWN);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// �y�A��ǉ�
					addPair(key, pObj);
				}
			} break;

			case 7: {
				CBlock* pObj = CBlockNeedleDown::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_HALFWAYPOINT);
				pObj->SetPairKey(key.c_str());
				if (key != "none")
				{
					// �y�A��ǉ�
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
					// �y�A��ǉ�
					addPair(key, pObj);
				}
			} break;

			case 100:
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f));
				break;

			default:
				break;
			}
			x++;	// ���̃J�E���g�����Z
		}
		x = 0;	// ���̃J�E���g�����Z�b�g
		y++;	// �c�̃J�E���g�����Z
	}
#endif

	return S_OK;
}

//======================================================
// �I������
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
// �X�V����
//======================================================
void CGame::Update()
{
	m_pCamera->Update();

	CScene::Update();
}

//======================================================
// �`�揈��
//======================================================
void CGame::Draw()
{
	CScene::Draw();
}

//======================================================
// �v���C���[�̎擾
//======================================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//======================================================
// �J�����擾
//======================================================
CCamera* CGame::GetCamera()
{
	return m_pCamera;
}