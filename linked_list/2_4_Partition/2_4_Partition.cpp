#include <iostream>
#include <fstream>

using namespace std;

class node
{
    int data;
    node *next;

public:
    node(int);
    int getData() const;
    node *getNext() const;
    void setNext(node *);
    void setData(int);
};

class linkedlist
{
    node *head;
    node *tail;

public:
    linkedlist();
    void AddAtLast(int);
    void printLL() const;
    node *getHead() const;
};

node::node(int d)
{
    data = d;
    next = NULL;
}

int node::getData() const
{
    return data;
}

node *node::getNext() const
{
    return next;
}

void node::setNext(node *temp)
{
    next = temp;
}

void node::setData(int d)
{
    data = d;
}

linkedlist::linkedlist()
{
    head = NULL;
    tail = NULL;
}

void linkedlist::AddAtLast(int d)
{
    node *temp = new node(d);

    if (head == NULL && tail == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->setNext(temp);
        tail = tail->getNext();
    }
}

void linkedlist::printLL() const
{
    // output file
    ofstream ofile;
    ofile.open("2_4_output.txt", ios::out | ios::app);

    node *temp = head;
    while (temp != NULL)
    {
        if (temp->getNext() != NULL)
            ofile << temp->getData() << "->";
        else
            ofile << temp->getData();

        temp = temp->getNext();
    }

    ofile << endl;
    ofile.close();
}

node *linkedlist::getHead() const
{
    return head;
}

void partition(linkedlist *L, int partition_value); // pointer to linkedlist to be used so that changes are reflected outside of function scope

int main()
{
    ifstream ifile;
    ifile.open("2_4_input.txt", ios::in);

    // to clean output file text for new program run
    ofstream ofile;
    ofile.open("2_4_output.txt", ios::out | ios::trunc);
    ofile.close();

    linkedlist L;

    int size_of_ll, data_to_add_to_ll;

    ifile >> size_of_ll;

    for (int i = 0; i < size_of_ll; i++)
    {
        ifile >> data_to_add_to_ll;
        L.AddAtLast(data_to_add_to_ll);
    }

    ifile.close(); // reading operations from file complete so close ifile stream

    // testing LL by printing it
    L.printLL();

    partition(&L, 5);

    // checking if partition happened
    L.printLL();

    return 0;
}

/*
Partition Algorithm
1. We will initialize partition_index and ll_iterator to the head of linkedlist
2. We will iterate over the linkedlist with ll_iterator if we find an element ie less than partition_value we swap the node's data with partition_index's node's data.
3. before swapping we have put a check if partition_index and ll_iterator arent pointing to the same node then there is no need for swap.
4. if swapped then partition_index should point to its next node
*/

void swapData(node **, node **); // to reflect changes outside of function scope we need to use node pointer to pointer

void partition(linkedlist *L, int partition_value)
{
    node *partition_index = L->getHead();
    node *ll_iterator = L->getHead();

    while (ll_iterator)
    {
        if (ll_iterator->getData() < partition_value)
        {
            if (ll_iterator != partition_index)
                swapData(&partition_index, &ll_iterator);

            partition_index = partition_index->getNext();
        }
        ll_iterator = ll_iterator->getNext();
    }
}

void swapData(node **first, node **second)
{
    int to_swap_data = (*first)->getData();
    (*first)->setData((*second)->getData());
    (*second)->setData(to_swap_data);
}