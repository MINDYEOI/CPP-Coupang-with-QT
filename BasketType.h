#pragma once
#include "BaseType.h"
#include <iostream>
#include <iomanip>
#include "SimpleType.h"
#include "DoublySortedLinkedList.h"

// #include "QueueList.h" -> SimpleType.h 에서 불러오기 때문에!
#define WIDTH 40
#define MAXCOMMANDS 10

using namespace std;


class BasketType :public BaseType
{
private:
    QueueList<SimpleType> basket;
    //DoublySortedLinkedList<ItemType> m_List;	// masterList
public:
    BasketType() {}	// Default Constoructor

    ~BasketType() {} // Destructor

    /*
    *	@brief	Display command on screen and get a input from keyboard.
    *	@pre	none.
    *	@post	none.
    *	@return	user's command.
    */
    int GetCommand();


    /**
    * @brief   Manage the basket.
    * @pre     The baset is initialized.
    * @post    none.
    * @return  If this function works well, return true, otherwise return false.
    */
    bool ManageBasket(DoublySortedLinkedList<ItemType>& m_List);

    /**
    * @brief   Display the goods in the basket.
    * @pre     The basket is not empty.
    * @post    none.
    * @return  If this function works well, return true, otherwise return false.
    */
    bool DisplayBasket(DoublySortedLinkedList<ItemType>& m_List);

    /**
     * @brief   Add the goods to the basket.
     * @pre     The goods is available, and the basket is initialized.
     * @post    none.
     * @return  If this function works well, return true, otherwise return false.
     */
    bool AddToBasket(DoublySortedLinkedList<ItemType>& m_List);

    /**
     * @brief   Search the goods in basket. Target content is set with keyboard input.
     * @pre     List should be initialized.
     * @post    none.
     * @return  If this function works well, return true, otherwise return false.
     */
    bool SearchTheGoodsInBasket(DoublySortedLinkedList<ItemType>& m_List);

    /**
     * @brief   Make the basket empty.
     * @pre     none.
     * @post    Basket is empty.
     * @return  If this function works well, return true, otherwise return false.
     */
    bool EmptyBasket();


};


int BasketType::GetCommand()
{
    int select;
    while (1) {

        cout << "\t=" << setw(WIDTH + 1) << setfill('=') << "=\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  0: Quit" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  1: Display the basket" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  2: Search the goods in the basket" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  3: Empty the basket" << "|\n";
        cout << "\t|" << left << setw(WIDTH) << setfill(' ') << "  4: Add the goods in the basket" << "|\n";

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

bool BasketType::ManageBasket(DoublySortedLinkedList<ItemType>& m_List)
{
    while (true)
    {
        int Command = GetCommand(); // Get command value from keyboard

        // Command execution
        switch (Command)
        {
        case 0:
            return true;
        case 1:// display all records on screen
            DisplayBasket(m_List);
            break;
        case 2:
            SearchTheGoodsInBasket(m_List);
            break;
        case 3:
            EmptyBasket();
            break;
        case 4:
            AddToBasket(m_List);
            break;
        default:
            cout << "\t [!]ERROR Illegal selection...\n";
            break;
        }
    }
}


bool BasketType::DisplayBasket(DoublySortedLinkedList<ItemType>& m_List)
{


    cout << "\t-------------- All records --------------" << "-\n";

    if (basket.isEmpty()) // If list is empty, show below error
    {
        cout << "\t [!] There's no data to show" << endl;
        return false;
    }

    basket.ResetQList();
    SimpleType data;
    int index;
    // Loop all item in the list
    while ((index = basket.GetNextItem(data) != -1))
    {
        cout << "\t [" << index << "]\n";
        data.DisplayTheBasket();
        cout << endl;
    }

    return true;
}



bool BasketType::AddToBasket(DoublySortedLinkedList<ItemType>& m_List)
{
    ItemType inData;
    inData.SetCodeNumFromKB();
    int bFind = m_List.Get(inData);

    if (bFind == true)
    {
        if (!basket.isFull())
        {
            SimpleType product;
            product.SetNameInBasket(inData.GetName());
            product.SetCodeInBasket(inData.GetCode());
            product.SetSalesPriceInBasket(inData);
            product.SetProductQuantityInBasketByKB();
            basket.EnQueue(product);
            cout << "\t[!] Successfully added!\n\n";
            return true;
        }

        else
        {
            cout << "\t[!] The basket is full\n";
            return false;
        }
    }
    else
    {
        cout << "\t[!] There is no goods with that code number.\n";
        return false;
    }
    
}


bool BasketType::SearchTheGoodsInBasket(DoublySortedLinkedList<ItemType>& m_List)
{
    if (basket.isEmpty())
    {
        cout << "\t [!] The basket is empty.\n";
        return false;
    }
    SimpleType item;
    ItemType data;
    item.SetCodeInBasketByKB();
    int index = basket.Retrieve(item);
    if (index == -1)
    {
        cout << "\t [!] The goods is not exist in the basket.\n";
        return false;
    }

    else
    {
        data.SetCode(item.GetGoodsCodeInBasket());
        if (m_List.Get(data) != -1)
        {
            cout << "\t---------- The Item Information -----------" << endl;
            data.DisplayRecordOnScreen();
            cout << endl << endl;
            return true;
        }
        else
        {
            cout << "[!] There is no data in the goods list.\n\n";
            return false;
        }
    }

}

bool BasketType::EmptyBasket()
{
    if (basket.isEmpty())
    {
        cout << "[!] The basket is already empty." << endl;
        return false;
    }
    basket.makeEmpty();
    cout << "\t[!] The basket is now empty." << endl;
    return true;
}