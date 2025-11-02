#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLUMNS 5

// Function prototypes
void updateSectorStatus(int grid[ROWS][COLUMNS]);
void querySectorStatus(int grid[ROWS][COLUMNS]);
void runSystemDiagnostic(int grid[ROWS][COLUMNS]);

int main ()
{
    int grid[ROWS][COLUMNS] = {0};  // ALL Set to NULL
    int choice;

    // MAIN MENU
    do
    {
        printf("\n\n");
        printf("\n\t\t\t############################################################");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t#              POWER GRID - MANAGEMENT SYSTEM              #");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t############################################################");
        printf("\n\n");

        printf("\n\n\n---->  MAIN MENU  <----\n");
        printf("\n  >  1. Update Sector Status");
        printf("\n  >  2. Query Sector Status");
        printf("\n  >  3. Run System Diagnostic");
        printf("\n  >  4. Exit");    
        
        printf("\n\nEnter your choice (between 1-4):  ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            updateSectorStatus(grid);
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 2:
            querySectorStatus(grid);
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 3:
            runSystemDiagnostic(grid);
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


void runSystemDiagnostic (int grid[ROWS][COLUMNS]) 
{
    int overloadedCount = 0;
    int maintenanceCount = 0;
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j=0 ; j<COLUMNS ; j++)
        {
            int status = grid[i][j];
            
            if (status & (1 << 1)) overloadedCount++;
            
            if (status & (1 << 2)) maintenanceCount++;
        }
    }
    
    printf("\n\n=================  SYSTEM DIAGNOSTIC REPORT  =================\n\n");
    printf("  >  Total Overloaded Sectors:  %d\n\n", overloadedCount);
    printf("  >  Total Sectors Requiring Maintenance:  %d\n\n", maintenanceCount);
    printf("  >  Total Sectors Scanned:  %d\n\n", ROWS * COLUMNS);
    printf("==============================================================\n\n");
}


void querySectorStatus (int grid[ROWS][COLUMNS])
{
    int row, column;
    
    printf("\n\n--> Enter Sector Coordinates to Query:-\n");
    printf("  >  ROW (0 - %d):  ", ROWS-1);
    scanf("%d", &row);
    printf("  >  COLUMN (0 - %d):  ", COLUMNS-1);
    scanf("%d", &column);
    
    if (row < 0 || row >= ROWS || column < 0 || column >= COLUMNS)
    {
        printf("\n\n[ERROR] - INVALID COORDINATES ENTERED!\n\n");
        return;
    }
    
    int status = grid[row][column];
    
    printf("\n\n=================  [%d][%d] STATUS REPORT  =================\n\n", row, column);
    printf("  >  Power Status:  %s\n", (status & (1 << 0)) ? "ON" : "OFF");
    printf("  >  Overload Warning:  %s\n", (status & (1 << 1)) ? "OVERLOADED" : "Normal");
    printf("  >  Maintenance Required:  %s\n", (status & (1 << 2)) ? "YES" : "NO");
    printf("  >  Raw Status Value:  %d\n\n", status);
    printf("================================================================\n\n");
}


void updateSectorStatus (int grid[ROWS][COLUMNS])
{
    int row, column, flag, action;
    
    printf("\n\n--> Enter Sector Coordinates to Query:-\n");
    printf("  >  ROW (0 - %d):  ", ROWS-1);
    scanf("%d", &row);
    printf("  >  COLUMN (0 - %d):  ", COLUMNS-1);
    scanf("%d", &column);
    
    if (row < 0 || row >= ROWS || column < 0 || column >= COLUMNS)
    {
        printf("\n\n[ERROR] - INVALID COORDINATES ENTERED!\n\n");
        return;
    }
    
    printf("\n\n---->  STATUS FLAG MENU  <----\n");
    printf("  >  1) Power Status\n");
    printf("  >  2) Overload Warning\n");
    printf("  >  3) Maintenance Required\n");
    printf("\nSelect Status Flag to Update:  ");
    scanf("%d", &flag);

    char selectedStatus[30];

    if (flag < 1 || flag > 3)
    {
        printf("\n\n[ERROR] - INVALID SELECTION ENTERED!\n\n");
        return;
    }
    else if (flag == 1) strcpy(selectedStatus, "Power");
    else if (flag == 2) strcpy(selectedStatus, "Overload Warning");
    else if (flag == 3) strcpy(selectedStatus, "Maintenance Required");
    
    int currentStatus = (grid[row][column] >> (flag-1)) & 1;
    printf("\n\n---->  ACTION MENU (Current Status: %s)  <----\n", currentStatus ? "ON - 1" : "OFF - 0");
    printf("  >  1) Set Flag (Set to 1)\n");
    printf("  >  2) Clear Flag (Set to 0)\n");
    printf("\nSelect Action:  ");
    scanf("%d", &action);
    
    if (action == 1)
    {
        // Set the bit: OR with the bit value
        grid[row][column] = grid[row][column] | (1 << (flag-1));
        printf("\n\n   >  Selected (%s) Status Flag SET (1) for Sector: [%d][%d]  <   \n\n", selectedStatus, row, column);
    }
    else if (action == 2)
    {
        // Clear the bit: AND with all bits EXCEPT this one
        grid[row][column] = grid[row][column] & ~(1 << (flag-1));
        printf("\n\n   >  Selected (%s) Status Flag CLEARED (0) for Sector: [%d][%d]  <   \n\n", selectedStatus, row, column);
    }
    else
    {
        printf("\n\n[ERROR] - INVALID ACTION SELECTED!\n\n");
    }
}