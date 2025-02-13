//==============================================
//
// ALTER_EGO[camera.h]
// Author: hiromu otake
//
//==============================================

#ifndef  _CAMERA_H_
#define  _CAMERA_H_

#include "manager.h"
#include "object.h"

class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();									// カメラの設定
	void SetShake(int nShakeTime, float fShakePower);	// 揺れの設定
	static D3DXVECTOR3* GetRot();
	static CCamera* Create();
	static constexpr float m_CAMERAPOS_X = 950.0f;
	static constexpr float m_CAMERAPOS_Y = 550.0f;
	static constexpr float m_CAMERAPOS_Z = 100.0f;
	static constexpr float m_CORRECTIOM_WIDTH = 1.564f;
	static constexpr float m_CORRECTIOM_HEIGHT = 1.67f;
	//static constexpr float m_CAMERAPOS_X = 850.0f;
	//static constexpr float m_CAMERAPOS_Y = 450.0f;
	//static constexpr float m_CAMERAPOS_Z = 100.0f;
	//static constexpr float m_CORRECTIOM_WIDTH = 1.405f;
	//static constexpr float m_CORRECTIOM_HEIGHT = 1.39f;
private:
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	static D3DXVECTOR3 m_rot;			//向き
	D3DXMATRIX m_mtxProjection;	// プロジェクション行列
	D3DXMATRIX m_mtxView;		// ビュー行列
	//int m_nShakeTime;
	//float m_fShakePower;
	bool m_bCameraChanger;
	CInputKeyboard* m_Keyboard;
};

#endif
