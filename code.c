#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Passenger structure
struct Passenger {
    char name[50];
    char source[50];
    char destination[50];
    struct Passenger* next;
};

// Flight structure
struct Flight {
    char flightNumber[10];
    char source[50];
    char destination[50];
    struct Passenger* passengers;
    struct Flight* next;
};

struct Flight* flightHead = NULL;

// Add new flight
void addFlight() {
    struct Flight* newFlight = (struct Flight*)malloc(sizeof(struct Flight));
    printf("Enter flight number: ");
    scanf("%s", newFlight->flightNumber);
    printf("Enter flight source: ");
    scanf("%s", newFlight->source);
    printf("Enter flight destination: ");
    scanf("%s", newFlight->destination);
    newFlight->passengers = NULL;
    newFlight->next = flightHead;
    flightHead = newFlight;
    printf("Flight added.\n");
}

// Book a passenger
void bookPassenger() {
    char flightNum[10];
    char name[50];
    char src[50], dest[50];

    printf("Enter flight number: ");
    scanf("%s", flightNum);

    struct Flight* temp = flightHead;

    while (temp != NULL && strcmp(temp->flightNumber, flightNum) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Flight not found.\n");
        return;
    }

    printf("Enter passenger name: ");
    scanf("%s", name);
    printf("Enter passenger source: ");
    scanf("%s", src);
    printf("Enter passenger destination: ");
    scanf("%s", dest);

    if (strcmp(src, temp->source) != 0 || strcmp(dest, temp->destination) != 0) {
        printf("Passenger route must match the flight's source and destination (%s to %s).\n", temp->source, temp->destination);
        return;
    }

    struct Passenger* newPass = (struct Passenger*)malloc(sizeof(struct Passenger));
    strcpy(newPass->name, name);
    strcpy(newPass->source, src);
    strcpy(newPass->destination, dest);
    newPass->next = temp->passengers;
    temp->passengers = newPass;
    printf("Passenger added.\n");
}

// Show all flights and passengers
void showFlights() {
    struct Flight* f = flightHead;
    if (f == NULL) {
        printf("No flights added yet.\n");
        return;
    }

    while (f != NULL) {
        printf("\nFlight: %s\n", f->flightNumber);
        printf("Route: %s -> %s\n", f->source, f->destination);

        struct Passenger* p = f->passengers;
        if (p == NULL) {
            printf("  No passengers.\n");
        } else {
            printf("  Passengers:\n");
            while (p != NULL) {
                printf("   - %s (From %s to %s)\n", p->name, p->source, p->destination);
                p = p->next;
            }
        }
        f = f->next;
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Add Flight\n2. Book Passenger\n3. Show Flights\n0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) addFlight();
        else if (choice == 2) bookPassenger();
        else if (choice == 3) showFlights();
        else if (choice == 0) break;
        else printf("Invalid choice.\n");
    }

    return 0;
}
