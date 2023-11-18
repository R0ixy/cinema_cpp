#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
class Cinema;

class Source { //абстрактный базовый класс
protected:
    string name;
public:
    virtual void Show() = 0; //чисто виртуальный метод 
};

class Repertoire:public Source
{
private:
    string date;
    int price;
    int freeplace;
    string hall;
public:
    Repertoire() { //конструктор за замовченням
        name = ""; 
        date = "";
        price = 0;
        freeplace = 0;
    }
    void addrep() { //функція додаввання репертуару
        cout << "Введите репертуар: " << endl;
        cout << "Название фильма: "; getline(cin, name); 
        cout << "Время: "; getline(cin, date); 
        cout << "Цена: "; cin >> price;
        cout << "Кол-во свободных мест: "; cin >> freeplace; cin.ignore(100,'\n');
        cout << "Зал: "; getline(cin, hall);
        cout << endl;
    }
    void Show() override //вывод на консоль 
    {
        cout << "Название фильма: «" << name << "»" << endl; 
        cout << "Время: " << date << endl;
        cout << "Цена: " << price << endl;
        cout << "Свободных мест: " << freeplace << endl;
        cout << "Зал: " << hall << endl;
    }
    void setRep(string name, string date, int price, int freeplace, string hall) { //функциія встановлення параметрів
        this->name = name; 
        this->date = date;
        this->price = price;
        this->freeplace = freeplace;
        this->hall = hall;
    }
    void WriteFileRep(Cinema list[], int CinemaNum);
    string getfilm() { return name; } 
    int getfreeplace() { return freeplace; }
    string getdate() { return date; }
    int getprice() { return price; }
 
};

class Cinema : public Source
{
private:
    string adress;
    int place;
    int halls;
public:
    Repertoire* arr;
    Cinema()//конструктор за замовченням
    {
        name = "";
        adress = "";
        place = 0;
        halls = 0;
    }
    void WriteFileCinema(Cinema spis[], int CinemaNum);
    void Show() override //вывод на консоль 
    {
        cout << "Название: " << name << endl;
        cout << "Адрес: " << adress << endl;
        cout << "Кол-во мест: " << place << endl;
        cout << "Кол-во залов: " << halls << endl;
    }
    void setCinema(string name, string adress, int place, int halls) {//функциія встановлення параметрів
        this->name = name;
        this->adress = adress;
        this->place = place;
        this->halls = halls; 
    }
    void addCinema() {  //функція додаввання кінотеатру
        cout << "Введите данные кинотеатра " << endl;
        cout << "Название: "; getline(cin, name);
        cout << "Адрес: "; getline( cin, adress);
        cout << "Кол-во мест: "; cin >> place;
        cout << "Кол-во залов: "; cin >> halls; cin.ignore(100, '\n');
        cout << endl;
    }
    string getname() { return name; }
    int gethalls() { return halls * 3; }
};



class Film :public Source
{
private:
    string director;
    string actors;
    string genre;
    string studio;
public:
    Film() {  //конструктор за замовченням
        name = "";
        director = "";
        actors = "";
        genre = "";
        studio = "";
    }
    void addfilm() {  //функція додавання фільму
        cout << "Введите данные о фильме " << endl;
        cout << "Введите название фильма: "; getline(cin, name);
        cout << "Введите актёров: "; getline(cin, actors);
        cout << "Введите жанр: ";  getline(cin, genre);
        cout << "Введите режисера: "; getline(cin, director);
        cout << "Введите название студии: "; getline(cin, studio);
        cout << endl;
    }
    void setFilm(string name, string director, string actors, string genre, string studio) {//функциія встановлення параметрів
        this->name = name; //title
        this->director = director;
        this->actors = actors;
        this->genre = genre;
        this->studio = studio;
    }
    void WriteFileFilm(Film num[], int FilmNum);

    string getgenre() { return genre; }
    string gettitle() { return name; } 
    string getdirector() { return director; }
    void Show() override  //вывод на консоль 
    {
        cout << "Название: «" << name << "»" << endl;
        cout << "Режисер: " << director << endl;
        cout << "Актёры: " << actors << endl;
        cout << "Жанр: " << genre << endl;
        cout << "Студия: " << studio << endl;
    }
};


void cinemaforgenre(Film num[], Cinema list[], int n, int m) // список кинотеатров что показывают фильм данного жанра
{
    string currgenre;
    cout << "Введите жанр: ";
    cin >> currgenre;
    bool exists = false;
    for (int i = 0; i < n; i++) {
        if (num[i].getgenre() == currgenre) {
            exists = true;
            for (int k = 0; k < m; k++) {
                for (int j = 0; j < list[k].gethalls(); j++) {
                    if (num[i].gettitle() == list[k].arr[j].getfilm()) {
                        cout << list[k].getname() << endl;
                    }
                }
            }
        }
    }

    if(!exists) {
        cout << "\nВ кинотеатрах нет сеансов на фильмы данного жанра" << endl;
    }
}

void repforcinema(Cinema list[], int CinemaNum) //вывод репертуара кинотеатра
{
    int currCinema = 0;
    cout << "Выберите кинотеатр" << endl;
    for (int i = 0; i < CinemaNum; i++) {
        cout << "(" << i + 1 << ")" << list[i].getname() << endl;
    }
    cout << "Ваш выбор: ";
    cin >> currCinema;
    if (currCinema > CinemaNum) {
        throw exception("Введенное число не соответствует пункту меню");
    }
    system("cls");
    cout << "====" << list[currCinema - 1].getname() << "====" << endl;
    for (int j = 0; j < list[currCinema - 1].gethalls(); j++) {
        cout << endl;
        list[currCinema - 1].arr[j].Show();
    }
}


void cinemafordirector(Film num[], Cinema list[], int n, int m) // список кинотеатров что показывают фильм данного режисера
{
    string currDirector;
    cout << "Введите Режисера: ";
    getline(cin, currDirector);
    bool exists = false;
    for (int i = 0; i < n; i++) {
        if (num[i].getdirector() == currDirector) {
            exists = true;
            for (int k = 0; k < m; k++) {
                for (int j = 0; j < list[k].gethalls(); j++) {
                    if (num[i].gettitle() == list[k].arr[j].getfilm()) {
                        cout << list[k].getname() << endl;
                    }
                }
            }
        }
    }

    if (!exists) {
        cout << "\nВ кинотеатрах нет сеансов на фильмы данного режисера" << endl;
    }
}

void freespace(Cinema list[], int CinemaNum) { //количество свободных мест на данном сеансе в выборанном кинотеатре
    int currCinema = 0;
    cout << "Выберите кинотеатр" << endl;
    for (int i = 0; i < CinemaNum; i++) {
        cout << "(" << i + 1 << ")" << list[i].getname() << endl;
    }
    cout << "Ваш выбор: ";
    cin >> currCinema;
    if (currCinema > CinemaNum) {
        throw exception("Введенное число не соответствует пункту меню");
    }
    system("cls");
    cout << "====" << list[currCinema - 1].getname() << "====\n" << endl;
    int currRep;
    for (int j = 0; j < list[currCinema - 1].gethalls(); j++) {
        cout << "(" << j + 1 << ")"<<list[currCinema - 1].arr[j].getfilm() <<" - "<< list[currCinema - 1].arr[j].getdate() << endl;
    }
    cout << "Ваш выбор: "; cin >> currRep;
    if (currRep > list[currCinema - 1].gethalls()) {
        throw exception("Введенное число не соответствует пункту меню");
    }
    cout << "Количество свободных мест: "<<list[currCinema - 1].arr[currRep - 1].getfreeplace() << endl;
}

void knewprice(Cinema list[], int CinemaNum) {  //цена билета на выбранный сеанс в данном кинотеатре
    int currCinema = 0;
    cout << "Выберите кинотеатр" << endl;
    for (int i = 0; i < CinemaNum; i++) {
        cout << "(" << i + 1 << ")" << list[i].getname() << endl;
    }
    cout << "Ваш выбор: ";
    cin >> currCinema;
    if (currCinema > CinemaNum) {
        throw exception("Введенное число не соответствует пункту меню");
    }
    system("cls");
    cout << "====" << list[currCinema - 1].getname() << "====\n" << endl;
    int currRep;
    for (int j = 0; j < list[currCinema - 1].gethalls(); j++) {
        cout << "(" << j + 1 << ")" << list[currCinema - 1].arr[j].getfilm() << " - " << list[currCinema - 1].arr[j].getdate() << endl;
    }
    cout << "Ваш выбор: "; cin >> currRep;
    if (currRep > list[currCinema - 1].gethalls()) {
        throw exception("Введенное число не соответствует пункту меню");
    }
    cout << "Цена: " << list[currCinema - 1].arr[currRep - 1].getprice() << endl;
}


int CinemaNumFromFile() //количество кинотеатров в файле
{
    ifstream fin("CinemaList.txt");
    int k = 0;
    if (fin.is_open()) {
        fin >> k;
    }
    else {
        cout << "Ошибка открытия файла" << endl;
    }
    fin.close();
    return k;
}

int FilmNumFromFile() //количество фильмов в файле
{
    ifstream fin("FilmList.txt");
    int k = 0;
    if (fin.is_open()) {
        fin >> k;
    }
    else {
        cout << "Ошибка открытия файла" << endl;
    }
    fin.close();
    return k;
}


void ReadFileCinema(Cinema list[]) //чтение данных о кинотеатрах из файла
{
    ifstream fin("CinemaList.txt");

    int k;
    string name, adress;
    int place;
    int halls;


    if (fin.is_open()) {
        fin >> k; fin.ignore(100, '\n');
        for (int i = 0; i < k; i++) {
            getline(fin, name);
            getline(fin, adress);
            fin >> place;
            fin >> halls; fin.ignore(100, '\n');
            list[i].setCinema(name, adress, place, halls);
        }
    }
    else {
        cout << "Ошибка открытия файла" << endl;
    }
    fin.close();
}

void ReadFileFilm(Film* num) //чтение данных о фильмах из файла
{
    ifstream fin("FilmList.txt");

    int k;
    string title;
    string director;
    string actors;
    string genre;
    string studio;

    if (fin.is_open()) {
        fin >> k; fin.ignore(100, '\n');
        for (int i = 0; i < k; i++) {
            getline(fin, title);
            getline(fin, director);
            getline(fin, actors);
            getline(fin, genre);
            getline(fin, studio);
            num[i].setFilm(title, director, actors, genre, studio);
        }
    }
    else {
        cout << "Ошибка открытия файла" << endl;
    }
    fin.close();
}

void ReadFileRep(Cinema* list) //чтение данных о репертуаре из файла 
{


    ifstream fin("RepList.txt");

    int k;
    string film;
    string date;
    int price, freeplace;
    string hall;


    if (fin.is_open()) {
        fin >> k; fin.ignore(100, '\n');

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < (list[i].gethalls()); j++) {
                getline(fin, film);
                getline(fin, date);
                fin >> price >> freeplace;
                fin >> hall; fin.ignore(100, '\n');
                list[i].arr[j].setRep(film, date, price, freeplace, hall);
            }
        }
    }
    else {
        cout << "Ошибка открытия файла" << endl;
    }
    fin.close();

}

void Cinema::WriteFileCinema(Cinema list[], int n) {  //запись данных о кинотеатрах в файла
    ofstream fout("CinemaList.txt");
    if (fout.is_open()) {
        fout << n << endl;
        for (int i = 0; i < n; i++) {
            if (list[i].name != "") {
                fout << list[i].name << "\n" << list[i].adress << endl;
                fout << list[i].place << "\n" << list[i].halls << endl;
            }
            else {
                n++;
            }
        }
    }
    else {
        cout << "Ошибка открытия файла" << endl;
    }
    fout.close();
}

void Film::WriteFileFilm(Film num[], int n){ //запить данных о фильмах в файл
    ofstream fout("FilmList.txt");
    if (fout.is_open()) {
        fout << n << endl;
        for (int i = 0; i < n; i++) {
            if (num[i].name != "") { 
                fout << num[i].name << "\n" << num[i].director << "\n" << num[i].actors << endl; 
                fout << num[i].genre << "\n" << num[i].studio << endl;
            }
            else {
                n++;
            }
        }
    }
    else {
        cout << "Ошибка открытия файла" << endl;
    }
    fout.close();
}

void Repertoire::WriteFileRep(Cinema list[], int CinemaNum) { //запить данных о репертуаре в файл
    ofstream fout("RepList.txt");
    if (fout.is_open()) {
        fout << CinemaNum << endl;
        int RepNum = 0;
        for(int i = 0; i < CinemaNum; i++) {
            RepNum +=list[i].gethalls();
        }
        for (int i = 0; i < CinemaNum; i++) {
            for (int j = 0; j < (list[i].gethalls()); j++) {
                if (list[i].arr[j].name != "") { 
                    fout << list[i].arr[j].name << "\n" << list[i].arr[j].date << endl; 
                    fout << list[i].arr[j].price << " " << list[i].arr[j].freeplace << endl;
                    fout << list[i].arr[j].hall << endl;
                }
            }
        }

    }
    else {
    cout << "Ошибка открытия файла" << endl;
    }
    fout.close();
}

int statemenu;
void MainMenu() { //главное меню
    cout << "====МЕНЮ====\n"
        << "(0) Выход\n"
        << "(1) Добавить кинотеатр\n"
        << "(2) Добавить фильм\n"
        << "(3) Удалить кинотеатр\n"
        << "(4) Удалить фильм\n"
        << "(5) Информация о кинотератрах\n"
        << "(6) Информация о фильмах\n"
        << "(7) Информация о репертуаре\n"
        << "(8) В каком кинотератре можно посмотреть фильмы данного жанра\n"
        << "(9) Число свободных мест на заданный сеанс в данном кинотеатре\n"
        << "(10) Цена билетов на заданный сеанс в данном кинотеатре\n"
        << "(11) В каком кинотератре можно посмотреть фильмы данного режисера\n"
        << "Ваш выбор: ";
    try {
        cin >> statemenu;
        if (statemenu > 11 || statemenu < 0) {
            throw exception("Введенное число не соответствует пункту меню");
        }
    }
    catch (exception& ex) {
        cout << ex.what() << endl;
        system("pause");
    }
}


int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int CinemaNum = 0; //количество кинотеатров
    int FilmNum = 0; //количество фильмов

    MainMenu();
    while (statemenu != 0) { //выход из программы при нуле

        CinemaNum = CinemaNumFromFile();
        Cinema* list = new Cinema[CinemaNum];
        ReadFileCinema(list);
        for (int i = 0; i < CinemaNum; i++) {
            list[i].arr = new Repertoire[list[i].gethalls()];
        }
        ReadFileRep(list);


        FilmNum = FilmNumFromFile();
        Film* num = new Film[FilmNum];
        ReadFileFilm(num);

        system("cls");
        switch (statemenu) {
        case 1:  //добавить кинотеатр
        {
            cin.ignore(1000, '\n');
            int newCinemaNum = CinemaNum + 1;

            Cinema* list1 = new Cinema[newCinemaNum];
            ReadFileCinema(list1);
            list1[CinemaNum].addCinema();
            list1->WriteFileCinema(list1, newCinemaNum);
            for (int i = 0; i < newCinemaNum; i++) {
                list1[i].arr = new Repertoire[list1[i].gethalls()];
            }
            ReadFileRep(list1);
            for (int j = 0; j < list1[CinemaNum].gethalls(); j++) {
                list1[CinemaNum].arr[j].addrep();
            }
            list1->arr->WriteFileRep(list1, newCinemaNum);

            for (int i = 0; i < CinemaNum; i++)
                delete[] list1[i].arr;
            delete[] list1;

            break;
        }
        case 2: //добавить фильм
        {
            cin.ignore(1000, '\n');
            int newFilmNum = FilmNum + 1;
            Film* num1 = new Film[newFilmNum];
            ReadFileFilm(num1);
            num1[FilmNum].addfilm();
            num1->WriteFileFilm(num1, newFilmNum);
            delete[]num1;
            break;
        }
        case 3: //удалить кинотеатр
        {
            cout << "Выбирете кинотеатр для удаления" << endl;
            int delCinema = 0;
            for (int i = 0; i < CinemaNum; i++) {
                cout << "(" << i + 1 << ")" << list[i].getname() << endl;
            }
            cout << "\n(0) Вернуться в меню" << endl;
            cout << "Ваш выбор: "; cin >> delCinema;
            if (delCinema == 0) { break; }
            list[delCinema - 1].setCinema("", "", 0, 0);
            list->WriteFileCinema(list, CinemaNum - 1);
            for (int j = 0; j < list[delCinema - 1].gethalls(); j++) {
                list[delCinema].arr[j].setRep("", "", 0, 0, "");
            }
            list->arr->WriteFileRep(list, CinemaNum - 1);
            break;
        }
        case 4: //удалить фильм
        {
            cout << "Выбирете фильм для удаления" << endl;
            int delfilm = 0;
            for (int i = 0; i < FilmNum; i++) {
                cout << "(" << i + 1 << ") '" << num[i].gettitle() <<"'"<< endl;
            }
            cout << "\n(0) Вернуться в меню" << endl;
            cout << "Ваш выбор: "; cin >> delfilm;
            if (delfilm == 0) { break; }
            num[delfilm - 1].setFilm("", "", "", "", "");
            num->WriteFileFilm(num, FilmNum - 1);
            break;
        }
        case 5: //инфо о кинотеатрах
        {
            for (int i = 0; i < CinemaNum; i++) {
                list[i].Show();
                cout << endl;
            }
            break;
        }
        case 6: //инфо о фильмах
            for (int i = 0; i < FilmNum; i++) {
                num[i].Show();
                cout << endl;
            }
            break;
        case 7: //афиша кинотеатра
            cin.ignore(1000, '\n');
            try {
                repforcinema(list, CinemaNum);
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 8: //кинотеатр по жанру
            cinemaforgenre(num, list, FilmNum, CinemaNum);
            break;
        case 9: //кол-во свободных мест
            try {
                freespace(list, CinemaNum);
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 10: //цена
            try {
                knewprice(list, CinemaNum);
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 11: //кинотеатр по режисеру
            cin.ignore(1000, '\n');
            cinemafordirector(num, list, FilmNum, CinemaNum);
            break;
        }
        //очистка памяти
        for (int i = 0; i < CinemaNum; i++)
            delete[] list[i].arr;
        delete[] list;
        delete[] num;

        system("pause");
        system("cls"); //очистка консоли
        MainMenu();
    }
    system("pause");
    return 0;
}