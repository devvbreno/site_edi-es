#include <stdio.h>
#include <string.h>
#include <locale.h> 

#define MAX_AGENDAMENTOS 100


typedef struct Projeto_Final
{
    char nomeCliente[50];
    char servico[50];
    char carro[50];
    int dia, mes, ano;
    int horario;

} Agendamento;

// validação de data
int dataValida (int dia, int mes, int ano) {

    if (mes < 1 || mes > 12 || dia < 1) return 0;
    
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return dia <= diasNoMes[mes - 1]; // mes - 1 seria para acessar a quantidade de dias desse mes   
}

// validaçãop de horário (entre 0000 e 2359)
int horarioValido(int horario) {
    int hora = horario / 100;
    int minuto = horario % 100;

    return (hora >= 0 && hora <= 23 && minuto >= 0 && minuto < 60);

}

// verificar se há conflito de data e horario
int Conflito(Agendamento agenda[], int total, int dia, int mes, int ano, int horario) {

    for (int i = 0; i < total; i++)
    {
        if (agenda[i].dia == dia && agenda[i].mes == mes && agenda[i].ano == ano && agenda[i].horario == horario) 
        {
            return 1;
        }
        
    }
    return 0; // se nn houver conflito
}
void telaInicial() {
    
    printf("****************\n");
    printf("*                                            *\n");
    printf("*         SISTEMA DE AGENDAMENTO             *\n");
    printf("*                                            *\n");
    printf("*     Desenvolvido por: Breno Elias          *\n");
    printf("*     Mátricula : 242028815                  *\n");
    printf("*     Disciplina: APC - Prof. Clenio         *\n");
    printf("*                                            *\n");
    printf("****************\n\n");

    printf("Bem-vindo ao sistema!\n");
    printf("Escolha uma das opções abaixo para continuar:\n\n");


}

void cadastrarAgendamento(Agendamento agenda[], int *total) {

    if (*total >= MAX_AGENDAMENTOS)
    {
        printf("Limite de agendamento atingido. \n");
        return;          // caso a quantia de agendamentos ultrapasse de 100 
    }

    getchar(); // elimina o buffer do teclado, que sobra evitando que atrapalhe
    
    printf("Digite o nome do cliente:");
    fgets((agenda[*total]).nomeCliente, 50, stdin);
    strtok(agenda[*total].nomeCliente, "\n"); // remove

    printf("Digite o nome do serviço:");
    fgets((agenda[*total]).servico, 50, stdin);
    strtok(agenda[*total].servico, "\n"); 

    printf("Digite o nome do carro:");
    fgets((agenda[*total]).carro, 50, stdin);
    strtok(agenda[*total].carro, "\n"); 

    // validar data

    int dia, mes, ano, horario;

    do  {
        printf("Digite o dia do agendamento (1 - 31):");
        scanf("%d", &dia);

        printf("Digite o mês do agendamento (1 - 12):");
        scanf("%d", &mes);

        printf("Digite o ano do agendamento :");
        scanf("%d", &ano);

        if (!dataValida (dia, mes, ano)) {
            printf ("Data inválida. Tente novamente. \n \n");
        }
        
    } while (!dataValida(dia, mes, ano));
    
    // validar horario
    do
    {
        printf("Digite o horário (formato 24hr, ex: 1630): /n /n");
        scanf("%d", &horario);

        if (!horarioValido(horario))
        {
            printf ("Horário inválido. Tente novamente \n \n");
        }       

    } while (!horarioValido(horario));
    
    // conflito
    if (Conflito(agenda, *total, dia, mes, ano, horario))
    {
        printf(" Já existe um agendamento para essa data e horário. Escolha outro.\n\n");
        return;
    }
    
    // se as validações passarem, é salvo:
    agenda[*total].dia = dia;
    agenda[*total].mes = mes;
    agenda[*total].ano = ano;
    agenda[*total].horario = horario;

    (*total)++; 
    printf ("Agendamento registrado com sucesso! \n\n");

}

void verAgendaSemana (Agendamento agenda[], int total) {

    printf("\n Agenda da Semana:\n");
    printf("+-----+----------+----------------------+----------------------+---------+--------+\n");
    printf("| Dia | Horário  | Cliente              | Serviço              | Carro   | Data   |\n");
    printf("+-----+----------+----------------------+----------------------+---------+--------+\n");

    for (int i = 0; i < total; i++) {
        printf("| %02d  | %04d    | %-20s | %-20s | %-7s | %02d/%02d/%d |\n",
               agenda[i].dia,
               agenda[i].horario,
               agenda[i].nomeCliente,
               agenda[i].servico,
               agenda[i].carro,
               agenda[i].dia,
               agenda[i].mes,
               agenda[i].ano);         // tabela
    }

    if (total == 0) {
        printf("|     |          | Nenhum agendamento para esta semana.         |         |        |\n");
    }
    
    printf("+-----+----------+----------------------+----------------------+---------+--------+\n\n");

}

void buscarCliente(Agendamento agenda[],int total){
     if (total == 0) {
        printf("  Nenhum agendamento registrado ainda.\n\n");
        return;
    }

    getchar(); // limpa o buffer antes de fgets

    char nomeBusca[50];
    int encontrados = 0;

    printf("Digite o nome do cliente para buscar: ");
    fgets(nomeBusca, 50, stdin);
    strtok(nomeBusca, "\n"); // remove o \n

    printf("\n Resultados da busca por \"%s\":\n", nomeBusca);
    printf("+-----+----------+----------------------+----------------------+---------+------------+\n");
    printf("| Dia | Horário  | Cliente              | Serviço              | Carro   | Data       |\n");
    printf("+-----+----------+----------------------+----------------------+---------+------------+\n");

    for (int i = 0; i < total; i++) {
        if (strcmp(agenda[i].nomeCliente, nomeBusca) == 0) {
            encontrados++;
            printf("| %02d  | %04d    | %-20s | %-20s | %-7s | %02d/%02d/%04d |\n",
                   agenda[i].dia,
                   agenda[i].horario,
                   agenda[i].nomeCliente,
                   agenda[i].servico,
                   agenda[i].carro,
                   agenda[i].dia,
                   agenda[i].mes,
                   agenda[i].ano);
        }
    }

    if (encontrados == 0) {
        printf("|     |          | Nenhum agendamento encontrado com esse nome.              |\n");
    }

    printf("+-----+----------+----------------------+----------------------+---------+------------+\n\n");

}

int main() {

    setlocale(LC_ALL, "pt_BR.UTF-8");

    Agendamento agenda[MAX_AGENDAMENTOS];
    int totalAgendamento = 0;
    int opcao;

    telaInicial();

    do {
        printf("-------- Menu de Agendamentos-------\n\n");
        printf("1 - Agendar Atendimento\n");
        printf("2 - Ver Agenda da Semana\n");
        printf("3 - Buscar por cliente \n");
        printf("4 - Sair\n\n");
        
        if (scanf("%d", &opcao) != 1) {  // tava tendo problemas com o while pq estava rodando com lixo  
        printf(" Entrada inválida! Digite um número.\n");

        while (getchar() != '\n'); 
        opcao = -1;
        continue;
        }

        switch (opcao) {
            case 1:
            cadastrarAgendamento(agenda, &totalAgendamento);
            break;

            case 2:
            verAgendaSemana(agenda, totalAgendamento);
            break;

            case 3:
            buscarCliente(agenda, totalAgendamento);
            break;  

            case 4:
            printf("Saindo do sistema... Até mais! \n");
            break;    

            default:
            printf(" Opção inválida. Tente novamente.\n");

        }
    } while (opcao != 4);
    
    return 0;
}