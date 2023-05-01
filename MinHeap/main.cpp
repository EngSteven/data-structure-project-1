#include <iostream>
#include <time.h>
#include <limits>
#include <conio.h>

#include "ArrayList.h"
#include "MinHeap.h"

using std::cout;
using std::endl;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::cerr;

//retorna true, en caso de que el numero ingresado es un entero, false de lo contrario
bool isInteger(char input[], int & num){

    char *end;                          //se declara un puntero de caracteres
    num = strtol(input, &end, 10);      //convierte el valor ingresado a entero y se lo pasa al número

    if (end == input || *end != '\0'){  //verifica si no se ha encontrado un número  o si el primer carácter no es un número
        return false;                   //de serlo, retorna false
    }

    return true;                        //si la entrada es entera retorna true
}

//solicita un número entero al usuario
void enterNumber(char input[], int & num){
    //cout << "\nIngrese un número entero: ";                                 //se manda el mensaje al usuario
    while(!(cin >> input) || (!isInteger(input, num)) || (num < 0)){                     //se siguen solicitando lo datos hasta que se ingrese un entero positivo
        cout << "\nEntrada inválida, el número debe ser un entero positivo" << endl;   //se manda el aviso al usuario
        cout << "\nIngrese de nuevo: ";                             //se vuelve a solicitar el entero
        cin.clear();                                                        //se limpia el cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');                //se ignora la entrada en caso de que esté mal ingresada
    }
}

//carga n numeros enteros aleatorios en el heap
void loadRandNumsMinHeap(MinHeap<int> *& heap, int nElements){
    for(int i = 0; i < nElements; i++){                 //se recorren todas las filas de la matriz
        heap->insert(rand() % 100);
    }
}

//carga n valores enteros aleatorios en el array
void loadRandNumsArray(int *& arr, int nElements){
    for(int i = 0; i < nElements; i++){                 //se recorren todas las filas de la matriz
        arr[i] = rand() % 100;
    }
}

int main(){

    setlocale(LC_ALL, "spanish");           //para usar letras en español

    MinHeap<int> *heap1 = new MinHeap<int>();   //se inicializa el heap 1
    MinHeap<int> *heap2 = new MinHeap<int>();   //se inicializa el heap 2
    List<int> *list = new ArrayList<int>();     //se inicializa la lista
    int *arr;                                   //se inicializa el array

    int num;
    char input[1000];

    srand(time(0));                         //permite generar números rands distintos

    cout << "Ingrese un entero positivo, para la cantidad de elementos a cargar en los dos heaps: ";
    enterNumber(input, num);                //se solicita un numero entero positivo, que corresponde a los n elementos iniciales a cargar en los heaps

    try{
        loadRandNumsMinHeap(heap1, num);    //se cargan los n enteros en el heap 1

    }
    catch(const runtime_error &e){
        cerr << "\nUps, algo salió mal \n" << "Error: " << e.what() <<"\nPresione cualquier tecla para continuar" << endl;   //se manda el error correspondiente
        getch();
    }

    try{
        loadRandNumsMinHeap(heap2, num);    //se cargan los n enteros en el heap 2
    }
    catch(const runtime_error &e){
        cerr << "\nUps, algo salió mal \n" << "Error: " << e.what() <<"\nPresione cualquier tecla para continuar" << endl;   //se manda el error correspondiente
        getch();
    }

    cout << "\nPrint del Heap 1 " << endl;
    heap1->print();                             //se imprime el contenido del heap 1

    cout << "\nPrint del Heap 2 " << endl;
    heap2->print();                             //se imprime el contenido del heap 2

    try{
        heap1->merge(heap2);                    //se hace merge del heap 1 con el heap 2
    }
    catch(const runtime_error &e){
        cerr << "\nUps, algo salió mal \n" << "Error: " << e.what() <<"\nPresione cualquier tecla para continuar" << endl;   //se manda el error correspondiente
        getch();
    }

    cout << "\nPrint del Heap 1 después del merge con el Heap 2" << endl;
    heap1->print();                             //se imprime el resultado del merge anterior

    cout << "\nIngrese un entero positivo, para calcular el top n del Heap 1: ";
    enterNumber(input, num);                    //se solicita los n top del heap 1

    try{
        list = heap1->removeTop(num);           //se hace el removeTop del heap 1 y se guarda el resultado en la lista
    }
    catch(const runtime_error &e){
        cerr << "\nUps, algo salió mal \n" << "Error: " << e.what() <<"\nPresione cualquier tecla para continuar" << endl;   //se manda el error correspondiente
        getch();
    }

    cout << "\nPrint después de hacer remove top al heap 1" << endl;
    list->print();                              //se imprime el resultado del removeTop del heap 1
    delete list;                                //se libera el espacio en memoria de la lista

    cout << "\nHaciendo remove first hasta que el heap 1 quede vacío" << endl;
    while(!heap1->isEmpty()){                   //se repite mientras el heap 1 no esté vacío
        cout << heap1->removeFirst() << " ";    //se va imprimiendo y removiendo con remove first, los elementos del heap 1
    }

    cout << "\n\nIngrese un entero positivo, para los n elementos a cargar en el arreglo a usar en el heapify: ";
    enterNumber(input, num);                    //se solicitan los n elementos aleatorios a cargar en el array, para probar el heapify
    arr = new int[num];                         //se crea el arr con el n elementos ingresado

    try{
        loadRandNumsArray(arr, num);            //se cargar los n enteros aleatorios en el arreglo
        heap1->heapify(arr, num);               //se hace el heapify del heap 1
    }
    catch(const runtime_error &e){
        cerr << "\nUps, algo salió mal \n" << "Error: " << e.what() <<"\nPresione cualquier tecla para continuar" << endl;   //se manda el error correspondiente
        getch();
    }

    cout << "\nPrint del heap 1 después de hacer el heapify" << endl;
    heap1->print();                             //se imprime el resultado del heapify del heap 1

    try{
        list = heap1->removeTop(heap1->getSize());      //se hace un remove top con los elementos resultantes del heap 1
        cout << "\nPrint de la lista después de hacer remove top de todos los elementos del heap 1 " << endl;
        list->print();                                  //se imprime el resultado del removeTop anterior
        delete list;                                    //se libera el espacio en memoria de la lista
    }
    catch(const runtime_error &e){
        cerr << "\nUps, algo salió mal \n" << "Error: " << e.what() <<"\nPresione cualquier tecla para continuar" << endl;   //se manda el error correspondiente
        getch();
    }

    //se liberan los espacios en memoria restantes
    delete arr;
    delete heap1;
    delete heap2;

    return 0;
}
