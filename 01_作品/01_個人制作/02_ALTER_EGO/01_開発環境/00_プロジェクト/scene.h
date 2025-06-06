//==============================================
//
// ALTER_EGO[scene.h]
// Author: hiromu otake
//
//==============================================

#include "main.h"

class CScene
{
public:
	// 画面の種類
	enum MODE
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_STAGESELECT,
		MODE_TUTORIAL1,
		MODE_TUTORIAL2,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	};
	CScene();							// コンストラクタ
	virtual ~CScene();					// デストラクタ
	virtual HRESULT Init();				// 初期設定
	virtual void Uninit();				// 終了処理
	virtual void Update();				// 更新処理
	virtual void Draw();				// 描画処理
	static CScene* Create(MODE mode);	// 生成
	MODE GetMode();
private:
	MODE m_Mode;						// 現在のモード
};

#pragma once
