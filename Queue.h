//
// Created by mindyeoi on 2021/03/29.
//

#ifndef LAB03_AGAIN_AGAIN_QUEUELIST_H
#define LAB03_AGAIN_AGAIN_QUEUELIST_H


#pragma once
#include <iostream>
#define MAX 8
using namespace std;


template <typename T>
class QueueList {
private:
    int m_iFront;       // front index of the circular queue
    int m_iRear;        // rear index of the circular queue
    int m_nMaxQueue;    // maximum size of the circular queue
    T* items;           // item queue
    int iterator;       // current item pointer (for iteration operation)

public:
    // Default Constructor
    QueueList()
    {
        m_nMaxQueue = MAX + 1;
        items = new T[m_nMaxQueue];
        m_iFront = m_nMaxQueue - 1;
        m_iRear = m_nMaxQueue - 1;
    }

    // Parameterized Constructor
    QueueList(int max)
    {
        m_nMaxQueue = max + 1;
        items = new T[m_nMaxQueue];
        m_iFront = m_nMaxQueue - 1;
        m_iRear = m_nMaxQueue - 1;
    }

    // Destructor
    ~QueueList()
    {
        delete[] items;
    }

    /**
     * @brief   Check this queue is full or not.
     * @pre     none.
     * @post    none.
     * @return  if the queue is full, return true, otherwise return false.
     */
    bool isFull();

    /**
     * @brief   Check this queue is empty or not.
     * @pre     none.
     * @post    none.
     * @return  if the queue is empty, return true, otherwise return false.
     */
    bool isEmpty();

    /**
     * @brief   Make the queue empty.
     * @pre     none.
     * @post    Queue is empty.
     */
    void makeEmpty();

    /**
     * @brief   Enqueue the item to top of the queue.
     * @pre     Item should be available, and queue has space.
     * @post    Item is added to the queue.
     * @pram    Item what we want to enqueue.
     */
    void EnQueue(T& item);

    /**
     * @brief   Dequeue the item at bottom of the queue.
     * @pre     Item should be available, and queue is not empty.
     * @post    Dequeue the item.
     * @param   Item what we want to dequeue.
     */
    void DeQueue(T& item);

    /**
     * @brief   Display all item on screen.
     * @pre     Items are set.
     * @post    none.
     */
    void DisplayAll();

    /**
    * @brief    Initialize the current pointer.
    * @pre      Queue should be initialized.
    * @post     The current pointer is reset.
    */
    void ResetQList();

    /**
    * @brief    move list iterator to the next item in list and get that item.
    * @pre      queue and iterator should be initialized.
    * @post     iterator is moved to next item.
    * @param    item    get current iterator's item
    * @return   if it is not end of queue, return index of current iterator's item, otherwise return -1.
    */
    int GetNextItem(T& item);

    //    /**
    //    * @brief    Delete an item on screen.
    //    * @pre      item should be available and the queue has the data.
    //    * @post     the queue does not have the item.
    //    * @param    the item what wants to delete.
    //    * @return   if successful, return 1, otherwise return 0.
    //    */
    //    int Delete(T item);

    /**
    *	@brief  Check the item is exist in the queue.
    *	@pre    item should be available.
    *	@post	none.
    *	@param	item what we want to know whether existed.
    *	@return	if the item exists, return the position, otherwise return false.
    */
    int Retrieve(T& item);

};

template <typename T>
bool QueueList<T>::isFull()
{
    return ((m_iRear + 1) % m_nMaxQueue == m_iFront);
}

template <typename T>
bool QueueList<T>::isEmpty()
{
    return (m_iRear == m_iFront);
}

template <typename T>
void QueueList<T>::makeEmpty()
{
    m_iRear = m_iFront;
}

template <typename T>
void QueueList<T>::EnQueue(T& item)
{
    if (isFull())
    {
        cout << "\t [!] This queue is full. Enqueue is not available.\n";
        return;
    }

    else
    {
        m_iRear = (m_iRear + 1) % m_nMaxQueue;
        items[m_iRear] = item;
    }
}

template <typename T>
void QueueList<T>::DeQueue(T& item)
{
    if (isEmpty())
    {
        cout << "\t [!] This queue is empty. Dequeue is not available.\n";
        return;
    }
    else
    {
        m_iFront = (m_iFront + 1) % m_nMaxQueue;
        item = items[m_iFront];
    }
}
template <typename T>
void QueueList<T>::DisplayAll()
{
    if (isEmpty())
    {
        cout << "\t This queue is empty. No data to show\n.";
    }

    int iPos = m_iFront;
    int index = 0;
    while (!isEmpty())
    {
        cout << "items[" << index << "] == " << items[iPos] << endl;
        DeQueue(items[iPos]);
    }
}

template <typename T>
void QueueList<T>::ResetQList()
{
    if (isEmpty())
    {
        cout << "\t [!] This queue is empty. Reset Queue is not available.\n";
        return;
    }
    else
    {
        iterator = m_iFront;
    }
}

template <typename T>
int QueueList<T>::GetNextItem(T& item)
{
    if (iterator == m_iRear)
    {
        return -1;
    }
    else
    {
        iterator = (iterator + 1) % m_nMaxQueue;
        item = items[iterator];
        return iterator;
    }
}

//  template <typename T>
//  int QListType<T>::Delete(T item)
//  {
//      int index = isExist(item);
//      if(isEmpty())
//      {
//          cout << "\t [!] This queue is empty. Dequeue is not available.\n";
//          return -1;
//      }
//      else
//      {
//
//      }
//  }

template <typename T>
int QueueList<T>::Retrieve(T& item)
{
    if (isEmpty()) return -1;
    int iPos = m_iFront;
    bool b_found = false;
    while (iPos != m_iRear && !b_found)
    {
        iPos = (iPos + 1) % m_nMaxQueue;
        if (items[iPos] == item)
        {
            item = items[iPos];
            return iPos;
        }
    }
    return -1;
}

#endif