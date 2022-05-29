#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
typedef long long ll;

struct Node
{
    ll data;
    Node *next;
    Node *prev;
};

void insert_before(Node **head, ll data, bool move)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = *head;
    if(*head != NULL) {
        new_node->prev = (*head)->prev;
    }
    else {
        new_node->prev = NULL;
    }
    
    if(*head != NULL && (*head)->prev != NULL) {
        (*head)->prev->next = new_node;
        (*head)->prev = new_node;
    }
    else if(*head != NULL) {
        (*head)->prev = new_node;
    }
    if(move) *head = new_node; // do only for head ptr
}

void insert_after(Node **tail, ll data, bool move)
{
    Node *new_node = (Node*)malloc(sizeof(Node));;
    new_node->data = data;
    if(*tail != NULL) {
        new_node->next = (*tail)->next;
    }
    else {
        new_node->next = NULL;
    }
    new_node->prev = *tail;

    if(*tail != NULL && (*tail)->next != NULL) {
        (*tail)->next->prev = new_node;
        (*tail)->next = new_node;
    }
    else if(*tail != NULL) {
        (*tail)->next = new_node;
    }
    if(move) *tail = new_node; // do only for tail ptr
}

void remove(Node **head)
{
    if (*head == NULL)
        return;
    
    if ((*head)->next == NULL && (*head)->prev != NULL) {
        Node *temp = *head;
        *head = (*head)->prev;
        (*head)->next = NULL;
        free(temp);
        return;
    }

    Node *temp = *head;
    Node *prev = (*head)->prev;
    *head = (*head)->next;
    if (*head != NULL && prev != NULL) {
        (*head)->prev = prev;
        (*head)->prev->next = *head;
    }
    else if(*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

void print_list(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        if(temp->data != -1) {
            printf("%lld ", temp->data);
        }
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    Node *head = NULL;
    Node *tail = NULL;
    int n = 0;
    char c[2];
    char x[3];
    Node** ptrs = (Node**)malloc(10 * sizeof(Node*));
    ll y;
    while (scanf("%s", c) != EOF)
    {
        switch (c[0])
        {
        case 'I':
            scanf("%lld", &y);
            break;
        case 'A':
        case '.':
            scanf("%s %lld", x, &y);
            if (strcmp(x, "BEG") == 0 || n == 0) {
                insert_before(&head, y, true);
            }
            else if (strcmp(x, "END") == 0) {
                insert_after(&tail, y, true);
            }
            else if (c[0] == 'A')
                insert_after(&ptrs[x[0] - 48], y, false);
            else if (c[0] == '.')
                insert_before(&ptrs[x[0] - 48], y, false);
            if(n == 0) {
                tail = head;
            }
            n++;
            break;
        
        case 'R':
            scanf("%s", x);
            if(n == 0) break;
            Node* ptr;
            if (strcmp(x, "BEG") == 0) {
                ptr = head;
                remove(&head);
            }
            else if (strcmp(x, "END") == 0) {
                ptr = tail;
                remove(&tail);
            }
            else {
                ptr = ptrs[x[0] - 48];
                remove(&ptrs[x[0] - 48]);
            }
            if (n == 1) {
                head = NULL;
                tail = NULL;
            }
            n--;
            break;
        
        case 'P':
            scanf("%s", x);
            if (strcmp(x, "ALL") == 0)
                print_list(head);
            else
                print_list(ptrs[x[0] - 48]);
            break;
        
        case 'i':
            scanf("%lld %x", &y, &x);
            if (strcmp(x, "BEG") == 0)
                ptrs[y] = head;
            else if (strcmp(x, "END") == 0)
                ptrs[y] = tail;
            else
                ptrs[y] = ptrs[x[0] - 48];
            break;
        
        case '+':
            scanf("%lld", &y);
            if (ptrs[y] != tail)
                ptrs[y] = ptrs[y]->next;
            break;
        
        case '-':
            scanf("%lld", &y);
            if (ptrs[y] != head)
                ptrs[y] = ptrs[y]->prev;
            break;

        default:
            break;
        }
    }
    
    while(head != NULL) {
        remove(&head);
    }

    return 0;
}