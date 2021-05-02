#pragma once
#include<iostream>
#include <iomanip>
#include <iostream>
#include "DoublySortedLinkedList.h"
#include "DoublyIterator.h"

class BaseType
{
protected:
	static DoublySortedLinkedList<ItemType> m_List;		// ������ ����Ʈ (master list)

public:

	/**
*	@brief	Search the item by item code and Display the item.
*	@pre	List should be initialized
*	@post	none
*	@param	item code(id)
*	@return	if it works well return true, otherwise return false.
*/
	int SearchAndDisplayByID(int ID) 
	{
		if (m_List.GetLength() == 0) 
		{
			cout << "\n\t %% List is Empty %%\n";
			return 0;
		}

		DoublyIterator<ItemType> itor(m_List);
		ItemType item;
		item.SetCode(ID);
		for (itor.Begin(); itor.NotEnd(); itor.Next())
		{
			if (item == *itor.GetCurrentNode()) {
				itor.GetCurrentNode()->DisplayRecordOnScreen();
				return true;
			}

		}
		return false;
	}

	
		/**
*	@brief	Search the item by item code and Display the item.
*			Ű����� ��ǰ ID�� �Է¹޾� master list���� ã�� ȭ�� ���
*	@pre	List should be initialized
*	@post	none
*	@return	if it works well return true, otherwise return false.
*/
	int SearchItembyID()
	{
		int id;
		cout << "\tID : ";
		cin >> id;
		return SearchAndDisplayByID(id); // master list���� ã�� ȭ�� ���
	}


/**
*	@brief	Display all goods in the master list
*	@pre	List should be initialized
*	@post	none
*	@return	if it works well return true, otherwise return false.
*/
	void DisplayAllItem()
	{
		ItemType data;

		cout << "\n\tCurrent list" << endl;

		// list�� ��� �����͸� ȭ�鿡 ���
		DoublyIterator<ItemType> itor(m_List);
		for (itor.Begin(); itor.NotEnd(); itor.Next()) {
			itor.GetCurrentNode()->DisplayRecordOnScreen();
		}
	}
};