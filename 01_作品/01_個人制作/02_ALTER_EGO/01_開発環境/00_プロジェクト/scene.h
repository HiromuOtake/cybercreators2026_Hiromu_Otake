//==============================================
//
// ALTER_EGO[scene.h]
// Author: hiromu otake
//
//==============================================

#include "main.h"

class CScene
{
public:
	// ��ʂ̎��
	enum MODE
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_STAGESELECT,
		MODE_TUTORIAL1,
		MODE_TUTORIAL2,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	};
	CScene();							// �R���X�g���N�^
	virtual ~CScene();					// �f�X�g���N�^
	virtual HRESULT Init();				// �����ݒ�
	virtual void Uninit();				// �I������
	virtual void Update();				// �X�V����
	virtual void Draw();				// �`�揈��
	static CScene* Create(MODE mode);	// ����
	MODE GetMode();
private:
	MODE m_Mode;						// ���݂̃��[�h
};

#pragma once
