//==============================================
//
// 3Dスクロールアクション[camera.h]
// Author: hiromu otake
//
//==============================================

#ifndef  _CAMERA_H_
#define  _CAMERA_H_

#include "manager.h"
#include "object.h"

// マクロ定義
#define AMOUNT_CAMERA_LENGTH		(400.0f)

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
private:
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	static D3DXVECTOR3 m_rot;			//向き
	D3DXMATRIX m_mtxProjection;	// プロジェクション行列
	D3DXMATRIX m_mtxView;		// ビュー行列
	//int m_nShakeTime;
	//float m_fShakePower;
	CInputKeyboard* m_Keyboard;
};

#endif
