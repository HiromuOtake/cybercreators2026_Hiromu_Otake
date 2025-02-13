//==============================================
//
// ALTER_EGO[block.cpp]
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

CBlockButton::BUTTON_COLOR CBlockButton::m_LastPressedButton = CBlockButton::BUTTON_NORMAL;

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
CBlockButton::CBlockButton(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0), m_bOpen(false), m_bColliderActive(false), m_bResetPending(false), m_bPressedOnce(false), m_Color(BUTTON_NORMAL)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockRedButton::CBlockRedButton(int nPriority) : CBlockButton(nPriority), m_Color(BUTTON_RED), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockBlueButton::CBlockBlueButton(int nPriority) : CBlockButton(nPriority), m_Color(BUTTON_BLUE), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockDoor::CBlockDoor(int nPriority, DOOR_COLOR color) : CBlock(nPriority), m_Color(color), m_deleteDoor(1.0f), m_nModelIdx(0), m_nTexIdx(0)
, m_Keyboard(nullptr), m_bOpen(false), m_bColliderActive(true), m_bVisible(true)
{
	m_Timer = 0;
}

//==============================================
// コンストラクタ
//==============================================
CBlockRedDoor::CBlockRedDoor(int nPriority) : CBlockDoor(nPriority), m_color(DOOR_RED), m_nModelIdx(0), m_nTexIdx(0), m_bOpen(false),m_bColliderActive(false)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockBlueDoor::CBlockBlueDoor(int nPriority) : CBlockDoor(nPriority), m_color(DOOR_BLUE), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// コンストラクタ
//==============================================
CBlockGoal::CBlockGoal(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0), m_fGoalRot(0.0f)
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
CBlockRedButton::~CBlockRedButton()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockBlueButton::~CBlockBlueButton()
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
CBlockRedDoor::~CBlockRedDoor()
{

}

//==============================================
// デストラクタ
//==============================================
CBlockBlueDoor::~CBlockBlueDoor()
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
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\neonblock001.png");

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

	m_bOpen = false;				// 初期状態は閉じた状態
	m_bColliderActive = true;		// 初期状態は当たり判定を有効にする
	m_bResetPending = false;
	m_LastPressedButton = BUTTON_NORMAL;
	CObjectX::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockRedButton::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\switch_R.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// 初期状態は閉じた状態
	m_bColliderActive = true;		// 初期状態は当たり判定を有効にする

	CObjectX::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockBlueButton::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\switch_B.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// 初期状態は閉じた状態
	m_bColliderActive = true;		// 初期状態は当たり判定を有効にする

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

	m_bOpen = false;				// 初期状態は閉じた状態
	m_bColliderActive = true;		// 初期状態は当たり判定を有効にする

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	CObjectX::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockRedDoor::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\door_R.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// 初期状態は閉じた状態
	m_bColliderActive = true;		// 初期状態は当たり判定を有効にする

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	CObjectX::Init();

	return S_OK;
}

//==============================================
// 初期設定
//==============================================
HRESULT CBlockBlueDoor::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\door_B.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// 初期状態は閉じた状態
	m_bColliderActive = true;		// 初期状態は当たり判定を有効にする

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
	CSound* pSound = CManager::GetSound();
	D3DXVECTOR3 pos = CBlockButton::GetPos();
	D3DXVECTOR3 buttonPos = GetPos();                // ボタンのワールド座標

	// NORMALボタンがすでに一度押されていた場合は何もしない
	if (m_Color == BUTTON_NORMAL && m_bPressedOnce)
	{
		CBlock::Update();
		return;
	}

	// ボタン押下判定
	bool bPressed = false;

	// プレイヤーやクローンとの衝突判定
	for (const auto& object : CObject::GetAllObjects())
	{
		if (object->GetType() == TYPE_PLAYER)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(object);
			if (player != nullptr && IsCollisionPlayer(player))
			{
				bPressed = true;
				break;
			}
		}
		else if (object->GetType() == TYPE_CLONE)
		{
			CClone* clone = dynamic_cast<CClone*>(object);
			if (clone != nullptr && IsCollisionClone(clone))
			{
				bPressed = true;
				break;
			}
		}
	}

	// ボタンが押された場合の処理
	if (bPressed && !m_bOpen)
	{
		if (m_Color == BUTTON_NORMAL)
		{
			m_bOpen = true;
			m_bPressedOnce = true;  // NORMALボタンが一度押されたことを記録

			// 通常の扉を開く
			for (auto* object : CObject::GetAllObjects())
			{
				if (CBlockDoor* door = dynamic_cast<CBlockDoor*>(object))
				{
					if (door->GetColor() == CBlockDoor::DOOR_NORMAL)
					{
						door->OpenAndClose(true);  // 通常の扉を開く
					}
				}
			}

			// パーティクル発生と効果音
			CParticleManager* pParticleManager = CManager::GetParticleManager();
			pParticleManager->EmitParticles(buttonPos, 40, 1.0f, 3.0f, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_BUTON);
		}
		else
		{
			// 他の色のボタンの場合の処理（赤や青の交互押下制御）
			if ((m_Color == BUTTON_RED && m_LastPressedButton != BUTTON_RED) ||
				(m_Color == BUTTON_BLUE && m_LastPressedButton != BUTTON_BLUE))
			{
				m_bOpen = true;
				m_LastPressedButton = m_Color;  // 最後に押されたボタンを記録
				m_bResetPending = true;  // リセット待ち状態に設定

				// 扉の開閉処理
				for (auto* object : CObject::GetAllObjects())
				{
					if (CBlockDoor* door = dynamic_cast<CBlockDoor*>(object))
					{
						if (m_Color == BUTTON_RED && door->GetColor() == CBlockDoor::DOOR_RED)
						{
							door->OpenAndClose(true);  // 赤い扉を開く
						}
						else if (m_Color == BUTTON_BLUE && door->GetColor() == CBlockDoor::DOOR_BLUE)
						{
							door->OpenAndClose(true);  // 青い扉を開く
						}
						else if (m_Color == BUTTON_RED && door->GetColor() == CBlockDoor::DOOR_BLUE)
						{
							door->OpenAndClose(false);  // 青い扉を閉じる
						}
						else if (m_Color == BUTTON_BLUE && door->GetColor() == CBlockDoor::DOOR_RED)
						{
							door->OpenAndClose(false);  // 赤い扉を閉じる
						}
					}
				}

				// パーティクル発生と効果音
				CParticleManager* pParticleManager = CManager::GetParticleManager();
				pParticleManager->EmitParticles(buttonPos, 40, 1.0f, 3.0f, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
				pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_BUTON);
			}
		}
	}
	// ボタンの状態をリセットする
	if (!bPressed)
	{
		m_bOpen = false;
	}

	CBlock::Update();
}

//==============================================
// 更新処理
//==============================================
void CBlockDoor::Update()
{
	if (!m_bColliderActive)
	{
		return;
	}

	bool bOpenDoor = false;

	// キーの取得
	const std::string& key = GetPairKey();

	// キーが存在する
	if (key != "none")
	{ 
		// キーに対応する全てのオブジェクトに対して処理を行う
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
					bOpenDoor = true;
					break;
				}
			}
			else
			{
				break;
			}
		}
	}

	if (bOpenDoor == true)
	{
		//m_deleteDoor--;

		//CBlockDoor::SetScale(D3DXVECTOR3(m_deleteDoor, m_deleteDoor, m_deleteDoor));

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
	m_fGoalRot += 0.01f;
	
	CObjectX::SetRot(D3DXVECTOR3(0.0f, 0.0f, m_fGoalRot));

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
	// 扉が開いている場合は描画しない
	if (!m_bOpen)
	{
		CBlock::Draw();
	}
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
	D3DXVECTOR3 playerPos = player->GetPos();		// プレイヤーのワールド座標
	D3DXVECTOR3 buttonPos = GetPos();				// ボタンのワールド座標

	// プレイヤーとボタンの相対位置を計算
	D3DXVECTOR3 relativePos = playerPos - buttonPos;

	// ボタンの回転行列を作成（逆回転）
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(-m_fRotation));	// 逆回転でローカル座標に戻す

	// 相対位置をボタンのローカル座標系に変換
	D3DXVECTOR3 transformedPos;
	D3DXVec3TransformCoord(&transformedPos, &relativePos, &matRotationZ);

	// ボタンのサイズを取得
	D3DXVECTOR3 buttonSize = GetSize();

	// オフセット値の設定（X軸とZ軸は小さめ、Y軸はそのまま）
	const float offsetXZ = 10.0;	// X軸とZ軸のオフセット値（当たり判定を縮小）
	const float offsetY = 20.0f;	// Y軸のオフセット（必要なら微調整）

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
	D3DXVECTOR3 clonePos = clone->GetPos();			// プレイヤーのワールド座標
	D3DXVECTOR3 buttonPos = GetPos();				// ボタンのワールド座標

	// プレイヤーとボタンの相対位置を計算
	D3DXVECTOR3 relativePos = clonePos - buttonPos;

	// ボタンの回転行列を作成（逆回転）
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(-m_fRotation));	// 逆回転でローカル座標に戻す

	// 相対位置をボタンのローカル座標系に変換
	D3DXVECTOR3 transformedPos;
	D3DXVec3TransformCoord(&transformedPos, &relativePos, &matRotationZ);

	// ボタンのサイズを取得
	D3DXVECTOR3 buttonSize = GetSize();

	// オフセット値の設定（X軸とZ軸は小さめ、Y軸はそのまま）
	const float offsetXZ = 20.0;	// X軸とZ軸のオフセット値（当たり判定を縮小）
	const float offsetY = 20.0f;	// Y軸のオフセット（必要なら微調整）

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
CBlockButton* CBlockButton::Create(D3DXVECTOR3 pos, BLOCK nType, BUTTON_COLOR color)
{
	CBlockButton* pBlockButton = new CBlockButton();

	if (pBlockButton != nullptr)
	{
		pBlockButton->SetBlockType(nType);
		pBlockButton->SetColor(color);  // 色を設定
		pBlockButton->Init();
		pBlockButton->SetPos(pos);
		pBlockButton->SetUseDeath(true);
	}
	return  pBlockButton;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockRedButton* CBlockRedButton::Create(D3DXVECTOR3 pos, BUTTON_COLOR color)
{
	CBlockRedButton* pBlockButton = new CBlockRedButton();
	if (pBlockButton != nullptr)
	{
		pBlockButton->SetBlockType(BLOCK_BUTTON);
		pBlockButton->SetColor(color);  // 色を設定
		pBlockButton->Init();
		pBlockButton->SetPos(pos);
		pBlockButton->SetUseDeath(true);
	}
	return pBlockButton;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockBlueButton* CBlockBlueButton::Create(D3DXVECTOR3 pos, BUTTON_COLOR color)
{
	CBlockBlueButton* pBlockButton = new CBlockBlueButton();
	if (pBlockButton != nullptr)
	{
		pBlockButton->SetBlockType(BLOCK_BUTTON);
		pBlockButton->SetColor(color);  // 色を設定
		pBlockButton->Init();
		pBlockButton->SetPos(pos);
		pBlockButton->SetUseDeath(true);
	}
	return pBlockButton;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockDoor* CBlockDoor::Create(D3DXVECTOR3 pos, BLOCK nType, DOOR_COLOR color)
{
	CBlockDoor* pBlockDoor = new CBlockDoor(3, color);

	if (pBlockDoor != nullptr)
	{
		pBlockDoor->SetBlockType(nType);
		//pBlockDoor->SetColor(color);  // 色を設定
		pBlockDoor->Init();
		pBlockDoor->SetPos(pos);
		pBlockDoor->SetUseDeath(true);
	}
	return  pBlockDoor;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockRedDoor* CBlockRedDoor::Create(D3DXVECTOR3 pos, DOOR_COLOR color)
{
	CBlockRedDoor* pBlockDoor = new CBlockRedDoor();
	if (pBlockDoor != nullptr)
	{
		pBlockDoor->SetBlockType(BLOCK_DOOR);
		pBlockDoor->SetColor(color);  // 色を設定
		pBlockDoor->Init();
		pBlockDoor->SetPos(pos);
		pBlockDoor->SetUseDeath(true);
	}
	return pBlockDoor;
}

//=====================================================
// モデルの生成
//=====================================================
CBlockBlueDoor* CBlockBlueDoor::Create(D3DXVECTOR3 pos, DOOR_COLOR color)
{
	CBlockBlueDoor* pBlockDoor = new CBlockBlueDoor();
	if (pBlockDoor != nullptr)
	{
		pBlockDoor->SetBlockType(BLOCK_DOOR);
		pBlockDoor->SetColor(color);  // 色を設定
		pBlockDoor->Init();
		pBlockDoor->SetPos(pos);
		pBlockDoor->SetUseDeath(true);
	}
	return pBlockDoor;
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
	// マテリアルの見た目の初期化
	if (nMatIdx == 2)
	{
		pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 1.0f;
	}

	// ボタンが押せない状態なら灰色にする
	if ((m_Color == BUTTON_RED && m_LastPressedButton == BUTTON_RED) ||
		(m_Color == BUTTON_BLUE && m_LastPressedButton == BUTTON_BLUE))
	{
		if (nMatIdx == 2)
		{
			pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 0.5f;
		}
		return; // ここで処理を終了し、ボタンの色を灰色に固定する
	}
	else if (GetColor() == CBlockButton::BUTTON_NORMAL)
	{
		if (m_bOpen == true)
		{
			if (nMatIdx == 2)
			{
				pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 0.5f;
			}
			return; // ここで処理を終了し、ボタンの色を灰色に固定する
		}
	}

	// 赤いボタンだったら
	if (GetColor() == CBlockButton::BUTTON_RED)
	{
		if (m_bOpen == false)
		{
			if (nMatIdx == 2)
			{
				pMat->Diffuse.g = pMat->Diffuse.b = 0.0f;
			}
		}
	}
	// 青いボタンだったら
	else if (GetColor() == CBlockButton::BUTTON_BLUE)
	{
		if (m_bOpen == false)
		{
			if (nMatIdx == 2)
			{
				pMat->Diffuse.g = pMat->Diffuse.r = 0.0f;
			}
		}
	}
	// 通常のボタンだったら
	else if(GetColor() == CBlockButton::BUTTON_NORMAL)
	{
		if (m_bOpen == false)
		{
			if (nMatIdx == 2)
			{
				pMat->Diffuse.g = pMat->Diffuse.b = 0.0f;
			}
		}
	}
}

//=========================================
// 扉の開閉処理
//=========================================
void CBlockDoor::OpenAndClose(bool open)
{
	m_bOpen = open;
	m_bColliderActive = !open;	// 開いたら当たり判定を無効にする
	m_bVisible = !open;			// 扉の表示・非表示を制御する
}