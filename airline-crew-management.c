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
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return id;
}

void getSafeName(char* name) {
    printf("Enter Crew Name: ");
    fgets(name, 49, stdin);
    name[strcspn(name, "\n")] = 0;
}

// ================== CLEANUP FUNCTION ==================
void cleanup() {
    while (head != NULL) {
        Crew* current = head;
        head = head->next;
        
        // Free adjacency list
        AdjList* adj = current->adj;
        while (adj != NULL) {
            AdjList* temp = adj;
            adj = adj->next;
            free(temp);
        }
        free(current);
    }
}

// ================== CRUD OPERATIONS ==================

// 🔹 CREATE → Add Crew (✅ FIXED: Safe input + Duplicate check)
void addCrew() {
    Crew* newCrew = (Crew*)malloc(sizeof(Crew));
    newCrew->id = getValidID("\nEnter Crew ID: ");  // ✅ FIXED: Safe input
    
    if (findCrew(newCrew->id)) {
        printf("❌ Duplicate ID exists!\n");
        free(newCrew);
        return;
    }
    
    getSafeName(newCrew->name);
    newCrew->adj = NULL;
    newCrew->next = head;
    head = newCrew;
    
    printf("✅ Crew Added Successfully!\n");
}

// 🔹 READ → Display Graph (✅ PERFECT)
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
        if (adj == NULL) printf("No assignments");
        while (adj != NULL) {
            printf("%d ", adj->dest->id);
            adj = adj->next;
        }
        printf("\n");
        temp = temp->next;
    }
}

// 🔹 UPDATE → Modify Crew (✅ FIXED)
void updateCrew() {
    int id = getValidID("\nEnter Crew ID to Update: ");
    
    Crew* temp = findCrew(id);
    if (temp == NULL) {
        printf("❌ Crew Not Found!\n");
        return;
    }
    
    getSafeName(temp->name);
    printf("✅ Crew Updated Successfully!\n");
}

// 🔹 DELETE → Remove Crew (✅ FULLY FIXED)
void deleteCrew(int targetId) {
    // Find and remove from main list
    Crew *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != targetId) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("❌ Crew Not Found!\n");
        return;
    }

    // Remove from linked list
    if (prev == NULL) head = temp->next;
    else prev->next = temp->next;

    // Free this crew's adjacency list
    AdjList* adj = temp->adj;
    while (adj != NULL) {
        AdjList* t = adj;
        adj = adj->next;
        free(t);
    }
    
    // Remove reverse edges (clean graph)
    Crew* otherCrew = head;
    while (otherCrew != NULL) {
        AdjList* edge = otherCrew->adj;
        AdjList* prevEdge = NULL;
        while (edge != NULL) {
            if (edge->dest->id == targetId) {
                if (prevEdge == NULL) {
                    otherCrew->adj = edge->next;
                } else {
                    prevEdge->next = edge->next;
                }
                AdjList* toFree = edge;
                edge = edge->next;
                free(toFree);
                break;
            }
            prevEdge = edge;
            edge = edge->next;
        }
        otherCrew = otherCrew->next;
    }
    
    free(temp);
    printf("✅ Crew Deleted Successfully!\n");
}

// Wrapper for menu
void deleteCrewMenu() {
    int id = getValidID("\nEnter Crew ID to Delete: ");
    deleteCrew(id);
}

// 🔹 SEARCH → Find Crew (✅ FIXED)
void searchCrew() {
    int id = getValidID("\nEnter Crew ID to Search: ");
    
    Crew* found = findCrew(id);
    if (found) {
        printf("🔍 Found → ID: %d | Name: %s\n", found->id, found->name);
        // Show assignments
        printf("Assignments: ");
        AdjList* adj = found->adj;
        if (adj == NULL) printf("None");
        while (adj != NULL) {
            printf("%d ", adj->dest->id);
            adj = adj->next;
        }
        printf("\n");
    } else {
        printf("❌ Crew Not Found!\n");
    }
}

// ================== GRAPH OPERATIONS ==================

// Add Assignment (✅ FIXED: All checks)
void addAssignment() {
    if (head == NULL) {
        printf("❌ No crews available. Add crew first!\n");
        return;
    }
    
    int id1 = getValidID("\nEnter Source Crew ID: ");
    int id2 = getValidID("Enter Destination Crew ID: ");
    
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
    
    // Check duplicate edge
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

    printf("✅ Assignment Added: %d ➝ %d\n", id1, id2);
}

// ================== MAIN MENU ==================
int main() {
    int choice;
    
    printf("✈ Welcome to AIRLINE CREW MANAGEMENT SYSTEM\n");
    
    while (1) {
        printf("\n====================================\n");
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
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: addCrew(); break;
            case 2: deleteCrewMenu(); break;  // ✅ Wrapper
            case 3: updateCrew(); break;
            case 4: searchCrew(); break;
            case 5: display(); break;
            case 6: addAssignment(); break;
            case 7: 
                cleanup();
                printf("👋 Exiting... All memory freed!\n"); 
                return 0;
            default: printf("❌ Invalid Choice (1-7)!\n");
        }
    }
    return 0;
}
