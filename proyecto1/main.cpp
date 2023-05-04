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
//#define N_MENU_OPTIONS 12
//#define N_MAX_RAND_NUMBERS 99

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

void setTiquet(string code, int nTiquet, int sPriority, int uPriority, Area area){

    string consecutive = code;
    int numero = nTiquet;
    //int seconds = 0;
    int fPriority = 0;

    consecutive += to_string(numero);
    nTiquet++;

    fPriority = uPriority * 10 + sPriority;

    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;
    int second = timeinfo->tm_sec;

    second += hour * 3600 + minute * 60;

    Tiquet tiquet(second, consecutive, fPriority);
    cout << "Consecutivo: " << tiquet.getConsecutive() << endl;
    cout << "Segundos iniciales: " << tiquet.getISeconds() << endl;
    cout << "Prioridad final: " << tiquet.getFPriority() << endl;

    area.addTiquet(tiquet);
}

void queueStatus(List<Area> * areas){
    system("cls");

    for(int i = 0; i < areas->getSize(); i ++){
        Area area = areas->getElement();
        cout << "\nArea: " << area.getDescription() << endl;
        cout << "Cantidad de ventanillas: " << area.getWindows()->getSize() << endl;

        cout << "Tiquetes: [ ";
        for(int j = 0; j < area.getTiquets()->getSize(); j++){
            Tiquet tiquet = area.getTiquets()->getElement(j);
            cout << tiquet.getConsecutive() << " ";
        }
        cout << " ]" << endl;
        areas->next();
    }

    cout << "\nPresione cualquier tecla para regresar al menu principal " << endl;
    getch();
}

void addUserDate(List<User> *& users){
    string exit, input, userType;
    int priority = 0;

    do{

        cout << "\nIngrese el tipo de usario: ";
        getline(cin, userType);

        cout << "Ingrese su prioridad: ";
        getline(cin, input);

        priority = stoi(input);
        User user(userType, priority);
        users->append(user);

        cout << "\nIngrese cero si desea salir: ";
        getline(cin, exit);

    }while(exit != "0");
}

int chooseUserTypes(List<User> *& users){
    system("cls");

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

    system("cls");

    return nUserType;
}

void deleteUserDate(List<User> *& users){
    int userSelected = chooseUserTypes(users);

    users->goToPos(userSelected-1);
    users->remove();
}

void userTypeMenu(List<User> *& users){
    const char * title = "Menu de tipos de usuarios";
    string options[] = {"Agregar", "Eliminar", "Regresar"};
    int option = 0;

    do{
        option = selectOption(title, options, 3);

        if(option == 1){
            system("cls");
            addUserDate(users);
        }

        else if(option == 2){
            deleteUserDate(users);
        }

    }while(option != 3);
}

void addAreas(List<Area> *& areas){
    string exit, code, description, input;
    int nWindows;
    do{

        cout << "\nIngrese la descripcion del area: ";
        getline(cin, description);

        cout << "Ingrese el código del area: ";
        getline(cin, code);

        cout << "Ingrese la cantidad de ventallas: ";
        getline(cin, input);
        nWindows = stoi(input);

        Area area(description, nWindows, code);
        areas->append(area);

        cout << "\nIngrese cero si desea salir: ";
        getline(cin, exit);

    }while(exit != "0");
}

int chooseAreas(List<Area> *& areas){
    system("cls");

    int nAreaDescrip;
    const char *title = "Areas disponibles"; // título del menú de opciones
    string options[areas->getSize()]; // opciones disponibles de la matriz

    areas->goToStart();
    for(int i = 0; i < areas->getSize(); i++){
        Area area = areas->getElement();
        options[i] = area.getDescription();
        areas->next();
    }

    nAreaDescrip = selectOption(title, options, areas->getSize());
    areas->goToPos(nAreaDescrip-1);

    system("cls");

    return nAreaDescrip;
}

void windowsModify(List<Area> *& areas){
    int areaSelected = chooseAreas(areas);
    int nWindows = 0;
    string input;

    areas->goToPos(areaSelected-1);
    Area area = areas->getElement();

    cout << "Cantidad de ventanillas actuales: " << area.getWindows()->getSize() << endl;


    cout << "Ingrese la cantidad de ventallas nuevas: ";
    getline(cin, input);
    nWindows = stoi(input);

    area.getWindows()->clear();
    area.setWindows(nWindows);
}

void deleteAreas(List<Area> *& areas, List<Service> *& services){
    int areaSelected = chooseAreas(areas);

    areas->goToPos(areaSelected-1);
    Area area = areas->getElement();
    area.getWindows()->clear();

    services->goToStart();
    for(int i = 0; i < services->getSize(); i++){
        Service service = services->getElement();
        Area aService = service.getArea();

        if(area.getDescription() == aService.getDescription()){
            services->remove();
        }
        services->next();
    }
    areas->remove();
}

void areaMenu(List<Area> *& areas, List<Service> *& services){
    const char * title = "Menu areas";
    string options[] = {"Agregar", "Modificar cantidad de ventanillas", "Eliminar", "Regresar"};
    string confirmation;
    int option = 0;

    do{
        option = selectOption(title, options, 4);

        if(option == 1){
            system("cls");
            addAreas(areas);
        }

        else if(option == 2){
            windowsModify(areas);

        }

        else if(option == 3){
            cout << "Está seguro de borrar el área ingrese (1) para confirmar: ";
            getline(cin, confirmation);

            if(confirmation == "1")
                deleteAreas(areas, services);
        }

    }while(option != 4);
}

void addServices(List<Service> *& services, List<Area> * areas){
    string exit, input, operation;
    int nAreaDescrip = 0, priority = 0;

    do{

        cout << "\nIngrese el tipo de servicio: ";
        getline(cin, operation);

        cout << "Ingrese su prioridad: ";
        getline(cin, input);

        priority = stoi(input);
        chooseAreas(areas);
        Area area = areas->getElement();
        Service service(operation, priority, area);
        services->append(service);

        system("cls");
        cout << "\nIngrese cero si desea salir: ";
        getline(cin, exit);

    }while(exit != "0");
}

int chooseServices(List<Service> *& services){
    system("cls");

    int nOperationServ;
    const char *title = "Servicios disponibles"; // título del menú de opciones
    string options[services->getSize()]; // opciones disponibles de la matriz

    for(int i = 0; i < services->getSize(); i++){
        Service service = services->getElement();
        options[i] = service.getOperation();
        services->next();
    }

    nOperationServ = selectOption(title, options, services->getSize());
    services->goToPos(nOperationServ-1);

    system("cls");

    return nOperationServ;
}

void deleteService(List<Service> *& services){
    int serviceSeleted = chooseServices(services);

    services->goToPos(serviceSeleted-1);
    services->remove();
}

void serviceMenu(List<Service> *& services, List<Area> *& areas){
    const char * title = "Menu de servicios";
    string options[] = {"Agregar", "Eliminar", "Reordenar", "Regresar"};

    int option = 0;

    do{
        option = selectOption(title, options, 3);

        if(option == 1){
            system("cls");
            addServices(services, areas);
        }

        else if(option == 2){
            deleteService(services);
        }

        else if(option == 3){
            //HACER EL REORDENAR
        }

    }while(option != 4);
}


void administrationMenu(List<User> *& users, List<Service> *& services, List<Area> *& areas){
    int option;
    const char *title = "Administración"; // título del menú de opciones
    string options[] = {"Tipos de usuarios", "Áreas", "Servicios disponibles", "Limpiar cola y estadística", "Salir"}; // opciones disponibles de la matriz

    do{

        option = selectOption(title, options, 5);

        if(option == 1){
            userTypeMenu(users);
        }

        else if(option == 2){
            areaMenu(areas, services);
        }

        else if(option == 3){
            serviceMenu(services, areas);
        }

        else if(option == 4){
            //HACER EL LIMPIAR COLAS Y ESTADISTICAS
        }

    }while(option != 5);
}

void mainMenu(){

    List<User> *users = new ArrayList<User>;
    List<Service> *services = new ArrayList<Service>;
    List<Area> *areas = new ArrayList<Area>;

    int option;
    const char *title = "Menu principal"; // título del menú de opciones
    string options[] = {"Estado de las colas", "Tiquetes", "Atender", "Administración", "Estadísticas del Sistemas", "Salir"}; // opciones disponibles de la matriz

    system("cls");

    /*setTiquet("CA", 100, 1, 2, areas->getElement());
    setTiquet("CA", 101, 1, 2, areas->getElement());
    areas->next();
    setTiquet("SC", 100, 1, 2, areas->getElement());
    */

    /*chooseAreas(areas);
    Area area1 = areas->getElement();
    cout << "\nArea elegida: " << area1.getDescription() << endl;
    windows = area1.getWindows();
    windows->print();
    getch();
    system("cls");
    */
    do{

        option = selectOption(title, options, 6);

        if(option == 1){
            areas->goToStart();
            queueStatus(areas);
        }

        else if(option == 4){
            administrationMenu(users, services, areas);
        }

    }while(option != 6);


}


int main(){



    List<User> *users = new ArrayList<User>;
    List<Service> *services = new ArrayList<Service>;
    List<Area> *areas = new ArrayList<Area>;

    List<string> *windows;
    MinHeap<Tiquet> *aTiquets;

    mainMenu();

    /*int nTiquet = 100;

    setTiquet("C", nTiquet, 5, 3, area);

    getch();

    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;
    int second = timeinfo->tm_sec;

    second += hour * 3600 + minute * 60;
    cout << "Segundos al ser atendido: " << second;
*/
    /*
    setUserDate(users);
    users->print();
    chooseUserTypes(users);

    User user1 = users->getElement();
    cout << "\nUsuario elegido: " << user1.getUserType();
    getch();
    system("cls");


    Area area;
    setAreas(areas);
    areas->print();
    getch();

    chooseAreas(areas);
    Area area1 = areas->getElement();
    cout << "\nArea elegida: " << area1.getDescription() << endl;
    windows = area1.getWindows();
    windows->print();
    getch();
    system("cls");

    setServices(services, areas);
    chooseServices(services);
    system("cls");
    Service service1 = services->getElement();
    cout << "\nServicio elegido: " << service1.getOperation();
    */
    return 0;
}
