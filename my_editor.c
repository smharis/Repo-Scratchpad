#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Macros*/
#define INSERT 1
#define DELETE 2
#define UPDATE 3
#define PRINT  4

/*Structure to maintain stack framework*/
typedef struct stack {
    struct stack *next;
    
    /*Type: either INSERT OR DELETE*/
    unsigned int type;
    
    /*It will be holding data to be deleted or inserete depending upon type*/
    char *data; 
}Stack;

/*API to push each operation*/
void
push (Stack **S, unsigned int type, char *data) {
    Stack *s;
    s = *S;
    Stack *new1 = NULL;
    if (!s) {
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

/*API to perform a pop of operation once user do undo*/
Stack*
pop (Stack **S) {
    Stack *s = *S;
    Stack *temp;
    if (!s)
       return NULL;
    temp = s;
    s = s->next;
    *S = s;
    return temp; 
}
 /*
 **********************************************
 * API will undo the operation by user.       *
 * It will update the current file pointer    *
 * and free the buffer created for stack node *
 * followed by freeing of stack node also     *
 **********************************************
 */
void
undo(Stack **S, char **my_texteditor) {
    Stack *undo_oper = NULL;
    undo_oper = pop (S);
    unsigned int del;
    if (undo_oper && undo_oper->type == INSERT) {
        /*perform delete*/
        (*my_texteditor)--;
        del = strlen(undo_oper->data);
        while(del) {
            **my_texteditor = '\0';
            (*my_texteditor)--;
            del--;
          }
        (*my_texteditor)++;
        free(undo_oper->data);
        free(undo_oper);
    }
    else if (undo_oper && undo_oper->type == DELETE) {
        /*peform insert*/
        del = strlen(undo_oper->data);
        strcpy(*my_texteditor,undo_oper->data);
        (*my_texteditor)=(*my_texteditor) + del;
        free(undo_oper->data);
        free(undo_oper);
    }
    return;
}

/*
 *************************************************************
 * API will put the data in editor and return the buffer     *
 * to be pushed to stack framework                           *
 *************************************************************
 */
char *
insert (char **my_texteditor) {
    char  *temp = *my_texteditor;
    unsigned int len=0;
    while (**my_texteditor != '\0') {
       (*my_texteditor)++;
        len++;
    }
    char *buf = (char *)malloc(len+1);
    strcpy(buf,temp);
    buf[len] = '\0';
    return buf;
}

/*
 *************************************************************
 * API will delete the given set of bytes data from editor   *
 * and return the buffer to be pushed to stack framework     *                         
 *************************************************************
 */
char *
delete (char **my_texteditor, unsigned int del) {
    (*my_texteditor)--;
    char *buf = (char *)malloc(del+1);
    unsigned int del1 = del;
    while(del) {
        buf[(del-1)] = **my_texteditor;
        **my_texteditor = '\0';
        (*my_texteditor)--;
        del--;
    }
    (*my_texteditor)++;
     
    buf[del1] = '\0';
   
    return buf;
}

/*API will print the character for the given byte from editor*/
void print (char *my_texteditor)
{
    unsigned int print;
    scanf ("%u", &print);
    printf ("%c\n",my_texteditor[(print-1)]);
    return;
}

/*Main Routine*/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    char *my_texteditor = (char *)calloc(1,2*1000000);
    unsigned int T, choice,del;
    Stack *S = NULL;
    char *buf;
    char *my_texteditor1 = my_texteditor;
    scanf ("%u", &T);
    /*Number of test cases*/
    while (T)
    {
        scanf ("%u",&choice);
        if (choice == INSERT)
        {
            scanf ("%s", my_texteditor1);
            buf = insert(&my_texteditor1);
            push (&S, 1, buf);
        }
        else if (choice == DELETE)
        {
            scanf("%u",&del);
            buf = delete1(&my_texteditor1,del);
            push (&S, 2, buf);
        }
        else if (choice == PRINT)
            print(my_texteditor);
        else if (choice == UNDO)
            undo (&S, &my_texteditor1);
        T--;
    }
    return 0;
}
