#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 100

typedef struct Node
{
    char name[MAX_NAME_LENGTH];
    struct Node* next;
} Node;

Node* createNode(const char* name)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy_s(newNode->name, MAX_NAME_LENGTH, name);
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head)
{
    if (head == NULL) {
        printf("Fruit list is empty.\n");
        return;
    }

    printf("Fruit list:\n");
    for (Node* curr = head; curr != NULL; curr = curr->next)
    {
        printf("%s\n", curr->name);
    }
}

int isFruitExists(Node* head, const char* name)
{
    if (head == NULL)
    {
        return 0;
    }

    for (Node* curr = head; curr != NULL; curr = curr->next)
    {
        if (strcmp(curr->name, name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

Node* addFruit(Node* head, const char* name)
{
    if (isFruitExists(head, name))
    {
        printf("%s already exists.\n", name);
        return head;
    }

    Node* newNode = createNode(name);
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node* curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    printf("%s has been added.\n", name);
    return head;
}

Node* deleteFruit(Node* head, const char* name, Node** deletedHead)
{
    if (head == NULL)
    {
        printf("Fruit list is empty.\n");
        return NULL;
    }

    Node* curr = head;
    Node* prev = NULL;

    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
        {
            if (prev == NULL)
            {
                head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            curr->next = *deletedHead;
            *deletedHead = curr;

            printf("%s has been deleted.\n", name);
            return head;
        }

        prev = curr;
        curr = curr->next;
    }

    printf("%s is not on the list.\n", name);
    return head;
}

void printDeletedFruits(Node* deletedHead)
{
    if (deletedHead == NULL)
    {
        printf("List of the deleted fruits: NULL\n");
        return;
    }

    printf("List of the deleted fruits: ");
    for (Node* curr = deletedHead; curr != NULL; curr = curr->next)
    {
        printf("%s->", curr->name);
    }
    printf("\n");
}

void freeList(Node* head)
{
    Node* curr = head;
    while (curr != NULL)
    {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

int main() 
{
    Node* fruitList = NULL;
    Node* deletedList = NULL;

    const char* initialFruits[] = {
        "Mango", "Orange", "Apple", "Grape", "Cherry",
        "Plum", "Guava", "Raspberry", "Banana", "Peach"
    };
    int numInitialFruits = sizeof(initialFruits) / sizeof(initialFruits[0]);

    // Add initial fruits to the list
    for (int i = 0; i < numInitialFruits; i++)
    {
        fruitList = addFruit(fruitList, initialFruits[i]);
    }

    int menu;
    char fruitName[MAX_NAME_LENGTH];

    while (1)
    {
        printf("Menu\n");
        printf("1. Insert new fruit\n");
        printf("2. Delete the fruit\n");
        printf("3. Print the deleted list\n");
        printf("4. Exit\n");
        printf("Enter the menu: ");
        scanf_s("%d", &menu);

        if (menu == 1)
        {
            printf("Enter the fruit name to add: ");
            scanf_s("%s", fruitName, MAX_NAME_LENGTH);
            fruitList = addFruit(fruitList, fruitName);
        }
        else if (menu == 2)
        {
            printf("Enter the fruit name to delete: ");
            scanf_s("%s", fruitName, MAX_NAME_LENGTH);
            fruitList = deleteFruit(fruitList, fruitName, &deletedList);
        }
        else if (menu == 3)
        {
            printDeletedFruits(deletedList);
        }
        else if (menu == 4)
        {
            printf("Exit the program.\n");
            freeList(fruitList);
            freeList(deletedList);
            return 0;
        }
        else
        {
            printf("Invalid menu. Please select again.\n");
        }
        printf("\n");
    }
}