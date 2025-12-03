#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char name[100];
    char batch[32];
    char membership[16];
    char regDate[11];
    char dob[11];
    char interest[16];
} Student;

Student *students = NULL;
size_t studentCount = 0;

int isValidDate(const char *d) {
    if (!d) return 0;
    if (strlen(d) != 10) return 0;
    if (d[4] != '-' || d[7] != '-') return 0;
    for (int i = 0; i < 10; i++) {
        if (i==4 || i==7) continue;
        if (d[i] < '0' || d[i] > '9') return 0;
    }
    return 1;
}

int findStudentIndexByID(int id) {
    for (size_t i = 0; i < studentCount; i++) if (students[i].id == id) return (int)i;
    return -1;
}

void freeDatabaseMemory() {
    free(students);
    students = NULL;
    studentCount = 0;
}

int loadDatabase(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return 0;
    freeDatabaseMemory();
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size <= 0) { fclose(f); return 1; }
    rewind(f);
    size_t recs = (size_t)(size / sizeof(Student));
    students = malloc(recs * sizeof(Student));
    if (!students) { fclose(f); fprintf(stderr, "Memory allocation failed while loading database\n"); return 0; }
    size_t read = fread(students, sizeof(Student), recs, f);
    if (read != recs) {
        freeDatabaseMemory();
        fclose(f);
        fprintf(stderr, "File read error\n");
        return 0;
    }
    studentCount = recs;
    fclose(f);
    return 1;
}

int saveDatabase(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) { fprintf(stderr, "Error: Cannot open file %s for writing\n", filename); return 0; }
    if (studentCount > 0) {
        size_t written = fwrite(students, sizeof(Student), studentCount, f);
        if (written != studentCount) { fclose(f); fprintf(stderr, "Error: Write failed\n"); return 0; }
    }
    fclose(f);
    return 1;
}

int addStudent(Student s, const char *filename) {
    if (findStudentIndexByID(s.id) != -1) { printf("Duplicate Student ID. Registration aborted.\n"); return 0; }
    Student *tmp = realloc(students, (studentCount + 1) * sizeof(Student));
    if (!tmp) { fprintf(stderr, "Memory allocation failed while adding student\n"); return 0; }
    students = tmp;
    students[studentCount] = s;
    studentCount++;
    FILE *f = fopen(filename, "ab");
    if (!f) { fprintf(stderr, "Error: Cannot open file %s for appending\n", filename); return 0; }
    size_t written = fwrite(&s, sizeof(Student), 1, f);
    fclose(f);
    if (written != 1) { fprintf(stderr, "Error: Failed to append record to file\n"); return 0; }
    return 1;
}

int updateStudent(int studentID, const char *filename) {
    int idx = findStudentIndexByID(studentID);
    if (idx == -1) { printf("Student ID %d not found.\n", studentID); return 0; }
    printf("Current Batch: %s\n", students[idx].batch);
    printf("Enter new batch (CS, SE, Cyber Security, AI) or press Enter to keep: ");
    char buf[128];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = 0;
        strncpy(students[idx].batch, buf, sizeof(students[idx].batch)-1);
        students[idx].batch[sizeof(students[idx].batch)-1] = '\0';
    }
    printf("Current Membership: %s\n", students[idx].membership);
    printf("Enter new membership (IEEE or ACM) or press Enter to keep: ");
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = 0;
        strncpy(students[idx].membership, buf, sizeof(students[idx].membership)-1);
        students[idx].membership[sizeof(students[idx].membership)-1] = '\0';
    }
    if (!saveDatabase(filename)) { fprintf(stderr, "Error saving database after update\n"); return 0; }
    printf("Student updated and saved.\n");
    return 1;
}

int deleteStudent(int studentID, const char *filename) {
    int idx = findStudentIndexByID(studentID);
    if (idx == -1) { printf("Student ID %d not found.\n", studentID); return 0; }
    for (size_t i = idx; i + 1 < studentCount; i++) students[i] = students[i+1];
    studentCount--;
    if (studentCount == 0) {
        free(students);
        students = NULL;
    } else {
        Student *tmp = realloc(students, studentCount * sizeof(Student));
        if (tmp) students = tmp;
    }
    if (!saveDatabase(filename)) { fprintf(stderr, "Error saving database after deletion\n"); return 0; }
    printf("Student deleted and database saved.\n");
    return 1;
}

void displayStudent(const Student *s) {
    printf("ID: %d\nName: %s\nBatch: %s\nMembership: %s\nRegistration Date: %s\nDOB: %s\nInterest: %s\n-------------------------\n",
           s->id, s->name, s->batch, s->membership, s->regDate, s->dob, s->interest);
}

void viewAllStudents() {
    if (studentCount == 0) { printf("No records found.\n"); return; }
    for (size_t i = 0; i < studentCount; i++) displayStudent(&students[i]);
}

void generateBatchReport() {
    char batchQ[32];
    char memQ[16];
    printf("Enter batch to filter (CS, SE, Cyber Security, AI or ALL): ");
    if (!fgets(batchQ, sizeof(batchQ), stdin)) return;
    batchQ[strcspn(batchQ, "\n")] = 0;
    printf("Enter membership filter (IEEE, ACM, Both, or ALL): ");
    if (!fgets(memQ, sizeof(memQ), stdin)) return;
    memQ[strcspn(memQ, "\n")] = 0;
    int found = 0;
    for (size_t i = 0; i < studentCount; i++) {
        int batchMatch = 0;
        int memMatch = 0;
        if (strcasecmp(batchQ, "ALL") == 0 || strlen(batchQ) == 0) batchMatch = 1;
        else if (strcasecmp(students[i].batch, batchQ) == 0) batchMatch = 1;
        if (strcasecmp(memQ, "ALL") == 0 || strlen(memQ) == 0) memMatch = 1;
        else if (strcasecmp(memQ, "Both") == 0) {
            if (strcasecmp(students[i].interest, "Both") == 0 || strcasecmp(students[i].interest, "IEEE") == 0 || strcasecmp(students[i].interest, "ACM") == 0) memMatch = 1;
        } else {
            if (strcasecmp(students[i].membership, memQ) == 0) memMatch = 1;
        }
        if (batchMatch && memMatch) { displayStudent(&students[i]); found = 1; }
    }
    if (!found) printf("No matching records found.\n");
}

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readLineTrim(char *buf, size_t sz) {
    if (!fgets(buf, sz, stdin)) return 0;
    buf[strcspn(buf, "\n")] = 0;
    return 1;
}

void registerStudentMenu(const char *filename) {
    Student s;
    char buf[128];
    printf("Enter Student ID (integer): ");
    if (scanf("%d", &s.id) != 1) { clearStdin(); printf("Invalid ID input.\n"); return; }
    clearStdin();
    if (findStudentIndexByID(s.id) != -1) { printf("Student ID already exists.\n"); return; }
    printf("Enter Full Name: ");
    if (!readLineTrim(s.name, sizeof(s.name))) return;
    printf("Enter Batch (CS, SE, Cyber Security, AI): ");
    if (!readLineTrim(s.batch, sizeof(s.batch))) return;
    printf("Enter Membership Type (IEEE or ACM): ");
    if (!readLineTrim(s.membership, sizeof(s.membership))) return;
    printf("Enter Registration Date (YYYY-MM-DD): ");
    if (!readLineTrim(s.regDate, sizeof(s.regDate))) return;
    if (!isValidDate(s.regDate)) { printf("Invalid registration date format.\n"); return; }

    clearStdin();
    
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    if (!readLineTrim(s.dob, sizeof(s.dob))) return;
    if (!isValidDate(s.dob)) { printf("Invalid DOB format.\n"); return; }
    printf("Enter Interest (IEEE, ACM, Both): ");
    if (!readLineTrim(s.interest, sizeof(s.interest))) return;
    if (addStudent(s, filename)) printf("Student registered successfully.\n");
    else printf("Failed to register student.\n");
}

void stressTest(const char *filename) {
    srand((unsigned)time(NULL));
    int toAdd = 25;
    const char *batches[] = {"CS","SE","Cyber Security","AI"};
    const char *members[] = {"IEEE","ACM"};
    const char *interests[] = {"IEEE","ACM","Both"};
    int startID = 1000;
    for (int i = 0; i < toAdd; i++) {
        Student s;
        int candidate;
        do {
            candidate = startID + rand() % 10000;
        } while (findStudentIndexByID(candidate) != -1);
        s.id = candidate;
        snprintf(s.name, sizeof(s.name), "Student_%d", s.id);
        strncpy(s.batch, batches[rand() % 4], sizeof(s.batch)-1);
        s.batch[sizeof(s.batch)-1]=0;
        strncpy(s.membership, members[rand()%2], sizeof(s.membership)-1);
        s.membership[sizeof(s.membership)-1]=0;
        int y = 1995 + rand()%10;
        int m = 1 + rand()%12;
        int d = 1 + rand()%28;
        snprintf(s.dob, sizeof(s.dob), "%04d-%02d-%02d", y, m, d);
        int ry = 2022 + rand()%4;
        int rm = 1 + rand()%12;
        int rd = 1 + rand()%28;
        snprintf(s.regDate, sizeof(s.regDate), "%04d-%02d-%02d", ry, rm, rd);
        strncpy(s.interest, interests[rand()%3], sizeof(s.interest)-1);
        s.interest[sizeof(s.interest)-1]=0;
        addStudent(s, filename);
    }
    int delCount = 8;
    for (int i = 0; i < delCount && studentCount>0; i++) {
        int idx = rand() % studentCount;
        int id = students[idx].id;
        deleteStudent(id, filename);
    }
    int updCount = 6;
    for (int i = 0; i < updCount && studentCount>0; i++) {
        int idx = rand() % studentCount;
        int id = students[idx].id;
        strncpy(students[idx].batch, batches[rand()%4], sizeof(students[idx].batch)-1);
        students[idx].batch[sizeof(students[idx].batch)-1]=0;
        strncpy(students[idx].membership, members[rand()%2], sizeof(students[idx].membership)-1);
        students[idx].membership[sizeof(students[idx].membership)-1]=0;
    }
    saveDatabase(filename);
    printf("Stress test completed. Total records: %zu\n", studentCount);
}

int main() {
    const char *filename = "members.dat";
    if (!loadDatabase(filename)) {
        printf("No existing database loaded or error occurred. Starting with empty database.\n");
    } else {
        printf("%zu records loaded from %s\n", studentCount, filename);
    }
    int choice = 0;
    while (1) {
        printf("\nMenu:\n1. Register a new student\n2. Update membership type or batch\n3. Delete a student registration\n4. View all registrations\n5. Generate batch-wise reports\n6. Stress test (auto add/update/delete)\n7. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) { clearStdin(); printf("Invalid input\n"); continue; }
        clearStdin();
        if (choice == 1) {
            registerStudentMenu(filename);
        } else if (choice == 2) {
            printf("Enter Student ID to update: ");
            int id;
            if (scanf("%d", &id) != 1) { clearStdin(); printf("Invalid input\n"); continue; }
            clearStdin();
            updateStudent(id, filename);
        } else if (choice == 3) {
            printf("Enter Student ID to delete: ");
            int id;
            if (scanf("%d", &id) != 1) { clearStdin(); printf("Invalid input\n"); continue; }
            clearStdin();
            deleteStudent(id, filename);
        } else if (choice == 4) {
            viewAllStudents();
        } else if (choice == 5) {
            generateBatchReport();
        } else if (choice == 6) {
            stressTest(filename);
        } else if (choice == 7) {
            if (!saveDatabase(filename)) fprintf(stderr, "Warning: Failed to save database on exit\n");
            freeDatabaseMemory();
            printf("Exiting. Database saved.\n");
            break;
        } else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}