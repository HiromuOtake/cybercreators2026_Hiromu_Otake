//==============================================
//
// ALTER_EGO[pause.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "object2D.h"

class CGame;

class CPause : public CObject2D
{
public:
	CPause(int nPriority = 0);
	~CPause();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SelectPause(CGame* game);
	static CPause* Create();							// �|�[�Y��ʐ���
	void SetDeath()override;
	static const int m_MAX_PAUSE = 3;
	static constexpr float m_PAUSE_UI_WIDTH = 400.0f;	// �|�[�YUI�̃T�C�Y(��)
	static constexpr float m_PAUSE_UI_HEIGHT = 60.0f;	// �|�[�YUI�̃T�C�Y(�c)
	static constexpr float m_INITIAL_POINT = 300.0f;	// �|�[�YUI�̏����ʒu
	static constexpr float m_SHIFT = 75.0f;				// �|�[�YUI�����炷
	static constexpr float m_PAUSE_BG_Z = 1.0f;			// �|�[�YBG��Z�̈ʒu
	static constexpr float m_PAUSE_CORRECTION = 0.75f;	// �|�[�Y�̈ʒu�̕␳
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	CInputKeyboard* m_Keyboard;
	CInputJoyPad* m_JoyPad;
	CObject2D* m_pPauseOptions[3];			// �e�|�[�Y�I�v�V������CObject2D�I�u�W�F�N�g
	CObject2D* m_nTexIdx;					// �e�N�X�`��ID
	CObject2D* m_nPauseBGTex;				// �|�[�Y�̔w�i�p�e�N�X�`��
	int m_nSelectPause;						// �I�𒆂̃|�[�Y���j���[�ԍ�
};

#pragma once