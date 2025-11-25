#include <stdio.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
    char grade;
    char hostel[10];
    char fee[10];
  };

   char grade(float b) {
    if (b >= 90) return 'A';
     else if (b >= 80) return 'B';
    else if (b >= 70) return 'C';
     else if (b >= 60) return 'D';
    else return 'F';
}

void addStudent() {
     FILE *fp;
     struct Student s;
 
    fp = fopen("students.txt", "a");

     printf("\nEnter Roll No: ");
    scanf("%d", &s.roll);
 
    printf("Enter Name: ");
       scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
        scanf("%f", &s.marks);

     printf("Hostel (Yes/No): ");
     scanf("%s", s.hostel);

       printf("Fee Status (Paid/Due): ");
    scanf("%s", s.fee);

         s.grade = grade(s.marks);

           fprintf(fp, "%d|%s|%.2f|%c|%s|%s\n",s.roll, s.name, s.marks, s.grade, s.hostel, s.fee);

      fclose(fp);
         printf("\nStudent Added Successfully!\n");
}

 void displayStudents() {
      FILE *fp;
     struct Student s;

     fp = fopen("students.txt", "r");

     if (fp == NULL) {
        printf("\nNo records found!\n");
        return;  }

  printf("\n--- All Student Records ---\n");

   
   
       while (fscanf(fp, "%d|%[^|]|%f|%c|%[^|]|%s",&s.roll, s.name, &s.marks, &s.grade, s.hostel, s.fee) != EOF) {
  
            printf("\nRoll: %d\nName: %s\nMarks: %.2f\nGrade: %c\nHostel: %s\nFee Status: %s\n",s.roll, s.name, s.marks, s.grade, s.hostel, s.fee);
    }

fclose(fp);
}

void   hostelAndfee() {
       FILE *fp;
   
    struct Student s;

    fp = fopen("students.txt", "r");

  
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    
	printf("\n==== Hostel Allocation & Fee Status ====\n");

    while (fscanf(fp, "%d|%[^|]|%f|%c|%[^|]|%s",&s.roll, s.name, &s.marks, &s.grade, s.hostel, s.fee) != EOF) {

        printf("\nRoll: %d\nName: %s\nHostel: %s\nFee Status: %s\n",s.roll, s.name, s.hostel, s.fee);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("\nNo records exist.\n");
        return;
    }

    printf("\nEnter Roll No to search: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d|%[^|]|%f|%c|%[^|]|%s",&s.roll, s.name, &s.marks, &s.grade, s.hostel, s.fee) != EOF) {

        if (s.roll == roll) {
            found = 1;
            printf("\nRecord Found:\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\nGrade: %c\nHostel: %s\nFee Status: %s\n",s.roll, s.name, s.marks, s.grade, s.hostel, s.fee);
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");

    fclose(fp);
}

void updateStudent() {
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("final.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("\nNo records to update.\n");
        return;
    }

    printf("\nEnter Roll No to update: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d|%[^|]|%f|%c|%[^|]|%s",&s.roll, s.name, &s.marks, &s.grade, s.hostel, s.fee) != EOF) {

        if (s.roll == roll) {
            found = 1;

            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            printf("Hostel (Yes/No): ");
            scanf("%s", s.hostel);

            printf("Fee Status (Paid/Due): ");
            scanf("%s", s.fee);

            s.grade = grade(s.marks);
        }

        fprintf(temp, "%d|%s|%.2f|%c|%s|%s\n",s.roll, s.name, s.marks, s.grade, s.hostel, s.fee);
    }

    fclose(fp);
    fclose(temp);

    remove("final.txt");
    rename("temp.txt", "final.txt");

    if (found)
        printf("\nRecord Updated Successfully!\n");
    else
        printf("\nStudent not found.\n");
}

void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("final.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("\nNo records to delete.\n");
        return;
    }

    printf("\nEnter Roll No to delete: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d|%[^|]|%f|%c|%[^|]|%s",&s.roll, s.name, &s.marks, &s.grade, s.hostel, s.fee) != EOF) {

        if (s.roll == roll) {
            found = 1;
            continue;
        }

        fprintf(temp, "%d|%s|%.2f|%c|%s|%s\n",s.roll, s.name, s.marks, s.grade, s.hostel, s.fee);
    }

    fclose(fp);
    fclose(temp);

    remove("final.txt");
    rename("temp.txt", "final.txt");

    if (found)
        printf("\nRecord Deleted Successfully!\n");
    else
        printf("\nStudent not found.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n\******Student Management System******");
        printf("\n1. Add Student");
        printf("\n2. Display All Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\n7. Show Hostel & Fee Status");     

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) addStudent();
        else if (choice == 2) displayStudents();
        else if (choice == 3) searchStudent();
        else if (choice == 4) updateStudent();
        else if (choice == 5) deleteStudent();
        else if (choice == 6) break;
        else if (choice == 7) hostelAndfee();
        else printf("\nInvalid choice!\n");
    }

    return 0;
}
