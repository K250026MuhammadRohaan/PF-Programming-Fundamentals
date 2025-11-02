#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_BOOKS 100
#define TITLE_LENGTH 50

// Function Declarations
void addNewBook (int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int *bookCount);
void processSale (int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int bookCount);
void generateLowStockReport (int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int bookCount);
int findBookByISBN (int isbns[], int bookCount, int isbn);

int main ()
{
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][TITLE_LENGTH];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];

    int bookCount = 0;
    int choice;

    // MAIN MENU
    do
    {
        printf("\n\n");
        printf("\n\t\t\t############################################################");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t#        LIBERTY BOOKS - INVENTORY MANAGEMENT SYSTEM       #");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t############################################################");
        printf("\n\n");

        printf("\n\n\n---->  MAIN MENU  <----\n");
        printf("\n  >  1. Add New Book");
        printf("\n  >  2. Process a Sale");
        printf("\n  >  3. Generate Low-Stock Report");
        printf("\n  >  4. Exit");    
        
        printf("\n\nEnter your choice (between 1-4):  ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addNewBook(isbns, titles, prices, quantities, &bookCount);
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 2:
            processSale(isbns, titles, prices, quantities, bookCount);
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 3:
            generateLowStockReport(isbns, titles, prices, quantities, bookCount);
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 4:
            break;
        
        default:
            printf("\n\n\n[INAVLID ENTRY] - A number BETWEEN 1 - 4 is REQUIRED!\n");
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;
        }   
    }
    while (choice != 4);

    printf("\n\n\n[EXITTING]...");
    printf("\n[PRESS ANYTHING TO CONTINUE..]\n");
    getch();
    return 0;   
}


// Helper-Function to Find Book by ISBN
int findBookByISBN(int isbns[], int bookCount, int isbn)
{
    for (int i=0 ; i<bookCount ; i++)
    {
        if (isbns[i] == isbn)
        {
            return i;
        }
    }
    return -1;  // Return -1 if not found
}


// Adding New Book Function
void addNewBook (int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int *bookCount)
{
    // Check if MAX BOOK Amount is Reached
    if (*bookCount >= MAX_BOOKS)
    {
        printf("\n\n[ERROR] - MAX BOOK AMOUNT REACHED!\n\n");
        return;
    }
    
    // Entry of ISBN
    int isbn;
    printf("\n\nEnter an ISBN (number):  ");
    scanf("%d", &isbn);
    
    // Check for duplicate ISBN
    if ( findBookByISBN(isbns, *bookCount, isbn) != -1)
    {
        printf("\n\n[ERROR] - Book With ISBN: %d Already EXSTS!\n\n", isbn);
        return;
    }
    
    // Adding Book Details
    isbns[*bookCount] = isbn;
    
    printf("\nEnter the title of your book:  ");
    scanf(" %[^\n]", titles[*bookCount]);
    
    printf("\nEnter the price of your book:  ");
    scanf("%f", &prices[*bookCount]);
    
    printf("\nEnter quantity of books:  ");
    scanf("%d", &quantities[*bookCount]);
    
    (*bookCount)++;
    printf("\n\n[BOOK SUCCESFULLY ADDED TO INVENTORY!]\n\n");
}


// Processing Sale Function
void processSale (int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int bookCount)
{
    // Check if There are no books in Inventory
    if (bookCount == 0)
    {
        printf("\n\n[ERROR] - NO Books in INVENTORY!\n\n");
        return;
    }
    
    int isbn, copies;
    printf("\n\nEnter ISBN of book to sell:  ");
    scanf("%d", &isbn);
    
    // Check if Book Exists
    int index = findBookByISBN (isbns, bookCount, isbn);
    if (index == -1)
    {
        printf("\n\n[ERROR] - Book With ISBN: %d NOT FOUND!\n\n", isbn);
        return;
    }
    
    printf("\n\nEnter Number of Copies to Sell:  ");
    scanf("%d", &copies);
    
    if (copies <= 0)
    {
        printf("\n\n[ERROR] - Number of Copies MUST BE POSITIVE!\n\n");
        return;
    }
    
    if (quantities[index] < copies)
    {
        printf("\n\n[ERROR] - INSUFFICIENT STOCK! Only %d Copies Available!\n\n", quantities[index]);
        return;
    }
    
    // Process the sale
    quantities[index] -= copies;
    float totalAmount = prices[index] * copies;
    
    printf("\n\n[SALE PROCESSED SUCCESSFULLY!]\n\n");

    printf("\n################################################");
    printf("\n#  >  Book Title:  %s", titles[index]);
    printf("\n#  >  Copies sold:  %d", copies);
    printf("\n#  >  Price per copy:  Rs. %.2f", prices[index]);
    printf("\n#  >  Total amount:  Rs. %.2f", totalAmount);
    printf("\n#  >  Remaining stock:  %d Books Left", quantities[index]);
    printf("\n################################################\n\n");
}


// Generating Low Stock Report Function
void generateLowStockReport (int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int bookCount)
{
    // Check if There are no books in Inventory
    if (bookCount == 0)
    {
        printf("\n\n[ERROR] - NO Books in INVENTORY!\n\n");
        return;
    }
    
    int lowStockCount = 0;
    
    printf("\n\n\t------>  LOW STOCK REPORT (where BOOK QUANTITY < 5)  <------\n\n");
    printf("     ISBN\t\tTitle\t\t\tPrice\t\tQuantity\n");
    printf("------------------------------------------------------------------------\n");
    
    for (int i=0 ; i<bookCount ; i++)
    {
        if (quantities[i] < 5)
        {
            printf("  >  %d\t\t%-20s\t$%-10.2f\t%d\n",isbns[i], titles[i], prices[i], quantities[i]);
            lowStockCount++;
        }
    }
    
    if (lowStockCount == 0)
    {
        printf("\n\n[ERROR] - NO Books with LOW STOCK COUNT found in INVENTORY!\n\n");
    }
    else
    {
        printf("------------------------------------------------------------------------\n");
        printf("\n->  TOTAL BOOK TITLES WITH LOW STOCK:  %d Titles\n\n", lowStockCount);
    }
}