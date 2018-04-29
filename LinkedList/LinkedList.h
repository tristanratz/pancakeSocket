/**
 * LinkedList
 *
 * A LinkedList for dynamicly, efficiently accessing data, stored in it
 * Created by Pancake Software, Tristan Ratz on 22.04.2018
 *
*/

#ifndef PANCAKESOCKET_LINKEDLIST_H
#define PANCAKESOCKET_LINKEDLIST_H

#include <Log/Log.h>
#include <stdlib.h>

using namespace std;

template< class T >
struct TypeIsInt
{
    static const bool value = false;
};

template<>
struct TypeIsInt< int >
{
    static const bool value = true;
};

template <class T>
class ListNode {
    public:
        ListNode(T obj) : next(nullptr), object(obj) {}

        ListNode<T> *next;
        T object;

};

template <class T>
class LinkedList
{
    protected:
        Log l;
        ListNode<T> *first;
        ListNode<T> *last;
        int currentPos;
        ListNode<T> *current;

        ListNode<T>* getNode(int x)
        {
            int z = 0;
            ListNode<T> *c = first;
            if (currentPos == x) {
                return current;
            } else if (currentPos < x) {
                z = currentPos;
                c = current;
            } else {
                c = first;
            }
            for (int i = z; i <= (x-z)+1;) {

                if (i == x) {
                    currentPos = i;
                    current = c;
                    return current;
                }

                if (c->next == nullptr)
                    return nullptr;

                c = c->next;
                i++;
            }
            return nullptr;
        }

    public:
        LinkedList() : l("LinkedList") , first(nullptr), last(nullptr), current(nullptr) {}
        //LinkedList(T obj) : l("LinkedList") , first(ListNode<T>(obj)), last(first), current(first) {}
        ~LinkedList()
        {
            for (int i = 0; i < size(); i++)
            {
                remove(0);
            }
        }

        void add(T obj) {
            ListNode<T> *n = new ListNode<T>(obj);
            if (first == nullptr) {
                first = n;
                last = first;
                current = first;
                currentPos = 0;
                return;
            }
            last->next = n;
            last = last->next;
        }


        T remove(int id) {
            ListNode<T> *d, *p;
            //l.info("Removed node");

            if (size() >= id)
                d = getNode(id);
            else
                throw out_of_range("Object out of range. Cannot remove item");

            if (current == d) {
                if (current == first)
                {
                    if (first->next == nullptr)
                    {
                        current = nullptr;
                        currentPos = 0;
                    } else
                        current = first->next;
                } else
                {
                    current = first;
                    currentPos = 0;
                }

            }

            if (size() > 1)
            {
                if (id > 0)
                {
                    p = getNode(id - 1);
                    if (size() > 2)
                        p->next = d->next;
                    else
                        p->next = nullptr;
                } else {
                    first = d->next;
                }
            } else {
                first = nullptr;
                last = nullptr;
            }

            T obj = d->object;
            delete(d);
            return obj;
        }

        T& get(int i) {
            if (size() < i)
                throw out_of_range("Index out of range");

            ListNode<T> *n = getNode(i);

            if (n == nullptr)
                cout << "NULLPOINTER";

            return n->object;
        }

        int getID(const T &obj)
        {
            int i = 0;
            ListNode<T> *n = first;
            if constexpr (TypeIsInt<T>::value)
                l.info("First value: " + to_string(n->object));

            while (obj != (const T)n->object) {
                i++;
                if constexpr (TypeIsInt<T>::value)
                    l.info("Search for "+ to_string(obj) + " candidate: " + to_string((int)n->object));
                if (n->next == nullptr)
                    throw out_of_range("Object not found");
                n = n->next;
            }
            return i;
        }

        unsigned int size()
        {
            int i = 0;
            ListNode<T> *n = first;

            while (n != nullptr)
            {
                i++;
                n = n->next;
            }

            return i;
        }

};


#endif //PANCAKESOCKET_LINKEDLIST_H
