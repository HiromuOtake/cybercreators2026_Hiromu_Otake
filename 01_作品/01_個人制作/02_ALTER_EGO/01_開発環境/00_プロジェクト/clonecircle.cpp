//==============================================
//
//ALTER_EGO[clonecircle.h]
//Author: hiromu otake
//
//==============================================

#include "CloneCircle.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include <d3dx9.h>

//==============================================
// コンストラクタ
//==============================================
CCloneCircle::CCloneCircle(int nPriority): CObject3D(nPriority), m_pos{ 0.0f, 0.0f, 0.0f }, m_nSelectedIndex(0),m_nCircleTexture(0), m_nNormalTexture(0), m_nSelectTexture(0)
, m_pVtxBuff(nullptr), m_Keyboard(nullptr), m_bUseDeath(true)
{

}

//==============================================
// デストラクタ
//==============================================
CCloneCircle::~CCloneCircle() 
{

}

//==============================================
// 初期化処理
//==============================================
HRESULT CCloneCircle::Init()
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();

    // 頂点バッファの生成
    pDevice->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4,
        D3DUSAGE_WRITEONLY,
        D3DFVF_CUSTOMVERTEX,
        D3DPOOL_MANAGED, 
        &m_pVtxBuff,
        NULL);

    // テクスチャの読み込み
    m_nCircleTexture = CManager::GetTexture()->Regist("data\\Texture\\clonecircle.png");
    m_nNormalTexture = CManager::GetTexture()->Regist("data\\Texture\\silhouette000.png");
    m_nSelectTexture = CManager::GetTexture()->Regist("data\\Texture\\silhouette001.png");

    if (m_nCircleTexture == -1 || m_nNormalTexture == -1 || m_nSelectTexture == -1)
    {
        return E_FAIL;
    }

    CUSTOMVERTEX* vertices;

    m_pVtxBuff->Lock(0, 0, (void**)&vertices, 0);

    vertices[0] = { D3DXVECTOR3(-75.0f,  75.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f) };
    vertices[1] = { D3DXVECTOR3(75.0f,  75.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f) };
    vertices[2] = { D3DXVECTOR3(-75.0f, -75.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f) };
    vertices[3] = { D3DXVECTOR3(75.0f, -75.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f) };

    m_pVtxBuff->Unlock();

    return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CCloneCircle::Uninit()
{
    if (m_pVtxBuff)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }

    CObject3D::Uninit();
}

//==============================================
// 更新処理
//==============================================
void CCloneCircle::Update()
{
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(CGame::GetPlayer());
    if (pPlayer)
    {
        m_pos = pPlayer->GetPos();
    }
}

//==============================================
// 描画処理
//==============================================
void CCloneCircle::Draw()
{
    if (m_bUseDeath)

    {
        return; // 無効化されていれば描画しない
    }

    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();

    // Zバッファを一時的に無効化
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
    pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

    if (!m_bUseDeath)
    {
        // 円描画
        LPDIRECT3DTEXTURE9 pCircleTex = CManager::GetTexture()->GetAddress(m_nCircleTexture);
        if (pCircleTex)
        {
            DrawTexture(pCircleTex, m_pos, D3DXVECTOR2(3.5f, 3.5f));
        }

        // クローン候補描画
        const float radius = 250.0f;
        D3DXVECTOR3 positions[4] =
        {
            { m_pos.x, m_pos.y + radius, m_pos.z },  // 上
            { m_pos.x, m_pos.y - radius, m_pos.z },  // 下
            { m_pos.x + radius, m_pos.y, m_pos.z },  // 右
            { m_pos.x - radius, m_pos.y, m_pos.z }   // 左
        };

        // クローン描画
        for (int i = 0; i < 4; i++)
        {
            int textureID = (i == m_nSelectedIndex) ? m_nSelectTexture : m_nNormalTexture;
            LPDIRECT3DTEXTURE9 pTexture = CManager::GetTexture()->GetAddress(textureID);
            if (pTexture)
            {
                DrawTexture(pTexture, positions[i], D3DXVECTOR2(0.3f, 0.5f));
            }
        }
    }
    // Zバッファを元に戻す
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//==============================================
// クローンサークルの生成
//==============================================
CCloneCircle* CCloneCircle::Create(D3DXVECTOR3 pos)
{
    CCloneCircle* pCircle = new CCloneCircle();
    if (pCircle != nullptr)
    {
        pCircle->Init();
        pCircle->SetPlayerPos(pos);
    }
    return pCircle;
}

//==============================================
// テクスチャ描画
//==============================================
void CCloneCircle::DrawTexture(LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR3 position, D3DXVECTOR2 scale)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();

    //頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CUSTOMVERTEX));
    // 頂点フォーマットを設定
    pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

    // 現在のライティング状態を保存
    DWORD  lightingEnabled;
    pDevice->GetRenderState(D3DRS_LIGHTING, &lightingEnabled);

    // ライティングを無効にする
    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    // ワールド行列を設定
    D3DXMATRIX matWorld, matScale, matTrans;
    D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);
    D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
    matWorld = matScale * matTrans;
    pDevice->SetTransform(D3DTS_WORLD, &matWorld);

    // テクスチャの設定と描画
    pDevice->SetTexture(0, pTexture);

    //ポリゴンの描画
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    // ライティングの状態を元に戻す
    pDevice->SetRenderState(D3DRS_LIGHTING, lightingEnabled);
}

//==============================================
// クローン出現位置選択
//==============================================
D3DXVECTOR3 CCloneCircle::GetSelectedPosition()
{
    const float radius = 250.0f;
    switch (m_nSelectedIndex)
    {
    case 0: return { m_pos.x, m_pos.y + radius, m_pos.z };  // 上
    case 1: return { m_pos.x, m_pos.y - radius, m_pos.z };  // 下
    case 2: return { m_pos.x + radius, m_pos.y, m_pos.z };  // 右
    case 3: return { m_pos.x - radius, m_pos.y, m_pos.z };  // 左
    default: return m_pos;
    }
}

//==============================================
// プレイヤー位置設定
//==============================================
void CCloneCircle::SetPlayerPos(D3DXVECTOR3 pos) 
{
    m_pos = pos;
}

//==============================================
// 選択位置設定
//==============================================
void CCloneCircle::SetSelectedIndex(int index)
{
    m_nSelectedIndex = index;
}

//==============================================
// 描画を再有効化
//==============================================
void CCloneCircle::Activate()
{
    m_bUseDeath = false; 
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CCloneCircle::SetDeath()
{
    // クローンサークルの描画を無効化
    m_bUseDeath = true; // フラグで描画を停止

    CObject::SetDeath();
}