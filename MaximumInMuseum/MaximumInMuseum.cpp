#include <iostream>
#include <string>
#include <time.h>

class Time
{
private:
	size_t _hour;
	size_t _minute;
	size_t _second;

	bool IsCorrectHours(size_t hour)
	{
		return hour >= 0 && hour <= 24;
	}

	bool IsCorrectMinutes(size_t minutes)
	{
		return minutes >= 0 && minutes <= 60;
	}

	void ShowZeroIf(size_t value)
	{
		if(value <= 9)
		{
			std::cout << '0';
		}
	}

public:
	Time(): _hour(size_t()), _minute(size_t()), _second(size_t())
	{}

	Time(size_t hour, size_t minute, size_t second)
	{
		if(IsCorrectHours(hour) && IsCorrectMinutes(minute) && IsCorrectMinutes(second))
		{
			_hour = hour;
			_minute = minute;
			_second = second;
		}
		else
		{
			throw - 1;
		}
	}

	bool operator == (Time t)
	{
		return _hour == t._hour && _minute == t._minute && _second == t._second;
	}
	
	bool operator != (Time t)
	{
		return _hour != t._hour || _minute != t._minute || _second != t._second;
	}
	
	bool operator > (Time t)
	{
		return _hour > t._hour || _minute > t._minute || _second > t._second;
	}
	
	bool operator < (Time t)
	{
		return _hour < t._hour || _minute < t._minute || _second < t._second;
	}

	void ShowInfo()
	{
		ShowZeroIf(_hour);
		std::cout << _hour;
		std::cout << ":";
		ShowZeroIf(_minute);
		std::cout << _minute;
		std::cout << ":";
		ShowZeroIf(_second);
		std::cout << _second;
	}

	size_t GetHour()
	{
		return _hour;
	}

	size_t GetMinutes()
	{
		return _minute;
	}
};

class Pair
{
private:
	Time _come;
	Time _getOut;

public:
	Pair(): _come(Time()), _getOut(Time())
	{}

	Pair(Time come, Time getOut)
	{
		_come = come;
		_getOut = getOut;
	}

	void ShowInfo()
	{
		_come.ShowInfo();
		std::cout << ' ';
		_getOut.ShowInfo();
		std::cout << '\n';
	}

	Time GetCome()
	{
		return _come;
	}

	Time GetLeave()
	{
		return _getOut;
	}
};

using namespace std;
int main()
{
	Time a(1, 1, 1);
	Time b(1, 2, 3);
	a.ShowInfo(); cout << endl;
	b.ShowInfo(); cout << endl;
	cout << (a == b) << endl;
	cout << (a != b) << endl;
	cout << (a > b) << endl;
	cout << (a < b) << endl;
	system("pause");
	return 0;
}