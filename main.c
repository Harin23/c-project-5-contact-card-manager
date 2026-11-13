#include <stdio.h>

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
    // Contact contacts[MAX_CONTACTS];

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

        printf("\nYour selection:");
        int selection;
        scanf("%i", &selection);

        // printf("\nselector: %i\n", selection);
        const MenuState action = selection;

        switch (action) {
            case ADD: {
                printf("ADD\n");
                
                // contacts[sizeof(contacts)-1].name[0] = '\0';
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
                printf("QUITTING...\n");
                return 0;
            }
        }
    }
}