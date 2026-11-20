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

typedef enum { ADD, LIST, SEARCH, DELETE, QUIT } MenuState;

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

static InputStatus get_contact(Contact *out) {
    Contact temp = {};
    temp.status = CONTACT_ACTIVE;
    const InputStatus name_status = prompt_string("Type name here:", temp.name, MAX_NAME_LEN);
    if (name_status != INPUT_OK) return name_status;
    const InputStatus age_status = prompt_int("Type age here:", &temp.age, 0, 150);
    if (age_status != INPUT_OK) return age_status;
    const InputStatus email_status = prompt_string("Type email here:", temp.email, MAX_NAME_LEN);
    if (email_status != INPUT_OK) return email_status;
    *out = temp;
    return INPUT_OK;
}

static void print_contact(Contact contact, const int i) {
    printf("\nContact %i:\n", i + 1);
    printf("Name: %s\n", contact.name);
    printf("Age: %d\n", contact.age);
    printf("Email: %s\n", contact.email);
}

static void handle_quit() {
    printf("\nQUITTING...\n");
}

int main() {
    Contact contacts[MAX_CONTACTS] = {};
    for (int i = 0; i < MAX_CONTACTS; i++) {
        contacts[i].status = CONTACT_DELETED;
    }
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
        const InputStatus received_int = prompt_int("\nYour selection:", &selection, 0, 4);

        if (received_int == INPUT_INVALID) {
            printf("\nFailed to select an action, please try again...\n\n");
            continue;
        }
        if (received_int == INPUT_EOF) selection = QUIT;

        const MenuState action = selection;

        switch (action) {
            case ADD: {
                int i = 0;
                bool found = false;
                for (int j = 0; j < MAX_CONTACTS; j++) {
                    if (contacts[j].status == CONTACT_DELETED) {
                        printf("\nAdding contact at %i...\n", j);
                        i = j;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    printf("\n\nRoster Full\n\n");
                    break;
                }
                printf("ADD\n");
                const InputStatus status = get_contact(&contacts[i]);
                if (status == INPUT_EOF) {
                    handle_quit();
                    return 0;
                }
                if (status == INPUT_INVALID) {
                    printf("\n\nInvalid input\n\n");
                }
                break;
            }
            case LIST: {
                printf("LIST\n");
                for (int i = 0; i < MAX_CONTACTS; i++) {
                    if (contacts[i].status == CONTACT_ACTIVE) {
                        print_contact(contacts[i], i);
                    }
                }
                break;
            }
            case SEARCH: {
                printf("SEARCH\n");
                char query[MAX_NAME_LEN] = "";
                const InputStatus status = prompt_string("Search for contact:", query, MAX_NAME_LEN);
                if (status == INPUT_EOF) {
                    handle_quit();
                    return 0;
                }
                if (status == INPUT_INVALID) {
                    printf("\n\nInvalid input\n\n");
                    break;
                }
                printf("Results for Query [%s]:\n", query);
                for (int i = 0; i < MAX_CONTACTS; i++) {
                    if (contacts[i].status == CONTACT_ACTIVE && strstr(contacts[i].name, query)) {
                        print_contact(contacts[i], i);
                    }
                }
                break;
            }
            case DELETE: {
                printf("DELETE\n");
                int i = 0;
                const InputStatus status = prompt_int("Enter index for contact:", &i, 1, MAX_CONTACTS);
                if (status == INPUT_EOF) {
                    handle_quit();
                    return 0;
                }
                if (status == INPUT_INVALID) {
                    printf("\n\nInvalid input\n\n");
                    break;
                }
                if (contacts[i].status == CONTACT_ACTIVE) {
                    contacts[i].status = CONTACT_DELETED;
                } else {
                    printf("\n\nInvalid: Nothing to delete\n\n");
                }
                break;
            }
            case QUIT: {
                handle_quit();
                return 0;
            }
        }
    }
}
