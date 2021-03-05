// Hoc vien: Khong Phuong Thao
// Lop: Bao dam an toan thong tin 
// Don vi: c155 - d1

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
typedef struct IRIS
{
    float sepal_l;          // _l: length; _w: width;
    float sepal_w;
    float petal_l;
    float petal_w;
    char clss[50];
} iris;
int numOfFields(char filename[]);
void readtxt(iris *p, char filename[]);
void addFields(iris *p, int n, char filename[]);
void writeBin(iris *p, int n, char filename[], char nameBin[]);
void clearScr();
int main()
{
    char filename[60];
    int select;
    int entered = 0;
    int check_while = 1;
    int addField;
    while (check_while)
    {
        printf("\n _________________________________________________________________________________");
        printf("\n|                       DO SOMETHING WITH YOUR FILE                               |");
        printf("\n| --------------------------------------------------------------------------------|");
        printf("\n|     0. Enter your file name.                                                    |");
        printf("\n|---------------------------------------------------------------------------------|");
        printf("\n|     1. Read your file.                                                          |");
        printf("\n|---------------------------------------------------------------------------------|");
        printf("\n|     2. Write your data to a binary file: <filename>.bin.                        |");
        printf("\n|---------------------------------------------------------------------------------|");
        printf("\n|     3. Add fields to your text file.                                            |");
        printf("\n|---------------------------------------------------------------------------------|");
        printf("\n|     4. Updating...                                                              |");
        printf("\n|---------------------------------------------------------------------------------|");
        printf("\n|     5. Updating...                                                              |");
        printf("\n|---------------------------------------------------------------------------------|");
        printf("\n|     6. Exit.                                                                    |");
        printf("\n|_________________________________________________________________________________|");
        printf("\n\n    Select a function\n");
        scanf("%d", &select);
        switch (select)
        {
        case 0: //Enter your file name.
        {
            entered = 1;
            fflush(stdin);
            printf("\nEnter your file name: ");
            gets(filename);
            clearScr();
            break;
        }
        case 1:    //Read your file.
        {
            if (entered == 0)
            {
                printf("\nRemember to entered your file name first");
            }
            else
            {
                FILE *fp = fopen(filename, "r");
                rewind(fp);
                if (fp == NULL)
                {
                    fprintf(stderr, "can't open file %s\n", filename);
                    perror("because: ");
                    exit(1);
                }
                iris *pIris = (iris *)malloc(numOfFields(filename) * sizeof(iris));
                readtxt(pIris, filename);
                free(pIris);
            }
            clearScr();
            break;
        }
        case 2:     //Write your data to a binary file: <filename>.bin.
        {
            if (entered == 0)
            {
                printf("\n Remember to entered your file name first");
            }
            else
            {
                char nameBin[100];
                printf("\nEnter name of output binary file (including '.bin'): ");
                fflush(stdin);
                gets(nameBin);
                FILE *fp = fopen(filename, "r");
                if (fp == NULL)
                {
                    fprintf(stderr, "can't open file %s\n", filename);
                    perror("because: ");
                    exit(1);
                }
                int n = numOfFields(filename);
                fseek(fp, 4, SEEK_SET);
                iris *p = (iris *)malloc(n * sizeof(iris));
                for (int i = 0; i < 0; i++)
                {
                    fscanf(fp, "%f,%f,%f,%f,%s\n", &((p + i)->sepal_l), &((p + i)->sepal_w), &((p + i)->petal_l), &((p + i)->petal_w), ((p + i)->clss));
                }
                writeBin(p, n, filename, nameBin);
                free(p);
            }
            clearScr();
            break;
        }
        case 3:     //Add fields to your text file.
        {
            if (entered == 0)
            {
                printf("\n Remember to entered your file name first");
            }
            else
            {
                printf("\nHow many fields would you like to add to your file? ");
                scanf("%d", &addField);
                iris *p = (iris *)malloc(addField * sizeof(iris));
                printf("\nPlease enter each field's attributions: \n");
                for (int i = 0; i < addField; i++)
                {
                    printf("Field %d:\n", i + 1);
                    printf("Sepal length: ");
                    scanf("%f", &((p + i)->sepal_l));
                    printf("\nSepal width: ");
                    scanf("%f", &((p + i)->sepal_w));
                    printf("\nPetal length: ");
                    scanf("%f", &((p + i)->petal_l));
                    printf("\nPetal width: ");
                    scanf("%f", &((p + i)->petal_w));
                    printf("\nClass: ");
                    fflush(stdin);
                    scanf("%s", (p + i)->clss);
                    fflush(stdin);
                }
                addFields(p, addField, filename);
                free(p);
            }
            clearScr();
            break;
        }
        case 4: case 5:     //Updating for more 
        {
            printf("\nThis function is being updated!\nPlease come back later!");
            clearScr();
            break;
        }
        case 6:     //Exit 
        {
            char ans;
            printf("\nAre you sure to quit the program? (y/n) ");
            fflush(stdin);
            scanf("%c", &ans);
            if (ans == 'y' || ans == 'Y')
            {
                printf("\nSee you later!");
                check_while = 0;
            }
            else
                clearScr();
            break;
        }
        default:
        {
            printf("\nInvalid selection!");
            clearScr();
            break;
        }
        }
    }
    return 0;
}
void readtxt(iris *p, char filename[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "can't open file %s\n", filename);
        perror("because: ");
        exit(1);
    }
    fseek(fp, 4, SEEK_SET);
    int i = 0;
    printf("\nLoading data ...\n");
    while (fscanf(fp, "%f,%f,%f,%f,%s\n", &((p + i)->sepal_l), &((p + i)->sepal_w), &((p + i)->petal_l), &((p + i)->petal_w), ((p + i)->clss)) != EOF)
    {

        printf("%.1f\t%.1f\t%.1f\t%.1f\t%s\n", (p + i)->sepal_l, (p + i)->sepal_w, (p + i)->petal_l, (p + i)->petal_w, (p + i)->clss);
        i++;
    }
    printf("%d fields have already been read!", i);
    fclose(fp);
}
int numOfFields(char filename[])
{
    FILE *fp = fopen(filename, "r");
    rewind(fp);

    if (fp == NULL)
    {
        fprintf(stderr, "can't open file %s\n", filename);
        perror("because: ");
        exit(1);
    }
    int n;
    fscanf(fp, "%d", &n);
    return n;
}
void addFields(iris *p, int n, char filename[])
{
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file %s\n", filename);
        perror("because: ");
        exit(1);
    }
    // ghi de gia tri so field o dau file
    rewind(fp);
    int x;
    fscanf(fp, "%d", &x);
    x += n;
    fprintf(fp, "%d", x);
    fseek(fp, -1, SEEK_END);
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "\n%.1f,%.1f,%.1f,%.1f,%s", (p + i)->sepal_l, (p + i)->sepal_w, (p + i)->petal_l, (p + i)->petal_w, (p + i)->clss);
    }
    fclose(fp);
    printf("\nYour data has just been successfully appended to %s file.\nPlease check it out for more!", filename);
}

void writeBin(iris *p, int n, char filename[], char nameBin[])
{
    FILE *fo = fopen(nameBin, "wb");
    if (fo == NULL)
    {
        fprintf(stderr, "Can't open file %s\n", filename);
        perror("because: ");
        exit(1);
    }
    rewind(fo);
    fwrite(&n, sizeof(int), 1, fo);
    for (int i = 0; i < n; i++)
    {
        fwrite(p + i, sizeof(iris), 1, fo);
    }
    fclose(fo);
    printf("\nSuccessfully writing your data to %s file.\nPlease check it out!", nameBin);
}
void clearScr()
{
    printf("\nEnter a key to continue...");
    getch();
    fflush(stdin);
    system("cls");
}
