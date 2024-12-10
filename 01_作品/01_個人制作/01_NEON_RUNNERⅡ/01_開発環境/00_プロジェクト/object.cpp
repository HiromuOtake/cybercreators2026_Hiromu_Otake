//======================================================
//
// 3D�X�N���[���A�N�V���� [object.cpp]
// Auther : ��|�
//
//======================================================

#include "object.h"

// �ÓI�����o������
int CObject::m_nNumAll = 0;
//CObject* CObject::m_apObject[m_MAXPRIORITY][m_MAXOBJECT] = {};
CObject* CObject::m_pTop[m_MAXPRIORITY] = {};
CObject* CObject::m_pCur[m_MAXPRIORITY] = {};

// �ÓI�I�u�W�F�N�g
std::unordered_map<std::string, std::vector<CObject*>> CObject::m_pair;

//======================================================
// �R���X�g���N�^ (�������g�̓o�^)
//======================================================
CObject::CObject(int nPriority) : m_nPriority(0), m_Type(TYPE_NONE), m_Death(false),m_bUseDeath(false)
{
	m_nPriority = nPriority;

	m_nNumAll++;							// �������J�E���g�A�b�v

	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = this;					// �I�u�W�F�N�g(���g)�����X�g�ɒǉ�
		m_pCur[nPriority] = this;					// �I�u�W�F�N�g(���g)�����X�g�ɒǉ�
		m_pPrev = nullptr;							// ��ԍŏ��̃I�u�W�F�N�g�Ȃ̂őO����������
		m_pNext = nullptr;							// ��ԍŏ��̃I�u�W�F�N�g�Ȃ̂őO����������
	}
	else
	{
		m_pNext = nullptr;							// ��ԍŐV�̃I�u�W�F�N�g�Ȃ̂Ŏ��͖���
		CObject* pCur = m_pCur[nPriority];
		pCur->SetNext(this);
		m_pPrev = pCur;								// �J�����g���X�V����O�Ƀv���r���[�ɏ���n��
		m_pCur[nPriority] = this;					// �������ŐV�Ȃ̂Ŏ����̏��������
	}
}

//======================================================
// �f�X�g���N�^
//======================================================
CObject::~CObject()
{

}

//======================================================
// �S�I�u�W�F�N�g���
//======================================================
void CObject::ReleaseAll()
{
	m_pair.clear();

	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->SetDeath();
			pObj = pNext;
		}
	}

	//for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	//{
	//	CObject* pObj = m_pTop[nCnt];		// �擪�擾

	//	// �ő吔���s���Ȃ̂�While���g�p
	//	while (pObj != nullptr)
	//	{
	//		CObject* pNext = pObj->m_pNext;
	//		if (pObj->m_Death == true)
	//		{
	//			pObj->Uninit();
	//			pObj->Release();
	//			pObj = nullptr;

	//		}
	//		pObj = pNext;
	//	}
	//}

	//for (int nCntPriority = 0; nCntPriority < m_MAXPRIORITY; nCntPriority++)
	//{
	//	for (int nCnt = 0; nCnt < m_MAXOBJECT; nCnt++)
	//	{
	//
	//		if (m_apObject[nCntPriority][nCnt] != nullptr)
	//		{
	//			m_apObject[nCntPriority][nCnt]->Uninit();
	//		}
	//	}
	//}
}

//======================================================
// �S�I�u�W�F�N�g�X�V
//======================================================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];		// �擪�擾
	
		// �ő吔���s���Ȃ̂�While���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Update();
			pObj = pNext;
		}
	}

	DeleateProcess();

	//for (int nCntPriority = 0; nCntPriority < m_MAXPRIORITY; nCntPriority++)
	//{
	//	for (int nCnt = 0; nCnt < m_MAXOBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPriority][nCnt] != nullptr)
	//		{
	//			m_apObject[nCntPriority][nCnt]->Update();
	//		}
	//	}
	//}
}

//======================================================
// �S�I�u�W�F�N�g�`��
//======================================================
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];
	
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Draw();
			pObj = pNext;
		}
	}

	//for (int nCntPriority = 0; nCntPriority < m_MAXPRIORITY; nCntPriority++)
	//{
	//	for (int nCnt = 0; nCnt < m_MAXOBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPriority][nCnt] != nullptr)
	//		{
	//			m_apObject[nCntPriority][nCnt]->Draw();
	//		}
	//	}
	//}
}

//======================================================
// �������g�̉��
//======================================================
void CObject::Release()
{
	m_nNumAll--;	// �������J�E���g�_�E��
	
	if (m_Type == TYPE_BG)
	{

		int n = 0;
	}

	if (m_pPrev != nullptr)
	{
		m_pPrev->m_pNext = m_pNext;
	}
	else
	{
		m_pTop[m_nPriority] = m_pNext;
	}

	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;
	}
	else
	{
		m_pCur[m_nPriority] = m_pPrev;
	}
	
	delete this;
}

//======================================================
// ���S�t���O�̐ݒ�
//======================================================
void CObject::SetDeath()
{
	if (m_bUseDeath == true)
	{
		m_Death = true;
	}
}

//======================================================
// ���S�t���O���g�p���邩�ǂ���
//======================================================
void CObject::SetUseDeath(bool bUseDeath)
{
	m_bUseDeath = bUseDeath;
}

//======================================================
// ���S�t���O��������
//======================================================
void CObject::DeleateProcess()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];		// �擪�擾

		// �ő吔���s���Ȃ̂�While���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			if (pObj->m_Death == true)
			{
				pObj->Uninit();
				pObj->Release();
			}
			pObj = pNext;
		}
	}
}

//======================================================
// �^�C�v�̐ݒ�
//======================================================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}

//======================================================
// �^�C�v�̎擾
//======================================================
CObject::TYPE CObject::GetType()
{
	return m_Type;
}

////======================================================
//// �I�u�W�F�N�g�̎擾
////======================================================
//CObject* CObject::GETObject(int nPrio,int nObj)
//{
//	return m_apObject[nPrio][nObj];
//}

//======================================================
// �I�u�W�F�N�g�̎擾
//======================================================
CObject* CObject::GetTop(int nPrio)
{
	return m_pTop[nPrio];
}

//======================================================
// ���̃I�u�W�F�N�g�̐ݒ�
//======================================================
void CObject::SetNext(CObject* pObject)
{
	m_pNext = pObject;
}

//======================================================
// ���̃I�u�W�F�N�g�̎擾
//======================================================
CObject* CObject::GetNext()
{
	return m_pNext;
}