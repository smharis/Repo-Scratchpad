#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define typecast(A) A-97

typedef struct tries_node {
    struct tries_node *child[26];
    int   count;
    char last_node;
}NODE;


void insert (NODE *root, char *str) {
     if (!root)
         return;
    
    if (*str == '\0')
        return;
    
     if (root->child[typecast(*str)] == NULL)
        root->child[typecast(*str)] =  (NODE *)calloc(1, sizeof(NODE));
    
    root->child[typecast(*str)]->count ++;
    if (*(str + 1) == '\0')
        root->child[typecast(*str)]->last_node = 1; 
    
    insert (root->child[typecast(*str)], str + 1);
    return;
}

void search (NODE *root, char *str) {
    if (!root)
        return;
    
    if (*str == '\0')
        return;
    
    if (root->child[typecast(*str)]) {
        if (*(str + 1) == '\0')
        printf ("%d\n", root->child[typecast(*str)]->count);
        search (root->child[typecast(*str)], str +1);
    }
    else
        printf ("0\n");
    return;
}

void add (NODE *root) {
    char *str = (char *)calloc(1, 23);
    scanf ("%s", str);
    insert (root, str);
    return;
}

void find (NODE *root) {
    char *str = (char *)calloc(1, 23);
    scanf ("%s", str);
    search (root, str);
    return ;
}

int main() {
    int n;
    char oper[4];
    NODE *root = (NODE *)calloc(1, sizeof(NODE));
    
    scanf ("%d", &n);
    while (n) {
        scanf ("%s", oper);
        if (*oper == 'a') {
            add (root);
        }
        if (*oper == 'f') {
            find (root);
        }
        n--;
    }    
    return 0;
}
