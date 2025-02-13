//==============================================
//
// ALTER_EGO[particlemanager.cpp]
// Author: hiromu otake
//
//==============================================

#include "particlemanager.h"

//=====================================
// コンストラクタ
//=====================================
CParticleManager::CParticleManager()
{

}

//=====================================
// デストラクタ
//=====================================
CParticleManager::~CParticleManager() 
{
    Uninit();
}

//==============================================
// 初期設定
//==============================================
void CParticleManager::Init()
{
    // パーティクル用のテクスチャをロード
    CParticle::Load();
}

//==============================================
// 終了処理
//==============================================
void CParticleManager::Uninit()
{
    for (CParticle* particle : m_particles)
    {
        if (particle)
        {
            delete particle;
        }
    }

    m_particles.clear();

    // パーティクル用のテクスチャを解放
    CParticle::Unload();
}

//==============================================
// 更新処理
//==============================================
void CParticleManager::Update()
{
    for (auto it = m_particles.begin(); it != m_particles.end();) 
    {
        (*it)->Update();
        if ((*it)->GetMove()->x == 0.0f && (*it)->GetMove()->y == 0.0f || (*it)->m_nLife <= 0)
        {  // 寿命チェック等
            delete* it;
            it = m_particles.erase(it);
        }
        else 
        {
            ++it;
        }
    }
}

//==============================================
// 描画処理
//==============================================
void CParticleManager::Draw()
{
    for (CParticle* particle : m_particles) 
    {
        particle->Draw();
    }
}

//=====================================================
// パーティクルの生成（大きさ、速さ、色を指定可能）
//=====================================================
void CParticleManager::EmitParticles(D3DXVECTOR3 pos, int numParticles, float size, float speed, D3DXCOLOR color)
{
    for (int i = 0; i < numParticles; ++i)
    {
        // ランダムな移動を設定
        D3DXVECTOR3 move;
        move.x = (rand() % 10 - 5) * speed * 0.1f;
        move.y = (rand() % 10) * speed * 0.1f;
        move.z = (rand() % 10 - 5) * speed * 0.1f;

        // パーティクル生成
        CParticle::Create(pos, move, size, speed, color);
    }
}