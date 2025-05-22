//======================================================
//
// ALTER_EGO [particlemanager.h]
// Auther : 大竹熙
//
//======================================================

#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

#include "particle.h"

class CParticleManager
{
public:
    CParticleManager();
    ~CParticleManager();
    void Init();
    void Uninit();
    void Update();
    void Draw();
    void EmitParticles(D3DXVECTOR3 pos, int numParticles, float size, float speed, D3DXCOLOR color);
    static constexpr float m_DECAY = 0.1f;
private:
    std::vector<CParticle*> m_particles;  // パーティクルリスト
};

#endif  // _PARTICLE_MANAGER_H_