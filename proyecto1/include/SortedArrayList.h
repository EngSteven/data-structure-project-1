/*
    - Estructura de datos genérica que usa un array list dinámico para guardar elementos genéricos ordenados ascendentemente y que deriva de la estructura de datos List.
    - Contiene un array list genérico dinámico que guarda los elementos ordenados ascendentemente.
    - Se encarga de insertar, modificar, remover, guardar y recorrer los elementos ingresados ascendentemente.
    - Escrito por el profesor Mauricio Áviles.
    - Modificado por Steven Sequira y Jefferson Salas.
*/

#ifndef SORTEDARRAYLIST_H
#define SORTEDARRAYLIST_H

#include "ArrayList.h"

template <typename E>
class SortedArrayList : public List<E> {
private:
    ArrayList<E> *arrayList;

public:
    SortedArrayList(int max = DEFAULT_MAX_SIZE) {
        arrayList = new ArrayList<E>(max);
    }
    ~SortedArrayList() {
        delete arrayList;
    }
    void insert(E element) {
        int pos = arrayList->getPos();
        arrayList->goToStart();
        while (!arrayList->atEnd() && arrayList->getElement() <= element)
            arrayList->next();
        arrayList->insert(element);
        arrayList->goToPos(pos);
    }
    void append(E element) {
        insert(element);
    }
    E remove() {
        return arrayList->remove();
    }
    void clear() {
        arrayList->clear();
    }
    E getElement() {
        return arrayList->getElement();
    }
    int getPos() {
        return arrayList->getPos();
    }
    void goToStart() {
        arrayList->goToStart();
    }
    void goToEnd() {
        arrayList->goToEnd();
    }
    void goToPos(int pos) {
        arrayList->goToPos(pos);
    }
    void next() {
        arrayList->next();
    }
    void previous() {
        arrayList->previous();
    }
    bool atStart() {
        return arrayList->atStart();
    }
    bool atEnd() {
        return arrayList->atEnd();
    }
    int getSize() {
        return arrayList->getSize();
    }
    void print() {
        arrayList->print();
    }

    int indexOf(E element){
        return arrayList->indexOf(element);
    }

    int getMax(){
        return arrayList->getMax();
    }
};

#endif // SORTEDARRAYLIST_H
