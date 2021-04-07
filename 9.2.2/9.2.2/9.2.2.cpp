#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;

enum Specialnist { KN, ME, IF, FI, TN }; // перелік спеціальностей  
string specialnistList[] = { "комп науки", "мат і економ", "інформ", "фіз і інформ", "труд навч" }; // масив назв спеціальностей
struct Student
{
	string prizv;
	int kurs;
	Specialnist spec;
	int fiz;
	int mat;
	double average;
	union
	{
		int prog;
		int chis_metod;
		int pedagog;
	};
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);

int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	int N;
	cout << "Введіть кількість студентів: "; cin >> N;
	Student* p = new Student[N]; // створення посилання на об'єкт типу Student
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - Сортування" << endl;
		cout << " [4] - Індексне сортування та його вивід" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			cout << "Таблиця була відсортована!";
			break;
		case 4:
			PrintIndexSorted(p, IndexSort(p, N), N);
		case 0:
			break;
		default:
			cout << "Неправильне значення" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Cтудент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
		cout << "прізвище: "; getline(cin, p[i].prizv);
		cout << "курс: "; cin >> p[i].kurs;
		cout << "оцінка з фізики: "; cin >> p[i].fiz;
		cout << "оцінка з математики: "; cin >> p[i].mat;
		cout << "cпеціальність (0 - комп. науки, 1 - мат і економ, 2 - інформ, 3 - фіз і інформ, 4 - труд. навч): ";  cin >> spec;
		if (spec > 4) {
			cout << "неправильне значення, вибрано 0 (комп. науки)" << endl;
			spec = 0;
		}

		p[i].spec = (Specialnist)spec; // присвоєння спеціальності, введенної користувачем через перелік
		switch (p[i].spec)
		{
		case KN:
			cout << "оцінка з програмування: "; cin >> p[i].prog;
			p[i].average = (p[i].mat + p[i].fiz + p[i].prog) / 3.0;
			break;
		case ME:
			cout << "оцінка з педагогіки: "; cin >> p[i].pedagog;
			p[i].average = (p[i].mat + p[i].fiz + p[i].pedagog) / 3.0;
			break;
		case IF:
			cout << "оцінка з чисельних методів: "; cin >> p[i].chis_metod;
			p[i].average = (p[i].mat + p[i].fiz + p[i].chis_metod) / 3.0;
			break;
		case FI:
			cout << "оцінка з педагогіки: "; cin >> p[i].pedagog;
			p[i].average = (p[i].mat + p[i].fiz + p[i].pedagog) / 3.0;
			break;
		case TN:
			cout << "оцінка з педагогіки: "; cin >> p[i].pedagog;
			p[i].average = (p[i].mat + p[i].fiz + p[i].pedagog) / 3.0;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "============================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Cпеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[i].prizv
			<< "| " << setw(2) << right << p[i].kurs << "  "
			<< " | " << setw(14) << left << specialnistList[p[i].spec]
			<< setw(4) << "| " << setw(3) << left << p[i].fiz << "  "
			<< setw(6) << "| " << setw(6) << left << p[i].mat << " ";
		switch (p[i].spec)
		{
		case KN:
			cout << setw(8) << "| " << setw(7) << left << p[i].prog << setw(19)
				<< " | " << setw(12) << left
				<< "| " << left << " |" << endl;
			break;
		case ME:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << p[i].pedagog << " |" << endl;
			break;
		case IF:
			cout << "" << setw(15) << "| " << setw(9) << " |" << " "
				<< setw(8) << p[i].chis_metod << " |" << " "
				<< setw(10) << "" << " |" << endl;
			break;
		case FI:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << p[i].pedagog << " |" << endl;
			break;
		case TN:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << p[i].pedagog << " |" << endl;
			break;
		}
	}
	cout << "============================================================================================================"
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) {
		for (int i1 = 0; i1 < N - i0 - 1; i1++) {
			if ((p[i1].average < p[i1+1].average)
				||
				(p[i1].average = p[i1 + 1].average) && 
				p[i1].kurs == p[i1 + 1].kurs
				||
				(p[i1].average = p[i1 + 1].average &&
					p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
		}
	}
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створення додаткового індексного масиву
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнення його початковими даними
	int i, j, value; // сортування масиву індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].average < p[value].average)
				||
				(p[I[j]].average == p[value].average &&
					p[I[j]].kurs > p[value].kurs)
				||
				(p[I[j]].average == p[value].average &&
					p[I[j]].kurs == p[value].kurs &&
					p[I[j]].prizv < p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "============================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Cпеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[I[i]].prizv
			<< "| " << setw(2) << right << p[I[i]].kurs << "  "
			<< " | " << setw(14) << left << specialnistList[p[I[i]].spec]
			<< setw(4) << "| " << setw(3) << left << p[I[i]].fiz << "  "
			<< setw(6) << "| " << setw(6) << left << p[I[i]].mat << " ";
		switch (p[I[i]].spec)
		{
		case KN:
			cout << setw(8) << "| " << setw(7) << left << p[I[i]].prog << setw(19)
				<< " | " << setw(12) << left
				<< "| " << left << " |" << endl;
			break;
		case ME:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << p[I[i]].pedagog << " |" << endl;
			break;
		case IF:
			cout << "" << setw(15) << "| " << setw(9) << " |" << " "
				<< setw(8) << p[I[i]].chis_metod << " |" << " "
				<< setw(10) << "" << " |" << endl;
			break;
		case FI:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << p[I[i]].pedagog << " |" << endl;
			break;
		case TN:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << p[I[i]].pedagog << " |" << endl;
			break;
		}
	}
	cout << "============================================================================================================"
		<< endl;
	cout << endl;
}