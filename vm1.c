#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#define Stack_Size 1024*29
#define PROGRAM_SIZE(ARR) sizeof(ARR) / sizeof(ARR[0])
typedef struct 
{

    int stack[Stack_Size];
    int SP;   //POINT TO A CURENT VALUE IN A STACK
    int JMPREG;   //USED FOR CONDITIONAL JMP
    int LOOP;     //USED FOR EXIT CONDITION FOR LOOP INCREMENT KINDA LIKE A  COUNTER

}Memory;

typedef enum
{

    NOP,         //BLANK CYCLE
    EXIT,        //CLOSE VM INSTANCE
    PUSH,        //PUSH VALUE OF OPERAND ON STACK IF STACK SIZE IS NOT EXCEEDED STORE VALUE IN JMP REG  
    POP,         //RETURN VALUE OF TOP OF THE STACK AND DECRES STACK SIZE
    PRINT,       //PRINT VALUE FROM TOP OF THE STACK
    ADDI,        //ADD TWO VALUES FROM TOP OF  STACK
    SUBTRACTI,   //SUBTRACT TWO VALUES FROM TOP OF THE STACK(TOP - TOP NEXT)
    MULTIPLAYI,  //MULTIPLAY TWO VALUES FROM TOP OF THE STACK
    LOAD,        //PUT SOME VALUE FROM A STACK TO TOP OF IT
    SET,         //SET VALUE OF STACK POINTER 
    STORE,       //PUT VALUE FROM TOP OF THE STACK ON GIVEN POSITION 
    JMP,         //SET ADDRES OF INSTRUCTION TO OPERAND1 IF DIFERENCE OPERAND AND JMPREG IS GREATER THEN ZERO 
    SETJMPREG,   //SET VALUE OF JMP REG USED FOR CONDITION ALWAYS HOLD LAST VALUE ON STACK 
    LOOP,        //INCREMENT VALUE OF loop REG EVRY TIME THIS FUCTION IS CALL 
    JMPLOOP,     //SET ADDRES OF INSTRUCTION TO OPERAND1 IF DIFERENCE OPERAND AND LOOP IS GREATER THEN ZERO 
     
}Type;

typedef struct 
{

    Type Instr;
    int operand;
    int operand1;   //used for jmp condition 
    
}Instruction;

Instruction program[] = {
    //{.Instr = NOP},
    
    {.Instr = PUSH, .operand = 0},
    {.Instr = LOOP, .operand = 0},
    {.Instr = PUSH, .operand = 1},
    {.Instr = ADDI},
    {.Instr = LOOP, .operand = 1},
    {.Instr = PRINT},
   
    //{.Instr = PUSH, .operand = 1},
    {.Instr = JMPLOOP , .operand = 20,.operand1 = 2},
    {.Instr = EXIT},

};


void save_program_to_file(const char *file_path)
{
    FILE *f = fopen(file_path, "wb");
    fwrite(program, sizeof(program[0]), PROGRAM_SIZE(program), f);
    fclose(f);
}

void halt() //STOP VM
{
    printf("EXITING VM !!!\n");
    exit(EXIT_SUCCESS);
}



//FUNCTION FOR RUNING VM INSTRUCTION 
void push(int value,Memory *mem)   //PUSH VALUE ON TOP OF THE STACK
{
 
    assert(mem->SP < Stack_Size);
    assert(mem->SP >= 0);
    mem->SP++;
    mem->stack[mem->SP] = value;
    mem->JMPREG=value;
    
}

int pop(Memory *mem) //REMOVE VALUE FROM TOP OF THE STACK
{
 
    assert(mem->SP >= 0);
    mem->SP--;
    return mem->stack[1+mem->SP];

}
void run(Instruction *instruc,Memory mem)  //MAIN RUN FUNCTION
{

    mem.stack[0]=0;
    for (size_t i = 0; i <PROGRAM_SIZE(program); i++)
    {
    //printf("stack: %d\n",mem.stack[mem.SP]);    
    switch (instruc[i].Instr)
    {
    case NOP:
            break;
    
    case EXIT:
        halt();
        break;
    

    case PUSH:
        
            {push(instruc[i].operand,&mem);}
            break;
        

     case POP:  //get value from top of the stack
        {pop(&mem);}
        break;
     
    
    case PRINT:     //print value from top of the stack   
        {printf("value %d\n",mem.stack[mem.SP]);}
        break;
    
    
    case ADDI:
        {int a=((pop(&mem)+pop(&mem)));mem.SP+=2;push(a,&mem);}  
        break;      
    
       case SUBTRACTI:    //TOP OF STACK - TOP NEXT OF THE STACK
        {int a=((pop(&mem)-pop(&mem)));mem.SP+=2;push(a,&mem);}  

        break;        
    

       case MULTIPLAYI:
        {int a=((pop(&mem)*pop(&mem)));mem.SP+=2;push(a,&mem);}  

        break;     

       case STORE:
    
        {
            assert(instruc[i].operand<Stack_Size);
            //assert(instruc[i].operand1>=0);
            mem.stack[instruc[i].operand]=pop(&mem);
            mem.SP++;
        }
        break;

        case LOAD:
    
        {
            assert(instruc[i].operand<Stack_Size);
            assert(instruc[i].operand>=0);
            push(mem.stack[instruc[i].operand],&mem);
        }
        break;
    
       case SET:
        {
            assert(instruc[i].operand<PROGRAM_SIZE(program));
            assert(instruc[i].operand>=0);
            mem.SP=instruc[i].operand;
        }
        break;
    
        case JMP:
        {
            if (instruc[i].operand-mem.JMPREG>=0)
            {

             // assert(instruc[i].operand>PROGRAM_SIZE(program));
              //assert(instruc[i].operand>=0);
              i=instruc[i].operand1;  
              //printf("%d",i);         
            }
        
         }    
            break;

    
        case LOOP:
    {
        if(instruc[i].operand==0)
            mem.LOOP=instruc[i].operand;
        else
            mem.LOOP++;
    }    
            break;


    
        case JMPLOOP:
        {
            if (instruc[i].operand-mem.LOOP>=0)
            {

             // assert(instruc[i].operand>PROGRAM_SIZE(program));
              //assert(instruc[i].operand>=0);
              i=instruc[i].operand1;  
              //printf("%d",i);         
            }
        
         }    
            break;        
    
    
    default:
        break;
    }
}
}
int main(void)
{

    Memory mem;
    mem.SP=0;
    run(program,mem);
}
