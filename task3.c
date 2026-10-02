#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student {
    int rollNo;
    char name[50];
    int age;
    char course[50];
    float marks;
};


void addStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully!\n");
}


void displayStudents() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("\nRoll No : %d", s.rollNo);
        printf("\nName    : %s", s.name);
        printf("\nAge     : %d", s.age);
        printf("\nCourse  : %s", s.course);
        printf("\nMarks   : %.2f", s.marks);
        printf("\n-------------------------------------\n");
    }

    fclose(fp);
}


void searchStudent() {
    struct Student s;
    int rollNo, found = 0;

    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == rollNo) {
            printf("\nStudent Found!\n");
            printf("Roll No : %d\n", s.rollNo);
            printf("Name    : %s\n", s.name);
            printf("Age     : %d\n", s.age);
            printf("Course  : %s\n", s.course);
            printf("Marks   : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nStudent not found!\n");
}


void updateStudent() {
    struct Student s;
    int rollNo, found = 0;

    FILE *fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\nEnter Roll Number to update: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {

        if (s.rollNo == rollNo) {

            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct Student), SEEK_CUR);
            fwrite(&s, sizeof(struct Student), 1, fp);

            found = 1;
            printf("\nStudent updated successfully!\n");
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nStudent not found!\n");
}


void deleteStudent() {
    struct Student s;
    int rollNo, found = 0;

    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("\nError opening file!\n");

        if (fp != NULL)
            fclose(fp);

        if (temp != NULL)
            fclose(temp);

        return;
    }

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {

        if (s.rollNo == rollNo) {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(struct Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent not found!\n");
}

// Main function
int main() {
    int choice;

    do {
        
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}

