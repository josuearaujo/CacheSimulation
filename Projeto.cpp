#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>

using namespace std;

struct LinhaCache{
	unsigned long int TAG;
	unsigned char validade=0; 
};

void Filho1_checarMapeamento_ColunaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]);
void Filho1_checarMapeamento_LinhaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]);

void Filho2_checarMapeamento_ColunaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]);
void Filho2_checarMapeamento_LinhaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]);

void Filho3_checarMapeamento_ColunaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[8][8]);
void Filho3_checarMapeamento_LinhaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[8][8]);

void limparCache(LinhaCache CACHE[8][8], int &hits, int &miss);
void limparCache(LinhaCache CACHE[64], int &hits, int &miss);

void filho1(int hits, int miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]);
void filho2(int hits, int miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]);
void filho3(int hits, int miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[8][8]);


int main(){
	LinhaCache CACHE[64];
	LinhaCache CACHE2[8][8];
	unsigned char MEMORIA[100][1000];
	int hits = 0;
	int miss = 0;

	pid_t Filho1, Filho2, Filho3;
	Filho1 = fork();
	if(Filho1 != 0){
		Filho2 = fork();
		if(Filho2 != 0){
			Filho3 = fork();
			if(Filho3 != 0){
				wait();
				wait();
				wait();
			}else{ //FILHO 3
				filho3(hits, miss, MEMORIA, CACHE2);
			}
		}else{ //FILHO 2
			filho2(hits, miss, MEMORIA, CACHE);
		}
	}else{ //FILHO 1
		filho1(hits, miss, MEMORIA, CACHE);
	}
	return 0;
}

void filho1(int hits, int miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]){
	ofstream arquivo1;
	arquivo1.open("Filho1.log");	

	Filho1_checarMapeamento_ColunaInterno(hits, miss, MEMORIA, CACHE);
	cout << "-----------MAPEAMENTO DIRETO-------------\n";
	cout << "~~~~~~COLUNA INTERNO~~~~~~" << endl;
	cout << "HITS: " << hits << endl;
	cout << "MISS: " << miss << endl;
	cout << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;

	arquivo1 << "-----------MAPEAMENTO DIRETO-------------\n\n";
	arquivo1 << "~~~~~~COLUNA INTERNO~~~~~~" << endl;
	arquivo1 << "HITS: " << hits << endl;
	arquivo1 << "MISS: " << miss << endl;
	arquivo1 << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;

	limparCache(CACHE, hits, miss);

	Filho1_checarMapeamento_LinhaInterno(hits, miss, MEMORIA, CACHE);
	cout << "-----------MAPEAMENTO DIRETO-------------\n";
	cout << "~~~~~~LINHA INTERNO~~~~~~" << endl;
	cout << "HITS: " << hits << endl;
	cout << "MISS: " << miss << endl;
	cout << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;

	arquivo1 << "~~~~~~LINHA INTERNO~~~~~~" << endl;
	arquivo1 << "HITS: " << hits << endl;
	arquivo1 << "MISS: " << miss << endl;
	arquivo1 << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl;

	arquivo1.close();
}

void filho2(int hits, int miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]){
	ofstream arquivo2;
	arquivo2.open("Filho2.log");	

	Filho2_checarMapeamento_ColunaInterno(hits, miss, MEMORIA, CACHE);
	cout << "----------- MAPEAMENTO ASSOCIATIVO ---------\n";
	cout << "~~~~~~COLUNA INTERNO~~~~~~" << endl;
	cout << "HITS: " << hits << endl;
	cout << "MISS: " << miss << endl;
	cout << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;

	arquivo2 << "-----------MAPEAMENTO ASSOCIATIVO-------------\n\n";
	arquivo2 << "~~~~~~COLUNA INTERNO~~~~~~" << endl;
	arquivo2 << "HITS: " << hits << endl;
	arquivo2 << "MISS: " << miss << endl;
	arquivo2 << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;

	limparCache(CACHE, hits, miss);

	Filho2_checarMapeamento_LinhaInterno(hits, miss, MEMORIA, CACHE);
	cout << "----------- MAPEAMENTO ASSOCIATIVO ---------\n";
	cout << "~~~~~~LINHA INTERNO~~~~~~" << endl;
	cout << "HITS: " << hits << endl;
	cout << "MISS: " << miss << endl;
	cout << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl;

	arquivo2 << "~~~~~~LINHA INTERNO~~~~~~" << endl;
	arquivo2 << "HITS: " << hits << endl;
	arquivo2 << "MISS: " << miss << endl;
	arquivo2 << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;

	arquivo2.close();
}

void filho3(int hits, int miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[8][8]){
	ofstream arquivo3;
	arquivo3.open("Filho3.log");	

	Filho3_checarMapeamento_ColunaInterno(hits, miss, MEMORIA, CACHE);
	cout << "----------- MAPEAMENTO ASSOCIATIVO EM CONJUNTO ---------\n";
	cout << "~~~~~~COLUNA INTERNO~~~~~~" << endl;
	cout << "HITS: " << hits << endl;
	cout << "MISS: " << miss << endl;
	cout << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;

	arquivo3 << "-----------MAPEAMENTO ASSOCIATIVO EM CONJUNTO-------------\n\n";
	arquivo3 << "~~~~~~COLUNA INTERNO~~~~~~" << endl;
	arquivo3 << "HITS: " << hits << endl;
	arquivo3 << "MISS: " << miss << endl;
	arquivo3 << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;

	limparCache(CACHE, hits, miss);

	Filho3_checarMapeamento_LinhaInterno(hits, miss, MEMORIA, CACHE);
	cout << "----------- MAPEAMENTO ASSOCIATIVO EM CONJUNTO ---------\n";
	cout << "~~~~~~LINHA INTERNO~~~~~~" << endl;
	cout << "HITS: " << hits << endl;
	cout << "MISS: " << miss << endl;
	cout << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl;

	arquivo3 << "~~~~~~LINHA INTERNO~~~~~~" << endl;
	arquivo3 << "HITS: " << hits << endl;
	arquivo3 << "MISS: " << miss << endl;
	arquivo3 << "TAXA DE ACERTO: " << (double(hits)/(hits+miss))*100 << "%" << endl << endl;
	arquivo3.close();
}



void Filho1_checarMapeamento_ColunaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]){
	unsigned long int endereco;
	unsigned long int tag;
	unsigned int linha;
	for(int i=0; i<100; i++){
		for(int j=0; j<1000; j++){
			endereco = (unsigned long int)(&MEMORIA[i][j]);
			linha = ((endereco & 0b1111110000)>>4);
			tag = (endereco >> 10);

			if(CACHE[linha].validade == 0){
				miss++;
				CACHE[linha].validade = 1;
				CACHE[linha].TAG = tag;
			}
			else{
				if(CACHE[linha].TAG == tag){
					hits++;
				}
				else{
					miss++;
					CACHE[linha].TAG = tag;
				}
			}

		}
	}
}

void Filho1_checarMapeamento_LinhaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]){
	unsigned long int endereco;
	unsigned long int tag;
	unsigned int linha;
	for(int j=0; j<1000; j++){
		for(int i=0; i<100; i++){
			endereco = (unsigned long int)(&MEMORIA[i][j]);
			linha = ((endereco & 0b1111110000)>>4);
			tag = (endereco >> 10);

			if(CACHE[linha].validade == 0){
				miss++;
				CACHE[linha].validade = 1;
				CACHE[linha].TAG = tag;
			}
			else{
				if(CACHE[linha].TAG == tag){
					hits++;
				}
				else{
					miss++;
					CACHE[linha].TAG = tag;
				}
			}
		}
	}
}


void Filho2_checarMapeamento_ColunaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]){
	unsigned long int endereco;
	unsigned long int tag;
	int FIFO=0;

	//VERIFICANDO SE O ENDEREÇO JÁ SE ENCONTRA NA CACHE
	for(int i = 0; i<100; i++){	            
			for(int j=0; j<1000; j++){ 		
			endereco = (unsigned long int)(&MEMORIA[i][j]);
			tag = (endereco >> 4);
			bool precisaSerAdicionado = true;
			bool primeiroVazio = true;

			//PROCURANDO TAG NA CACHE
			for(int k=0; k<64; k++){
				if(CACHE[k].validade == 1){
					if(CACHE[k].TAG == tag){
						hits++;
						precisaSerAdicionado = false; //SE NÃO ENCONTRAR O ELEMENTO NA CACHE, ESSA VARIÁVEL VAI PERMANECER "TRUE"
						break;
					}
				}
			}

			//SE NÃO TIVER ENCONTRADO A TAG, ADICIONAR ENDEREÇO NA CACHE
			if(precisaSerAdicionado == true){	//ESSA VARIAVEL BOOLEANA INDICA SE O ENDEREÇO FOI ENCONTRADO NA CACHE OU NÃO
				miss++;
				CACHE[FIFO].validade = 1;
				CACHE[FIFO].TAG = tag;
				FIFO++;
				FIFO = FIFO%64;
			}
		}
	}
}

void Filho2_checarMapeamento_LinhaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[64]){
	unsigned long int endereco;
	unsigned long int tag;
	int FIFO=0;

	//VERIFICANDO SE O ENDEREÇO JÁ SE ENCONTRA NA CACHE
	for(int j=0; j<1000; j++){
		for(int i = 0; i<100; i++){			
			endereco = (unsigned long int)(&MEMORIA[i][j]);
			tag = (endereco >> 4);
			bool precisaSerAdicionado = true;
			bool primeiroVazio = true;

			//PROCURANDO TAG NA CACHE
			for(int k=0; k<64; k++){
				if(CACHE[k].validade == 1){
					if(CACHE[k].TAG == tag){
						hits++;
						precisaSerAdicionado = false; //SE NÃO ENCONTRAR O ELEMENTO NA CACHE, ESSA VARIÁVEL VAI PERMANECER "TRUE"
						break;
					}
				}
			}

			//SE NÃO TIVER ENCONTRADO A TAG, ADICIONAR ENDEREÇO NA CACHE
			if(precisaSerAdicionado == true){	//ESSA VARIAVEL BOOLEANA INDICA SE O ENDEREÇO FOI ENCONTRADO NA CACHE OU NÃO
				miss++;
				CACHE[FIFO].validade = 1;
				CACHE[FIFO].TAG = tag;
				FIFO++;
				FIFO = FIFO%64;
			}
		}
	}
}


void Filho3_checarMapeamento_ColunaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[8][8]){
	unsigned long int endereco;
	unsigned long int tag;
	unsigned int conjunto;
	int vetFIFO[8] = {};

	for(int i=0; i<100; i++){
		for(int j=0; j<1000; j++){
			endereco = (unsigned long int)(&MEMORIA[i][j]);
			conjunto = ((endereco & 0b1110000)>>4);
			tag = (endereco>>7);
			bool precisaSerAdicionado = true;

			for(int k=0; k<8; k++){
				if(CACHE[conjunto][k].validade == 1){
					if(CACHE[conjunto][k].TAG == tag){
						hits++;
						precisaSerAdicionado = false;
						break;
					}
				}
			}

			if(precisaSerAdicionado == true){
				miss++;
				CACHE[conjunto][vetFIFO[conjunto]].validade = 1;
				CACHE[conjunto][vetFIFO[conjunto]].TAG = tag;
				vetFIFO[conjunto]++;
				vetFIFO[conjunto]= vetFIFO[conjunto]%8;
			}
		}
	}
}


void Filho3_checarMapeamento_LinhaInterno(int &hits, int &miss, unsigned char MEMORIA[100][1000], LinhaCache CACHE[8][8]){
	unsigned long int endereco;
	unsigned long int tag;
	unsigned int conjunto;
	int vetFIFO[8] = {};

	for(int j=0; j<1000; j++){
		for(int i=0; i<100; i++){
			endereco = (unsigned long int)(&MEMORIA[i][j]);
			conjunto = ((endereco & 0b1110000)>>4);
			tag = (endereco>>7);
			bool precisaSerAdicionado = true;

			for(int k=0; k<8; k++){
				if(CACHE[conjunto][k].validade == 1){
					if(CACHE[conjunto][k].TAG == tag){
						hits++;
						precisaSerAdicionado = false;
						break;
					}
				}
			}

			if(precisaSerAdicionado == true){
				miss++;
				CACHE[conjunto][vetFIFO[conjunto]].validade = 1;
				CACHE[conjunto][vetFIFO[conjunto]].TAG = tag;
				vetFIFO[conjunto]++;
				vetFIFO[conjunto]= vetFIFO[conjunto]%8;
			}
		}
	}
}

void limparCache(LinhaCache CACHE[8][8], int &hits, int &miss){
	hits = 0;
	miss = 0;

	for(int i=0; i<64; i++){
		CACHE[0][i].validade = 0;
	}
}

void limparCache(LinhaCache CACHE[64], int &hits, int &miss){
	hits=0;
	miss=0;

	for(int i=0; i<64; i++){
		CACHE[i].validade = 0;
	}
}