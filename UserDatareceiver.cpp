#include "UserDataReceiver.h"
#include"SHA256.h"
#include<direct.h>
#include<Windows.h>

string getFilePath();

// инициализация статической константной переменной, отвечающей за название файла
const string UserDataReceiver::fileName = "Hotels.txt";

//получаем информацию о пользователе для дальнейшей обработки
void UserDataReceiver::getUserData()
{
	getchar();
	cout << "\tВведите логин, пожалуйста : ";
	getline(cin, userLogin);
	while (userLogin.size() < 3) {
		cout << "\n\tМало символов, введите заново:";
		getline(cin, userLogin);
	}
	string password;
	cout << "\tВведите пароль, пожалуйста : ";
	char cInput;
	while ((cInput = _getch()) != '\r' && password.size() < 22)
	{
		if ((int)cInput != 8) {
			password.push_back(cInput);
			_putch('*');
		}
		if ((int)cInput == 8) {
			if (!password.empty()) {
				std::cout << "\b \b";
				password.pop_back();
			}
		}
	}

	userHashPassword = Crypt::sha256(password);
}

// узнаём сществует ли данный пользователь
bool Authorization::isExists(shared_ptr<User>  baseClassSmartPointer, Hotel& Hotel)
{
	//получем названия всех записанных отелей
	vector<string> vectorHotelNames;
	ifstream  hotels;
	hotels.open(this->fileName);
	string hotelName;
	while (getline(hotels, hotelName)) {
		vectorHotelNames.push_back(hotelName);
	}
	hotels.close();

	// ищем по полученным названиям пользователей системы
	if (!vectorHotelNames.empty()) {

		for (unsigned int k = 0; k < vectorHotelNames.size(); k++) {
			ifstream  hotel;
			hotel.open(vectorHotelNames[k] + "\\Clients.txt");

			//используем шаблонный класс, облегчающий файловый ввод-вывод объектов
			FileWorker<User> obj;
			hotel >> obj;
			vector<User> users;
			obj.cloneTo(users);

			for (int i = 0; i < users.size(); i++) {

				if (users[i].getLogin() == this->userLogin && users[i].getHashPassword() == this->userHashPassword) {

					//инициализируем поля нашего авторизовавшегося пользователя
					baseClassSmartPointer->initialize(users[i].getLogin(), users[i].getHashPassword(), users[i].getRole(), users[i].getAccess());

					//так как в дальнейшем пользователь взаимодействует с объектами отеля - присвоим ему имя, облегчающее поиск необходимых данных
					Hotel.setName(vectorHotelNames[k]);
					return true;
				}

			}
			hotel.close();
		}
	}
	if (vectorHotelNames.empty())
	{
		cout << "\n\tВы первый пользователь - обязательно пройдите регистрацию!";
		return false;
	}

	cout << "\tОшибка авторизации!";
	return false;
}

bool Registration::isExists()
{
	//получем названия всех записанных отелей
	vector<string> vectorHotelNames;
	ifstream  hotels;
	hotels.open(this->fileName);
	string hotelName;
	while (getline(hotels, hotelName)) {
		vectorHotelNames.push_back(hotelName);
	}
	hotels.close();

	// ищем по полученным названиям пользователя системы
	if (!vectorHotelNames.empty()) {

		for (unsigned int k = 0; k < vectorHotelNames.size(); k++) {
			ifstream  hotel;
			hotel.open(vectorHotelNames[k] + "\\Clients.txt");

			//используем шаблонный класс, облегчающий файловый ввод-вывод объектов
			FileWorker<User> obj;
			hotel >> obj;
			vector<User> users;
			obj.cloneTo(users);

			for (int i = 0; i < users.size(); i++) {

				if (users[i].getLogin() == this->userLogin && users[i].getHashPassword() == this->userHashPassword) {

					return true;
				}

			}
			hotel.close();
		}
	}
	return false;
}


void Registration::Register()
{
	if (!isExists()) {
		int choice;
		cout << "\n\t1 - регистрация в качестве администратора отеля";
		cout << "\n\t2 - регистрация в качестве гостя";
		cout << "\n\t0 - выход из меню регистрации\n\tответ - ";
		cin >> choice;
		while (cin.fail() || choice < 0 || choice>2) {
			cout << "\t!!! Вы некорректно ввели значение !!!\n";
			cout << "\tваш новый ответ - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> choice;
		}

		switch (choice)
		{
		case 0:
			break;
		case 1:
		{
			getchar();
			string hotelName;

			cout << "\tНазвание регистрируемого отеля - ";
			getline(cin, hotelName);
			while (hotelName.size() < 5) {
				cout << "\n\tСлишком короткое название отеля\n";
				getline(cin, hotelName);
			}
			if (!isHotelExists(hotelName)) {
				//записываем в перечень отелей новый
				ofstream  hotels;
				hotels.open(this->fileName, ios::app);
				hotels << hotelName << endl;
				hotels.close();

				//создаём директорию с именем отеля
				string ss = hotelName;
				if (!_mkdir(ss.c_str())) {
					cout << "\n\tПапка, где будет храниться информация вашего отеля, создана по пути:\n\t";
					cout << getFilePath() << ss << endl;
				}
				else cout << "\n\tНе удалось зарегистрировать отель!";


				//записываем администратора отеля в файл
				ofstream  hotel;
				hotel.open(hotelName + "\\Clients.txt", ios::out);
				hotel << this->userLogin << endl;
				hotel << this->userHashPassword << endl;
				hotel << 0 << " " << 1 << endl; // 0 - администратор, 1 - с доступом ко всему
				hotel.close();

			}
			else cout << "\n\tНазвание такого отеля уже существует\n";
		}
		break;
		case 2:
		{
			//получем названия всех записанных отелей
			vector<string> vectorHotelNames;
			ifstream  hotels;
			hotels.open(this->fileName);
			string hotelName;
			while (getline(hotels, hotelName)) {
				vectorHotelNames.push_back(hotelName);
			}
			hotels.close();

			//выводим для выбора
			if (!vectorHotelNames.empty()) {
				cout << setw(32) << "\n\t\tЗарегистрированные отели\n";
				cout << setfill('_') << setw(32) << '\n';
				cout << setfill(' ');
				for (unsigned int i = 0; i < vectorHotelNames.size(); i++) {
					cout << "||" << setw(3) << i + 1 << "|" << setw(24) << vectorHotelNames[i] << "||\n";
					cout << setfill('_') << setw(32) << '\n';
					cout << setfill(' ');
				}
			}
			else {
				cout << "\n\tК сожалению ни одного отеля не найдено\n";
				return;
			}
			cout << "\n\tответ - ";
			cin >> choice;
			while (cin.fail() || choice < 1 || choice>(int)vectorHotelNames.size()) {
				cout << "\t!!! Вы некорректно ввели значение !!!\n";
				cout << "\tваш новый ответ - ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> choice;
			}

			//запись гостя в файле директории выбранного отеля
			ofstream  hotel;
			hotel.open(vectorHotelNames[choice - 1] + "\\Clients.txt", ios::app);
			hotel << this->userLogin << endl;
			hotel << this->userHashPassword << endl;
			hotel << 1 << " " << 1 << endl; // 1 - гость
			hotel.close();
		}
		break;

		default:
			break;
		}
	}
	else cout << "\n\tК сожалению Вам надо придумать другой логин!\n";
}

// благодаря этой функции мы получаем абсолютный путь места запуска нашего проекта
string getFilePath() {
	WCHAR path[500];
	DWORD size = GetModuleFileNameW(NULL, path, 500);

	char ch[260];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, path, -1, ch, 260, &DefChar, NULL);

	//A std:string  using the char* constructor.
	string ss(ch);
	unsigned int i = ss.size();
	while (ss[i] != '\\') {
		ss[i] = '\0';
		i--;
	}
	return ss;
}



string Registration::getLogin() {
	return this->userLogin;
}

string Registration::getHashPassword() {
	return this->userHashPassword;
}

bool Authorization::isExists()
{
	return false;
}


bool Registration::isHotelExists(string nameHotel) {
	//получем названия всех записанных отелей
	vector<string> vectorHotelNames;
	ifstream  hotels;
	hotels.open(this->fileName);
	string firmName;
	while (getline(hotels, firmName)) {
		vectorHotelNames.push_back(firmName);
	}
	hotels.close();

	// ищем по полученным названиям работника фирмы или гостя
	if (!vectorHotelNames.empty()) {

		for (unsigned int k = 0; k < vectorHotelNames.size(); k++) {
			if (nameHotel == vectorHotelNames[k])
				return true;
		}
	}

	return false;
}
