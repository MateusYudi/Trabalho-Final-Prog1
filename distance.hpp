#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <math.h>
#include "split.hpp"
#include <iomanip>
using namespace std;

fstream Cep, Municipios; //Inicializar arquivo

void abre_cep(); //Função do arquivo dos CEP's
void abre_municipios_br(); //Função do arquivo que possui as coordenadas das cidades


void distancia_simples(){ //Função que é chamada no cabeçalho, para pesquisar as distâncias entre 2 cidades
    bool procurar_cep = false; //Booleana para procura da Cidade
    cout << fixed << setprecision(3);
    string linha;
    string cidade_cep1,cidade_cep2;
    string cidade_estado1,cidade_estado2;
    string lat_cid1,lat_cid2;
    string long_cid1,long_cid2;
    int cep1,cep2;
    float alfa,beta,gama;
    float cidade1_lat,cidade1_long;
    float cidade2_lat,cidade2_long;
    float longitude, distancias;
    float pi = 3.1415926536;
    float raio = 6372.795477598;

    cout << "Distancia entre cidade: " << endl;
    cout << "De: " ;
    cin >> cep1;
    cout << "Ate: " ;
    cin >> cep2;
    //Cidade 1
    abre_cep();
    while(Cep.good()){ //Condição de parada: Final do arquivo
        getline(Cep,linha); //Leitura do arquivo
        if (linha.size()== 0){ //Condição de parada: Final do arquivo
            break;
        }
        vector<string> v = split(linha, ';'); //Separa em vetores, todos os itens de 1 linha
        int cep_inicio = atoi(v[1].c_str()); //Transforma o vetor secundário(string) em inteiro
        int cep_final = atoi(v[2].c_str()); //Transforma o vetor terciário(string) em inteiro
        if (cep1>=cep_inicio && cep1<=cep_final){ //Identificar uma cidade entre os 2 CEPs
            cidade_cep1 = v[0]; //Atribui o nome da Cidade a variavel
            cidade_estado1 = v[0] + "-" + v[3]; //Atribui o estado da cidade a variavel
            procurar_cep = true; //Booleana para parar a procura da cidade
        }
    }
    Cep.close(); //Fechar o arquivo
    //Cidade 2
    abre_cep();
    while(Cep.good()){
        getline(Cep,linha);
        if (linha.size()== 0){
            break;
        }
        vector<string> v = split(linha, ';');
        int cep_inicio = atoi(v[1].c_str());
        int cep_final = atoi(v[2].c_str());
        if (cep2>=cep_inicio && cep2<=cep_final){
            cidade_cep2 = v[0];
            cidade_estado2 = v[0] + "-" + v[3];
            procurar_cep = true;
        }
    }
    Cep.close();
    //Latitude e Longitude cidade 1
    abre_municipios_br();
    while(Municipios.good()){
        getline(Municipios, linha);
        if (linha.size()== 0){
            break;
        }
        vector<string> v = split(linha, ';');
        if(cidade_cep1 == v[3]){
            lat_cid1 = v[1]; //Atribui ao vetor secundário o valor da latitude da cidade 1
            long_cid1 = v[2]; //Atribui ao vetor terciário o valor da longitude da cidade 1
        }
    }
    Municipios.close();

    // Latitude Longitude cidade 2
    abre_municipios_br(); //Abrir o arquivo de long/lat
    while(Municipios.good()){ //Ler até o final do arquivo
        getline(Municipios, linha);
        if (linha.size()== 0){
            break;
        }
        vector<string> v = split(linha, ';');
        if(cidade_cep2 == v[3]){
            lat_cid2 = v[1]; //Atribui ao vetor secundário o valor da latitude da cidade 2
            long_cid2 = v[2]; //Atribui ao vetor terciário o valor da longitude da cidade 2
        }
    }
    Municipios.close();

    //Cálculo da distância



    cidade1_lat = atof(lat_cid1.c_str());  //Transforma o valor da variavel string em double
    cidade1_long = atof(long_cid1.c_str());
    cidade2_lat = atof(lat_cid2.c_str());
    cidade2_long = atof(long_cid2.c_str());

    //Transforma os graus em radianos
    cidade1_lat = cidade1_lat* pi/180;
    cidade1_long = cidade1_long* pi/180;
    cidade2_lat = cidade2_lat* pi/180;
    cidade2_long = cidade2_long* pi/180;
    longitude =  (cidade1_long - cidade2_long);


    alfa = (sin(cidade1_lat) * (sin(cidade2_lat))); //Calculo para descobrir as distâncias
    beta = (cos(cidade1_lat) * (cos(cidade2_lat)));
    gama = cos(longitude);
    distancias = raio * (acos(alfa + beta * gama));

    cout << cidade_estado1 << " -> " << cidade_estado2 << " "; // Mostrar os nomes das cidades digitadas
    cout << "Distancia: " << distancias << endl; // Mostrar a distância


}
    void distancia_bloco(){ // Função que faz a função 2
    string arquivo_ceps;    // Nome do arquivo que possuí os ceps
    string linha;           // String auxiliar para contar quantos CEPs possuem no arquivo
    int con=0;              // Contar quantos CEPs possuem no arquivo
    cout << "Insira o nome do arquivo CSV: " << endl;
    cin >> arquivo_ceps;

    fstream cep1; //Criar uma stream do arquivo
    cep1.open(arquivo_ceps.c_str(),ios::in); //Abrir o arquivo para leitura

    while(cep1.good()){ //Condição de parada: Final do arquivo
        getline(cep1,linha); //Ler arquivo
        con++;
    }

    cout<<endl;

    int cod[con]; //Declarar o vetor que fica com os CEPs do arquivo
    cep1.clear(); //Limpa todos parâmetros do cep1
    cep1.seekg(0,ios::beg); //Volta o arquivo para o começo
    con=0; //Zera o contador
    while(cep1.good()){
        cep1>>cod[con]; //Passar o CEP para o cod
        con++;
    }
     fstream cep2;
    cep2.open("distances.csv", ios::out | ios::trunc); //Abrir o arquivo para escrita, deleta e cria um novo arquivo
    for(int i = 0; i < con; i++){ //Comparar primeiro cep com os outros
        for(int j = i + 1; j < con - 1; j++){ //Comparar segundo cep com os outros

    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO

    bool procurar_cep = false; //Booleana para procura da Cidade
    string linha;
    string cidade_cep1,cidade_cep2;
    string cidade_estado1,cidade_estado2;
    string lat_cid1,lat_cid2;
    string long_cid1,long_cid2;
    double alfa,beta,gama;
    double cidade1_lat,cidade1_long;
    double cidade2_lat,cidade2_long;
    double radiano, latitude, longitude, distancias;
    float pi = 3.1415926536;
    float raio = 6372.795477598;
//Cidade 1
    abre_cep();
    while(Cep.good()){ //Condição de parada: Final do arquivo
        getline(Cep,linha); //Leitura do arquivo
        if (linha.size()== 0){ //Condição de parada: Final do arquivo
            break;
        }
        vector<string> v = split(linha, ';'); //Separa em vetores, todos os itens de 1 linha
        int cep_inicio = atoi(v[1].c_str()); //Transforma o vetor secundário(string) em inteiro
        int cep_final = atoi(v[2].c_str()); //Transforma o vetor terciário(string) em inteiro
        if (cod[i]>=cep_inicio && cod[i]<=cep_final){ //Identificar uma cidade entre os 2 CEPs
            cidade_cep1 = v[0]; //Atribui o nome da Cidade a variavel
            cidade_estado1 = v[0] + "-" + v[3]; //Atribui o estado da cidade a variavel
            procurar_cep = true; //Booleana para parar a procura da cidade
        }
    }
    Cep.close(); //Fechar o arquivo
    //Cidade 2
    abre_cep();
    while(Cep.good()){
        getline(Cep,linha);
        if (linha.size()== 0){
            break;
        }
        vector<string> v = split(linha, ';');
        int cep_inicio = atoi(v[1].c_str());
        int cep_final = atoi(v[2].c_str());
        if (cod[j]>=cep_inicio && cod[j]<=cep_final){
            cidade_cep2 = v[0];
            cidade_estado2 = v[0] + "-" + v[3];
            procurar_cep = true;
        }
    }
    Cep.close();
    //Latitude e Longitude cidade 1
    abre_municipios_br();
    while(Municipios.good()){
        getline(Municipios, linha);
        if (linha.size()== 0){
            break;
        }
        vector<string> v = split(linha, ';');
        if(cidade_cep1 == v[3]){
            lat_cid1 = v[1]; //Atribui ao vetor secundário o valor da latitude da cidade 1
            long_cid1 = v[2]; //Atribui ao vetor terciário o valor da longitude da cidade 1
        }
    }
    Municipios.close();

    // Latitude Longitude cidade 2
    abre_municipios_br(); //Abrir o arquivo de long/lat
    while(Municipios.good()){ //Ler até o final do arquivo
        getline(Municipios, linha);
        if (linha.size()== 0){
            break;
        }
        vector<string> v = split(linha, ';');
        if(cidade_cep2 == v[3]){
            lat_cid2 = v[1]; //Atribui ao vetor secundário o valor da latitude da cidade 2
            long_cid2 = v[2]; //Atribui ao vetor terciário o valor da longitude da cidade 2
        }
    }
    Municipios.close();

    //Cálculo da distância
    cidade1_lat = atof(lat_cid1.c_str());  //Transforma o valor da variavel string em double
    cidade1_long = atof(long_cid1.c_str());
    cidade2_lat = atof(lat_cid2.c_str());
    cidade2_long = atof(long_cid2.c_str());
    //Transforma os graus em radianos
    cidade1_lat = cidade1_lat* pi/180;
    cidade1_long = cidade1_long* pi/180;
    cidade2_lat = cidade2_lat* pi/180;
    cidade2_long = cidade2_long* pi/180;
    longitude =  (cidade1_long - cidade2_long);
    alfa = (sin(cidade1_lat) * (sin(cidade2_lat))); //Calculo para descobrir as distâncias
    beta = (cos(cidade1_lat) * (cos(cidade2_lat)));
    gama = cos(longitude);
    distancias = raio * (acos(alfa + beta * gama));

    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO
    //PASSAR PARA UMA FUNÇÃO

    cout << cidade_estado1 << "; CEP: " <<cod[i] << " -> " << cidade_estado2 <<"; CEP: " <<cod[j] << " "; // Mostrar os nomes das cidades digitadas
    cout << "; " << distancias << " KM" << endl; // Mostrar a distância
    cep2 << cidade_estado1  << "; CEP: " << cod[i] << "; "; //Passar as informações para o novo arquivo criado
    cep2 << cidade_estado2  << "; CEP: " << cod[j]  << "; "; //Passar as informações para o novo arquivo
    cep2 << fixed << setprecision(3) << distancias<< " KM\n"; //Passar as informações para o novo arquivo

        }
    }
    cep2.close();
}
void abre_cep(){ //Função que transforma o arquivo das cidades em string
    string cep_arquivo = "cep.csv";
    Cep.open(cep_arquivo.c_str(),ios::in); //Abre arquivo
};
void abre_municipios_br(){ //Função que transforma o arquivo das long/lat em string
    string cidades = "municipios_br.csv";
    Municipios.open(cidades.c_str(),ios::in); //Abre arquivo
};

