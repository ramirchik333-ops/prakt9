#include <iostream>
using namespace std;

double Head = 20.0; // размер служебного заголовка
double maxPack = 1500.0; //макс размер пакета
double minPack = 64.0; //мин допустимый размер

void AddHeader(double* data, int size) //увеличить размер каждого пакета на размер служебного заголовка;
{
    for (int i = 0; i < size; i++)
        data[i] += Head;
}

void limitMaxsize(double* data, int size) //ограничить максимальный размер пакета;
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] > maxPack) data[i] = maxPack;
    }
}

void dropToo(double* data, int size) //слишком большие пакеты заменить на 0 ;
{
    for (int i = 0; i < size; i++)
        if (data[i] > maxPack) data[i] = 0;
}

void valve(double* data, int size) // слишком маленькие пакеты заменить минимально допустимым размером.
{
    for (int i = 0; i < size; i++)
        if (data[i] < minPack) data[i] = minPack;
}

void(*processos[])(double*, int) = {
    AddHeader, limitMaxsize, dropToo, valve
};

void aoa(double* data, int size, void(*processos)(double*, int))
{
    if (processos != nullptr)
        processos(data, size);
    else cout << "ошибка: указатель на функцию пустой" << endl;
}

void print(double* data, int size)
{
    for (int i = 0; i < size; i++)
        cout << data[i] <<  " ";
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    const int maxSize = 100;
    double data[maxSize];
    double origData[maxSize]; //массив для хранения копии
    int size = 0;
    int choice = 0;
    do
    {
        cout << "Меню" << endl;
        cout << "1. Ввести данные" << endl;
        cout << "2. Показать данные" << endl;
        cout << "3. Выбрать и выполнить обработку" << endl;
        cout << "4. Восстановить исходные данные" << endl;
        cout << "5. Выход" << endl;
        cout << "Выберите действие" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1: {
            cout << "Введите кол-во пакетов до 100" << endl;
            cin >> size;
            if (size > maxSize) size = maxSize;
            cout << "Введите размеры пакетов" << endl;
            for (int i = 0; i < size; i++)
                cin >> data[i];
            for (int i = 0; i < size; i++)
                origData[i] = data[i];
            cout << "данные введены успешно" << endl;
            break;
        }
        case 2: {
            if (size == 0) cout << "Массив пуст, сначала введите данные" << endl;
            else {
                cout << "Текущие данные: ";
                print(data, size);
            }
            break;
        }
        case 3: {
            if (size == 0) {
                cout << "Массив пуст, обрабатывать нечего" << endl; break;
            }
            cout << "Массив до обработки: ";
            print(data, size);
            cout << endl;
            cout << "Выберете операцию: " << endl;
            cout << "1. Добавить размер заголовка" << endl;
            cout << "2. Ограничить максимальный размер пакета" << endl;
            cout << "3. Слишком большие пакеты заменить на 0" << endl;
            cout << "4. Слишком маленькие пакеы заменить минимально допустимым размером";
            int opChoice;
            cout << "Ваше действие: " << endl;
            cin >> opChoice;
            if (opChoice >= 1 && opChoice <= 4)
            {
                void(*selectedproc)(double*, int) = processos[opChoice - 1];
                aoa(data, size, selectedproc);
            }
            else cout << "Неверный номер операции" << endl;
            cout << "Массив после обработки: ";
            print(data, size);
            break;
        }
        case 4: {
            if (size == 0) cout << "Нечего восстанавливать" << endl;
            else
            {
                for (int i = 0; i < size; i++)
                    data[i] = origData[i];
            }
            cout << "Исходне данные восстановлены" << endl;
            break;
        }
        case 5: {
            cout << "Удаление мира..." << endl;
            break;
        }
        default: {
            cout << "Ошибка ввода";
            break;
        }
        } 
    }
    while (choice != 5);
}

