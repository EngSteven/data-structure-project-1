/*
    - Estructura de datos genérica que usa un arreglo dinámico para guardar elementos genéricos y que deriva de la clase List.
    - Contiene un arreglo genérico dinámico, un tamaño máximo, una posición y tamaño actual.
    - Se encarga de insertar, modificar, remover, guardar y recorrer los elementos ingresados.
    - Escrito por el profesor Mauricio Áviles.
    - Modificado por Steven Sequira y Jefferson Salas.
*/

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Window.h"

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

public:
    ArrayList(int max = DEFAULT_MAX_SIZE){
        if(max < 1){
            throw runtime_error("Invalid max size.");
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
            duplicateArrayList();
        }

        elements[size] = element;
        size ++;
    }

    E remove(){
        if(size == 0){
            throw runtime_error("List is empty");
        }

        if(pos == size){
            throw runtime_error("No current element");

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
            throw runtime_error("No current element");
        }

        return elements[pos];
    }

    int getPos() {
        return pos;
    }

    void goToStart(){
        pos = 0;
    }

    void goToEnd(){
        pos = size;
    }

    void goToPos(int pos){
        if(pos < 0 || pos > size){
            throw runtime_error("Index out bounds");
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

    //recibe un elemento e indica la posicion en la que se encuentra
    int indexOf(E element){
        for(int i = 0; i < size; i++){
            if(elements[i] == element){
                return i;
            }
        }

        return -1;
    }

    int getMax(){
        return max;
    }
};

#endif // ARRAYLIST_H
