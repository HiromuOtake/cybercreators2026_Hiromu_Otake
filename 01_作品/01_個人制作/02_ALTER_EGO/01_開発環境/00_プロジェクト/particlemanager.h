//======================================================
//
// ALTER_EGO [particlemanager.h]
// Auther : 大竹熙
//
//======================================================

#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

#include "particle.h"
#include <d3dx9.h>
#include <vector>

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
private:
    std::vector<CParticle*> m_particles;  // パーティクルリスト
};

#endif  // _PARTICLE_MANAGER_H_