#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#define _USE_MATH_DEFINES

struct Incident
{
	char datatime[20];
	char discrip[50];
	char category[50];
	int priority;
	short status;
	char respons[30];
};

int StructReading(struct Incident* incident, int inc_count);
int FileWriting(struct Incident* incident, int inc_count);
int MakeIncidentInfo(struct Incident* incident);
int FindRespons(struct Incident* incident, int inc_count);
int FindCategory(struct Incident* incident, int inc_count);
int MassiveSort(struct Incident* arr, int inc_count);

//Îñíîâíàÿ ôóíêöèÿ
void main()
{
	FILE* file;
	system("chcp 1251");
	setlocale(LC_ALL, "RUS");
	struct Incident incident[100];
	int inc_count = 0;
	int ans1;
	do
	{
		printf("---------------------------------------------------------------------------------------\n");
		puts("Âûáåðèòå äåéñòâèå:");
		puts("1) Ñîçäàòü çàïèñü îá èíöèäåíòå.");
		puts("2) Âûâåñòè çàïèñàííûå â áóôåð èíöèäåíòû.");
		puts("3) Îòñîðòèðîâàòü ïî ïðèîðèòåòó (Âûñîêèé -> Íèçêèé).");
		puts("4) Çàïèñàòü ââåä¸ííûå èíôèäåíòû â ôàéë.");
		puts("5) Íàéòè èíöèäåíò(-û) ïî îòâåòñòâåííîìó.");
		puts("6) Íàéòè èíöèäåíò(-û) ïî êàòåãîðèè.");
		puts("7) Î÷èñòèòü ôàéë.");
		puts("8) Çàâåðøèòü ðàáîòó ïðîãðàììû.");
		printf("---------------------------------------------------------------------------------------\n");
		scanf("%d", &ans1);
		getchar();
		printf("---------------------------------------------------------------------------------------\n");
		switch (ans1)
		{
		case 1:
			if (inc_count < 100)
			{
				struct Incident newincident;
				MakeIncidentInfo(&newincident);
				incident[inc_count] = newincident;
				inc_count++;
			}
			else
			{
				printf("Ñëèøêîì ìíîãî çàïèñåé");
			}
			break;
		case 2:
			if (inc_count > 0)
			{
				StructReading(incident, inc_count);
			}
			else
			{
				printf("Çàïèñàííûå èíöèäåíòû îòñóòñòâóþò\n");
			}
			break;
		case 3:
			MassiveSort(incident, inc_count);
			printf("Èíöèäåíòû îòñîðòèðîâàíû\n");
			break;
		case 4:
			FileWriting(incident, inc_count);
			puts("Èíôîðìàöèÿ îá èíöèäåíòàõ çàïèñàíà â ôàéë.");
			break;
		case 5:
			printf("Ââåäèòå èìÿ íåîáõîäèìîãî îòâåòñòâåííîãî: ");
			FindRespons(incident, inc_count);
			break;
		case 6:
			printf("Ââåäèòå íåîáõîäèìóþ êàòåãîðèþ: ");
			FindCategory(incident, inc_count);
			break;
		case 7:
			file = fopen("data.txt", "w");
			inc_count = 0;
			printf("Ôàéë î÷èùåí\n");
			break;
		default:
			if (ans1 != 8)
			{
				printf("Íåïðàâèëüíîå çíà÷åíèå\n");
			}
			break;
		}
	} while (ans1 != 8);
}

//Ôóíêöèÿ çàïèñè â ôàéë
int FileWriting(struct Incident* incident, int inc_count)
{
	FILE* file = fopen("data.txt", "w");
	if (file == NULL)
	{
		printf("Ôàéë íå ñóùåñòâóþò");
		return;
	}
	for (int i = 0; i < inc_count; ++i)
	{
		fprintf(file, "%s%s%s%d\n%i\n%s\n", incident[i].datatime, incident[i].discrip, incident[i].category, incident[i].priority, incident[i].status, incident[i].respons);
	}
	fclose(file);
	return 1;
}

//Ôóíêöèÿ ñîçäàíèÿ èíöèäåíòà
int MakeIncidentInfo(struct Incident* incident)
{
	printf("Ââåäèòå äàòó è âðåìÿ èíöèäåíòà (dd.mm.yyy/hh:mm:ss): ");
	fgets(incident->datatime, sizeof(incident->datatime), stdin);
	printf("Ââåäèòå îïèñàíèå èíöèäåíòà: ");
	fgets(incident->discrip, sizeof(incident->discrip), stdin);
	printf("Ââåäèòå êàòåãîðèþ èíöèäåíòà (Óâåäîìëåíèå î êîìïüþòåðíîì èíöèäåíòå/Óâåäîìëåíèå î êîìïüþòåðíîé àòàêå/Óâåäîìëåíèå î íàëè÷èè óÿçâèìîñòè): ");
	fgets(incident->category, sizeof(incident->category), stdin);
	printf("Ââåäèòå ïðèîðèòåò èíöèäåíòà (1 - Íèçêèé, 2 - Ñðåäíèé, 3 - Âûñîêèé): ");
	scanf("%d", &incident->priority);
	getchar();
	printf("Ââåäèòå ñòàòóñ èíöèäåíòà (1 - Íà ðàññìîòðåíèè, 2 - Ðàññìîòðåíî, 3 - Ïðèíÿòû ìåðû): ");
	scanf("%d", &incident->status);
	getchar();
	printf("Ââåäèòå îòâåòñòâåííîãî: ");
	fgets(incident->respons, sizeof(incident->respons), stdin);
	printf("--------------------------------------------------------------------------------\n");
	return 1;
}

//Ôóíêöèÿ âûâîäà â êîíñîëü èíöèäåíòîâ
int StructReading(struct Incident* incident, int inc_count)
{
	for (int i = 0; i < inc_count; i++)
	{
		printf("%s%s%s%d\n%i\n%s\n", incident[i].datatime, incident[i].discrip, incident[i].category, incident[i].priority, incident[i].status, incident[i].respons);
	}

	return 1;
}

//Ôóíêöèÿ ïîèñêà èíöèäåíòà ïî îòâåòñòâåííîìó
int FindRespons(struct Incident* incident, int inc_count)
{
	char res[30];
	fgets(res, sizeof(res), stdin);
	for (int i = 0; i < inc_count; i++)
	{
		if (strcmp(incident[i].respons, res) == 0)
		{
			printf("%s%s%s%d\n%i\n%s\n", incident[i].datatime, incident[i].discrip, incident[i].category, incident[i].priority, incident[i].status, incident[i].respons);
		}
	}
	return 1;
}

//Ôóíêöèÿ ïîèñêà èíöèäåíòà ïî êàòåãîðèè
int FindCategory(struct Incident* incident, int inc_count)
{
	char cat[50];
	fgets(cat, sizeof(cat), stdin);
	for (int i = 0; i < inc_count; i++)
	{
		if (strcmp(incident[i].category, cat) == 0)
		{
			printf("%s%s%s%d\n%i\n%s\n", incident[i].datatime, incident[i].discrip, incident[i].category, incident[i].priority, incident[i].status, incident[i].respons);
		}
	}
	return 1;
}

//Ñîðòèðîâêà ìàññèâà ïî ïðèîðèòåòó (Âûñîêèé -> Íèçêèé)
int MassiveSort(struct Incident* arr, int inc_count)
{
	struct Incident temp;
	for (int i = 0; i < inc_count - 1; i++)
	{
		for (int j = 0; j < inc_count - i - 1; j++)
		{
			if (arr[j].priority < arr[j + 1].priority)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return 1;
}
