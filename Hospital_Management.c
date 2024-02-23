#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[20];
    float bill;
    char doctor[50];
    char doctor_specialization[60];
    struct patient *next;
} Patient;

Patient *head = NULL;

void add_patient() {
    Patient *new_patient = (Patient *)malloc(sizeof(Patient));
    printf("Enter the patient id:");
    scanf("%d", &new_patient->id);
    printf("Enter patient name: ");
    scanf("%s", new_patient->name);
    printf("Enter patient age: ");
    scanf("%d", &new_patient->age);
    printf("Enter patient gender: ");
    scanf("%s", new_patient->gender);
    printf("Enter patient disease: ");
    scanf("%s", new_patient->disease);
    printf("Enter bill amount: ");
    scanf("%f", &new_patient->bill);
    new_patient->next = head;
    head = new_patient;
}

void assign_doctor() {
    char name[50];
    char doctor[50];
    char doctor_specialization[50];
    printf("Enter patient name to assign doctor: ");
    scanf("%s", name);
    Patient *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Enter doctor name: ");
            scanf("%s", doctor);
            printf("Enter doctor's specialization: ");
            scanf("%s", doctor_specialization);
            strcpy(temp->doctor, doctor);
            printf("Doctor %s assigned to patient %s\n", doctor, name);
            return;
        }
        temp = temp->next;
    }
    printf("Patient not found\n");
}

void display_patients() {
    int ct = 0;
    if (head == NULL) {
        printf("No patients found\n");
        return;
    }
    Patient *temp = head;
    printf("ID\tName\tAge\tGender\tDisease\tDoctor\tBill\n");
    while (temp != NULL) {
        printf("%d\t%s\t%d\t%s\t%s\t%s\t%.2f\n", temp->id, temp->name, temp->age, temp->gender, temp->disease, temp->doctor, temp->bill);
        temp = temp->next;
        ct++;
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    printf("Total number of patients:%d\n", ct);
}

void search_patient() {
    char name[50];
    printf("Enter patient name to search: ");
    scanf("%s", name);
    Patient *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Name\tAge\tGender\tBill\n");
            printf("%s\t%d\t%s\t%.2f\n", temp->name, temp->age, temp->gender, temp->bill);
            return;
        }
        temp = temp->next;
    }
    printf("Patient not found\n");
}

void calculate_bill() {
    char name[50];
    printf("Enter patient name to calculate bill: ");
    scanf("%s", name);
    Patient *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            float charges;
            printf("Enter charges: ");
            scanf("%f", &charges);
            temp->bill += charges;
            printf("Bill for %s is now %.2f\n", temp->name, temp->bill);
            return;
        }
        temp = temp->next;
    }
    printf("Patient not found\n");
}

void delete_patient() {
    char name[50];
    printf("Enter patient name to delete: ");
    scanf("%s", name);
    if (head == NULL) {
        printf("No patients found\n");
        return;
    }
    Patient *temp = head, *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Patient %s deleted\n", name);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Patient not found\n");
}

void bubble_sort() {
    int swapped;
    Patient *ptr1;
    Patient *lptr = NULL;
    if (head == NULL) {
        printf("No patients found\n");
        return;
    }
    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->age > ptr1->next->age) {
                Patient temp = *ptr1;
                *ptr1 = *(ptr1->next);
                *(ptr1->next) = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void loadList() {
    FILE *fp = fopen("hosp_list.bin", "rb");
    if (!fp) {
        printf("\nNote: Empty Data file, the program is being run for the 1st time!!\n");
        return;
    }
    Patient *new_patient = (Patient *)malloc(sizeof(Patient));
    while (fread(new_patient, sizeof(Patient), 1, fp)) {
        new_patient->next = NULL;
        Patient *temp = head;
        if (head == NULL) {
            head = new_patient;
        } else {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_patient;
        }
        new_patient = (Patient *)malloc(sizeof(Patient));
    }
    fclose(fp);
}

void storeList() {
    FILE *fp = fopen("hosp_list.bin", "wb");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    Patient *temp = head;
    while (temp != NULL) {
        fwrite(temp, sizeof(Patient), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}

int main() {
    int choice;
    loadList();
    printf("*****************||SANATHA HOSPITAL||****************");
    do {
        printf("\n1. Add Patient\n");
        printf("2. Assigning doctor\n");
        printf("3. Display Patients\n");
        printf("4. Search Patient\n");
        printf("5. Calculate Bill\n");
        printf("6. Delete Patient\n");
        printf("7. Sort Patients by Age\n");
        printf("8. Exit\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        switch (choice) {
            case 1:
                add_patient();
                printf("-----------------------------------------------------------------------------------------------------------------------\n");
                break;
            case 2:
                assign_doctor();
                printf("----------------------------------------------------------------------------------------------------------------------\n");
                break;
            case 3:
                display_patients();
                printf("----------------------------------------------------------------------------------------------------------------------\n");
                break;
            case 4:
                search_patient();
                printf("----------------------------------------------------------------------------------------------------------------------\n");
                break;
            case 5:
                calculate_bill();
                printf("---------------------------------------------------------------------------------------------------------------------\n");
                break;
            case 6:
                delete_patient();
                printf("---------------------------------------------------------------------------------------------------------------------\n");
                break;
            case 7:
                bubble_sort();
                printf("Patients sorted by age\n");
                printf("--------------------------------------------------------------------------------------------------------------------\n");
                break;
            case 8:
                storeList();
                exit(0);
                break;
            case 9:
                printf("Exiting program\n");
                printf("-------------------------------------------------------------------------------------------------------------------\n");
                break;
            default:
                printf("Invalid choice\n");
                printf("------------------------------------------------------------------------------------------------------------------\n");
                break;
        }
    } while (choice != 8);
    return 0;
}
