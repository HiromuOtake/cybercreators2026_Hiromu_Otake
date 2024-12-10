//==============================================
//
// 3D�X�N���[���A�N�V����[objectX.cpp]
// Author: hiromu otake
//
//==============================================

#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "block.h"


 //==============================================
// �R���X�g���N�^
//==============================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority), m_pos{ 0.0f,0.0f,0.0f }, m_posold{ 0.0f,0.0f,0.0f }, m_rot{ 0.0f,0.0f,0.0f }, m_move{ 0.0f,0.0f,0.0f },
m_min{ 0.0f,0.0f,0.0f },m_max{ 0.0f,0.0f,0.0f }, m_size{0.0f,0.0f,0.0f}, m_pMesh(nullptr), m_dwNumMat(NULL), m_pBuffMat(nullptr), m_pTexture(nullptr), m_nNumVtx(0), m_pVtxBuff(nullptr), m_sizeFVF(0)
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CObjectX::~CObjectX()
{

}

//==============================================
// �����ݒ�
//==============================================
HRESULT CObjectX::Init()
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	CRenderer* pRenderer = CManager::GetRenderere();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_���̎擾
	m_nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;

		if (vtx.x < m_min.x)
		{
			m_min.x = vtx.x;
		}
		else if (vtx.x > m_max.x)
		{
			m_max.x = vtx.x;
		}

		if (vtx.y < m_min.y)
		{
			m_min.y = vtx.y;
		}
		else if (vtx.y > m_max.y)
		{
			m_max.y = vtx.y;
		}

		if (vtx.z < m_min.z)
		{
			m_min.z = vtx.z;
		}
		else if (vtx.z > m_max.z)
		{
			m_max.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���̃|�C���^��i�߂�
		m_pVtxBuff += m_sizeFVF;
	}

	m_size = m_max - m_min;

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//==============================================
// �I������
//==============================================
void CObjectX::Uninit()
{

}

//==============================================
// �X�V����
//==============================================
void CObjectX::Update()
{

}

//==============================================
// �`�揈��
//==============================================
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�ւ̃|�C���^
	CRenderer* pRenderer = CManager::GetRenderere();
	pDevice = pRenderer->GetDevice();					//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;								//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;									//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);

	//LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�ւ̃|�C���^
	//CRenderer* pRenderer = CManager::GetRenderere();
	//pDevice = pRenderer->GetDevice();					//�f�o�C�X�̎擾
	//
	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	//
	//D3DXMATRIX mtxRot, mtxTrans, mtxScale;						//�v�Z�p�}�g���b�N�X
	//D3DMATERIAL9 matDef;								//���݂̃}�e���A���ۑ��p
	//D3DXMATERIAL* pMat;									//�}�e���A���f�[�^�ւ̃|�C���^
	//
	//D3DXMATRIX& matrix = GetMatrix();
	//D3DXVECTOR3& rot = GetRot();
	//D3DXVECTOR3& pos = GetPos();
	//
	////���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&matrix);
	//
	//static constexpr float SCALE = 1.0f;
	//
	//// �X�P�[���𔽉f
	//D3DXMatrixScaling(&mtxScale, SCALE, SCALE, SCALE);
	//D3DXMatrixMultiply(&matrix, &matrix, &mtxScale);
	//
	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

////==============================================
//// ���f���̈ꊇ�Ǘ�
////==============================================
//void CObjectX::ModelPath(std::string sPath)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^
//	D3DXMATERIAL* pMat;														//�}�e���A���f�[�^�ւ̃|�C���^
//
//	//X�t�@�C���̓ǂݍ���
//	D3DXLoadMeshFromX(sPath.c_str(),
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&m_pBuffMat,
//		NULL,
//		&m_dwNumMat,
//		&m_pMesh);
//
//	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//	for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
//	{
//		if (pMat[nCnt].pTextureFilename != nullptr)
//		{
//			//�e�N�X�`���̓ǂݍ���
//			D3DXCreateTextureFromFile(pDevice,
//				pMat[nCnt].pTextureFilename,
//				&m_pTexture[nCnt]);
//		}
//	}
//}

////======================================================
//// �e�N�X�`������
////======================================================
//void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
//{
//	m_pTexture = pTex;
//}

//======================================================
// �e�N�X�`������
//======================================================
void CObjectX::BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh, LPDIRECT3DTEXTURE9* Texture)
{
	m_pBuffMat = BuffMat;
	m_dwNumMat = dwNumMat;
	m_pMesh = Mesh;
	m_pTexture = Texture;
}

//======================================================
// �ʒu�̎擾
//======================================================
D3DXVECTOR3& CObjectX::GetPos()
{
	return m_pos;
}

//======================================================
// �ߋ��̈ʒu�̎擾
//======================================================
D3DXVECTOR3& CObjectX::GetPosOld()
{
	return m_posold;
}

//======================================================
// �����̎擾
//======================================================
D3DXVECTOR3& CObjectX::GetRot()
{
	return m_rot;
}

//======================================================
// �ړ��̎擾
//======================================================
D3DXVECTOR3& CObjectX::GetMove()
{
	return m_move;
}

//======================================================
// �傫���̎擾
//======================================================
D3DXVECTOR3& CObjectX::GetSize()
{
	return m_size;
}

//======================================================
// �ŏ��̎擾
//======================================================
D3DXVECTOR3& CObjectX::GetMin()
{
	return m_min;
}

//======================================================
// �ő�̎擾
//======================================================
D3DXVECTOR3& CObjectX::GetMax()
{
	return m_max;
}