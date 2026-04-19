#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================== STRUCTURES ==================
typedef struct Crew {
    int id;
    char name[50];
    struct Crew* next;
    struct AdjList* adj;
} Crew;

typedef struct AdjList {
    struct Crew* dest;
    struct AdjList* next;
} AdjList;

Crew* head = NULL;

// ================== UTILITY FUNCTIONS ==================
Crew* findCrew(int id) {
    Crew* temp = head;
    while (temp != NULL) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

// ================== SAFE INPUT HELPER ==================
int getValidID(const char* prompt) {
    int id;
    printf("%s", prompt);
    while (scanf("%d", &id) != 1) {
        printf("❌ Enter valid number: ");
        while (getchar() != '\n');  // Clear buffer
    }
    while (getchar() != '\n');  // Clear buffer after valid input
    return id;
}

void getSafeName(char* name) {
    printf("Enter Crew Name: ");
    fgets(name, 49, stdin);
    name[strcspn(name, "\n")] = 0;  // Remove newline
}

// ================== CLEANUP FUNCTION ==================
void cleanup() {
    while (head != NULL) {
        deleteCrew(head->id);
    }
}

// ================== CRUD OPERATIONS ==================

// 🔹 CREATE → Add Crew (FIXED: Duplicate check + Safe input)
void addCrew() {
    Crew* newCrew = (Crew*)malloc(sizeof(Crew));
    
    printf("\nEnter Crew ID: ");
    scanf("%d", &newCrew->id);
    while (getchar() != '\n');  // Clear buffer
    
    // ✅ FIX 2: Duplicate ID check
    if (findCrew(newCrew->id)) {
        printf("❌ Duplicate ID exists!\n");
        free(newCrew);
        return;
    }
    
    // ✅ FIX 1: Safe name input
    getSafeName(newCrew->name);
    
    newCrew->adj = NULL;
    newCrew->next = head;
    head = newCrew;
    
    printf("✅ Crew Added Successfully!\n");
}

// 🔹 READ → Display Graph (PERFECT - No changes)
void display() {
    if (head == NULL) {
        printf("\n⚠ No Crew Data Available\n");
        return;
    }

    Crew* temp = head;
    printf("\n--- Crew Assignment Graph ---\n");

    while (temp != NULL) {
        printf("Crew %d (%s) ➝ ", temp->id, temp->name);
        AdjList* adj = temp->adj;
        while (adj != NULL) {
            printf("%d ", adj->dest->id);
            adj = adj->next;
        }
        printf("\n");
        temp = temp->next;
    }
}

// 🔹 UPDATE → Modify Crew (FIXED: Safe input)
void updateCrew() {
    int id = getValidID("\nEnter Crew ID to Update: ");  // ✅ FIX 4: Safe ID
    
    Crew* temp = findCrew(id);
    if (temp == NULL) {
        printf("❌ Crew Not Found!\n");
        return;
    }
    
    getSafeName(temp->name);  // ✅ FIX 1: Safe name input
    printf("✅ Crew Updated Successfully!\n");
}

// 🔹 DELETE → Remove Crew (PERFECT - No changes)
void deleteCrew() {
    int id = getValidID("\nEnter Crew ID to Delete: ");  // ✅ FIX 4: Safe ID
    
    Crew *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("❌ Crew Not Found!\n");
        return;
    }

    if (prev == NULL) head = temp->next;
    else prev->next = temp->next;

    AdjList* adj = temp->adj;
    while (adj != NULL) {
        AdjList* t = adj;
        adj = adj->next;
        free(t);
    }
    free(temp);
    printf("✅ Crew Deleted Successfully!\n");
}

// 🔹 SEARCH → Find Crew (FIXED: Safe input)
void searchCrew() {
    int id = getValidID("\nEnter Crew ID to Search: ");  // ✅ FIX 4: Safe ID
    
    Crew* found = findCrew(id);
    if (found)
        printf("🔍 Found → ID: %d | Name: %s\n", found->id, found->name);
    else
        printf("❌ Crew Not Found!\n");
}

// ================== GRAPH OPERATION ==================

// Add Assignment (FIXED: Self-loop + Duplicate edge check)
void addAssignment() {
    int id1 = getValidID("\nEnter Source Crew ID: ");      // ✅ FIX 4
    int id2 = getValidID("Enter Destination Crew ID: ");   // ✅ FIX 4
    
    // ✅ FIX 5: Prevent self-loops
    if (id1 == id2) {
        printf("❌ Cannot assign crew to itself!\n");
        return;
    }
    
    Crew* c1 = findCrew(id1);
    Crew* c2 = findCrew(id2);

    if (c1 == NULL || c2 == NULL) {
        printf("❌ Invalid Crew ID(s)\n");
        return;
    }
    
    // ✅ BONUS: Check duplicate edge
    AdjList* check = c1->adj;
    while (check != NULL) {
        if (check->dest->id == id2) {
            printf("❌ Assignment already exists!\n");
            return;
        }
        check = check->next;
    }

    AdjList* newEdge = (AdjList*)malloc(sizeof(AdjList));
    newEdge->dest = c2;
    newEdge->next = c1->adj;
    c1->adj = newEdge;

    printf("✅ Assignment Added!\n");
}

// ================== MAIN MENU ==================
int main() {
    int choice;
    
    while (1) {
        printf("\n====================================\n");
        printf(" ✈ AIRLINE CREW MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Crew (Create)\n");
        printf("2. Delete Crew\n");
        printf("3. Update Crew\n");
        printf("4. Search Crew\n");
        printf("5. Display Graph\n");
        printf("6. Add Assignment\n");
        printf("7. Exit\n");
        printf("====================================\n");

        printf("Enter Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("❌ Invalid Choice!\n");
            while (getchar() != '\n');  // ✅ FIX 4: Clear bad input
            continue;
        }
        while (getchar() != '\n');  // Clear buffer

        switch (choice) {
            case 1: addCrew(); break;
            case 2: deleteCrew(); break;
            case 3: updateCrew(); break;
            case 4: searchCrew(); break;
            case 5: display(); break;
            case 6: addAssignment(); break;
            case 7: 
                cleanup();  // ✅ FIX 3: Memory cleanup
                printf("👋 Exiting...\n"); 
                exit(0);
            default: printf("❌ Invalid Choice!\n");
        }
    }
    return 0;
}