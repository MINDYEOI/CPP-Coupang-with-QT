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
	// �Էµ� ID�� ��ġ�ϴ� ��ǰ�� ã�Ƽ� �ش� ��ǰ�� �ڼ��� ������ ȭ�鿡 ���
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

	//Ű���忡�� ��ǰ ID�� �Է¹޾Ƽ�, master list���� ã��, ȭ�� ���
	int SearchItembyID()
	{
		int id;
		cout << "\tID : ";
		cin >> id;
		return SearchAndDisplayByID(id); // master list���� ã�� ȭ�� ���
	}

	// mater list�� ��� ��ǰ�� ȭ�����
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