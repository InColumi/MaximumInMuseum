#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//класс для работы с временем
class Time
{
private:
	size_t _hour;
	size_t _minute;
	size_t _second;
	size_t _id;
	string _description; // start or end

	//проверка корректности часов
	//принимает час
	//возвращает лог.значение
	bool IsCorrectHours(size_t hour)
	{
		return hour >= 0 && hour < 24;
	}

	//проверка корректности минут
	//принимает минуты
	//возвращает лог.значение
	bool IsCorrectMinutesOrSeconds(size_t time)
	{
		return time >= 0 && time < 60;
	}

	//добавление нуля при его отсутствии в шаблоне
	//принимает значение
	void ShowZeroIfMoreThenNine(size_t value)
	{
		if(value <= 9)
		{
			cout << '0';
		}
	}

public:
	Time(): _hour(size_t()), _minute(size_t()), _second(size_t()), _id(size_t())
	{}

	Time(size_t hour, size_t minute, size_t second, string description, size_t id)
	{
		//проверка корректности времени
		if(IsCorrectHours(hour) && IsCorrectMinutesOrSeconds(minute) && IsCorrectMinutesOrSeconds(second))
		{
			_hour = hour;
			_minute = minute;
			_second = second;
			_description = description;
			_id = id;
		}
		else
		{
			throw "Проблема с созданием Time, проверьте формат входных параметров! Верный формат 00:00:00\n";
		}
	}

	//перегрузка операторов
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
		//проверка корректности часов, минут, секунд
		return (_hour == t._hour) ? (_minute == t._minute) ? _second > t._second : _minute > t._minute : _hour > t._hour;
	}

	bool operator < (Time t)
	{
		//проверка корректности часов, минут, секунд
		return (_hour == t._hour) ? (_minute == t._minute) ? _second < t._second : _minute < t._minute : _hour < t._hour;
	}

	bool operator <= (Time t)
	{
		//проверка корректности часов, минут, секунд
		return (_hour == t._hour) ? (_minute == t._minute) ? _second <= t._second : _minute < t._minute : _hour < t._hour;
	}

	bool operator >= (Time t)
	{
		//проверка корректности часов, минут, секунд
		return (_hour == t._hour) ? (_minute == t._minute) ? _second >= t._second : _minute > t._minute : _hour > t._hour;
	}

	//вывод времени
	void ShowInfo()
	{
		//добавление нуля, если его нет
		ShowZeroIfMoreThenNine(_hour);
		cout << _hour;
		cout << ":";
		ShowZeroIfMoreThenNine(_minute);
		cout << _minute;
		cout << ":";
		ShowZeroIfMoreThenNine(_second);
		cout << _second << "\n";
	}
	//получение времени
	size_t GetHour()
	{
		return _hour;
	}

	size_t GetMinutes()
	{
		return _minute;
	}

	size_t GetId()
	{
		return _id;
	}

	string GetDescription()
	{
		return _description;
	}
};

class Pair
{

private:
	Time _start;
	Time _end;
public:
	Pair():_start(Time()), _end(Time())
	{}

	Pair(Time start, Time end):_start(start), _end(end)
	{}

	Time GetStart()
	{
		return _start;
	}

	Time GetEnd()
	{
		return _end;
	}
};

//преобразование string в size_t
//принимает строку и число
//возвращает лог.значение
bool TryStringTosize_t(string input, size_t& number)
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

//проверка правильности расширения файла
//принимает имя файла и расширение
//возвращает лог.значение проверки
bool IsCorrectExtention(string& filename, string  extention = ".txt")
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
	catch(std::exception err)
	{
		std::cout << "Неверное расширение файла" << std::endl;
	}

	return true;
}

//разделение строки времени
vector<string> Split(string line, char splitter = ' ')
{
	vector<string> strings;
	size_t size = line.size();
	string temp = "";
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

//обработка строки со временем
//принимает время
//возвращает разделенное время: часы, минуты, секунды
Time StringtoTime(string timeInStr, string description, size_t id)
{
	vector<string> hourMinuteSecond;
	hourMinuteSecond = Split(timeInStr, ':');
	//первоначальная проверка соответствия шаблону 
	if(hourMinuteSecond.size() != 3)
	{
		throw "Проверьте данные в файле. Верный формат 00:00:00\n";
	}

	vector<size_t> time;
	size_t number;
	for(size_t i = 0; i < hourMinuteSecond.size(); i++)
	{
		//проверка соответствия шаблону
		if(TryStringTosize_t(hourMinuteSecond[i], number))
		{
			time.push_back(number);
		}
		else
		{
			throw "Проверьте данные в файле. Верный формат 00:00:00\n";
		}
	}
	return Time(time[0], time[1], time[2], description, id);
}

//работа с файлом
//принимает объект файла
//возвращает вектор времени прихода,ухода
vector<Time> ParseFromFile(ifstream& outFile, vector<Pair>& pairs)
{
	vector<Time> times;
	string line;
	string timeInStr = "";
	Time come;
	Time leave;
	size_t countCustomers = 1;
	//чтение строк из файла
	while(getline(outFile, line))
	{
		for(size_t i = 0; i < line.size(); i++)
		{
			if(line[i] == ' ')
			{
				come = StringtoTime(timeInStr, "start", countCustomers);
				timeInStr.clear();
			}
			else if((i + 1) == line.size())
			{
				timeInStr += line[i];
				leave = StringtoTime(timeInStr, "end", countCustomers);
				timeInStr.clear();
			}
			else
			{
				timeInStr += line[i];
			}

		}
		//проверка корректности времени прихода,ухода
		if(come > leave)
		{
			throw "Время прихода не может быть больше времени ухода!\n";
		}
		//добавление времени прихода,ухода
		else
		{
			times.push_back(come);
			times.push_back(leave);
			size_t size = times.size();
			pairs.push_back(Pair(times[size - 2], times[size - 1]));
		}
		countCustomers++;
	}
	outFile.close();
	return times;
}

//сортировка времени для обработки
//принимает вектор времени
void Sort(vector<Time>& times)
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

//поиск интервала с макс.числом людей
void FindMaxInMuseum(vector<Time>& times, vector<Pair>& pairs)
{
	Sort(times);
	int countCustomers = 0;
	int maxCounCustomers = 0;
	Time start;
	Time end;
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
			throw "В описании возможны start или end!\n";
		}

		//добавление нового числа макс.людей
		if(countCustomers > maxCounCustomers)
		{
			start = times[i];
			end = times[i + 1];
			maxCounCustomers = countCustomers;
		}
	}

	cout << "Интервал с максимальным количеством посетителей\n";
	//вывод интервала времени с макс.числом людей
	start.ShowInfo();
	end.ShowInfo();

	cout << "Находились люди: ";
	Time startInPair;
	Time endInPair;
	for(size_t i = 0; i < pairs.size(); i++)
	{
		startInPair = pairs[i].GetStart();
		endInPair = pairs[i].GetEnd();
		if(startInPair.GetDescription() == "start" && startInPair <= start &&
		   endInPair.GetDescription() == "end" && endInPair >= end)
		{
			cout << endInPair.GetId() << ',';
		}
	}
}

//чтение из файла
void ReadFromFile()
{
	string input;
	bool isCorrect = false;
	ifstream outFile;
	while(isCorrect == false)
	{
		cout << "Введите имя файла с раширением txt" << endl;
		cout << "Пример верного файла с расширением: input.txt" << endl;
		cin >> input;
		//проверка расширения файла
		if(IsCorrectExtention(input))
		{
			outFile.open(input);
			//проверка наличия файла
			if(outFile.is_open())
			{
				//чтение файла
				//поиск интервала с макс.числом
				try
				{
					vector<Pair> pairs;
					vector<Time> times = ParseFromFile(outFile, pairs);
					FindMaxInMuseum(times, pairs);
				}
				catch(const char* str)
				{
					cout << str;
				}
				isCorrect = true;
			}
			else
			{
				cout << "Такого файла не сущестует!" << endl;
			}
		}
		else
		{
			cout << "Неверное расширение!" << endl;
		}
	}
}

//проверка корректности ввода данных
//принимает строку, число и лог.принадлежнсть числа
void TryParseToSize_t(string name, size_t& number, bool (*compare)(size_t))
{
	string input;
	cout << name;
	cin >> input;
	size_t num;

	if(TryStringTosize_t(input, num) && compare(num))
	{
		number = num;
	}
	else
	{
		throw "Ошибка конвертации строки в число!";
	}
}

//проверка часов
bool IsHours(size_t hour)
{
	return hour >= 0 && hour < 24;
}

//проверка минут, секунд
bool IsMinutes(size_t minutes)
{
	return minutes >= 0 && minutes < 60;
}

//ввод времени пользователем
Time GetTimeFromUser(string name, string description, size_t id)
{
	size_t hour;
	size_t min;
	size_t sec;
	cout << name;
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
			cout << str;
		}
	}

	return Time(hour, min, sec, description, id);
}

//ввод с клавиатуры
void ReadFromKeyboard()
{
	vector<Time> times;
	vector<Pair> pairs;
	string input;
	Time come;
	Time leave;
	size_t idCustomer = 1;
	bool isEnd = false;
	while(isEnd == false)
	{
		cout << "Продолжить ввод ? Введите Y or N: ";
		cin >> input;
		//проверка условия остановки ввода
		if(input == "Y" || input == "y")
		{
			come = GetTimeFromUser("Введите время прихода:\n", "start", idCustomer);
			leave = GetTimeFromUser("Введите время ухода:\n", "end", idCustomer);
			//проверка корректности величины времени
			if(come > leave)
			{
				cout << "Время прихода больше, чем ухода!" << endl;
			}
			//добавление времени прихода, ухода
			else
			{
				times.push_back(come);
				times.push_back(leave);
				size_t size = times.size();
				pairs.push_back(Pair(times[size - 2], times[size - 1]));
				idCustomer++;
			}
		}
		//проверка условия остановки ввода
		else if(input == "N" || input == "n")
		{
			isEnd = true;
		}
		else
		{
			cout << "Введите Y or N!" << endl;
		}
	}
	if(times.empty() == false)
	{
		FindMaxInMuseum(times, pairs);
	}
}

//ввод и вывод меню
int GetModeFromConsole()
{
	string mode = "";
	cout << "\nВыберите пункт меню:" << endl;
	cout << "1. Чтение из файла" << endl;
	cout << "2. Ввод с клавиатуры" << endl;
	cout << "3. Выход" << endl;
	int exit = 0;
	while(exit != 1)
	{
		cin >> mode;
		//проверка ввода номера меню
		if((mode == "1") || (mode == "2") || (mode == "3"))
		{
			return atoi(mode.c_str());
		}
		else
		{
			cout << "Введите правильный режим" << endl;
		}
	}
}

//функция выбора меню
void Menu()
{
	int mode = GetModeFromConsole();
	try
	{
		switch(mode)
		{
			case 1:
			{
				ReadFromFile();
				Menu();
				break;
			}
			case 2:
			{
				ReadFromKeyboard();
				Menu();
				break;
			}
			case 3:
			{
				cout << "До свидания!" << endl;
				return;
			}

			default:
				cout << "Неизвестная команда!\n";
				break;
		}
	}
	catch(const char* message)
	{
		cout << message << '\n';
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	//выбор меню
	Menu();
	return 0;
}