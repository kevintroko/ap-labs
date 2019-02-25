#include <stdio.h>
#include <stdlib.h>

// Structs definition
struct node {
    int value;
    int key;
    struct node *next;
};
struct table {
    struct node **list;
    int size;
};

struct table *createTable(int size) {
    struct table *t = (struct table *)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node **)malloc(sizeof(struct node *) * size);
    int i;
    for (i = 0; i < size; i++) {
        t->list[i] = NULL;
    }
    return t;
}

int hashCode(struct table *t, int key);
int lookup(struct table *t, int key);
void insert(struct table *t, int key, int value);

int hashCode(struct table *t, int key) {
    if (key < 0) {
        return -(key % t->size);
    }
    return key % t->size;
}

int lookup(struct table *t, int key) {
    int pos = hashCode(t, key);
    struct node *list = t->list[pos];
    struct node *temp = list;
    while (temp) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

void insert(struct table *t, int key, int value) {
    int pos = hashCode(t, key);
    struct node *list = t->list[pos];
    struct node *temp = list;
    while (temp) {
        if (temp->key == key) {
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    struct node *nodeNew = (struct node *)malloc(sizeof(struct node));
    nodeNew->key = key;
    nodeNew->value = value;
    nodeNew->next = list;
    t->list[pos] = nodeNew;
}