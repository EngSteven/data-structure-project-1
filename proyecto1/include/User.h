#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User{
public:
    string userType;
    int priority;

    /*
    User(string userType, int priority){
        this->userType = userType;
        this->priority = priority;
    }
    */

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


    void operator = (User &other){
        userType = other.userType;
        priority =  other.priority;
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
    os << "(" << pair.userType << ", " << pair.priority << ")";
    return os;
}

#endif // USER_H
