#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_VISITS 20

struct Visit{
    char date[20];
    char diagnosis[50];
    char prescription[50];
};

struct Patient{
    int id, age, visitCount;
    char name[50], phone[15];
    struct Visit visits[MAX_VISITS];
};

struct Patient p[MAX];
int count=0;

/* Load data from text file */
void loadData()
{
    FILE *fp=fopen("patients.txt","r");
    if(fp==NULL) return;

    fscanf(fp,"%d",&count);

    for(int i=0;i<count;i++)
    {
        fscanf(fp,"%d %d %d",&p[i].id,&p[i].age,&p[i].visitCount);
        fscanf(fp," %[^\n]",p[i].name);
        fscanf(fp,"%s",p[i].phone);

        for(int j=0;j<p[i].visitCount;j++)
        {
            fscanf(fp," %[^\n]",p[i].visits[j].date);
            fscanf(fp," %[^\n]",p[i].visits[j].diagnosis);
            fscanf(fp," %[^\n]",p[i].visits[j].prescription);
        }
    }

    fclose(fp);
}

/* Save data to text file */
void saveData()
{
    FILE *fp=fopen("patients.txt","w");

    if(fp==NULL)
    {
        printf("File save error\n");
        return;
    }

    fprintf(fp,"%d\n",count);

    for(int i=0;i<count;i++)
    {
        fprintf(fp,"%d %d %d\n",p[i].id,p[i].age,p[i].visitCount);
        fprintf(fp,"%s\n",p[i].name);
        fprintf(fp,"%s\n",p[i].phone);

        for(int j=0;j<p[i].visitCount;j++)
        {
            fprintf(fp,"%s\n",p[i].visits[j].date);
            fprintf(fp,"%s\n",p[i].visits[j].diagnosis);
            fprintf(fp,"%s\n",p[i].visits[j].prescription);
        }
    }

    fclose(fp);
}

/* Register patient */
void registerPatient()
{
    if(count>=MAX)
    {
        printf("Patient limit reached\n");
        return;
    }

    printf("Patient ID: ");
    scanf("%d",&p[count].id);

    printf("Name: ");
    scanf(" %[^\n]",p[count].name);

    printf("Age: ");
    scanf("%d",&p[count].age);

    if(p[count].age<=0)
    {
        printf("Invalid age\n");
        return;
    }

    printf("Phone: ");
    scanf("%s",p[count].phone);

    p[count].visitCount=0;
    count++;

    printf("Patient registered\n");
}

/* Add visit */
void addVisit()
{
    int id;

    printf("Enter Patient ID: ");
    scanf("%d",&id);

    for(int i=0;i<count;i++)
    {
        if(p[i].id==id)
        {
            if(p[i].visitCount>=MAX_VISITS)
            {
                printf("Visit limit reached\n");
                return;
            }

            int v=p[i].visitCount;

            printf("Date: ");
            scanf(" %[^\n]",p[i].visits[v].date);

            printf("Diagnosis: ");
            scanf(" %[^\n]",p[i].visits[v].diagnosis);

            printf("Prescription: ");
            scanf(" %[^\n]",p[i].visits[v].prescription);

            p[i].visitCount++;

            printf("Visit added\n");
            return;
        }
    }

    printf("Patient not found\n");
}

/* Search patient */
void searchPatient()
{
    int id;

    printf("Enter Patient ID: ");
    scanf("%d",&id);

    for(int i=0;i<count;i++)
    {
        if(p[i].id==id)
        {
            printf("\nID: %d\nName: %s\nAge: %d\nPhone: %s\nVisits: %d\n",
            p[i].id,p[i].name,p[i].age,p[i].phone,p[i].visitCount);
            return;
        }
    }

    printf("Patient not found\n");
}

/* Show visit history */
void showHistory()
{
    int id;

    printf("Enter Patient ID: ");
    scanf("%d",&id);

    for(int i=0;i<count;i++)
    {
        if(p[i].id==id)
        {
            for(int j=0;j<p[i].visitCount;j++)
            {
                printf("\nVisit %d\n",j+1);
                printf("Date: %s\n",p[i].visits[j].date);
                printf("Diagnosis: %s\n",p[i].visits[j].diagnosis);
                printf("Prescription: %s\n",p[i].visits[j].prescription);
            }
            return;
        }
    }

    printf("Patient not found\n");
}

/* Show frequent visitors */
void showFrequent()
{
    printf("\nFrequent Visitors (>3 visits)\n");

    for(int i=0;i<count;i++)
    {
        if(p[i].visitCount>3)
        {
            printf("ID:%d Name:%s Visits:%d\n",
            p[i].id,p[i].name,p[i].visitCount);
        }
    }
}

/* Main menu */
int main()
{
    int ch;

    loadData();

    do
    {
        printf("\n--- Hospital Tracker ---\n");
        printf("1 Register Patient\n");
        printf("2 Add Visit\n");
        printf("3 Search Patient\n");
        printf("4 Show Visit History\n");
        printf("5 Show Frequent Visitors\n");
        printf("6 Save & Exit\n");
        printf("Choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: registerPatient(); break;
            case 2: addVisit(); break;
            case 3: searchPatient(); break;
            case 4: showHistory(); break;
            case 5: showFrequent(); break;
            case 6:
                saveData();
                printf("Data saved\n");
                break;
            default:
                printf("Invalid choice\n");
        }

    }while(ch!=6);

    return 0;
}