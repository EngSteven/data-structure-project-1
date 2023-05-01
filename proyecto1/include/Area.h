#ifndef AREA_H
#define AREA_H

#include <string>
#include "ArrayList.h"
#include "MinHeap.h"
#include "Tiquet.h"


using namespace std;

//template <typename E>
class Area{;
public:
    string description;
    string code;
    List<string> *windows;
    MinHeap<Tiquet> *queues;

    //int aPriority;

    Area(){}

    Area(int nWindows, string code){
        //windows = new ArrayList<int>(nWindows);
        queues = new MinHeap<Tiquet>;
        windows = new ArrayList<string>(nWindows);

        for(int i=0; i<nWindows; i++){
            string aux = code;
            code += to_string(i+1);
            windows->append(code);
            code = aux;
        }
    }

    // Getter para el atributo description
    string getDescription() {
        return description;
    }

    // Setter para el atributo description
    void setDescription(string description) {
        this->description = description;
    }

    // Getter para el atributo code
    string getCode() {
        return code;
    }

    // Setter para el atributo code
    void setCode(string code) {
        this->code = code;
    }

    // Getter para el atributo windows
    List<string>* getWindows() {
        return windows;
    }

    void addTiquet(Tiquet tiquet){
        queues->insert(tiquet);
    }

    List<string> * getWindows()const {
        return windows;
    }

    MinHeap<Tiquet> *getQueues() const{
        return queues;
    }

    void operator = (Area &other){
        description = other.description;
        code = other.code;
    }

    bool operator == (const Area &other){
        return code == other.code;
    }

    bool operator < (const Area &other){
        return code < other.code;
    }

    bool operator <= (const Area &other){
        return code <= other.code;
    }

    bool operator > (const Area &other){
        return code > other.code;
    }

    bool operator >= (const Area &other){
        return code >= other.code;
    }

    bool operator != (const Area &other){
        return code != other.code;
    }

};

ostream& operator <<(ostream & os,const Area &pair){
    os << "(" << pair.description << ", " << pair.code << ")";
    return os;
}

#endif // AREA_H
