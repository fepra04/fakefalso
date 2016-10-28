#ifndef GERADORES_H
#define GERADORES_H

//
// definição de enumeração para armazenar a bandeira do cartão gerado
//
enum bandeira {
    VISA, MASTER, DINERS, DISCOVER, AMERICAN
};

extern enum bandeira credito;

//
// definição de enumeração para armazenar o estado do CEP gerado
//
enum estado {
    SP, SI, RJ, ES, MG, BA, SE, PE, AL, PB, RN, CE, PI, MA, PA, AM, AC, AP,
    RR, GO, TO, MT, MS, RO, DF, PR, SC, RS
};

extern enum estado regiao;

int raiz_digital(int n);

void gera_cpf(int *cpf);
void formata_cpf(int *n, char *cpf_formatado);

void gera_rg(int *rg);
void formata_rg(int *n, char *rg_formatado);

int gera_cartao(int *cartao, int bandeira);
void formata_cartao(int *n, char *cartao_formatado);

int  gera_cep(int *cep, int estado);
void formata_cep(int *n, char *cep_formatado);

#endif
