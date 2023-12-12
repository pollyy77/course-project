#include "Hotel.h"
#include <regex>
#include <numeric>

void Hotel::setName(string name)
{
	this->name = name;
}

string Hotel::getName()
{
	return this->name;
}

int Hotel::getRoomNumber(int p)
{
	return rooms[p].getNumber();
}

int Hotel::getRoomType(int p)
{
	return rooms[p].getType();
}

int Hotel::getRoomGuests(int p)
{
	return rooms[p].getGuests();
}

float Hotel::getRoomPrice(int p)
{
	return rooms[p].getPrice();
}

int Hotel::getRoomBath(int p)
{
	return rooms[p].getBath();
}

int Hotel::getRoomSmoking(int p)
{
	return rooms[p].getSmoking();
}

void Hotel::initialisation()
{
	ifstream  hotel, hotel1, hotel2;
	hotel.open(this->name + "\\Clients.txt");

	//используем шаблонный класс, облегчающий файловый ввод-вывод объектов
	FileWorker<User> objUsers;
	hotel >> objUsers;
	//сдесь мы перекопировали данные об юзерах из obj в вектор отеля
	objUsers.cloneTo(this->users);

	hotel.close();

	hotel1.open(this->name + "\\Rooms.txt");

	//используем шаблонный класс, облегчающий файловый ввод-вывод объектов
	FileWorker<Room> objRooms;
	hotel1 >> objRooms;
	//здесь мы перекопировали данные об юзерах из obj в вектор отеля
	objRooms.cloneTo(this->rooms);
	hotel1.close();

	hotel2.open(this->name + "\\Reservations.txt");
	//используем шаблонный класс, облегчающий файловый ввод-вывод объектов
	FileWorker<Reservation> objReservation;
	hotel2 >> objReservation;
	//здесь мы перекопировали данные об юзерах из obj в вектор отеля
	objReservation.cloneTo(this->reservations);
	hotel2.close();
}

void Hotel::updateFiles()
{
	ofstream hotel, hotel1, hotel2;
	hotel.open(this->name + "\\Clients.txt");
	// используем шаблонный класс, облегчающий файловый ввод-вывод объектов
	FileWorker<User> objUsers;
	// здесь мы перекопировали данные об юзерах
	objUsers.cloneFrom(this->users);
	hotel << objUsers;
	hotel.close();

	hotel1.open(this->name + "\\Rooms.txt");
	// используем шаблонный класс, облегчающий файловый ввод-вывод объектов
	FileWorker<Room> objRooms;
	// здесь мы перекопировали данные о комнатах
	objRooms.cloneFrom(this->rooms);
	hotel1 << objRooms;
	hotel1.close();

	hotel2.open(this->name + "\\Reservations.txt");
	//используем шаблонный класс, облегчающий файловый ввод-вывод объектов
	FileWorker<Reservation> objReservation;
	//здесь мы перекопировали данные об юзерах из obj в вектор отеля
	objReservation.cloneFrom(this->reservations);
	hotel2 << objReservation;
	hotel2.close();
}

void Hotel::showEmployeesClients()
{
	if (users.size()) {
		cout << "_________________________________________________________________________\n";
		cout << "|" << " № " << "|" << setw(30) << "ЛОГИН" << "|" << setw(27) << "Роль" << "|" << setw(8) << "ДОСТУП" << "|\n";
		cout << "_________________________________________________________________________\n";

		for (unsigned int i = 0; i < users.size(); i++) {
			cout << "_________________________________________________________________________\n";

			cout << "|" << setw(3) << i + 1;
			users[i].demonstrate();
		}
		cout << "_________________________________________________________________________\n";
	}
	else cout << "\n\tНет пользователей\n";

}

void Hotel::addEmployee(User user)
{
	this->users.push_back(user);
}

void Hotel::deleteEmployee(int choice)
{
	if (choice > 1 && choice <= numberUsers()) {
		this->users.erase(users.begin() + choice - 1);
	}
	else cout << "\n\tЧто-то не так с введённым значением\n";

}

void Hotel::viewRooms()
{
	if (rooms.size()) {
		cout << "___________________________________________________________________________________________________________________\n";
		cout << "|" << " № " << "|" << setw(30) << "НОМЕР КОМНАТЫ" << "|" << setw(12) << "ЦЕНА" << "|" << setw(12) << "КОЛ-ВО ВОЗМОЖНЫХ ЖИЛЬЦОВ" << "|" << setw(13) << "КЛАСС КОМНАТЫ" << "|" << setw(13) << "САНУЗЕЛ" << "|" << setw(13) << "ДЛЯ КУРЯЩИХ" << "|\n";
		cout << "___________________________________________________________________________________________________________________\n";

		for (unsigned int i = 0; i < rooms.size(); i++) {
			cout << "___________________________________________________________________________________________________________________\n";

			cout << "|" << setw(3) << i + 1;
			rooms[i].demonstrate(getRoomNumber(i), getRoomPrice(i), getRoomGuests(i), getRoomType(i), getRoomBath(i), getRoomSmoking(i));
		}
		cout << "___________________________________________________________________________________________________________________\n";
	}
	else cout << "\n\tНет зарегистрированных номеров";
}

void Hotel::addRoom(Room room)
{
	this->rooms.push_back(room);
}

void Hotel::deleteRoom(int choice)
{
	if (choice > 0 && choice <= numberRooms()) {
		this->rooms.erase(rooms.begin() + choice - 1);
		cout << "\tКомната была успешно удалена из дирректории\n";
	}
	else
		cout << "\n\tЧто-то не так с введённым значением\n";

}

void Hotel::setAccessAllow(int choice)
{
	if (users[choice].getAccess() == 0) {
		users[choice].setAccess(1);
		cout << "\n\tДоступ пользователю успешно предоставлен\n";
	}
	else
		cout << "\n\tПользователь и так обладал необходимым доступом\n";
}

void Hotel::setAccessDeny(int choice)
{
	if (users[choice].getAccess() == 1) {
		users[choice].setAccess(0);
		cout << "\n\tДоступ пользователю успешно запрещён\n";
	}
	else
		cout << "\n\tПользователь и так не обладал необходимым доступом\n";
}

unsigned int Hotel::numberUsers()
{
	return this->users.size();
}

unsigned int Hotel::numberRooms()
{
	return this->rooms.size();
}

void Hotel::clear()
{
	users.clear();
	rooms.clear();
	reservations.clear();
}

void Hotel::Find(int roomNumberToFind) {
	Room foundRoom = findRoomByNumber(roomNumberToFind);
	if (foundRoom.getNumber() == 0) {
		cout << "Комната не найдена\n";
	}
	else {
		foundRoom.demonstrate(foundRoom.getNumber(), foundRoom.getPrice(), foundRoom.getGuests(), foundRoom.getType(), foundRoom.getBath(), foundRoom.getSmoking());
	}
}

bool compareByPrice(Room& room1, Room& room2) {
	return room1.getPrice() < room2.getPrice();
}

bool compareByGuests(Room& room1, Room& room2) {
	return room1.getGuests() < room2.getGuests();
}

void Hotel::Sort()
{
	cout << "\n\t\tСОРТИРОВКА КОМНАТ\n\t" << endl;
	cout << "\nВыберите критерий сортировки:\n";
	cout << "1. По цене\n";
	cout << "2. По количеству возможных жильцов\n";
	cout << "0. Выход\n";
	int choice = 0;
	cin >> choice;
	while (cin.fail() || choice < 0 || choice>2) {
		cout << "\t!!! Вы некорректно ввели значение !!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}
	if (choice) {
		switch (choice) {
		case 1:
			// Сортировка по цене
			sort(rooms.begin(), rooms.end(), compareByPrice);
			viewRooms();
			break;
		case 2:
			// Сортировка по количеству возможных жильцов
			sort(rooms.begin(), rooms.end(), compareByGuests);
			viewRooms();
			break;
		case 0:
			return;
			break;
		default:
			cout << "Некорректный выбор\n";
			break;
		}
	}
}

void Hotel::readReservationsFromFile() {
	ifstream reservationsFile(this->name + "\\Reservations.txt");
	if (reservationsFile.is_open()) {
		Reservation reservation;
		while (reservationsFile >> reservation) {
			this->reservations.push_back(reservation);
		}
		reservationsFile.close(); // Закрываем файл после завершения чтения
	}
	else {
		cout << "невозможно открыть файл для чтения" << endl;
	}
}

void Hotel::generateRoomsStatisticsReport() {
	int totalRooms = rooms.size();
	int freeRooms = count_if(rooms.begin(), rooms.end(), [&](Room& room) {return !isRoomOccupied(room.getNumber()); });
	int occupiedRooms = totalRooms - freeRooms;

	// Средняя цена за комнату
	float averagePrice = 0;
	if (totalRooms > 0) {
		averagePrice = accumulate(rooms.begin(), rooms.end(), 0.0f,
			[](float sum, Room& room) { return sum + room.getPrice(); }) / totalRooms;
	}

	// Статистика по классам комнат
	map<int, int> roomClassCount;
	for (Room& room : rooms) {
		roomClassCount[room.getType()]++;
	}

	// Статистика по типу ванны
	int bathCount = count_if(rooms.begin(), rooms.end(), [](Room& room) { return room.getBath() == 1; });
	int showerCount = totalRooms - bathCount;

	// Статистика по курящим/некурящим комнатам
	int smokingRoomsCount = count_if(rooms.begin(), rooms.end(), [](Room& room) { return room.getSmoking() == 1; });
	int nonSmokingRoomsCount = totalRooms - smokingRoomsCount;

	ofstream hotel;
	hotel.open(this->name + "\\Report.txt", ios::trunc);
	if (!hotel.is_open()) {
		cerr << "Ошибка открытия файла для записи." << endl;
		return;
	}

	hotel << "\nСтатистика по комнатам:\n";
	hotel << "Общее количество комнат: " << totalRooms << endl;
	hotel << "Количество свободных комнат: " << freeRooms << endl;
	hotel << "Количество забронированных комнат: " << occupiedRooms << endl;
	hotel << "Средняя цена за комнату: " << fixed << setprecision(2) << averagePrice << endl;

	hotel << "\nСтатистика по классам комнат:\n";
	for (const auto& pair : roomClassCount) {
		hotel << "Класс " << pair.first << ": " << pair.second << " комнат" << endl;
	}

	hotel << "\nСтатистика по типу ванны:\n";
	hotel << "Ванная: " << bathCount << " комнат\n";
	hotel << "Душ: " << showerCount << " комнат\n";

	hotel << "\nСтатистика комнат для курящих/некурящих:\n";
	hotel << "Для курящих: " << smokingRoomsCount << " комнат\n";
	hotel << "Некурящих: " << nonSmokingRoomsCount << " комнат\n";

	hotel.close();
}




