//==============================================
//
//ALTER_EGO[character.cpp]
//Author: hiromu otake
//
//==============================================

#include "character.h"
#include "model.h"
#include "manager.h"

//==============================================
// コンストラクタ
//==============================================
CCharacter::CCharacter(int nPriorit) : m_nLife(0), m_aFilename(), m_pModelParts(), m_pMotion(MOTION_NONE)
, m_pos{ 0.0f,0.0f,0.0f }, m_posold{ 0.0f,0.0f,0.0f }, m_rot{ 0.0f,0.0f,0.0f }, m_nFlameCnt(0), m_nKeyCount(0)
{

}

//==============================================
// デストラクタ
//==============================================
CCharacter::~CCharacter()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CCharacter::Init()
{
	m_pMotion = MOTION_NONE;

	FILE* pFile = fopen("data\\Motion\\motion.txt", "r");

	int nCnt = 0;

	if (pFile == NULL)
	{
		return S_FALSE;
	}

	char aStr[m_MAX_LETTER];	// 文字列を格納

	// スクリプトが開始するまで読み進める
	while (1)
	{
		fscanf(pFile, "%s", &aStr[0]);
		if (strcmp(&aStr[0], "SCRIPT") == 0)
		{
			break;
		}
	}

	// メインループ
	while (1)
	{
		// 文字列を読み込む
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_SCRIPT") == 0)
		{ // スクリプト終了
			fclose(pFile);
			break;
		}
		else if (strcmp(&aStr[0], "MODEL_FILENAME") == 0)
		{ // モデルファイルを読み込む
			//char aFilename[m_MAX_LETTER][m_NUM_MODEL_PARTS];
			char aFilename[m_NUM_MODEL_PARTS][m_MAX_LETTER];
			fscanf(pFile, "%s %s", &aStr[0], &aFilename[nCnt][0]);

			OutputDebugStringA(aFilename[nCnt]);

			m_pModelParts[nCnt] = CModelParts::Create(D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), &aFilename[nCnt][0]);

			nCnt++;
		}
		else if (strcmp(&aStr[0], "CHARACTERSET") == 0)
		{ // キャラクターの設定
			LoadCharacterSet(pFile);
		}
	}

	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CCharacter::Uninit()
{

}

//==============================================
// 更新処理
//==============================================
void CCharacter::Update()
{

}

//==============================================
// 描画処理
//==============================================
void CCharacter::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;							//デバイスへのポインタ
	CRenderer* pRenderer = CManager::GetRenderere();
	pDevice = pRenderer->GetDevice();					//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < m_NUM_MODEL_PARTS; nCnt++)
	{
		m_pModelParts[nCnt]->Draw();
	}
}

//=====================================
// キャラクター情報を読み込む
//=====================================
void CCharacter::LoadCharacterSet(FILE* pFile)
{
	char aStr[m_MAX_LETTER];	// 文字列を格納
	int nCntModel = 0;		// モデルの数をカウント

	while (1)
	{
		// 文字列を読み込む
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_CHARACTERSET") == 0)
		{ // キャラクター設定が終わる
			break;
		}
		else if (strcmp(&aStr[0], "PARTSSET") == 0)
		{ // パーツの設定
			LoadPartsSet(pFile, &nCntModel);
		}
	}
}

//=====================================
// パーツの設定情報を読み込む
//=====================================
void CCharacter::LoadPartsSet(FILE* pFile, int* nCntModel)
{
	char aStr[m_MAX_LETTER];	// 文字列を格納

	while (1)
	{
		// 文字列を読み込む
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_PARTSSET") == 0)
		{ // パーツの設定終了
			(*nCntModel)++;
			break;
		}
		else if (strcmp(&aStr[0], "INDEX") == 0)
		{
			fscanf(pFile, "%s %d",
				&aStr[0],										// =
				&m_pModelParts[(*nCntModel)]->m_nIdx);				// インデックス
		}
		else if (strcmp(&aStr[0], "PARENT") == 0)
		{
			fscanf(pFile, "%s %d",
				&aStr[0],										// =
				&m_pModelParts[(*nCntModel)]->m_nIdxParents);	// 親モデルのインデックス

			if (m_pModelParts[(*nCntModel)]->m_nIdxParents == -1)
			{
				m_pModelParts[(*nCntModel)]->SetParent(nullptr);
			}
			else
			{
				m_pModelParts[(*nCntModel)]->SetParent(m_pModelParts[m_pModelParts[(*nCntModel)]->m_nIdxParents]);
			}
		}
		else if (strcmp(&aStr[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f",
				&aStr[0],										// =
				&m_pModelParts[(*nCntModel)]->m_pos.x,			// x座標を読み込む
				&m_pModelParts[(*nCntModel)]->m_pos.y,			// y座標を読み込む
				&m_pModelParts[(*nCntModel)]->m_pos.z);			// z座標を読み込む
		}
		else if (strcmp(&aStr[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f",
				&aStr[0],										// =
				&m_pModelParts[(*nCntModel)]->m_rot.x,			// x軸向きを読み込む
				&m_pModelParts[(*nCntModel)]->m_rot.y,			// y軸向きを読み込む
				&m_pModelParts[(*nCntModel)]->m_rot.z);			// z軸向きを読み込む
		}
	}
}

//=====================================
// ファイルネームの取得
//=====================================
char* CCharacter::GetFileName()
{
	return m_aFilename[0][0];
}

//=====================================
//モーションファイルの読み込み
//=====================================
void CCharacter::LoadMotion(int* nCntMotion)
{
	FILE* pFile = fopen("data\\Motion\\motion.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	char aStr[m_MAX_LETTER];	// 文字列を格納

	// スクリプトが開始するまで読み進める
	while (1)
	{
		fscanf(pFile, "%s", &aStr[0]);
		if (strcmp(&aStr[0], "SCRIPT") == 0)
		{
			break;
		}
	}

	// メインループ
	while (1)
	{
		// 文字列を読み込む
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_SCRIPT") == 0)
		{ // スクリプト終了
			fclose(pFile);
			break;
		}
		else if (strcmp(&aStr[0], "MOTIONSET") == 0)
		{ // モーションの設定
			LoadMotionSet(pFile, (*nCntMotion));
			(*nCntMotion)++;
		}
	}
}

//=====================================
// キャラクター情報を読み込む
//=====================================
void CCharacter::LoadMotionSet(FILE* pFile, int nCntMotion)
{
	char aStr[m_MAX_LETTER];	// 文字列を格納
	int nCntKeySet = 0;

	while (1)
	{
		// 文字列を読み込む
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_MOTIONSET") == 0)
		{ // キャラクター設定が終わる
			break;
		}
		else if (strcmp(&aStr[0], "LOOP") == 0)
		{
			fscanf(pFile, "%s %d",
				&aStr[0],							// =
				&m_pMotionSet[nCntMotion].nLoop);	// ループ
		}
		else if (strcmp(&aStr[0], "NUM_KEY") == 0)
		{
			fscanf(pFile, "%s %d",
				&aStr[0],							// =
				&m_pMotionSet[nCntMotion].NumKey);	// 何番目のキー
		}
		else if (strcmp(&aStr[0], "KEYSET") == 0)
		{ // パーツの設定
			LoadKeySet(pFile, nCntMotion, nCntKeySet);
			nCntKeySet++;
		}
	}
}

//=====================================
// モデルのキーを読み込む
//=====================================
void CCharacter::LoadKeySet(FILE* pFile, int nCntMotion, int nCntKeySet)
{
	char aStr[m_MAX_LETTER];	// 文字列を格納
	int nCntKey = 0;

	while (1)
	{
		// 文字列を読み込む
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "#") == 0)
		{
			//fgets(aStr, 20, pFile);
			LoadSkip(pFile);
			continue;
		}

		if (strcmp(&aStr[0], "END_KEYSET") == 0)
		{ // パーツの設定終了

			break;
		}
		else if (strcmp(&aStr[0], "KEY") == 0)
		{ // パーツの設定
			LoadKey(pFile, nCntMotion, nCntKeySet, nCntKey);
			nCntKey++;
		}
		else if (strcmp(&aStr[0], "FRAME") == 0)
		{
			fscanf(pFile, "%s %f",
				&aStr[0],												// =
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].nFlame);	// フレーム読み込み
		}
	}
}

//=====================================
// モデルのキーの設定情報を読み込む
//=====================================
void CCharacter::LoadKey(FILE* pFile, int nCntMotion, int nCntKeySet, int nCntKey)
{
	char aStr[m_MAX_LETTER];	// 文字列を格納

	while (1)
	{
		// 文字列を読み込む
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_KEY") == 0)
		{ // パーツの設定終了
			break;
		}
		else if (strcmp(&aStr[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f",
				&aStr[0],															// =
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].pos.x,	// x座標を読み込む
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].pos.x,	// y座標を読み込む
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].pos.x);	// z座標を読み込む
		}
		else if (strcmp(&aStr[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f",
				&aStr[0],															// =
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.x,	// x軸向きを読み込む
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.y,	// y軸向きを読み込む
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.z);	// z軸向きを読み込む
		}
	}
	return;
}

void CCharacter::LoadSkip(FILE* pFile)
{
	int nSkip;

	while (1)
	{
		nSkip = fgetc(pFile);

		if (nSkip == '\n' || nSkip == EOF)
		{
			break;
		}
	}
}

void CCharacter::SetMotion(MOTION motion)
{
	if (m_pMotion != motion)
	{
		m_pMotion = motion;

		m_nFlameCnt = 0;

		m_nKeyCount = 0;

		for (int nCnt = 0; nCnt < m_NUM_MODEL_PARTS; nCnt++)
		{
			//g_Player.aModel[nCnt].pos = g_aMotionSet[motion].aKeySet[0].aKey[nCnt].pos;
			m_pModelParts[nCnt]->m_rot = m_pMotionSet[motion].aKeySet[0].aKey[nCnt].rot;
		}
	}
}

void CCharacter::PlayerMotion(void)
{
	D3DXVECTOR3 posMotion[m_NUM_MODEL_PARTS];
	D3DXVECTOR3 rotMotion[m_NUM_MODEL_PARTS];

	//次のキー
	int nNextKey = (m_nKeyCount + 1) % m_pMotionSet[m_pMotion].NumKey;

	for (int nCnt = 0; nCnt < m_NUM_MODEL_PARTS; nCnt++)
	{
		//現在のキーから過去のキーを引いてからフレームで割る
		rotMotion[nCnt] = ((m_pMotionSet[m_pMotion].aKeySet[nNextKey].aKey[nCnt].rot) - (m_pMotionSet[m_pMotion].aKeySet[m_nKeyCount].aKey[nCnt].rot)) / (float)m_pMotionSet[m_pMotion].aKeySet[m_nKeyCount].nFlame;
		m_pModelParts[nCnt]->m_rot += rotMotion[nCnt];
	}

	m_nFlameCnt++;

	//
	if (m_nFlameCnt >= m_pMotionSet[m_pMotion].aKeySet[m_nKeyCount].nFlame)
	{
		m_nFlameCnt = 0;
		m_nKeyCount = (m_nKeyCount + 1) % m_pMotionSet[m_pMotion].NumKey;
	}
}

//======================================================
// 位置の設定
//======================================================
void CCharacter::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

D3DXVECTOR3& CCharacter::GetPos()
{
	return m_pos;
}

//======================================================
// 過去の位置の取得
//======================================================
D3DXVECTOR3& CCharacter::GetPosOld()
{
	return m_posold;
}

D3DXVECTOR3& CCharacter::GetRot()
{
	return m_rot;
}

CModelParts* CCharacter::GetModelParts(int idx)
{
	return m_pModelParts[idx];
}