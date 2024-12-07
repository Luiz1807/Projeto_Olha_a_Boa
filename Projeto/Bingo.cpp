#include <iostream>


using namespace std;

const int TAMANHO_CARTELA = 5; // Define o tamanho fixo da cartela como 5x5 
                               // (uma cartela de bingo padrão tem 5 linhas e 
                              //5 colunas)
                              
struct NumerosChamados {
    int numeros[75];  // Vetor que armazenará até 75 números chamados
    int quantidade;  // Um contador que indica quantos números já foram chamados até o momento
}; 

struct Cartela {
    string matriz[TAMANHO_CARTELA][TAMANHO_CARTELA];  // Matriz para armazenar os números da cartela
    bool marcada[TAMANHO_CARTELA][TAMANHO_CARTELA];   // Matriz para armazenar o estado (marcado ou não) de cada número
};  

// Função que irá gerar o numeros aleatórios, recebendo como parâmetro o intervalo, a quantidade de cada coluna e o vetor que irá armazenar os valores aleatório.
void gerar_numeros(int inicio, int fim, int quantidade, int numeros[]) {
    int i = 0; //  será usado para controlar quantos números únicos já foram gerados e armazenados no vetor.
    while (i < quantidade) { 
        int num = rand() % (fim - inicio + 1) + inicio;  // Gera um número aleatório no intervalo e salva na variável num
        bool ja_existe = false; //  variável para verificar se o número gerado já está no vetor
        for (int j = 0; j < i; ++j) { // enquanto j for menor doque os numeros da coluna faça... 
            if (numeros[j] == num) { // se o numero que esta salvo na variavel numeros[j] for igual ao numero que acabou de receber o valor aleatório então...
                ja_existe = true;
                break;
            }
        }
        if (!ja_existe) { // Verifica se ja_existe é false, ou seja, se o número é único
            numeros[i] = num;  // Se o número for único, adiciona ao vetor
            i++;  // Avança para o próximo número aleatório
        }
    }
}


// Função que faz a criação das cartelas onde a mesma chama outras funções para preencher as cartelas
Cartela criar_cartela() { 

Cartela cartela; //Variável que armazenará a cartela ja pronta e será o valor de saída

int B[5], I[5], N[5], G[5], O[5]; // Vetores que serão as colunas da cartela

//Função que irá preencher os vetores com os numeros aleatórios 
   gerar_numeros(1, 15, 5, B); 
    gerar_numeros(16, 30, 5, I);
    gerar_numeros(31, 45, 5, N);
    gerar_numeros(46, 60, 5, G);
    gerar_numeros(61, 75, 5, O);

 for (int i = 0; i < TAMANHO_CARTELA; ++i) { //Enquanto i for menor doque o tanto de colunas... 
       
       //preenchendo a variável cartela com os resultados que estão sendo convertidos para String 
        cartela.matriz[i][0] = to_string(B[i]); 
        cartela.matriz[i][1] = to_string(I[i]);
        cartela.matriz[i][2] = (i == 2 ? "FREE" : to_string(N[i])); // Se a matrize for[2][2] (o centro) adicionará "FREE" 
        cartela.matriz[i][3] = to_string(G[i]);
        cartela.matriz[i][4] = to_string(O[i]);

        // Adicionando o valor booleano 'false' para todas as posições da segunda matriz que será de comparação e como nenhum valor foi marcado começa com false todas

        for (int j = 0; j < TAMANHO_CARTELA; ++j) {
            cartela.marcada[i][j] = false;
        }
    }

    // Retornando a cartela ja criada com seus espaços ja preenchidos
    return cartela;
}


//Função que irá exibir as tabelas ja criadas recebendo a cartela ja pronta[]
void exibir_cartela(const Cartela& cartela) {  
    cout << "___________________________________" << endl;
    cout << "B        I       N       G       O" << endl;
    cout << "___________________________________" << endl;

   //Loop que irá mostrar os números que estão salvos dentro da matriz  

    for (int i = 0; i < TAMANHO_CARTELA; ++i) {
        for (int j = 0; j < TAMANHO_CARTELA; ++j) {
            cout << cartela.matriz[i][j] << "\t";
        }
        cout << endl;
    }
}


// Função para marcar um número na cartela, que irá receber as duas matrizes (de numero e de valor booleano) e o número que foi selecionado 
bool marcar_numero(Cartela& cartela, int numero) {

   //Loop que irá fazer com que percorra as posições das duas matrizes 
    for (int i = 0; i < TAMANHO_CARTELA; ++i) {
        for (int j = 0; j < TAMANHO_CARTELA; ++j) {

           // Se o numero que esta dentro da cartela.matriz[i][j] for igual ao numero passado na função então...
            if (cartela.matriz[i][j] == to_string(numero)) {
                cartela.marcada[i][j] = true;  // Marca verdadeiro na posição que coincidiu com o valor passado da matriz de booleanos
                cartela.matriz[i][j] = "X";    // Marca X na posição que estava batendo os numeros
                return true; // retorna como verdadeiro e que coincidiu os numeros
            }
        }
    }

   // caso não coincida os numeros, retorna falso indicando que não achou nenhum numero na cartela
    return false;
}


// Função para salvar cartelas em arquivos recebendo a matriz com os numeros da cartela e um id para identificar o arquivo da tabela 
void salvar_cartela_em_arquivo(const Cartela& cartela, int id) {
    char nome_arquivo[20]; // Variável que salva o nome do arquivo 
    sprintf(nome_arquivo, "cartela_%d.txt", id); //Nomeando o arquivo com base no ID passado 
    FILE* arquivo = fopen(nome_arquivo, "w"); // Abrindo arquivo para escrever nele  

    if (arquivo) { // Se o arquivo foi aberto para subscrever com sucesso então... 
        fprintf(arquivo, "B        I       N       G       O\n");

        //Loop que irá percorrer as posições da matriz e inserir no arquivo  
        for (int i = 0; i < TAMANHO_CARTELA; ++i) {
            for (int j = 0; j < TAMANHO_CARTELA; ++j) {

                // faz a inserção dos numeros (e FREE) dentro do arquivo
                fprintf(arquivo, "%s\t", cartela.matriz[i][j].c_str());  
            }
            fprintf(arquivo, "\n"); //Pula linha para a próxima linha ser preenchida 
        }
        fclose(arquivo);

        // Após o processo se tem a seguinte mensagem de sucesso

        cout << "Cartela " << id << " salva em " << nome_arquivo << endl;
    } else { //Se não foi aberto para subscrever o arquivo dá a seguinte mensagem 
        cout << "Erro ao salvar a cartela no arquivo!" << endl;
    }
}


// Função para verificar as mensagens especiais que receberá a cartela e o id da cartela para saber qual cartela está sendo verificada.
void verificar_mensagens_especiais(Cartela& cartela, int id_cartela) {
    bool linha_completa, coluna_completa; // variaveis que serão utilizadas para controlar o estado da linha e coluna 

    // Verificar linhas completas
    for (int i = 0; i < TAMANHO_CARTELA; ++i) {
        linha_completa = true;
        for (int j = 0; j < TAMANHO_CARTELA; ++j) {

	    //Se o valor da matriz marcada for igual a false (ou seja, não foi marcado o numero) e o valor da matriz matriz for diferente de "FREE" (ou seja, for um numero)  então... 
            if (!cartela.marcada[i][j] && cartela.matriz[i][j] != "FREE") {
                linha_completa = false;
                break; // sai do for mais interno e pula para a próxima linha para a próxima verificação
            }
        }
        if (linha_completa) { // se a linha for true então aparece a mensagem 
            cout << "Cartela " << id_cartela + 1 << ": LINHA COMPLETA!" << endl;
        }
    }
    
        // Verificar colunas completas
    for (int i = 0; i < TAMANHO_CARTELA; ++i) {
        coluna_completa = true;
        for (int j = 0; j < TAMANHO_CARTELA; ++j) {
            if (!cartela.marcada[j][i] && cartela.matriz[j][i] != "FREE") {
                coluna_completa = false;
                break;
            }
        }
        if (coluna_completa) {
            cout << "Cartela " << id_cartela + 1 << ": COLUNA COMPLETA!" << endl;
        }
    }



    // Verificar cartela completa ou quase completa
    int numeros_nao_marcados = 0; // variavel que fará a verificação se é bingo ou olha a boa 
    for (int i = 0; i < TAMANHO_CARTELA; ++i) {
        for (int j = 0; j < TAMANHO_CARTELA; ++j) {
            if (!cartela.marcada[i][j] && cartela.matriz[i][j] != "FREE") {
                numeros_nao_marcados++; //incrementa 
            }
        }
    }

    // Se a variavel numeros_nao_marcados for igual a 0 significa que todos os numeros foram preenchidos fazendo assim o bingo
    if (numeros_nao_marcados == 0) {
        cout << "Cartela " << id_cartela + 1 << ": BINGO!" << endl;

      // Se não, se a variavel numeros_nao_marcados for igual a 1 significa que falta apenas 1 numero para completar a cartela, fazendo assim o "Olha a boa!" 

    } else if (numeros_nao_marcados == 1) {
        cout << "Cartela " << id_cartela + 1 << ": Olha a boa!" << endl;
    }
}


// Função para exibir os números que ja foram chamados recebendo a struct que salva a quantidade de numeros ja sorteados e o vetor que armazena os numeros chamados 
void exibir_numeros_chamados(const NumerosChamados& chamados) {
    cout << "Números chamados: ";

    // loop que percorre o vetor para mostrar os numeros ja chamados que estão dentro do vetor

    for (int i = 0; i < chamados.quantidade; ++i) {
        cout << chamados.numeros[i] << " ";
    }
    cout << endl;
}


// Função principal que exibe o menu de seleção para o usuário 
void menu() {
    Cartela cartelas[10]; //variavel que será responsável em passar as matrizes 
    NumerosChamados numeros_chamados = { {}, 0 }; //Variavel que será responsável em inicializar todas as posições de numeros[] com o valor de 0 e quantidade também 0 
    int quantidade_cartelas = 0; // variavel que conta quantas cartelas ja foram criadas 

    int opcao;
    do {
        cout << "\n--- Menu Bingo ---\n";
        cout << "1. Criar nova cartela\n";
        cout << "2. Exibir cartelas\n";
        cout << "3. Marcar número\n";
        cout << "4. Exibir números chamados\n";
        cout << "5. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                if (quantidade_cartelas < 10) {
                    
                   //cartelas recebe a tabela que acabou de ser gerada

                    cartelas[quantidade_cartelas] = criar_cartela();

                   //Passa a cartela que acabou de ser criada para salvar em arquivo

                    salvar_cartela_em_arquivo(cartelas[quantidade_cartelas], quantidade_cartelas + 1);
                    quantidade_cartelas++;
                } else {
                    cout << "Número máximo de cartelas alcançado!" << endl;
                }
                break;
            }
            case 2: {

                //Loop que faz com que apareça as tabelas existentes

                for (int i = 0; i < quantidade_cartelas; ++i) {
                    cout << "\nCartela " << i + 1 << ":" << endl;
                    exibir_cartela(cartelas[i]);
                }
                break;
            }
            case 3: {
                int numero;
                cout << "Digite o número a ser marcado: ";
                cin >> numero;
            
                //Se a quatidade de numeros chamados for menor que 75 executa o if

                if (numeros_chamados.quantidade < 75) {
                    numeros_chamados.numeros[numeros_chamados.quantidade++] = numero;
                }
                bool marcado_em_alguma_cartela = false; // variavel que serve para ser usada na comparação do trecho final
                for (int i = 0; i < quantidade_cartelas; ++i) { //loop que passa pelas cartelas ja criadas 
                    
                    //Se o retorno da função for verdadeiro (se o numero foi marcado) então... 
                    if (marcar_numero(cartelas[i], numero)) {

                        //verifica se há alguma mensagem de linha, coluna, olha a boa ou Bingo disponivel
                        verificar_mensagens_especiais(cartelas[i], i);
                        marcado_em_alguma_cartela = true; // Continua marcando outras cartelas
                    }
                }
                
                if (marcado_em_alguma_cartela) {
                    cout << "Número marcado com sucesso!" << endl;
                }
            
                if (!marcado_em_alguma_cartela) {
                    cout << "Número não encontrado em nenhuma cartela!" << endl;
                }
                break;
            }

            case 4:
                exibir_numeros_chamados(numeros_chamados);
                break;
            case 5:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } while (opcao != 5);
}


int main() {
    menu();
    return 0;
}