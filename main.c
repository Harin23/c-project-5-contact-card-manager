#include <stdio.h>
#include <string.h>

#include "helpers.h"

#define MAX_NAME_LEN 64
#define MAX_CONTACTS 50

typedef enum {
    CONTACT_ACTIVE,
    CONTACT_DELETED
} ContactStatus;

typedef struct {
    char name[MAX_NAME_LEN];
    char email[MAX_NAME_LEN];
    int age;
    ContactStatus status;
} Contact;

typedef enum {ADD, LIST, SEARCH, DELETE, QUIT} MenuState;
static const char *get_menu_state(MenuState state) {
    switch (state) {
        case ADD: return "ADD";
        case LIST: return "LIST";
        case SEARCH: return "SEARCH";
        case DELETE: return "DELETE";
        case QUIT: return "QUIT";
    }

    return "Invalid";
}

static void print_contact(Contact contact) {
    printf("\nContact:\n");
    printf("Name: %s\n", contact.name);
    printf("Age: %d\n", contact.age);
    printf("Email: %s\n", contact.email);
}

int main() {
    Contact contacts[MAX_CONTACTS] = {};
    for (int i = 0; i < MAX_CONTACTS; i++) {
        contacts[i].status = CONTACT_DELETED;
    }
    int count = -1;
    while (1) {
        printf("\nPlease select an action:\n%i. %s\n%i. %s\n%i. %s\n%i. %s\n%i. %s\n",
            ADD,
            get_menu_state(ADD),
            LIST,
            get_menu_state(LIST),
            SEARCH,
            get_menu_state(SEARCH),
            DELETE,
            get_menu_state(DELETE),
            QUIT,
            get_menu_state(QUIT)
        );

        int selection;
        const InputStatus received_int = prompt_int("\nYour selection:", &selection, 0,4);

        if (received_int == INPUT_INVALID) {
            printf("\nFailed to select an action, please try again...\n\n");
            continue;
        }
        
        if (received_int == INPUT_EOF) {
            selection = QUIT;
        }

        const MenuState action = selection;

        switch (action) {
            case ADD: {
                int i=0;
                if (count >= MAX_CONTACTS) {
                    for (int j=0; j < MAX_CONTACTS; j++) {
                        if (contacts[j].status == CONTACT_DELETED) {
                            printf("\nReplacing the deleted contact %i...\n", j);
                            print_contact(contacts[j]);
                            i = j;
                        }
                    }
                }else {
                    count++;
                    i = count;
                }
                printf("ADD\n");
                prompt_string("Type name here:", contacts[i].name, MAX_NAME_LEN);
                prompt_int("Type age here:", &contacts[i].age, 0, 150);
                prompt_string("Type email here:", contacts[i].email, MAX_NAME_LEN);
                contacts[i].status = CONTACT_ACTIVE;
                break;
            }
            case LIST: {
                printf("LIST\n");
                for (int i = 0; i < MAX_CONTACTS; i++) {
                    if (contacts[i].status == CONTACT_ACTIVE) {
                        print_contact(contacts[i]);
                    }
                }
                break;
            }
            case SEARCH: {
                printf("SEARCH\n");
                char query[MAX_NAME_LEN] = "";
                prompt_string("Search for contact:", query, MAX_NAME_LEN);
                printf("Results for Query [%s]:\n", query);
                for (int i = 0; i < MAX_CONTACTS; i++) {
                    if (contacts[i].status == CONTACT_ACTIVE && strstr(contacts[i].name, query)) {
                        print_contact(contacts[i]);
                    }
                }
                break;
            }
            case DELETE: {
                printf("DELETE\n");
                break;
            }
            case QUIT: {
                printf("\nQUITTING...\n");
                return 0;
            }
        }

    }
}