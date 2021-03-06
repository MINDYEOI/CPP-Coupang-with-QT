#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "BaseType.h"
#include "DoublySortedLinkedList.h"
#include "DoublyIterator.h"

using namespace std;

// 하나의 category 정보만 저장하는 class
// 마지막 카테고리에는 해당 카테고리에 소속된 상품들의 ID가 prodList에 저장됨
// 중간 카테고리에는 서브 카테고리들이 m_cateList에 저장됨


class CateType :public BaseType
{
private:
	string cateName;
	int cateID;
	DoublySortedLinkedList<CateType> m_cateList; // 카테고리 리스트
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
	void SetCateInfoFrKB(); // 키보드에서 카타고리 정보 입력


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



bool CateType::IsTerminal() // Terminal Node : 자식이 하나도 없는 노드
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

void CateType::SetCateInfoFrKB() // 키보드에서 카타고리 정보 입력
{
	cout << "\n\t Sub_Category Name -->";
	cin >> cateName;
	cout << "\t Sub_Category ID -->";
	cin >> cateID;
}

// 내가 만든 거! m_cateList에 카테고리 추가!
//	void CateType::AddCateList(string _cateName, int _cateID)
//	{
//		CateType cate;
//		cate.SetCate(_cateName, _cateID);
//		m_cateList.Add(cate);
//	}

void CateType::DisplayCategory() // display current category
{
	if (IsTerminal()) {  // display terminal node. 등록된 상품 정보를 화면출력
		DoublyIterator<int> itor(prodList);
		itor.Begin(); // 다음으로 이동.
		cout << "\n\t %% " << cateName << " 카타고리에 소속된 상품은 다음과 같습니다.\n";
		for (itor.Begin(); itor.NotEnd(); itor.Next())
		{
			SearchAndDisplayByID(*itor.GetCurrentNode());
		}
	}
	else { // 중간 서브카테고리. 서브 카테고리 리스트를 화면출력
		DoublyIterator<CateType> itor(m_cateList);
		cout << "\n\t [ Display Sub_category List ]" << endl;
		for (itor.Begin(); itor.NotEnd(); itor.Next()) {
			cout << "\t 이름: " << itor.GetCurrentNode()->cateName << " , ID: "
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
