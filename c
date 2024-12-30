#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include <io.h>

#define MAX_PATH_LENGTH 256
#define MAX_FILENAME_LENGTH 256

void getDesktopPath(char *path, const char *folderName) {
    strcpy(path, "C:\\Users\\RK\\Desktop\\");
    strcat(path, folderName);
}

int checkExists(const char *path, int isFolder) {
    DWORD attrib = GetFileAttributes(path);
    if (attrib == INVALID_FILE_ATTRIBUTES) return 0;
    return isFolder ? (attrib & FILE_ATTRIBUTE_DIRECTORY) : 1;
}

void createFolder(const char *folderPath) {
    if (_mkdir(folderPath) == 0) {
        printf("Folder created successfully.\n");
    } else {
        printf("Error: Unable to create folder. It might already exist.\n");
    }
}

void createFile(const char *folderPath) {
    char fileName[MAX_FILENAME_LENGTH];
    char filePath[MAX_PATH_LENGTH];

    printf("Enter the file name (with extension): ");
    scanf("%s", fileName);

    snprintf(filePath, sizeof(filePath), "%s\\%s", folderPath, fileName);
    FILE *file = fopen(filePath, "w");
    if (file) {
        printf("File '%s' created successfully.\n", fileName);
        fclose(file);
    } else {
        printf("Error: Unable to create file.\n");
    }
}

void searchFile(const char *folderPath) {
    char fileName[MAX_FILENAME_LENGTH];
    char filePath[MAX_PATH_LENGTH];

    printf("Enter the file name to search: ");
    scanf("%s", fileName);

    snprintf(filePath, sizeof(filePath), "%s\\%s", folderPath, fileName);
    if (checkExists(filePath, 0)) {
        printf("File '%s' found.\n", fileName);
    } else {
        printf("File '%s' not found.\n", fileName);
    }
}

void manageFolder(const char *folderName) {
    char folderPath[MAX_PATH_LENGTH];
    getDesktopPath(folderPath, folderName);

    if (!checkExists(folderPath, 1)) {
        printf("Folder '%s' does not exist. Please create it first.\n", folderName);
        return;
    }

    while (1) {
        int action;
        printf("\n1. Insert File\n2. Search File\n3. Exit\nEnter your choice: ");
        scanf("%d", &action);

        if (action == 1) {
            createFile(folderPath);
        } else if (action == 2) {
            searchFile(folderPath);
        } else if (action == 3) {
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
}

void searchFolder() {
    char folderName[MAX_FILENAME_LENGTH];
    char folderPath[MAX_PATH_LENGTH];

    printf("Enter the folder name to search: ");
    scanf("%s", folderName);

    getDesktopPath(folderPath, folderName);
    if (checkExists(folderPath, 1)) {
        printf("Folder '%s' found.\n", folderName);
    } else {
        printf("Folder '%s' not found.\n", folderName);
    }
}

int main() {
    while (1) {
        int choice;
        char folderName[MAX_FILENAME_LENGTH];

        printf("\n--- Folder and File Manager ---\n");
        printf("1. Create Folder\n");
        printf("2. Manage Folder\n");
        printf("3. Search Folder\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter folder name to create: ");
            scanf("%s", folderName);

            char folderPath[MAX_PATH_LENGTH];
            getDesktopPath(folderPath, folderName);

            createFolder(folderPath);
        } else if (choice == 2) {
            printf("Enter folder name to manage: ");
            scanf("%s", folderName);
            manageFolder(folderName);
        } else if (choice == 3) {
            searchFolder();
        } else if (choice == 4) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
