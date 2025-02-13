//==============================================
//
//ALTER_EGO[player.h]
//Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"
#include "modelparts.h"
#include "character.h"
#include "collision.h"

class CClone : public CCharacter
{
public:
	typedef enum
	{
		PLAYER_NONE = 0,
		PLAYER_NORMAL,
		PLAYER_DEATH,
		PLAYER_MAX,
	}TYPE;
	CClone(int nPriority = 3);
	~CClone()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	bool CollisionUPDOWN(bool& bIsLanding, CObject* pObj);					// �����蔻��㉺
	void CollisionLEFTRIGHT(CObject* pObj);									// �����蔻�荶�E
	static bool& GetGoal() { return m_bUse; }								// �S�[�����̎擾
	void SetStopClone(bool bStopClone) { m_bStopClone = bStopClone; }		// �N���[���̓���ON/OFF�X�C�b�`
	static CClone* Create(D3DXVECTOR3 pos);									// �N���[���̐���
	static const int m_CLONE_LIFE = 1;										// �N���[���̗̑�
	static const int m_DEATH_COUNT = 30;									// �N���[������������܂ł̎���
	static const int m_RESET_CLONE_POS_X = 200;								// �N���[���𕜊�������ꏊ(X���W)
	static const int m_RESET_CLONE_POS_Y = -1200;							// �N���[���𕜊�������ꏊ(Y���W)
	static constexpr float m_CLONE_SHOT_POS = 20.0f;						// �N���[�����e���o���ʒu�̕␳
	static constexpr float m_CLONE_SHOT_MOVE = 15.0f;						// �N���[���̒e�̑��x
	static constexpr float m_CLONE_ROTATION_SPEED = 0.15f;					// �N���[���̉�]�̑���
	static constexpr float m_CLONE_JUMP = 22.5f;							// �N���[���̃W�����v��
	static constexpr float m_CLONE_SPEED = 1.0f;							// �N���[���̃X�s�[�h
	static constexpr float m_LEFTRIGHT = 0.5f;
	void SetDeath()override;
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_size;
	int m_nTextureIdx;
	bool m_bLanding;
	bool m_bJumping;
	bool m_bStopClone;
	static bool m_bUse;
	static bool m_bhalfwaypoint;
	int m_nJumpCnt;
	int m_nModelIdx;
	int m_nLife;
	int m_nType;
	int m_nDeathTimer;
	CInputKeyboard* m_Keyboard;
	CInputJoyPad* m_JoyPad;
	CModelParts* m_pModelParts[15];
	CCollision* m_pCollision;
};

#pragma once