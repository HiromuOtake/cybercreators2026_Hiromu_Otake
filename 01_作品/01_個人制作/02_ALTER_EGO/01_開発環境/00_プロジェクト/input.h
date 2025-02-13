//==============================================
//
// ALTER_EGO[input.h]
// Author: hiromu otake
//
//==============================================

#ifndef   _INPUT_H_
#define   _INPUT_H_

#include "main.h"

//マクロ定義
#define JOYPAD_ZONE     (1)
#define JOYPAD_SPEED    (15)
#define MAX_KEY         (256)

class CInput
{
public:
    //キーの種類
    typedef enum
    {
        JOYKEY_UP = 0,
        JOYKEY_DOWN,
        JOYKEY_LEFT,
        JOYKEY_RIGHT,
        JOYKEY_START,
        JOYKEY_BACK,
        JOYKEY_L3,
        JOYKEY_R3,
        JOYKEY_LB,
        JOYKEY_RB,
        JOYKEY_LT,
        JOYKEY_RT,
        JOYKEY_A,
        JOYKEY_B,
        JOYKEY_X,
        JOYKEY_Y,
        JOYKEY_MAX
    }JOYKEY;

    //スティックの番号
    typedef enum
    {
        STICKTYPE_LEFT = 0, // 左スティック
        STICKTYPE_RIGHT, // 右スティック
        STICKTYPE_MAX
    }STICKTYPE;

    //スティックの方向
    typedef enum
    {
        STICKANGLE_UP = 0, // 上
        STICKANGLE_DOWN,   // 下
        STICKANGLE_LEFT,   // 左
        STICKANGLE_RIGHT,  // 右
        STICKANGLE_MAX,
    }STICKANGLE;

    //スティックの入力情報
    typedef struct
    {
        float afTplDiameter[STICKTYPE_MAX];                      // スティックの倒し具合
        float afAngle[STICKTYPE_MAX];                            // スティックの角度
        bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // スティックの方向プレス情報
        bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向トリガー情報
        bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // スティックの方向リピート情報
        bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向リリース情報
    }STICKINPUT;

    CInput();
    ~CInput();
    virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    virtual void Uninit();
    virtual void Update() = 0;
protected:
    static LPDIRECTINPUT8 m_pInput;
    LPDIRECTINPUTDEVICE8 m_pDevice;
};

class CInputKeyboard : public CInput
{
public:
    CInputKeyboard();
    ~CInputKeyboard();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit();
    void Update();
    bool GetPress(int nKey);    // プレス状態取得
    bool GetTrigger(int nKey);   // トリガー状態取得
private:
    BYTE m_aKetStatePress[MAX_KEY];
    BYTE m_aKeyStateTrigger[MAX_KEY];
};

class CInputJoyPad : public CInput
{
public:
    CInputJoyPad();
    ~CInputJoyPad();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit();
    void Update();
    void UpdateStick(XINPUT_STATE GamePadState);
    bool GetJoyPadPress(JOYKEY nKey);    // プレス状態取得
    bool GetJoyPadTrigger(JOYKEY nKey);   // トリガー状態取得
    float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
    WORD GetJoypadStick(SHORT sThumbx, SHORT sThumby, SHORT sDeaZone);
    STICKINPUT GetStick();
    XINPUT_STATE* GetXInputState();
private:
    BYTE m_aJoyPadStatePress[MAX_KEY];
    BYTE m_aJoyPadStateTrigger[MAX_KEY];
    WORD m_joykeyState;                                         //ジョイパッドのプレス情報
    WORD m_joyKeyStateTrigger; //ジョイパッドのトリガー情報
    WORD m_joyKeyStateRepeat; //ジョイパッドのリピート情報
    WORD m_ajoyKeyStateRelease; //コントローラーのリリース情報
    WORD m_aJoypadCurrentTime; //コントローラーの現在の時間
    WORD m_aJoypadExecLastTime; //コントローラーの最後に真を返した時間
    WORD m_JoypadInput; //コントローラーの入力情報
    D3DXVECTOR3 m_joyStickPos; //スティックの傾き
    bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの入力情報
    DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
    DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
    STICKINPUT m_stick; //スティックの入力情報
    XINPUT_STATE m_XInput; //入力情報
    XINPUT_VIBRATION m_JoypadMotor;
    int m_nCntkey;
};



#endif