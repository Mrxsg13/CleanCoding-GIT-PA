//Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf                                                                                                                                                                                                                                                
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

typedef struct graph
{
    int nr_restaurante;
    int *visited;
    struct Node **adjlist;
} Graph;

typedef struct stack
{   int top;
    int capacitate;
    int *arr;
} Stack;

Node *create_node(int value)
{
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph *g, int src, int dest)
{
    Node *new_node = create_node(dest);

    new_node -> next = g->adjlist[src];
    g -> adjlist[src] = new_node;

    new_node = create_node(src);

    new_node->next = g->adjlist[dest];
    g->adjlist[dest] = new_node;
}

Graph *create_graph(int vertices)
{
    int i;
    Graph *graph = malloc(sizeof(Graph));

    graph->nr_restaurante = vertices;
    graph->adjlist = malloc(sizeof(Node *) * vertices);
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph->adjlist[i] = NULL;
        graph->visited[i] = 0;
    } 
    return graph;
}

Stack *create_stack(int capacitate)
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->arr = malloc(capacitate * sizeof(int));
    stack->top = -1;
    stack->capacitate = capacitate;

    return stack;
}

void push(int pushed, Stack *stack)
{
    stack->top++;
    stack->arr[stack->top] = pushed;
}

void DFS(Graph *graph, Stack *stack, int nr_restaurant)
{
    Node *adj_list = graph->adjlist[nr_restaurant];
    Node *aux = adj_list;
    graph->visited[nr_restaurant] = 1;

    printf("%d ", nr_restaurant);
    push(nr_restaurant, stack);

    while (aux != NULL)
    {
        int restaurant_conectat = aux->data;

        if (graph->visited[restaurant_conectat] == 0)
        { 
            DFS(graph ,stack, restaurant_conectat);
        }
        aux = aux->next;
    }
}

void insert_edges(Graph *graph, int edge_nr, int nr_restaurante)
{
    int src, dest, i;
    printf("Adauga %d munchii (de la 0 la %d)\n", edge_nr, nr_restaurante - 1);

    for (i = 0; i < edge_nr; i++)
    {
        printf("Conexiunea %d: ", i + 1);
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void clear_visited(Graph *graph, int nr_vertices)
{
    for (int i = 0 ; i < nr_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}    

int verify_connection(Graph *graph, int nr_vertices, Stack *stack1, Stack *stack2)// 0 sau 1 daca poate fi sau nu ajuns
{
    int exista = 0;

    for (int i = 0; i < nr_vertices; i++) // aici i tine loc de numar adica de restaurant
    {
        clear_visited(graph, nr_vertices);
        DFS(graph, stack1, i);

        for (int j = 0; j < nr_vertices; j++)
            {
                if (graph->visited[j] != 0 && i !=j)
                {
                    exista = 1;
                }
            }
    }

    return exista;
}
            
int main()
{

    int nr_restaurante, nr_drumuri, i;
    int ans;

    printf("Cate restaurante sunt?");
    scanf("%d", &nr_restaurante);

    printf("Cate conexiuni exista?");
    scanf("%d", &nr_drumuri);

    Graph *graph = create_graph(nr_restaurante);

    Stack *stack1 = create_stack(nr_restaurante);
    Stack *stack2 = create_stack(nr_restaurante);

    insert_edges(graph, nr_drumuri, nr_restaurante);

    ans = verify_connection(graph, nr_restaurante, stack1, stack2);

    if (ans)
    {
        printf("\nExista drum direct intre doua restaurante.");
    }
    else 
    {
        printf("\nNu exista drum direct intre doua restaurante.");
    }

    return 0;
}