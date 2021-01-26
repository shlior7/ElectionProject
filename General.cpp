#include "General.h"

int getInt(int rangeL, int rangeR, const string& prompt) {
	cin.exceptions(ios_base::failbit);
	int num = 0;
	while (true) {
		try {
			cout << prompt << endl;
			cin >> num;
			if (num < rangeL || num > rangeR)
				throw 1;
			return num;
		}
		catch (exception& ex)
		{
			cout << " Not a Number--try again\n";
			cin.clear();
			cin.ignore();
		}
		catch (...)
		{
			cout << "Invalid Number--try again\n";
			cin.clear();
			cin.ignore();
		}
	}
}