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

    Service(string operation, int priority, Area area){
        this->operation = operation;
        this->priority = priority;
        this->area = area;
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

    void setArea(Area area){
        this->area = area;
    }

    void operator = (Service &other){
        operation = other.operation;
        priority = other.priority;
        area = other.area;
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
    os << "(" << pair.operation << ", " << pair.priority << ")";
    return os;
}

#endif // SERVICE_H
