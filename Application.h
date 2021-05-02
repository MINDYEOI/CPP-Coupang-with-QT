#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "BaseType.h"
#include "DoublySortedLinkedList.h"
#include "CategoryType.h"
#include "BasketType.h"
using namespace std;

class Application:public BaseType
{
private:
    ifstream m_inFile;	// input file descriptor
    ofstream m_outFile;	// output file descriptor
    DoublySortedLinkedList<ItemType> m_List;	// masterList
    DoublySortedLinkedList<CateType> m_cate;
    BasketType m_basket;
    int m_Command;		// current command number

public:
    Application()
    {
        m_Command = 0;
    }
    ~Application() {}

    /*
*	@brief	Open a file by file descriptor as an inputput file.
*	@pre	list should be initialized.
*	@post	open the file for writing.
*	@param	fileName	a filename to open for writing.
*	@return	return true if this function works well, otherwise false.
*/
    bool OpenInFile(string fileName);


    /*
    *	@brief	Open a file by file descriptor as an output file.
    *	@pre	list should be initialized.
    *	@post	open the file for writing.
    *	@param	fileName	a filename to open for writing.
    *	@return	return true if this function works well, otherwise false.
    */
    bool OpenOutFile(string fileName);

    /*
*	@brief	Open a file as a write mode, and write all data into the file,
*	@pre	The file is not opened.
*	@post	the list is stored in the output file.
*	@return	return true if this function works well, otherwise false.
*/
    bool WriteDataToFile();


    /*
*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
*	@pre	The file is not opened.
*	@post	list holds all records from the file.
*	@return	return true if this function works well, otherwise false.
*/
    bool ReadDataFromFile(string filename);


    /*
    *	@brief	Display command on screen and get a input from keyboard.
    *	@pre	none.
    *	@post	none.
    *	@return	user's command.
    */
    int GetCommand();

    /**
*	@brief	Manage the basket.
*	@pre	basket should be initialized.
*	@post	basket may be changed.
*	@return	return true if this function works well, otherwise false.
*/
    bool ManageBasket();

    /**
*	@brief	Manage the category.
*	@pre	The category should be initialized.
*	@post	The category may be changed
*	@return	return true if this function works well, otherwise false.
*/
    int ManageCategory();

    void RunCategory(int select);

    /*
*	@brief	Display All content data from list.
*	@pre	list should be initialized.
*	@post	none.
*	@return	return true if this function works well, otherwise false.
*/
    bool DisplayAllRecords();

    /**
*  @brief  Clear List.
*  @pre    none.
*  @post   list is empty.
*/
    void MakeEmpty();

    /*
*	@brief	Add new content into list. Target content is set with Keyboard input.
*	@pre	list should be initialized.
*	@post	new content is added into the list.
*	@return	return true if this function works well, otherwise false.
*/
    bool AddProduct();


    /*
     *  @brief  Run application.
     *  @pre    application is started.
     *  @post   application is finished.
     */
    void Run();

    /*
*	@brief  Search a record by name entered by keyboard.
*	@pre	list must have one or more item.
*	@post	none.
*	@return	return true if this function works well, otherwise false.
*/
    bool RetrieveProductByName();

    /*
*	@brief  Delete a record by using resident number entered by keyboard.
*	@pre	list must have one or more item.
*	@post	none.
*	@return	return true if this function works well, otherwise false.
*/
    bool DeleteProduct();

    /*
*	@brief  Replace a record by using a record entered by keyboard.
*	@pre	list must have one or more item.
*	@post	none.
*	@return	return true if this function works well, otherwise false.
*/
    bool ReplaceProduct();


    bool DisplayCateProducts();
    bool DisplayCateName();
    bool FindTheProduct();
    bool GoToSubCate();
    bool AddCate();
    bool AddProd();
};

/*
*	@brief	Open a file by file descriptor as an inputput file.
*	@pre	list should be initialized.
*	@post	open the file for writing.
*	@param	fileName	a filename to open for writing.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::OpenInFile(string fileName)
{
    m_inFile.open(fileName);
    if (m_inFile) // Check opened file valid
    {
        return true;
    }

    cout << "\n\t [!]ERROR There's no such File" << endl;
    return false;
}


/*
*	@brief	Open a file by file descriptor as an output file.
*	@pre	list should be initialized.
*	@post	open the file for writing.
*	@param	fileName	a filename to open for writing.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::OpenOutFile(string fileName)
{
    m_outFile.open(fileName);

    if (m_outFile) // Check opened file valid
    {
        return true;
    }

    return false;
}

/*
*	@brief	Open a file as a write mode, and write all data into the file,
*	@pre	The file is not opened.
*	@post	the list is stored in the output file.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::WriteDataToFile()
{
    int length = m_List.GetLength();
    if (length <= 0)
    {
        cout << "\n\t [!]ERROR There's no data to save" << endl;
        return false;
    }

    string fileName;

    cout << "\n\t Enter a Filename to Save : ";
    cin >> fileName;

    if (!OpenOutFile(fileName)) return false;

    ItemType data;
    DoublyIterator<ItemType> itor(m_List);
    bool hasInvalidData = false;
    int index;


    for(itor.Begin(); itor.NotEnd(); itor.Next())
    {
        if (!data.WriteDataToFile(m_outFile)) // Write only valid data
        {
            hasInvalidData = true;
        }
    }

    if (hasInvalidData) // If invalid data exist, show below error
    {
        cout << "\n\t [!] There's data that has not been written due to invalid element value" << endl;
    }

    m_outFile.close();
    cout << "\n\t " << length << " data have been successfully saved as '" << fileName << "'" << endl;

    return true;
}


/*
*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
*	@pre	The file is not opened.
*	@post	list holds all records from the file.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::ReadDataFromFile(string filename)
{
    ItemType readData;

    if (!OpenInFile(filename)) return false;

    bool hasMissingData = false;
    int readDataCount = 0;
    while (!m_inFile.eof())
    {
        if (readData.ReadDataFromFile(m_inFile)) // Add only valid data
        {

            m_List.Add(readData);
            readDataCount++;
        }
        else
        {
            hasMissingData = true;
        }
    }

    if (hasMissingData) // If missing data exist, show below error
    {
        cout << "\n\t [!] There's missing data due to invalid element \n";
        return false;
    }

    m_inFile.close();
    cout << "\n\t " << readDataCount << " data have been successfully read from '"
        << filename << "'" << endl;


    DisplayAllRecords();
    return true;
}


/*
*	@brief	Display command on screen and get a input from keyboard.
*	@pre	none.
*	@post	none.
*	@return	user's command.
*/
int Application::GetCommand()
{

    int select;
    while (1) {

        cout << "\t=" << setw(WIDTH + 1) << setfill('=') << "=\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  0: Quit" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  1: Display All Records" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  2: Read data from file" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  3: Empty Data in List" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  4: Add a Record" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  5: Delete a Record" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  6: Replace a Record" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  7: Retrieve by name" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  8: Manage the basket" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  9: Go to category" << "|\n";

        cout << "\t=" << right << setw(WIDTH + 1) << setfill('=') << "=\n";
        cout << "\t  Select a function --> ";

        if (cin.fail() || !(cin >> select) || select < 0 || select>MAXCOMMANDS)	// input fail or input value is out of bound
        {
            cout << "\t    ### Invalid Command Number. Select again  ####" << endl;
            cin.clear();	//clear flag
            cin.ignore(INT_MAX, '\n');	//empty input buffer
        }
        else {
            cin.clear();  // clear flag
            cin.ignore(INT_MAX, '\n');  // empty input buffer
            return select;
        }
    }
}

/*
 *  @brief  Run application.
 *  @pre    application is started.
 *  @post   application is finished.
 */
void Application::Run()
{
    string datafile = "a.txt";
    
    
    while (true)
    {
        m_Command = GetCommand(); // Get command value from keyboard

        // Command execution
        switch (m_Command)
        {
        case 0:
            return;
        case 1:// display all records on screen
            DisplayAllRecords();
            break;
        case 2:
            ReadDataFromFile(datafile);
            break;
        case 3: // empty list
            MakeEmpty();
            break;
        case 4: // add a record to list
            AddProduct();

            break;
        case 5:	// delete a record
            DeleteProduct();
            break;
        case 6: // Replace a record
            ReplaceProduct();
            break;
     
        case 7:
            RetrieveProductByName();
            break;

        case 8:
            ManageBasket();
            break;

        case 9:
            ManageCategory();
            break;

        default:
            cout << "\t [!]ERROR Illegal selection...\n";
            break;
        }
    }
}

/**
*	@brief	Manage the basket.
*	@pre	basket should be initialized.
*	@post	basket may be changed.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::ManageBasket()
{
    m_basket.ManageBasket(m_List);
    return true;
}

/**
*	@brief	Manage the category.
*	@pre	The category should be initialized.
*	@post	The category may be changed
*	@return	return true if this function works well, otherwise false.
*/
int Application::ManageCategory()
{
     CateType temp;
     // 카테고리 등록
     temp.SetCate("Home",10);
     m_cate.Add(temp);
     // 서브 카테고리 등록
     CateType* motherCatePtr = m_cate.GetPtr(temp);
     motherCatePtr->AddProductInTheCate(1011);
     motherCatePtr->AddProductInTheCate(1012);
     motherCatePtr->AddProductInTheCate(1021);
     motherCatePtr->AddProductInTheCate(1031);
     motherCatePtr->AddProductInTheCate(1032);
     // motherCatePtr->AddCateList("Kitchen", 101);
     // motherCatePtr->AddProductInTheCate(1011);
     // motherCatePtr->AddProductInTheCate(1012);
     // motherCatePtr->AddCateList("Bath", 102);
     // motherCatePtr->AddProductInTheCate(1021);
     // motherCatePtr->AddCateList("Home decor", 103);
     // motherCatePtr->AddProductInTheCate(1031);
     // motherCatePtr->AddProductInTheCate(1032);
     
     
     // 카테고리 등록
     temp.SetCate("Eletronics", 20);
     m_cate.Add(temp);
     // 서브 카테고리 등록
     //motherCatePtr->AddCateList("TV", 201);
     motherCatePtr->AddProductInTheCate(2011);
     motherCatePtr->AddProductInTheCate(2012);
    // motherCatePtr->AddCateList("Cell Phones", 202);
     motherCatePtr->AddProductInTheCate(2021);
     motherCatePtr->AddProductInTheCate(2022);
     //motherCatePtr->AddCateList("Laptops", 203);
     motherCatePtr->AddProductInTheCate(2031);
     motherCatePtr->AddProductInTheCate(2032);
     
    int select;
    while (1) {
        cout << endl << endl;
        cout << "\t=" << setw(WIDTH + 1) << setfill('=') << "=\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  0: Quit" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  1: Display the product" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  2: Display the category in this layer" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  3: Add the product" << "|\n";
        cout << "\t=" << right << setw(WIDTH + 1) << setfill('=') << "=\n";
        cout << "\t  Select a function --> ";
        cin >> select;
        if (cin.fail() || !(cin >> select) || select < 0 || select>4)	// input fail or input value is out of bound
        {
            cout << "\t    ### Invalid Command Number. Select again  ####" << endl;
            cin.clear();	//clear flag
            cin.ignore(INT_MAX, '\n');	//empty input buffer
        }
        else {
            cin.clear();  // clear flag
            cin.ignore(INT_MAX, '\n');  // empty input buffer
            RunCategory(select);
        }

}

}
void Application::RunCategory(int select)
{

    // Command execution
    switch (select)
    {
    case 0:
        return;

    case 1:
        // 카테고리에 있는 물건 출력
        DisplayCateProducts();
        break;

    case 2:
        // 지금 계층에 있는 카테고리들 출력
        DisplayCateName();      break;

    case 3:
        // 현재 카테고리에 상품 추가하기
        AddProd();
        break;
    default:
        cout << "\t [!]ERROR Illegal selection...\n";
        break;
    }
}

// 검색을 원하는 카테고리 ID를 입력받아서 
// 해당 카테고리의 모든 상품의 자세한 정보를 화면에 출력
bool Application::DisplayCateProducts()
{
    CateType temp;
    int id;
    cout << "\n\t Home : 10   |  Eletronics : 20\n";
    cout << "\n\t Enter the Category ID : ";
    cin >> id;
    temp.SetCateID(id);
    if (m_cate.Get(temp))
    {
        temp.DisplayAllItem();
        return true;
    }
    else
    {
        cout << "\n\t [!] Not Found such cate ID\n";
        return false;
    }
}



bool Application::DisplayCateName()
{
    cout << "\t-------------- All records --------------" << "-\n";

    if (m_cate.IsEmpty()) // If list is empty, show below error
    {
        cout << "\t [!] There's no data to show" << endl;
        return false;
    }

    CateType data;
    int index = 1;
    DoublyIterator<CateType> itor(m_cate);
    // Loop all item in the list
    //while ((index = m_List.GetNextItem(data)) != -1)
    for (itor.Begin(); itor.NotEnd(); itor.Next())
    {
        cout << "\t " << index << ".";
        itor.GetCurrentNode()->DisplayCategory();
        cout << endl;
        index++;
    }

    return true;
}



// 추가를 원하는 카테고리 ID를 입력받아서 
// 해당 카테고리에 추가
bool Application::AddProd()
{
    CateType temp;
    int id;
    cout << "\n\t Home : 10   |  Eletronics : 20\n";
    cout << "\n\t Enter the Category ID : ";
    cin >> id;
    temp.SetCateID(id);
    if (m_cate.Get(temp))
    {
        ItemType item;
        item.SetRecordExceptPrimaryKeyFromKB();
        item.SetCode(id + 0+(rand() % 10));
        m_List.Add(item);
        temp.AddProductInTheCate(item.GetCode());
        return true;
    }
    else
    {
        cout << "\n\t [!] Not Found such cate ID\n";
        return false;
    }
}

/*
*	@brief	Display All content data from list.
*	@pre	list should be initialized.
*	@post	none.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::DisplayAllRecords()
{
    cout << "\t-------------- All records --------------" << "-\n";

    if (m_List.IsEmpty()) // If list is empty, show below error
    {
        cout << "\t [!] There's no data to show" << endl;
        return false;
    }

    ItemType data;
    int index = 1;
    DoublyIterator<ItemType> itor(m_List);
    // Loop all item in the list
    //while ((index = m_List.GetNextItem(data)) != -1)
    for(itor.Begin(); itor.NotEnd(); itor.Next())
    {
        itor.GetCurrentNode()->DisplayRecordOnScreen();
        cout << endl;
        index++;
    }

    return true;
}

/*
*  @brief  Clear List.
*  @pre    none.
*  @post   list is empty.
*/
void Application::MakeEmpty()
{
    m_List.MakeEmpty();

    cout << "\t [!] The master list is now empty.\n" << endl;
}

/*
*	@brief	Add new content into list. Target content is set with Keyboard input.
*	@pre	list should be initialized.
*	@post	new content is added into the list.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::AddProduct()
{
    ItemType item;
    item.SetRecordFromKB();

    m_List.Add(item);

    return true;
}




/*
*	@brief  Search a record by name entered by keyboard.
*	@pre	list must have one or more item.
*	@post	none.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::RetrieveProductByName()
{
    if (m_List.IsEmpty())
    {
        cout << "\n\t [!] There is no data to show" << endl;
        return false;
    }

    ItemType data;
    string inName;
    cout << "\t Enter the name of product -->";
    cin >> inName;
    // data에 inName 넣어줘야지,,ㅠㅠ

    DoublyIterator<ItemType> itor(m_List);

    for (itor.Begin(); itor.NotEnd(); itor.Next())
    {
        if (itor.GetCurrentNode()->GetName() == inName)
        {
            cout << "\t---------- Retrieved Item -----------" << endl;
            data.SetName(itor.GetCurrentNode()->GetName());
            data.SetCode(itor.GetCurrentNode()->GetCode());
            data.SetPrice(itor.GetCurrentNode()->GetPrice());
            data.SetWarehousing(itor.GetCurrentNode()->GetWarehousingNum());
            data.SetSalesNum(itor.GetCurrentNode()->GetSalesNum());
            data.DisplayRecordOnScreen();
            cout << endl;
            return true;
        }
    }

    // If item is not found...
    cout << "\t [!]ERROR There's no such item with that name" << endl;
    return false;
}


/*
*	@brief  Delete a record by using resident number entered by keyboard.
*	@pre	list must have one or more item.
*	@post	none.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::DeleteProduct()
{

    if (m_List.IsEmpty()) // If list is empty, show below error
    {
        cout << "\t [!] There's no data to delete" << endl;
        return false;
    }

    ItemType item;
    item.SetCodeNumFromKB();

    bool bIsit = m_List.Get(item);

    if (bIsit == true)
    {
        m_List.Delete(item);
        cout << "\t Successfuly deleted." << endl;
        return true;
    }

    else
    {
        cout << "\t [!] There's no data with that Product Number\n";
        return false;
    }
}

/*
*	@brief  Replace a record by using a record entered by keyboard.
*	@pre	list must have one or more item.
*	@post	none.
*	@return	return true if this function works well, otherwise false.
*/
bool Application::ReplaceProduct()
{
    if (m_List.IsEmpty()) // If list is empty, show below error
    {
        cout << "\t [!] There's no data to delete" << endl;
        return false;
    }

    ItemType item;
    item.SetCodeNumFromKB();

    bool bIsit = m_List.Get(item);

    if (bIsit == true)
    {
        cout << "\t (new name)\n";
        item.SetRecordExceptPrimaryKeyFromKB();
        m_List.Replace(item);
        cout << "\t Successfuly Replaced." << endl;
        return true;
    }

    else
    {
        cout << "\t [!] There's no data with that Product Number\n";
        return false;
    }
}