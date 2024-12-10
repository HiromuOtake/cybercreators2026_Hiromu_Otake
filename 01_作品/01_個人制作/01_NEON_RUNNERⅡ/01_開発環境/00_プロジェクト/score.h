//==============================================
//
//STG制作[score.h]
//Author: hiromu otake
//
//==============================================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "manager.h"
#include "object2D.h"
#include "number.h"

//==============================================
//マクロ定義
//==============================================

#define MAX_POS    (100.0f)
#define MAX_POS2   (200.0f)
#define MAX_POS3   (200.0f)
#define MAX_POS4   (300.0f)


//==============================================
//プロトタイプ宣言
//==============================================
class CScore : public CObject2D
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;     //位置
		int nDigit;
	}Score;
	CScore(int nPriority = 0);
	~CScore();
	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void SetScore(int nScore);
	void AddScore(int nValue);
	void SddScore(int nValue);
	int GetScore(void);
	static CScore* Create(float fpos, float fposX, float fposY, float fsizeX, float fsizeY);
	void SetDeath()override;
	static const int m_MAX_SCORE = 8;
	void SaveSetScore(int nScore);
	int GetSaveScore();
	int m_nScore;							//スコアの値
private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	static int m_SaveScore;					// スコア保存用の変数
	CNumber* m_pNumber[m_MAX_SCORE];
};

#endif 