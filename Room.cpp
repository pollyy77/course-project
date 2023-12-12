#include "Room.h"
#include <iomanip>
#include <limits>

using namespace std;

float Room::getPrice()
{
	return this->price;
}

int Room::getGuests()
{
	return this->guests;
}

int Room::getNumber()
{
	return number;
}

int Room::getType()
{
	return type;
}

int Room::getBath()
{
	return bath;
}

int Room::getSmoking()
{
	return smoking;
}

void Room::readFromFile(const std::string& filePath) {
	std::ifstream inputFile(filePath);
	if (inputFile.is_open()) {
		inputFile >> number >> price >> guests >> type >> bath >> smoking;
		inputFile.close();
	}
}

void Reservation::demonstrateReservation()
{
	cout << "|" << setw(30) << roomNumber << "|" << setw(25) << totalPrice << "|" << setw(25) << checkInDate << "|" << setw(25) << checkOutDate << "|\n";
}

void Reservation::demonstrateReservationMaid()
{
	if (cleaned == true)
	{
		cout << "|" << setw(15) << roomNumber << "|" << setw(20) << totalPrice << "|" << setw(25) << checkInDate << "|" << setw(25) << checkOutDate << "|" << setw(25) << "убрана" << "|\n";
	}
	else
	{
		cout << "|" << setw(15) << roomNumber << "|" << setw(20) << totalPrice << "|" << setw(25) << checkInDate << "|" << setw(25) << checkOutDate << "|" << setw(25) << "не убрана" << "|\n";
	}
}

void Room::demonstrate(int number, int price, int guests, int type, int bath, int smoking)
{
	string roomType;
	string bathType;
	string smokingStatus;

	switch (type) {
	case 1:
		roomType = "standart";
		break;
	case 2:
		roomType = "superior";
		break;
	case 3:
		roomType = "studio";
		break;
	case 4:
		roomType = "lux";
		break;
	case 5:
		roomType = "delux";
		break;
	case 6:
		roomType = "suite";
		break;
	case 7:
		roomType = "business";
		break;
	case 8:
		roomType = "prec. suite";
		break;
	default:
		roomType = "unknown";
		break;
	}

	switch (bath) {
	case 1:
		bathType = "ванная";
		break;
	case 2:
		bathType = "душ";
		break;
	default:
		bathType = "unknown";
		break;
	}

	switch (smoking) {
	case 1:
		smokingStatus = "да";
		break;
	case 2:
		smokingStatus = "нет";
		break;
	default:
		smokingStatus = "unknown";
		break;
	}

	cout << "|" << setw(30) << number << "|" << setw(12) << price << "|" << setw(24) << guests << "|"
		<< setw(13) << roomType << "|" << setw(13) << bathType << "|" << setw(13) << smokingStatus << "|\n";
}

void Room::initialisation()
{
	cout << "\tВведите номер комнаты: ";
	cin >> number;
	while (cin.fail() || (number < 1 || number>1000)) {
		cout << "\t!!! Вы некорректно ввели значение!!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> number;
	}
	cout << "\tВведите цену: ";
	cin >> price;
	while (cin.fail() || (price < 100 || price>1000000)) {
		cout << "\t!!! Вы некорректно ввели значение, цена должна быть больше 100!!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> price;
	}
	cout << "\tВведите количество возможных жильцов: ";
	cin >> guests;
	while (cin.fail() || (guests < 1 || guests > 5)) {
		cout << "\t!!! Вы некорректно ввели значение, кол-во возможных жильцов должно быть от 1 до 5!!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> guests;
	}
	cout << "\tВведите класс комнаты(1-standart|2-superior|3-studio|4-lux|5-delux|6-suite|7-business|8-presidential suite): ";
	cin >> type;
	while (cin.fail() || (type <= 0 || type > 8)) {
		cout << "\t!!! Вы некорректно ввели значение!!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> type;
	}
	cout << "\tВведите тип санузла(1-ванная|2-душ): ";
	cin >> type;
	while (cin.fail() || (type <= 0 || type > 2)) {
		cout << "\t!!! Вы некорректно ввели значение!!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> type;
	}
	cout << "\tКомната для курящих?(1-да|2-нет): ";
	cin >> type;
	while (cin.fail() || (type <= 0 || type > 2)) {
		cout << "\t!!! Вы некорректно ввели значение!!!\n";
		cout << "\tваш новый ответ - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> type;
	}
}


