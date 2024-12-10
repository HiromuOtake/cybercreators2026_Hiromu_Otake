//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_SE_JUMP,		// ジャンプ音
		SOUND_LABEL_SE_COIN,		// コイン音
		SOUND_LABEL_SE_DEATH,		// 死亡音
		SOUND_LABEL_SE_GOAL,		// ゴール音
		SOUND_LABEL_SE_SHOT,		// 弾発射音
		SOUND_LABEL_SE_BUTON,		// ボタン音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;		    // ループカウント
		float Volume;           //音量
	} SOUNDINFO;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopAllSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[CSound::SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[CSound::SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[CSound::SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
	CSound::SOUNDINFO m_aSoundInfo[CSound::SOUND_LABEL_MAX] =
	{
		{"data/BGM/neon.wav", -1,1.0f},		// BGM0
		{"data/BGM/ネオン.wav", -1,1.5f} ,	// BGM1
		{"data/SE/jump.wav", 0,1.5f},		// ジャンプ音
		{"data/SE/get000.wav", 0,0.9f},		// コイン音
		{"data/SE/death.wav", 0,1.0f},		// 死亡音
		{"data/SE/goal.wav", 0,2.0f},		// ゴール音
		{"data/SE/shot.wav", 0,1.0f},		// 弾発射音
		{"data/SE/get001.wav", 0,2.0f},		// ボタン音
	};
};

#endif
