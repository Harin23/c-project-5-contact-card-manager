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

int main() {
    Contact contacts[MAX_CONTACTS] = {};

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
                printf("ADD\n");

                // printf("Type name here:");
                // char name[MAX_NAME_LEN];
                // while (fgets(name, MAX_NAME_LEN, stdin));
                // name[strcspn(name, "\n")] = '\0';
                // strncpy(contacts[0].name, name, MAX_NAME_LEN-1);
                //
                // printf("\nType email here:");
                // fgets(name, MAX_NAME_LEN, stdin);
                // name[strcspn(name, "\n")] = '\0';
                // strncpy(contacts[0].email, name, MAX_NAME_LEN-1);
                //
                // printf("\nType age here:");
                // int age;
                // scanf("%i", &age);
                // contacts[0].age = age;
                break;
            }
            case LIST: {
                printf("LIST\n");
                break;
            }
            case SEARCH: {
                printf("SEARCH\n");
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