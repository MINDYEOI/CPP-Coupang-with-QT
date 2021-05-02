#pragma once
#include "ItemType.h"
#include "DoublyIterator.h"

template<typename T>
class DoublyIterator;


/* NodeType */
template <typename T>
struct DoublyNodeType
{
	T data;					// ����� ������
	DoublyNodeType* prev;	// �ճ�� ������
	DoublyNodeType* next;	// �޳�� ������
};

/* ���ĵ� �������Ḯ��Ʈ */
template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>;

private:
	DoublyNodeType<T>* m_pFirst;	// ����Ʈ ù ���
	DoublyNodeType<T>* m_pLast;		// ����Ʈ ������ ���
	int m_nLength;		// ����Ʈ�� ����

public:
	DoublySortedLinkedList()
	{
		m_pFirst = NULL;
		m_pLast = NULL;
		m_nLength = 0;
		// �����ڿ��� DoublySortedLinkedList ������ �������� �ϴϱ�
		//  m_pFirst->next = m_pLast, m_pLast->prev = m_pFrist �� �ؾ��ϱ� �ϴµ�
		// ���⼭ m_pFirst->next = m_pLast, m_pLast->prev = m_pFrist �� �ϸ�
		// ��� �ʱ�ȭ�� �ǹǷ�, �̰� �ʿ��� �Լ����� ���� ��������� ��!
		// (��: Add)

	}

	~DoublySortedLinkedList()
	{
		delete m_pFirst;
		delete m_pLast;
	}

	bool IsEmpty();

	void MakeEmpty();

	int GetLength() const;

	int Add(T item);

	bool Delete(T item);

	bool Replace(T item);

	int Get(T& item); // item�� ���޵� Ű�� ��ġ�ϴ� ���ڵ带 �����Ͽ� ����

	T* GetPtr(T& item); // item�� ���޵� Ű�� ��ġ�ϴ� ���ڵ� ������ ����

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
	if (m_nLength == 0)	// list�� �ƹ��͵� ���� ��
	{
		// �����Ҵ�
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
			if (item < *itor.GetCurrentNode())	// ��  GetCurrentNode�� Node Data�� �ּҸ� ��ȯ�ϹǷ� *itor.GetCurrentNode()
				break;
			else if (item == *itor.GetCurrentNode()) //  ��  GetCurrentNode�� Node Data�� �ּҸ� ��ȯ�ϹǷ� *itor.GetCurrentNode()
			{
				cout << "\t �̹� �����ϴ� ��ǰ�Դϴ�.\n";
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
