#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function prototypes
void push(int stack[], int *top);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main ()
{
    int stack[MAX_SIZE];
    int top = -1;

    int choice;

    do
    {
        printf("\n\n");
        printf("\n\t\t\t############################################################");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t#               STACK IMPLEMENTATION SYSTEM                #");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t############################################################");
        printf("\n\n");

        printf("\n\n\n---->  MAIN MENU  <----\n");
        printf("\n  >  1. Push Element In Stack");
        printf("\n  >  2. Pop Element Out of Stack");
        printf("\n  >  3. Peep Element on Top of Stack");
        printf("\n  >  4. Display ALL Elements of Stack");
        printf("\n  >  5. Exit");    
        
        printf("\n\nEnter your choice (between 1-5):  ");
        scanf("%d", &choice);

        switch (choice)
            {
            case 1:
                push(stack, &top);
                printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
                getch();
                system("cls");
                break;

            case 2:
                pop(stack, &top);
                printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
                getch();
                system("cls");
                break;

            case 3:
                peek(stack, top);
                printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
                getch();
                system("cls");
                break;

            case 4:
                display(stack, top);
                printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
                getch();
                system("cls");
                break;

            case 5:
                break;
            
            default:
                printf("\n\n\n[INAVLID ENTRY] - A number BETWEEN 1 - 5 is REQUIRED!\n");
                printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
                getch();
                system("cls");
                break;
            }   
        }
        while (choice != 5);

    printf("\n\n\n[EXITTING]...");
    printf("\n[PRESS ANYTHING TO CONTINUE..]\n");
    getch();
    return 0;   
}


void display (int stack[], int top)
{
    if (top == -1)
    {
        printf("\n\n[ERROR] - STACK IS EMPTY!\n\n");
        return;
    }
    
    printf("\n\n---->  Stack Elements (Top to Bottom):  <----\n");
    
    for (int i=top ; i>=0 ; i--)
    {
        printf("\n  >  %d ", stack[i]);
    }
    printf("\n\n---------------------------------------------\n\n");
}


void peek (int stack[], int top)
{
    if (top == -1)
    {
        printf("\n\n[ERROR] - STACK IS EMPTY!\n\n");
        return;
    }
    
    printf("\n\n-->  Top Element In Stack is:  %d  <--\n\n", stack[top]);
}


void push (int stack[], int *top)
{
    if (*top == MAX_SIZE-1)
    {
        printf("\n\n[ERROR] - STACK OVERFLOW! - CANNOT PUSH ELEMENT!\n\n");
        return;
    }
    
    int element;
    printf("\n\n-->  Enter Element to Push in Stack:  ");
    scanf("%d", &element);
    
    (*top)++;
    stack[*top] = element;

    printf("\n\n  >  [ELEMENT %d PUSHED SUCCESSFULLY]\n\n", element);
}


void pop (int stack[], int *top)
{
    if (*top == -1)
    {
        printf("\n\n[ERROR] - STACK UNDERFLOW! - CANNOT POP ELEMENT!\n\n");
        return;
    }
    
    printf("\n\n  >  [ELEMENT %d POPPED SUCCESSFULLY]\n\n", stack[*top]);
    (*top)--;
}