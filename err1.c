#include <stdio.h>
#include <stdlib.h>


typedef struct person {
    char* name;
    int age;
    struct person* next;
} PERSON;


PERSON* createPerson(char* name, int age) {
    PERSON* person = (PERSON*)malloc(sizeof(PERSON));
    person->name = name;
    person->age = age;
    person->next = NULL;

    return person;
}


PERSON* insert(PERSON* first, char* name, int age) {
    PERSON* new, *current;
    new = createPerson(name, age);

    current = first;

    if (first == NULL) {
        first = new;
        return first;
    }

    while (current->next!=NULL)
    {
        current = current->next;
    }

    current->next = new;

    return first;
}


int main(void) {
    PERSON* first = NULL;

    first = insert(first, "Marian", 21);
    first = insert(first, "Fero", 20);
    first = insert(first, "Marko", 22);

    return 0;
}