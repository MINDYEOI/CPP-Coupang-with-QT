#pragma once
#include<iostream>
#include <iomanip>
#include <iostream>
#include "DoublySortedLinkedList.h"
#include "DoublyIterator.h"

class BaseType
{
protected:
	static DoublySortedLinkedList<ItemType> m_List;		// 아이템 리스트 (master list)

public:
	// 입력된 ID와 일치하는 상품을 찾아서 해당 상품의 자세한 정보를 화면에 출력
	int SearchAndDisplayByID(int ID) {
		if (m_List.GetLength() == 0) {
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

	//키보드에서 상품 ID를 입력받아서, master list에서 찾아, 화면 출력
	int SearchItembyID()
	{
		int id;
		cout << "\tID : ";
		cin >> id;
		return SearchAndDisplayByID(id); // master list에서 찾아 화면 출력
	}

	// mater list의 모든 상품을 화면출력
	void DisplayAllItem()
	{
		ItemType data;

		cout << "\n\tCurrent list" << endl;

		// list의 모든 데이터를 화면에 출력
		DoublyIterator<ItemType> itor(m_List);
		for (itor.Begin(); itor.NotEnd(); itor.Next()) {
			itor.GetCurrentNode()->DisplayRecordOnScreen();
		}
	}
};