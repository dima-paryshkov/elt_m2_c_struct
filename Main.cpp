#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>       
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int countAccount = 1000;

const int nameLen = 30;

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
	char name[nameLen];
	int numberAccount;
	float amount;
	date lastDate;

	account()
	{
		numberAccount = countAccount;
		countAccount++;
		amount = 0;
	}

	void set(char* curName, float curAmount = 0)
	{
		int tmpLen = strlen(curName);
		if (tmpLen != 0)
		{
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
		next = NULL;\

	}
};

listAcc* initListAcc()
{
	listAcc* item = new listAcc;
	item->next = NULL;
	return item;
}

listAcc* addListAcc(listAcc* list, account curAcc)
{
	listAcc* tmp = new listAcc;
	tmp->next = list;
	tmp->acc = curAcc;
	return tmp;
}

listAcc* rmListAcc(listAcc* list, listAcc* item)
{
	listAcc* tmp = list;
	if (tmp == item)
	{
		list = list->next;
		delete tmp;
	}
	else
	{
		while (tmp->next != item && tmp->next->next != NULL)
			tmp = tmp->next;
		listAcc* tmpS = tmp->next;
		tmp->next = tmp->next->next;
		delete tmpS;
	}
	return list;
}

listAcc* enterAccount(listAcc* list, FILE* fd = stdin)
{
	account* acc = new account;
	if (fd == stdin)
	{
		fprintf(stdout, "Write name: ");
		fscanf(fd, "%s", &acc->name);

		fprintf(stdout, "Write amount: ");
		fscanf(fd, "%f", &acc->amount);

		fprintf(stdout, "For this account was created id(number account): %d\n", acc->numberAccount);

		fprintf(stdout, "Write data in format: dd mm yyyy: ");
		fscanf(fd, "%d%d%d", &acc->lastDate.dd, &acc->lastDate.mm, &acc->lastDate.yy);
		list = addListAcc(list, *acc);
	}
	else
	{
		if (!feof(fd))
			fscanf(fd, "%d", &countAccount);
		while (!feof(fd))
		{
			fscanf(fd, "%s%d%f%d%d%d", &acc->name, &acc->numberAccount, &acc->amount, &acc->lastDate.dd, &acc->lastDate.mm, &acc->lastDate.yy);
			if (!feof(fd)) list = addListAcc(list, *acc);
		}
	}
	return list;
}

listAcc* print(listAcc* list, FILE* fd = stdout)
{
	listAcc* item = list;

	if (fd == stdout)
	{
		fprintf(fd, "Name\t\tAccount\tAmount\t date\n");
		while (item->next != NULL)
		{
			fprintf(fd, "%s\t\t%d\t%.2f\t%d.%d.%d\n", item->acc.name, item->acc.numberAccount, item->acc.amount, item->acc.lastDate.dd, item->acc.lastDate.mm, item->acc.lastDate.yy);
			item = item->next;
		}
		
	}
	else
	{
		fprintf(fd, "%d\n", countAccount);
		while (item->next != NULL)
		{
			fprintf(fd, "%s %d %f %d %d %d\n", item->acc.name, item->acc.numberAccount, item->acc.amount, item->acc.lastDate.dd, item->acc.lastDate.mm, item->acc.lastDate.yy);
			item = item->next;
		}
	}

	return list;
}

listAcc* sort(listAcc* list, int option)
{
	listAcc* result = initListAcc();
	listAcc* tmp = list;
	listAcc* max;

	while (list->next != NULL)
	{
		tmp = list;
		max = list;
		while (tmp->next != NULL)
		{
			switch (option)
			{
			case 1:
				if (max->acc.amount < tmp->acc.amount)
					max = tmp;
				break;

			case 2:
				if (max->acc.numberAccount < tmp->acc.numberAccount)
					max = tmp;
				break;

			case 3:
				if (strcmp(tmp->acc.name, max->acc.name) > 0)
					max = tmp;
				break;

			case 4:
				if (max->acc.lastDate.yy < tmp->acc.lastDate.yy)
					max = tmp;
				else 
					if (max->acc.lastDate.yy == tmp->acc.lastDate.yy)
						if (max->acc.lastDate.mm < tmp->acc.lastDate.mm)
							max = tmp;
						else 
							if (max->acc.lastDate.mm == tmp->acc.lastDate.mm)
								if (max->acc.lastDate.dd <= tmp->acc.lastDate.dd)
									max = tmp;
				break;

			}
			tmp = tmp->next;
		}

		result = addListAcc(result, max->acc);
		list = rmListAcc(list, max);
	}
	return result;
}

int main()
{
	listAcc* list;
	list = initListAcc();

	FILE* fd;
	fd = fopen("data.txt", "r");
	if (fd == NULL)
		perror("Couldn't open file with data\n");
	list = enterAccount(list, fd);
	fclose(fd);

	fprintf(stdout, "Data load from file.\n");
	int decision;
	int flag = 1;
	while (flag)
	{
		fprintf(stdout, " 1. Add new account\n 2. Print all account\n 3. Sort table\n 4. Search account\n 5. Delete account\n 6. Edir account\n 7. Calculate and print sum all account\n 8. Exit\n");
		fscanf(stdin, "%d", &decision);

		switch (decision)
		{
		case 1: 
			list = enterAccount(list);
			break;

		case 2:
			print(list);
			break;

		case 3:
			fprintf(stdout, "Select options for sorting\n 1. Name\n 2. Amount\n 3. Number of account\n 4. Date\n");
			fscanf(stdin, "%d", &decision);
			switch (decision)
			{
			case 1:
				list = sort(list, 3);
				break;

			case 2:
				list = sort(list, 1);
				break;

			case 3:
				list = sort(list, 2);
				break;

			case 4:
				list = sort(list, 4);
				break;

			default:
				fprintf(stdout, "Incorect point of menu! Try again.\n");
				break;
			}
			print(list);
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;

		case 7:
			break;

		case 8:
			flag = 0;
			break;

		default:
			fprintf(stdout, "Incorect point of menu! Try again.\n");
			break;
		}
		fprintf(stdout, "\n");
	}

	fd = fopen("data.txt", "w");
	if (fd == NULL)
		perror("Couldn't open file with data\n");
	else 
		print(list, fd);
	fprintf(stdout, "Data save in file.\n");
	fclose(fd);

}