#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User{
public:
    string userType;
    int priority;
    int nTiquets;

    User(string userType, int priority){
        this->userType = userType;
        this->priority = priority;
    }

    User(){}

    void setUserType(string userType){
        this->userType = userType;
    }

    void setPriority(int priority){
        this->priority = priority;
    }

    string getUserType(){
        return userType;
    }

    int getPriority(){
        return priority;
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


    void operator = (User &other){
        userType = other.userType;
        priority =  other.priority;
        nTiquets = other.nTiquets;
    }

    bool operator == (const User &other){
        return priority == other.priority;
    }

    bool operator < (const User &other){
        return priority < other.priority;
    }

    bool operator <= (const User &other){
        return priority <= other.priority;
    }

    bool operator > (const User &other){
        return priority > other.priority;
    }

    bool operator >= (const User &other){
        return priority >= other.priority;
    }

    bool operator != (const User &other){
        return priority != other.priority;
    }

};

ostream& operator <<(ostream & os,const User &pair){
    os << "(" << pair.userType << ", " << pair.priority << pair.nTiquets << ")";
    return os;
}

#endif // USER_H
