#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int lastUsed; 
};

void addBook(struct Book shelf[], int *size, int capacity, int id, int popularity, int *timeCounter);
int accessBook(struct Book shelf[], int size, int id, int *timeCounter);
int findLeastRecentlyUsed(struct Book shelf[], int size);

int main() {
    int capacity, Q;
    printf("Enter shelf capacity: ");
    if (scanf("%d", &capacity) != 1 || capacity <= 0) {
        printf("Invalid capacity.\n");
        return 1;
    }

    struct Book *shelf = malloc(capacity * sizeof(struct Book));
    if (!shelf) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    int size = 0;          
    int timeCounter = 0;   
    int choice;

    while (1) {
        printf("\n--- Library Shelf Menu ---\n");
        printf("1. ADD x y (Add/Update book with ID x and popularity y)\n");
        printf("2. ACCESS x (Access book with ID x)\n");
        printf("3. VIEW (Show all books)\n");
        printf("4. EXIT\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }

        if (choice == 1) {
            int id, pop;
            printf("Enter book ID: ");
            if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); continue; }
            printf("Enter popularity: ");
            if (scanf("%d", &pop) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); continue; }
            addBook(shelf, &size, capacity, id, pop, &timeCounter);
        } else if (choice == 2) {
            int id;
            printf("Enter book ID to access: ");
            if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); continue; }
            int pop = accessBook(shelf, size, id, &timeCounter);
            if (pop == -1) printf("-1\n");
            else printf("Popularity: %d\n", pop);
        } else if (choice == 3) {
            if (size == 0) printf("Shelf is empty.\n");
            else {
                printf("\nID\tPopularity\tLastUsed\n");
                for (int i = 0; i < size; i++) {
                    printf("%d\t%d\t\t%d\n", shelf[i].id, shelf[i].popularity, shelf[i].lastUsed);
                }
            }
        } else if (choice == 4) {
            free(shelf);
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

void addBook(struct Book shelf[], int *size, int capacity, int id, int popularity, int *timeCounter) {
    (*timeCounter)++;

    for (int i = 0; i < *size; i++) {
        if (shelf[i].id == id) {
            shelf[i].popularity = popularity;
            shelf[i].lastUsed = *timeCounter;
            printf("Book updated.\n");
            return;
        }
    }

    if (*size == capacity) {
        int lruIndex = findLeastRecentlyUsed(shelf, *size);
        printf("Shelf full. Removing least recently accessed book ID %d.\n", shelf[lruIndex].id);
        shelf[lruIndex].id = id;
        shelf[lruIndex].popularity = popularity;
        shelf[lruIndex].lastUsed = *timeCounter;
    } else {
        shelf[*size].id = id;
        shelf[*size].popularity = popularity;
        shelf[*size].lastUsed = *timeCounter;
        (*size)++;
    }
    printf("Book added.\n");
}

int accessBook(struct Book shelf[], int size, int id, int *timeCounter) {
    (*timeCounter)++;
    for (int i = 0; i < size; i++) {
        if (shelf[i].id == id) {
            shelf[i].lastUsed = *timeCounter;
            return shelf[i].popularity;
        }
    }
    return -1;
}

int findLeastRecentlyUsed(struct Book shelf[], int size) {
    int idx = 0;
    for (int i = 1; i < size; i++) {
        if (shelf[i].lastUsed < shelf[idx].lastUsed) idx = i;
    }
    return idx;
}