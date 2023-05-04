#ifndef TIQUET_H
#define TIQUET_H

#include <string>

using namespace std;

class Tiquet{
public:
    int iSeconds;
    string consecutive;
    int fPriority;
    int nTiquete;

//public:
    Tiquet(){
    }

    Tiquet(int iSeconds, string consecutive, int fPriority){
        this->iSeconds = iSeconds;
        this->consecutive = consecutive;
        this->fPriority = fPriority;
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
        //value =  other.value;
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
    os << "(" << pair.iSeconds << ", " << pair.consecutive << ", " << pair.fPriority << ")";
    return os;
}

#endif // TIQUET_H
