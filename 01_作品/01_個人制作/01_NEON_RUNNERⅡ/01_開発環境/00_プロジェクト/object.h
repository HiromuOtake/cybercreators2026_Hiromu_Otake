//======================================================
//
// 3Dスクロールアクション [object.h]
// Auther : 大竹熙
//
//======================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

// 全オブジェクト基底クラス
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_FIELD,
		TYPE_BULLET,
		TYPE_BLOCK,
		TYPE_NEEDLE,
		TYPE_ITEM,
		TYPE_BG,
		TYPE_MAX,
	}TYPE;
	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();									// 全オブジェクト解放
	static void UpdateAll();									// 全オブジェクト更新
	static void DrawAll();										// 全オブジェクト描画
	void SetType(TYPE type);									// タイプ設定
	TYPE GetType();												// タイプ取得
	//CObject* GETObject(int nPrio, int nObj);
	CObject* GetTop(int nPrio);
	void SetNext(CObject* pObject);
	CObject* GetNext();
	virtual void SetDeath();
	void SetUseDeath(bool bUseDeath);
	static void DeleateProcess();
	static const int m_MAXPRIORITY = 10;

	using BlockPair = std::unordered_map<std::string, std::vector<CObject*>>;
	static BlockPair& GetPair() { return m_pair; }	// ペアの取得

protected:
	void Release();												// 自分自身の解放
private:
	//static CObject* m_apObject[m_MAXPRIORITY][m_MAXOBJECT];		// オブジェクト管理
	static CObject* m_pTop[m_MAXPRIORITY];					// 先頭のオブジェクトのポインタ
	static CObject* m_pCur[m_MAXPRIORITY];					// 現在(最後尾)のポインタ
	CObject* m_pPrev;											// 前のオブジェクトのポインタ
	CObject* m_pNext;											// 次のオブジェクトのポインタ
	static int m_nNumAll;										// オブジェクト総数
	int m_nID;													// 自分自身のID
	int m_nPriority;											// 描画優先度
	bool m_Death;												// 死亡フラグ
	bool m_bUseDeath;
	TYPE m_Type;												// タイプ設定用

	static BlockPair m_pair;	// ハッシュマップ
};

#endif // !_OBJECT_H_