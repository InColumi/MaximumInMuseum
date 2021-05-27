#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//����� ��� ������ � ��������
class Time
{
private:
	size_t _hour;
	size_t _minute;
	size_t _second;
	string _description; // start or end

	//�������� ������������ �����
	//��������� ���
	//���������� ���.��������
	bool IsCorrectHours(size_t hour)
	{
		return hour >= 0 && hour < 24;
	}

	//�������� ������������ �����
	//��������� ������
	//���������� ���.��������
	bool IsCorrectMinutesOrSeconds(size_t time)
	{
		return time >= 0 && time < 60;
	}

	//���������� ���� ��� ��� ���������� � �������
	//��������� ��������
	void ShowZeroIfMoreThenNine(size_t value)
	{
		if(value <= 9)
		{
			cout << '0';
		}
	}

public:
	Time(): _hour(size_t()), _minute(size_t()), _second(size_t())
	{}

	Time(size_t hour, size_t minute, size_t second, string description)
	{
		//�������� ������������ �������
		if(IsCorrectHours(hour) && IsCorrectMinutesOrSeconds(minute) && IsCorrectMinutesOrSeconds(second))
		{
			_hour = hour;
			_minute = minute;
			_second = second;
			_description = description;
		}
		else
		{
			throw "�������� � ��������� Time, ��������� ������ ������� ����������! ������ ������ 00:00:00\n";
		}
	}

	//���������� ����������
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
		//�������� ������������ �����, �����, ������
		return (_hour == t._hour) ? (_minute == t._minute) ? _second > t._second : _minute > t._minute : _hour > t._hour;
	}

	bool operator < (Time t)
	{
		//�������� ������������ �����, �����, ������
		return (_hour == t._hour) ? (_minute == t._minute) ? _second < t._second : _minute < t._minute : _hour < t._hour;
	}

	bool operator <= (Time t)
	{
		//�������� ������������ �����, �����, ������
		return (_hour == t._hour) ? (_minute == t._minute) ? _second <= t._second : _minute < t._minute : _hour < t._hour;
	}

	bool operator >= (Time t)
	{
		//�������� ������������ �����, �����, ������
		return (_hour == t._hour) ? (_minute == t._minute) ? _second >= t._second : _minute > t._minute : _hour > t._hour;
	}

	//����� �������
	void ShowInfo()
	{
		//���������� ����, ���� ��� ���
		ShowZeroIfMoreThenNine(_hour);
		cout << _hour;
		cout << ":";
		ShowZeroIfMoreThenNine(_minute);
		cout << _minute;
		cout << ":";
		ShowZeroIfMoreThenNine(_second);
		cout << _second << endl;
	}
	//��������� �������
	size_t GetHour()
	{
		return _hour;
	}

	size_t GetMinutes()
	{
		return _minute;
	}

	string GetDescription()
	{
		return _description;
	}
};

//�������������� string � size_t
//��������� ������ � �����
//���������� ���.��������
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

//�������� ������������ ���������� �����
//��������� ��� ����� � ����������
//���������� ���.�������� ��������
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
		std::cout << "Wrong extention" << std::endl;
	}

	return true;
}

//���������� ������ �������
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

//��������� ������ �� ��������
//��������� �����
//���������� ����������� �����: ����, ������, �������
Time StringtoTime(string timeInStr, string description)
{
	vector<string> hourMinuteSecond;
	hourMinuteSecond = Split(timeInStr, ':');
	//�������������� �������� ������������ ������� 
	if(hourMinuteSecond.size() != 3)
	{
		throw "��������� ������ � �����. ������ ������ 00:00:00\n";
	}

	vector<size_t> time;
	size_t number;
	for(size_t i = 0; i < hourMinuteSecond.size(); i++)
	{
		//�������� ������������ �������
		if(TryStringTosize_t(hourMinuteSecond[i], number))
		{
			time.push_back(number);
		}
		else
		{
			throw "��������� ������ � �����. ������ ������ 00:00:00\n";
		}
	}
	return Time(time[0], time[1], time[2], description);
}

//������ � ������
//��������� ������ �����
//���������� ������ ������� �������,�����
vector<Time> ParseFromFile(ifstream& outFile)
{
	string line;
	vector<Time> times;
	string timeInStr = "";
	Time come;
	Time leave;
	//������ ����� �� �����
	while(getline(outFile, line))
	{
		for(size_t i = 0; i < line.size(); i++)
		{
			if(line[i] == ' ')
			{
				come = StringtoTime(timeInStr, "start");
				timeInStr.clear();
			}
			else if((i + 1) == line.size())
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
		//�������� ������������ ������� �������,�����
		if(come > leave)
		{
			throw "����� ������� �� ����� ���� ������ ������� �����!\n";
		}
		//���������� ������� �������,�����
		else
		{
			times.push_back(come);
			times.push_back(leave);
		}
	}
	outFile.close();
	return times;
}

//���������� ������� ��� ���������
//��������� ������ �������
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
				// ������ �������� �������
				temp = times[j];
				times[j] = times[j + 1];
				times[j + 1] = temp;
			}
		}
	}
}

//����� ��������� � ����.������ �����
void FindMaxInMuseum(vector<Time>& times)
{
	Sort(times);
	int countCustomers = 0;
	int maxCounCustomers = 0;
	vector<Time> interval;
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
			throw "� �������� �������� start ��� end!\n";
		}

		//���������� ������ ����� ����.�����
		if(countCustomers > maxCounCustomers)
		{
			interval.clear();
			interval.push_back(times[i]);
			interval.push_back(times[i + 1]);
			maxCounCustomers = countCustomers;
		}
	}
	cout << "�������� � ������������ ����������� �����������\n";
	//����� ��������� ������� � ����.������ �����
	for(size_t i = 0; i < interval.size(); i++)
	{
		interval[i].ShowInfo();
	}

}

//������ �� �����
void ReadFromFile()
{
	string input;
	bool isCorrect = false;
	ifstream outFile;
	while(isCorrect == false)
	{
		cout << "������� ��� ����� � ���������� txt" << endl;
		cout << "������ ������� ����� � �����������: input.txt" << endl;
		cin >> input;
		//�������� ���������� �����
		if(IsCorrectExtention(input))
		{
			outFile.open(input);
			//�������� ������� �����
			if(outFile.is_open())
			{
				//������ �����
				//����� ��������� � ����.������
				try
				{
					vector<Time> times = ParseFromFile(outFile);
					FindMaxInMuseum(times);
				}
				catch(const char* str)
				{
					cout << str;
				}
				isCorrect = true;
			}
			else
			{
				cout << "������ ����� �� ���������!" << endl;
			}
		}
		else
		{
			cout << "�������� ����������!" << endl;
		}
	}
}

//�������� ������������ ����� ������
//��������� ������, ����� � ���.������������� �����
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
		throw "������� ���������� ������!\n";
	}
}

//�������� �����
bool IsHours(size_t hour)
{
	return hour >= 0 && hour < 24;
}

//�������� �����, ������
bool IsMinutes(size_t minutes)
{
	return minutes >= 0 && minutes < 60;
}

//���� ������� �������������
Time GetTimeFromUser(string name, string description)
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
			TryParseToSize_t("������� ����: ", hour, IsHours);
			TryParseToSize_t("������� ������: ", min, IsMinutes);
			TryParseToSize_t("������� �������: ", sec, IsMinutes);
			isCorrect = true;
		}
		catch(const char* str)
		{
			cout << str;
		}
	}

	return Time(hour, min, sec, description);
}

//���� � ����������
void ReadFromKeyboard()
{
	vector<Time> times;
	string input;
	Time come;
	Time leave;
	bool isEnd = false;
	while(isEnd == false)
	{
		cout << "���������� ���� ? ������� Y or N: ";
		cin >> input;
		//�������� ������� ��������� �����
		if(input == "Y" || input == "y")
		{
			come = GetTimeFromUser("������� ����� �������:\n", "start");
			leave = GetTimeFromUser("������� ����� �����:\n", "end");
			//�������� ������������ �������� �������
			if(come > leave)
			{
				cout << "����� ������� ������, ��� �����!" << endl;
			}
			//���������� ������� �������, �����
			else
			{
				times.push_back(come);
				times.push_back(leave);
			}
		}

		//�������� ������� ��������� �����
		else if(input == "N" || input == "n")
		{
			isEnd = true;
		}
		else
		{
			cout << "������� Y or N!" << endl;
		}
	}
	if(times.empty() == false)
	{
		FindMaxInMuseum(times);
	}
}

//���� � ����� ����
int GetModeFromConsole()
{
	string mode = "";
	cout << "\n�������� ����� ����:" << endl;
	cout << "1. ������ �� �����" << endl;
	cout << "2. ���� � ����������" << endl;
	cout << "3. �����" << endl;
	int exit = 0;
	while(exit != 1)
	{
		cin >> mode;
		//�������� ����� ������ ����
		if((mode == "1") || (mode == "2") || (mode == "3"))
		{
			return atoi(mode.c_str());
		}
		else
		{
			cout << "������� ���������� �����" << endl;
		}
	}
}

//������� ������ ����
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
				cout << "�� ��������!" << endl;
				return;
			}

			default:
				cout << "����������� �������!\n";
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
	//����� ����
	Menu();
	return 0;
}