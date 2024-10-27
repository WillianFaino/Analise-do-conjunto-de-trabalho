#include <bits/stdc++.h>

using namespace std;

//Classe para armazenar e realizar operações sobre as páginas.
class Page
{
	private:
		int pageNumber, tam;
		char *hex;

	public:
		Page(char *hexa, int tamanho)
		{
			hex = hexa;
			tam = tamanho;
			pageNumber = setPageNumber(hex2bin(hex, 32), 32, tam);
		}
	
		//Converter números binários para decimal.
		int bin2dec(int8_t *bin, int qtdbits)
		{
			int dec = 0;
			int m = 1;
			for(int i = qtdbits-1;i>=0;i--)
			{
				dec += bin[i]*m;
				m*=2;
			}
			return dec;
		}

		//Converter números hexadecimais para binário.
		int8_t *hex2bin(char* hex ,int qtdbits)
		{
			int8_t *bin = (int8_t *)malloc(qtdbits);

			int dec = 0, m = 1;
			int temp;

			for(int i=7;i >=0;i--)
			{
				
				//printf("%c", hex[i]);
				
				switch(hex[i])
				{
					case '0':
						temp = 0;
						break;
					case '1':
						temp = 1;
						break;
					case '2':
						temp = 2;
						break;
					case '3':
						temp = 3;
						break;
					case '4':
						temp = 4;
						break;
					case '5':
						temp = 5;
						break;
					case '6':
						temp = 6;
						break;
					case '7':
						temp = 7;
						break;
					case '8':
						temp = 8;
						break;
					case '9':
						temp = 9;
						break;
					case 'a':
						temp = 10;
						break;
					case 'b':
						temp = 11;
						break;
					case 'c':
						temp = 12;
						break;
					case 'd':
						temp = 13;
						break;
					case 'e':
						temp = 14;
						break;
					case 'f':
						temp = 15;
						break;
				}

				dec += temp*m;
				m*=16;

			}
			for(int i = qtdbits-1;i>=0;i--)
			{
				bin[i] = dec%2;
				dec/=2;
			}
			return bin;
		}
	
		//Identificar o número da página.
		int setPageNumber(int8_t *end, int qtdbits, int pgsize)
		{
			int bitsRefDes = log2(pgsize);
			return bin2dec(end,qtdbits-bitsRefDes);
		}
		
		//Exibe algumas informações sobre a página.
		void print()
		{
			printf("hexadecimal: %s\nTamanho: %d\nNúmero: %d\n", hex, tam, pageNumber);
		}
		
		int getPageNumber()
		{
			return pageNumber;
		}
};


int medttl=0;
int menttl=0; //variáveis para armazenar a média dos valores entre todos os traces.
int maittl=0;

//Função para percorrer um arquivo de trace e identificar o número das páginas acessadas e a quantidade de frames necessários para armazená-las a cada janela de tempo.
void runTrace(char *fileName, int pgSize, int delta)
{
	
	FILE *arq;
	
	arq = fopen(fileName, "r");
	fseek(arq,0,SEEK_END);
	int arqSize = ftell(arq);
	fseek(arq,0,SEEK_SET);
	
	char *traceVet = (char *) malloc(sizeof(char)*arqSize);
	fread(traceVet,1,arqSize,arq);
	
	int count = 0;
	int count2 = 0;
	int countframes=0;
	int maiornframes = 0;
	int menornframes = 999999999;
	bool b = false;
	printf("Paginas: ");
	std::set<int> pages;
	for(int i = 0;i<ceil((double)arqSize)/11.0;i++)
	{
			
			Page page(&traceVet[11*(i)],pgSize);
			
			printf("%d ", page.getPageNumber());
			pages.insert(page.getPageNumber());
			
			count++;
			if(count==delta)
			{	
				if((int)pages.size() > maiornframes)
				{
					maiornframes = pages.size();
				}
				if((int)pages.size() < menornframes)
				{
					menornframes = pages.size();
				}
				
				
				printf("\nFrames necessários: %d\n", (int)pages.size());
				
				if(i!=ceil((double)arqSize/11.0)-1)
				{
					
					printf("\nPaginas: ");
				}
				else
				{
					b = true;
				}
				countframes+=pages.size();
				pages.clear();
				count = 0;
				count2++;
				
				
			}
			
	}
	if(!b)
	{
		count2++;
		countframes+=pages.size();
	}
	
	medttl+=(double)countframes/(double)count2;
	menttl+=menornframes;
	maittl+=maiornframes;
	
}

int main()
{
	int x,y;
	printf("Tamanho da página: ");
	scanf("%d", &x);
	printf("Janela de tempo: ");
	scanf("%d", &y);
	
	//printf("bigone trace\n");
	//runTrace("bigone.trace", x,y);
	//printf("bzip trace\n");
	runTrace("bzip.trace", x,y);
	//printf("gcc trace\n");
	runTrace("gcc.trace", x,y);
	//printf("sixpack trace\n");
	runTrace("sixpack.trace", x,y);
	//printf("swim trace\n");
	runTrace("swim.trace", x,y);
	
	printf("Delta: %d\nTamanho da página: %d\n", y,x);
	printf("Média: %.2lf\nMenor: %.2lf\nMaior: %.2lf\n\n",  (double)medttl/5.0,(double)menttl/5.0, (double)maittl/5.0);

	
	
	
	return 0;
}
