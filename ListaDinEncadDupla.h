#define N 50

struct schedule{
	char subject[N];
	char local[N];
	char name[N];
	int startTime;
	int endTime;
	int effort;
	int priority;
	int presence;
	int event;
};

typedef struct component* List;

List* creatList();


// Declaração dos prototipos das funções

void freeList(List* LI);

int sizeList(List* LI);

int findList(List* LI, int num, struct schedule *SC);

int insertList(List* LI, struct schedule SC);

int removeList(List* LI, int num);

void printList(List *LI);

void printEvent(List *LI);

void writeSchedule(List* LI, char email[]);

void readSchedule(List* LI, char email[]);