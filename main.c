//
// fakefalso - Programa para gerar números válidos de CPF, RG, cartão de 
//             crédito e CEP. 
//           
//             Desenvolvido para fins educacionais.      
//
//             Disponibilizado gratuitamente e sem garantia.
//
//             Autor :     fepra e andrevrpires
//             Versão:     0.1
//             Licença:    GNU GPL 3
//             Criado:     26/10/2016
//             Atualizado: 28/10/2016
//
//             Compilar:   ./makefile 
//                         gcc -o ff main.c geradores.c
//
//             Implementar: validadores de números de CPF, RG, cartão de
//             crédito e CEP; função de ajuda; checagem de erro nas funções; e
//             gerador de nomes.
//

#include <stdio.h>       // funções de I/O 
#include <stdlib.h>      // funções srand(), rand() e exit()
#include <string.h>      // função strcpy()
#include <stdbool.h>     // tipo bool
#include <time.h>        // função time()
#include <getopt.h>      // função getopt()
#include <sys/types.h>   // tipo pid_t
#include <unistd.h>      // funções fork() e execl()
#include "geradores.h"   // funções para gerar os números 

//
// magic numbers para caracteres de espaço, ponto e traço utilizados para a 
// formatação dos dados gerados
//
#define ESPACO ' ' 
#define PONTO  '.'
#define TRACO  '-'

//
// função principal
//
int
main(int argc, char **argv)
{
    //
    // definição da estrutura para armazenar os dados gerados formatados
    //
    struct pessoa {     
        char cpf[15];
        char rg[13];
        char cartao[20];
        char cep[11];
    };

    struct pessoa pessoa_fisica; // estrutura para armazenar os dados gerados
    struct pessoa pessoa_ultima; // estrutura para armazenar os dados salvos

    enum bandeira credito = VISA; // bandeira padrão VISA
    enum estado regiao = SP;      // estado padrão SP

    //
    // variaveis de controle
    //
    int opt;             // armazena as opções da linha de comando
    int exec;            // armazena o valor de retorno da função execl()
    
    pid_t pid;           // armazena o valor de retorno da função fork()

    FILE *arquivo;       // ponteiro para a estrutura FILE para I/O

    bool email = false;  // define se o e-mail será aberto
    bool save = false;   // define se os dados serão salvos
    bool ultimo = false; // define se os últimos dados salvos serão carregados

    //
    // vetores de inteiros para armazenar os dados gerados sem formatação
    //
    int cpf[11];
    int rg[9];
    int cartao[16];
    int cep[8];

    //
    // vetores de caracteres para armazenar os dados gerados formatados
    //
      char cpf_formatado[] = {
        ESPACO, 
        ESPACO, 
        ESPACO, 
        PONTO, 
        ESPACO, 
        ESPACO, 
        ESPACO, 
        PONTO, 
        ESPACO, 
        ESPACO, 
        ESPACO, 
        TRACO, 
        ESPACO, 
        ESPACO, 
        '\0'
    }; 
    
    char rg_formatado[] = {
        ESPACO, 
        ESPACO, 
        PONTO, 
        ESPACO, 
        ESPACO, 
        ESPACO, 
        PONTO, 
        ESPACO, 
        ESPACO,
        ESPACO,
        TRACO, 
        ESPACO, 
        '\0'
    };
  
    char cartao_formatado[] = {
        ESPACO,
        ESPACO,
        ESPACO,
        ESPACO,
        TRACO,
        ESPACO,
        ESPACO,
        ESPACO,
        ESPACO,
        TRACO,
        ESPACO,
        ESPACO,
        ESPACO,
        ESPACO,
        TRACO,
        ESPACO,
        ESPACO,
        ESPACO,
        ESPACO,
        '\0'
    };

    char cep_formatado[] = {
        ESPACO,
        ESPACO,
        ESPACO,
        PONTO,
        ESPACO,
        ESPACO,
        TRACO,
        ESPACO,
        ESPACO,
        ESPACO,
        '\0'
    };

    //
    // laço para função getopt() processar as opções da linha de comando
    // escrever funções para checar as opções 'b' e 'r'
    //
    while ((opt = getopt(argc, argv, ":b:r:esu")) != -1)
    {
        switch (opt)                  
        {
            case 'b':                    // enum credito
                credito = atoi(optarg);
                break;
            case 'r':                    // enum regiao
                regiao = atoi(optarg);
                break;
            case 'e':                    // bool email
                email = true;
                break;
            case 's':                    // bool save
                save = true;
                break;
            case 'u':                    // bool ultimo
                ultimo = true;
                break;
            default:                     // escrever função de ajuda
                break;
        }
    }

    //
    // chamar a função srand() para alimentar a função rand() utilizada nos 
    // geradores
    //
    srand(time(NULL));

    //
    // chamar as funções para gerar e formatar os dados
    //
    gera_cpf(cpf);
    formata_cpf(cpf, cpf_formatado);

    gera_rg(rg);
    formata_rg(rg, rg_formatado);

    gera_cartao(cartao, credito);
    formata_cartao(cartao, cartao_formatado);

    gera_cep(cep, regiao);
    formata_cep(cep, cep_formatado);

    //
    // chamar a função strcpy() para copiar os dados formatados para os membros 
    // da estrutura pessoa_fisica
    //
    strcpy(pessoa_fisica.cpf, cpf_formatado);
    strcpy(pessoa_fisica.rg, rg_formatado);
    strcpy(pessoa_fisica.cartao, cartao_formatado);
    strcpy(pessoa_fisica.cep, cep_formatado);

    //
    // imprimir na tela os dados gerados
    //
    printf("\n\t\t\tFake Falso - Gerador de dados \n"); 
    printf("\nDados gerados:\n");
    printf("\nCPF              : %s\n", pessoa_fisica.cpf);
    printf("RG               : %s\n", pessoa_fisica.rg);
    printf("Cartão de crédito: %s\n", pessoa_fisica.cartao);
    printf("CEP              : %s\n", pessoa_fisica.cep);

    //
    // imprimir a estrutura salva no arquivo "fake" se a opção "-u" foi 
    // fornecida - checar os erros
    //
    if (ultimo)
    {
        arquivo = fopen("fake", "rb");
        if (arquivo == NULL)
            exit(EXIT_FAILURE);

        fread(&pessoa_ultima, sizeof(struct pessoa), 1, arquivo);
        fclose(arquivo);
        printf("\nDados carregados do arquivo:\n");
        printf("\nÚltimo CPF gerado              : %s\n", pessoa_ultima.cpf);
        printf("Último RG gerado               : %s\n", pessoa_ultima.rg);
        printf("Último cartão de crédito gerado: %s\n", pessoa_ultima.cartao);
        printf("Último CEP gerado              : %s\n\n", pessoa_ultima.cep);
    }

    //
    // salvar a estrutura no arquivo "fake" se a opção "-s" foi fornecida -     
    // checar os erros
    //
    if (save)
    {
        arquivo = fopen("fake", "wb");
        if (arquivo == NULL)
            exit(EXIT_FAILURE);
 
        printf("\nDados gravados no arquivo\n");       
        fwrite(&pessoa_fisica, sizeof(struct pessoa), 1, arquivo);
        fclose(arquivo);
    }

    //
    // abrir o firefox no site mintemail.com se a opção e foi fornecida - 
    // checar os erros - utilizar a função wait()
    //
    if (email)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("Abrindo e-mail.\n");
            exec = execl("/usr/bin/firefox", "firefox", 
                         "www.mintemail.com", NULL);
            if (exec == -1)
                perror ("execl");
        }
        else if (pid > 1)
            exit(EXIT_SUCCESS);
        else
            exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
    
