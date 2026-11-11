#include <stdio.h>

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
    while (1) {
        printf("\nPlease select an action:\n%i. %s\n%i. %s\n%i. %s\n%i. %s\n%i. %s\n",
            ADD,
            get_menu_state(ADD), LIST,
            get_menu_state(LIST),
            SEARCH,
            get_menu_state(SEARCH),
            DELETE,
            get_menu_state(DELETE),
            QUIT,
            get_menu_state(QUIT));

        MenuState action = QUIT;

        switch (action) {
            case ADD: {
                printf("ADD\n");
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