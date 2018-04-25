//
// Created by Tristan Ratz on 23.04.18.
//

#ifndef PANCAKESOCKET_LINKEDLIST_H
#define PANCAKESOCKET_LINKEDLIST_H

#include <stdlib.h>

using namespace std;



template <class T>
class ListNode {
    public:
        ListNode(T *obj) : object(obj) {}

        ListNode<T> *next;
        T *object;

};

template <class T>
class LinkedList
{
    protected:
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
                c = first;
            } else {
                c = current;
            }

            for (int i = z; i <= (x-z); i++) {
                if (i == x) {
                    currentPos = i;
                    current = c;
                    return current;
                }

                if (c->next == NULL)
                {
                    return NULL;
                } else
                {
                    c = c->next;
                }
            }
            return NULL;
        }

    public:
        LinkedList() {}
        LinkedList(T obj) : first(ListNode<T>(obj)), last(first), current(first) {}
        ~LinkedList()
        {
            for (int i = 0; i < size(); i++)
            {
                delete(remove(0));
            }
        }

        void add(T &obj) {
            ListNode<T> *n = new ListNode<T>(&obj);
            n->object = &obj;
            if (first == NULL) {
                first = n;
                last = first;
                return;
            }

            last->next = n;
            last = last->next;
        }


        T remove(int id) {
            ListNode<T> *p = getNode(id-1);
            ListNode<T> *d = getNode(id);

            p->next = d->next;

            T obj = d->object;
            delete(d);
            return obj;
        }

        T* get(int i) {
            return getNode(i)->object;
        }

        int getID(const T &obj)
        {
            int i = 0;
            ListNode<T> *n = first;

            while (obj != *n->object) {
                i++;
                if (n->next == NULL)
                    return -1;
                n = n->next;
            }
            return i;
        }

        unsigned int size()
        {
            int i = 1;
            ListNode<T> *n = first;

            while (n == NULL)
            {
                i++;
                n = n->next;
            }

            return i;
        }

};


#endif //PANCAKESOCKET_LINKEDLIST_H