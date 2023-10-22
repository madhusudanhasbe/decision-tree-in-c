#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

#define LOG_FILE "scholarship_log.txt"

// Define a structure to represent a decision tree node
typedef struct Node {
    char *data; // The data (a question or condition) associated with the node
    struct Node *left, *right; // Pointers to left (yes) and right (no) child nodes
} node;

// Define global variables to store minimum requirements and decision tree nodes
float minGpa = 8.0;
float minAttendanceFemale = 80.0;
float minAttendanceMale = 85.0;
int minEligibleYear = 3;
int maxEligibleYear = 4;

node *year, *gpa, *coding, *attendance, *eligible, *not_eligible;

// Function to construct the decision tree
void decision_tree_construction() {
    // Allocate memory for decision tree nodes
    year = (node *)malloc(sizeof(node));
    gpa = (node *)malloc(sizeof(node));
    coding = (node *)malloc(sizeof(node));
    attendance = (node *)malloc(sizeof(node));
    eligible = (node *)malloc(sizeof(node));
    not_eligible = (node *)malloc(sizeof(node));

    // Set data for each node
    year->data = "year";
    gpa->data = "gpa";
    coding->data = "coding";
    attendance->data = "attendance";
    eligible->data = "eligible";
    not_eligible->data = "not eligible";

    // Construct the decision tree by defining the left (yes) and right (no) child nodes
    year->left = gpa;
    year->right = not_eligible;

    gpa->left = coding;
    gpa->right = not_eligible;

    coding->left = attendance;
    coding->right = not_eligible;

    attendance->left = eligible;
    attendance->right = not_eligible;
}

// Function to get a valid integer input within a specified range
int getValidInputInt(const char *prompt, int min, int max) {
    int input;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &input) != 1 || input < min || input > max) {
            printf("Invalid input. Please enter a valid value between %d and %d.\n", min, max);
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
            return input;
        }
    }
}

// Function to get a valid floating-point input within a specified range
float getValidInputFloat(const char *prompt, float min, float max) {
    float input;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &input) != 1 || input < min || input > max) {
            printf("Invalid input. Please enter a valid value between %.1f and %.1f.\n", min, max);
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
            return input;
        }
    }
}

// Function to get a valid string input with a maximum length
void getValidInputString(const char *prompt, char *input, size_t maxLength) {
    while (1) {
        printf("%s", prompt);
        if (fgets(input, maxLength, stdin) == NULL) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n');
        } else {
            input[strcspn(input, "\n")] = '\0'; // Remove the newline character
            if (strlen(input) > 0) {
                return;
            } else {
                printf("Input should not be empty. Please try again.\n");
            }
        }
    }
}

// Function to get a valid yes or no input
int getYesOrNoInput(const char *prompt) {
    char input[10];
    while (1) {
        getValidInputString(prompt, input, sizeof(input));
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]); // Convert the input to lowercase
        }
        if (strcmp(input, "yes") == 0) {
            return 1;
        } else if (strcmp(input, "no") == 0) {
            return 0;
        } else {
            printf("Invalid input. Please enter 'yes' or 'no'.\n");
        }
    }
}

// Function to make scholarship eligibility decisions based on inputs
void decision_making(int in_year, float in_gpa, int in_coding, float in_attendance, char *result, int isFemale) {
    node *ptr = year; // Start the decision process at the "year" node

    // Check if the student's year of study is within the eligible range
    if (!(in_year >= minEligibleYear && in_year <= maxEligibleYear)) {
        printf("You are not eligible for a scholarship as a year %d student.\n", in_year);
        strcpy(result, "Not eligible"); // Set the result
        return;
    }

    // Check if the student's GPA meets the minimum requirement
    if (in_gpa < minGpa) {
        printf("You are not eligible due to a low GPA.\n");
        strcpy(result, "Not eligible"); // Set the result
        return;
    }

    // Check if the student has coding skills
    if (in_coding != 1) {
        printf("You are not eligible because you don't have coding skills.\n");
        strcpy(result, "Not eligible"); // Set the result
        return;
    }

    // Check attendance and gender to make the final decision
    if ((isFemale && in_attendance > minAttendanceFemale) || (!isFemale && in_attendance > minAttendanceMale)) {
        printf("Congratulations! You are eligible for a scholarship.\n");
        strcpy(result, "Eligible"); // Set the result
    } else {
        printf("You are not eligible for a scholarship due to low attendance.\n");
        strcpy(result, "Not eligible"); // Set the result
    }
}

// Function to log the scholarship eligibility results
void logResult(int in_year, float in_gpa, int in_coding, float in_attendance, const char *result) {
    FILE *file = fopen(LOG_FILE, "a"); // Open the log file in append mode
    if (file != NULL) {
        fprintf(file, "Year: %d, GPA: %.2f, Coding: %s, Attendance: %.2f - Result: %s\n", in_year, in_gpa, in_coding ? "yes" : "no", in_attendance, result);
        fclose(file);
    }
}

// Function to view past scholarship eligibility results
void viewPastResults() {
    FILE *file = fopen(LOG_FILE, "r"); // Open the log file in read mode
    if (file != NULL) {
        char line[200];
        int entryCount = 0;
        printf("Past Results:\n");
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            entryCount++;
        }
        fclose(file);

        if (entryCount == 0) {
            printf("No past results available.\n");
        }
    } else {
        printf("No past results available.\n");
    }
}

// Function to delete a specific entry from the log file
void deleteEntry(int entryToDelete) {
    FILE *file = fopen(LOG_FILE, "r"); // Open the log file in read mode
    FILE *tempFile = fopen("temp_log.txt", "w"); // Create a temporary file for rewriting

    if (file != NULL) {
        char line[200];
        int lineCount = 1;
        int deleted = 0;

        while (fgets(line, sizeof(line), file)) {
            if (lineCount != entryToDelete) {
                fprintf(tempFile, "%s", line); // Copy lines to the temporary file (excluding the entry to be deleted)
            } else {
                deleted = 1;
            }
            lineCount++;
        }

        fclose(file);
        fclose(tempFile);

        if (deleted == 0) {
            printf("No entry found at line %d. Nothing deleted.\n", entryToDelete);
        } else {
            remove(LOG_FILE); // Remove the original log file
            rename("temp_log.txt", LOG_FILE); // Rename the temporary file to the original log file
            printf("Entry %d deleted.\n", entryToDelete);
        }
    } else {
        printf("No past results available to delete.\n");
    }
}

// Function to delete all entries in the log file
void deleteAllEntries() {
    FILE *file = fopen(LOG_FILE, "w"); // Open the log file in write mode (clearing its contents)
    if (file != NULL) {
        fclose(file);
    } else {
        printf("No past results available to delete.\n");
    }
}

// Function to check if a file is empty
int isFileEmpty(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file != NULL) {
        char ch = fgetc(file);
        fclose(file);
        return ch == EOF; // If the first character is EOF, the file is empty
    }
    return 1;
}

// Function to clear the console (for Windows systems)
void clearConsole() {
    system("cls");
}

// Function to print the main menu options
void printMenu() {
    printf("Please select an option:\n");
    printf("1. Check Eligibility\n");
    printf("2. View Past Results\n");
    printf("3. Delete Entry\n");
    printf("4. Delete All Entries\n");
    printf("5. Settings\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

// Function to handle the settings menu
void settingsMenu() {
    clearConsole();
    printf("Settings Menu:\n");
    printf("1. Change Minimum GPA (Current: %.2f)\n", minGpa);
    printf("2. Change Minimum Attendance for Females (Current: %.2f)\n", minAttendanceFemale);
    printf("3. Change Minimum Attendance for Males (Current: %.2f)\n", minAttendanceMale);
    printf("4. Change Eligible Year Range (Current: %d-%d)\n", minEligibleYear, maxEligibleYear);
    printf("5. Return to Main Menu\n");

    int choice;
    char confirm;
    do {
        choice = getValidInputInt("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1:
                minGpa = getValidInputFloat("Enter the new minimum GPA: ", 0.0, 10.0);
                printf("Minimum GPA updated to %.2f\n", minGpa);
                break;
            case 2:
                minAttendanceFemale = getValidInputFloat("Enter the new minimum attendance for females: ", 0.0, 100.0);
                printf("Minimum attendance for females updated to %.2f\n", minAttendanceFemale);
                break;
            case 3:
                minAttendanceMale = getValidInputFloat("Enter the new minimum attendance for males: ", 0.0, 100.0);
                printf("Minimum attendance for males updated to %.2f\n", minAttendanceMale);
                break;
            case 4:
                minEligibleYear = getValidInputInt("Enter the new minimum eligible year: ", 1, 4);
                maxEligibleYear = getValidInputInt("Enter the new maximum eligible year: ", minEligibleYear, 4);
                printf("Eligible year range updated to %d-%d\n", minEligibleYear, maxEligibleYear);
                break;
            case 5:
                return;
        }

        printf("Do you want to continue changing settings? (1 for Yes, 0 for No): ");
        while (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
            printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
        }
        while (getchar() != '\n');
    } while (confirm == 1);
}

// main function
int main() {
    decision_tree_construction();

    int in_year;
    int in_coding;
    float in_gpa, in_attendance;
    int isFemale = 0;

    int choice;
    char confirm;

    while (1) {
        clearConsole();
        printf("Welcome to the Scholarship Eligibility Checker\n");
        printMenu();

        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 6) {
            printf("Invalid input. Please select a valid option.\n");
            while (getchar() != '\n');  
            continue; 
        }

        while (getchar() != '\n');

        switch (choice) {
            case 1:
            {
                int isDone = 0;
                while (!isDone) {
                    char genderInput[10];
                    while (1) {
                        printf("Are you male or female? (Enter 'male' or 'female'): ");
                        getValidInputString("", genderInput, sizeof(genderInput));
                        for (int i = 0; genderInput[i]; i++) {
                            genderInput[i] = tolower(genderInput[i]);
                        }
                        if (strcmp(genderInput, "male") == 0) {
                            isFemale = 0;
                            break;
                        }
                        else if (strcmp(genderInput, "female") == 0) {
                            isFemale = 1;
                            break;
                        }
                        else {
                            printf("Invalid input. Please enter 'male' or 'female'.\n");
                        }
                    }

                    in_year = getValidInputInt("In which year are you currently studying? (Enter a number from 1 to 4): ", 1, 4);
                    in_gpa = getValidInputFloat("What is your current GPA: ", 0.0, 10.0);
                    in_coding = getYesOrNoInput("Do you have coding skills? (yes or no): ");
                    in_attendance = getValidInputFloat("What is your current attendance percentage: ", 0.0, 100.0);

                    char result[100];
                    decision_making(in_year, in_gpa, in_coding, in_attendance, result, isFemale);

                    logResult(in_year, in_gpa, in_coding, in_attendance, result);

                    int inputCheck;
                    printf("Do you want to continue checking eligibility? (1 for Yes, 0 for No): ");
                    while ((inputCheck = scanf("%d", &confirm)) != 1 || (confirm != 0 && confirm != 1)) {
                        printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
                        while (getchar() != '\n'); // Clear the input buffer
                    }
                    while (getchar() != '\n'); // Clear the input buffer

                    if (confirm == 0) {
                        isDone = 1;
                    }
                }
            }
            break;

            case 2:
                clearConsole();
                viewPastResults();
                printf("Do you want to continue? (1 for Yes, 0 for No): ");
                while (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                    printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
                }
                while (getchar() != '\n');

                if (confirm == 0) {
                    exit(0);
                }
                break;

            case 3:
                while (1) {
                    clearConsole();
                    if (isFileEmpty(LOG_FILE)) {
                        printf("No past results available to delete.\n");
                    } else {
                        viewPastResults();
                        int entryToDelete;
                        printf("Enter the number of the entry you want to delete (0 to return to the main menu): ");
                        if (scanf("%d", &entryToDelete) == 1) {
                            if (entryToDelete == 0) {
                                break;
                            } else {
                                deleteEntry(entryToDelete);
                            }
                        } else {
                            printf("Invalid input. Entry not deleted.\n");
                        }
                        while (getchar() != '\n');
                    }

                    printf("Do you want to continue? (1 for Yes, 0 for No): ");
                    while (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                        printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
                    }
                    while (getchar() != '\n');

                    if (confirm == 0) {
                        break;
                    }
                }
                break;

            case 4:
                clearConsole();
                if (isFileEmpty(LOG_FILE)) {
                    printf("No past results available to delete.\n");
                } else {
                    printf("Are you sure you want to delete all entries? (y/n): ");
                    scanf(" %c", &confirm);
                    if (confirm == 'y' || confirm == 'Y') {
                        deleteAllEntries();
                        printf("All entries deleted.\n");
                    } else {
                        printf("Deletion canceled.\n");
                    }
                    while (getchar() != '\n');
                }

                printf("Do you want to continue? (1 for Yes, 0 for No): ");
                while (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                    printf("Invalid input. Please enter 1 for Yes or 0 for No: ");
                }
                while (getchar() != '\n');

                if (confirm == 0) {
                    exit(0);
                }
                break;

            case 5:
                settingsMenu();
                break;

            case 6:
                printf("\nThank You for using.");
                exit(0);
        }
    }
    return 0;
}
