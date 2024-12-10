//==============================================
//
//ATG制作[ranking.cpp]
//Author: hiromu otake
//
//==============================================

#include "main.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include <stdio.h>
#include <string.h>

//=====================================================
// コンストラクタ
//======================================================
CRanking::CRanking() : m_pTexture(nullptr), m_pVtxBuff(nullptr)
{

}

//======================================================
// デストラクタ
//======================================================
CRanking::~CRanking()
{

}

//==========================================
//ランキングの初期化処理
//==========================================

HRESULT CRanking::Init()
{
	CScene::Init();

	CBg::Create(CScene::MODE::MODE_TITLE, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);

	return S_OK;
}

//==========================================
//ランキングの終了処理
//==========================================

void UninitRanking(void)
{
	UninitRankingBG();
	UninitRankingA();
	UninitRankingRank();

	//テクスチャを破棄
	if (g_TextureRank != NULL)
	{
		g_TextureRank->Release();
		g_TextureRank = NULL;
	}

	//頂点バッファの破壊
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	StopSound();
}

//==========================================
//ランキングの更新処理
//==========================================

void UpdateRanking(void)
{
	g_nTimerRanking++;	//ランキングを点灯させる時間の更新

	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	int nCntRank = 0;
	int nCntNumber = 0;

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//ENTERキーが押された
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_TITLE);
	}

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntNumber].pos.x - RANK_WIDTH, g_aRankScore[nCntRank][nCntNumber].pos.y - RANK_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntNumber].pos.x + RANK_WIDTH, g_aRankScore[nCntRank][nCntNumber].pos.y - RANK_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntNumber].pos.x - RANK_WIDTH, g_aRankScore[nCntRank][nCntNumber].pos.y + RANK_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntNumber].pos.x + RANK_WIDTH, g_aRankScore[nCntRank][nCntNumber].pos.y + RANK_HEIGHT, 0.0f);


			if (g_aRankScore[nCntRank][nCntNumber].bRight == true)
			{
				if (g_nTimerRanking % 1 == 0)
				{//赤くする
					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.6f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.6f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.6f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.6f, 1.0f);
				}
				else
				{//元に戻す
					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
			pVtx += 4;
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffRank->Unlock();
}

//=======================================================================
//ランキングの描画処理
//=======================================================================

void DrawRanking(void)
{
	DrawRankingBG();
	DrawRankingA();
	DrawRankingRank();

	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));


	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_NUMBER; nCntRank++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_TextureRank);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);

	}
}

//==========================================
//ランキングのリセット
//==========================================

void ResetRanking(void)
{
	int nCntRank; //数をカウントする(順位)
	int nCntNumber;	//数をカウントする(桁数)

	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
		{
			g_aRankScore[nCntRank][nCntNumber].nScore = 0;                       //使用していない状態
		}
	}
}

//==========================================
//ランキングの設定
//==========================================

void SetRanking(int nScore)
{
	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	FILE* pFile;

	int nCnt = 0;
	int nCntRank = 0;
	int nCntNumber = 0;	//桁数

	int nCntData = 0;	//要素1の情報
	int nAddRank = 0;	//今回のスコア
	int nCopyData = 0;	//データの受け皿
	int nData[MAX_RANK];	//すでにランクインしてるスコア	
	int nDataRank[MAX_RANK];	//データを保存する用
	int nDataSave[MAX_RANK];	//ランクインしたスコアの保存(並べ替えた後)

	pFile = fopen("data\\Ranking.txt", "r");

	if (pFile != NULL)
	{
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fscanf(pFile, "%d", &nData[nCntRank]);	//スコアをファイルから読み込む

			nDataRank[nCntRank] = nData[nCntRank];	//保存する

			nDataSave[nCntRank] = 0;	//初期化
		}

		nAddRank = nScore;	//今回のスコアを代入する
	}
	fclose(pFile);

	if (nAddRank >= nData[MAX_RANK - 1])
	{//もし5位より現在のスコアが高かったら
		nData[MAX_RANK - 1] = nAddRank;//5位に現在のスコアを代入
	}

	for (nCntData = 0; nCntData <= MAX_RANK - 1; nCntData++)//要素1と要素2を比較する
	{
		for (nCntRank = nCntData + 1; nCntRank < MAX_RANK; nCntRank++)
		{
			if (nData[nCntData] < nData[nCntRank])
			{
				nCopyData = nData[nCntData];	//受け皿に要素1を代入
				nData[nCntData] = nData[nCntRank];	//要素1に要素2を代入
				nData[nCntRank] = nCopyData;		//数値を入れ替える
			}
		}
	}

	pFile = fopen("data\\Ranking.txt", "w");
	if (pFile != NULL)
	{
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", nData[nCnt]);	//並べ替えたものを改めて保存する
		}
	}

	fclose(pFile);

	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		nDataSave[nCnt] = nData[nCnt];	//スコアの代入
	}

	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
		{
			g_aRankScore[nCnt][nCntNumber].nScorePos = nData[nCnt] % 10;
			nData[nCnt] = nData[nCnt] / 10;
		}
	}


	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntNumber].nScorePos), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntNumber].nScorePos), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntNumber].nScorePos), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntNumber].nScorePos), 1.0f);

			if (nDataSave[nCntRank] == nScore)
			{
				g_aRankScore[nCntRank][nCntNumber].bRight = true;
			}

			pVtx += 4;
		}

	}

	//頂点バッファのアンロック
	g_pVtxBuffRank->Unlock();
}