#pragma once
#include<vector>
#include<fstream>
#include<iostream>
#include<string>
using namespace std;

template<typename T>//шаблонный класс, существующий для записи вектора в файл 

class FileWorker
{
protected:
	vector<T> myVec;

public:
	//вывод своего вектора из файла
	friend istream& operator >> (istream& in, FileWorker& t)
	{
		T obj;
		string newLine;
		while (in >> obj && getline(in, newLine))
			t.myVec.push_back(obj);

		return in;
	}
	//запись своего вектора в файл
	friend ostream& operator << (ostream& os, FileWorker& t)
	{
		for (size_t i = 0; i < t.myVec.size(); i++) {

			os << t.myVec[i];
		}

		return os;
	}

	// копирует переданный вектор в свой вектор
	void cloneFrom(vector<T>& vec) {
		for (unsigned int i = 0; i < vec.size(); i++) {
			myVec.push_back(vec[i]);
		}
	}

	// копирует свой вектор в переданный вектор
	void cloneTo(vector<T>& vec) {
		for (size_t i = 0; i < myVec.size(); i++) {
			vec.push_back(myVec[i]);
		}
	}
};
