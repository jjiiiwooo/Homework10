#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; //�θ� ��� 

void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

void set_union(int a, int b)
{
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2)
		parent[root1] = root2;
}

typedef struct Edge {
	int start, end, weight;
}Edge;

typedef struct GraphType {
	int n; //������ ���� 
	int nvertex; //������ ���� 
	struct Edge edges[2 * MAX_VERTICES];
}GraphType;

//���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

//�� �Լ� 
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

//ũ�罺Į
void Kruskal(GraphType* g)
{
	int edge_aceepted = 0; //������� ���õ� ������ �� 
	int uset, vset; //���� u�� ���� v�� ���� ��ȣ 
	struct Edge e;

	set_init(g->nvertex);
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("Kruskal MST Algorithm\n");
	int i = 0;
	while (edge_aceepted < (g->nvertex - 1))
	{
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("Edge (%d %d) Select %d", e.start, e.end, e.weight);
			edge_aceepted++;
			set_union(uset, vset);
		}
		i++;
	}
}


int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	g->nvertex = 
	insert_edge(g, 1, 6,11);
	insert_edge(g, 6, 5, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 9, 10, 10);
	insert_edge(g, 10, 8, 15);
	insert_edge(g, 8,7,13);
	insert_edge(g, 7, 1, 12);
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 7,3, 6);

	kruskal(g);
	free(g);
	return 0;
}