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
			throw "Проблема с созданием Time, проверьте формат входных параметров! Верный формат 00:00:00\n";
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

bool TryStringTosize_t(std::string input, size_t& number)
{
	int countNumer = 0;
	size_t size = input.size();
	int charNumber;
	for(size_t i = 0; i < size; i++)
	{
		charNumber = (int)input[i];
		if(charNumber >= 48 && charNumber <= 57)
		{
			countNumer++;
		}
	}
	bool isCorrect = countNumer == size;
	if(isCorrect)
	{
		number = stoi(input);
	}
	return isCorrect;
}

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

std::vector<std::string> Split(std::string line, char splitter = ' ')
{
	std::vector<std::string> strings;
	size_t size = line.size();
	std::string temp = "";
	for(size_t i = 0; i < size; i++)
	{
		if(splitter == line[i])
		{
			strings.push_back(temp);
			temp = "";
		}
		else
		{
			temp += line[i];
		}
	}
	strings.push_back(temp);
	return strings;
}

Time StringtoTime(std::string timeInStr, std::string description)
{
	std::vector<std::string> hourMinuteSecond;
	hourMinuteSecond = Split(timeInStr, ':');
	if(hourMinuteSecond.size() != 3)
	{
		throw "Проверьте данные в файле. Верный формат 00:00:00\n";
	}

	std::vector<std::size_t> time;
	size_t number;
	for(size_t i = 0; i < hourMinuteSecond.size(); i++)
	{
		if(TryStringTosize_t(hourMinuteSecond[i], number))
		{
			time.push_back(number);
		}
		else
		{
			throw "Проверьте данные в файле. Верный формат 00:00:00\n";
		}
	}
	return Time(time[0], time[1], time[2], description);
}

std::vector<Time> ParseFromFile(std::ifstream& outFile)
{
	std::string line;
	std::vector<Time> times;
	std::string timeInStr = "";
	Time come;
	Time leave;
	while(std::getline(outFile, line))
	{
		for(size_t i = 0; i < line.size(); i++)
		{
			if(line[i] == ' ')
			{
				come = StringtoTime(timeInStr, "start");
				timeInStr.clear();
			}
			else if((i + 1 )== line.size())
			{
				timeInStr += line[i];
				leave = StringtoTime(timeInStr, "end");
				timeInStr.clear();
			}
			else
			{
				timeInStr += line[i];
			}

		}

		if(come > leave)
		{
			throw "Время прихода не может быть больше времени ухода!\n";
		}
		else
		{
			times.push_back(come);
			times.push_back(leave);
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
			throw "В описании может быть start or end!\n";
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

void TryParseToSize_t(std::string name, size_t& number, bool (*compare)(size_t))
{
	std::string input;
	std::cout << name;
	std::cin >> input;
	size_t num;

	if(TryStringTosize_t(input, num) && compare(num))
	{
		number = num;
	}
	else
	{
		throw "Вводите корректные данные!\n";
	}
}

bool IsHours(size_t hour)
{
	return hour >= 0 && hour < 24;
}

bool IsMinutes(size_t minutes)
{
	return minutes >= 0 && minutes < 60;
}

Time GetTimeFromUser(std::string name, std::string description)
{
	size_t hour;
	size_t min;
	size_t sec;
	std::cout << name;
	bool isCorrect = false;
	while(isCorrect == false)
	{
		try
		{
			TryParseToSize_t("Введите часы: ", hour, IsHours);
			TryParseToSize_t("Введите минуты: ", min, IsMinutes);
			TryParseToSize_t("Введите секунды: ", sec, IsMinutes);
			isCorrect = true;
		}
		catch(const char* str)
		{
			std::cout << str;
		}
	}

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
		std::cout << "Продолжить ввод ? Введите Y or N: ";
		std::cin >> input;
		if(input == "Y")
		{
			try
			{
				come = GetTimeFromUser("Введите время прихода:\n", "start");
				leave = GetTimeFromUser("Введите время ухода:\n", "end");
				if(come > leave)
				{
					std::cout << "Время прихода больше черм ухода!!\n";
				}
				else
				{
					times.push_back(come);
					times.push_back(leave);
				}
			}
			catch(const char* str)
			{
				std::cout << str;
			}
		}
		else if(input == "N")
		{
			isEnd = true;
			system("pause");
		}
		else
		{
			std::cout << "Введите Y or N!\n";
		}
	}
	if(times.empty() == false)
	{
		FindMaxInMuseum(times);
	}
}

void ShowMenu()
{
	std::string input;
	bool isExit = false;
	size_t numberOfCommand;
	while(isExit == false)
	{
		std::cout << "Выберете режим\n";
		std::cout << "\t 1 - Ввод из файла.\n";
		std::cout << "\t 2 - Ввод с клавиатуры.\n";
		std::cout << "\t 3 - Выход из программы.\n";
		std::cin >> input;
		if(TryStringTosize_t(input, numberOfCommand) == false)
		{
			std::cout << "Вводить можно только цифры!\n";
			continue;
		}
		switch(numberOfCommand)
		{
			case 1:
			{
				system("cls");
				std::cout << "Вы выбрали ввод из файла!\n";
				ReadFromFile();
				break;
			}
			case 2:
			{
				system("cls");
				std::cout << "Вы выбрали ввод с клавиатуры!\n";
				ReadFromKeyboard();
				break;
			}
			case 3:
			{
				isExit = true;
				std::cout << "Программа закончила свою работу!\n";
				break;
			}

			default:
				std::cout << "Неизвестная команда!\n";
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