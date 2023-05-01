#ifndef TIQUET_H
#define TIQUET_H

#include <string>

using namespace std;

class Tiquet{
public:
    int seconds;
    string consecutive;
    int fPriority;

//public:
    Tiquet(){
    }

    void setSeconds(int seconds) {
        this->seconds = seconds;
    }

    int getSeconds(){
        return seconds;
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
        seconds = other.seconds;
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
    os << "(" << pair.consecutive << ", " << pair.fPriority << ")";
    return os;
}

#endif // TIQUET_H
