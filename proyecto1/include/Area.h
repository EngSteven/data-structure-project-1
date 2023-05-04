#ifndef AREA_H
#define AREA_H

#include <string>
#include "ArrayList.h"
#include "MinHeap.h"
#include "Tiquet.h"


using namespace std;

class Area{;
public:
    string description;
    string code;
    List<string> *windows;
    MinHeap<Tiquet> *tiquets;

    Area(){}

    Area(string description, int nWindows, string code){
        tiquets = new MinHeap<Tiquet>;
        windows = new ArrayList<string>(nWindows);
        this->code = code;
        this->description = description;

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
        tiquets->insert(tiquet);
    }

    void setWindows(int nWindows){

        for(int i=0; i<nWindows; i++){
            string aux = code;
            code += to_string(i+1);
            windows->append(code);
            code = aux;
        }
    }

    List<string> * getWindows()const {
        return windows;
    }

    MinHeap<Tiquet> *getTiquets() const{
        return tiquets;
    }

    void operator = (Area &other){
        description = other.description;
        code = other.code;
        windows = other.windows;
        tiquets = other.tiquets;
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
    os << "(" << pair.description << ", " << pair.code << ", " << pair.windows << ", " << pair.tiquets << ")";
    return os;
}

#endif // AREA_H
