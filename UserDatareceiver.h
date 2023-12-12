#pragma once
#include <string>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<vector>
#include<memory>
#include"User.h"
#include<iomanip>
#include"Hotel.h"
#include"FileWorkerClients.h"
using namespace std;
class User;
class Hotel;

// абстрактный класс (с помощью чисто виртуального деструктора) - дабы не было возможности
//создать объект этого класса
class UserDataReceiver
{
protected:
	string userHashPassword;
	string userLogin;
	static const string fileName;

public:
	virtual ~UserDataReceiver() = 0 {};
	void getUserData();//получение пользовательских данных
	virtual bool isExists() = 0;
};

class Authorization : public UserDataReceiver
{
public:
	bool isExists();
	bool isExists(shared_ptr<User>  BaseClassSmartPointer, Hotel&);//проверка существования зарегистрированного пользователя
};

class Registration : public UserDataReceiver
{
public:
	void Register();
	friend string getFilePath();

	string getLogin();
	string getHashPassword();
	bool isExists();
	bool isHotelExists(string);
};
