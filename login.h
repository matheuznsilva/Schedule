#define N 50

struct info{
	int id;
	char Name[N];
	char LastName[N];
	char email[N];
	int password;
	Lista *LI;
};

typedef struct elemento* Login;

Login* cria_login();

// Declaracao dos prototipos das funcoes

void libera_logins(Login* LO);

int busca_email(Login* LO, char email[], struct info *al);

int insere_login(Login* LO, struct info al);

int remove_login(Login* LO, int num);

void imprime_Logins(Login *LO);

void EscreverLogins(Login *LO);

void loadingData(Lista* LI, char email[]);

void loadingSchedule(Login* LO);

