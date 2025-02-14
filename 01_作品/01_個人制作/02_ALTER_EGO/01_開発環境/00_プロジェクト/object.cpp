//======================================================
//
// ALTER_EGO [object.cpp]
// Auther : 大竹熙
//
//======================================================

#include "object.h"

// 静的メンバ初期化
int CObject::m_nNumAll = 0;
CObject* CObject::m_pTop[m_MAXPRIORITY] = { nullptr };
CObject* CObject::m_pCur[m_MAXPRIORITY] = { nullptr };

// 静的オブジェクト
std::unordered_map<std::string, std::vector<CObject*>> CObject::m_pair;

//======================================================
// コンストラクタ (自分自身の登録)
//======================================================
CObject::CObject(int nPriority) : m_nPriority(0), m_Type(TYPE_NONE), m_Death(false),m_bUseDeath(false)
{
	m_nPriority = nPriority;

	m_nNumAll++;									// 総数をカウントアップ

	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = this;					// オブジェクト(自身)をリストに追加
		m_pPrev = nullptr;							// 一番最初のオブジェクトなので前も次も無し
	}
	else
	{
		CObject* pCur = m_pCur[nPriority];
		pCur->SetNext(this);
		m_pPrev = pCur;								// カレントを更新する前にプレビューに情報を渡す
	}

	m_pCur[nPriority] = this;					// 自分が最新なので自分の情報をいれる
	m_pNext = nullptr;							// 一番最新のオブジェクトなので次は無し
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
			if (pObj != nullptr)  // nullptrチェック
			{
 				pObj->Update();
			}
			pObj = pNext;
		}
	}
	DeleateProcess();
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
}

//======================================================
// 自分自身の解放
//======================================================
void CObject::Release()
{
	if (this == nullptr) return;

	
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

	m_pNext = nullptr;
	m_pPrev = nullptr;

	m_nNumAll--;	// 総数をカウントダウン

	delete this;
}

//======================================================
// 死亡フラグの設定
//======================================================
void CObject::SetDeath()
{
	if (m_Death == false)
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

//======================================================
// ペアにオブジェクトを追加
//======================================================
void CObject::AddToPair(const std::string& key, CObject* object)
{
	if (!object || key.empty())
		return;

	// 重複登録を防ぐ
	auto& objects = m_pair[key];
	if (std::find(objects.begin(), objects.end(), object) == objects.end())
	{
		objects.push_back(object);
	}
}

void CObject::RemoveFromPair(const std::string& key, CObject* object)
{
	if (m_pair.count(key) == 0)
		return;

	auto& objects = m_pair[key];
	objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());

	// リストが空になったらエントリ自体を削除
	if (objects.empty())
	{
		m_pair.erase(key);
	}
}

std::vector<CObject*>& CObject::GetPairObjects(const std::string& key)
{
	return m_pair[key];
}

std::vector<CObject*> CObject::GetAllObjects()
{
	std::vector<CObject*> objects;

	for (int nCnt = 0; nCnt < m_MAXPRIORITY; ++nCnt)
	{
		CObject* pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			objects.push_back(pObj); // 現在のオブジェクトをリストに追加
			pObj = pObj->GetNext();
		}
	}

	return objects;
}

CObject* CObject::FindFirstOfType(TYPE type)
{
	auto objects = GetAllObjects();

	for (auto* obj : objects)
	{
		if (obj->GetType() == type)
		{
			return obj; // 最初に一致するオブジェクトを返す
		}
	}

	return nullptr; // 見つからなかった場合
}