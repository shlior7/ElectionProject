#include "Date.h"


	Date::Date(){day = month = year = 0;}

	Date::Date(int _day, int _month, int _year) : day(_day), month(_month), year(_year)
	{	
		if (month == 2 && day > 28)
			throw Except("Febuary has 28 days!");
		if(month == 4 || month == 6 || month == 9 || month == 11)
			if(day>30)
				throw Except("this month only has 30 days!");
	}

	Date ::~Date() = default;

	bool Date::setDay(int _day) { day = _day; return true; }
	bool Date::setMonth(int _month){month = _month; return true;}
	bool Date::setYear(int _year){year = _year; return true;}
	bool Date::setDate(int _day, int _month, int _year) { return (setDay(_day) && setMonth(_month) && setYear(_year)); }

	void Date::save(ostream& out)const
	{
		out.write(rcastcc(this), sizeof(*this));
		if (!out.good())
			throw Except("Saving Error");
	}
	void Date::load(istream& in)
	{
		in.read(rcastc(this), sizeof(*this));
	}