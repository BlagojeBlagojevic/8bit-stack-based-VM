#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef unsigned short BYTE;
typedef unsigned int WORD;
typedef struct MEM   //PREDSTAVLJA RADNU MEMORIJU KOJA SE KORISTI ZA NAS CPU 1024 BYTE
{
	int before; //prije
	int cycle; //KOLIKO CIKLUSA INSTRUKIJA NE POSTOJI ALI RADI LAKSE
	int Broj_Bajtova;
	BYTE PODATCI[1024];	  //MEMORIJA RAM
}MEM;

//INICIJALIZACIJA MEMORIJE
void init_memorije(MEM *memorija) //VJEROVATNO FAJL SA KOJIM RADIMO ZA INICIJALIZACIJU
	{
		FILE *f;
		int i=0,j=0;
										//INSTRUKCIJE
		char code[6],MOVA[]="MOVA",MOVX[]="MOVX",MOVY[]="MOVY",ADD[]="ADDD",LOAD[]="LOCD";
		//f=fopen("C:\\Users\\BLAGI\\Desktop\\PA\\emulator\\asd.txt","r");
		memorija->cycle=0;
		memorija->Broj_Bajtova=1024;
		memorija->before=0x00;
		i=0;
	
		while(1)
		{
		printf("Unesite komandu:\n");
		scanf("%s",&code);
			if(code[3]=='B')
				break;
			else;			
				//code[i-1]='a';
			if(code[3]=='A')
				{
					memorija->PODATCI[j++]=0x00;
					printf("mova\n");
					code[3]='B';
				}
			else if(code[3]=='X')
				{
					memorija->PODATCI[j++]=0x01;
					printf("movx\n");
				}
			else if(code[3]=='Y')
				{
				
					memorija->PODATCI[j++]=0x02;
					printf("movy\n");
				
				}
			else if(code[3]=='D')
				{
					printf("add");
					memorija->PODATCI[j++]=0x03;
				}
			else if(code[2]=='C')
				{
					memorija->PODATCI[j++]=0x04;
					printf("load\n");
				}
			else 
			{
				memorija->PODATCI[j++]=atoi(code);	
				printf("\n%d\n",atoi(code));
			}
			}
			for(i=0;i<4;i++)	
			printf("\n%d\n",memorija->PODATCI[i]);
		} 
			//memorija->PODATCI[i]=;
		
	
/*Predstavlja implementaciju jednostavnog cpu 
PC predstavlja broj instruckije
SP je instrukcija
A,X,Y su GPR 
BITOVI C,N,I PREDSTAVLJAJU PRENOS,NEGATIVNI BROJ, INTERUPT RESPEKTIVNO
funkcija Reset predstavlja vracanje cp u pocetno stanje  
*/ 
typedef struct CPU  
{
	WORD PC;
	WORD SP;
	BYTE A,X,Y; //GPRegistri
	//Status registar
	BYTE C : 1;  //Da li postoji prenos (OVERFLOW)
	BYTE N : 1;  //Da li je broj za sabiranje + ili - TREBA PRAVITI INVERTOVANJE
	BYTE I : 1;  //Interupt bit  mozda	
}CPU;
//resetuje cpu
void reset_cpu(CPU *cpu,MEM *mem)
{
	int i;
	cpu->A=0;
	cpu->C=0;
	cpu->I=0;
	cpu->N=0;
	cpu->PC=0;
	cpu->SP=0xFF;
	cpu->X=0;
	cpu->Y=0;
	for(i=0;i<mem->Broj_Bajtova;i++)
		{
			mem->PODATCI[i]=0xFF;
		}
}
//POKRECE INSTCUKCIJU OD ZAVISNOSTI TIPA KOG JE 
void run(MEM *memory,CPU *cpu)
{
	//PROVJERI KOJA JE INSTRUKCIJA I NESTO DA RADI
	printf("execute\n");
	//DECODIRANJE INSTRUKCIJE VON NOYMAN UZIMA POSLIJE VRIJEDNOSTI U MEMORIJI
	
	if(memory->cycle==0)
	switch(memory->PODATCI[cpu->PC]){
	
		case 0x00: //MOVA 1
	 //CYCLE 2
				{
				memory->cycle=2;
				memory->before=0x01;
				//printf("\n2 clocks\n");
				//printf("\nPUSH ON STACK \n");
				cpu->SP=cpu->PC;
				printf("CALL STACK\n");
				break;				
			}
		case 0x01: //MOVX 1 CYCLE 2
			{
				memory->cycle=2;
				memory->before=0x01;
				printf("\n2 clocks\n");
				printf("\nPUSH ON STACK %d \n", memory->PODATCI[cpu->PC]);
				cpu->SP=cpu->PC;	
				printf("CALL STACK\n");
				//printf("%d",cpu->SP);
				break;				
			}
		case 0x02: //MOVY 3 CYCLE 2
			{
				memory->cycle=2;
				memory->before=0x01;
				//printf("2 clocks\n");
				//printf("\nPUSH ON STACK\n");
				cpu->SP=cpu->PC;
						
				printf("CALL STACK\n");
				break;				
			}
		case 0x03: //add value of a A  i sacuvaj ga u A  ADD, 12
		{
			memory->cycle=2;
			printf("\nADD A to\n");
				//printf("CALL STACK");
			cpu->SP=cpu->PC;	
			memory->before=0x01;
			break;
		}
		case 0x04:  //LOAD INTO MEMORY
			{
				memory->cycle=3; //JOS JEDAN REGISTAR ZA 3 CIKLUSA INSTRUKCIJE
				cpu->SP=cpu->PC;
				cpu->PC++;		

				//printf("\nLoad into memory, \n");
				break;
			}
	}
	else;
		if(memory->before==0x01)
		{
		switch(memory->PODATCI[cpu->SP])
	{
		case 0x00:  // ZA A
			{
				cpu->A=memory->PODATCI[cpu->PC+1];
				memory->before=0x00;

				//printf("MOVE TO A, %d\n",cpu->A);
		    	cpu->SP=0XFF;
				memory->cycle=0x00;
				break;
			}
		case 0x01:   //ZA X
			{
				cpu->X=memory->PODATCI[cpu->PC+1];  //SLEDECU VRIJEDNOST
				//printf("MOVE TO X, %d\n",cpu->X);
				cpu->SP=0XFF;
				memory->cycle=0x00;
				memory->before=0x00;
				break;
			}
		case 0x02:   //ZA Y
			{
				cpu->Y=memory->PODATCI[cpu->PC+1];
				//printf("MOVE TO Y, %d\n",cpu->Y);
				cpu->SP=0XFF;
				memory->cycle=0x00;
				memory->before=0x00;
				break;
			}
		case 0x03: //ZA ADD
			{
				if(cpu->N==1)
				{
					
				}
				else
				{
					//printf("ADD %d to\n",cpu->A,memory->PODATCI[cpu->PC+1]);//SLEDECU
					cpu->A+=memory->PODATCI[cpu->PC+1];
					cpu->SP=0xFF;
					memory->before=0x00;
					if((cpu->A)>0xFF)
						{
							cpu->C=1;
							cpu->A=(cpu->A)-255;
						}
					else;}
		}
				
			  
		case 0x04: //ZA LOAD U MEMORIJU TREBALO BI OGRANICITI GDJE 
			{
				//cpu->SP=cpu->PC;
				if(memory->cycle==3)
				{
					memory->before=memory->PODATCI[cpu->PC];
					memory->cycle--;
				}
				else;
				if(memory->cycle==2) //TREBALO BI OGRANICITI GDJE DA SE PISE
				{
					memory->cycle=0;
					cpu->SP=0XFF;
					memory->PODATCI[memory->before];
				}
				else;
				//memory->cycle--;
			memory->before=0x00;
				break;
			}
			}
	
		}
	
	
	
	//
	if(cpu->PC==1023) //INCREMENTIRATI PC AKO JE INSTRUKCIJA ZAVRSENA ILI AKO JE 1024
	{
		printf("Nema vise instrukcija ili instukcija nije zavrsena\n");
	
			//	printf("Nema vise instrukcija ili instukcija nije zavrsena\n");	reset_cpu(memory,cpu);
	
	}
	else
	{   
		cpu->PC++;		
	}
}
int  main()
{
	int i=0;
	MEM mem;
	CPU cpu;
	reset_cpu(&cpu,&mem);
	init_memorije(&mem);
	
	while(1)
	{
		system("pause");
		run(&mem,&cpu);
		printf("CPU REGISTRI:\n\n");
		printf("A:%d ,X:%d ,Y:%d \nPC: %d ,SP:%d\n",cpu.A,cpu.X,cpu.Y,cpu.PC,cpu.SP);
		printf("Memory content:\n");
		for(i=0;i<8;i++)
			printf("%d ",mem.PODATCI[i]);
		printf("\n");
	}
	//printf("\nA:%d, X: %d\n",cpu.A,cpu.X);

	system("exit");
}