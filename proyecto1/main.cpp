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

static int nTiquet = 100;

// Definición de una función que utiliza la variable global
void incNTiquet(){
    nTiquet++;
}

int getNCurrentSeconds(){
    //generar el tiempo
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;
    int second = timeinfo->tm_sec;
    second += hour * 3600 + minute * 60;
    return second;
}

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



bool isPositive(int num){
    if(num >= 0){
        return true;
    }
    cout << "\nEl número debe ser positivo" << endl;
    return false;
}

bool isInteger(string input){
    if(input[0] == '-'){
        input[0] = '0';
    }

    for(char c : input){
        if(!isdigit(c)){
            cout << "\nEl número debe ser entero" << endl;
            return false;
        }
    }

    return true;                        //si la entrada es entera retorna true
}

//solicita un número entero al usuario
string enterIntNumber(string message){
    string input;

    do {
        cout << "\n" << message;
        getline(cin, input);

    }while((!isInteger(input)) || (!isPositive(stoi(input))));       //se siguen solicitando lo datos hasta que se ingrese un entero positivo

    return input;
}

void queueStatus(List<Area> * areas){
    system("cls");
    int nWindows, nTiquets;

    for(int i = 0; i < areas->getSize(); i ++){
        Area area = areas->getElement();
        List<Window> *windows = area.getWindows();
        nWindows = windows->getSize();

        cout << "\n----------------------------------------------------" << endl;
        cout << "Area: " << area.getDescription() << endl;
        cout << "Cantidad de ventanillas: " << nWindows << endl;

        cout << "Tiquetes: [ ";
        MinHeap<Tiquet> *tiquets = area.getTiquets();
        nTiquets = tiquets->getSize();

        for(int j = 0; j < nTiquets; j++){
            Tiquet tiquet = tiquets->getElement(j);
            cout << tiquet.getConsecutive() << " ";
        }
        cout << " ]" << endl;

        cout << "\nÚltimos tiquetes atendidos por ventanilla " << endl;
        MinHeap<Tiquet> *attendTiquets = area.getAttendTiquets();
        int nAttendTiquets = attendTiquets->getSize();
        for(int j = 0; j < nAttendTiquets; j++){
            Tiquet attendTiquet = attendTiquets->getElement(j);
            string tiquetWindow = attendTiquet.getWindow();

            if(tiquetWindow != ""){
                cout << "Ventanilla: " << tiquetWindow << endl;
                cout << "Último tiquete atendido: " << attendTiquet.getConsecutive() << endl;
            }
        }

        areas->next();
    }

    cout << "\nPresione cualquier tecla para regresar al menu principal " << endl;
    getch();
}

void addUserDate(List<User> *& users){
    string exit, input, userType, message;
    int priority = 0;

    cout << "\nIngrese el tipo de usario: ";
    getline(cin, userType);

    message = "Ingrese su prioridad: ";
    input = enterIntNumber(message);


    priority = stoi(input);
    User user(userType, priority);
    users->append(user);
}

int chooseUserTypes(List<User> *& users){
    system("cls");
    users->goToStart();

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
        system("cls");

        if(option == 1){
            addUserDate(users);
        }

        else if(option == 2){
            deleteUserDate(users);
        }

    }while(option != 3);
}

void addAreas(List<Area> *& areas){
    string exit, code, description, input, message;
    int nWindows;

    cout << "\nIngrese la descripcion del area: ";
    getline(cin, description);

    cout << "Ingrese el código del area: ";
    getline(cin, code);

    message = "Ingrese la cantidad de ventallas: ";
    input = enterIntNumber(message);
    nWindows = stoi(input);

    Area area(description, nWindows, code);
    areas->append(area);
}

int chooseAreas(List<Area> *& areas){
    system("cls");
    areas->goToStart();

    int nAreaDescrip, nAreas;
    const char *title = "Areas disponibles"; // título del menú de opciones
    nAreas = areas->getSize();
    string options[nAreas]; // opciones disponibles de la matriz

    areas->goToStart();
    for(int i = 0; i < nAreas; i++){
        Area area = areas->getElement();
        options[i] = area.getDescription();
        areas->next();
    }

    nAreaDescrip = selectOption(title, options, nAreas);
    areas->goToPos(nAreaDescrip-1);

    system("cls");

    return nAreaDescrip;
}

void windowsModify(List<Area> *& areas){
    int areaSelected = chooseAreas(areas);
    int nNewWindows = 0;
    string input, message;

    areas->goToPos(areaSelected-1);
    Area area = areas->getElement();
    List<Window> *windows = area.getWindows();
    int nCurrentWindows = windows->getSize();

    cout << "Cantidad de ventanillas actuales: " << nCurrentWindows << endl;

    message = "Ingrese la cantidad de ventallas nuevas: ";
    input = enterIntNumber(message);
    nNewWindows = stoi(input);

    area.windows->clear();
    area.setWindows(nNewWindows);
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
        system("cls");

        if(option == 1){
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
    string exit, input, operation, message;
    int priority = 0;


        cout << "\nIngrese el tipo de servicio: ";
        getline(cin, operation);

        message = "Ingrese su prioridad: ";
        input = enterIntNumber(message);
        priority = stoi(input);

        chooseAreas(areas);
        Area area = areas->getElement();
        Service service(operation, priority, area);
        services->append(service);
}

int chooseServices(List<Service> *& services){
    //system("cls");
    services->goToStart();

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

void rearrangeService(List<Service> *& services){
    cout << "\nA continuación se mostrarán los servicios, seleccione el que desea reordenar" << endl;
    cout << "Presione cualquier tecla para continuar " << endl;
    getch();

    chooseServices(services);
    Service service = services->getElement();
    services->remove();

    cout << "\nA continuación se mostrarán los servicios, seleccione donde lo quiere colocar" << endl;
    cout << "Presione cualquier tecla para continuar " << endl;
    getch();

    int pos = chooseServices(services) - 1;
    services->remove();

    services->goToPos(pos);
    services->insert(service);
}

void serviceMenu(List<Service> *& services, List<Area> *& areas){
    const char * title = "Menu de servicios";
    string options[] = {"Agregar", "Eliminar", "Reordenar", "Regresar"};

    int option = 0;

    do{
        option = selectOption(title, options, 4);
        system("cls");

        if(option == 1){
            addServices(services, areas);
        }

        else if(option == 2){
            deleteService(services);
        }

        else if(option == 3){
            rearrangeService(services);
        }

    }while(option != 4);
}

void clearStatisticAndQueues(List<User> *& users, List<Service> *& services, List<Area> *& areas){
    //eliminar datos de las areas
    areas->goToStart();
    for(int i = 0; i < areas->getSize(); i++){
        Area area = areas->getElement();
        MinHeap<Tiquet> *tiquets = area.getTiquets();
        tiquets->clear();

        MinHeap<Tiquet> *attendedTiquets = area.getAttendTiquets();
        attendedTiquets->clear();

        List<Window> *windows = area.getWindows();
        windows->goToStart();
        for(int j = 0; j < windows->getSize(); j++){
            Window window = windows->getElement();
            window.setNAttendedTiquets(0);
            windows->remove();
            windows->insert(window);
            windows->next();
        }

        area.setTotalTime(0);
        area.setNTiquets(0);
        areas->remove();
        areas->insert(area);
        areas->next();
    }

    services->goToStart();
    for(int i = 0; i < services->getSize(); i++){
        Service service = services->getElement();
        service.setNTiquets(0);
        services->remove();
        services->insert(service);
        services->next();
    }

    users->goToStart();
    for(int i = 0; i < users->getSize(); i++){
        User user = users->getElement();
        user.setNTiquets(0);
        users->remove();
        users->insert(user);
        users->next();
    }

    nTiquet = 100;
}


void administrationMenu(List<User> *& users, List<Service> *& services, List<Area> *& areas){
    int option;
    const char *title = "Administración"; // título del menú de opciones
    string options[] = {"Tipos de usuarios", "Áreas", "Servicios disponibles", "Limpiar cola y estadística", "Regresar"}; // opciones disponibles de la matriz

    do{

        option = selectOption(title, options, 5);
        system("cls");

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
            clearStatisticAndQueues(users, services, areas);
        }

    }while(option != 5);
}

void generateTiquet(List<User> *& users, List<Service> *& services, List<Area> *& areas){
    chooseUserTypes(users);
    chooseServices(services);

    User user = users->getElement();
    Service service = services->getElement();

    //generar prioridad final
    int userPriority = user.getPriority();
    int servicePriority = service.getPriority();
    int finalPriority = userPriority * 10 + servicePriority;

    //generar el consecutivo
    Area aService = service.getArea();
    int posArea = areas->indexOf(aService);
    areas->goToPos(posArea);
    Area area = areas->getElement();
    string consecutive = area.getCode() + to_string(nTiquet);

    int second = getNCurrentSeconds();
    Tiquet tiquet(second, consecutive, finalPriority);
    area.addTiquet(tiquet);
    incNTiquet();

    user.increaseNTiquets();
    service.increaseNTiquets();
    area.increaseNTiquets();
    users->remove();
    services->remove();
    users->insert(user);
    services->insert(service);

    cout << posArea << " " << area.getTotalTime() << endl;
    getch();
    areas->remove();
    areas->insert(area);
}

void tiquetMenu(List<User> * users, List<Service> *& services, List<Area> *& areas){

    const char *title = "Menu de tiquetes"; // título del menú de opciones
    string options[] = {"Seleccionar tipo de cliente y servicio", "Regresar"}; // opciones disponibles de la matriz
    int option = 0;

    do {

        option = selectOption(title, options, 2);

        if(option == 1){
            system("cls");
            generateTiquet(users, services, areas);
        }

    }while(option != 2);
}

int chooseWindow(Area area){
    system("cls");

    List<Window> *windows = area.getWindows();
    int nWindows = windows->getSize();
    int nChooseWindow;

    const char *title = "Ventanillas disponibles"; // título del menú de opciones
    string options[windows->getSize()]; // opciones disponibles de la matriz

    windows->goToStart();
    for(int i = 0; i < nWindows; i++){
        Window window = windows->getElement();
        string windowCode = window.getCode();
        options[i] = windowCode;
        windows->next();
    }

    nChooseWindow = selectOption(title, options, nWindows);
    windows->goToPos(nChooseWindow-1);

    system("cls");

    return nChooseWindow;
}

void attend(List<Area> *& areas){
    int nChooseArea, nChooseWindow;

    nChooseArea = chooseAreas(areas);
    areas->goToPos(nChooseArea-1);
    Area area = areas->getElement();

    nChooseWindow = chooseWindow(area);
    List<Window> *windows = area.getWindows();
    windows->goToPos(nChooseWindow-1);
    Window window = windows->getElement();
    string windowCode = window.getCode();

    MinHeap<Tiquet> *tiquets = area.getTiquets();
    MinHeap<Tiquet> *attendedTiquets = area.getAttendTiquets();

    if(tiquets->getSize() > 0){
        Tiquet tiquetToAttend = tiquets->removeFirst();
        tiquetToAttend.setWindow(windowCode);

        for(int i = 0; i < attendedTiquets->getSize(); i++){
            Tiquet attendedTiquet = attendedTiquets->getElement(i);

            if(attendedTiquet.getWindow() == windowCode){
                attendedTiquets->remove(i);
            }
        }
        window.increaseNAttendedTiquets();
        windows->remove();
        windows->insert(window);

        int second = getNCurrentSeconds();
        int finalSeconds = second - tiquetToAttend.getISeconds();
        area.addTime(finalSeconds);

        area.addAttendTiquet(tiquetToAttend);
        area.increseaNTiquetsAttended();
        areas->remove();
        areas->insert(area);
    }
    else{
        cout << "\nNo hay usuarios a la espera" << endl;
        getch();
        cout << "\nPresione cualquier tecla para continuar " << endl;
    }
}

void systemStatistics(List<Area> *areas, List<Service> *services, List<User> *users){
    cout << "\nEstadísticas del sistema " << endl;

    cout << "\n------------------------------------------------------------------------" << endl;
    areas->goToStart();
    for(int i = 0; i < areas->getSize(); i++){
        Area area = areas->getElement();

        cout << "\nArea: " << area.getDescription() << endl;
        cout << "Tiempo promedio de espera: " << area.getAverageTime() << " segundos" << endl;
        cout << "Cantidad de tiquetes dispensados: " << area.getNTiquets() << endl;

        //cout << "\n------------------------------------------------------------------------" << endl;
        cout << "\nCantidad de tiquetes antendidos por ventanilla" << endl;
        List<Window> *windows = area.getWindows();
        windows->goToStart();
        for(int j = 0; j < windows->getSize(); j++){
            Window window = windows->getElement();
            cout << "\nVentanilla: " << window.getCode() << endl;
            cout << "Cantidad de tiquetes atendidos: " << window.getAttendedTiquets() << endl;

            windows->next();
        }

        areas->next();
    }

    cout << "\n------------------------------------------------------------------------" << endl;
    services->goToStart();
    for(int i = 0; i < services->getSize(); i++){
        Service service = services->getElement();

        cout << "\nServicio: " << service.getOperation() << endl;
        cout << "Cantidad de tiquetes solicitados: " << service.getNTiquets() << endl;

        services->next();
    }

    cout << "\n------------------------------------------------------------------------" << endl;
    users->goToStart();
    for(int i = 0; i < users->getSize(); i++){
        User user = users->getElement();

        cout << "\nUsuario: " << user.getUserType() << endl;
        cout << "Cantidad de tiquetes emitidos: " << user.getNTiquets() << endl;

        users->next();
    }

    cout << "\nPresione cualquier tecla para continuar " << endl;
    getch();
}

void mainMenu(List<User> *users, List<Service> *services, List<Area> *areas){

    int option;
    const char *title = "Menu principal"; // título del menú de opciones
    string options[] = {"Estado de las colas", "Tiquetes", "Atender", "Administración", "Estadísticas del Sistemas", "Salir"}; // opciones disponibles de la matriz

    do{
        try{

            option = selectOption(title, options, 6);
            system("cls");

            if(option == 1){
                areas->goToStart();
                queueStatus(areas);
            }

            if(option == 2){
                tiquetMenu(users, services, areas);
            }

            else if(option == 3){
                attend(areas);
            }

            else if(option == 4){
                administrationMenu(users, services, areas);
            }

            else if(option == 5){
                systemStatistics(areas, services, users);
            }

        }

        catch(const runtime_error &e){
            cerr << "\nUps, algo salió mal \n" << "Error: " << e.what() <<"\nPresione cualquier tecla para continuar" << endl;   //se manda el error correspondiente
            getch();
        }

    }while(option != 6);
}

int main(){

    setlocale(LC_ALL, "spanish");

    List<User> *users = new ArrayList<User>;
    List<Service> *services = new ArrayList<Service>;
    List<Area> *areas = new ArrayList<Area>;

    mainMenu(users, services, areas);

    delete users;
    delete services;
    delete areas;

    return 0;
}
