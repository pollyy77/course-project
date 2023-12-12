#include<Windows.h>
#include<fstream>
#include<memory>
#include"SHA256.h"
#include"User.h"
#include"UserDataReceiver.h"
#include"Hotel.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true) {

		system("cls");

		int choice;
		cout << "\t\t\tМЕНЮ\n\t1 - авторизоваться\n\t2 - зарегистрироваться\n\t0 - завершить работу\n\tответ: ";
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
			return 0;
			break;
		case 1: {
			Hotel hotel;// отель
			shared_ptr<User> pObject = make_shared<User>();
			Authorization obj;
			obj.getUserData();
			if (obj.isExists(pObject, hotel))//реализована инициализация пользователя и отеля
			{
				cout << "\n\tВы успешно авторизовались\n";
				if (pObject->getAccess() == 1) {
					if (pObject->getRole() == 0) {
						shared_ptr<User> pAdmin = make_shared<Administrator>();
						pAdmin->clone(pObject);//данные общего типа конкретизируются в частном типе

						pAdmin->ShowMenu(hotel);
					}
					if (pObject->getRole() == 1) {
						shared_ptr<User> pEmployee = make_shared<Client>();
						pEmployee->clone(pObject);//данные общего типа конкретизируются в частном типе

						pEmployee->ShowMenu(hotel);
					}
					if (pObject->getRole() == 2) {
						shared_ptr<User> pClient = make_shared<Maid>();
						pClient->clone(pObject);//данные общего типа конкретизируются в частном типе

						pClient->ShowMenu(hotel);
					}
				}
				else cout << "\n\tНо Вам не предоставлен доступ\n";
			}
		}
			  break;
		case 2: {

			Registration obj;
			obj.getUserData();
			obj.Register();

		}
			  break;
		}

		system("pause");

	}
}
