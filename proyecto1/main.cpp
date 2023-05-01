#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <limits>
#include <cstdlib>
#include <stdexcept>
#include <string>


#include "User.h"
#include "Service.h"
#include "Area.h"
#include "Tiquet.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13
#define N_MENU_OPTIONS 12
#define N_MAX_RAND_NUMBERS 99

using namespace std;

//coloca el cursor en las coordenadas x,y, según los valores recibidos
void gotoxy(short x, short y){
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // obtiene el identificador de la consola
   COORD pos = {x, y}; // crea una estructura COORD con las coordenadas
   SetConsoleCursorPosition(hConsole, pos); // establece la posición del cursor
}

//imprime el título y las opciones recibidas, contrala el cursor y devuelve la opción seleccionada
int selectOption(const char *title, string options[], int nOptions){
    int selectedOption = 1;     //guarda la opción seleccionada
    int key;                    //obtiene la tecla seleccionada
    bool repeat = true;         //maneja si se debe salir del do while o no

    do{                                     //se repite hasta que el usuario de un enter en la opción deseada
        system("cls");                      //limpia la pantalla

        gotoxy(5,1 + selectedOption);       //coloca el cursor
        cout << "==>";                      //se imprime el cursor que indica en que opción se encuentra

        gotoxy(10,0);                       //se coloca el cursor
        cout << title;                      //se imprime el título recibido

        for(int i = 0; i < nOptions; i++){              //se recorren el número de las opciones recibidas
            gotoxy(10,2 + i);                           //se coloca el cursor
            cout << i + 1 << ") " << options[i];        //se imprime el número y la opción correspondiente
        }

        do{
            key = getch();                                          //captura la tecla seleccionada

        }while(key != KEY_UP && key != KEY_DOWN && key != ENTER);   //se repite hasta que se seleccione enter, flecha arriba o abajo

        if(key == KEY_UP){                      //verifica si la tecla seleccionada es la tecla arriba
            selectedOption--;                   //de serlo, decrementa el número de la opción

            if(selectedOption < 1){             //verifica si el cursor está en la primera opción
                selectedOption = nOptions;      //en caso de estarlo, mueve el cursor de la primera opción hasta la última opción
            }
        }

        else if(key == KEY_DOWN){               //verifica si la tecla seleccionada es la flecha abajo
            selectedOption++;                   //incrementa el número de la opción en la que se este

            if(selectedOption > nOptions){      //verifica si el cursor está en la última opción
                selectedOption = 1;             //mueve el cursor de la última opción hasta la primera
            }
        }

        else if(key == ENTER){                  //verifica si la tecla seleccionada es un enter
            repeat = false;                     //de serlo, entonces pone el repeat en false, para salirse del do while
        }

    }while(repeat);                             //mientras repeat sea true, se repite el ciclo

    return selectedOption;                      //se retorna la opción seleccionada
}

int chooseUserTypes(List<User> *& users){
    int nUserType;
    const char *title = "Tipos de usuarios"; // título del menú de opciones
    string options[users->getSize()]; // opciones disponibles de la matriz

    for(int i = 0; i < users->getSize(); i++){
        User user = users->getElement();
        options[i] = user.getUserType();
        users->next();
    }

    nUserType = selectOption(title, options, users->getSize());
    users->goToPos(nUserType-1);

    return nUserType;
}

int chooseAreas(List<Area> *& areas){
    int nAreaDescrip;
    const char *title = "Areas disponibles"; // título del menú de opciones
    string options[areas->getSize()]; // opciones disponibles de la matriz

    for(int i = 0; i < areas->getSize(); i++){
        Area area = areas->getElement();
        options[i] = area.getDescription();
        areas->next();
    }

    nAreaDescrip = selectOption(title, options, areas->getSize());
    areas->goToPos(nAreaDescrip-1);

    return nAreaDescrip;
}

int chooseServices(List<Service> *& services){
    int nOperationServ;
    const char *title = "Areas disponibles"; // título del menú de opciones
    string options[services->getSize()]; // opciones disponibles de la matriz

    for(int i = 0; i < services->getSize(); i++){
        Service service = services->getElement();
        options[i] = service.getOperation();
        services->next();
    }

    nOperationServ = selectOption(title, options, services->getSize());
    services->goToPos(nOperationServ-1);

    return nOperationServ;
}

void setUserDate(User &user, List<User> *& users){
    string exit, input;
    do{

        cout << "Ingrese el tipo de usario: ";
        getline(cin, input);

        user.setUserType(input);

        cout << "\nIngrese su prioridad: ";
        getline(cin, input);

        user.setPriority(stoi(input));

        users->append(user);

        cout << "\nIngrese cero si desea salir: ";
        getline(cin, exit);

    }while(exit != "0");
}

void setAreas(List<Area> *& areas){
    string exit, code, description, input;
    int nWindows;
    do{

        cout << "Ingrese la descripcion del area: ";
        getline(cin, description);

        cout << "\nIngrese el código del area: ";
        getline(cin, code);

        cout << "\nIngrese la cantidad de ventallas: ";
        getline(cin, input);
        nWindows = stoi(input);

        Area area(nWindows, code);
        area.setDescription(description);

        areas->append(area);

        cout << "\nIngrese cero si desea salir: ";
        getline(cin, exit);

    }while(exit != "0");
}


void setServices(Service &service, List<Service> *& services, List<Area> * areas){
    string exit, input;
    int nAreaDescrip = 0;
    do{

        cout << "\nIngrese el tipo de servicio: ";
        getline(cin, input);

        service.setOperation(input);

        cout << "\nIngrese su prioridad: ";
        getline(cin, input);

        service.setPriority(stoi(input));

        nAreaDescrip = chooseAreas(areas);

        Area area = areas->getElement();

        service.setArea(area);

        services->append(service);

        cout << "\nIngrese cero si desea salir: ";
        getline(cin, exit);

    }while(exit != "0");
}


int main1(){

    List<User> *users;
    List<string> *windows;
    MinHeap<Tiquet> *queues;


    User user;

    user.setUserType("Regular");
    user.setPriority(1);
    cout << user.getUserType();

    Tiquet tiquet;
    tiquet.setConsecutive("C100");
    cout << tiquet.getConsecutive() << endl;
    tiquet.setSeconds(15);
    tiquet.setFPriority(15);

    Area area(5, "CA");
    area.setDescription("Cajas");
    area.addTiquet(tiquet);

    Service service(area);
    service.setOperation("Deposito");
    service.setPriority(2);

    windows = area.getWindows();
    windows->print();

    queues = area.getQueues();
    //cout << queues->removeFirst() << endl;
    queues->print();

    return 0;
}

int main(){

    List<User> *users = new ArrayList<User>;
    List<Service> *services = new ArrayList<Service>;
    List<Area> *areas = new ArrayList<Area>;

    List<string> *windows;
    MinHeap<Tiquet> *queues;


    User user;
    setUserDate(user, users);
    users->print();

    chooseUserTypes(users);

    User user1 = users->getElement();
    cout << user1.getUserType();
    getch();

    system("cls");


    Area area;
    setAreas(areas);
    areas->print();
    getch();

    chooseAreas(areas);
    Area area1 = areas->getElement();
    //area1.getWindows()->print();
    getch();
    system("cls");


    Service service;
    setServices(service, services, areas);
    chooseServices(services);
    Service service1 = services->getElement();
    cout << service1.getOperation();

    /*
    user.setUserType("Regular");
    user.setPriority(1);
    cout << user.getUserType();
    */



    return 0;
}
