#define N 50

struct agenda{
	char subject[N];
	char local[N];
	char name[N];
	int time_start;
	int time_end;
	int esforco;
	int priority;
	int presenca;
	int evento;
};

typedef struct elemento* Lista;

Lista* cria_lista();


// Declaracao dos prototipos das funcoes

void libera_lista(Lista* li);

int busca_lista(Lista* li, int num, struct agenda *ag);

int insere_lista_ordenada(Lista* li, struct agenda ag);

int remove_lista(Lista* li, int num);

void imprime_Lista(Lista *li);

void imprime_Evento(Lista *LI);
