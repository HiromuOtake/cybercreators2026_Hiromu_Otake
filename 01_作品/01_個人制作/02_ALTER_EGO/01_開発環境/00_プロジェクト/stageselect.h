//======================================================
//
// ALTER_EGO [stageselect.h]
// Auther : 大竹熙
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
    static const int m_NUM_STAGE = 5;	// ステージの数
private:
    int m_selectedStage;                // 選択中のステージ番号
    int m_stageTextures[m_NUM_STAGE];   // 各ステージ用のテクスチャ
    int m_bgTexture;                    // 背景用のテクスチャ
    int m_nItemSilhouetteTexIdx;
    int m_ItemTexIdx;
    float m_alpha;
    CInputKeyboard* m_Keyboard;
    CInputJoyPad* m_JoyPad;
    void SelectStage();                 // ステージ選択処理
    CObject2D* m_pObj[m_NUM_STAGE];
    CObject2D* m_pItemTex[m_NUM_STAGE];
};
#endif