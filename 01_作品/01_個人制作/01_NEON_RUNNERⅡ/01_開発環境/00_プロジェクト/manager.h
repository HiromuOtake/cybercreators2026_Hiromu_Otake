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
	static int& GetMode();
	//static CFade* GetFade();
	static void SetMode(CScene::MODE mode);
private:
	static CRenderer* m_pRnderer;
	static CInputKeyboard* m_pKeyboard;
	static CInputJoyPad* m_pJoyPad;
	static CLight* m_pLight;				// ライト情報
	static CTexture* m_pTexture;
	static CModel* m_pModel;
	static CScene* m_pScene;
	static CSound* m_pSound;
	static int m_nMode;
	//static CFade* m_pFade;
};
#pragma once
