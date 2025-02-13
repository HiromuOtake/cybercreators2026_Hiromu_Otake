////==============================================
////
//// ALTER_EGO[field.h]
//// Author: hiromu otake
////
////==============================================
//
//#ifndef _FIELD_H_
//#define _FIELD_H_
//
//#include "manager.h"
//#include "object3D.h"
//
//// マクロ定義
//#define VTX_L			(100.0f)
//#define VTX_R			(300.0f)
//#define VTX_U			(100.0f)
//#define VTX_V			(400.0f)
//#define MOVE_LATE		(5)
//#define MAX_DEFAURT2nd	(0)				// デフォルト引数
//
//class CField : public CObject3D
//{
//public:
//	CField(int nPriority = MAX_DEFAURT2nd);
//	~CField()override;
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	static CField* Create(D3DXVECTOR3 pos);
//	static HRESULT Load();
//	static void Unload();
//	D3DXVECTOR3& GetPos();
//	void SetDeath()override;
//private:
//	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
//	D3DXVECTOR3 m_pos;						//頂点座標
//};
//
//#endif // !_FIELD_H_
//#pragma once
