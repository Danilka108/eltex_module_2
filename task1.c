#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CONTACTS_LIST_SIZE 50
#define PROFILES_SIZE 5
#define FIELD_SIZE 256

typedef struct {
	char home[FIELD_SIZE];
	char work[FIELD_SIZE];
} Email;

typedef struct {
	char address[FIELD_SIZE];
	char nickname[FIELD_SIZE];
} SocialProfile;

typedef struct {
	char firstName[FIELD_SIZE];
	char lastName[FIELD_SIZE];

	Email email;

	SocialProfile profiles[PROFILES_SIZE];
	int profilesSize;
} Person;

Person contacts[CONTACTS_LIST_SIZE];
int contactsSize;

bool addContact(char firstName[], char lastName[], char homeEmail[], char workEmail[], SocialProfile profiles[], int profilesSize) {
	if (contactsSize > CONTACTS_LIST_SIZE) {
		printf("contacts list is full\n");
		return false;
	}

	Person *contact = &contacts[contactsSize];

	strcpy(contact->firstName, firstName);
	strcpy(contact->lastName, lastName);

	if (homeEmail != NULL) {
		strcpy(contacts->email.home, homeEmail);
	}
	if (workEmail != NULL) {
		strcpy(contacts->email.work, workEmail);
	}

	if (profilesSize > PROFILES_SIZE) {
		printf("too many profiles\n");
		return false;
	}

	memcpy(contact->profiles, profiles, sizeof(SocialProfile) * profilesSize);
	contact->profilesSize = profilesSize;

	contactsSize++;
	return true;
}

bool editContact(char firstName[], char lastName[], char homeEmail[], char workEmail[], SocialProfile profiles[], int profilesSize) {
	for (int i = 0; i < contactsSize; ++i) {
		if (strcmp(contacts[i].firstName, firstName) == 0 && strcmp(contacts[i].lastName, lastName) == 0) {
			strcpy(contacts[i].email.home, homeEmail);
			strcpy(contacts[i].email.work, workEmail);

			memcpy(contacts[i].profiles, profiles, sizeof(SocialProfile) * profilesSize);
			contacts[i].profilesSize = profilesSize;

			return true;
		}
	}

	return false;
}

bool removeContact(char firstName[], char lastName[]) {
	for (int i = 0; i < contactsSize; ++i) {
		if (strcmp(contacts[i].firstName, firstName) == 0 && strcmp(contacts[i].lastName, lastName) == 0) {
			memmove(contacts + i, contacts + i + 1, (contactsSize - i - 1) * sizeof(Person));
			--contactsSize;
			return true;
		}
	}

	return false;
}

bool findContact(char firstName[], char lastName[], Person *foundPerson) {
	for (int i = 0; i < contactsSize; ++i) {
		if (strcmp(contacts[i].firstName, firstName) == 0 && strcmp(contacts[i].lastName, lastName) == 0) {
			*foundPerson = contacts[i];
			return true;
		}
	}

	return false;
}

void printContact(Person contact) {
	printf("{\n");
	printf("\tfirstName = \"%s\",\n", contact.firstName);
	printf("\tlastName = \"%s\",\n", contact.lastName);

	printf("\tworkEmail = \"%s\",\n", contact.email.work);
	printf("\thomeEmail = \"%s\",\n", contact.email.home);
	printf("\t\profiles = [\n");
	for (int j = 0; j < contact.profilesSize; j++) {
		printf("\t\t{\n");
		printf("\t\t\taddress = \"%s\",\n", contact.profiles[j].address);
		printf("\t\t\tnickname = \"%s\",\n", contact.profiles[j].nickname);
		printf("\t\t},\n");
	}
	printf("\t],\n");
	printf("},\n");
}

void printContacts() {
	printf("contacts = [\n");

	for (int i = 0; i < contactsSize; ++i) {
		printf("\t{\n");
		printf("\t\tfirstName = \"%s\",\n", contacts[i].firstName);
		printf("\t\tlastName = \"%s\",\n", contacts[i].lastName);
		printf("\t\tworkEmail = \"%s\",\n", contacts[i].email.work);
		printf("\t\thomeEmail = \"%s\",\n", contacts[i].email.home);
		printf("\t\tprofiles = [\n");
		for (int j = 0; j < contacts[i].profilesSize; j++) {
			printf("\t\t\t{\n");
			printf("\t\t\t\taddress = \"%s\",\n", contacts[i].profiles[j].address);
			printf("\t\t\t\tnickname = \"%s\",\n", contacts[i].profiles[j].nickname);
			printf("\t\t\t},\n");
		}
		printf("\t\t],\n");
		printf("\t},\n");
	}

	printf("]\n");
}

bool enterName(char *firstname, char *lastname) {
	printf("enter contact firstname: ");
	scanf("%s", firstname);

	printf("enter contact lastname: ");
	scanf("%s", lastname);


	return true;
}

bool enterEmail(char *homeEmail, char *workEmail) {
	printf("enter home email: ");
	scanf("%s", homeEmail);

	printf("enter work email: ");
	scanf("%s", workEmail);

	return true;
}

int enterProfiles(SocialProfile *profiles) {
	printf("enter profiles:\n");

	int stop = 0;
	int i = 0;

	while (true) {
		printf("stop (0 - false, 1 - true)?: ");
		scanf("%d", &stop);

		if (stop == 1 || i == PROFILES_SIZE) {
			printf("after i = %d\n", i);
			break;
		}

		printf("enter profile address: ");
		scanf("%s", profiles[i].address);

		printf("enter profile nickname: ");
		scanf("%s", profiles[i].nickname);

		i += 1;
	}

	return i;
}

int main() {
	while (true) {
		printf("menu options:\n");
		printf("1 - add contact\n");
		printf("2 - edit contact\n");
		printf("3 - remove contact\n");
		printf("4 - find contact\n");
		printf("5 - print all contacts\n");
		printf("6 - exit\n"):
		printf("> ");

		int option;
		scanf("%d", &option);

		char firstname[FIELD_SIZE];
		char lastname[FIELD_SIZE];

		char homeEmail[FIELD_SIZE];
		char workEmail[FIELD_SIZE];

		SocialProfile profiles[PROFILES_SIZE];
		int profilesSize;

		Person foundContact;

		switch (option) {
			case 1:
				enterName(firstname, lastname);
				enterEmail(homeEmail, workEmail);
				profilesSize = enterProfiles(profiles);
				printf("size = %d\n", profilesSize);

				if (addContact(firstname, lastname, homeEmail, workEmail, profiles, profilesSize)) {
					printf("contact added\n");
				} else {
					printf("failed to add contact\n");
				}

				continue;
			case 2:
				enterName(firstname, lastname);
				enterEmail(homeEmail, workEmail);
				profilesSize = enterProfiles(profiles);

				if (editContact(firstname, lastname, homeEmail, workEmail, profiles, profilesSize)) {
					printf("contact updated\n");
				} else {
					printf("contact not found\n");
				}

				continue;
			case 3:
				enterName(firstname, lastname);

				if (removeContact(firstname, lastname)) {
					printf("contact removed\n");
				} else {
					printf("contact not found\n");
				}

				continue;
			case 4:
				enterName(firstname, lastname);

				if (findContact(firstname, lastname, &foundContact)) {
					printContact(foundContact);
				} else {
					printf("contact not found\n");
				}

				continue;
			case 5:
				printContacts();
				continue;
			case 6:
				return 0;
			default:
				printf("invalid menu option\n");
				continue;
		}
	}

	return 0;
}
