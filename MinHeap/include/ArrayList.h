#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>
#include "List.h"

using std::runtime_error;
using std::cout;
using std::endl;

template<typename E>
class ArrayList : public List<E>{
private:
    E *elements;
    int max;
    int pos;
    int size;

public:
    ArrayList(int max = DEFAULT_MAX_SIZE){
        if(max < 1){
            throw runtime_error("ERROR: Invalid max size.");
        }
        elements = new E[max];
        size = pos = 0;
        this->max = max;
    }

    ~ArrayList(){
        delete [] elements;
    }

    void insert(E element){
        if(size == max){
            //throw runtime_error("ERROR: List is full");
            duplicateArrayList();
        }
        for(int i = size; i > pos; i--){
            elements[i] = elements[i-1];
        }
        elements[pos] = element;
        size ++;
    }

    void append(E element){
        if(size == max){
            //throw runtime_error("Error: List is full");
            duplicateArrayList();
        }

        elements[size] = element;
        size ++;
    }

    E remove(){
        if(size == 0){
            throw runtime_error("Error: List is empty");
        }

        if(pos == size){
            throw runtime_error("Error: No current element");

        }

        E result = elements[pos];

        for(int i = pos; i<size-1; i++){
            elements[i] = elements[i+1];
        }

        size--;
        return result;
    }

    void clear(){
        pos = size = 0;
    }

    E getElement(){
        if(size == 0){
            throw runtime_error("List is empty");
        }

        if(pos == size){
            throw runtime_error("Error: no current element");
        }

        return elements[pos];
    }

    void goToStart(){
        pos = 0;
    }

    void goToEnd(){
        pos = size;
    }

    void goToPos(int pos){
        if(pos < 0 || pos > size){
            throw runtime_error("Error: index out bounds");
        }
        this->pos = pos;
    }

    void next(){
        if(pos < size){
            pos++;
        }
    }

    void previous(){
        if(pos > 0){
            pos--;
        }
    }

    bool atStart(){
        return pos == 0;
    }

    bool atEnd(){
        return pos == size;
    }

    int getSize(){
        return size;
    }

    void print(){
        cout << "[ ";
        for(int i = 0; i < size; i++){
            cout << elements[i] << " ";
        }
        cout << " ]" << endl;
    }

    //metodos extras
    //recibe un elemento y retorna true en caso de encontrarlo dentro de la lista
    bool contains(E element){
        for(int i = 0; i < size; i++){
            if(elements[i] == element){
                return true;
            }
        }
        return false;
    }

    //recibe un elemento e indica la posicion en la que se encuentra
    int indexOf(E element){
        for(int i = 0; i < size; i++){
            if(elements[i] == element){
                return i;
            }
        }

        return -1;
    }

    //recibe una lista y se la agrega al fina de la lista original
    void extend(List<E> *list){
        int listPos = list->indexOf(list->getElement());    //se guarda la posición actual de la lista recibida

        if(list->getSize() + size > max){
            throw runtime_error("Error: the size is not enough");
        }

        for(list->goToStart(); !list->atEnd(); list->next()){
            append(list->getElement());
        }

        list->goToPos(listPos);                             //se regresa la posición actual de la lista recibida
    }

    //invierte el orden de la lista
    void reverse(){

        E *temp = new E[max];
        int sizeTemp = size - 1;

        for(int i = 0; i < size; i++){
            temp[i] = elements[sizeTemp];
            sizeTemp--;
        }

        elements = temp;
    }

    //duplica la el largo de la lista original
    void duplicateArrayList(){
        max *= 2;
        E *temp = new E[max];

        for(int i = 0; i < size; i++){
            temp[i] = elements[i];
        }

        delete [] elements;
        elements = temp;
    }

    //recibe una lista y retorna true en caso de ser igual a la lista original, false de lo contrario
    bool equals(List<E> *list){
        bool isEquals = true;
        int listPos = list->indexOf(list->getElement());    //se guarda la posición actual de la lista recibida


        if(list->getSize() == size){
            list->goToStart();
            for(int i = 0; i < size; i++){
                if(elements[i] != list->getElement()){
                    isEquals = false;
                    break;
                }
                list->next();
            }
        }
        else{
            isEquals = false;
        }

        list->goToPos(listPos);                             //se regresa la posición actual de la lista recibida

        return isEquals;
    }


};

#endif // ARRAYLIST_H
