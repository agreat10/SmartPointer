
#define _CRT_SECURE_NO_WARNINGS
//#define gotoxy(x, y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y})

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <limits>


using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void Display(int row,const vector<vector<string> > &tab1)
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout << "№                Фамилия                Имя            Отчество             телефон               Город \n\n";
    
    for (size_t i = 0; i < row; i++)
    {
        SetConsoleTextAttribute(hConsole, 3);
        cout << i + 1 << "  ";
        SetConsoleTextAttribute(hConsole, 14);
        for (string j : tab1[i])
        {
            cout.width(20);
            cout  << j ;            
        }
        cout << endl;
    }cout << endl;
    SetConsoleTextAttribute(hConsole, 7);
}
string IntVvod()
{
    string user;
    char c;
    int i;
    cout << endl;
    SetConsoleTextAttribute(hConsole, 3);
    while (true)
    {
        c = _getch();
        i = (int)c;       
        if (i == 13)
        {
             return user;
        }
        else if ((i > 47) && (i < 58))
        {
            cout << c;
            user.push_back(c);
        }
        else if(i == 8)
        {           
            if (!user.empty()) {
                user.pop_back();
                cout << '\r' << "                         " << '\r';
                cout << user;
            }
            
        }
    }
}
string KirVvid()
{
    string user;
    char c;
    int i;
    cout << endl;
    SetConsoleTextAttribute(hConsole, 3);
    while (true)
    {
        c = _getch();
        i = (int)c;        
        if (i == 13) 
        {
            return user;
        }
        else if ((i > -65) && (i< 0)||(i == -88)||(i== -72))
        { 
            cout << c;
        user.push_back(c);
        }
        else if (i == 8)
        {
            if (!user.empty()) {
                user.pop_back();
                cout << '\r' << "                         " << '\r';
                cout << user;
            }
        }
    }
}
void AddUser(vector<vector<string> > &vec,int &count)
{
    string user;
    vector <string> temp;
    
    cin.sync(); 
    char q = '2';
    cout << "Добавляем нового человека? 1- да, 0 - отмена\n";
    while (q!='1')
    {
        q = _getch();
        if (q == '0') return;
    }
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\nВведите фамилию: "; user = KirVvid(); /*getline(cin, user, '\n');*/
    temp.push_back(user);
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\nВведите Имя : "; user = KirVvid(); /*getline(cin, user);*/
    temp.push_back(user);
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\nВведите Отчество: "; user = KirVvid(); /*getline(cin, user);*/ 
    temp.push_back(user);
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\nВведите номер телефона : "; user = IntVvod(); /*getline(cin, user);*/
    temp.push_back(user);
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\nВведите Город : "; user = KirVvid(); /*getline(cin, user);*/ 
    temp.push_back(user);
    vec.push_back(temp);
    ++count;
}

void SaveinFile(int row, const vector<vector<string> >& vec)
{
    ofstream file{ "baza.txt" };
    for (size_t i = 0; i < row; i++)
    {       
        for (string j : vec[i])
        {
            file << j << "\n";
        }        
    }
    file.close();
}
void OpeninFile(int row,  vector<vector<string> >& vec)
{
    char c[30];    
    ifstream file{ "baza.txt" };
    for (size_t i = 0; i < row; i++)
    {vector <string> temp;
        for (size_t j = 0; j < 5; j++)
        {            
            (file.getline(c, 30));           
            temp.emplace_back(c);
        }
        vec.push_back(temp);
    }    
    file.close();
}
void Search(int row,const  vector<vector<string> >& vec)
{    
    string user;
    bool flag = true;
    cout << "Будем искать!\nВведите Фамилию, телефон или город: ";
    char c;
    int i{0};
    while (i!=13)
    {
        c = _getch();
        i = (int)c;
        
        if ((i > 47) && (i < 58)|| ((i > -65) && (i < 0) || (i == -88) || (i == -72)))
        {
            cout << c;
            user.push_back(c);
        }
    }
    cout << endl;
   // getline(cin, user);/////////////////////////
    for (size_t i = 0; i < row; i++)
    {
        for (string j : vec[i])
        {
            if (j == user)
            {
                flag = false;
                SetConsoleTextAttribute(hConsole, 3);
                cout << i + 1 << "  ";  
                SetConsoleTextAttribute(hConsole, 6);
                    for (string jj : vec[i])
                    {cout << jj << "\t\t";}
                cout << endl;
            }
        }SetConsoleTextAttribute(hConsole, 7);
    }cout << endl;
    if (flag) { SetConsoleTextAttribute(hConsole, 4); cout << "Записи с таким именем не существует!!!" << endl ;
    SetConsoleTextAttribute(hConsole, 7);
    }
}
void Erase(int &row,   vector<vector<string> >& vec)
{
    int c;
    auto begin = vec.begin();
    cout << "Введите порядковый номер удаляемой записи: ";
    cin >> c;
    if (c<1 || c>row) { SetConsoleTextAttribute(hConsole, 4); 
    cout << "Записи с таким номером не существует.\n ";
    SetConsoleTextAttribute(hConsole, 7); return; }

    for (string j : vec[c-1])
    {
        cout << j << "\t";
    }
    cout << endl;
    cin.sync();
    char q = '2';
    SetConsoleTextAttribute(hConsole, 4);
    cout << "Удаляем эту запись? 1- да, 0 - отмена\n";
    SetConsoleTextAttribute(hConsole, 7);
    while (q != '1')
    {
        q = _getch();
        if (q == '0') return;
    }
    vec.erase(begin + c-1);
    --row;
}
void Editors(int& row, vector<vector<string> >& vec)
{
    int c; 
    int count = 0;
    string arr[5] = { "Фамилия","Имя","Отчество","Телефон","Город" };
    char q = '5';
    auto begin = vec.begin();
    cout << "Введите порядковый номер редактируемой записи: ";
    cin >> c;
    if (c<1 || c>row) {
        SetConsoleTextAttribute(hConsole, 4); 
        cout << "Записи с таким номером не существует.\n ";
        SetConsoleTextAttribute(hConsole, 7); return; }

    for (string j : vec[c - 1])
    {
        cout << j << "\t";
    }
    cout << endl;//////////////////////
    for (string &j : vec[c - 1])
    {
        q = '5';
        SetConsoleTextAttribute(hConsole, 4);
        cout << arr[count] << "  ---- " <<  j << endl;
        ++count;
        SetConsoleTextAttribute(hConsole, 6);
        cout << "Редактируем? 1 - да, 0 - нет. \n";
        SetConsoleTextAttribute(hConsole, 7);
        while (q!='0')
            {
                q = _getch();            
                if (q == '1')
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << "Ведите " << arr[count-1] << " -> ";
                    if (count == 4) j = IntVvod();
                    else j = KirVvid();
                    q = '0';
                    cout << endl;
                    SetConsoleTextAttribute(hConsole, 14);
                }

            }
        
    }
    
}
void Scrin()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n\n\n\n\n\n\n                                      Экзаменационная работа студента Академии \"ШАГ\" " << endl;
    cout << "                                             Комолова Александра Васильевича\n";
    cout << "                                             по языку программирования с++.\n";
    cout << "                                                        Органайзер\n";
    SetConsoleTextAttribute(hConsole, 7);
    cout << "\n\n\n\n\n\nДля продолжения нажмите любую клавишу ";
    char w = _getch();
    system("cls");
}

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    

    Scrin();
    vector<vector<string>> vec;   
    string user;
    char c[30];
    int count = 0;
    ifstream file{ "baza.txt" };
    while (file)
    {
        file.getline(c, 30);
        ++count;
    }
    file.close();count /= 5;

    //cout << "Количество человек в базе -> " << count << endl;
    
    if (!count)
    {
        SetConsoleTextAttribute(hConsole, 4);
        cout << "Количество записей в базе -> " << count << endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Давайте добавим первого первого человека.\n";
        AddUser(vec,count);        
    }
    else OpeninFile(count, vec);
   
    char z{' '};

    while (z != '0')
    {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\nКоличество записей в базе -> " << count << endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Выберите действие: \n0 = Выход" << endl <<
            "1 = Добавить" << endl <<
            "2 = Редактировать" << endl <<
            "3 = Удалить" << endl <<
            "4 = Поиск" << endl <<
            "5 = Вывести на экран" <<            
            endl;
        z = _getch();
        cout << z << endl;
        
        switch (z)
        {
        case '1': { AddUser(vec,count);  break; }
        case '2': {Editors(count,vec); break; }
        case '3': {Erase(count,vec); break; }
        case '4': {Search(count,vec); break; }
        case '5': {Display(count,vec); break; }       
        case '0': {SaveinFile(count,vec); Scrin(); exit(0); break; }

        default:
            break;
        }
    }
    
        
    
    cout << "===============\n";
   
}

