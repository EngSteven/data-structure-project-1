/*
    - Clase gen�rica que define los diversos nodos que van a contener las estructuras de datos que lo usen.
    - Contiene un elemento gen�rico y un puntero a la siguiente posici�n de la estructura de datos usada.
    - Se encarga guardar los elementos y enlazar cada nodo para formar una estructura de datos.
    - Escrito por el profesor Mauricio �viles.
    - Modificado por Steven Sequira y Jefferson Salas.
*/


#ifndef NODE_H
#define NODE_H


template <typename E>
class Node{
public:
    E element;
    Node<E> *next;

    Node(E element, Node<E> *next = nullptr){
        this->element = element;
        this->next = next;
    }

    //special node
    Node(Node<E> *next = nullptr){
        this->next = next;
    }
};

#endif // NODE_H
