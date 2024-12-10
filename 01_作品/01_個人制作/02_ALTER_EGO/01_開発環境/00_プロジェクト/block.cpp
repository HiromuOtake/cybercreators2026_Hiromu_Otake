//==============================================
//
// 3Dスクロールアクション[block.cpp]
// Author: hiromu otake
//
//==============================================

#include "block.h"
#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "particlemanager.h"
#include <random>

//==============================================
// コンストラクタ
//==============================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority), m_BlockType(BLOCK_NONE), m_Keyboard(nullptr), m_pVtxBuff(nullptr), m_bOpen(false)
, m_nModelIdx(0), m_nTimer(0), m_nTexIdx(0), m_move{ 0.0f,0.0f,0.0f }
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockNeedle::CBlockNeedle(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockButton::CBlockButton(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0), m_bOpen(false)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockDoor::CBlockDoor(int nPriority) : CBlock(nPriority), m_deleteDoor(1.0f), m_nModelIdx(0), m_nTexIdx(0), m_Keyboard(nullptr), m_pPlayer(nullptr)
{
	m_Timer = 0;
}

//==============================================
// コンストラクタ
//==============================================
CBlockGoal::CBlockGoal(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// デストラクタ
//==============================================
CBlock::~CBlock()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockNeedle::~CBlockNeedle()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockButton::~CBlockButton()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockDoor::~CBlockDoor()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockGoal::~CBlockGoal()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CBlock::Init()
{
	SetType(TYPE_BLOCK);

	m_Keyboard = CManager::GetKeyboard();

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonblock.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\neonblock.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockNeedle::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonneedle.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\needle.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockButton::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\switch.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockDoor::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\door.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	CObjectX::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockGoal::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\goal.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\potal3.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CBlock::Uninit()
{
	CObjectX::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockNeedle::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockButton::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockDoor::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 終了処理
//==============================================
void CBlockGoal::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// 更新処理
//==============================================
void CBlock::Update()
{
	// 回転行列を適用
	if (m_fRotation != 0.0f)
	{
		D3DXMATRIX matRotation;
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(m_fRotation));  // Y軸回転

		// ワールド行列に回転を適用
		D3DXMatrixMultiply(&m_matWorld, &matRotation, &m_matWorld);
	}

	CObjectX::Update();
}

//==============================================
// 更新処理
//==============================================
void CBlockNeedle::Update()
{
	CBlock::Update();
}

//==============================================
// 更新処理
//==============================================
void CBlockButton::Update()
{
	std::random_device seed;
	std::mt19937 random(seed());
	int nMin = 1;
	int nMax = 4;
	float a = 1.0f;
	float b = 1.0f;

	std::uniform_int_distribution<> number(nMin, nMax);

	if (number(random) == 1)
	{
		a = 1.0f;
	}
	if (number(random) == 2)
	{
		b = 1.0f;
	}
	if (number(random) == 3)
	{
		a = -1.0f;
	}
	if (number(random) == 4)
	{
		b = -1.0f;
	}

	D3DXVECTOR3 pos = CBlockButton::GetPos();
	//CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(a, b, 0.0f));

	// ボタンが押されているかを判定
	bool bPressed = false;

	// 判定ロジック（ここでボタンが押されているかどうかを計算）
	for (const auto& object : CObject::GetAllObjects())
	{
		if (object->GetType() == TYPE_PLAYER)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(object);
			if (player != nullptr)
			{
				// 衝突判定（省略可能）
				if (IsCollisionPlayer(player))
				{
					bPressed = true;
					break;
				}
			}

			CClone* clone = dynamic_cast<CClone*>(object);
			if (clone != nullptr)
			{
				// 衝突判定（省略可能）
				if (IsCollisionClone(clone))
				{
					bPressed = true;
					break;
				}
			}
		}
	}

	if (m_bOpen != true)
	{
		// ボタンの状態を更新
		m_bOpen = bPressed;
	}

	CBlock::Update();
}

//==============================================
// 更新処理
//==============================================
void CBlockDoor::Update()
{
	//CSound* pSound = CManager::GetSound();

	bool bOpenDoor = false;

	// キーの取得
	const std::string& key = GetPairKey();
	if (key != "none")
	{ // キーが存在する
		for (const auto& object : CObject::GetPair()[key])
		{
			if (object == nullptr)
			{ // 空だった
				continue;
			}

			if (this == object)
			{ // 自分自身だった
				continue;
			}

			if (CBlockButton* button = dynamic_cast<CBlockButton*>(object))
			{
				if (button->GetOpenDoor())
				{
					//pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_BUTON);

					bOpenDoor = true;
					break;
				}
			}
		}
	}

	if (bOpenDoor == true)
	{
		m_deleteDoor--;

		CBlockDoor::SetScale(D3DXVECTOR3(m_deleteDoor, m_deleteDoor, m_deleteDoor));

		m_Timer++;
		if (m_Timer >= 20)
		{
			Uninit();
			CObject::SetDeath();
		}
	}
	CBlock::Update();
}

//==============================================
// 更新処理
//==============================================
void CBlockGoal::Update()
{
	CBlock::Update();
}

//==============================================
// 描画処理
//==============================================
void CBlock::Draw()
{
	CObjectX::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockNeedle::Draw()
{
	CBlock::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockButton::Draw()
{
	CBlock::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockDoor::Draw()
{
	CBlock::Draw();
}

//==============================================
// 描画処理
//==============================================
void CBlockGoal::Draw()
{
	CBlock::Draw();
}

//==============================================
// ボタンとプレイヤーの当たり判定
//==============================================
bool CBlockButton::IsCollisionPlayer(CPlayer* player)
{
	D3DXVECTOR3 playerPos = player->GetPos();        // プレイヤーのワールド座標
	D3DXVECTOR3 buttonPos = GetPos();                // ボタンのワールド座標

	//// パーティクルマネージャーのインスタンスを取得
	//CParticleManager* pParticleManager = CManager::GetParticleManager();

	//// パーティクルを発生させる
	//pParticleManager->EmitParticles(buttonPos, 50, 2.0f, 1.5f, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	// プレイヤーとボタンの相対位置を計算
	D3DXVECTOR3 relativePos = playerPos - buttonPos;

	// ボタンの回転行列を作成（逆回転）
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(-m_fRotation));  // 逆回転でローカル座標に戻す

	// 相対位置をボタンのローカル座標系に変換
	D3DXVECTOR3 transformedPos;
	D3DXVec3TransformCoord(&transformedPos, &relativePos, &matRotationZ);

	// ボタンのサイズを取得
	D3DXVECTOR3 buttonSize = GetSize();

	// オフセット値の設定（X軸とZ軸は小さめ、Y軸はそのまま）
	const float offsetXZ = 10.0;  // X軸とZ軸のオフセット値（当たり判定を縮小）
	const float offsetY = 20.0f;   // Y軸のオフセット（必要なら微調整）

	// 変換後の座標を使って当たり判定を行う
	bool isOnTop = (transformedPos.y > 0.0f + offsetY && transformedPos.y < buttonSize.y - offsetY);

	// X軸とZ軸の範囲内にいるかを判定（オフセットを適用）
	return (transformedPos.x > -buttonSize.x + offsetXZ &&
		transformedPos.x < buttonSize.x - offsetXZ &&
		transformedPos.z > -buttonSize.z + offsetXZ &&
		transformedPos.z < buttonSize.z - offsetXZ &&
		isOnTop);
}

//==============================================
// ボタンとクローンの当たり判定
//==============================================
bool CBlockButton::IsCollisionClone(CClone* clone)
{
	D3DXVECTOR3 clonePos = clone->GetPos();        // プレイヤーのワールド座標
	D3DXVECTOR3 buttonPos = GetPos();                // ボタンのワールド座標

	// プレイヤーとボタンの相対位置を計算
	D3DXVECTOR3 relativePos = clonePos - buttonPos;

	// ボタンの回転行列を作成（逆回転）
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(-m_fRotation));  // 逆回転でローカル座標に戻す

	// 相対位置をボタンのローカル座標系に変換
	D3DXVECTOR3 transformedPos;
	D3DXVec3TransformCoord(&transformedPos, &relativePos, &matRotationZ);

	// ボタンのサイズを取得
	D3DXVECTOR3 buttonSize = GetSize();

	// オフセット値の設定（X軸とZ軸は小さめ、Y軸はそのまま）
	const float offsetXZ = 20.0;  // X軸とZ軸のオフセット値（当たり判定を縮小）
	const float offsetY = 20.0f;   // Y軸のオフセット（必要なら微調整）

	// 変換後の座標を使って当たり判定を行う
	bool isOnTop = (transformedPos.y > 0.0f + offsetY && transformedPos.y < buttonSize.y - offsetY);

	// X軸とZ軸の範囲内にいるかを判定（オフセットを適用）
	return (transformedPos.x > -buttonSize.x + offsetXZ &&
		transformedPos.x < buttonSize.x - offsetXZ &&
		transformedPos.z > -buttonSize.z + offsetXZ &&
		transformedPos.z < buttonSize.z - offsetXZ &&
		isOnTop);
}

//==============================================
// ブロックのタイプ設定処理
//==============================================
void CBlock::SetBlockType(BLOCK BlockType)
{
	m_BlockType = BlockType;
}

//==============================================
// ブロックのタイプ取得処理
//==============================================
CBlock::BLOCK CBlock::GetBlockType()
{
	return m_BlockType;
}

//=====================================================
// モデルの生成
//=====================================================
CBlock* CBlock::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlock* pBlock = new CBlock();

	if (pBlock != nullptr)
	{
		pBlock->SetBlockType(nType);
		pBlock->Init();
		pBlock->SetPos(pos);
		pBlock->SetUseDeath(true);
	}
	return  pBlock;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockNeedle* CBlockNeedle::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockNeedle* pBlockNeedle = new CBlockNeedle();

	if (pBlockNeedle != nullptr)
	{
		pBlockNeedle->SetBlockType(nType);
		pBlockNeedle->Init();
		pBlockNeedle->SetPos(pos);
		pBlockNeedle->SetUseDeath(true);
	}
	return  pBlockNeedle;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockButton* CBlockButton::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockButton* pBlockButton = new CBlockButton();

	if (pBlockButton != nullptr)
	{
		pBlockButton->SetBlockType(nType);
		pBlockButton->Init();
		pBlockButton->SetPos(pos);
		pBlockButton->SetUseDeath(true);
	}
	return  pBlockButton;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockDoor* CBlockDoor::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockDoor* pBlockDoor = new CBlockDoor();

	if (pBlockDoor != nullptr)
	{
		pBlockDoor->SetBlockType(nType);
		pBlockDoor->Init();
		pBlockDoor->SetPos(pos);
		pBlockDoor->SetUseDeath(true);
	}
	return  pBlockDoor;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockGoal* CBlockGoal::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockGoal* pBlockGial = new CBlockGoal();

	if (pBlockGial != nullptr)
	{
		pBlockGial->SetBlockType(nType);
		pBlockGial->Init();
		pBlockGial->SetPos(pos);
		pBlockGial->SetUseDeath(true);
	}
	return  pBlockGial;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlock::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockNeedle::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockButton::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockDoor::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBlockGoal::SetDeath()
{
	CObject::SetDeath();
}

//==============================================
// 扉の状態取得処理
//==============================================
bool& CBlockButton::GetOpenDoor()
{
	return m_bOpen;
}

//==============================================
// ボタンのマテリアルカラー変更処理
//==============================================
void CBlockButton::SetMatColor(D3DMATERIAL9* pMat, int nMatIdx)
{
	pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 1.0f;

	if (m_bOpen == true)
	{
		if (nMatIdx == 2)
		{
			pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 0.5f;
		}
	}
	else if(m_bOpen == false)
	{
		if (nMatIdx == 2)
		{
			pMat->Diffuse.g = pMat->Diffuse.b = 0.0f;
		}
	}
}