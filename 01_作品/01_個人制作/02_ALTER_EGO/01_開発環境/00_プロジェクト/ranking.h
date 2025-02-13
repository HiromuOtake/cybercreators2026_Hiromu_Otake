////==============================================
////
////ALTER_EGO[ranking.h]
////Author: hiromu otake
////
////==============================================
//
//#ifndef  _RANKING_H_
//#define  _RANKING_H_
//
//#include "manager.h"
//#include "scene.h"
//#include "object3D.h"
//
////#define NUM_RANK     (2)
//
//class CRanking : public CScene
//{
//public:
//	typedef struct
//	{
//		D3DXVECTOR3 pos;     //位置
//		int nScore;          //スコア
//		int nScorePos;		//テクスチャの位置
//		bool bRight;		//新しくランクインした場合点灯させる
//	}RankScore;
//
//	// 画面の種類
//	typedef enum
//	{
//		MODE_TITLE = 0,
//		MODE_TYUTORIAL,
//		MODE_GAME,
//		MODE_RESULT,
//		MODE_MAX,
//	}MODE;
//	CRanking();							// コンストラクタ
//	~CRanking()override;					// デストラクタ
//	HRESULT Init()override;				// 初期設定
//	void Uninit()override;				// 終了処理
//	void Update()override;				// 更新処理
//	void Draw()override;				// 描画処理
//	void ResetRanking();
//	void SetRanking(int nScore);
//	static const int m_RANK = 1;
//	static const int m_NUMBER = 8;
//	static constexpr float m_RANK_WIDTH = 50.0f;
//	static constexpr float m_RANK_HEIGHT = 50.0f;
//private:
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
//	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
//	RankScore m_aRankScore[m_RANK][m_NUMBER];       //ランキングスコア情報
//	int m_nRnkUpdate = -1;                             //更新ランクNo
//	int m_nTimerRanking;                               //ランキング画面表示タイマー
//};
//
//#endif 
