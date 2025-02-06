#include <stdio.h>
#include <stdlib.h>  
#include <conio.h>

// Function prototypes
void addStudent();
void searchStudent();
void deleteStudent();
void displayMenu();
void studentRecord();

// Structure defination for student
struct student {
    char first_name[20];
    char last_name[20];
    int roll_no;
    char class[10];
    char vill[20];
    float per;
};

int main() {
        int choice = 0;     // Variable to store user's menu choice
        while (choice!=5){  // Continue looping until the user chooses to exit
        displayMenu();      // Display the menu options
        printf("Enter your choice between 1 to 5: ");
        scanf("%d", &choice);

        switch (choice) {
    case 1:
        system("cls");      // Clear screen
        addStudent();       // Function to add student record
        system("cls");      // Clear screen
        break;
    case 2:
        system("cls");      // Clear screen
        searchStudent();    // Function to search student record
        printf("\n\t\t\tPress any key to exit\n");
        getch();            // Wait for user input
        system("cls");      // Clear screen
        break;
    case 3:
        system("cls");      // Clear screen
        studentRecord();    // Function to display all student records
        printf("\t\t\t\tPress any key to exit\n");      
        getch();            // Wait for user input
        system("cls");      // Clear screen
        break;
    case 4:
        system("cls");      // Clear screen
        deleteStudent();    // Function to delete student record
        printf("\n\t\t\tPress any key to exit\n");
        getch();            // Wait for user input
        system("cls");      // Clear screen
        break;
    case 5:
        exit(0);            // Proper exit
    default:
        printf("Invalid choice! Please enter a valid option.\n");
}          
    }
    return 0;
}

// Function to display the main menu
void displayMenu() {
    printf("\t\t\t=====STUDENT DATABASE MANAGEMENT SYSTEM=====\n");
    printf("\n\n\t\t\t 1. Add Student Record\n");
    printf("\n\n\t\t\t 2. Search Student Record\n");
    printf("\n\n\t\t\t 3. Display All Records\n");
    printf("\n\n\t\t\t 4. Delete Record\n");
    printf("\n\n\t\t\t 5. Exit\n");
    printf("\t\t\t ___________________________\n");
    printf("\t\t\t ");
}

// Function to add new student
void addStudent() {
    char another = 'y';     // Variable to determine if user wants to add another record
    FILE *fp;
    struct student info;

    do {
        system("cls");
        printf("\t\t\t\t======Add Student Info======\n\n\n");
        fp = fopen("student_info.txt", "a");       // Open file in append mode
        if (fp == NULL) {
            fprintf(stderr, "Can't open file\n");
            return;
        }

        printf("\n\t\t\t Enter first name   : ");
        scanf("%s", info.first_name);
        printf("\n\t\t\t Enter last name    : ");
        scanf("%s", info.last_name);
        printf("\n\t\t\t Enter roll no      : ");
        scanf("%d", &info.roll_no);
        printf("\n\t\t\t Enter class        : ");
        scanf("%s", info.class);
        printf("\n\t\t\t Enter address      : ");
        scanf("%s", info.vill);
        printf("\n\t\t\t Enter percentage   : ");
        scanf("%f", &info.per);

        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);

        printf("\t\t\tRecord stored successfully\n");
        printf("\t\t\tDo you want to add another record? (y/n): ");      
        scanf(" %c", &another);      // Note the space before %c to handle newline character

    } while (another == 'y' || another == 'Y');     // Continue if the user inputs 'y' or 'Y'
}

// Function to display student record
void studentRecord(){
    FILE *fp;
    struct student info;
    fp = fopen("student_info.txt", "r");    // Open file in read mode
    printf("\t\t\t\t======Student Records======\n\n\n");

    if(fp == NULL){
        fprintf(stderr, "\t\t\tCan't open file\n");
    } else {
        printf("\t\t\t\t_____________________\n\n");
        while(fread(&info, sizeof(struct student), 1, fp)){
            printf("\n\t\t\t\tStudent name : %s %s ", info.first_name, info.last_name);
            printf("\n\t\t\t\tRoll no      : %d ", info.roll_no);
            printf("\n\t\t\t\tClass        : %s ", info.class);
            printf("\n\t\t\t\tAddress      : %s ", info.vill);
            printf("\n\t\t\t\tPercentage   : %.2f ", info.per);
            printf("\n\t\t\t\t__________________________________\n");
        }
    }
    fclose(fp);
    getch();    // Wait for user input
}

// Function to search student
void searchStudent() {
    FILE *fp;
    struct student info;
    int roll_no, found = 0;
    fp = fopen("student_info.txt", "r");
    printf("\t\t\t\t======Search Student======\n\n\n");
    printf("\t\t\tEnter roll no: ");
    scanf("%d", &roll_no);

// Read and search for the student record
    while(fread(&info, sizeof(struct student), 1, fp)){
        if (info.roll_no == roll_no) {
            found = 1;
            printf("\n\t\t\t\tStudent name : %s %s ", info.first_name, info.last_name);
            printf("\n\t\t\t\tRoll no      : %d ", info.roll_no);
            printf("\n\t\t\t\tClass        : %s ", info.class);
            printf("\n\t\t\t\tAddress      : %s ", info.vill);
            printf("\n\t\t\t\tPercentage   : %.2f ", info.per);
            printf("\n\t\t\t\t__________________________________\n");
        }
    }
    if(!found){
        printf("\t\t\tRecord not found\n");
    }
    fclose(fp);
    getch();    // Wait for user input
}

// Function to delete student record by roll no
void deleteStudent() {
    FILE *fp, *fp1;
    struct student info;
    int roll_no, found = 0;

    printf("\t\t\t\t======Delete Student======\n\n\n");
    fp = fopen("student_info.txt", "r");       // Open file in read mode
    fp1 = fopen("temp.txt", "w");              // Open temporary file in write mode
    if(fp == NULL || fp1 == NULL){
        fprintf(stderr, "\t\t\t\tCan't open file\n");
        return;
    }

    printf("\t\t\tEnter roll no: ");
    scanf("%d", &roll_no);

    while(fread(&info, sizeof(struct student), 1, fp)){
        if (info.roll_no == roll_no) {
            found = 1;
        } else {
            fwrite(&info, sizeof(struct student), 1, fp1);      // Write to temporary file if not deleting
        }
    }

    fclose(fp);
    fclose(fp1);

    if(found){
        remove("student_info.txt");     // Delete the original file
        rename("temp.txt", "student_info.txt");     //Rename temporary file to original file name
        printf("\n\t\t\tRecord deleted successfully\n");
    } else {
        printf("\n\t\t\tRecord not found\n");
    }
}

    