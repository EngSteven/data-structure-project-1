/*
    - Clase que representa los diversos tiquetes dispensados por el sistema.
    - Contiene los segundos en los que fue dispensado, un consecutivo para indentificarlo, una prioridad final calculada usando la prioridad del servicio y
      de usuario relacionado y una ventanilla en caso de ser atendido.
    - Se encarga de decidir en que orden se va atender un tipo de usuario para un servicio de un área.
    - Escrito por Steven Sequeira y Jefferson Salas.
    - Modificado por Steven Sequira y Jefferson Salas.
*/

#ifndef TIQUET_H
#define TIQUET_H

#include <string>

using namespace std;

class Tiquet{
public:
    int iSeconds;
    string consecutive;
    int fPriority;
    string window;

    Tiquet(){}

    Tiquet(int iSeconds, string consecutive, int fPriority){
        this->iSeconds = iSeconds;
        this->consecutive = consecutive;
        this->fPriority = fPriority;
        window = "";
    }

    void setWindow(string window){
        this->window = window;
    }

    string getWindow(){
        return window;
    }

    void setISeconds(int iSeconds) {
        this->iSeconds = iSeconds;
    }

    int getISeconds(){
        return iSeconds;
    }

    void setConsecutive(string consecutive) {
        this->consecutive = consecutive;
    }

    string getConsecutive() {
        return consecutive;
    }

    void setFPriority(int fPriority) {
        this->fPriority = fPriority;
    }

    int getFPriority() {
        return fPriority;
    }

    void operator = (Tiquet &other){
        fPriority = other.fPriority;
        consecutive = other.consecutive;
        iSeconds = other.iSeconds;
        window =  other.window;
    }

    bool operator == (const Tiquet &other){
        return fPriority == other.fPriority;
    }

    bool operator < (const Tiquet &other){
        return fPriority < other.fPriority;
    }

    bool operator <= (const Tiquet &other){
        return fPriority <= other.fPriority;
    }

    bool operator > (const Tiquet &other){
        return fPriority > other.fPriority;
    }

    bool operator >= (const Tiquet &other){
        return fPriority >= other.fPriority;
    }

    bool operator != (const Tiquet &other){
        return fPriority != other.fPriority;
    }
};

ostream& operator <<(ostream & os,const Tiquet &pair){
    os << "(" << pair.iSeconds << ", " << pair.consecutive << ", " << pair.fPriority << pair.window << ")";
    return os;
}

#endif // TIQUET_H
