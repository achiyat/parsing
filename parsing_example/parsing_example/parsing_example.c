#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)
#define file_name "oskar Actor.bin"
#define Version 1;

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

struct oskarActor_header
{
    int version;
    int itemCount;
    char reserved[1000];
};
struct oskarActor_header header;

struct oskarActor* head = NULL;
struct oskarActor* current;
struct oskarActor* tail = NULL;
struct oskarActor* currentLoad;

void loadFile();
void Add(int index, int year, int age, char movie[100], char name[100]);
void PrintList();
void FreeList();
int RandomNum(int start, int end, int range);
void PrintAllMoviesForYear(int Year);
void GetMovieByIndex(int Index);
int GetItemCount();
void UpdatePopularity(int inedx);
void Random();
void Save();
void LoadList();

int num;
int sum = 0;
int popularNum = 0;
char popularName[100];

char* token;

int main()
{
    time_t t = time(&t);
    srand(t);

    // קריאה מהקובץ והשמה לרשימה המקושרת
    loadFile();

    // הדפסת הרשימה המקושרת
    PrintList();

    // פרטי השחקן שזכה באוסקר באותה שנה
    num = RandomNum(1928, 2016, 10000);
    PrintAllMoviesForYear(num);

    // פרטי הרשימה לפי אינדקס
    printf("\n");
    num = RandomNum(1, 89, 100);
    GetMovieByIndex(num);

    // כמות האייטים שיש בתוכנית
    GetItemCount();

    // השמת נתוני פופולריות
    for (int i = 1; i <= 3; i++)
    {
        Random();
    }

    printf("\nThe most popular actor: %s!\n", popularName);

    // שמירה לקובץ
    Save();
    // קריאה מהקובץ וטעינת הנתונים
    LoadList();
    // שחרור זיכרון
    FreeList();

    return 0;
}

void loadFile()
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
        char str[1000];

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

            // השמה לרשימה המקושרת
            Add(index, year, age, movie, name);

        }

        fclose(f);
    }
}

void Add(int index, int year, int age, char movie[100], char name[100])
{
    current = (struct oskarActor*)malloc(sizeof(struct oskarActor));

    current->index = index;
    current->year = year;
    current->age = age;
    current->Popularity = 0;
    strcpy(current->name,name);
    strcpy(current->movie, movie);
    current->next = NULL;
    current->prev = NULL;

    if (head == NULL)
    {
        head = current;
        tail = current;
    }
    else
    {
        current->prev = tail;
        tail->next = current;
        tail = current;
    }
}

void PrintList()
{
    struct oskarActor* print = head;

    if (print == NULL)
    {
        printf("\nthe list is empty\n\n");
    }
    else
    {
        printf("\n\nthe list:\n");
        while (print != NULL)
        {
            printf("list_%d :\n", print->index);
            printf("index: %d\nyear: %d\nage: %d\nname: %s\nmovie: %s\n\n",print->index, print->year, print->age, print->name, print->movie);
            print = print->next;
        }
    }
    return;
}

void FreeList()
{
    struct oskarActor* current = head;
    struct oskarActor* freeitem = head;
    while (current != NULL)
    {
        freeitem = current;
        current = current->next;
        free(freeitem);
        head = current;
    }
    //head = current;
    //iD_COUNTER = 0;
    printf("\ncongratulations, the memory of all list is free\n\n");
    return;
}

int RandomNum(int start, int end, int range)
{
    int ran = (rand() % range) + 1;

    while (ran <= start || ran >= end)
    {
        ran = (rand() % range) + 1;
    }

    return ran;
}

void PrintAllMoviesForYear(int Year)
{
    struct oskarActor* p_a_m_f_y = head;

    int count = 0;

    while (p_a_m_f_y != NULL)
    {
        if (p_a_m_f_y->year == Year)
        {
            printf("\nDetails of the player who won in %d:", Year);
            printf("\nname: %s\nage: %d", p_a_m_f_y->name, p_a_m_f_y->age);
            return;
        }
        else
        {
            p_a_m_f_y = p_a_m_f_y->next;
        }
    }

    if (count == 0)
    {
        printf("Such a year does not exist in the list\n");
    }
}

void GetMovieByIndex(int Index)
{
    struct oskarActor* idx = head;

    int count = 0;

    while (idx != NULL)
    {
        if (idx->index == Index)
        {
            printf("\nThe details of the index %d record:", Index);
            printf("\nyear: %d\nage: %d\nname: %s\nmovie: %s\n", idx->year, idx->age, idx->name, idx->movie);
            return;
        }
        else
        {
            idx = idx->next;
        }
    }

    if (!count)
    {
        printf("Such a Index does not exist in the list\n");
    }
}

int GetItemCount()
{
    struct oskarActor* countItem = head;

    int count = 0;

    while (countItem != NULL)
    {
        count++;
        countItem = countItem->next;
    }

    return count;
}

void Random()
{
    for (int i = 0; i <= 100000; i++)
    {
        int ran = (rand() % 100) + 1;
        
        while (ran >= 90)
        {
            ran = (rand() % 100) + 1;
        }
        
        UpdatePopularity(ran);
    }

    struct oskarActor* Popular = head;

    while (Popular != NULL)
    {

        if (popularNum < Popular->Popularity)
        {
            strcpy(popularName, Popular->name);
            popularNum = Popular->Popularity;
        }
        else if (popularNum == Popular->Popularity)
        {
            strcat(popularName, " and ");
            strcat(popularName, Popular->name);
        }

        Popular = Popular->next;
    }

    return;

}

void UpdatePopularity(int Inedx)
{
    struct oskarActor* Popular = head;
    
    while (Popular->index != Inedx)
    {
        Popular = Popular->next;
    }

    Popular->Popularity++;


}

void Save()
{
    //הגדרת header
    header.version = Version;
    header.itemCount = GetItemCount();

    FILE* f = fopen(file_name, "wb");

    if (f == NULL)
    {
        printf("The file did not open");
        exit(1);
    }
    else
    {
        fwrite(&header, sizeof(struct oskarActor_header), 1, f);

        struct oskarActor* saveItem = head;

        while (saveItem != NULL)
        {
            fwrite(saveItem, sizeof(struct oskarActor), 1, f);
            saveItem = saveItem->next;
        }

        fclose(f);
    }
}

void LoadList()
{
    FILE* f = fopen(file_name, "rb");

    if (f == NULL)
    {
        printf("The file did not open");
        exit(1);
    }
    else
    {
        FreeList();
        head = NULL;
        tail = NULL;
        struct oskarActor* currentOFload;
        struct oskarActor_header headerOFload;
        
        currentOFload = (struct oskarActor*)malloc(sizeof(struct oskarActor));

        int read = fread(&headerOFload, sizeof(struct oskarActor_header), 1, f);

        for (int i = 0; i < headerOFload.itemCount ; i++)
        {
            read = fread(currentOFload, sizeof(struct oskarActor), 1, f);

            Add(currentOFload->index, currentOFload->year, currentOFload->age, currentOFload->movie, currentOFload->name);
            printf("list_%d :\n", currentOFload->index);
            printf("index: %d\nyear: %d\nage: %d\nname: %s\nmovie: %s\n\n", currentOFload->index, currentOFload->year, currentOFload->age, currentOFload->name, currentOFload->movie);
        }

        free(currentOFload);
        fclose(f);
    }
}
