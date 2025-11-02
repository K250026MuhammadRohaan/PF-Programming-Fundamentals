#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRODUCTS 250
#define NAME_LENGTH 50
#define CNIC_LENGTH 20
#define PROMO_CODE "Eid2025"

// Function Declarations
void customerInformation (char name[], char cnic[]);
void displayInventory (int productCodes[], int quantities[], float prices[], int productCount);
void updateInventory (int productCodes[], int quantities[], int productCount, int productCode, int quantitySold);
void addItemToCart (int cart[], int cartQuantities[], int *cartCount, int productCodes[], int quantities[], float prices[], int productCount);
void displayTotalBill (int cart[], int cartQuantities[], int cartCount, int productCodes[], float prices[], int productCount);
void showInvoice (char name[], char cnic[], int cart[], int cartQuantities[], int cartCount, int productCodes[], float prices[], int productCount, float discount);


int main ()
{
    // Inventory Arrays
    int productCodes[MAX_PRODUCTS] = {001, 002, 003, 004};
    int quantities[MAX_PRODUCTS] = {50, 10, 20, 8};
    float prices[MAX_PRODUCTS] = {100, 200, 300, 150};
    int productCount = 4;
    
    // Customer Information
    char customerName[NAME_LENGTH];
    char customerCNIC[CNIC_LENGTH];
    
    // Cart Arrays
    int cart[MAX_PRODUCTS];
    int cartQuantities[MAX_PRODUCTS];
    int cartCount = 0;
    
    int choice;
    bool customerInfoEntered = 0;

    // MAIN MENU
    do
    {
        printf("\n\n");
        printf("\n\t\t\t############################################################");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t#         SUPERMARKET - INVENTORY MANAGEMENT SYSTEM        #");
        printf("\n\t\t\t#                                                          #");
        printf("\n\t\t\t############################################################");
        printf("\n\n");

        printf("\n\n\n---->  MAIN MENU  <----\n");
        printf("\n  >  1. Enter Customer Information");
        printf("\n  >  2. Display Inventory");
        printf("\n  >  3. Add Item to Cart");
        printf("\n  >  4. Display Total Bill");
        printf("\n  >  5. Show Invoice");
        printf("\n  >  6. Exit");    
        
        printf("\n\nEnter your choice (between 1-6):  ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (customerInfoEntered == 0)
            {
                customerInformation(customerName, customerCNIC);
                customerInfoEntered = 1;
            }
            else
            {
                printf("\n\n[ERROR] - Customer Info ALREADY ENTERED!\n\n");
            }

            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 2:
            if (customerInfoEntered == 1)
            {
                displayInventory(productCodes, quantities, prices, productCount);
            }
            else
            {
                printf("\n\n[ERROR] - Customer Info NOT ENTERED - Please ENTER Customer Info FIRST!\n\n");
            }
            
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 3:
            if (customerInfoEntered == 1)
            {
                addItemToCart(cart, cartQuantities, &cartCount, productCodes, quantities, prices, productCount);
            }
            else
            {
                printf("\n\n[ERROR] - Customer Info NOT ENTERED - Please ENTER Customer Info FIRST!\n\n");
            }
            
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 4:
            if (customerInfoEntered && cartCount > 0)
            {
                displayTotalBill(cart, cartQuantities, cartCount, productCodes, prices, productCount);
            }
            else if (!customerInfoEntered)
            {
                printf("\n\n[ERROR] - Customer Info NOT ENTERED - Please ENTER Customer Info FIRST!\n\n");
            }
            else
            {
                printf("\n\n[ERROR] - CART IS EMPTY - Please ADD Items to Cart FIRST!\n\n");
            }
            
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 5:
            if (customerInfoEntered && cartCount > 0)
            {
                showInvoice(customerName, customerCNIC, cart, cartQuantities, cartCount, productCodes, prices, productCount, 0.0);
            }
            else if (!customerInfoEntered)
            {
                printf("\n\n[ERROR] - Customer Info NOT ENTERED - Please ENTER Customer Info FIRST!\n\n");
            }
            else
            {
                printf("\n\n[ERROR] - CART IS EMPTY - Please ADD Items to Cart FIRST!\n\n");
            }
            
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;

        case 6:
            break;
        
        default:
            printf("\n\n\n[INAVLID ENTRY] - A number BETWEEN 1 - 6 is REQUIRED!\n");
            printf("\n[PRESS ANYTHING TO RETURN TO MENU..]");
            getch();
            system("cls");
            break;
        }   
    }
    while (choice != 6);

    printf("\n\n\n[EXITTING]...");
    printf("\n[PRESS ANYTHING TO CONTINUE..]\n");
    getch();
    return 0;   
}


// Customer Information Entry Function
void customerInformation (char name[], char cnic[])
{
    printf("\n\nEnter Customer Name:  ");
    scanf(" %[^\n]", name);
    
    printf("\nEnter Customer CNIC:  ");
    scanf(" %[^\n]", cnic);
    
    printf("\n\n[CUSTOMER INFORMATION SUCCESSFULLY SAVED!]\n\n");
}


// Display Inventory Function
void displayInventory (int productCodes[], int quantities[], float prices[], int productCount)
{
    printf("\n\n============================================================");
    printf("\nProduct Code\tQuantity in Stock\tPrice per Product\n");
    printf("------------------------------------------------------------\n");
    
    for (int i=0 ; i<productCount ; i++)
    {
        printf("%03d\t\t%d\t\t\t%.2f\n", productCodes[i], quantities[i], prices[i]);
    }
    printf("============================================================\n\n");
}


// Adding Item to Cart Function
void addItemToCart (int cart[], int cartQuantities[], int *cartCount, int productCodes[], int quantities[], float prices[], int productCount)
{
    int productCode;
    displayInventory(productCodes, quantities, prices, productCount);
    
    // Enter Product Code to Add
    printf("\nEnter Product Code to add to cart:  ");
    scanf("%d", &productCode);

    // Check if Product is Found (1/2)
    int found = 0;
    int productIndex = -1;

    for (int i=0 ; i<productCount ; i++)
    {
        if (productCodes[i] == productCode)
        {
            found = 1;
            productIndex = i;
            break;
        }
    }
    
    // Check if Product is Found (2/2)
    if (!found)
    {
        printf("\n\n[ERROR] - Product NOT FOUND!\n\n");
        return;
    }
    
    // Enter Quantity of Product to Add
    int quantity;
    printf("\nEnter Quantity of Product:  ");
    scanf("%d", &quantity);
    
    // Check if Quantity is 0 or -ve
    if (quantity <= 0)
    {
        printf("\n\n[ERROR] - Quantity Number MUST BE POSITIVE!\n\n");
        return;
    }
    
    // Check if Entered Quantity is greater than Stock Available
    if (quantity > quantities[productIndex])
    {
        printf("\n\n[ERROR] - INSUFFICIENT Quantity Entered! Only %d is Available in STOCK!\n\n", quantities[productIndex]);
        return;
    }
    
    // Add Product to cart
    cart[*cartCount] = productCode;
    cartQuantities[*cartCount] = quantity;
    (*cartCount)++;
    
    // Run Update Inventory Function
    updateInventory(productCodes, quantities, productCount, productCode, quantity);
    
    printf("\n\n[ITEM ADDED TO CART SUCCESSFULLY!]\n\n");
}


// Update Inventory Function
void updateInventory (int productCodes[], int quantities[], int productCount, int productCode, int quantitySold)
{
    for (int i=0 ; i<productCount ; i++)
    {
        if (productCodes[i] == productCode)
        {
            quantities[i] -= quantitySold;
            break;
        }
    }
}


// Display Total Bill Function
void displayTotalBill (int cart[], int cartQuantities[], int cartCount, int productCodes[], float prices[], int productCount)
{
    float total = 0;
    
    printf("\n");
    printf("\n############################################################");
    printf("\n#                         YOUR CART                        #");
    printf("\n############################################################");
    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("\n        Product\tQuantity\tPrice\tSubtotal\n");
    printf("------------------------------------------------------------\n");
    
    for (int i=0 ; i<cartCount ; i++)
    {
        for (int j=0 ; j<productCount ; j++)
        {
            if (cart[i] == productCodes[j])
            {
                float subtotal = prices[j] * cartQuantities[i];
                total += subtotal;

                printf("     >  %03d\t%d\t\t%.2f\t%.2f\n", cart[i], cartQuantities[i], prices[j], subtotal);
                break;
            }
        }
    }
    printf("------------------------------------------------------------\n");
    printf("->  TOTAL: Rs. %.2f\n", total);
    printf("------------------------------------------------------------\n");
    
    // Promo code check
    char promo[20];
    char applyDiscount;
    
    printf("\n\n->  Do you have a Promo Code? (y/n):  ");
    scanf(" %c", &applyDiscount);
    
    float discount = 0.0;
    
    if (applyDiscount == 'y' || applyDiscount == 'Y')
    {
        printf(">  Enter Promo Code:  ");
        scanf(" %[^\n]", promo);
        
        if (strcmp(promo, PROMO_CODE) == 0)
        {
            discount = total * 0.25;
            printf("\n\n->  Promo Code Applied! Added 25%% discount:  -%.2f Rupees\n", discount);
            
        }
        else printf("\n\nInvalid Promo Code!\n");
    }
    else printf("\n\nNO Discount Added to TOTAL!\n");

    printf("\n\n\n----->  Final Amount After Discount:  Rs. %.2f  <-----\n\n", total - discount);
}


// Show Invoice Function
void showInvoice (char name[], char cnic[], int cart[], int cartQuantities[], int cartCount, int productCodes[], float prices[], int productCount, float discount)
{
    float total = 0.0;
    
    printf("\n");
    printf("\n############################################################");
    printf("\n#                       YOUR INVOICE                       #");
    printf("\n############################################################");
    printf("\n\n");
    printf("Customer Name:  %s\n", name);
    printf("Customer CNIC:  %s\n", cnic);
    printf("\n------------------------------------------------------------");
    printf("\n                --->  Items Purchased  <---                 \n");
    printf("------------------------------------------------------------\n");
    printf("        Product\tQuantity\tPrice\tSubtotal\n");
    printf("------------------------------------------------------------\n");
    
    for (int i=0 ; i<cartCount ; i++)
    {
        for (int j=0 ; j<productCount ; j++)
        {
            if (cart[i] == productCodes[j])
            {
                float subtotal = prices[j] * cartQuantities[i];
                total += subtotal;
                printf("     >  %03d\t%d\t\t%.2f\t%.2f\n", cart[i], cartQuantities[i], prices[j], subtotal);
                break;
            }
        }
    }
    
    printf("------------------------------------------------------------\n");
    printf("\n[O]  Total without discount: Rs. %.2f\n", total);
    
    // Apply promo code discount
    char promo[20];
    char applyDiscount;
    
    printf("\n\n->  Do you have a Promo Code? (y/n):  ");
    scanf(" %c", &applyDiscount);
    
    float finalDiscount = 0.0;
    
    if (applyDiscount == 'y' || applyDiscount == 'Y')
    {
        printf(">  Enter Promo Code:  ");
        scanf(" %[^\n]", promo);
        
        if (strcmp(promo, PROMO_CODE) == 0)
        {
            discount = total * 0.25;
            printf("\n\n->  Promo Code Applied! Added 25%% discount:  -%.2f Rupees\n", discount);
            
        }
        else printf("\n\nInvalid Promo Code!\n");
    }
    else printf("\n\nNO Discount Added to TOTAL!\n");
    
    printf("[O]  Total After Discount: Rs. %.2f\n\n", total - finalDiscount);
    printf("############################################################\n");
}