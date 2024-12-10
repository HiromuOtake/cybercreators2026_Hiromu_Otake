//==============================================
//
// 3Dスクロールアクション[tutorial.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "player.h"
#include "camera.h"
#include "item.h"

class CTutorial : public CScene
{
public:
	// 画面の種類
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;
	CTutorial();							// コンストラクタ
	~CTutorial()override;					// デストラクタ
	HRESULT Init()override;				// 初期設定
	void Uninit()override;				// 終了処理
	void Update()override;				// 更新処理
	void Draw()override;				// 描画処理
	static CPlayer* GetPlayer();
	static CCamera* GetCamera();
	static const int m_BLOCK_BESIDE = 30;
	static const int m_BLOCK_VERTICAL = 15;
private:
	static CPlayer* m_pPlayer;
	static CItem* m_pItem;
	static CCamera* m_pCamera;
	int m_nType[m_BLOCK_BESIDE][m_BLOCK_VERTICAL];
};

#pragma once
