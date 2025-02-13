//======================================================
//
// ALTER_EGO [stageselect.h]
// Auther : ��|�
//
//======================================================

#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "scene.h"
#include "bg.h"
#include <vector>
#include <string>

class CStageSelect : public CScene
{
public:
    CStageSelect();
    ~CStageSelect();
    HRESULT Init() override;
    void Uninit() override;
    void Update() override;
    void Draw() override;
    static const int m_NUM_STAGE = 5;	// �X�e�[�W�̐�
private:
    int m_selectedStage;                // �I�𒆂̃X�e�[�W�ԍ�
    int m_stageTextures[m_NUM_STAGE];   // �e�X�e�[�W�p�̃e�N�X�`��
    int m_bgTexture;                    // �w�i�p�̃e�N�X�`��
    int m_nItemSilhouetteTexIdx;
    int m_ItemTexIdx;
    float m_alpha;
    CInputKeyboard* m_Keyboard;
    CInputJoyPad* m_JoyPad;
    void SelectStage();                 // �X�e�[�W�I������
    CObject2D* m_pObj[m_NUM_STAGE];
    CObject2D* m_pItemTex[m_NUM_STAGE];
};
#endif