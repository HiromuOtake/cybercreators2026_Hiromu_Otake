//======================================================
//
// ALTER_EGO [manager.h]
// Auther : 大竹熙
//
//======================================================

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "light.h"
#include "object3D.h"
#include "texture.h"
#include "scene.h"
#include "fade.h"
#include "model.h"
#include "sound.h"

// 前方宣言
class CParticleManager;

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer* GetRenderere() { return m_pRnderer; }								// レンダラーの取得
	static CInputKeyboard* GetKeyboard() { return m_pKeyboard; }						// キーボードの取得
	static CInputJoyPad* GetJoyPad() { return m_pJoyPad; }								// ゲームパッドの取得
	static CLight* GetLight() { return m_pLight; }										// ライトの取得
	static CTexture* GetTexture() { return m_pTexture; }								// テクスチャの取得
	static CModel* GetModel() { return m_pModel; }										// モデルの取得
	static CScene* GetScene() { return m_pScene; }										// シーンの取得
	static CSound* GetSound() { return m_pSound; }										// サウンドの取得
	static CParticleManager* GetParticleManager() { return m_pParticleManager; }		// パーティクルマネージャーの取得
	static int& GetMode() { return m_nMode; }											// モードの取得
	static void SetNextStage(const char* stageFile) { m_nextStageFile = stageFile; }
	static const char* GetNextStage() { return m_nextStageFile.c_str(); }
	static void SetNextScene(CScene::MODE nextScene) { m_nextSceneMode = nextScene; }
	static CScene::MODE GetNextScene() { return m_nextSceneMode; }
	static void SetMode(CScene::MODE mode);
	static void SetPaused(bool paused) { m_bPaused = paused; }
	static bool IsPaused() { return m_bPaused; }
	static CFade* GetFade();
	static void SetFadeInstance(CFade* fade);
private:
	static CRenderer* m_pRnderer;					// レンダラー情報
	static CInputKeyboard* m_pKeyboard;				// キーボード情報
	static CInputJoyPad* m_pJoyPad;					// ゲームパッド情報
	static CLight* m_pLight;						// ライト情報
	static CTexture* m_pTexture;					// テクスチャ情報
	static CModel* m_pModel;						// モデル情報
	static CScene* m_pScene;						// シーン情報
	static CSound* m_pSound;						// サウンド情報
	static CParticleManager* m_pParticleManager;	// パーティクルマネージャー情報
	static int m_nMode;								// 画面遷移を管理する静的メンバ
	static std::string m_nextStageFile;				// 次のステージファイル名
	static CScene::MODE m_nextSceneMode;			// 次のシーンモード
	static bool m_bPaused;							// ポーズ状態を管理する静的メンバ
	static CFade* m_pFade;
};
#pragma once
