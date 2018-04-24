//
// Created by Tristan Ratz on 23.04.18.
//

#ifndef PANCAKESOCKET_LINKEDLIST_H
#define PANCAKESOCKET_LINKEDLIST_H

#include <stdlib.h>

using namespace std;

template <class T>
class LinkedList
{
    protected:
        T object;
        LinkedList<T> * next;

    public:
        LinkedList(T obj) : object(obj) {}
        int add(T obj) {
            if (next == NULL)
            {
                next = new LinkedList(obj);
                return 1;
            }
            else
            {
                return next->add(obj)+1;
            }
        }

        // TODO improve
        LinkedList* remove(int id) {
            if (id == 0) {
                return next;
            } else if (id == 1) {
                LinkedList* x = next;
                next = remove(id-1);
                return x;
            }
            return remove(id-1);
        }

        T getObject()
        {
            return object;
        }

        // TODO improve
        int getID(T obj)
        {
            return 0;
        }

        LinkedList<T>* getNext()
        {
            return next;
        }

        unsigned int size()
        {
            if (next == NULL) {
                return 1;
            } else {
                return next->size()+1;
            }
        }

};


#endif //PANCAKESOCKET_LINKEDLIST_H
