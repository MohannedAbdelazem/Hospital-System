#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void view_records();
void view_reservations();
void add_new_patient();
void edit_patient_record(int);
void reserve_a_slot(int);
void cancel_reservation(int);
typedef struct Patient patients;
struct Patient
{
    char name[40];
    int age;
    char gender;
    int id;
    int reservation[5];
    patients* next;
};
patients* head = NULL;
patients* tail = NULL;
int main()
{
    char mode[10];
    a:printf("Please Enter the mode(Admin or User): ");
    scanf(" %s", &mode);
    if(strcmp(mode, "Admin") == 0)
    {
        int counter = 0;
        int password;
        do
        {
            counter++;
            printf("Please enter the correct password: ");
            scanf("%d", &password);
        } while (password != 1234 && counter != 3);
        if(password == 1234)
        {
            int choice;
            printf("Welcome Admin\nPlease choose from the four following features: \n");
            printf("1. Add new patient record\n");
            printf("2. Edit patient record\n");
            printf("3. Reserve a slot with the doctor\n");
            printf("4. Cancel reservation.\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                add_new_patient();
                break;
            case 2:
            {
                int id;
                printf("Please enter the id of the patient you want to edit their data: ");
                scanf("%d", &id);
                patients *idd = head;
                int flag_id = 1;
                while (idd != NULL)
                {
                    if(idd->id == id)
                    {
                        flag_id = 0;
                        break;
                    }
                    idd = idd->next;
                }
                if(!flag_id)
                {
                    edit_patient_record(id);
                }
                else
                {
                    printf("The ID you entered does not exist");

                }
                break;
            }
            case 3:
            {
                int id;
                printf("Please enter the id of the patient you want to reserve a slot for them: ");
                scanf("%d", &id);
                patients *idd = head;
                int flag_id = 1;
                while (idd != NULL)
                {
                    if(idd->id == id)
                    {
                        flag_id = 0;
                    }
                    idd = idd->next;
                }
                if(!flag_id)
                {
                    reserve_a_slot(id);
                }
                else
                {
                    printf("The ID you entered does not exist");

                }

                break;
            }
            case 4:
            {
                int id;
                printf("Please enter the id of the patient you want to cancel their reservation: ");
                scanf("%d", &id);
                patients *idd = head;
                int flag_id = 1;
                while (idd != NULL)
                {
                    if(idd->id == id)
                    {
                        flag_id = 0;
                    }
                    idd = idd->next;
                }
                if(!flag_id)
                {
                    cancel_reservation(id);
                }
                else
                {
                    printf("The ID you entered does not exist");

                }

                break;
            }
            default:
                printf("You did't enter the correct feature");
                break;
            }
        }
        else
        {
            printf("Incorrect password for three times, goodbye!");
        }
    }
    else if (strcmp(mode, "User") == 0)
    {
        int Choice;
        printf("Welcome User\nPlease choose from the two following features: \n");
        printf("1. View patient record.\n");
        printf("2. View today's reservations.\n");
        printf("Please choose the available feature: ");
        scanf("%d", &Choice);
        switch (Choice)
        {
        case 1:
            view_records();
            break;
        case 2:
            view_reservations();
            break;
        default:
            printf("Incorrect feature");
            break;
        }
    }
    else
    {
        printf("Please enter the correct answer (Admin or User)\n");
        goto a;
    }
    printf("\nDo you want to quit?(Yes/No)\n");
    char answer[3];
    scanf("%s", &answer);
    if(strcmp(answer, "No") == 0)
        goto a;
    else
        printf("Goodbye!");
    return 0;
}
void add_new_patient()
{
    patients *ptr = head;
    if(head == NULL)
    {
        char Name[40];
        int Age;
        char gender;
        int Id;
        printf("Please enter the patients' ID: ");
        scanf("%d", &Id);
        printf("Please enter the patients' Name: ");
        scanf("%s", &Name);
        printf("Please enter the patients' gender (m, f): ");
        scanf(" %c", &gender);
        printf("please enter the patients' age: ");
        scanf("%d", &Age);
        patients *record = (patients*) malloc(sizeof(patients));
        head = record;
        record->next = NULL;
        ptr = record;
        tail = record;
        record->age = Age;
        record->gender = gender;
        record->id = Id;
        strcpy(record->name, Name);
        for(int i = 0;i<5;i++)
            record->reservation[i] = 0;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        printf("Please enter patients' ID: ");
        int id;
        scanf("%d", &id);
        patients *checker  = head;
        int flag = 1;
        while (checker != NULL)
        {
            if(checker->id == id)
            {
                flag = 0;
            }
            checker = checker->next;
        }
        if(flag)
        {
            patients *record = (patients*) malloc(sizeof(patients));
            record->next = NULL;
            ptr->next = record;
            record->id = id;
            tail = record;
            printf("Please Enter the patients' Name: ");
            char name[40];
            scanf("%s", name);
            strcpy(record->name, name);
            printf("Please Enter your age: ");
            int age;
            scanf("%d", &age);
            record->age = age;
            printf("Please enter your gender: ");
            char gender;
            scanf(" %c", &gender);
            record->gender = gender;
            for(int i = 0;i<5;i++)
                record->reservation[i] = 0;
        }
        else
            printf("Invalid ID");
    }
}
void edit_patient_record(int id)
{
    patients *ptr = head;
    while (ptr != NULL)
    {
        if(ptr->id == id)
            break;
        ptr = ptr->next;
    }
    int age;
    printf("Please enter the patient's age: ");
    scanf("%d", &age);
    ptr->age = age;
    printf("Please Enter the patient's gender: ");
    char gender;
    scanf(" %c", &gender);
    ptr->gender = gender;
    printf("Please enter the patient's name: ");
    char name[40];
    scanf("%s", name);
    strcpy(ptr->name, name);
}
void reserve_a_slot(int id)
{
    int slot;
    patients *ptr = head;
    while(ptr != NULL)
    {
        if(ptr->id == id)
            break;
        ptr = ptr->next;
    }
    printf("The available slots:\n");
    if(ptr->reservation[0] == 0)
        printf("1-2pm to 2:30pm\n");
    if(ptr->reservation[1] == 0)
        printf("2-2:30pm to 3pm\n");
    if(ptr->reservation[2] == 0)
        printf("3-3pm to 3:30pm\n");
    if(ptr->reservation[3] == 0)
        printf("4-4pm to 4:30pm\n");
    if(ptr->reservation[4] == 0)
        printf("5-4:30pm to 5pm\n");
    printf("Please Enter the number of the prefered slot: ");
    scanf("%d", &slot);
    ptr->reservation[slot-1] = 1;
}
void cancel_reservation(int id)
{
    patients *ptr = head;
    while(ptr != NULL)
    {
        if(ptr->id == id)
            break;
        ptr = ptr->next;
    }
    printf("Please Enter the reservation slot you want to cancel:-\n");
    printf("The available slots:\n");
    if(ptr->reservation[0] == 1)
        printf("1-2pm to 2:30pm\n");
    if(ptr->reservation[1] == 1)
        printf("2-2:30pm to 3pm\n");
    if(ptr->reservation[2] == 1)
        printf("3-3pm to 3:30pm\n");
    if(ptr->reservation[3] == 1)
        printf("4-4pm to 4:30pm\n");
    if(ptr->reservation[4] == 1)
        printf("5-4:30pm to 5pm\n");
    printf("Please Enter the prefered slot: ");
    int slot;
    scanf("%d", &slot);
    if(ptr->reservation[slot-1] == 0)
        printf("You didn't do any reservations in this slot");
    else if(ptr->reservation[slot-1] == 1)
    {
        ptr->reservation[slot-1] = 0;
        printf("The reservation got cancelled successfully!\n");
    }
    else
        printf("It's not an available slot\n");
}
void view_records()
{
    patients *ptr = head;
    if(ptr == NULL)
        printf("You have no patient records");
    else
    {
        while (ptr != NULL)
        {
            printf("ID: %d\n", ptr->id);
            printf("Name: %s\n", ptr->name);
            printf("Age: %d\n", ptr->age);
            printf("Gender: %c\n", ptr->gender);
            ptr = ptr->next;
        }
    }
}
void view_reservations()
{
    patients *ptr = head;
    if(ptr == NULL)
    {
        printf("You have no patient records");
    }
    else
    {
        int counter = 0;
        while(ptr != NULL)
        {
            if(ptr->reservation[0] == 1)
            {
                printf("%s has reservation at 2pm to 2:30pm\n", ptr->name);
                counter++;
            }
            if(ptr->reservation[1] == 1)
            {
                printf("%s has reservation at 2:30pm to 3pm\n", ptr->name);
                counter++;
            }
            
            if(ptr->reservation[2] == 1)
            {
                printf("%s has reservation at 3pm to 3:30pm\n", ptr->name);
                counter++;
            }
            
            if(ptr->reservation[3] == 1)
            {
                printf("%s has reservation at 4pm to 4:30pm\n", ptr->name);
                counter++;
            }
            if(ptr->reservation[4] == 1)
            {
                printf("%s has reservation at 4:30pm to 5pm\n", ptr->name);
                counter++;
            }
            ptr = ptr->next;
        }
        if(counter == 0)
            printf("There are no reservations today\n");
    }
}
