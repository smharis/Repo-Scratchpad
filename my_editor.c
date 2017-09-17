#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stack {
    struct stack *next;
    unsigned int type;
    char *data;
}Stack;

void push (Stack **S, unsigned int type, char *data)
{
    Stack *s;
    s = *S;
    Stack *new1 = NULL;
    if (!s)
    {
        s = (Stack *)malloc(sizeof(Stack));
        s->next = NULL;
        s->type = type;
        s->data = data;
        *S = s;
        return;
    }
    new1 = (Stack *)malloc(sizeof(Stack));
    new1->next = s;
    new1->type = type;
    new1->data = data;
    *S = new1;
    return;
}

Stack *pop (Stack **S)
{
    Stack *s = *S;
    Stack *temp;
    if (!s)
       return NULL;
    temp = s;
    s = s->next;
    *S = s;
    return temp;
   
}

void undo(Stack **S, char **my_texteditor)
{
    Stack *undo_oper = NULL;
    undo_oper = pop (S);
    unsigned int del;
    if (undo_oper && undo_oper->type == 1)
    {
        /*perform delete*/
        (*my_texteditor)--;
        del = strlen(undo_oper->data);
        while(del)
          {
            **my_texteditor = '\0';
            (*my_texteditor)--;
            del--;
          }
        (*my_texteditor)++;
        free(undo_oper->data);
        free(undo_oper);
    }
    else if (undo_oper && undo_oper->type == 2)
    {
        /*peform insert*/
        del = strlen(undo_oper->data);
        strcpy(*my_texteditor,undo_oper->data);
        (*my_texteditor)=(*my_texteditor) + del;
        free(undo_oper->data);
        free(undo_oper);
    }
    return;
}

char *insert (char **my_texteditor)
{
    char  *temp = *my_texteditor;
    unsigned int len=0;
    while (**my_texteditor != '\0')
    {
       (*my_texteditor)++;
        len++;
    }
    char *buf = (char *)malloc(len+1);
    strcpy(buf,temp);
    buf[len] = '\0';
    return buf;
}

char *delete1 (char **my_texteditor, unsigned int del)
{
    (*my_texteditor)--;
    char *buf = (char *)malloc(del+1);
    unsigned int del1 = del;
    while(del)
    {
        buf[(del-1)] = **my_texteditor;
        **my_texteditor = '\0';
        (*my_texteditor)--;
        del--;
    }
    (*my_texteditor)++;
     
    buf[del1] = '\0';
   
    return buf;
}

void print (char *my_texteditor)
{
    unsigned int print;
    scanf ("%u", &print);
    printf ("%c\n",my_texteditor[(print-1)]);
    return;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    char *my_texteditor = (char *)calloc(1,2*1000000);
    unsigned int T, choice,del;
    Stack *S = NULL;
    char *buf;
    char *my_texteditor1 = my_texteditor;
    scanf ("%u", &T);
    while (T)
    {
        scanf ("%u",&choice);
        if (choice == 1)
        {
            scanf ("%s", my_texteditor1);
            buf = insert(&my_texteditor1);
            push (&S, 1, buf);
        }
        else if (choice == 2)
        {
            scanf("%u",&del);
            buf = delete1(&my_texteditor1,del);
            push (&S, 2, buf);
        }
        else if (choice == 3)
            print(my_texteditor);
        else if (choice == 4)
            undo (&S, &my_texteditor1);
        T--;
    }
    return 0;
}
