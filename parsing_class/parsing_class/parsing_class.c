#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)


struct oskarActor
{
    int index;
    int year;
    int age;
    int Popularity;
    char name[100];
    char movie[100];
    struct oskarActor* next;
    struct oskarActor* prev;
};

struct oskarActor* head = NULL;
struct oskarActor* current;
struct oskarActor* tail = NULL;

void targil1();
void targil2();
void targil3();
void targil4();

int num;
int sum = 0;

char* token;

int main()
{
    char str[100] = "123*456*789";

    token = strtok(str, "*");

    while (token != NULL)
    {
        printf("%s ", token);
        token = strtok(NULL, "*");
    }

    targil1();

    targil2();

    targil3();

    targil4();
}

void targil1()
{

    char str[100] = "123, 456, 789, 1, 2, 3, 4, 5, 6, 7, 2000";

    token = strtok(str, ",");


    while (token != NULL)
    {
        num = atoi(token);
        sum = sum + num;
        token = strtok(NULL, ",");
    }

    printf("\n%d \n", sum);
}

void targil2()
{
    char str[100];
    printf("Please enter your full name with a space (for example: achiya tzuriel) \n");
    gets(str);

    token = strtok(str, " ");

    while (token != NULL)
    {
        printf("%s \n", token);
        token = strtok(NULL, " ");
    }
}

void targil3()
{
    char str[100];
    printf("Please enter your full name with a space (for example: tzuriel achiya) \n");
    gets(str);

    token = strtok(str, " ");

    while (token != NULL)
    {
        printf("%s \n", token);
        token = strtok(NULL, "\n");
    }

    //printf("\n");
}

void targil4()
{

    int index;
    int year;
    int age;
    char name[100];
    char movie[100];

    FILE* f;
    f = fopen("oscar_age_female.txt", "r");

    if (f == NULL)
    {
        // problem
        // error message
    }
    else
    {
        char str[500];

        fgets(str, 500, f);

        char* token = strtok(str, ",");

        while (fgets(str, 500, f) != NULL)
        {
            // קריאה מהקובץ והשמה של המספרים
            token = strtok(str, ",");
            index = atoi(token);

            token = strtok(NULL, ",");
            year = atoi(token);

            token = strtok(NULL, ",");
            age = atoi(token);

            token = strtok(NULL, ",");
            strcpy(name, token);

            token = strtok(NULL, "\n");
            strcpy(movie, token);

            token = strtok(NULL, "\n");

            printf("\nThe Oskar Goes to %s at %d Movie %s", name, year, movie);
        }

        fclose(f);
    }
}