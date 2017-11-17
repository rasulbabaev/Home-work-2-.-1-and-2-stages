#include <iostream>
#include <list>
#include <locale.h>
#include <string>
#include <strstream>

using namespace std;

struct LinkedList
{
	int value;
	LinkedList *next;
};

void Add(LinkedList *list, int element)
{
	while (list->next != nullptr)
		list = list->next;

	list->value = element;
	list->next = new LinkedList;
	list->next->next = nullptr;
}

void Add(LinkedList *list, const string& str)
{
	strstream stream;
	stream << str;

	while (!stream.eof())
	{
		int num;
		stream >> num;
		Add(list, num);
	}
}

void DeleteLinkedList(LinkedList *list)
{
	LinkedList *nextElement;
	
	do
	{
		nextElement = list->next;
		delete list;
	} while (nextElement);
}

LinkedList * InitializeLinkedList(int elements[], int count)
{
	LinkedList* list = new LinkedList;
	list->next = nullptr;

	for (int i = 0; i < count; ++i)
		Add(list, elements[i]);

	return list;
}

void FromCharToInt(int* dest, char *source[], int count)
{
	for (int i = 0; i < count; ++i)
		sscanf(source[i], "%d", dest + i);
}

void CoutElements(LinkedList *list)
{
	if (list->next == nullptr)
	{
		cout << "Ñïèñîê ïóñò" << endl;
		return;
	}

	cout << list->value;
	list = list->next;

	while (list->next)
	{
		cout << " -> " << list->value;
		list = list->next;
	}

	cout << endl;

	return;
}

bool ProcesMessages(LinkedList *list)
{
	cout << "Âûáåðèòå îäíó èç îïåðàöèé" << endl;
	cout << "1. Ðàñïå÷àòàòü ñïèñîê" << endl;
	cout << "2. Äîáàâèòü ýëåìåíòû â ñïèñîê" << endl;
	cout << "7. Çàâåðøèòü ðàáîòó ïðîãðàììû" << endl;

	char buff[200];
	cin >> buff;
	if (strlen(buff) != 1 || buff[0] > '7' || buff[0] < '1')
		return true;

	int commandNum = buff[0] - '0';
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string str;


	switch (commandNum)
	{
	case 1:
		CoutElements(list);
		return true;

	case 2:
		cout << "Ââåäèòå çíà÷åíèå ýåëåìåíòà" << endl;

		getline(cin, str);

		Add(list, str);

		return true;

	case 7:
		cout << "Âû óâåðåíû (y/n)" << endl;
		
		getline(cin, str);

		if (str == "y" || str == "Y" || str == "Yes" || str == "YES" || str == "yes")
		{
			cout << "Äî âñòðå÷è!" << endl;
			return false;
		}

		return true;

	default:
		return true;
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	int *elements = new int[argc - 1];
	FromCharToInt(elements, argv + 1, argc - 1);

	LinkedList *list = InitializeLinkedList(elements, argc - 1);
	delete[] elements;

	while (ProcesMessages(list));
}
