#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>

class Time
{
private:
	size_t _hour;
	size_t _minute;
	size_t _second;

	bool IsCorrectHours(size_t hour)
	{
		return hour >= 0 && hour < 24;
	}

	bool IsCorrectMinutes(size_t minutes)
	{
		return minutes >= 0 && minutes < 60;
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
			throw "Проблема с созданием Time, проверьте входные параметры!\n";
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
		if(_hour > t._hour)
		{
			if(_minute > t._minute)
			{
				return _second > t._second;
			}
		}
		return  false;
	}

	bool operator < (Time t)
	{
		if(_hour < t._hour)
		{
			if(_minute < t._minute)
			{
				return _second < t._second;
			}
		}
		return  false;
	}

	bool operator <= (Time t)
	{
		if(_hour <= t._hour)
		{
			if(_minute <= t._minute)
			{
				return _second <= t._second;
			}
		}
		return  false;
	}

	bool operator >= (Time t)
	{
		if(_hour >= t._hour)
		{
			if(_minute >= t._minute)
			{
				return _second >= t._second;
			}
		}
		return  false;
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
		if(come >= getOut)
		{
			come.ShowInfo(); std::cout << '\n';
			getOut.ShowInfo(); std::cout << '\n';
			throw "Время прихода больше или равно чем время ухода!\n";
		}
		else
		{
			_come = come;
			_getOut = getOut;
		}
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

bool IsCorrectExtention(std::string& filename, std::string  extention = ".txt")
{
	try
	{
		for(int i = extention.size() - 1, j = filename.size() - 1; i >= 0; i--, j--)
		{
			if(extention[i] != filename[j])
			{
				return false;
			}
		}
	}
	catch(const std::exception&)
	{
		return false;
	}

	return true;
}

//00:00:00
Time StringToTime(std::string s)
{
	std::string hour = "";
	hour += s[0];
	hour += s[1];

	std::string min = "";
	min += s[3];
	min += s[4];

	std::string sec = "";
	sec += s[6];
	sec += s[7];

	return Time(stoi(hour), stoi(min), stoi(sec));
}

std::vector<Pair> ParseFromFile(std::ifstream& outFile)
{
	std::string line;
	std::vector<Pair> times;
	Time come;
	Time leave;
	std::string timeInStr = "";

	while(std::getline(outFile, line))
	{
		for(size_t i = 0; i < line.size(); i++)
		{
			if(line[i] != ' ')
			{
				timeInStr += line[i];
			}
			else
			{
				come = StringToTime(timeInStr);
				timeInStr.clear();
			}
		}
		leave = StringToTime(timeInStr);
		times.push_back(Pair(come, leave));
		timeInStr.clear();
	}
	outFile.close();
	return times;
}

void ReadFromFile()
{
	std::string input;
	bool isCorrect = false;
	std::ifstream outFile;
	while(isCorrect == false)
	{
		std::cout << "Введите имя файла с раширением txt\n";
		std::cout << "Пример верного файла с расширением: input.txt\n";
		std::cin >> input;

		if(IsCorrectExtention(input))
		{
			outFile.open(input);
			if(outFile.is_open())
			{
				system("cls");
				try
				{
					std::vector<Pair> times = ParseFromFile(outFile);
					for(size_t i = 0; i < times.size(); i++)
					{
						times[i].ShowInfo();
					}
				}
				catch(const char* str)
				{
					std::cout << str;
				}
				isCorrect = true;
			}
			else
			{
				std::cout << "Такого файла не сущестует!\n";
			}
		}
		else
		{
			std::cout << "Неверное расширение!\n";
		}
	}
}

using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");

	ReadFromFile();
	system("pause");
	return 0;
}