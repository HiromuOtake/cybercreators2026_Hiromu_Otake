//==============================================
//
//ALTER_EGO[player.h]
//Author: hiromu otake
//
//==============================================

#ifndef _CLONECIRCLE_H_
#define _CLONECIRCLE_H_

#include "object3D.h"
#include "input.h"

class CCloneCircle : public CObject3D
{
public:
    CCloneCircle(int nPriority = 9);
    ~CCloneCircle();

    HRESULT Init();             // 初期化
    void Uninit();              // 終了処理
    void Update();              // 更新処理
    void Draw();                // 描画処理

    static CCloneCircle* Create(D3DXVECTOR3 pos);
    void SetPlayerPos(D3DXVECTOR3 pos); // プレイヤー位置設定
    void SetSelectedIndex(int index);   // 選択位置設定
    D3DXVECTOR3 GetSelectedPosition();
    void Activate();
    void SetDeath()override;
    static const int m_ERROR = 1;
    static const int m_MAX_POSITION = 4;
    static const int m_NUM_SILHOUETTE = 4;
    static constexpr float m_INITIAL_VTX = 75.0f;
    static constexpr float m_CIRCLE_SCALE = 3.5f;
    static constexpr float m_CIRCLE_RADIUS = 250.0f;
private:
    void DrawTexture(LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR3 position, D3DXVECTOR2 scale);

    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
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