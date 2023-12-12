#include"User.h"
#include <regex>

using namespace std;

void User::initialize(string login, string hashPassword, unsigned int role, unsigned int access)
{
	this->login = login;
	this->hashPassword = hashPassword;
	this->role = role;
	this->access = access;
}

void User::demonstrate()
{

	if (role == 0) {
		std::cout << "|" << setw(30) << login << "|" << setw(27) << "Администратор" << "|" << setw(8) << "есть" << "|\n";
	}
	if (role == 1) {
		if (access == 1)
			cout << "|" << setw(30) << login << "|" << setw(27) << "Гость" << "|" << setw(8) << "есть" << "|\n";
		else
			cout << "|" << setw(30) << login << "|" << setw(27) << "Гость" << "|" << setw(8) << "нет" << "|\n";
	}
	if (role == 2) {

		if (access == 1)
			cout << "|" << setw(30) << login << "|" << setw(27) << "Горничная" << "|" << setw(8) << "есть" << "|\n";
		else
			cout << "|" << setw(30) << login << "|" << setw(27) << "Горничная" << "|" << setw(8) << "нет" << "|\n";
	}
	if (role == 3) {

		if (access == 1)
			cout << "|" << setw(30) << login << "|" << setw(27) << "Работник ресторана" << "|" << setw(8) << "есть" << "|\n";
		else
			cout << "|" << setw(30) << login << "|" << setw(27) << "Работник ресторана" << "|" << setw(8) << "нет" << "|\n";
	}
}



void User::ShowMenu(Hotel& f)
{
}

unsigned int User::getRole()
{
	return this->role;
}

void User::setAccess(int access)
{
	this->access = access;
}

void User::setRole(int role)
{
	this->role = role;
}

void User::clone(shared_ptr<User> user)
{
	this->login = user->login;
	this->hashPassword = user->hashPassword;
	this->role = user->role;
	this->access = user->access;
}

void User::clone(Registration& obj)
{
	this->login = obj.getLogin();
	this->hashPassword = obj.getHashPassword();
}

string User::getHashPassword()
{
	return this->hashPassword;
}

string User::getLogin()
{
	return this->login;
}

unsigned int User::getAccess()
{
	return this->access;
}


void Administrator::ShowMenu(Hotel& hotel)

{   //заполнение данных в отеле из хранящихся в папке текстовых файлов
	while (true) {

		std::system("cls");

		int adChoice1;
		cout << "\n\t\tМеню администратора\n\t1 - работа с персоналом и гостями\n\t2 - работа с данными\n\t0 - вернуться назад\n\tответ - ";
		std::cin >> adChoice1;
		while (cin.fail() || adChoice1 < 0 || adChoice1 > 2) {
			cout << "\t!!! Вы некорректно ввели значение !!!\n";
			cout << "\tваш новый ответ - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> adChoice1;
		}
		switch (adChoice1)
		{
		case 1:
			workWithStaffClients(hotel);
			break;
		case 2:
			workWithData(hotel);
			break;
		case 0:
			hotel.updateFiles();
			return;
			break;

		default:
			break;
		}

		system("pause");
	}

}

void Administrator::workWithStaffClients(Hotel& hotel)
{
	while (true) {
		//заполнение данных в отеле из хранящихся в папке текстовых файлов
		hotel.clear();
		hotel.initialisation();

		system("cls");

		int adChoice2 = 0;
		cout << "\n\t\tМеню для работы с персоналом и гостями\n\t1 - Просмотреть всех пользователей\n\t2 - Разрешить доступ\n\t3 - Запретить доступ\n\t4 - Добавить сотрудника\n\t5 - Удалить сотрудника или гостя\n\t0 - Вернуться назад\n\tответ - ";
		cin >> adChoice2;
		while (cin.fail() || adChoice2 < 0 || adChoice2>5) {
			cout << "\t!!! Вы некорректно ввели значение !!!\n";
			cout << "\tваш новый ответ - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> adChoice2;
		}
		int choice = 0;
		switch (adChoice2)
		{
		case 1:
			hotel.showEmployeesClients();
			break;
		case 2:
			if (hotel.numberUsers() > 1) {
				cout << "\n\tВведите номер - ";
				cin >> choice;
				while (cin.fail()) {
					cout << "\t!!! Вы некорректно ввели значение !!!\n";
					cout << "\tваш новый ответ - ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> choice;
				}
				allowAccess(choice, hotel);
			}
			else cout << "\n\tНет ни одного работника!\n";
			break;
		case 3:
			if (hotel.numberUsers() > 1) {
				cout << "\n\tВведите номер - ";
				cin >> choice;
				while (cin.fail()) {
					cout << "\t!!! Вы некорректно ввели значение !!!\n";
					cout << "\tваш новый ответ - ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> choice;
				}
				denyAccess(choice, hotel);
			}
			else cout << "\n\tНет ни одного работника!\n";
			break;
		case 4:
			addEmployee(hotel);
			break;
		case 5:
			if (hotel.numberUsers() > 1) {
				deleteEmployeeClient(hotel);
			}
			else cout << "\n\tНет ни одного работника или гостя!\n";
			break;
		case 0:
			hotel.updateFiles();
			return;
			break;
		default:
			break;

		}

		std::system("pause");
		hotel.updateFiles();
	}
}

void Administrator::workWithData(Hotel& hotel)
{
	while (true) {
		std::system("cls");
		//заполнение данных в отеле из хранящихся в папке текстовых файлов
		hotel.clear();
		hotel.initialisation();

		int owChoice2;
		cout << "\n\t\tМеню для работы с данными\n\t1 - Просмотреть комнаты отеля\n\t2 - Удалить комнату\n\t3 - Добавить новую комнату\n\t4 - Посмотреть информацию о конкретной комнате\n\t5 - Сортировать комнаты\n\t6 - Сгенерировать отчёт\n\t0 - выход\n\tответ - ";

		cin >> owChoice2;
		while (cin.fail() || owChoice2 < 0 || owChoice2>8) {
			cout << "\t!!! Вы некорректно ввели значение !!!\n";
			cout << "\tваш новый ответ - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> owChoice2;
		}
		int choice = 0;
		switch (owChoice2)
		{
		case 1:
			hotel.viewRooms();
			break;
		case 2: {
			if (hotel.numberRooms()) {
				deleteRoom(hotel);
			}
			else cout << "\n\tНет ни одной комнаты!\n\n\t";
		}
			  break;
		case 3: {
			addRoom(hotel);
		}
			  break;
		case 4:
			if (hotel.numberRooms()) {
				cout << "\n\tВведите номер интересуемой комнаты - ";
				cin >> choice;
				while (cin.fail() || choice < 0) {
					cout << "\t!!! Вы некорректно ввели значение !!!\n";
					cout << "\tваш новый ответ - ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> choice;
				}
				cout << "___________________________________________________________________________________________________________________\n";
				cout << "|" << " № " << "|" << setw(30) << "НОМЕР КОМНАТЫ" << "|" << setw(12) << "ЦЕНА" << "|" << setw(12) << "КОЛ-ВО ВОЗМОЖНЫХ ЖИЛЬЦОВ" << "|" << setw(13) << "КЛАСС КОМНАТЫ" << "|" << setw(13) << "САНУЗЕЛ" << "|" << setw(13) << "ДЛЯ КУРЯЩИХ" << "|\n";
				cout << "___________________________________________________________________________________________________________________\n";
				hotel.Find(choice);
				cout << "____________________________________________________________________________________\n";
			}
			else cout << "\n\tНет ни одной комнаты!\n";
			break;
		case 5:
			if (hotel.numberRooms() != 0) {
				hotel.Sort();
			}
			else cout << "\n\tНет ни одной комнаты!\n";
			break;
		case 6:
			if (hotel.numberRooms() != 0) {
				hotel.generateRoomsStatisticsReport();
				hotel.generateRoomsStatisticsReport();
				cout << "\nОтчёт успешно создан\n";
			}
			else cout << "\n\tНет ни одной комнаты!\n";
			break;
		case 0:
			hotel.updateFiles();
			return;
			break;
		}

		std::system("pause");
		hotel.updateFiles();
	}
}


void Administrator::allowAccess(int choice, Hotel& hotel)
{
	if (choice > 0 && choice <= hotel.numberUsers()) {
		hotel.setAccessAllow(choice - 1);
	}
	else
		cout << "\n\tЧто-то не так с введённым значением\n";
}

void Administrator::denyAccess(int choice, Hotel& hotel)
{
	if (choice > 1 && choice <= hotel.numberUsers()) {
		hotel.setAccessDeny(choice - 1);
	}
	else
		cout << "\n\tЧто-то не так с введённым значением\n";
}

void Administrator::addEmployee(Hotel& hotel)
{
	int choice;
	cout << "\tКого вы хотите добавить?\n\t2 - Горничная\n\t3 - Работник ресторана\n\t0 - Администратора\n\t";
	Registration obj;
	cin >> choice;
	while (cin.fail() || choice < 0 || choice>3) {
		cout << "\t!!! Вы некорректно ввели значение !!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}
	obj.getUserData();
	User user;
	user.clone(obj);
	user.setAccess(0);
	user.setRole(choice);
	hotel.addEmployee(user);
}

void Administrator::deleteEmployeeClient(Hotel& hotel)
{
	int choice = 0;
	cout << "\n\tВведите номер - ";
	cin >> choice;
	while (cin.fail()) {
		cout << "\t!!! Вы некорректно ввели значение !!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}
	hotel.deleteEmployee(choice);
}

void Administrator::addRoom(Hotel& hotel)
{
	getchar();
	Room pr;
	pr.initialisation();
	hotel.addRoom(pr);
}

void Administrator::deleteRoom(Hotel& hotel)
{
	int choice = 0;
	cout << "\n\tВведите №- ";
	cin >> choice;
	while (cin.fail()) {
		cout << "\t!!! Вы некорректно ввели значение !!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}
	hotel.deleteRoom(choice);
}

void Maid::ShowMenu(Hotel& hotel)
{
	while (true) {
		std::system("cls");
		// заполнение данных в отеле из хранящихся в папке текстовых файлов
		hotel.clear();
		hotel.initialisation();

		int maidChoice;
		cout << "\n\t\tМеню горничной\n\t1 - Просмотреть забронированные комнаты\n\t2 - Пометить комнаты как убранные\n\t0 - Вернуться назад\n\tответ - ";
		cin >> maidChoice;
		while (cin.fail() || maidChoice < 0 || maidChoice > 2) {
			cout << "\t!!! Вы некорректно ввели значение !!!\n";
			cout << "\tваш новый ответ - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> maidChoice;
		}

		switch (maidChoice)
		{
		case 1:
			viewAllReservedRooms(hotel);
			break;
		case 2:
			int roomNumber;
			cout << "Введите номер комнаты, которую вы убрали: ";
			while (cin.fail() || (roomNumber < 1 || roomNumber > 1000)) {
				cout << "\t!!! Вы некорректно ввели значение!!!\n";
				cout << "\tваш новый ответ - ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> roomNumber;
			}
			markRoomAsCleaned(hotel, roomNumber);
			break;
		case 0:
			return;
			break;
		}

		std::system("pause");
		hotel.updateFiles();
	}
}

void Maid::readReservationsFromFileMaid(Hotel& hotel) {
	hotel.readReservationsFromFile();
}

bool isValidDateFormat(const string& date) {
	// Проверка формата "дд-мм-гггг"
	regex dateRegex("\\b\\d{2}-\\d{2}-\\d{4}\\b");
	return regex_match(date, dateRegex);
}

void Client::ShowMenu(Hotel& hotel)
{
	while (true) {
		std::system("cls");

		// заполнение данных в отеле из хранящихся в папке текстовых файлов
		hotel.clear();
		hotel.initialisation();

		int clientChoice;
		cout << "\n\t\tМеню гостя\n\t1 - Просмотреть комнаты отеля\n\t2 - Сортировать список комнат\n\t3 - Забронировать комнату\n\t4 - Просмотреть забронированные комнаты\n\t5 - Фильтровать комнаты по цене\n\t0 - Вернуться назад\n\tответ - ";
		cin >> clientChoice;

		while (cin.fail() || clientChoice < 0 || clientChoice > 5) {
			cout << "\t!!! Вы некорректно ввели значение !!!\n";
			cout << "\tваш новый ответ - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> clientChoice;
		}

		switch (clientChoice) {
		case 1:
			hotel.viewRooms();
			break;
		case 2: {
			if (hotel.numberRooms() != 0) {
				hotel.Sort();
			}
			else cout << "\n\tНет ни одной комнаты\n";
		}
			  break;
		case 3: {
			if (hotel.numberRooms() != 0) {
				int roomNumber;
				string checkInDate, checkOutDate;
				cout << "Введите номер комнаты: ";
				cin >> roomNumber;
				bool validDate = false;
				cout << "Введите дату заезда (дд-мм-гггг): ";
				while (!validDate) {
					cin >> checkInDate;
					if (isValidDateFormat(checkInDate)) {
						cout << "Верный формат даты!" << endl;
						validDate = true;
					}
					else {
						cout << "Неверный формат даты. Введите дату в формате дд-мм-гггг." << endl;
					}
				}

				validDate = false;
				cout << "Введите дату выезда (дд-мм-гггг): ";
				while (!validDate) {
					cin >> checkOutDate;
					if (isValidDateFormat(checkOutDate)) {
						cout << "Верный формат даты!" << endl;
						validDate = true;
					}
					else {
						cout << "Неверный формат даты. Введите дату в формате дд-мм-гггг." << endl;
					}
				}
				if (checkOutDate > checkInDate) {
					hotel.makeReservation(roomNumber, checkInDate, checkOutDate, getLogin(), hotel);

				}
				else {
					cout << "Дата выезда должна быть позже даты заезда" << endl;
				}
				break;
			}
			else {
				cout << "\n\tНет ни одной доступной комнаты\n";
			}
			break;
		}
		case 4:
			// просмотр забронированных комнат для текущего пользователя
			viewUserReservedRooms(hotel);
			break;
		case 5: {
			vector<Room> roomss;
			if (hotel.numberRooms() != 0) {
				float minPrice, maxPrice;
				cout << "\n\tВведите минимальную стоимость - ";
				cin >> minPrice;
				while (cin.fail() || minPrice < 0) {
					cout << "\t!!! Вы некорректно ввели значение !!!\n";
					cout << "\tваш новый ответ - ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> minPrice;
				}
				cout << "\n\tВведите максимальную стоимость - ";
				cin >> maxPrice;
				while (cin.fail() || maxPrice < 0) {
					cout << "\t!!! Вы некорректно ввели значение !!!\n";
					cout << "\tваш новый ответ - ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> maxPrice;
				}
				cout << "___________________________________________________________________________________________________________________\n";
				cout << "|" << " № " << "|" << setw(30) << "НОМЕР КОМНАТЫ" << "|" << setw(12) << "ЦЕНА" << "|" << setw(12) << "КОЛ-ВО ВОЗМОЖНЫХ ЖИЛЬЦОВ" << "|" << setw(13) << "КЛАСС КОМНАТЫ" << "|" << setw(13) << "САНУЗЕЛ" << "|" << setw(13) << "ДЛЯ КУРЯЩИХ" << "|\n";
				cout << "___________________________________________________________________________________________________________________\n";
				roomss = hotel.filterRoomsByPrice(minPrice, maxPrice);
				for (Room& room : roomss) {
					room.demonstrate(room.getNumber(), room.getPrice(), room.getGuests(), room.getType(), room.getBath(), room.getSmoking());
					cout << "____________________________________________________________________________________\n";
				}
			}
			else cout << "\n\tНет ни одной комнаты\n";
		}
			  break;
		case 0:
			return;
			break;
		}

		std::system("pause");
		hotel.updateFiles();
	}
}

void Maid::viewAllReservedRooms(const Hotel& hotel) {
	vector<Reservation> allReservations = hotel.getAllReservations();

	if (allReservations.empty()) {
		cout << "Нет забронированных комнат." << endl;
	}
	else {
		cout << "Забронированные комнаты:" << endl;
		cout << "___________________________________________________________________________________________________________________\n";
		cout << "|" << setw(15) << "НОМЕР КОМНАТЫ" << "|" << setw(20) << "ОБЩАЯ СТОИМОСТЬ" << "|" << setw(25) << "ДАТА ЗАЕЗДА" << "|" << setw(25) << "ДАТА ВЫЕЗДА" << "|" << setw(25) << "СТАТУС УБОРКИ" << "|\n";
		cout << "___________________________________________________________________________________________________________________\n";
		for (Reservation& reservation : allReservations) {
			reservation.demonstrateReservationMaid();
			cout << "___________________________________________________________________________________________________________________\n";
		}
	}
}

void Maid::markRoomAsCleaned(Hotel& hotel, int roomNumber) {
	//int roomNumber=0;
	hotel.markRoomCleaned(roomNumber);
}

void Client::viewUserReservedRooms(Hotel& hotel) {
	vector<Reservation> userReservations = hotel.getReservations(getLogin());
	if (userReservations.empty()) {
		cout << "\n\tУ вас нет забронированных комнат.\n";
	}
	else {
		cout << "\n\tВаши забронированные комнаты:\n";
		cout << "______________________________________________________________________________________________________________\n";
		cout << "|" << setw(30) << "НОМЕР КОМНАТЫ" << "|" << setw(25) << "ОБЩАЯ СТОИМОСТЬ" << "|" << setw(25) << "ДАТА ЗАЕЗДА" << "|" << setw(25) << "ДАТА ВЫЕЗДА" << "|\n";
		cout << "______________________________________________________________________________________________________________\n";
		for (Reservation& reservation : userReservations) {
			reservation.demonstrateReservation();
			cout << "______________________________________________________________________________________________________________\n";
		}
	}
}
