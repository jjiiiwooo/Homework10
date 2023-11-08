#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; //부모 노드 

//초기화 
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

//curr가 속하는 집합을 반환 
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

//합집합
void set_union(int a, int b)
{
	int root1 = set_find(a); //노드 a의 루트를 찾음
	int root2 = set_find(b); //노드 b의 루트를 찾음
	if (root1 != root2)
		parent[root1] = root2;
}


//간선 구조체
struct Edge {
	int start, end, weight;
};

//그래프 구조체 
typedef struct GraphType {
	int n; //간선의 개수 
	int nvertex; //정점의 개수 
	struct Edge edges[2 * MAX_VERTICES];
}GraphType;

//그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = g->nvertex = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

//간선 삽입 연산 
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start=start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

//비교 함수 
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
//크루스칼 알고리즘 
void Kruskal(GraphType* g)
{
	int edge_accepted = 0; //현재까지 선택된 간선의 수 
	int uset, vset; //정점 u와 정점 v의 집합 번호 
	struct Edge e;

	set_init(g->nvertex); //집합 초기화 
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("qsort version\n");
	printf("Kruskal MST Algorithm \n");
	int i = 0;
	while (edge_accepted < (g->nvertex - 1))
	{
		e = g->edges[i];
		uset = set_find(e.start); //정점 u의 집합 번호 
		vset = set_find(e.end); //정점 v의 집합 번호 
		if (uset != vset) {
			printf("간선 (%d %d) %d Select\n", e.start, e.end, e.weight);
			edge_accepted++;
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

	g->nvertex = 11;
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);

	insert_edge(g, 2, 1, 3);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 2, 4, 4);

	insert_edge(g, 3, 2, 5);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);


	insert_edge(g, 4, 2, 4);
	insert_edge(g, 4, 3, 2);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 10, 16);


	insert_edge(g, 5, 2, 1);
	insert_edge(g, 5, 4, 13);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);

	insert_edge(g, 6, 1, 11);
	insert_edge(g, 6, 2, 7);
	insert_edge(g, 6, 5, 9);

	insert_edge(g, 7, 1, 12);
	insert_edge(g, 7, 2, 8);
	insert_edge(g, 7, 3, 6);
	insert_edge(g, 7, 8, 13);

	insert_edge(g, 8, 3, 5);
	insert_edge(g, 8, 4, 14);
	insert_edge(g, 8, 7, 13);
	insert_edge(g, 8, 10, 15);

	insert_edge(g, 9, 5, 18);
	insert_edge(g, 9, 10, 10);

	insert_edge(g, 10, 4, 16);
	insert_edge(g, 10, 5, 17);
	insert_edge(g, 10, 8, 15);
	insert_edge(g, 10, 9, 10);

	Kruskal(g);
	free(g);
	return 0;

}
