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
	static CPause* Create();				// �|�[�Y��ʐ���
	void SetDeath()override;
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