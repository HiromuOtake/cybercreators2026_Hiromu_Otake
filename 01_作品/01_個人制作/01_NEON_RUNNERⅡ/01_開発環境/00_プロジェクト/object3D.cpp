//======================================================
//
// 3D�X�N���[���A�N�V���� [object2D.cpp]
// Auther : ��|�
//
//======================================================

#include "object3D.h"
#include "manager.h"

//======================================================
// �R���X�g���N�^
//======================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority), m_pVtxBuff(nullptr), m_pTexture(nullptr), m_pos{ 0.0f,0.0f,0.0f }, m_rot{ 0.0f,0.0f,0.0f }
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CObject3D::~CObject3D()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CObject3D::Init()
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	CRenderer* pRenderer = CManager::GetRenderere();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\Texture\\sss.jpg",
		&m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx;				//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-1000.0, 0.0f, 1000.0);
	pVtx[1].pos = D3DXVECTOR3(1000.0, 0.0f, 1000.0);
	pVtx[2].pos = D3DXVECTOR3(-1000.0, 0.0f, -1000.0);
	pVtx[3].pos = D3DXVECTOR3(1000.0, 0.0f, -1000.0);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//======================================================
// �X�V����
//======================================================
void CObject3D::Update()
{

}

//======================================================
// �`�揈��
//======================================================
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	CRenderer* pRenderer = CManager::GetRenderere();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//======================================================
// �e�N�X�`������
//======================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
