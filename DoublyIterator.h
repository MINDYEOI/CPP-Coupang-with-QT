#pragma once

#include "DoublySortedLinkedList.h"

template <typename T>
struct DoublyNodeType;
template<typename T>
class DoublySortedLinkedList;


template <typename T>
class DoublyIterator
{
	friend class DoublySortedLinkedList<T>;

private:
	const DoublySortedLinkedList<T>& m_List;
	DoublyNodeType<T>* m_pCurNode;	// m_pCurPointer

public:
	DoublyIterator(const DoublySortedLinkedList<T>& list)
		: m_List(list), m_pCurNode(list.m_pFirst) {};

	void Begin()
	{
		m_pCurNode = m_List.m_pFirst->next;
	}

	void Next()
	{
		m_pCurNode = m_pCurNode->next;
	}
	
	void Prev()
	{
		m_pCurNode = m_pCurNode->prev;
	}

	// 현재 노드(m_pCurNode)의 data의 주소를 리턴
	T* GetCurrentNode()
	{
		return &m_pCurNode->data;
	}

	bool NotEnd()
	{
		if (m_pCurNode->next == nullptr) return false;
		else	return true;
	}
};