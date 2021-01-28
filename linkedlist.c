#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node
{
    char *word;
    int count;
    struct node* next;
};

typedef struct node node_t;

node_t *create_new_node(char word[],int count){
    node_t *newnode = malloc(sizeof(node_t));
    newnode->word = malloc(strlen(word) + 1);
    strcpy(newnode->word, word);
    newnode->count = count;
    newnode->next = NULL;
    return newnode;
}


void printlist(node_t *head){
    
    node_t *temporary = head;

    if (temporary == NULL){
        
        return;
    }
    while (temporary != NULL){
        printf("%s %d - ", temporary->word, temporary->count);
        temporary = temporary->next;
    }

    return;
}

void *insert_at_head(node_t **head, node_t *node_to_insert){
    
        node_to_insert->next = *head;
        *head = node_to_insert;
    

}


int find_value(node_t *head, char word[]){

    if (head == NULL){
        return 0;
    }

    node_t *temp = head;

    while (temp->next != NULL){

        if (strcmp(temp->word,word) == 0){
            temp->count++;
            return 1;
            }
        temp = temp->next;
    } 

    if (strcmp(temp->word,word) == 0){
            temp->count++;
            return 1;
            }

    return 0;
}

