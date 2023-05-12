#ifndef AREA_H
#define AREA_H

#define N_COLUMNS_WINDOWS 2

#include <string>
#include "ArrayList.h"
#include "MinHeap.h"
#include "Tiquet.h"
#include "Window.h"
#include "conio.h"


using namespace std;

class Area{;
public:
    string description;
    string code;
    List<Window> *windows;
    MinHeap<Tiquet> *tiquets;
    MinHeap<Tiquet> *attendTiquets;
    int totalTime;
    int nTiquets;
    int nTiquetsAttended;

    Area(){}

    Area(string description, int nWindows, string code){
        tiquets = new MinHeap<Tiquet>;
        windows = new ArrayList<Window>(nWindows);
        attendTiquets = new MinHeap<Tiquet>;

        this->code = code;
        this->description = description;

        for(int i=0; i<nWindows; i++){
            string aux = code;
            code += to_string(i+1);
            Window window(code);
            windows->append(window);
            code = aux;
        }
        totalTime = 0;
        nTiquets = 0;
        nTiquetsAttended = 0;
    }

    ~Area(){

    }

    void addTime(int time){
        totalTime += time;
    }

    int getTotalTime(){
        return totalTime;
    }

    void setTotalTime(int totalTime){
        this->totalTime = totalTime;
    }

    int getAverageTime(){
        if(nTiquetsAttended > 0){
            return totalTime / nTiquetsAttended;
        }
        return 0;
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

    void addTiquet(Tiquet tiquet){
        tiquets->insert(tiquet);
    }

    void addAttendTiquet(Tiquet tiquet){
        attendTiquets->insert(tiquet);
    }

    MinHeap<Tiquet> * getAttendTiquets(){
        return attendTiquets;
    }

    void setWindows(int nWindows){
        for(int i=0; i<nWindows; i++){
            string aux = code;
            code += to_string(i+1);
            Window window(code);
            windows->append(window);
            code = aux;
        }
    }

    List<Window> * getWindows()const {
        return windows;
    }

    MinHeap<Tiquet> *getTiquets() const{
        return tiquets;
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

    void increseaNTiquetsAttended(){
        nTiquetsAttended++;
    }

    int getNTiquetsAtteded(){
        return nTiquetsAttended;
    }

    void setNTiquetsAttended(){
        this->nTiquetsAttended = nTiquetsAttended;
    }

    void operator = (Area &other){
        description = other.description;
        code = other.code;
        windows = other.windows;
        tiquets = other.tiquets;
        attendTiquets = other.attendTiquets;
        totalTime = other.totalTime;
        nTiquets = other.nTiquets;
        nTiquetsAttended = other.nTiquetsAttended;
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
    os << "(" << pair.description << ", " << pair.code << ", " << pair.nTiquets << ", " << pair.nTiquetsAttended << pair.attendTiquets << pair.totalTime << ")";
    return os;
}

#endif // AREA_H
