#define N 50

struct info{
	int id;
	char Name[N];
	char LastName[N];
	char email[N];
	int password;
	List *LI;
};

typedef struct element* Login;

Login* creatLogin();

// Declaração dos prototipos das funções

void freeLogin(Login* LO);

int findEmail(Login* LO, char email[], struct info *al);

int insertLogin(Login* LO, struct info al);

int removeLogin(Login* LO, int num);

void printLogin(Login *LO);

void writeLogin(Login *LO);

int menu(struct info *al);