#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstring >
#include "Reservation.h"

using namespace std;


class Room {
    int number;
    float price;
    int guests;
    int type;
    int bath;
    int smoking;
    vector<Reservation> reservations;

public:

    friend istream& operator>>(istream& in, Room& t)
    {
        in >> t.number;
        in >> t.price;
        in >> t.guests;
        in >> t.type;
        in >> t.bath;
        in >> t.smoking;
        return in;
    }

    friend ostream& operator<<(ostream& os, const Room& t)
    {
        os << t.number << endl;
        os << t.price << endl;
        os << t.guests << endl;
        os << t.type << endl;
        os << t.bath << endl;
        os << t.smoking << endl;
        return os;
    }

    float getPrice();
    int getNumber();
    int getGuests();
    int getType();
    int getBath();
    int getSmoking();
    void readFromFile(const string& filePath);

  //void demonstrate();

    void demonstrate(int number, int price, int guests, int type, int bath, int smoking);

    void initialisation();

    tm parseDate(const string& date) const {
        tm t = {};
        istringstream ss(date);
        ss >> get_time(&t, "%d-%m-%Y");
        return t;
    }

    int calculateNumberOfDays(const string& checkInDate, const string& checkOutDate) const {
        tm t1 = parseDate(checkInDate);
        tm t2 = parseDate(checkOutDate);

        time_t time1 = mktime(&t1);
        time_t time2 = mktime(&t2);
        double seconds = difftime(time2, time1);

        int numDays = static_cast<int>(seconds / 60 / 60 / 24);

        return numDays;
    }

    float calculateReservationCost(const string& checkInDate, const string& checkOutDate) const {
        int pricePerDay = price;
        int numDays = calculateNumberOfDays(checkInDate, checkOutDate);
        float totalCost = numDays * pricePerDay;
        return totalCost;
    }

    Reservation bookRoom(const string& checkInDate, const string& checkOutDate, const string& userLogin) {
        Reservation reservation;
        reservation.roomNumber = number;
        reservation.checkInDate = checkInDate;
        reservation.checkOutDate = checkOutDate;
        reservation.totalPrice = calculateReservationCost(checkInDate, checkOutDate);
        reservation.userLogin = userLogin;
        reservations.push_back(reservation);
        return reservation;
    }
};
