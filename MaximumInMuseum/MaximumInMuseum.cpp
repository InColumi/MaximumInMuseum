#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>

class Time
{
private:
	size_t _hour;
	size_t _minute;
	size_t _second;
	std::string _description; // start or end

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

	Time(size_t hour, size_t minute, size_t second, std::string description)
	{
		if(IsCorrectHours(hour) && IsCorrectMinutes(minute) && IsCorrectMinutes(second))
		{
			_hour = hour;
			_minute = minute;
			_second = second;
			_description = description;
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
			return true;
		}
		else if(_hour < t._hour)
		{
			return false;
		}
		else
		{
			if(_minute > t._minute)
			{
				return true;
			}
			else if(_minute < t._minute)
			{
				return false;
			}
			else
			{
				return _second > t._second;
			}
		}
	}

	bool operator < (Time t)
	{
		if(_hour < t._hour)
		{
			return true;
		}
		else if(_hour > t._hour)
		{
			return false;
		}
		else
		{
			if(_minute < t._minute)
			{
				return true;
			}
			else if(_minute > t._minute)
			{
				return false;
			}
			else
			{
				return _second < t._second;
			}
		}
	}

	bool operator <= (Time t)
	{
		if(_hour < t._hour)
		{
			return true;
		}
		else if(_hour > t._hour)
		{
			return false;
		}
		else
		{
			if(_minute < t._minute)
			{
				return true;
			}
			else if(_minute > t._minute)
			{
				return false;
			}
			else
			{
				return _second <= t._second;
			}
		}
	}

	bool operator >= (Time t)
	{
		if(_hour > t._hour)
		{
			return true;
		}
		else if(_hour < t._hour)
		{
			return false;
		}
		else
		{
			if(_minute > t._minute)
			{
				return true;
			}
			else if(_minute < t._minute)
			{
				return false;
			}
			else
			{
				return _second >= t._second;
			}
		}
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
		std::cout << " " << _description << '\n';
	}

	size_t GetHour()
	{
		return _hour;
	}

	size_t GetMinutes()
	{
		return _minute;
	}

	std::string GetDescription()
	{
		return _description;
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
Time StringToTime(std::string s, std::string description)
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

	return Time(stoi(hour), stoi(min), stoi(sec), description);
}

std::vector<Time> ParseFromFile(std::ifstream& outFile)
{
	std::string line;
	std::vector<Time> times;
	std::string timeInStr = "";
	size_t size;
	while(std::getline(outFile, line))
	{
		size = line.size() - 1;
		for(size_t i = 0; i <= size; i++)
		{
			if(line[i] == ' ')
			{
				times.push_back(StringToTime(timeInStr, "start"));
				timeInStr.clear();
			}
			else if(i == size)
			{
				times.push_back(StringToTime(timeInStr, "end"));
				timeInStr.clear();
			}
			else
			{
				timeInStr += line[i];
			}
		}
	}
	outFile.close();
	return times;
}

bool IsMax(Time value, Time max)
{
	return value > max;
}

bool IsMin(Time value, Time min)
{
	return value < min;
}

void FindMinMaxCome(std::vector<Pair> pairs, bool (*Compere)(Time, Time))
{
	Time minMax = pairs[0].GetCome();
	for(size_t i = 1; i < pairs.size(); i++)
	{
		if(Compere(pairs[i].GetCome(), minMax))
		{
			minMax = pairs[i].GetCome();
		}
	}

	minMax.ShowInfo();
	std::cout << '\n';
}

void Sort(std::vector<Time>& times)
{
	size_t size = times.size();
	Time temp;
	for(int i = 0; i < size - 1; i++)
	{
		for(int j = 0; j < size - i - 1; j++)
		{
			if(times[j] > times[j + 1])
			{


				// меняем элементы местами
				temp = times[j];
				times[j] = times[j + 1];
				times[j + 1] = temp;
			}
		}
	}
}

void FindMaxInMuseum(std::vector<Time>& times)
{
	/*for(size_t i = 0; i < times.size(); i++)
	{
		times[i].ShowInfo();
	}*/
	Sort(times);
	std::cout << '\n';
	for(size_t i = 0; i < times.size(); i++)
	{
		times[i].ShowInfo();
	}
	int countCustomers = 0;
	int maxCounCustomers = 0;
	for(size_t i = 0; i < times.size(); i++)
	{
		if(times[i].GetDescription() == "start")
		{
			countCustomers++;
		}
		else if(times[i].GetDescription() == "end")
		{
			countCustomers--;
		}
		else
		{
			throw "В описании может быть start or end!\n";
		}

		if(countCustomers > maxCounCustomers)
		{
			maxCounCustomers = countCustomers;
		}
	}

	std::cout << maxCounCustomers << std::endl;

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
		//std::cin >> input;
		input = "1.txt";
		if(IsCorrectExtention(input))
		{
			outFile.open(input);
			if(outFile.is_open())
			{
				system("cls");
				try
				{
					std::vector<Time> times = ParseFromFile(outFile);
					FindMaxInMuseum(times);
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