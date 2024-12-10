//==============================================
//
//3D�X�N���[���A�N�V����[player.h]
//Author: hiromu otake
//
//==============================================

#ifndef _CLONECIRCLE_H_
#define _CLONECIRCLE_H_

#include "object3D.h"
#include "input.h"
#include <d3dx9.h>
#include <vector>

// ���_�t�H�[�}�b�g���`���邽�߂̍\����
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position;  // ���_�̈ʒu
    D3DXVECTOR2 texCoord;  // �e�N�X�`�����W
};

// ���_�t�H�[�}�b�g�̒�`
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)

class CCloneCircle : public CObject3D
{
public:
    CCloneCircle(int nPriority = 9);
    ~CCloneCircle();

    HRESULT Init();             // ������
    void Uninit();              // �I������
    void Update();              // �X�V����
    void Draw();                // �`�揈��

    static CCloneCircle* Create(D3DXVECTOR3 pos);
    void SetPlayerPos(D3DXVECTOR3 pos); // �v���C���[�ʒu�ݒ�
    void SetSelectedIndex(int index);   // �I���ʒu�ݒ�
    D3DXVECTOR3 GetSelectedPosition();
    void Activate();
    void SetDeath()override;
private:
    void DrawTexture(LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR3 position, D3DXVECTOR2 scale);

    LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
    D3DXVECTOR3 m_pos;
    int m_nCircleTexture;
    int m_nNormalTexture;
    int m_nSelectTexture;
    int m_nSelectedIndex;
    bool m_bUseDeath;
    static constexpr float m_RADIUS = 200.0f;
    CInputKeyboard* m_Keyboard;
};
#endif // _CLONECIRCLE_H_