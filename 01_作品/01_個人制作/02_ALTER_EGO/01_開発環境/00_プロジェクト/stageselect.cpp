//======================================================
//
// ALTER_EGO [stageselect.cpp]
// Auther : ��|�
//
//======================================================

#include "stageselect.h"
#include "manager.h"
#include "texture.h"
#include "block.h"
#include <cassert>
#include <sstream>
#include <iomanip>

//=================================
// �R���X�g���N�^
//=================================
CStageSelect::CStageSelect() : m_selectedStage(0), m_bgTexture(0), m_alpha(0.0f), m_Keyboard(nullptr), m_JoyPad(nullptr), m_pObj{}
{
    for (int i = 0; i < m_NUM_STAGE; i++) m_stageTextures[i] = 0;
}

//=================================
// �f�X�g���N�^
//=================================
CStageSelect::~CStageSelect() 
{

}

//=================================
// ����������
//=================================
HRESULT CStageSelect::Init()
{
    CSound* pSound = CManager::GetSound();

    pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

    m_Keyboard = CManager::GetKeyboard();
    m_JoyPad = CManager::GetJoyPad();

    // �w�i�e�N�X�`����ǂݍ���
    CBg::Create(CScene::MODE::MODE_STAGESELECT);

    // �X�e�[�W�e�N�X�`���𐶐�
    float fInitialPointX = 140.0f;
    float fInitialPointY = 450.0f;

    for (int i = 0; i < m_NUM_STAGE; i++, fInitialPointX += 250.0f)
    {
        std::ostringstream filename;
        filename << "data\\Texture\\stage" << std::setfill('0') << std::setw(2) << (i + 1) << ".png";
        m_stageTextures[i] = CManager::GetTexture()->Regist(filename.str().c_str());

        m_nItemSilhouetteTexIdx = CManager::GetTexture()->Regist("data\\Texture\\itemsilhouette.png");
        m_ItemTexIdx = CManager::GetTexture()->Regist("data\\Texture\\item.png");

        float alpha = (i == m_selectedStage) ? 1.0f : 0.5f;

        m_pObj[i] = CObject2D::Create(
            CManager::GetTexture()->GetAddress(m_stageTextures[i]),
            D3DXVECTOR3(fInitialPointX, fInitialPointY, 0.0f),
            200.0f, 200.0f, 1.0f, alpha);

        m_pItemTex[i] = CObject2D::Create(
            CManager::GetTexture()->GetAddress(m_ItemTexIdx),
            D3DXVECTOR3(fInitialPointX, 275.0f, 0.0f),
            100.0f, 100.0f, 1.0f, 1.0f);

        //if ((i + 1) % 5 == 0) // 5�����Ƃɗ��؂�ւ�
        //{
        //    fInitialPointX = 50.0f;
        //    fInitialPointY += 200.0f;
        //}

        if (m_stageTextures[i] == -1)
        {
            char debugMessage[256];
            sprintf(debugMessage, "�e�N�X�`���̃��[�h�Ɏ��s���܂���: %s\n", filename.str().c_str());
            OutputDebugStringA(debugMessage);
        }
    }
    return S_OK;
}

//=================================
// �I������
//=================================
void CStageSelect::Uninit()
{
    CScene::Uninit();
}

//=================================
// �X�V����
//=================================
void CStageSelect::Update()
{
    SelectStage();

    // �A���t�@�l���X�V
    for (int i = 0; i < m_NUM_STAGE; i++)
    {
        float alpha = (i == m_selectedStage) ? 1.0f : 0.5f;
        m_pObj[i]->SetColor(alpha);
    }
}

//=================================
// �`�揈��
//=================================
void CStageSelect::Draw()
{

}

//=================================
// ���͏���
//=================================
void CStageSelect::SelectStage()
{
    // �㉺���E�L�[����
    if (m_Keyboard->GetTrigger(DIK_W) || m_Keyboard->GetTrigger(DIK_UP) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_UP) == true)
    {
        m_selectedStage = (m_selectedStage - 5 + m_NUM_STAGE) % m_NUM_STAGE; // ��i��
    }
    else if (m_Keyboard->GetTrigger(DIK_S) || m_Keyboard->GetTrigger(DIK_DOWN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_DOWN) == true)
    {
        m_selectedStage = (m_selectedStage + 5) % m_NUM_STAGE; // ���i��
    }
    else if (m_Keyboard->GetTrigger(DIK_D) || m_Keyboard->GetTrigger(DIK_RIGHT) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_RIGHT) == true)
    {
        m_selectedStage = (m_selectedStage + 1) % m_NUM_STAGE; // �E�ׂ̃X�e�[�W
    }
    else if (m_Keyboard->GetTrigger(DIK_A) || m_Keyboard->GetTrigger(DIK_LEFT) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_LEFT) == true)
    {
        m_selectedStage = (m_selectedStage - 1 + m_NUM_STAGE) % m_NUM_STAGE; // ���ׂ̃X�e�[�W
    }

    // ����L�[����
    if (m_Keyboard->GetTrigger(DIK_RETURN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_START) == true)
    {
        // �I�����ꂽ�X�e�[�W�����̃V�[���ɓn��
        std::ostringstream stageFile;
        stageFile << "data\\Stage\\SetStage" << std::setfill('0') << std::setw(3) << (m_selectedStage + 1) << ".txt";
        CManager::SetNextStage(stageFile.str().c_str());
        CManager::SetNextScene(CScene::MODE_TUTORIAL1);
    }
}