#include "linkedlist.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
int hash(char word[]);
void sort(node_t *array[], int wordcount, int difwordcount);
void quicksort(node_t *array[], int low, int high);
void swap(node_t *array[], int a, int b);
void printresults(node_t *array[], int wordcount, int difwordcount);
void slowsort(node_t *array[], int length);

#define SIZE 2500

//Lauri Taanila


int main()
{
    node_t *array[SIZE] = {};

    int index;
    int wordcount = 0, difwordcount = 0;

    FILE *fp;
    char tempword[100] = {};
    char ch;
    int n = 0;
    
    //Find a file to search.
    while(1){
        char filename[50];
        printf("Enter name of the text file: ");
        scanf("%s",filename);
        fp = fopen(filename, "r");

        if(fp != NULL){
            break;
        } else {
            printf("File not found! \n");
        }
        
    }

    //Calculates runtime.
    clock_t tStart = clock();

    //Searches the file and creates a node for every unique word.
    //If a node exists for a word it will increment the count by 1.
    //Nodes are placed into a hashtable with linked lists. 
    //On collicion it will add another node to the linked list.
    while (ch != EOF)
    {
        ch = fgetc(fp);

        if (isalpha(ch) || ch == '\'')
        {
            tempword[n] = ch;
            n++;
        }
        else if (n > 0)
        {
            tempword[n] = '\0';
            n = 0;
            wordcount++;

            for (int i = 0; i < strlen(tempword); i++)
            {

                tempword[i] = toupper(tempword[i]);

            }

            index = hash(tempword);

            if (find_value(array[index], tempword) != 1)
            {
                difwordcount++;
                insert_at_head(&array[index], create_new_node(tempword, 1));
            }
        }
    }

    fclose(fp);
    
    //Starts sorting.
    sort(array, wordcount, difwordcount);

    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    return 0;
}

//Starts by connecting all the linked lists into one array.
//Sorts the array with quicksort and prints out the 100 most used words.
void sort(node_t *array[], int wordcount, int length)
{

    node_t *temporary;
    node_t *head = create_new_node("FIRST NODE", 0);
    node_t *finalarray[length];

    temporary = head;

    for (int i = 0; i < SIZE; i++)
    {

        if (array[i] == NULL)
        {
            continue;
        }

        while (temporary->next != NULL)
        {
            temporary = temporary->next;
        }

        temporary->next = array[i];
    }

    temporary = head->next;

    for (int i = 0; i <= length - 1; i++)
    {
        finalarray[i] = temporary;
        temporary = temporary->next;
    }

    quicksort(finalarray, 0, length - 1);


    printresults(finalarray,wordcount,length);
}

//Quicksort that accounts for many duplicates
//https://www.coursera.org/lecture/algorithms-part1/duplicate-keys-XvjPd

void quicksort(node_t *array[], int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int pivot = array[low]->count;

    int left = low, i = low, right = high;

    while (i <= right)
    {
        if (array[i]->count > pivot)
        {
            swap(array, left, i);
            left++;
            i++;
        }
        else if (array[i]->count < pivot)
        {
            swap(array, i, right);
            right--;
        }
        else if (array[i]->count == pivot)
        {
            i++;
        }
    }

    quicksort(array, low, left - 1);
    quicksort(array, right + 1, high);
}

void swap(node_t *array[], int a, int b)
{
    node_t *temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void printresults(node_t *array[], int wordcount, int difwordcount){

    printf("Total number of words = %d\nNumber of different words = %d\n", wordcount,difwordcount);
    printf("The 100 most common words:\n");
    printf("WORD            NUMBER OF OCCURRENCES\n");

    for (int i = 0; i < 100; i++)
    {
        printf("%-15s %d\n", array[i]->word, array[i]->count);
    }

}

int hash(char word[])
{
    int hash = 1;
    int m = 31;
    for (int i = 0; i < strlen(word); i++)
    {
        hash = m * hash + word[i];
    }

    hash = hash % 2477;
    if (hash < 0)
    {
        hash = -hash;
    }

    return hash;
}

