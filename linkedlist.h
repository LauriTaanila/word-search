
typedef struct node
{
    char *word;
    int count;
    struct node* next;
} node_t;

node_t *create_new_node(char *word, int count);

void printlist(node_t *head);

void *insert_at_head(node_t **head, node_t *node_to_insert);

int find_value(node_t *head, char *word);