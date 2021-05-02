#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "BaseType.h"
#include "DoublySortedLinkedList.h"
#include "DoublyIterator.h"

using namespace std;

// �ϳ��� category ������ �����ϴ� class
// ������ ī�װ����� �ش� ī�װ��� �Ҽӵ� ��ǰ���� ID�� prodList�� �����
// �߰� ī�װ����� ���� ī�װ����� m_cateList�� �����


class CateType :public BaseType
{
private:
	string cateName;
	int cateID;
	DoublySortedLinkedList<CateType> m_cateList; // ī�װ� ����Ʈ
	DoublySortedLinkedList<int> prodList;	// product list
public:

	/**
*	@brief	If this category is terminal node, return true, otherwise return false.
*	@pre	List should be initialized.
*	@post	none
*	@return If this category is terminal node, return true, otherwise return false.
*/
	bool IsTerminal();

	/**
   *	@brief	Set a category information(id, name).
   *	@pre	none.
   *	@post	category id, name is set.
   */
	void SetCate(string _name, int _id);

	/**
*	@brief	Set a category id.
*	@pre	none.
*	@post	category id is set.
*/
	void SetCateID(int _id);

	/**
*	@brief	Set a category information(id, name) from keyboard.
*	@pre	none.
*	@post	category id, name is set.
*/
	void SetCateInfoFrKB(); // Ű���忡�� īŸ�� ���� �Է�


	/**
*	@brief	display current category.
*	@pre	Category should be initialized.
*	@post	none.
*/
	void DisplayCategory();

	/**
*	@brief	Add product to the terminal node from keyboard.
*	@pre	Category should be initialized, and terminal node should exist.
*	@post	none.
*/
	void AddProdFrKB();  
	//void AddProdFr(int _id);


	//void AddCateList(string _cateName, int _cateID);

	/**
*	@brief	Add product to the terminal node
*	@pre	Category should be initialized, and terminal node should exist.
*	@post	none.
*/
	void AddProductInTheCate(int _id);


	bool operator < (CateType& data)
	{
		if (this->cateID < data.cateID)
			return true;
		else
			return false;
	}
	bool operator > (CateType& data)
	{
		if (this->cateID > data.cateID)
			return true;
		else
			return false;
	}
	bool operator == (CateType& data)
	{
		if (this->cateID == data.cateID)
		{
			return true;
		}
		else
			return false;
	}

};



bool CateType::IsTerminal() // Terminal Node : �ڽ��� �ϳ��� ���� ���
{
	if (prodList.GetLength() != 0)
		return true;
	else
		return false;
}

void CateType::SetCate(string _name, int _id)
{
	cateID = _id;
	cateName = _name;
}

void CateType::SetCateID(int _id)
{
	cateID = _id;
}

void CateType::SetCateInfoFrKB() // Ű���忡�� īŸ�� ���� �Է�
{
	cout << "\n\t Sub_Category Name -->";
	cin >> cateName;
	cout << "\t Sub_Category ID -->";
	cin >> cateID;
}

// ���� ���� ��! m_cateList�� ī�װ� �߰�!
//	void CateType::AddCateList(string _cateName, int _cateID)
//	{
//		CateType cate;
//		cate.SetCate(_cateName, _cateID);
//		m_cateList.Add(cate);
//	}

void CateType::DisplayCategory() // display current category
{
	if (IsTerminal()) {  // display terminal node. ��ϵ� ��ǰ ������ ȭ�����
		DoublyIterator<int> itor(prodList);
		itor.Begin(); // �������� �̵�.
		cout << "\n\t %% " << cateName << " īŸ���� �Ҽӵ� ��ǰ�� ������ �����ϴ�.\n";
		for (itor.Begin(); itor.NotEnd(); itor.Next())
		{
			SearchAndDisplayByID(*itor.GetCurrentNode());
		}
	}
	else { // �߰� ����ī�װ�. ���� ī�װ� ����Ʈ�� ȭ�����
		DoublyIterator<CateType> itor(m_cateList);
		cout << "\n\t [ Display Sub_category List ]" << endl;
		for (itor.Begin(); itor.NotEnd(); itor.Next()) {
			cout << "\t �̸�: " << itor.GetCurrentNode()->cateName << " , ID: "
				<< itor.GetCurrentNode()->cateID << endl;
		}
	}
}




void CateType::AddProdFrKB()   // Add product to the terminal node from KB
{
	int id;
	cout << "\n\t Enter product ID -->";
	cin >> id;
	prodList.Add(id);
}

void CateType::AddProductInTheCate(int _id)
{
	prodList.Add(_id);
}
