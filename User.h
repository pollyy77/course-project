#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<map>
#include"Hotel.h"
#include"UserDatareceiver.h"
#include"SHA256.h"

class Hotel;
class Registration;
class User {
protected:
	unsigned int role;
	unsigned int access;
	string login;
	string hashPassword;
public:

	void initialize(string, string, unsigned int, unsigned int);//инициализация данными
	void demonstrate();//отображение данных пользователя


	virtual void ShowMenu(Hotel&);//меню

	void clone(shared_ptr<User>);//копирование данных из умного указателя
	void clone(Registration& obj);//копирование данных из объекта регистрации

	// перегруженные операторы потокового ввода-вывода
	friend istream& operator >> (istream& in, User& t)
	{
		getline(in, t.login);
		getline(in, t.hashPassword);
		in >> t.role >> t.access;

		return in;
	}
	friend ostream& operator << (ostream& os, const User& t)
	{
		os << t.login << endl;
		os << t.hashPassword << endl;
		os << t.role << " " << t.access << endl;
		return os;
	}

	string getHashPassword();//получить пароль
	string getLogin();//получить логин
	unsigned int getAccess();//получить параметр доступа
	unsigned int getRole();//получить роль

	void setAccess(int);//изменить доступ
	void setRole(int);//изменить роль

};
// администратор отеля
class Administrator : public User {
private:
public:

	void ShowMenu(Hotel&) override;
	void workWithStaffClients(Hotel&);
	void workWithData(Hotel&);
	void allowAccess(int, Hotel&);
	void denyAccess(int, Hotel&);
	void addEmployee(Hotel&);
	void deleteEmployeeClient(Hotel&);
	void addRoom(Hotel&);
	void deleteRoom(Hotel&);

};

//гость
class Client : public User {
public:
	void ShowMenu(Hotel&) override;
	void addReservation(Hotel& hotel);
	void viewUserReservedRooms(Hotel&);
};

// горничная
class Maid : public Client {
public:
	void ShowMenu(Hotel&) override;
	void readReservationsFromFileMaid(Hotel&);
	void viewAllReservedRooms(const Hotel& hotel);
	void markRoomAsCleaned(Hotel& hotel, int roomNumber);
};

// работник ресторана
class RestaurantWorker : public User {
};
