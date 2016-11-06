//
// Arquivo contendo as funções para os geradores e formatadores:
//
// CPF    - gera_cpf(int *cpf) e formata_cpf(int *n, char *cpf_formatado) 
// RG     - gera_rg(int *rg) e formata_rg(int *n, char *rg_formatado)
// Cartão - gera_cartao(int *cartao, int bandeira) e 
//          formata_cartao(int *n, char *cartao_formatado)  
// CEP    - gera_cep(int *cep, int estado) e 
//          formata_cep(int *n, char *cep_formatado)
//
// Contém também a função raiz_digital(int n) para calcular a raiz digital de
// um número.
//

#include <stdlib.h>    // função rand()
#include <ctype.h>     // função isspace()
#include "geradores.h" // variáveis enum bandeira e enum estado

int
raiz_digital(int n)
{
    return 1 + ((n - 1) % 9);
}

void
gera_cpf(int *cpf)
{
    int i = 0;
    int soma = 0;
    int resto = 0;

    for (i = 0; i < 9; i++) 
    {
        cpf[i] = rand() % 10;
        soma += cpf[i] * (10 - i);
    }

    resto = soma % 11;

    cpf[9] = resto < 2 ? 0 : 11 - resto;

    for (i = 0, soma = 0; i < 10; i++)
        soma += cpf[i] * (11 - i);

    resto = soma % 11;

    cpf[10] = resto < 2 ? 0 : 11 - resto;
}   

void
formata_cpf(int *n, char *cpf)
{
    int i = 0;

    while (i < 11)
        if (isspace(*cpf))
            *cpf++ = n[i++] + '0';
        else
            cpf++;
} 
    
void
gera_rg(int *rg)
{
    int i;
    int soma = 0;
    int resto = 0;

    for (i = 0; i < 8; i++) 
    {
        rg[i] = rand() % 10;
        soma += rg[i] * (2 + i);
    }
    
    resto = soma % 11;

    rg[8] = resto < 2 ? 0 : 11 - resto;
}

void
formata_rg(int *n, char *rg)
{
    int i = 0;

    while (i < 9)
        if (isspace(*rg))
            *rg++ = n[i++] + '0';
        else
            rg++; 
}

int
gera_cartao(int *cartao, int bandeira)
{
    int i;
    int soma = 0;
    int resto = 0;

    switch(bandeira) 
    {
        case VISA: 
            cartao[0] = 4; 
            i = 1;
            soma = 8; 
            break;
        case MASTER: 
            cartao[0] = 5; 
            cartao[1] = 1;
            i = 2;
            soma = 2; 
            break;
        case DINERS: 
            cartao[0] = 3; 
            cartao[1] = 6;
            i = 2;
            soma = 12;
            break;
        case DISCOVER: 
            cartao[0] = 6; 
            cartao[1] = 5;
            i = 2;
            soma = 8;
            break;
        case AMERICAN: 
            cartao[0] = 3; 
            cartao[1] = 4;
            i = 2;
            soma = 10;
            break;
        default:
            return -1;
            break;
    }

    for (; i < 15; i++) 
    {
        cartao[i] = rand() % 10;
        if (i % 2)
            soma += cartao[i];
        else if (cartao[i] * 2 < 10)
            soma += cartao[i] * 2;
        else
            soma += raiz_digital(cartao[i] * 2);
    }

    resto = soma % 10;
       
    cartao[15] = resto > 0 ? 10 - resto : 0;  

    return 0;
}

void
formata_cartao(int *n, char *cartao)
{
    int i = 0;

    while (i < 16)
        if (isspace(*cartao))
            *cartao++ = n[i++] + '0';
        else
            cartao++;
}

//
// gera números de CEP incorretos pois faltam dados sobre as subregiões,
// setores, subsetores, divisores e identificadores de distribuição
//
int
gera_cep(int *cep, int estado)
{
    int i;

    switch(estado) 
    {
        case SP:
            cep[0] = 0;
            cep[1] = 1;
            cep[7] = 1;
            i = 2;
            break;
        case SI:
            cep[0] = 1;
            i = 1;
            break;
        case RJ:
            cep[0] = 2;
            cep[1] = 0;
            i = 2;
            break;
        case ES:
            cep[0] = 2;
            cep[1] = 9;
            i = 2;
            break;
        case MG:
            cep[0] = 3;
            i = 1;
            break;
        case BA:
            cep[0] = 4;
            cep[1] = 0;
            i = 2;
            break;
        case SE:
            cep[0] = 4;
            cep[1] = 9;
            i = 2;
            break;
        case PE:
            cep[0] = 5;
            cep[1] = 0;
            i = 2;
            break;
        case AL:
            cep[0] = 5;
            cep[1] = 7;
            i = 2;
            break;
        case PB:
            cep[0] = 5;
            cep[1] = 8;
            i = 2;
            break;
        case RN:
            cep[0] = 5;
            cep[1] = 9;
            i = 2;
            break;
        case CE:
            cep[0] = 6;
            cep[1] = 0;
            i = 2;
            break;
        case PI:
            cep[0] = 6;
            cep[1] = 4;
            i = 2;
            break;
        case MA:
            cep[0] = 6;
            cep[1] = 5;
            i = 2;
            break;
        case PA:
            cep[0] = 6;
            cep[1] = 6;
            i = 2;
            break;
        case AP:
            cep[0] = 6;
            cep[1] = 8;
            i = 2;
            break;
        case AM:
            cep[0] = 6;
            cep[1] = 9;
            cep[2] = 0;
            i = 3;
            break;
        case RR:
            cep[0] = 6;
            cep[1] = 9;
            cep[2] = 3;
            i = 3;
            break;
        case AC:
            cep[0] = 6;
            cep[1] = 9;
            cep[2] = 9;
            i = 3;
            break;
        case GO:
            cep[0] = 7;
            cep[1] = 2;
            i = 2;
            break;
        case TO:
            cep[0] = 7;
            cep[1] = 7;
            i = 2;
            break;
        case MT:
            cep[0] = 7;
            cep[1] = 8;
            cep[2] = 0;
            i = 3;
            break;
        case MS:
            cep[0] = 7;
            cep[1] = 9;
            i = 2;
            break;
        case RO:
            cep[0] = 7;
            cep[1] = 8;
            cep[2] = 9;
            i = 3;
            break;
        case DF:
            cep[0] = 7;
            cep[1] = 0;
            i = 2;
            break;
        case PR:
            cep[0] = 8;
            cep[1] = 0;
            i = 2;
            break;
        case SC:
            cep[0] = 8;
            cep[1] = 8;
            i = 2;
            break;
        case RS:
            cep[0] = 9;
            i = 1;
            break;
        default:
            return -1;
            break;
    }

    for (; i < 7; i++)
        cep[i] = rand() % 10;

    return 0;      
}

void
formata_cep(int *n, char *cep)
{
    int i = 0;

    while (i < 8)
        if (isspace(*cep))
            *cep++ = n[i++] + '0';
        else
            cep++;
}

