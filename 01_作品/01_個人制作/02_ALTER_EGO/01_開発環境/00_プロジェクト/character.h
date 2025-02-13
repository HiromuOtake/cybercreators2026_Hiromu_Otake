//==============================================
//
//ALTER_EGO[character.h]
//Author: hiromu otake
//
//==============================================

#include "object.h"
#include "modelparts.h"

class CCharacter : public CObjectX
{
public:
	static const int m_NUM_MOTION = 6;
	static const int m_NUM_MODEL_PARTS = 10;
	static const int m_MAX_LETTER = 496;
	typedef enum
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ACTION,
		MOTION_JUMP,
		MOTION_RANDING,
		MOTION_NONE,
		MOTION_MAX
	}MOTION;

	//==============================================
	//キーの構造体
	//==============================================
	typedef struct
	{
		D3DXVECTOR3 pos;							 // モーションの位置
		D3DXVECTOR3 rot;							 // モーションの移動量
	}KEY;

	//==============================================
	//キーセットの構造体
	//==============================================
	typedef struct
	{
		float nFlame;					// モーションが動く時間
		KEY aKey[m_NUM_MODEL_PARTS];
	}KEYSET;

	//==============================================
	//モーションセットの構造体
	//==============================================
	typedef struct
	{
		int nLoop;					// モーションがループするかどうか
		int NumKey;					// モーションのキーがいくつあるか
		KEYSET aKeySet[m_NUM_MOTION];	// モーションの数
	}MOTIONSET;

	CCharacter(int nPriority = 3);
	~CCharacter()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void LoadCharacterSet(FILE* pFile);
	void LoadPartsSet(FILE* pFile, int* nCntModel);
	void LoadMotion(int* nCntMotion);
	void LoadMotionSet(FILE* pFile, int nCntMotion);
	void LoadKeySet(FILE* pFile, int nCntMotion, int nCntKeySet);
	void LoadKey(FILE* pFile, int nCntMotion, int nCntKeySet, int nCntKey);
	void LoadSkip(FILE* pFile);
	void SetMotion(MOTION motion);
	void PlayerMotion();
	char* GetFileName();
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3& GetPosOld();
	D3DXVECTOR3& GetRot();
	CModelParts* GetModelParts(int idx);
private:
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_rot;
	int m_nLife;
	int m_nFlameCnt;
	int m_nKeyCount;
	char* m_aFilename[m_MAX_LETTER][m_NUM_MODEL_PARTS];
	MOTION m_pMotion;
	MOTIONSET m_pMotionSet[m_NUM_MOTION];
	CModelParts* m_pModelParts[m_NUM_MODEL_PARTS];
};

#pragma once
