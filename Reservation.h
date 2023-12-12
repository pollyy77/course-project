#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;
class Reservation {
public:
    int roomNumber;
    float totalPrice;
    string checkInDate;
    string checkOutDate;
    string userLogin;
    bool cleaned;

    friend ostream& operator<<(ostream& os, const Reservation& reservation) {
        os << reservation.roomNumber << endl;
        os << reservation.totalPrice << endl;
        os << reservation.checkInDate << endl;
        os << reservation.checkOutDate << endl;
        os << reservation.userLogin << endl;
        os << reservation.cleaned << endl;
        return os;
    }

    friend istream& operator>>(istream& is, Reservation& reservation) {
        is >> reservation.roomNumber;
        is >> reservation.totalPrice;
        is >> reservation.checkInDate;
        is >> reservation.checkOutDate;
        is >> reservation.userLogin;
        is >> reservation.cleaned;
        return is;
    }
    void demonstrateReservation();
    void demonstrateReservationMaid();
};
