#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<direct.h>
#include <regex>
#include< chrono >
#include"User.h"
#include"FileWorkerClients.h"
#include"Room.h"


class User;

class Hotel {

	string name;
	vector<User>users;
	vector<Room> rooms;
	vector<Reservation> reservations;
public:
	bool isValidDateFormat(const string& date) {
		// Проверка формата "дд-мм-гггг"
		regex dateRegex("\\b\\d{2}-\\d{2}-\\d{4}\\b");
		return regex_match(date, dateRegex);
	}

	void setName(string);//изменить название отеля
	string getName();//получить название отеля
	int getRoomNumber(int);//получить номер комнаты
	float getRoomPrice(int);//получить цену конкретной комнаты
	int getRoomType(int);//получить класс номера
	int getRoomGuests(int);//получить возможное кол-во жильцов
	int getRoomBath(int);
	int getRoomSmoking(int);


	void initialisation();//иннициализация данными из файла (запись в вектора пользователей и комнат)
	void updateFiles();//сохранение изменений в соответствующих файлах

	void showEmployeesClients();//демонстрация всех 
	void addEmployee(User);//добавление пользователя
	void deleteEmployee(int);//удаление пользователя

	Room findRoomByNumber(int roomNumber) {
		for (Room& room : rooms) {
			if (room.getNumber() == roomNumber) {
				return room;
			}
		}
		// Если комната не найдена, вернуть пустую комнату 
		return Room();
	}

	void viewRooms();//отображение всех комнат отеля
	void addRoom(Room);
	//добавление комнаты
	void deleteRoom(int);//удаление комнаты

	void setAccessAllow(int);//изменение доступа (разрешение)
	void setAccessDeny(int);//изменение доступа (запрет)

	unsigned int numberUsers();//возвращает кол-во 
	unsigned int numberRooms();//возвращает кол-во комнат
	void clear();//очищает вектора клиентов и комнат в отеле

	void Find(int roomNumberToFind);
	void Sort();
	void readReservationsFromFile();
	//сотрировка
	vector<Reservation> getReservations(const string& userLogin) const {
		vector<Reservation> userReservations;
		for (const Reservation& reservation : reservations) {
			if (reservation.userLogin == userLogin) {
				userReservations.push_back(reservation);
			}
		}
		return userReservations;
	}

	vector<Reservation> getAllReservations() const {
		vector<Reservation> allReservations;
		for (const Reservation& reservation : reservations) {
			allReservations.push_back(reservation);
		}
		return allReservations;
	}

	bool isRoomAvailable(int roomNumber, const string& checkInDate, const string& checkOutDate) {
		tm checkInTime = {};
		tm checkOutTime = {};
		istringstream ss1(checkInDate);
		istringstream ss2(checkOutDate);
		ss1 >> get_time(&checkInTime, "%Y-%m-%d");
		ss2 >> get_time(&checkOutTime, "%Y-%m-%d");

		auto checkIn = chrono::system_clock::from_time_t(mktime(&checkInTime));
		auto checkOut = chrono::system_clock::from_time_t(mktime(&checkOutTime));

		for (const Reservation& reservation : reservations) {
			if (reservation.roomNumber == roomNumber) {
				tm reservationCheckInTime = {};
				tm reservationCheckOutTime = {};
				istringstream ss3(reservation.checkInDate);
				istringstream ss4(reservation.checkOutDate);
				ss3 >> get_time(&reservationCheckInTime, "%Y-%m-%d");
				ss4 >> get_time(&reservationCheckOutTime, "%Y-%m-%d");

				auto reservationCheckIn = chrono::system_clock::from_time_t(mktime(&reservationCheckInTime));
				auto reservationCheckOut = chrono::system_clock::from_time_t(mktime(&reservationCheckOutTime));

				if (checkOut > reservationCheckIn && checkIn < reservationCheckOut) {
					return false; // Комната забронирована для указанного периода
				}
			}
		}
		return true; // Комната доступна для указанного периода
	}

	void makeReservation(int roomNumber, string& checkInDate, string& checkOutDate, string userLogin, Hotel& hotel) {
		Room room = findRoomByNumber(roomNumber);
		if (room.getNumber() == 0) {
			cout << "Комната не найдена." << endl;
			return;
		}

		if (!isValidDateFormat(checkInDate) || !isValidDateFormat(checkOutDate)) {
			cout << "Неверный формат даты." << endl;
			return;
		}

		if (isRoomAvailable(roomNumber, checkInDate, checkOutDate)==false){
			cout << "Комната забронирована в указанный период." << endl;
			return;
		}
		else {
			Reservation reservation = room.bookRoom(checkInDate, checkOutDate, userLogin);
			reservation.cleaned = false;
			reservations.push_back(reservation);

			cout << "Бронирование успешно. Детали:" << endl;
			cout << "______________________________________________________________________________________________________________\n";
			cout << "|" << setw(30) << "НОМЕР КОМНАТЫ" << "|" << setw(25) << "ОБЩАЯ СТОИМОСТЬ" << "|" << setw(25) << "ДАТА ЗАЕЗДА" << "|" << setw(25) << "ДАТА ВЫЕЗДА" << "|\n";
			cout << "______________________________________________________________________________________________________________\n";
			reservation.demonstrateReservation();
			cout << "______________________________________________________________________________________________________________\n";
		}
	}

	void markRoomCleaned(int roomNumber) {
		for (Reservation& reservation : reservations) {
			if (reservation.roomNumber == roomNumber) {
				reservation.cleaned = true;
				cout << "Уборка для комнаты номер " << roomNumber << " отмечена." << endl;
				return;
			}
		}
		cout << "Комната не найдена." << endl;
	}

	vector<Room> filterRoomsByPrice(float minPrice, float maxPrice) {
		vector<Room> filteredRooms;
		// Используем алгоритм copy_if для фильтрации комнат по стоимости
		copy_if(rooms.begin(), rooms.end(), back_inserter(filteredRooms),
			[minPrice, maxPrice](Room& room) {
				float roomPrice = room.getPrice();
				return roomPrice >= minPrice && roomPrice <= maxPrice;
			});
		return filteredRooms;
	}

	void generateRoomsStatisticsReport();

	bool isRoomOccupied(int roomNumber) {
		for (const Reservation& reservation : reservations) {
			if (reservation.roomNumber == roomNumber) {
				return true; // Комната забронирована
			}
		}
		return false; // Комната доступна
	}
};
