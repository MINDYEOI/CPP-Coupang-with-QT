#pragma once
#include "ItemType.h"
#include "DoublyIterator.h"

template<typename T>
class DoublyIterator;


/* NodeType */
template <typename T>
struct DoublyNodeType
{
	T data;					// 노드의 데이터
	DoublyNodeType* prev;	// 앞노드 포인터
	DoublyNodeType* next;	// 뒷노드 포인터
};

/* 정렬된 더블연결리스트 */
template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>;

private:
	DoublyNodeType<T>* m_pFirst;	// 리스트 첫 노드
	DoublyNodeType<T>* m_pLast;		// 리스트 마지막 노드
	int m_nLength;		// 리스트의 길이

public:
	DoublySortedLinkedList()
	{
		m_pFirst = NULL;
		m_pLast = NULL;
		m_nLength = 0;
		// 생성자에서 DoublySortedLinkedList 구조를 만들어줘야 하니까
		//  m_pFirst->next = m_pLast, m_pLast->prev = m_pFrist 도 해야하긴 하는데
		// 여기서 m_pFirst->next = m_pLast, m_pLast->prev = m_pFrist 를 하면
		// 계속 초기화가 되므로, 이게 필요한 함수에서 각각 정의해줘야 함!
		// (예: Add)

	}

	~DoublySortedLinkedList()
	{
		delete m_pFirst;
		delete m_pLast;
	}

	/**
* @brief   Check this list is empty or not.
* @pre     none.
* @post    none.
* @return  if the iist is empty, return true, otherwise return false.
*/
	bool IsEmpty();

	/**
* @brief	Make the list empty.
* @pre		The list is allocated.
* @post		The list is empty.
*/
	void MakeEmpty();

	/**
* @breif	Return the item number in the list.
* @pre		none.
* @post		none.
* @return	the item number in the list.
*/
	int GetLength() const;


	/**
	* @brief	Add the item in the list.
	* @pre		The list doesn't have the item. (The list can't be 'full' because it is linked list!)
	* @post		The item is added.
	* @param	The item which is added in the list.
	* @return	If this function works well, return true, otherwise return false.
	*/
	int Add(T item);

	/**
	* @brief	Delete the item in the list.
	* @pre		The list is not empty and have the item.
	* @post		The item is deleted.
	* @param	The item which is deleted in the list.
	* @return	If this function works well, return true, otherwise return false.
	*/
	bool Delete(T item);

	/**
* @brief	Replace the item in the list.
* @pre		The list has the item.
* @post		The item information is changed.
* @param	The item which information will be changed.
* @return	If this function works well, return true, otherwise return false.
*/
	bool Replace(T item);

	/**
*	@brief	Retrieve list element whose key matches item's key (if present).
*			(item에 전달된 키와 일치하는 레코드를 복사하여 리턴)
*	@pre	Key member of item is initialized.
*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
*   @param	The item which want to retrieve in the list.
*	@return	1 if any element's primary key matches with item's, otherwise 0.
*/
	int Get(T& item); 

		/**
	*	@brief	Retrieve list element pointer whose key matches item's key (if present).
	*			(item에 전달된 키와 일치하는 레코드 포인터 리턴)
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*   @param	The item which want to retrieve in the list.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	T* GetPtr(T& item);

	DoublyNodeType<T>* GetFirstNode() { return m_pFirst; };
};

template <typename T>
bool DoublySortedLinkedList<T>::IsEmpty()
{
	if (m_nLength == 0)
		return true;
	else
		return false;
}


template <typename T>
void DoublySortedLinkedList<T>::MakeEmpty()
{
	DoublyNodeType<T>* pItem;
	DoublyIterator<T> itor(*this);
	itor.Begin();

	while (itor.NotEnd())
	{
		pItem = itor.m_pCurNode;
		itor.Next();
		delete pItem;
	}

	m_pFirst->next = m_pLast;
	m_pFirst->prev = NULL;
	m_pLast->next = NULL;
	m_pLast->prev = m_pFirst;
	m_nLength = 0;
}

template <typename T>
int DoublySortedLinkedList<T>::GetLength() const
{
	return m_nLength;
}

template <typename T>
int DoublySortedLinkedList<T>::Add(T item)
{
	DoublyIterator<T> itor(*this);
	if (m_nLength == 0)	// list에 아무것도 없을 때
	{
		// 동적할당
		m_pFirst = new DoublyNodeType<T>;
		m_pLast = new DoublyNodeType<T>;
		
		m_pFirst->next = m_pLast;
		m_pFirst->prev = NULL;
		m_pLast->next = NULL;
		m_pLast->prev = m_pFirst;

		DoublyNodeType<T>* pItem = new DoublyNodeType<T>;
		pItem->data = item;
		pItem->prev = m_pFirst;
		pItem->next = m_pLast;
		m_pFirst->next = pItem;
		m_pLast->prev = pItem;
		m_nLength++;
	}
	else
	{
		for (itor.Begin(); itor.NotEnd(); itor.Next())
		{
			if (item < *itor.GetCurrentNode())	// ★  GetCurrentNode는 Node Data의 주소를 반환하므로 *itor.GetCurrentNode()
				break;
			else if (item == *itor.GetCurrentNode()) //  ★  GetCurrentNode는 Node Data의 주소를 반환하므로 *itor.GetCurrentNode()
			{
				cout << "\t 이미 존재하는 상품입니다.\n";
				return 0;
			}
		}

		DoublyNodeType<T>* pItem = new DoublyNodeType<T>;
		pItem->data = item;
		pItem->prev = itor.m_pCurNode->prev;
		pItem->next = itor.m_pCurNode;
		itor.m_pCurNode->prev->next = pItem;
		itor.m_pCurNode->prev = pItem;
		m_nLength++;
	}
	return 1;
}

template <typename T>
bool DoublySortedLinkedList<T>::Delete(T item)
{
	DoublyIterator<T> itor(*this);
	bool bIsit = false;
	for (itor.Begin(); itor.NotEnd(); itor.Next())
	{
		if (itor.m_pCurNode->data == item)
		{
			DoublyNodeType<T>* pItem = new DoublyNodeType<T>;
			pItem = itor.m_pCurNode;
			itor.Next();
			pItem->prev->next = itor.m_pCurNode;
			itor.m_pCurNode->prev = pItem->prev;
			delete pItem;
			m_nLength--;
			bIsit = true;
			break;
		}
	}
	if (bIsit == true)
		return  true;
	else
		return false;
}

template <typename T>
bool DoublySortedLinkedList<T>::Replace(T item)
{
	DoublyIterator<T> itor(*this);
	
	for (itor.Begin(); itor.NotEnd(); itor.Next())
	{
		if (itor.m_pCurNode->data == item)
		{
			itor.m_pCurNode->data = item;
			return true;
		}
	}

	return false;
}

template <typename T>
int DoublySortedLinkedList<T>::Get(T& item)	// == Retrieve
{
	DoublyIterator<T> itor(*this);
	for (itor.Begin(); itor.NotEnd(); itor.Next())
	{
		if (*itor.GetCurrentNode() == item)
		{
			item = *itor.GetCurrentNode();
			return true;
		}
	}

	return false;
}

template <typename T>
T* DoublySortedLinkedList<T>::GetPtr(T& item)
{
	DoublyIterator<T> itor(*this);
	for (itor.Begin(); itor.NotEnd(); itor.Next())
	{
		if (*itor.GetCurrentNode() == item)
		{
			return itor.GetCurrentNode();
		}
	}

	return NULL;
}

