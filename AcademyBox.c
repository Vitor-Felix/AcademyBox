#include <stdio.h>
struct dadosAluno
{
    int matricula;
    char nome[15];
    char sobrenome[10];
    int idade;
    float peso;
    int abdominal;
    int flexao;
    int esteira;
};

    int digitaEscolha(void);
    void arquivoTexto(FILE *lePtr );
    void RemoverAluno(FILE *fPtr );
    void atualizaserie(FILE *fPtr );
    void novoRegistro(FILE *fPtr );

int main(void)
{
    FILE *cfPtr;
    int escolha;

        if( (cfPtr = fopen("cadastro.dat", "rb+")) == NULL) //abre um arquivo binário para leitura e escrita
        printf("Arquivo nao pode ser aberto.\n \a"); //Se o arquivo não existir, o programa não executa e aparece essa mensagem de erro
        else
        {
            while ((escolha = digitaEscolha()) != 5) //digita escolha é um subprograma q retorna um valor para escolha determinado pelo usuário
            {
                switch (escolha) //Se o valor retornado do usuário for diferente de 5 entra no switch se não segue direto e encerra o programa
                {
                    case 1:
                    arquivoTexto(cfPtr); //executa subprograma arquivoTexto que gerá um arquivo texto com os dados dos alunos cadastrados
                    break;

                    case 2 :
                    atualizaserie(cfPtr); // executa atualizaserie que pesquisa dados de um usuário e permite atualizar as séries de exercício dele
                    break;

                    case 3:
                    novoRegistro(cfPtr); // executa novoRegistro que matricula um aluno
                    break;

                    case 4:
                    RemoverAluno(cfPtr); // executa RemoverAluno que deleta um aluno do cadastro
                    break;

                    default:
                    printf("Escolha incorreta\n \a"); //mensagem de erro caso o usuário digite uma opção invalida
                    system("cls"); //limpa a tela
                    break;
                } //fecha o switch
            }   //fecha o while
            fclose(cfPtr);
        } //fecha o else
    return 0;
}; //fecha o main



void arquivoTexto(FILE *lePtr) //subprograma para gerar um arquivo do tipo .txt com os dados cadastrados de cada aluno
{
    FILE *gravaPtr;

    struct dadosAluno aluno = {0, "", "", 0, 0.0}; // zerando os valores dos elementos da struct

    if ((gravaPtr = fopen("dados_dos_alunos.txt", "w")) == NULL) //cria um arquivo texto para escrita
    {
        printf("Arquivo nao pode ser aberto.\n \a"); //mensagem de erro caso não seja possivel criar o arquivo
    }

    else
    {
        rewind(lePtr); //Define um ponteiro para o inicio do arquivo
        fprintf(gravaPtr, "%-6s%-16s%-lls%10s%15s\n",
        "Matricula", "Nome", "Sobrenome", "Idade", "Peso"); //escreve no arquivo

        while (!feof(lePtr)) //Devolve verdadeiro se o fim de arquivo foi atingido
        {
            fread(&aluno, sizeof(struct dadosAluno), 1, lePtr); //permite a leitura de blocos de qualquer tipo de dados

            if (aluno.matricula != 0)
            {
                fprintf(gravaPtr, "%-6d%-16s%-lls%10d%15.2f\n",
                aluno.matricula, aluno.nome, aluno.sobrenome, aluno.idade, aluno.peso);
            }//fim do if
        }//fim do while
    }//fim do else
    fclose(gravaPtr);
    system("cls"); //limpa a tela
    printf("\n \n Arquivo gerado com sucesso, acesse a pasta raiz do programa para ter acesso aos dados cadastrados \n \n \a");
} //fim do subprograma



void atualizaserie(FILE *fPtr) // esse subprograma pesquisa um aluno pela matricula e atualiza a série q o aluno realizou e mostra em % o quanto esse aluno melhorou
{
    int conta;
    int abdominal;
    int flexao;
    int esteira;
    float x;
    struct dadosAluno aluno = {0, "", "", 0, 0.0, 0, 0, 0};

    printf("Digite a conta a atualizar (1 - 100): ");
    scanf("%d", &conta);

    fseek(fPtr, (conta - 1) * sizeof(struct dadosAluno), SEEK_SET); //o fseek posiciona o arquivo em um byte específico
    fread(&aluno, sizeof(struct dadosAluno), 1, fPtr); //o fread permite a leitura e a escrita de blocos de qualquer tipo de dado

    if (aluno.matricula == 0)
    {
       printf("Matricula #%d nao contem informações.\n \a", conta); //mensgem de erro
    }
    else
    {
        printf("%-6d%-16s%-lls%10d%10.2f\n\n",
        aluno.matricula, aluno.nome, aluno.sobrenome, aluno.idade, aluno.peso);
        int simb_perc = 37; //declarando uma variável para imprimir o caractere %, pois 37 = % na tabela ASCII

        printf("Digite o numero de abdominais: ");//essa parte se repete para os demais exercícios, para inserir mais atividades é só aumentar umas linhas de códigos
        scanf("%d", &abdominal);

        if(aluno.abdominal!= 0)
            {
                x = (abdominal-aluno.abdominal) * 100/ aluno.abdominal; // algoritimo que cálcula o rendimento em % do aluno com relação ao dia anterior
                printf("Voce aumentou sua serie em %.2f %c \n", x,simb_perc); // declarando simb_perc como %c podemos imprimir o caractere '%'
            }

        aluno.abdominal = abdominal;

        printf("Digite o numero de flexao: ");
        scanf("%d", &flexao);

        if(aluno.flexao!= 0)
            {
                x = (flexao-aluno.flexao) * 100/ aluno.flexao; // algoritimo que cálcula o rendimento em % do aluno com relação ao dia anterior
                printf("Voce aumentou sua serie em %.2f %c \n", x,simb_perc);  // declarando simb_perc como %c podemos imprimir o caractere '%'
            }
        aluno.flexao = flexao;

        printf("Digite o numero de esteira: ");
        scanf("%d", &esteira);

        if(aluno.esteira!= 0)
            {
                x = (esteira-aluno.esteira) * 100/ aluno.esteira; // algoritimo que cálcula o rendimento em % do aluno com relação ao dia anterior
                printf("Voce aumentou sua serie em %.2f %c \n", x,simb_perc);  // declarando simb_perc como %c podemos imprimir o caractere '%'
            }
        aluno.esteira = esteira;

        printf("%-6d%-16s%-lls%10d%10.2f\n\n",
        aluno.matricula, aluno.nome, aluno.sobrenome, aluno.idade, aluno.peso);

        fseek(fPtr, (conta - 1) * sizeof(struct dadosAluno), SEEK_SET); //fseek posiciona um arquivo em um byte específico
        fwrite(&aluno, sizeof(struct dadosAluno), 1, fPtr); // fwrite permite a escrita de blocos de qualquer tipo de dado
    }
    system("pause"); //apenas para usuários de windows, pausa a execução do programa
    system("cls"); //limpa a tela, necessário q esteja ligada ao system pause, pois se não os dados sumirão da tela do usuário sem q ele possa enxergar;
}



void RemoverAluno(FILE *fPtr) //programa para remover um aluno da academia
{
    struct dadosAluno aluno;
    struct dadosAluno alunoNulo = {0, "", "", 0, 0.0};
    int numeroConta;

    printf ("Digite o numero da matricula do aluno que deseja excluir (1 - 100): ");
    scanf ("%d", &numeroConta); //se a matricula não possiur um aluno cadastrado irá imprimir uma mensagem de erro

    fseek (fPtr, (numeroConta - 1) * sizeof(struct dadosAluno), SEEK_SET); //o fseek posiciona o arquivo em um byte específico
    fread (&aluno, sizeof(struct dadosAluno), 1, fPtr); //o fread permite a leitura e a escrita de blocos de qualquer tipo de dado

    if (aluno.matricula == 0)
    {
        printf("Matricula #%d nao existe.\n \a", numeroConta); //mensagem de erro caso a matricula não exista
        system("pause");//apenas para windowns
        system("cls");//apenas para o windows, pois necessita do pause para mostrar a imagem de erro
    }

        else
        {
            fseek(fPtr, (numeroConta - 1) * sizeof(struct dadosAluno), SEEK_SET); //o fseek posiciona o arquivo em um byte específico
            fwrite(&alunoNulo, sizeof(struct dadosAluno), 1, fPtr); // fwrite permite a escrita de blocos de qualquer tipo de dado

            printf("O aluno foi removido com sucesso \n \a");

            system("pause");//apenas para windowns
            system("cls");//apenas para o windows, pois necessita do pause para mostrar a imagem de erro

        }
}



void novoRegistro(FILE *fPtr) //subprograma para matricular um aluno
{
    struct dadosAluno aluno = { 0, "", "", 0, 0.0};
    int matricula;

    printf ("Digite um numero de matricula para o novo aluno (1 - 100): ");
    scanf ("%d", &matricula);

    fseek (fPtr, (matricula - 1) * sizeof(struct dadosAluno), SEEK_SET); //o fseek posiciona o arquivo em um byte específico
    fread (&aluno, sizeof(struct dadosAluno), 1, fPtr) ; //o fread permite a leitura e a escrita de blocos de qualquer tipo de dado

    if (aluno.matricula != 0)
        {
            printf("Matricula #%d ja contem informações.\n \a", aluno.matricula); // Mensagem de erro caso a matricula digitada já exista
        }
    else
    {
        system("cls"); //limpa a tela

        printf("\n Digite o nome do novo aluno:");
        scanf("%s",&aluno.nome);

        printf("\n Digite o Sobrenome do novo aluno:");
        scanf("%s",&aluno.sobrenome);

        printf("\n Digite a idade do novo aluno:");
        scanf("%d",&aluno.idade);

        printf("\n Digite o peso do novo aluno:");
        scanf("%f",&aluno.peso);

        printf("\a"); //som de confirmação de cadastro do usuário
        system("cls"); //limpa a tela


        aluno.matricula = matricula;

        fseek(fPtr, (aluno.matricula - 1) *sizeof(struct dadosAluno),SEEK_SET); //o fseek posiciona o arquivo em um byte específico
        fwrite(&aluno, sizeof(struct dadosAluno), 1, fPtr); //o fread permite a leitura e a escrita de blocos de qualquer tipo de dado
    }
}

int digitaEscolha(void) //subprograma para exibir o menu e receber uma opção de escolha do usuário
{
    int menuChoice;

    printf("\n Bem vindo ao AcademyBox\n"   //menu de opções que será exibido para o usuário
           "\n \n Escolha uma opção para prosseguir\n \n"
           "1-Gerar arquivo de cadastro de todos os alunos matriculados \n"
           "2-Pesquisar dados e atualizar serie de exercicio de um aluno\n"
           "3-Matricular um novo aluno\n"
           "4-Remover um aluno da academia\n"
           "5-Sair\n");
    scanf("%d", &menuChoice); //o que o usuário deseja realizar

    return menuChoice;
}





