/*
 Contact Management System (C)
 - Features:
   1. Add contact
   2. Display all contacts
   3. Search by name or phone
   4. Edit contact
   5. Delete contact
   6. Save/load to/from binary file "contacts.dat"
 - Compile: gcc contacts.c -o contacts
 - Run: ./contacts
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATAFILE "contacts.dat"
#define MAX_NAME 100
#define MAX_PHONE 20
#define MAX_EMAIL 100

typedef struct {
    int id;                 // unique id (simple autoincrement)
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
    char address[200];
} Contact;

/* --- Utility functions --- */
static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin)) {
        size_t len = strlen(buffer);
        if (len && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        else clear_stdin();
    } else {
        buffer[0] = '\0';
        clear_stdin();
    }
}

/* --- File helpers --- */
static int count_contacts_in_file(void) {
    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) return 0;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return (int)(size / sizeof(Contact));
}

static Contact *load_all_contacts(int *out_count) {
    *out_count = count_contacts_in_file();
    if (*out_count == 0) return NULL;
    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) return NULL;
    Contact *arr = malloc((*out_count) * sizeof(Contact));
    if (!arr) { fclose(fp); return NULL; }
    fread(arr, sizeof(Contact), *out_count, fp);
    fclose(fp);
    return arr;
}

static int save_all_contacts(Contact *arr, int count) {
    FILE *fp = fopen(DATAFILE, "wb");
    if (!fp) return 0;
    fwrite(arr, sizeof(Contact), count, fp);
    fclose(fp);
    return 1;
}

/* --- Operations --- */
static int get_next_id(void) {
    int count;
    Contact *arr = load_all_contacts(&count);
    int maxid = 0;
    for (int i = 0; i < count; ++i) if (arr[i].id > maxid) maxid = arr[i].id;
    free(arr);
    return maxid + 1;
}

void add_contact(void) {
    Contact c;
    c.id = get_next_id();
    read_line("Name: ", c.name, MAX_NAME);
    read_line("Phone: ", c.phone, MAX_PHONE);
    read_line("Email: ", c.email, MAX_EMAIL);
    read_line("Address: ", c.address, sizeof(c.address));

    FILE *fp = fopen(DATAFILE, "ab");
    if (!fp) {
        printf("Error: unable to open data file for appending.\n");
        return;
    }
    fwrite(&c, sizeof(Contact), 1, fp);
    fclose(fp);
    printf("Contact added with ID %d.\n", c.id);
}

void display_all_contacts(void) {
    int count;
    Contact *arr = load_all_contacts(&count);
    if (!arr || count == 0) {
        printf("No contacts found.\n");
        free(arr);
        return;
    }
    printf("Total contacts: %d\n", count);
    for (int i = 0; i < count; ++i) {
        Contact *c = &arr[i];
        printf("ID: %d\n  Name   : %s\n  Phone  : %s\n  Email  : %s\n  Address: %s\n",
               c->id, c->name, c->phone, c->email, c->address);
        printf("-----------------------------\n");
    }
    free(arr);
}

void search_contacts(void) {
    char q[200];
    read_line("Enter name or phone to search: ", q, sizeof(q));
    if (strlen(q) == 0) { printf("Empty query.\n"); return; }

    int count;
    Contact *arr = load_all_contacts(&count);
    if (!arr || count == 0) {
        printf("No contacts.\n");
        free(arr);
        return;
    }

    int found = 0;
    for (int i = 0; i < count; ++i) {
        if (strcasestr(arr[i].name, q) || strcasestr(arr[i].phone, q)) {
            Contact *c = &arr[i];
            printf("ID: %d\n  Name   : %s\n  Phone  : %s\n  Email  : %s\n  Address: %s\n",
                   c->id, c->name, c->phone, c->email, c->address);
            printf("-----------------------------\n");
            found = 1;
        }
    }
    if (!found) printf("No matching contacts found.\n");
    free(arr);
}

void edit_contact(void) {
    int id;
    printf("Enter contact ID to edit: ");
    if (scanf("%d", &id) != 1) { clear_stdin(); printf("Invalid input.\n"); return; }
    clear_stdin();

    int count;
    Contact *arr = load_all_contacts(&count);
    if (!arr || count == 0) { printf("No contacts.\n"); free(arr); return; }

    int idx = -1;
    for (int i = 0; i < count; ++i) if (arr[i].id == id) { idx = i; break; }
    if (idx == -1) { printf("Contact with ID %d not found.\n", id); free(arr); return; }

    Contact *c = &arr[idx];
    char tmp[300];

    printf("Editing contact ID %d (leave blank to keep current)\n", c->id);
    printf("Current name: %s\n", c->name);
    read_line("New name: ", tmp, sizeof(tmp));
    if (strlen(tmp)) strncpy(c->name, tmp, MAX_NAME);

    printf("Current phone: %s\n", c->phone);
    read_line("New phone: ", tmp, sizeof(tmp));
    if (strlen(tmp)) strncpy(c->phone, tmp, MAX_PHONE);

    printf("Current email: %s\n", c->email);
    read_line("New email: ", tmp, sizeof(tmp));
    if (strlen(tmp)) strncpy(c->email, tmp, MAX_EMAIL);

    printf("Current address: %s\n", c->address);
    read_line("New address: ", tmp, sizeof(tmp));
    if (strlen(tmp)) strncpy(c->address, tmp, sizeof(c->address));

    if (save_all_contacts(arr, count)) printf("Contact updated.\n");
    else printf("Error saving contacts.\n");

    free(arr);
}

void delete_contact(void) {
    int id;
    printf("Enter contact ID to delete: ");
    if (scanf("%d", &id) != 1) { clear_stdin(); printf("Invalid input.\n"); return; }
    clear_stdin();

    int count;
    Contact *arr = load_all_contacts(&count);
    if (!arr || count == 0) { printf("No contacts.\n"); free(arr); return; }

    int idx = -1;
    for (int i = 0; i < count; ++i) if (arr[i].id == id) { idx = i; break; }
    if (idx == -1) { printf("Contact with ID %d not found.\n", id); free(arr); return; }

    // shift left to remove
    for (int i = idx; i < count - 1; ++i) arr[i] = arr[i + 1];
    count--;

    if (count == 0) {
        // remove file
        if (remove(DATAFILE) == 0) printf("Contact deleted. No contacts remain.\n");
        else printf("Contact deleted (but couldn't remove file).\n");
        free(arr);
        return;
    }

    if (save_all_contacts(arr, count)) printf("Contact deleted.\n");
    else printf("Error saving after delete.\n");
    free(arr);
}

/* simple case-insensitive substring finder (POSIX strcasestr not always available) */
char *strcasestr_local(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    for (; *haystack; ++haystack) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n))) { ++h; ++n; }
        if (!*n) return (char *)haystack;
    }
    return NULL;
}

/* Provide portability: if strcasestr exists, use it; otherwise use local */
#ifdef __GNUC__
/* GCC environments usually have strcasestr in string.h via _GNU_SOURCE, but to be safe use local */
#endif
#define strcasestr(x,y) strcasestr_local((x),(y))

/* --- Menu --- */
void print_menu(void) {
    printf("\n=== Contact Management ===\n");
    printf("1. Add contact\n");
    printf("2. Display all contacts\n");
    printf("3. Search contacts\n");
    printf("4. Edit contact\n");
    printf("5. Delete contact\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

int main(void) {
    int choice = 0;
    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            printf("Invalid choice.\n");
            continue;
        }
        clear_stdin();
        switch (choice) {
            case 1: add_contact(); break;
            case 2: display_all_contacts(); break;
            case 3: search_contacts(); break;
            case 4: edit_contact(); break;
            case 5: delete_contact(); break;
            case 6: printf("Goodbye.\n"); return 0;
            default: printf("Invalid option. Choose 1-6.\n"); break;
        }
    }
    return 0;
}

