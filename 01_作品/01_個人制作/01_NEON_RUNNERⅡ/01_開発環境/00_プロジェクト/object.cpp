//======================================================
//
// 3Dスクロールアクション [object.cpp]
// Auther : 大竹熙
//
//======================================================

#include "object.h"

// 静的メンバ初期化
int CObject::m_nNumAll = 0;
//CObject* CObject::m_apObject[m_MAXPRIORITY][m_MAXOBJECT] = {};
CObject* CObject::m_pTop[m_MAXPRIORITY] = {};
CObject* CObject::m_pCur[m_MAXPRIORITY] = {};

// 静的オブジェクト
std::unordered_map<std::string, std::vector<CObject*>> CObject::m_pair;

//======================================================
// コンストラクタ (自分自身の登録)
//======================================================
CObject::CObject(int nPriority) : m_nPriority(0), m_Type(TYPE_NONE), m_Death(false),m_bUseDeath(false)
{
	m_nPriority = nPriority;

	m_nNumAll++;							// 総数をカウントアップ

	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = this;					// オブジェクト(自身)をリストに追加
		m_pCur[nPriority] = this;					// オブジェクト(自身)をリストに追加
		m_pPrev = nullptr;							// 一番最初のオブジェクトなので前も次も無し
		m_pNext = nullptr;							// 一番最初のオブジェクトなので前も次も無し
	}
	else
	{
		m_pNext = nullptr;							// 一番最新のオブジェクトなので次は無し
		CObject* pCur = m_pCur[nPriority];
		pCur->SetNext(this);
		m_pPrev = pCur;								// カレントを更新する前にプレビューに情報を渡す
		m_pCur[nPriority] = this;					// 自分が最新なので自分の情報をいれる
	}
}

//======================================================
// デストラクタ
//======================================================
CObject::~CObject()
{

}

//======================================================
// 全オブジェクト解放
//======================================================
void CObject::ReleaseAll()
{
	m_pair.clear();

	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->SetDeath();
			pObj = pNext;
		}
	}

	//for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	//{
	//	CObject* pObj = m_pTop[nCnt];		// 先頭取得

	//	// 最大数が不明なのでWhileを使用
	//	while (pObj != nullptr)
	//	{
	//		CObject* pNext = pObj->m_pNext;
	//		if (pObj->m_Death == true)
	//		{
	//			pObj->Uninit();
	//			pObj->Release();
	//			pObj = nullptr;

	//		}
	//		pObj = pNext;
	//	}
	//}

	//for (int nCntPriority = 0; nCntPriority < m_MAXPRIORITY; nCntPriority++)
	//{
	//	for (int nCnt = 0; nCnt < m_MAXOBJECT; nCnt++)
	//	{
	//
	//		if (m_apObject[nCntPriority][nCnt] != nullptr)
	//		{
	//			m_apObject[nCntPriority][nCnt]->Uninit();
	//		}
	//	}
	//}
}

//======================================================
// 全オブジェクト更新
//======================================================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];		// 先頭取得
	
		// 最大数が不明なのでWhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Update();
			pObj = pNext;
		}
	}

	DeleateProcess();

	//for (int nCntPriority = 0; nCntPriority < m_MAXPRIORITY; nCntPriority++)
	//{
	//	for (int nCnt = 0; nCnt < m_MAXOBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPriority][nCnt] != nullptr)
	//		{
	//			m_apObject[nCntPriority][nCnt]->Update();
	//		}
	//	}
	//}
}

//======================================================
// 全オブジェクト描画
//======================================================
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];
	
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Draw();
			pObj = pNext;
		}
	}

	//for (int nCntPriority = 0; nCntPriority < m_MAXPRIORITY; nCntPriority++)
	//{
	//	for (int nCnt = 0; nCnt < m_MAXOBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPriority][nCnt] != nullptr)
	//		{
	//			m_apObject[nCntPriority][nCnt]->Draw();
	//		}
	//	}
	//}
}

//======================================================
// 自分自身の解放
//======================================================
void CObject::Release()
{
	m_nNumAll--;	// 総数をカウントダウン
	
	if (m_Type == TYPE_BG)
	{

		int n = 0;
	}

	if (m_pPrev != nullptr)
	{
		m_pPrev->m_pNext = m_pNext;
	}
	else
	{
		m_pTop[m_nPriority] = m_pNext;
	}

	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;
	}
	else
	{
		m_pCur[m_nPriority] = m_pPrev;
	}
	
	delete this;
}

//======================================================
// 死亡フラグの設定
//======================================================
void CObject::SetDeath()
{
	if (m_bUseDeath == true)
	{
		m_Death = true;
	}
}

//======================================================
// 死亡フラグを使用するかどうか
//======================================================
void CObject::SetUseDeath(bool bUseDeath)
{
	m_bUseDeath = bUseDeath;
}

//======================================================
// 死亡フラグ発動処理
//======================================================
void CObject::DeleateProcess()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];		// 先頭取得

		// 最大数が不明なのでWhileを使用
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			if (pObj->m_Death == true)
			{
				pObj->Uninit();
				pObj->Release();
			}
			pObj = pNext;
		}
	}
}

//======================================================
// タイプの設定
//======================================================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}

//======================================================
// タイプの取得
//======================================================
CObject::TYPE CObject::GetType()
{
	return m_Type;
}

////======================================================
//// オブジェクトの取得
////======================================================
//CObject* CObject::GETObject(int nPrio,int nObj)
//{
//	return m_apObject[nPrio][nObj];
//}

//======================================================
// オブジェクトの取得
//======================================================
CObject* CObject::GetTop(int nPrio)
{
	return m_pTop[nPrio];
}

//======================================================
// 次のオブジェクトの設定
//======================================================
void CObject::SetNext(CObject* pObject)
{
	m_pNext = pObject;
}

//======================================================
// 次のオブジェクトの取得
//======================================================
CObject* CObject::GetNext()
{
	return m_pNext;
}