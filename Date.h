#pragma once
#include "General.h"
class Date
{
private:
	int day, month, year;
public:
	Date();
	Date(int _day, int _month, int _year);
	~Date();
	/*Getters*/
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }
	/*Setters*/
	bool setDay(int _day);
	bool setMonth(int _month);
	bool setYear(int _year);
	bool setDate(int _day, int _month, int _year);
	/*Serialization*/
	void save(ostream& out)const;
	void load(istream& in);
};
