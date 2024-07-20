#include "contacts.h"
#include "person.h"
#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>

#define CONTACTS_LIB_PATH "./libcontacts.so"

#define CONTACTS_INIT_FN_SYM "contacts_init"
typedef contacts_t (*contacts_init_t)();

#define CONTACTS_ADD_FN_SYM "contacts_add"
typedef bool (*contacts_add_t)(contacts_t *self, person_t person);

#define CONTACTS_FIND_FN_SYM "contacts_find"
typedef person_t *(*contacts_find_t)(contacts_t *self, name_t *name);

#define CONTACTS_REMOVE_FN_SYM "contacts_remove"
typedef person_t *(*contacts_remove_t)(contacts_t *self, name_t *name);

#define CONTACTS_PRINT_FN_SYM "contacts_print"
typedef void (*contacts_print_t)(contacts_t *self);

#define CONTACTS_DESTROY_FN_SYM "contacts_destroy"
typedef void (*contacts_destroy_t)(contacts_t *self);

bool enter_name(name_t *name);

bool enter_emails(emails_t *emails);

bool enter_profiles(profile_t *profiles, size_t *profiles_size);

int main() {
  void *lib_handle = dlopen(CONTACTS_LIB_PATH, RTLD_LAZY);

  contacts_init_t contacts_init = dlsym(lib_handle, CONTACTS_INIT_FN_SYM);
  contacts_t contacts = contacts_init();

  contacts_add_t contacts_add;
  contacts_find_t contacts_find;
  contacts_remove_t contacts_remove;
  contacts_print_t contacts_print;

  while (true) {
    printf("menu options:\n");
    printf("1 - add contact\n");
    printf("2 - edit contact\n");
    printf("3 - remove contact\n");
    printf("4 - find contact\n");
    printf("5 - print all contacts\n");
    printf("6 - exit\n");
    printf("> ");

    int option;
    scanf("%d", &option);

    switch (option) {
    case 1: {
      name_t name;
      emails_t emails;
      profile_t profiles[PROFILES_SIZE];
      size_t profiles_size;

      enter_name(&name);
      enter_emails(&emails);
      enter_profiles(profiles, &profiles_size);

      person_t person = person_init(&name, &emails, profiles, profiles_size);

      if (!contacts_add)
        contacts_add = dlsym(lib_handle, CONTACTS_ADD_FN_SYM);
      contacts_add(&contacts, person);

      continue;
    }
    case 2: {
      name_t name;
      emails_t emails;
      profile_t profiles[PROFILES_SIZE];
      size_t profiles_size;

      enter_name(&name);
      enter_emails(&emails);
      enter_profiles(profiles, &profiles_size);

      if (!contacts_find)
        contacts_find = dlsym(lib_handle, CONTACTS_FIND_FN_SYM);

      person_t *person = contacts_find(&contacts, &name);
      if (person) {
        person_edit(person, &name, &emails, profiles, profiles_size);
      } else {
        printf("person not found\n");
      }

      continue;
    }
    case 3: {
      name_t name;
      enter_name(&name);

      if (!contacts_remove)
        contacts_remove = dlsym(lib_handle, CONTACTS_REMOVE_FN_SYM);

      if (contacts_remove(&contacts, &name)) {
        printf("contact removed\n");
      } else {
        printf("contact not found\n");
      }

      continue;
    }
    case 4: {
      name_t name;
      enter_name(&name);

      if (!contacts_find)
        contacts_find = dlsym(lib_handle, CONTACTS_FIND_FN_SYM);

      person_t *person = person = contacts_find(&contacts, &name);
      if (person) {
        person_print(person, 0);
      } else {
        printf("contact not found\n");
      }

      continue;
    }
    case 5: {
      if (!contacts_print)
        contacts_print = dlsym(lib_handle, CONTACTS_PRINT_FN_SYM);

      contacts_print(&contacts);
      continue;
    }
    case 6:
      return 0;
    default:
      printf("invalid menu option\n");
      continue;
    }
  }

  contacts_destroy_t contacts_destroy =
      dlsym(lib_handle, CONTACTS_DESTROY_FN_SYM);
  contacts_destroy(&contacts);

  dlclose(lib_handle);

  return 0;
}

bool enter_name(name_t *name) {
  printf("enter contact firstname: ");
  scanf("%s", name->first_name);

  printf("enter contact lastname: ");
  scanf("%s", name->last_name);

  return true;
}

bool enter_emails(emails_t *emails) {
  printf("enter home email: ");
  scanf("%s", emails->home);

  printf("enter work email: ");
  scanf("%s", emails->work);

  return true;
}

bool enter_profiles(profile_t *profiles, size_t *profiles_size) {
  printf("enter profiles amount: ");
  scanf("%lu", profiles_size);

  if (*profiles_size > PROFILES_SIZE) {
    return false;
  }

  printf("enter profiles:\n");

  for (size_t i = 0; i < *profiles_size; i++) {
    printf("enter profile address: ");
    scanf("%s", profiles[i].address);

    printf("enter profile nickname: ");
    scanf("%s", profiles[i].nickname);
  }

  return true;
