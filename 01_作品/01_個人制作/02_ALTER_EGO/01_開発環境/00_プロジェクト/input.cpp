//==============================================
//
// ALTER_EGO[input.cpp]
// Author: hiromu otake
//
//==============================================

#include "input.h"

// 静的メンバ初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//============================
// コンストラクタ
//============================
CInput::CInput() : m_pDevice(nullptr)
{

}

//============================
// デストラクタ
//============================
CInput::~CInput()
{

}

//============================
// 初期化処理
//============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================
// 終了処理
//============================
void CInput::Uninit()
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();      //キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//============================
// 更新処理
//============================
void CInput::Update()
{

}

//============================
// キーボードのコンストラクタ
//============================
CInputKeyboard::CInputKeyboard() : m_aKeyStateTrigger(), m_aKetStatePress()
{
	for (int i = 0; i < MAX_KEY; i++)
	{
		m_aKeyStateTrigger[i] = NULL;
		m_aKetStatePress[i] = NULL;
	}
}

//============================
// キーボードのデストラクタ
//============================
CInputKeyboard::~CInputKeyboard()
{

}

//============================
// キーボードの初期化処理
//============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//============================
// キーボードの終了処理
//============================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//============================
// キーボードの更新処理
//============================
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY];     //キーボードの入力情報

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
		{
			m_aKeyStateTrigger[nCnt] = (m_aKetStatePress[nCnt] ^ aKeyState[nCnt]) & aKeyState[nCnt];
			m_aKetStatePress[nCnt] = aKeyState[nCnt];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=================================
// キーボードのプレス情報を取得
//=================================
bool CInputKeyboard::GetPress(int nKey)
{
	return((m_aKetStatePress[nKey] & 0x80) != 0) ? true : false;
	return(m_aKetStatePress[nKey] & 0x80) != 0;
}

//=================================
// キーボードのトリガー情報を取得
//=================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//============================
// キーボードのコンストラクタ
//============================
CInputJoyPad::CInputJoyPad() : m_aJoyPadStatePress(), m_aJoyPadStateTrigger()
{
	for (int i = 0; i < MAX_KEY; i++)
	{
		m_aJoyPadStatePress[i] = NULL;
		m_aJoyPadStateTrigger[i] = NULL;
	}
}

//============================
// キーボードのデストラクタ
//============================
CInputJoyPad::~CInputJoyPad()
{

}

//============================
// キーボードの初期化処理
//============================
HRESULT CInputJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//============================
// キーボードの終了処理
//============================
void CInputJoyPad::Uninit()
{
	CInput::Uninit();
}

//=============================================
// スティックの入力を方向パッドフラグに変換
//=============================================
WORD CInputJoyPad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

void CInputJoyPad::UpdateStick(XINPUT_STATE GamePadState)
{
	//キーボードの状態を取得
	if (XInputGetState(0, &GamePadState) == ERROR_SUCCESS)
	{
		for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
		{
			float fX, fY; //スティックのX軸、Y軸

			switch (nCntStick)
			{
			case STICKTYPE_LEFT:
				fX = GamePadState.Gamepad.sThumbLX;
				fY = GamePadState.Gamepad.sThumbLY;
				break;
			case STICKTYPE_RIGHT:
				fX = GamePadState.Gamepad.sThumbRX;
				fY = GamePadState.Gamepad.sThumbRY;
				break;
			}

			//角度を取得
			m_stick.afAngle[nCntStick] = FindAngle(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

			//スティックの倒し具合を取得
			m_stick.afTplDiameter[nCntStick] = fabsf(fX);

			if (m_stick.afTplDiameter[nCntStick] < fabsf(fY))
			{
				m_stick.afTplDiameter[nCntStick] = fabsf(fY);
			}

			m_stick.afTplDiameter[nCntStick] /= 32768.0f; //倒している状態の初期値

			//方向入力フラグを初期化
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				m_bAngle[nCntStick][nCntAngle] = false;
			}

			if (m_stick.afTplDiameter[nCntStick] > 0.1f)
			{
				//角度が四分割で上に位置する時、上フラグを真にする
				if ((m_stick.afAngle[nCntStick] < D3DX_PI * -0.75) || (m_stick.afAngle[nCntStick] > D3DX_PI * 0.75))
				{
					m_bAngle[nCntStick][STICKANGLE_UP] = true;
				}

				//角度が四分割で下に位置する時、下フラグを真にする
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.25))
				{
					m_bAngle[nCntStick][STICKANGLE_DOWN] = true;
				}

				//角度が四分割で左に位置する時、左フラグを真にする
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.75) && (m_stick.afAngle[nCntStick] < D3DX_PI * -0.25))
				{
					m_bAngle[nCntStick][STICKANGLE_LEFT] = true;
				}

				//角度が四分割で右に位置する時、右フラグを真にする
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * 0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.75))
				{
					m_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
				}
			}

			//角度に応じた入力処理
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				//スティックのトリガー情報を保存
				m_stick.abAngleTrigger[nCntStick][nCntAngle] = (m_stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & m_bAngle[nCntStick][nCntAngle];

				//スティックのリリース情報を保存
				m_stick.abAngleRelease[nCntStick][nCntAngle] = (m_stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & ~m_bAngle[nCntStick][nCntAngle];

				//現在の時間を取得
				m_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();

				if (m_bAngle[nCntStick][nCntAngle] && ((m_aStickCurrentTime[nCntStick][nCntAngle] - m_aStickExecLastTime[nCntStick][nCntAngle]) > JOYPAD_SPEED))
				{
					//最後に真を返した時間を保存
					m_aStickExecLastTime[nCntStick][nCntAngle] = m_aStickCurrentTime[nCntStick][nCntAngle];

					//スティックのリピート情報を保存
					m_stick.abAngleRepeat[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
				}
				else
				{
					//スティックのリピート情報を保存
					m_stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
				}

				//スティックのプレス情報を保存
				m_stick.abAnglePress[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
			}
		}
	}
}

//=================================
//ジョイパッドの更新処理
//=================================
void CInputJoyPad::Update()
{
	XINPUT_STATE joykeyState;     //ジョイパッドの入力情報

	    //ジョイパッドの状態を取得
		if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
		{
			UpdateStick(joykeyState);
			WORD Button = joykeyState.Gamepad.wButtons;
			WORD OldButton = m_joykeyState;
			m_joyKeyStateTrigger = Button & ~OldButton;    // トリガー処理
			m_ajoyKeyStateRelease = ~Button & OldButton;    // リリース処理
			joykeyState.Gamepad.wButtons |= GetJoypadStick(joykeyState.Gamepad.sThumbLX, joykeyState.Gamepad.sThumbLY, JOYPAD_ZONE);

			// 現在の時間を取得する
			m_aJoypadCurrentTime = (WORD)timeGetTime();

			if (joykeyState.Gamepad.wButtons && ((m_aJoypadCurrentTime - m_aJoypadExecLastTime) > JOYPAD_SPEED))
			{
				// 最後に真を返した時間を保存
				m_aJoypadExecLastTime = m_aJoypadCurrentTime;

				// キーボードのリピート情報を保存
				m_joyKeyStateRepeat = joykeyState.Gamepad.wButtons;
			}
			else
			{
				// キーボードのリピート情報を保存
				m_joyKeyStateRepeat = 0;
			}
			m_joykeyState = joykeyState.Gamepad.wButtons;                // プレス処理
		}
}

//2点の角度を求める
float CInputJoyPad::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //角度

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

//=====================================
// コントローラーの入力情報の取得
//=====================================
XINPUT_STATE* CInputJoyPad::GetXInputState(void)
{
	return &m_XInput;
}

//=====================================
// スティックの入力情報を取得
//=====================================
CInputJoyPad::STICKINPUT CInputJoyPad::GetStick(void)
{
	return m_stick;
}

//=====================================
//ジョイパッドのプレス情報を取得
//=====================================
bool CInputJoyPad::GetJoyPadPress(JOYKEY key)
{
	return (m_joykeyState & (0x01 << key)) ? true : false;
}

//=====================================
//ジョイパッドのトリガー情報を取得
//=====================================
bool CInputJoyPad::GetJoyPadTrigger(JOYKEY key)
{
	return (m_joyKeyStateTrigger & (0x01 << key)) ? true : false;
}
