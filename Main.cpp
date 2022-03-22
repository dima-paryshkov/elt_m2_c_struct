#include <stdio.h>       
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int countAccount = 1;

struct date
{
	int dd, mm, yy;

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

		numberAccount = countAccount;
		countAccount++;
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