/*
    - Clase que representa los servicios creados en el programa por el usuario.
    - Contiene una operación que representa su funcionalidad, una prioridad, un área asociada y la cantidad de tiquetes dispensados.
    - Se encarga de brindar su prioridad a los tiquetes dispensados relacionados, para mantener un orden de atención.
    - Escrito por Steven Sequeira y Jefferson Salas.
    - Modificado por Steven Sequira y Jefferson Salas.
*/

#ifndef SERVICE_H
#define SERVICE_H

#include <string>

#include "Area.h"

using namespace std;

class Service{
public:
    string operation;
    int priority;
    Area area;
    int nTiquets;

    Service(string operation, int priority, Area area){
        this->operation = operation;
        this->priority = priority;
        this->area = area;
        nTiquets = 0;
    }

    Service(){}

    // Setter para el atributo operation
    void setOperation(string operation) {
        this->operation = operation;
    }

    // Getter para el atributo operation
    string getOperation() {
        return this->operation;
    }

    // Setter para el atributo priority
    void setPriority(int priority) {
        this->priority = priority;
    }

    // Getter para el atributo priority
    int getPriority() {
        return this->priority;
    }


    // Getter para el atributo area
    Area getArea() {
        return this->area;
    }

    Area & getAreaDirection(){
        return area;
    }

    void setArea(Area area){
        this->area = area;
    }

    void increaseNTiquets(){
        nTiquets++;
    }

    int getNTiquets(){
        return nTiquets;
    }

    void setNTiquets(int nTiquets){
        this->nTiquets = nTiquets;
    }

    void operator = (Service &other){
        operation = other.operation;
        priority = other.priority;
        area = other.area;
        nTiquets = other.nTiquets;
    }

    bool operator == (const Service &other){
        return priority == other.priority;
    }

    bool operator < (const Service &other){
        return priority < other.priority;
    }

    bool operator <= (const Service &other){
        return priority <= other.priority;
    }

    bool operator > (const Service &other){
        return priority > other.priority;
    }

    bool operator >= (const Service &other){
        return priority >= other.priority;
    }

    bool operator != (const Service &other){
        return priority != other.priority;
    }


};

ostream& operator <<(ostream & os,const Service &pair){
    os << "(" << pair.operation << ", " << pair.priority << pair.nTiquets << ")";
    return os;
}

#endif // SERVICE_H
