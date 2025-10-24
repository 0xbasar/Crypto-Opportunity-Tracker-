#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constants and Definitions ---
#define MAX_TITLE_LEN 100
#define MAX_URL_LEN 200
#define MAX_CATEGORY_LEN 50
#define DATA_FILE "opportunities.dat"

// A structure to hold the details of a single opportunity
typedef struct {
    char category[MAX_CATEGORY_LEN];
    char title[MAX_TITLE_LEN];
    char url[MAX_URL_LEN];
} Opportunity;

// --- Global Variables ---
Opportunity *opportunities = NULL; // A dynamic array to store all opportunities
int opportunity_count = 0;       // The current number of opportunities

// --- Function Prototypes ---
void printMenu();
void addOpportunity();
void viewOpportunities();
void saveOpportunities();
void loadOpportunities();
void cleanInputBuffer();

// --- Main Program Logic ---
int main() {
    // Load existing opportunities from the file at the start
    loadOpportunities();

    int choice = 0;
    while (choice != 3) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            cleanInputBuffer(); // Clear the bad input
            continue;
        }
        cleanInputBuffer(); // Always clean buffer after scanf

        switch (choice) {
            case 1:
                addOpportunity();
                break;
            case 2:
                viewOpportunities();
                break;
            case 3:
                printf("Saving and exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    }

    // Save all opportunities to the file before exiting
    saveOpportunities();
    free(opportunities); // Free the allocated memory

    return 0;
}

// --- Function Implementations ---

// Prints the main menu to the console
void printMenu() {
    printf("--- Crypto Opportunity Tracker ---\n");
    printf("1. Add a New Opportunity\n");
    printf("2. View All Opportunities\n");
    printf("3. Save and Exit\n");
    printf("----------------------------------\n");
    printf("Enter your choice: ");
}

// Adds a new opportunity to our dynamic array
void addOpportunity() {
    // Allocate more memory for the new opportunity
    opportunity_count++;
    opportunities = realloc(opportunities, opportunity_count * sizeof(Opportunity));
    if (opportunities == NULL) {
        perror("Error reallocating memory");
        exit(EXIT_FAILURE);
    }

    Opportunity *newOp = &opportunities[opportunity_count - 1];

    printf("Enter Category (e.g., Airdrop, NFT, DeFi): ");
    fgets(newOp->category, MAX_CATEGORY_LEN, stdin);
    newOp->category[strcspn(newOp->category, "\n")] = 0; // Remove newline

    printf("Enter Title: ");
    fgets(newOp->title, MAX_TITLE_LEN, stdin);
    newOp->title[strcspn(newOp->title, "\n")] = 0; // Remove newline

    printf("Enter URL: ");
    fgets(newOp->url, MAX_URL_LEN, stdin);
    newOp->url[strcspn(newOp->url, "\n")] = 0; // Remove newline

    printf("\nOpportunity added successfully!\n");
}

// Displays all currently stored opportunities
void viewOpportunities() {
    printf("\n--- All Tracked Opportunities (%d) ---\n", opportunity_count);
    if (opportunity_count == 0) {
        printf("No opportunities found. Add one first!\n");
        return;
    }

    for (int i = 0; i < opportunity_count; i++) {
        printf("---------------------------------------\n");
        printf("Opportunity #%d\n", i + 1);
        printf("  Category: %s\n", opportunities[i].category);
        printf("  Title:    %s\n", opportunities[i].title);
        printf("  URL:      %s\n", opportunities[i].url);
    }
    printf("---------------------------------------\n");
}

// Saves the entire opportunities array to a binary file
void saveOpportunities() {
    FILE *file = fopen(DATA_FILE, "wb"); // "wb" = write binary
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // First, write the number of records, so we know how many to read back later
    fwrite(&opportunity_count, sizeof(int), 1, file);
    // Then, write the actual data
    fwrite(opportunities, sizeof(Opportunity), opportunity_count, file);

    fclose(file);
}

// Loads opportunities from the binary file into memory
void loadOpportunities() {
    FILE *file = fopen(DATA_FILE, "rb"); // "rb" = read binary
    if (file == NULL) {
        // This is not an error if the file doesn't exist yet
        printf("No previous data file found. Starting fresh.\n");
        return;
    }

    // Read the number of records
    fread(&opportunity_count, sizeof(int), 1, file);

    // Allocate memory to hold the data
    opportunities = malloc(opportunity_count * sizeof(Opportunity));
    if (opportunities == NULL) {
        perror("Error allocating memory for loading");
        exit(EXIT_FAILURE);
    }
    
    // Read the data from the file into our allocated memory
    fread(opportunities, sizeof(Opportunity), opportunity_count, file);

    fclose(file);
    printf("Successfully loaded %d opportunities from %s\n", opportunity_count, DATA_FILE);
}

// A helper function to clear the input buffer (stdin)
// This prevents issues with scanf and fgets
void cleanInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
