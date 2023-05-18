#include <stdio.h>

typedef struct {
    char name[50];
    int id;
    int phone;
} Client;

typedef struct {
    char brand[50];
    char model[50];
    int id;
    char problem[100];
} Laptop;

void addClientRecord() {
    Client client;
    printf("Enter client name: ");
    scanf(" %[^\n]", client.name);
    printf("Enter client ID: ");
    scanf("%d", &client.id);
    printf("Enter client phone number: ");
    scanf("%d", &client.phone);

    FILE *file = fopen("client_details.txt", "w");
    fwrite(&client, sizeof(Client), 1, file);
    fclose(file);
    printf("Client record added successfully.\n");
}

void addLaptopRecord() {
    Laptop laptop;
    printf("Enter laptop brand: ");
    scanf(" %[^\n]", laptop.brand);
    printf("Enter laptop model: ");
    scanf(" %[^\n]", laptop.model);
    printf("Enter laptop ID: ");
    scanf("%d", &laptop.id);
    printf("Enter laptop problem description: ");
    scanf(" %[^\n]", laptop.problem);

    FILE *file = fopen("laptop_details.txt", "w");
    fwrite(&laptop, sizeof(Laptop), 1, file);
    fclose(file);
    printf("Laptop record added successfully.\n");
}

void updateClientRecord() {
    int idToSearch;
    printf("Enter client ID to update: ");
    scanf("%d", &idToSearch);

    FILE *file = fopen("client_details.txt", "r+");
    Client client;

    int found = 0;

    while (fread(&client, sizeof(Client), 1, file) == 1) {
        if (client.id == idToSearch) {
            printf("Enter updated client name: ");
            scanf(" %[^\n]", client.name);
            printf("Enter updated client phone: ");
            scanf("%d", &client.phone);

            fseek(file, -sizeof(Client), SEEK_CUR);
            fwrite(&client, sizeof(Client), 1, file);
            printf("Client record updated successfully.\n");
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Client record with ID %d not found.\n", idToSearch);
    }
}

void updateLaptopRecord() {
    int idToSearch;
    printf("Enter laptop ID to update: ");
    scanf("%d", &idToSearch);

    FILE *file = fopen("laptop_details.txt", "r+");
    Laptop laptop;

    int found = 0;

    while (fread(&laptop, sizeof(Laptop), 1, file) == 1) {
        if (laptop.id == idToSearch) {
            printf("Enter updated laptop brand: ");
            scanf(" %[^\n]", laptop.brand);
            printf("Enter updated laptop model: ");
            scanf(" %[^\n]", laptop.model);
            printf("Enter updated laptop problem description: ");
            scanf(" %[^\n]", laptop.problem);

            fseek(file, -sizeof(Laptop), SEEK_CUR);
            fwrite(&laptop, sizeof(Laptop), 1, file);
            printf("Laptop record updated successfully.\n");
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Laptop record with ID %d not found.\n", idToSearch);
    }
}

void deleteClientRecord() {
    int idToSearch;
    printf("Enter client ID to delete: ");
        scanf("%d", &idToSearch);

    FILE *file = fopen("client_details.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    Client client;
    int found = 0;

    while (fread(&client, sizeof(Client), 1, file) == 1) {
        if (client.id == idToSearch) {
            found = 1;
            continue;
        }
        fwrite(&client, sizeof(Client), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("client_details.txt");
        rename("temp.txt", "client_details.txt");
        printf("Client record with ID %d deleted successfully.\n", idToSearch);
    } else {
        remove("temp.txt");
        printf("Client record with ID %d not found.\n", idToSearch);
    }
}

void deleteLaptopRecord() {
    int idToSearch;
    printf("Enter laptop ID to delete: ");
    scanf("%d", &idToSearch);

    FILE *file = fopen("laptop_details.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    Laptop laptop;
    int found = 0;

    while (fread(&laptop, sizeof(Laptop), 1, file) == 1) {
        if (laptop.id == idToSearch) {
            found = 1;
            continue;
        }
        fwrite(&laptop, sizeof(Laptop), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("laptop_details.txt");
        rename("temp.txt", "laptop_details.txt");
        printf("Laptop record with ID %d deleted successfully.\n", idToSearch);
    } else {
        remove("temp.txt");
        printf("Laptop record with ID %d not found.\n", idToSearch);
    }
}

int main() {
    printf("------LAPTOP REPAIRING SYSTEM------\n");
    printf("1. Add client record\n");
    printf("2. Add laptop record\n");
    printf("3. Update client record\n");
    printf("4. Update laptop record\n");
    printf("5. Delete client record\n");
    printf("6. Delete laptop record\n");

    int user;
    scanf("%d", &user);

    switch (user) {
        case 1:
            addClientRecord();
            break;
        case 2:
            addLaptopRecord();
            break;
        case 3:
            updateClientRecord();
            break;
        case 4:
            updateLaptopRecord();
            break;
        case 5:
            deleteClientRecord();
            break;
        case 6:
            deleteLaptopRecord();
            break;
        default:
            printf("Invalid option. Please choose a valid option.\n");
            break;
    }

    return 0;
}

