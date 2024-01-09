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

int FileWriting(struct Incident* incident, int inc_count);
int MakeIncidentInfo(struct Incident* incident);
struct Incident* FindRespons(struct Incident* incident, int inc_count, char* res);
struct Incident* FindCategory(struct Incident* incident, int inc_count, char* cat);
int MassiveSort(struct Incident* arr, int inc_count);

//Основная функция
void main()
{
	FILE* file;
	system("chcp 1251");
	setlocale(LC_ALL, "RUS");
	struct Incident incident[100];
	int inc_count = 0;
	int ans1;
	struct Incident Temp;
	do
	{
		printf("---------------------------------------------------------------------------------------\n");
		puts("Выберите действие:");
		puts("1) Создать запись об инциденте.");
		puts("2) Вывести записанные в буфер инциденты.");
		puts("3) Отсортировать по приоритету (Высокий -> Низкий).");
		puts("4) Записать введённые инфиденты в файл.");
		puts("5) Найти инцидент(-ы) по ответственному.");
		puts("6) Найти инцидент(-ы) по категории.");
		puts("7) Очистить файл.");
		puts("8) Завершить работу программы.");
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
				printf("Слишком много записей");
			}
			break;
		case 2:
			if (inc_count > 0)
			{
				for (int i = 0; i < inc_count; i++)
				{
					printf("%s%s%s%d\n%i\n%s\n", incident[i].datatime, incident[i].discrip, incident[i].category, incident[i].priority, incident[i].status, incident[i].respons);
				}
			}
			else
			{
				printf("Записанные инциденты отсутствуют\n");
			}
			break;
		case 3:
			MassiveSort(incident, inc_count);
			printf("Инциденты отсортированы\n");
			break;
		case 4:
			FileWriting(incident, inc_count);
			puts("Информация об инцидентах записана в файл.");
			break;
		case 5:
			printf("Введите имя необходимого ответственного: ");
			char res[30];
			fgets(res, sizeof(res), stdin);
			for (int j = 0; j < inc_count; j++)
			{
				Temp = FindRespons(incident, inc_count, res)[j];
				if (Temp.priority > 0)
				{
					printf("%s%s%s%d\n%i\n%s\n", Temp.datatime, Temp.discrip, Temp.category, Temp.priority, Temp.status, Temp.respons);
				}
			}
			break;
		case 6:
			printf("Введите необходимую категорию: ");
			char cat[50];
			fgets(cat, sizeof(cat), stdin);
			for (int j = 0; j < inc_count; j++)
			{
				Temp = FindCategory(incident, inc_count, cat)[j];
				if (Temp.priority > 0)
				{
					printf("%s%s%s%d\n%i\n%s\n", Temp.datatime, Temp.discrip, Temp.category, Temp.priority, Temp.status, Temp.respons);
				}
			}
			break;
		case 7:
			file = fopen("data.txt", "w");
			inc_count = 0;
			printf("Файл очищен\n");
			break;
		default:
			if (ans1 != 8)
			{
				printf("Неправильное значение\n");
			}
			break;
		}
	} while (ans1 != 8);
}

//Функция записи в файл
int FileWriting(struct Incident* incident, int inc_count)
{
	FILE* file = fopen("data.txt", "w");
	if (file == NULL)
	{
		printf("Файл не существует");
		return;
	}
	else
	{
		for (int i = 0; i < inc_count; ++i)
		{
			fprintf(file, "%s%s%s%d\n%i\n%s\n", incident[i].datatime, incident[i].discrip, incident[i].category, incident[i].priority, incident[i].status, incident[i].respons);
		}
		fclose(file);
		return 1;
	}
}

//Функция создания инцидента
int MakeIncidentInfo(struct Incident* incident)
{
	printf("Введите дату и время инцидента (dd.mm.yyy/hh:mm:ss): ");
	fgets(incident->datatime, sizeof(incident->datatime), stdin);
	printf("Введите описание инцидента: ");
	fgets(incident->discrip, sizeof(incident->discrip), stdin);
	printf("Введите категорию инцидента (Уведомление о компьютерном инциденте/Уведомление о компьютерной атаке/Уведомление о наличии уязвимости): ");
	fgets(incident->category, sizeof(incident->category), stdin);
	printf("Введите приоритет инцидента (1 - Низкий, 2 - Средний, 3 - Высокий): ");
	scanf("%d", &incident->priority);
	getchar();
	printf("Введите статус инцидента (1 - На рассмотрении, 2 - Рассмотрено, 3 - Приняты меры): ");
	scanf("%d", &incident->status);
	getchar();
	printf("Введите ответственного: ");
	fgets(incident->respons, sizeof(incident->respons), stdin);
	printf("--------------------------------------------------------------------------------\n");
	return 1;
}


//Функция поиска инцидента по ответственному
struct Incident* FindRespons(struct Incident* incident, int inc_count, char* res)
{
	struct Incident inc_respons[100];
	int res_count = 0;
	struct Incident blank = { "", "", "", 0, 0, "" };
	for (int i = 0; i < inc_count; i++)
	{
		if (strcmp(incident[i].respons, res) == 0)
		{
			inc_respons[res_count] = incident[i];
			res_count++;
		}
		else
		{
			inc_respons[res_count] = blank;
		}
	}
	return inc_respons;
}

//Функция поиска инцидента по категории
struct Incident* FindCategory(struct Incident* incident, int inc_count, char* cat)
{
	struct Incident inc_category[100];
	int cat_count = 0;
	struct Incident blank = { "", "", "", 0, 0, "" };
	for (int i = 0; i < inc_count; i++)
	{
		if (strcmp(incident[i].category, cat) == 0)
		{
			inc_category[cat_count] = incident[i];
			cat_count++;
		}
		else
		{
			inc_category[cat_count] = blank;
		}
	}
	return inc_category;
}

//Сортировка массива по приоритету (Высокий -> Низкий)
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
