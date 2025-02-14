//==============================================
//
// ALTER_EGO[game.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "player.h"
#include "camera.h"
#include "item.h"
#include "pause.h"

//#include <unordered_map>
//#include "block.h"

class CGame : public CScene
{
public:
	CGame();							// コンストラクタ
	~CGame()override;					// デストラクタ
	HRESULT Init()override;				// 初期設定
	void Uninit()override;				// 終了処理
	void Update()override;				// 更新処理
	void Draw()override;				// 描画処理
	void CreateObject(int type, const std::string& key, D3DXVECTOR3 position, float rotation);
	static CPlayer* GetPlayer();
	static CCamera* GetCamera();
	bool GetPauseSwitch() { return m_bPauseSwitch; }
	void SetPauseSwitch(bool bPauseSwitch) { m_bPauseSwitch = bPauseSwitch; }
	void SetQuit(bool bQuit) { m_bQuit = bQuit; }
	static const int m_BLOCK_BESIDE = 30;
	static const int m_BLOCK_VERTICAL = 15;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	int m_nType[m_BLOCK_BESIDE][m_BLOCK_VERTICAL];
	bool m_bPauseSwitch;
	bool m_bQuit;
	static CPlayer* m_pPlayer;
	static CCamera* m_pCamera;
	CPause* m_pPause;
};

#pragma once
