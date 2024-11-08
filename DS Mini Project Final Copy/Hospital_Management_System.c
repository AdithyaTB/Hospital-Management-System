#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct User {
    char username[50];
    char password[50];
    struct User* next;
};

struct User* userHead = NULL;

struct Patient{
    int id;
    char name[50];
    int age;
    char gender[10];
    char address[100];
    char contact[15];
    char medicalHistory[500];
    struct Patient* next;
};

struct Patient* patientHead = NULL;

void addPatient();
void viewPatients();
void updatePatient();
void deletePatient();

void managePatients(){

      int choice;

    while (1) {
        printf("\n========== Patient Management ==========\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Update Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){

            case 1:
            addPatient();
            break;

            case 2:
            viewPatients();
            break;

            case 3:
            updatePatient();
            break;

            case 4:
            deletePatient();
            break;

            case 5:
            return;

            default:
            printf("Invalid Choice! Please enter a vaild option .\n");
        }
}
}

void addPatient(){
    FILE *fptr;
    fptr = fopen("patients.txt", "a");  
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    newPatient -> next = NULL;

    printf("Enter Patient ID: ");
    scanf("%d", &newPatient -> id);
    printf("Enter Name: ");
    getchar(); 
    scanf("%[^\n]s", newPatient -> name );
    printf("Enter Age: ");
    scanf("%d", &newPatient->age);
    printf("Enter Gender: ");
    getchar();
    scanf("%[^\n]s", newPatient->gender);
    printf("Enter Address: ");
    getchar();
    scanf("%[^\n]s", newPatient->address);
    printf("Enter Contact: ");
    getchar();
    scanf("%[^\n]s", newPatient->contact);
    printf("Enter Medical History: ");
    getchar();
    scanf("%[^\n]s", newPatient->medicalHistory);

    
    fprintf(fptr, "%d,%s,%d,%s,%s,%s,%s\n", newPatient->id, newPatient->name, newPatient->age, newPatient->gender, newPatient->address, newPatient->contact, newPatient->medicalHistory);
    fclose(fptr);  

    
    if (patientHead == NULL) {
        patientHead = newPatient;
    } else {
        struct Patient* temp = patientHead;
        while(temp -> next != NULL) {
            temp = temp -> next;
        }
        temp -> next = newPatient;
    }
    printf("Patient added successfully and stored to file.\n");
}


void viewPatients() {
    FILE *fptr;
    fptr = fopen("patients.txt", "r");  
    if (fptr == NULL) {
        printf("No Patients Available (file not found).\n");
        return;
    }

    printf("\n List of Patients :\n");
    printf("ID    Name                 Age   Gender     Contact\n");
    printf("-------------------------------------------------------\n");

    char line[1024];
    while (fgets(line, sizeof(line), fptr)) {
        int id, age;
        char name[50], gender[10], address[100], contact[15], medicalHistory[500];
        sscanf(line, "%d,%49[^,],%d,%9[^,],%99[^,],%14[^,],%499[^\n]", &id, name, &age, gender, address, contact, medicalHistory);

        
        printf("%-5d %-20s %-5d %-10s %-15s\n", id, name, age, gender, contact);
    }

    fclose(fptr);  
}



void updatePatient() {
    int id;
    printf("Enter Patient ID to Update: ");
    scanf("%d", &id);

    struct Patient* temp = patientHead;
    while (temp != NULL) {
        if (temp->id == id) {
            
            printf("Updating details for Patient ID %d:\n", id);
            printf("Enter New Name: ");
            scanf(" %[^\n]s", temp->name);
            printf("Enter New Age: ");
            scanf("%d", &temp->age);
            printf("Enter New Gender: ");
            scanf(" %[^\n]s", temp->gender);
            printf("Enter New Address: ");
            scanf(" %[^\n]s", temp->address);
            printf("Enter New Contact: ");
            scanf(" %[^\n]s", temp->contact);
            printf("Enter New Medical History: ");
            scanf(" %[^\n]s", temp->medicalHistory);

            
            FILE *file = fopen("patients.txt", "w");
            if (file == NULL) {
                printf("Error opening file for updating!\n");
                return;
            }

            struct Patient* current = patientHead;
            while (current != NULL) {
                if (current->id == id) {
                    fprintf(file, "%d,%s,%d,%s,%s,%s\n", current->id, current->name, current->age, current->gender, current->address, current->contact, current->medicalHistory);
                } else {
                    fprintf(file, "%d,%s,%d,%s,%s,%s\n", current->id, current->name, current->age, current->gender, current->address, current->contact, current->medicalHistory);
                }
                current = current->next;
            }

            fclose(file);
            printf("Patient details updated successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Patient with ID %d not found!\n", id);
}



void deletePatient() {
    int id;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    struct Patient* temp = patientHead;
    struct Patient* prev = NULL;

    
    while (temp != NULL) {
        if (temp->id == id) {
        
            if (prev == NULL) {
                patientHead = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);

            
            FILE* fptr = fopen("patients.txt", "w");  
            if (fptr == NULL) {
                printf("Error opening file!\n");
                return;
            }

            
            struct Patient* current = patientHead;
            while (current != NULL) {
                fprintf(fptr, "%d,%s,%d,%s,%s,%s,%s\n", current->id, current->name, current->age, current->gender, current->address, current->contact, current->medicalHistory);
                current = current->next;
            }
            fclose(fptr);

            printf("Patient deleted successfully and file updated.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Patient with ID %d not found!\n", id);
}


struct Billing {
    int billID;
    int patientID;
    char date[15];
    float consultationFee;
    float treatmentCost;
    float medicineCost;
    float totalCost;
    struct Billing* next;
};

struct Billing* billingHead = NULL;

void generateBill();
void ViewBills();
void deleteBills();

void manageBilling() {
    int choice;

    while (1) {
        printf("\n========== Billing System ==========\n");
        printf("1. Generate Bill\n");
        printf("2. View Bills\n");
        printf("3. Delete Bill\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateBill();
                break;
            case 2:
                ViewBills();
                break;
            case 3:
                deleteBills();
                break;
            case 4:
                return;      
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}

void generateBill() {
    FILE* fptr;
    fptr = fopen("billing.txt", "a");  
    if (fptr == NULL) {
        printf("Error opening file to save the bill!\n");
        return;
    }

    struct Billing* newBill = (struct Billing*)malloc(sizeof(struct Billing));
    newBill->next = NULL;

    printf("Enter Bill ID: ");
    scanf("%d", &newBill->billID);
    printf("Enter Patient ID: ");
    scanf("%d", &newBill->patientID);
    printf("Enter Date for Admission (DD/MM/YYYY): ");
    scanf("%s", newBill->date);  
    printf("Enter Consultation Fee: ");
    scanf("%f", &newBill->consultationFee);
    printf("Enter Treatment Cost: ");
    scanf("%f", &newBill->treatmentCost);
    printf("Enter Medicine Cost: ");
    scanf("%f", &newBill->medicineCost);

    newBill->totalCost = newBill->consultationFee + newBill->treatmentCost + newBill->medicineCost;

    fprintf(fptr, "%d,%d,%s,%.2f,%.2f,%.2f,%.2f\n", newBill->billID, newBill->patientID, newBill->date,
            newBill->consultationFee, newBill->treatmentCost, newBill->medicineCost, newBill->totalCost);
    fclose(fptr);

    
    if (billingHead == NULL) {
        billingHead = newBill;
    } else {
        struct Billing* temp = billingHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBill;
    }
    printf("Bill generated and saved to file.\n");
}

void ViewBills() {
    FILE* fptr;
    fptr = fopen("billing.txt", "r");  
    if (fptr == NULL) {
        printf("No Bills Available (file not found).\n");
        return;
    }

    printf("\n List of Bills :\n");
    printf("Bill ID   Patient ID   Date         Consultation   Treatment   Medicine   Total\n");
    printf("--------------------------------------------------------------------------------------\n");

    char line[1024];
    while (fgets(line, sizeof(line), fptr)) {
        int billID, patientID;
        float consultationFee, treatmentCost, medicineCost, totalAmount;
        sscanf(line, "%d,%d,%[^,],%f,%f,%f,%f", &billID, &patientID, line, &consultationFee, 
               &treatmentCost, &medicineCost, &totalAmount); 
        
        printf("%-8d %-12d %-12s %-14.2f %-11.2f %-9.2f %-10.2f\n", billID, patientID, line, consultationFee, treatmentCost, medicineCost, totalAmount);
    }

    fclose(fptr);  
}

void deleteBills() {
    int billID;
    printf("Enter Bill ID to delete: ");
    scanf("%d", &billID);

    struct Billing* temp = billingHead;
    struct Billing* prev = NULL;

    while (temp != NULL) {
        if (temp->billID == billID) {
            
            if (prev == NULL) {
                billingHead = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);

            
            FILE* fptr = fopen("billing.txt", "w");  
            if (fptr == NULL) {
                printf("Error opening file to update after deletion!\n");
                return;
            }

            
            struct Billing* current = billingHead;
            while (current != NULL) {
                fprintf(fptr, "%d,%d,%s,%.2f,%.2f,%.2f,%.2f\n", current->billID, current->patientID, current->date,
                        current->consultationFee, current->treatmentCost, current->medicineCost, current->totalCost);
                current = current->next;
            }
            fclose(fptr);

            printf("Bill with ID %d deleted successfully and file updated.\n", billID);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Bill with ID %d not found!\n", billID);
}


struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    char contact[15];
    struct Doctor* next;
};

struct Doctor* doctorHead = NULL;

void addDoctor(){
    FILE *fptr;
    fptr = fopen("doctors.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Doctor* newDoctor = (struct Doctor*)malloc(sizeof(struct Doctor));
    newDoctor -> next = NULL;

    printf("Enter Doctor ID: ");
    scanf("%d", &newDoctor->id);
    printf("Enter Doctor Name: ");
    getchar();
    scanf("%[^\n]s", newDoctor->name);
    printf("Enter Specialization: ");
    getchar();
    scanf("%[^\n]s", newDoctor->specialization);
    printf("Enter Contact: ");
    getchar();
    scanf("%[^\n]s", newDoctor->contact);

    
    fprintf(fptr, "%d,%s,%s,%s\n", newDoctor->id, newDoctor->name, newDoctor->specialization, newDoctor->contact);
    fclose(fptr);

    
    if (doctorHead == NULL) {
        doctorHead = newDoctor;
    } else {
        struct Doctor* temp = doctorHead;
        while(temp -> next != NULL) {
            temp = temp -> next;
        }
        temp -> next = newDoctor;
    }
    printf("Doctor added successfully and stored to file.\n");
}



void viewDoctors() {
    FILE *fptr;
    fptr = fopen("doctors.txt", "r");  
    if (fptr == NULL) {
        printf("No Doctors Available (file not found).\n");
        return;
    }

    printf("\n List of Doctors :\n");
    printf("Doctor ID   Name                 Specialization       Contact\n");
    printf("------------------------------------------------------------------\n");

    char line[1024];
    while (fgets(line, sizeof(line), fptr)) {
        int id;
        char name[50], specialization[50], contact[15];
        sscanf(line, "%d,%49[^,],%49[^,],%14[^\n]", &id, name, specialization, contact);

        
        printf("%-10d %-20s %-20s %-15s\n", id, name, specialization, contact);
    }

    fclose(fptr);  
}


void updateDoctor() {
    int id;
    printf("Enter Doctor ID to Update: ");
    scanf("%d", &id);

    struct Doctor* temp = doctorHead;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Updating details for Doctor ID %d:\n", id);
            printf("Enter New Doctor Name: ");
            scanf(" %[^\n]s", temp->name);
            printf("Enter New Specialization: ");
            scanf(" %[^\n]s", temp->specialization);
            printf("Enter New Contact: ");
            scanf(" %[^\n]s", temp->contact);

            
            FILE *file = fopen("doctors.txt", "w");
            if (file == NULL) {
                printf("Error opening file for updating!\n");
                return;
            }

            
            struct Doctor* current = doctorHead;
            while (current != NULL) {
                fprintf(file, "%d,%s,%s,%s\n", current->id, current->name, current->specialization, current->contact);
                current = current->next;
            }

            fclose(file);
            printf("Doctor details updated successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Doctor with ID %d not found!\n", id);
}



void deleteDoctor() {
    int id;
    printf("Enter Doctor ID to delete: ");
    scanf("%d", &id);

    struct Doctor* temp = doctorHead;
    struct Doctor* prev = NULL;

    
    while (temp != NULL) {
        if (temp->id == id) {
            
            if (prev == NULL) {
                doctorHead = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);

            
            FILE* fptr = fopen("doctors.txt", "w");  
            if (fptr == NULL) {
                printf("Error opening file!\n");
                return;
            }

            
            struct Doctor* current = doctorHead;
            while (current != NULL) {
                fprintf(fptr, "%d,%s,%s,%s\n", current->id, current->name, current->specialization, current->contact);
                current = current->next;
            }
            fclose(fptr);

            printf("Doctor deleted successfully and file updated.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Doctor with ID %d not found!\n", id);
}


struct Appointment {
    int appointmentID;
    int patientID;
    int doctorID;
    char date[20];
    char time[10];
    struct Appointment* next;
};

struct Appointment* appointmentHead = NULL;

void scheduleAppointment();
void viewAppointments();
void updateAppointment();
void cancelAppointment();

void manageAppointments(){
    int choice;

     while (1) {

        printf("\n========== Appointment Management ==========\n");
        printf("1. Schedule Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Update Appointment\n");
        printf("4. Cancel Appointment\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                scheduleAppointment();
                break;

            case 2:
                viewAppointments();
                break;

            case 3:
                updateAppointment();
                break;

            case 4:
                cancelAppointment();
                break;

            case 5:
                return;  
                
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

}

void scheduleAppointment() {
    FILE *fptr;
    fptr = fopen("appointments.txt", "a");  
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Appointment* newAppointment = (struct Appointment*)malloc(sizeof(struct Appointment));
    newAppointment -> next = NULL;

    printf("Enter Appointment ID: ");
    scanf("%d", &newAppointment->appointmentID);
    printf("Enter Patient ID: ");
    scanf("%d", &newAppointment->patientID);
    printf("Enter Doctor ID: ");
    scanf("%d", &newAppointment->doctorID);
    printf("Enter Appointment Date (DD/MM/YYYY): ");
    getchar();
    scanf("%[^\n]s", newAppointment->date);
    printf("Enter Appointment Time (HH:MM): ");
    getchar();
    scanf("%[^\n]s", newAppointment->time);

    
    fprintf(fptr, "%d,%d,%d,%s,%s\n", newAppointment->appointmentID, newAppointment->patientID, newAppointment->doctorID, newAppointment->date, newAppointment->time);
    fclose(fptr);

    
    if (appointmentHead == NULL) {
        appointmentHead = newAppointment;
    } else {
        struct Appointment* temp = appointmentHead;
        while(temp -> next != NULL) {
            temp = temp -> next;
        }
        temp -> next = newAppointment;
    }
    printf("Appointment scheduled and saved to file.\n");
}


void viewAppointments() {
    FILE *fptr;
    fptr = fopen("appointments.txt", "r");  
    if (fptr == NULL) {
        printf("No Appointments Available (file not found).\n");
        return;
    }

    printf("\n List of Appointments :\n");
    printf("Appointment ID   Patient ID   Doctor ID   Date          Time\n");
    printf("------------------------------------------------------------------\n");

    char line[1024];
    while (fgets(line, sizeof(line), fptr)) {
        int appointmentID, patientID, doctorID;
        char date[20], time[10];
        sscanf(line, "%d,%d,%d,%19[^,],%9[^\n]", &appointmentID, &patientID, &doctorID, date, time);

        
        printf("%-15d %-12d %-11d %-12s %-10s\n", appointmentID, patientID, doctorID, date, time);
    }

    fclose(fptr);  
}


void updateAppointment() {
    int id;
    printf("Enter Appointment ID to update: ");
    scanf("%d", &id);

    struct Appointment* temp = appointmentHead;
    while (temp != NULL) {
        if (temp->appointmentID == id) {
            printf("Updating details for Appointment ID %d:\n", id);
            printf("Enter Patient ID: ");
            scanf("%d", &temp->patientID);
            printf("Enter Doctor ID: ");
            scanf("%d", &temp->doctorID);
            printf("Enter Appointment Date (DD/MM/YYYY): ");
            scanf(" %[^\n]s", temp->date);
            printf("Enter Appointment Time (HH:MM): ");
            scanf(" %[^\n]s", temp->time);

            
            FILE *file = fopen("appointments.txt", "w");
            if (file == NULL) {
                printf("Error opening file for updating!\n");
                return;
            }

            
            struct Appointment* current = appointmentHead;
            while (current != NULL) {
                fprintf(file, "%d,%d,%d,%s,%s\n", current->appointmentID, current->patientID, current->doctorID, current->date, current->time);
                current = current->next;
            }

            fclose(file);
            printf("Appointment updated successfully!\n");
            return;
        }
        temp = temp->next;
    } 
    printf("Appointment with ID %d not found!\n", id);
}



void cancelAppointment() {
    int id;
    printf("Enter Appointment ID to cancel: ");
    scanf("%d", &id);

    struct Appointment* temp = appointmentHead;
    struct Appointment* prev = NULL;

    
    while (temp != NULL) {
        if (temp->appointmentID == id) {
            
            if (prev == NULL) {
                appointmentHead = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);

            
            FILE* fptr = fopen("appointments.txt", "w"); 
            if (fptr == NULL) {
                printf("Error opening file!\n");
                return;
            }

            
            struct Appointment* current = appointmentHead;
            while (current != NULL) {
                fprintf(fptr, "%d,%d,%d,%s,%s\n", current->appointmentID, current->patientID, current->doctorID, current->date, current->time);
                current = current->next;
            }
            fclose(fptr);

            printf("Appointment cancelled successfully and file updated.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Appointment with ID %d not found!\n", id);
}






void manageDoctors(){
    int choice;

    while(1){
        printf("\n========== Doctor Management ==========\n");
        printf("1. Add Doctor\n");
        printf("2. View Doctors\n");
        printf("3. Update Doctor\n");
        printf("4. Delete Doctor\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            addDoctor();
            break;
            case 2:
            viewDoctors();
            break;
            case 3:
            updateDoctor();
            break;
            case 4:
            deleteDoctor();
            break;
            case 5:
            return;
            default:
            printf("Invalid choice! Please enter a valid option.\n");
        }

    }
}

void mainMenu(){
    int choice;

    while(1){

         printf("========== Hospital Management System ==========\n");
        printf("                    Welcome           \n");
        printf("=================================================\n");

        printf("1. Manage Patients\n");
        printf("2. Manage Doctors\n");
        printf("3. Manage Appointments\n");
        printf("4. Manage Billing\n");
        printf("5. Exit\n");
        
        printf("=================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){

              case 1:
                managePatients();
                break;
            case 2:
                manageDoctors();
                break;
            case 3:
                manageAppointments();
                break;
            case 4:
                manageBilling();
                break;
            case 5:
                printf("Exiting system...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");

        }

    }
}

void registerUser();
int loginUser();
void saveUsersToFile();
void loadUsersFromFile();


void registerUser() {
    FILE *fptr = fopen("users.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    newUser->next = NULL;

    printf("Enter a username: ");
    getchar(); 
    scanf("%[^\n]s", newUser->username);
    printf("Enter a password: ");
    getchar();  
    scanf("%[^\n]s", newUser->password);

    fprintf(fptr, "%s,%s\n", newUser->username, newUser->password);
    fclose(fptr);


    if (userHead == NULL) {
        userHead = newUser;
    } else {
        struct User* temp = userHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newUser;
    }

    printf("Registration successful!\n");
}


int loginUser() {
    char username[50], password[50];
    int loginSuccess = 0;

    printf("Enter your username: ");
    getchar();  
    scanf("%[^\n]s", username);
    printf("Enter your password: ");
    getchar();
    scanf("%[^\n]s", password);

    
    struct User* temp = userHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && strcmp(temp->password, password) == 0) {
            loginSuccess = 1;
            break;
        }
        temp = temp->next;
    }

    if (loginSuccess) {
        printf("Login successful! Welcome, %s.\n", username);
        return 1;  
    } else {
        printf("Invalid username or password. Please try again.\n");
        return 0;  
    }
}


void loadUsersFromFile() {
    FILE *fptr = fopen("users.txt", "r");
    if (fptr == NULL) {
        printf("No users registered yet. Please register first.\n");
        return;
    }

    while (!feof(fptr)) {
        struct User* newUser = (struct User*)malloc(sizeof(struct User));
        newUser->next = NULL;

        if (fscanf(fptr, "%[^,],%[^\n]\n", newUser->username, newUser->password) == 2) {
            
            if (userHead == NULL) {
                userHead = newUser;
            } else {
                struct User* temp = userHead;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newUser;
            }
        } else {
            free(newUser);
        }
    }
    fclose(fptr);
}

void saveUsersToFile() {
    FILE *fptr = fopen("users.txt", "w");
    if (fptr == NULL) {
        printf("Error saving users to file!\n");
        return;
    }

    struct User* temp = userHead;
    while (temp != NULL) {
        fprintf(fptr, "%s,%s\n", temp->username, temp->password);
        temp = temp->next;
    }

    fclose(fptr);
}

int main() {
    int choice;
    loadUsersFromFile();  

    while (1) {
      printf("\n");
        printf("========== Welcome to Hospital Management System ==========\n");
        printf("============================================================\n");
        printf("                     User Authentication                      \n");
        printf("============================================================\n");

        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("============================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                saveUsersToFile();  
                break;
            case 2:
                if (loginUser()) {
                   
                    printf("Redirecting to the Hospital Management System...\n");
                     mainMenu();  
                }
                break;
            case 3:
                printf("Exiting the system...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}


