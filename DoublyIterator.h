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

	/**
*	@brief	Make the current node point list's first node's next node
*	@pre	m_List should be initialized.
*	@post	current node is first node's next node in the list.
*/
	void Begin()
	{
		m_pCurNode = m_List.m_pFirst->next;
	}

	/**
*	@brief	Make the current node go to next node
*	@pre	m_List should be initialized.
*	@post	m_pCurNode = m_pCurNode->next;
*/
	void Next()
	{
		m_pCurNode = m_pCurNode->next;
	}
	
	/**
*	@brief	Make the current node go to previous node
*	@pre	m_List should be initialized.
*	@post	m_pCurNode = m_pCurNode->prev;
*/
	void Prev()
	{
		m_pCurNode = m_pCurNode->prev;
	}

	/**
*	@brief	Return the current node's address
*			(현재 노드(m_pCurNode)의 data의 주소를 리턴)
*	@pre	m_List should be initialized.
*	@post	none
*	@return current node's data adrress
*/
	T* GetCurrentNode()
	{
		return &m_pCurNode->data;
	}

	/**
*	@brief	Check whether the node is at the end or not
*	@pre	m_List should be initialized.
*	@post	none
*	@return if the node is not at the end, return true, otherwise return false
*/
	bool NotEnd()
	{
		if (m_pCurNode->next == nullptr) return false;
		else	return true;
	}
};