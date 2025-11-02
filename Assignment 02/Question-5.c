#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void encodeMessage(char message[]);
void decodeMessage(char message[]);

int main ()
{
    int choice;
    char message[1000];

    do
    {
        printf("\n\n");
        printf("\n\t\t\t############################################################");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t#          TCS MESSAGE ENCODING / DECODING TOOL            #");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t############################################################");
        printf("\n\n");

        printf("\n\n\n---->  MAIN MENU  <----\n");
        printf("\n  >  1. Encode Message");
        printf("\n  >  2. Decode Message");
        printf("\n  >  3. Exit");    
        
        printf("\n\nEnter your choice (between 1-3):  ");
        scanf("%d", &choice);

        switch (choice)
            {
            case 1:
                printf("\n\n-->  Enter Message to Encode:  ");
                scanf(" %[^\n]", message);

                encodeMessage(message);

                printf("\n\n  >  ENCODED MESSAGE:  %s\n\n", message);

                printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
                getch();
                system("cls");
                break;

            case 2:
                printf("\n\n-->  Enter Message to Decode:  ");
                scanf(" %[^\n]", message);

                decodeMessage(message);

                printf("\n\n  >  DECODED MESSAGE:  %s\n\n", message);

                printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
                getch();
                system("cls");
                break;

            case 3:
                break;
            
            default:
                printf("\n\n\n[INAVLID ENTRY] - A number BETWEEN 1 - 3 is REQUIRED!\n");
                printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
                getch();
                system("cls");
                break;
            }   
        }
        while (choice != 3);

    printf("\n\n\n[EXITTING]...");
    printf("\n[PRESS ANYTHING TO CONTINUE..]\n");
    getch();
    return 0;   
}


void encodeMessage (char message[])
{
    int length = strlen(message);
    
    // String Reversal
    for (int i=0 ; i<length/2 ; i++)
    {
        char temp = message[i];
        message[i] = message[length-1-i];
        message[length-1-i] = temp;
    }
    
    // Toggling of 2nd and 5th bits of each character
    for (int i=0 ; i<length ; i++)
    {
        message[i] = message[i] ^ (1 << 1);  // Toggle 2nd bit (bit position 1)
        message[i] = message[i] ^ (1 << 4);  // Toggle 5th bit (bit position 4)
    }
}


void decodeMessage (char message[])
{
    int length = strlen(message);
    
    // Toggling of 2nd and 5th bits of each character
    for (int i=0 ; i<length ; i++)
    {
        message[i] = message[i] ^ (1 << 1);  // Toggle 2nd bit (bit position 1)
        message[i] = message[i] ^ (1 << 4);  // Toggle 5th bit (bit position 4)
    }
    
    // String Reversal
    for (int i=0 ; i<length/2 ; i++)
    {
        char temp = message[i];
        message[i] = message[length-1-i];
        message[length-1-i] = temp;
    }
}