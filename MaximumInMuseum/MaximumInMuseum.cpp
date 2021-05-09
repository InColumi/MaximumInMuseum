#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "MaximumInMuseum.h"

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
			throw "�������� � ��������� Time, ��������� ������� ���������!\n";
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
		std::cout << _second << std::endl;
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

void Sort(std::vector<Time>& times)
{
	size_t size = times.size();
	Time temp;
	for(size_t i = 0; i < size - 1; i++)
	{
		for(size_t j = 0; j < size - i - 1; j++)
		{
			if(times[j] > times[j + 1])
			{


				// ������ �������� �������
				temp = times[j];
				times[j] = times[j + 1];
				times[j + 1] = temp;
			}
		}
	}
}

void FindMaxInMuseum(std::vector<Time>& times)
{
	Sort(times);
	int countCustomers = 0;
	int maxCounCustomers = 0;
	std::vector<Time> interval;
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
			throw "� �������� ����� ���� start or end!\n";
		}

		if(countCustomers > maxCounCustomers)
		{
			interval.clear();
			interval.push_back(times[i]);
			interval.push_back(times[i + 1]);
			maxCounCustomers = countCustomers;
		}
	}
	for(size_t i = 0; i < interval.size(); i++)
	{
		interval[i].ShowInfo();
	}

}

void ReadFromFile()
{
	std::string input;
	bool isCorrect = false;
	std::ifstream outFile;
	while(isCorrect == false)
	{
		std::cout << "������� ��� ����� � ���������� txt\n";
		std::cout << "������ ������� ����� � �����������: input.txt\n";
		std::cin >> input;
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
				std::cout << "������ ����� �� ���������!\n";
			}
		}
		else
		{
			std::cout << "�������� ����������!\n";
		}
	}
}

bool TryParseToInt(int& number)
{
	std::string input;
	std::cin >> input;
	try
	{
		number = stoi(input);
		return true;
	}
	catch(const std::exception&)
	{
		std::cout << "������� ����� ������ �����!\n\n";
		return false;
	}

}

void TryParseToSize_t(std::string name, size_t& number)
{
	std::string input;
	std::cout << name;
	std::cin >> input;
	int num;
	try
	{
		num = stoi(input);
		if(number >= 0)
		{
			number = num;
		}
	}
	catch(const std::exception&)
	{
		std::cout << "������� ���������� ������!\n";
	}
}

Time GetTimeFromUser(std::string name, std::string description)
{
	size_t hour;
	size_t min;
	size_t sec;
	std::cout << name;
	TryParseToSize_t("������� ����: ", hour);
	TryParseToSize_t("������� ������: ", min);
	TryParseToSize_t("������� �������: ", sec);
	return Time(hour, min, sec, description);
}

void ReadFromKeyboard()
{
	std::vector<Time> times;
	std::string input;
	Time come;
	Time leave;
	bool isEnd = false;
	while(isEnd == false)
	{
		std::cout << "���������� ���� ? ������� Y or N: ";
		std::cin >> input;
		if(input == "Y")
		{
			come = GetTimeFromUser("������� ����� �������:\n", "start");
			leave = GetTimeFromUser("������� ����� �����:\n", "end");
			if(come > leave)
			{
				std::cout << "����� ������� ������ ���� �����!!\n";
			}
			else
			{
				times.push_back(come);
				times.push_back(leave);
			}
			
		}
		else if(input == "N")
		{
			isEnd = true;
			system("pause");
		}
		else
		{
			std::cout << "������� Y or N!\n";
		}
	}
	FindMaxInMuseum(times);
}

void ShowMenu()
{
	std::string input;
	bool isExit = false;
	int numberOfCommand;
	while(isExit == false)
	{
		std::cout << "�������� �����\n";
		std::cout << "\t 1 - ���� �� �����.\n";
		std::cout << "\t 2 - ���� � ����������.\n";
		std::cout << "\t 3 - ����� �� ���������.\n";
		if(TryParseToInt(numberOfCommand) == false)
		{
			continue;
		}
		switch(numberOfCommand)
		{
			case 1:
			{
				system("cls");
				std::cout << "�� ������� ���� �� �����!\n";
				ReadFromFile();
				break;
			}
			case 2:
			{
				system("cls");
				std::cout << "�� ������� ���� � ����������!\n";
				ReadFromKeyboard();
				break;
			}
			case 3:
			{
				isExit = true;
				std::cout << "��������� ��������� ���� ������!\n";
				break;
			}

			default:
				std::cout << "����������� �������!\n";
				break;
		}
	}
}

using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");

	ShowMenu();
	system("pause");
	return 0;
}