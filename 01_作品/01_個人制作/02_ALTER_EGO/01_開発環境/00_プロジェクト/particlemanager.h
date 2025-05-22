//======================================================
//
// ALTER_EGO [particlemanager.h]
// Auther : ��|�
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
    std::vector<CParticle*> m_particles;  // �p�[�e�B�N�����X�g
};

#endif  // _PARTICLE_MANAGER_H_