//======================================================
//
// 3Dスクロールアクション [manager.h]
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
//class CParticleManager;

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer* GetRenderere();
	static CInputKeyboard* GetKeyboard();
	static CInputJoyPad* GetJoyPad();
	static CLight* GetLight();
	static CTexture* GetTexture();
	static CModel* GetModel();
	static CScene* GetScene();
	static CSound* GetSound();
	//static CParticleManager* GetParticleManager();
	static int& GetMode();
	//static CFade* GetFade();
	static void SetMode(CScene::MODE mode);
	static void SetPaused(bool paused) { m_bPaused = paused; }
	static bool IsPaused() { return m_bPaused; }
private:
	static CRenderer* m_pRnderer;
	static CInputKeyboard* m_pKeyboard;
	static CInputJoyPad* m_pJoyPad;
	static CLight* m_pLight;				// ライト情報
	static CTexture* m_pTexture;
	static CModel* m_pModel;
	static CScene* m_pScene;
	static CSound* m_pSound;
	//static CParticleManager* m_pParticleManager;
	static int m_nMode;
	static bool m_bPaused; // ポーズ状態を管理する静的メンバ
	//static CFade* m_pFade;
};
#pragma once
