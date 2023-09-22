//https://www.nongnu.org/avr-libc/user-manual/modules.html 
//MOZDA JE BOLJE  KORISTITI AVR C DODJE DIREKTNO U ARDUINO IDE 

//#include <servo.h>

//#include <arduino.h>  /MOZDA MOZE I SA OVIM MAIN MOZDA


//ili

//#include <assert.h>  //NEZNAM DA LI 
//#include <stdio.h>
//#include <stdint.h>


typedef enum {   //TIPOVI INSTRUKCIJA JEBIGA MISLIM DA NE TREBA NISTA VISE 
	
    SET_ANGLE,   //POSTAVLJA UGAO SERVO MOTORA   {.Instr = SET_ANGLE, .operand = 32,.motor = 1},
    MOVE_X,      //POMJERA RUKU U POZICIJU X     {.Instr = MOVE_X, .operand = 32},
    MOVE_Y,		 //POMJERA RUKU U POZICIJU Y     {.Instr = MOVE_Y, .operand = 32},
    MOVE_Z,		 //POMJERA RUKU U POZICIJU Z     {.Instr = MOVE_Z, .operand = 32},
    JMP,		 //KORISTI SE ZA PONAVLJANE ODREDJENOG BROJA INSTRUKIJA  
				 //TO JES VRACA SE NA INSTRUKCIJU IZ OPERANDA  {.Instr = JMP, .operand = 2,.motor = 3},ROBOT.loop++;
    			 //.motor NA KOJU INSTRUKCIJU  .operand KOLIKO PUTA
	EXIT,      	 //ZAUSTAVLJA RUKU JEBIGA TREBALO BI ODRAITI U INTERUPTU ZA EMRGENCY UVIJEK NA KRAJU 
    //IF,        //NEZNAM DA LI TREBA AKO BI BILA ONDA BI POREDILA OPERAND I MOTOR I DVA RAZLICITA JMP 
    DELAY,       //KASNJENJE U ms
} Inst_Type;

typedef struct {       //INSTRUKCIJA SE SATOJI OD TIPA KOJI VADI IS Inst_Type 
						//enum(SAMO IME PRETVORI U BROJ TO JEST SET_ANGLE 0X00, MOVE_X 0X01 itd )
						//OPERAND JE 16 BIT VRJEDNOST KORSTIEMO JE ZA UGAO I ZA PROSLEDJIVANJE KORDINATA
    Inst_Type type;
    int16_t operand;
    uint8_t motor;     //TREBALO BI ZAMJENITI U OPERAND 2 ALI JEBIGA
    
} Inst;

Inst program[] = {      //OVDJE IDU INSTRUKCIJE KOJE TREBA DA SE IZVRSAVAJU
   						//{.Instr = MOVE_X, .operand = 32},
   						//{.Instr = MOVE_Y, .operand = 32},
   						//{.Instr = MOVE_Z, .operand = 32},
   						//{.Instr = DELAY, .operand = 32},
};
//ZAVISI KOJI JE STANDARD MORAS IZDVOJITI NA POCETAK 
#define PROGRAM_SIZE (sizeof(program) / sizeof(program[0]))   //RACUNA BROJ INSTRUKCIJA  AK ONA POCETAK ONDA DOLE RACUNAJ ISTO

#define DEGREE_OF_FREEDOM 3                                   //STEPENI SLOBODE   
typedef struct ROBOT
{
	uint16_t angel[DEGREE_OF_FREEDOM];    //UGLOVI ZA KOLIKO SU SERVOI POMJERENI (TRENUTNI)
	uint16_t x;
	uint16_t y;
	uint16_t z;    //TRENUTNI POLOZAJ RUKE
	
	//AKO SU POTREBNI POLOZAJI ZGLOBOVA ONDA
	//uint16_t x[DEGREE_OF_FREEDOM];
	//uint16_t y[DEGREE_OF_FREEDOM];
	//uint16_t z[DEGREE_OF_FREEDOM];
	//
	uint16_t lenght[DEGREE_OF_FREEDOM]; //DUZINA OD ZGLOBA DO ZGLOBA ILI RAZDVOJ JEDAN PO JEDAN KAKO GOD SI OZNACIO
	
	
	
	int16_t  loop;                      //OVO SLUZI ZA JMP AKO SE NESTO PONAVLJA ODREDJENI BROJ PUTA
	
	//AKO JOS STA TREBA DODAJ 
}ROBOT;



// GLOBALNE VARIJABLE ROBOT I SERVO I AKO JOS STA TREBA
ROBOT robot;
//Servo myservo[DEGREE_OF_FREEDOM];  //AKO SE KORISTI <servo.h> globalni servo
//I AKO JOS STA TREBA
//



//SVE FUNKCIJE OVDJE
//void setup()
void init()
{
	 robot.loop=0;
	 //myservo[KOJI].attach(PIN);
	 //OSTALI INITI  POSTAVLJANJE PARAMETARA ROBOTA
	 robot.lenght[0]=10;// NPR DUZINA OD 0 DO  I STA JOS TREBA
}



void set_angle(int16_t angle , uint8_t motor)//1 KOLIKI UGAO DA SE POSTAVI  //2 KOJI MOTOR
{
	//NEMAM POJMA STA CETE KORISTITI SERVO ILI STEPERE
	//AKO SERVO ONDA OVA https://www.arduino.cc/reference/en/libraries/servo/
	// myservo[motor].write(angle);              // tell servo to go to position in variable 'angle'
	//RADI SA INTERUPTOM NEMORA SE NISTA PROVJERAVARI SAMO RADI TO UNUTAR BIBLIOTEKE MOZE OKO 10 SERVOA 
	//MADA SI VAJDA RADIO SA OVIM KAD SI PRAVIO ROBOTA
   
}  


//NAJ JEDNOSTAVNI MOGUCI RACUN AKO RACUNAS KAO FLOAT MAPIRAJ POMOCU 
//https://www.arduino.cc/reference/en/language/functions/math/map/(NPR 0.1 FLOAT 1 INT16 ; 0.2 FLOAT 2 INT16 itd)
//ali bolje je da drzis int16 mat
//ROBOTA IMAS KAO GLOBALNA robot. pa koji ti parametar treba

void calculate_x(int16_t operand)
{
	//MAMBO JUMBO RACUNAJE UGLOVA
	set_angle(/*UGAO_IZRACUNATI*/,/*ZA_KOJI MOTOR*/);
	//JOS KOJI TREBAJU POSTAVITI DELAY  //JEDAN PO JEDAN
}

void calculate_y(int16_t operand)
{
	//MAMBO JUMBO RACUNAJE UGLOVA
	set_angle(/*UGAO_IZRACUNATI*/,/*ZA_KOJI MOTOR*/);
	//JOS KOJI TREBAJU POSTAVITI DELAY  //JEDAN PO JEDAN
}

void calculate_z(int16_t operand)
{
	//MAMBO JUMBO RACUNAJE UGLOVA
	set_angle(/*UGAO_IZRACUNATI*/,/*ZA_KOJI MOTOR*/);
	//JOS KOJI TREBAJU POSTAVITI DELAY  //JEDAN PO JEDAN
}
//AKO I RUKA IMA NEKE KOMANDE POZICIJU NAKALEMI INTRUKCIJU


//void loop()
int main()
{
	//ako setup i loop init ne treba
    init();

    for (size_t ip = 0; ip < PROGRAM_SIZE; ip++) {
        switch (program[ip].type) {   //PROVJERI TIP INSTRUKCIJE IZ PROGRAMA I RADI STA NAM TREBA
        case SET_ANGLE:
        {
            set_angle(program[ip].operand,program[ip].motor);
		}
        break;
        
		case MOVE_X: 
		{
        	calculate_x(program[ip].operand);   
        }
        break;
        
        case MOVE_Y: 
		{
        	calculate_y(program[ip].operand);  
        }
        break;
       
        case MOVE_Z: 
		{
        	calculate_z(program[ip].operand);   
        }
        break;
        
        case JMP: 
		{
        	if(robot.loop!=program[ip].operand)  
			{
				ip=program[ip].motor;
				robot.loop++;
			} 
			else
			{
				loop=0;    //reset brojaca na 0
			} 
        	
        }
        break;
        case DELAY: 
		{
        	//delay(program[ip].operand); //ako arduino.h ako ne onda tajmer
        }
        break;
        
         case EXIT: 
		{
        	//exit(EXIT_SUCCESS); ovo ako je stdio.h neznam sta je ako je arduino.h 
			//mozda nema EXIT_SUCCESS PA pisi exit(1);
        }
        break;
        
        default:
            //assert(0 && "Invalid instruction");// TREBLO BI I OGRANICITI SVA OSTALA SRANJA DA SE NE MOGU 
	    //	DA  UGAO NE MOZE BITI VECI OD 360 POZICIJA OD MAX NECEGA I SLICNO  
        }
    }

    return 0;
}
