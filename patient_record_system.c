#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    struct Patient* next;
} Patient;

Patient* createPatient(int id, char name[], int age, char disease[]) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->id = id;
    strcpy(newPatient->name, name);
    newPatient->age = age;
    strcpy(newPatient->disease, disease);
    newPatient->next = NULL;
    return newPatient;
}

void addPatient(Patient** head, int id, char name[], int age, char disease[]) {
    Patient* newPatient = createPatient(id, name, age, disease);
    if (*head == NULL) {
        *head = newPatient;
    } else {
        Patient* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newPatient;
    }
    printf("Patient added successfully!\n");
}

void deletePatient(Patient** head, int id) {
    Patient* temp = *head;
    Patient* prev = NULL;
    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        printf("Patient with ID %d deleted.\n", id);
        return;
    }
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Patient with ID %d deleted.\n", id);
}

void displayPatients(Patient* head) {
    if (head == NULL) {
        printf("No patients in the record.\n");
        return;
    }
    printf("\nPatient Records:\nID\tName\t\tAge\tDisease\n");
    printf("----------------------------------------\n");
    while (head != NULL) {
        printf("%d\t%s\t\t%d\t%s\n", head->id, head->name, head->age, head->disease);
        head = head->next;
    }
}

void searchPatient(Patient* head, int id) {
    while (head != NULL) {
        if (head->id == id) {
            printf("Patient found:\nID: %d\nName: %s\nAge: %d\nDisease: %s\n", head->id, head->name, head->age, head->disease);
            return;
        }
        head = head->next;
    }
    printf("Patient with ID %d not found.\n", id);
}

int main() {
    Patient* head = NULL;
    int choice, id, age;
    char name[50], disease[50];

    while (1) {
        printf("\nHospital Patient Record System\n");
        printf("1. Add Patient\n2. Delete Patient\n3. Display Patients\n4. Search Patient\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter Age: ");
                scanf("%d", &age);
                getchar();
                printf("Enter Disease: ");
                fgets(disease, sizeof(disease), stdin);
                disease[strcspn(disease, "\n")] = 0;
                addPatient(&head, id, name, age, disease);
                break;
            case 2:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deletePatient(&head, id);
                break;
            case 3:
                displayPatients(head);
                break;
            case 4:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchPatient(head, id);
                break;
            case 5:
                while (head != NULL) {
                    Patient* temp = head;
                    head = head->next;
                    free(temp);
                }
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
