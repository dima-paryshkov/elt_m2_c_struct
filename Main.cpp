#include <stdio.h>       
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int countAccount = 1;

struct date
{
	int dd, mm, yy;

	date() {}	

	date(int day = 0, int mounth = 0, int year = 0)
	{
		dd = day;
		mm = mounth;
		yy = year;
	}

	int print(FILE* fd = stdout)
	{
		if (dd != 0 && mm != 0 && yy != 0)
			return fprintf(fd, "%2d.%2d.%2d", dd, mm, yy);
	}

	int set(int day = 1, int mounth = 1, int year = 2022)
	{
		if (day > 0 && day < 32)
			dd = day;
		else
			return 1;

		if (mounth >= 1 && mounth <= 12)
			mm = mounth;
		else
			return 2;

		if (year >= 1970 and year < 2050)
			yy = year;
		else
			return 3;

		return 0;
	}

	int getDay()
	{
		return dd;
	}

	int getMounth()
	{
		return mm;
	}

	int getYear()
	{
		return yy;
	}

	int setDay(int day)
	{
		if (day > 0 && day < 32)
			dd = day;
		else
			return 1;
		return 0;
	}

	int setMounth(int mounth)
	{
		if (mounth >= 1 && mounth <= 12)
			mm = mounth;
		else
			return 1;
		return 0;
	}

	int setYear(int year)
	{
		if (year >= 1970 and year < 2050)
			yy = year;
		else
			return 1;
		return 0;
	}
};

struct account
{
	char* name;
	int numberAccount;
	float amount;

	account()
	{
		numberAccount = countAccount;
		countAccount++;
	}

	account(char* curName, float curAmount = 0)
	{
		int tmpLen = strlen(curName);
		if (tmpLen <= 0)
		{
			name = new char[1];
			name[0] = '\0';
		}
		else
		{
			name = new char[tmpLen];
			strcpy(name, curName);
		}
		amount = curAmount;
	}

	void set(char* curName, float curAmount = 0)
	{
		int tmpLen = strlen(curName);
		if (tmpLen != 0)
		{
			delete name;
			name = new char[tmpLen];
			strcpy(name, curName);

			amount = curAmount;
		}
	}

	void setAmount(float curAmount)
	{
		amount = curAmount;
	}

	int getAmount()
	{
		return amount;
	}

	int getAccount()
	{
		return numberAccount;
	}

	char* getName()
	{
		return name;
	}
};

struct listAcc
{
	account acc;
	listAcc* next;

	listAcc()
	{
		next = NULL;
	}
};

void initListAcc(listAcc* next)
{
	next = NULL;
}

void addListAcc(listAcc* list, account curAcc)
{
	listAcc* tmp = new listAcc;
	tmp->next = list;
	tmp->acc = curAcc;
	list = tmp;
}

void rmListAcc(listAcc* list, listAcc* item)
{
	listAcc* tmp = list;
	while (tmp->next != item && tmp->next != NULL)
		tmp = tmp->next;
	listAcc* tmpS = tmp->next;
	tmp->next = tmp->next->next;
	delete tmpS;
}

void enterAccount(listAcc* list, FILE* fd = stdin)
{
	account* acc = new account;
	if (fd == stdin)
	{
		fprintf(stdout, "Write name: ");
		fscanf_s(fd, "%s", &acc->name);

		fprintf(stdout, "Write amount: ");
		fscanf_s(fd, "%f", &acc->amount);

		fprintf(stdout, "For this account was created id(number account): %d\n", acc->numberAccount);
	}
	else
	{
		countAccount--;
		while (feof(fd))
		{
			fscanf_s(fd, "%s%d%d", &acc->name, &acc->numberAccount, &acc->amount);
			addListAcc(list, *acc);
		}
	}
}

void print(listAcc* list, FILE* fd = stdout)
{
	if (fd = stdout)
		fprintf(fd, "Name\t\tAccount\tAmount\n");

	listAcc* item = list;
	while (item != NULL)
	{
		fprintf(fd, "%20s\t\t%d\t%.2f\n", item->acc.name, item->acc.numberAccount, item->acc.amount);
		item = item->next;
	}
}

int main()
{

}