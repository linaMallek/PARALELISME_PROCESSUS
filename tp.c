#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>


//------------------------------------------------------nbr operation ------------------------------------------

int nbr_opr(char *exp){
   int nbr=0 ;
    for (int i=0;i<strlen(exp);i++)
    {   
        if (exp[i]=='(')
            {nbr=nbr + 2;}
        else {
             if (exp[i]==')')
             {nbr=nbr-1;}}  
    }

    return nbr;
}
// -----------------------------------------------------operateur centrale -------------------------------------

int oper_central(char *op){
   int nbr_F=0;
    int nbr_O=0;
    for ( int  i=0 ; i <strlen(op); i++)
    {
        if (op[i]=='(')
        {
            nbr_O=nbr_O+1;
        }
        if (op[i]==')')
        {
            nbr_F=nbr_F+1;
        }

        if (((nbr_O-nbr_F)==1) && (op[i]=='*' || op[i]=='+' ||op[i]=='-' || op[i]=='/'))
        {
            return (i);
        }
        
    }
}





// -------------------------------------------------genere noeud -------------------------------------------------------------

void genere_neoud(int noeud){
     printf("processus %d pid %d  %d\n",noeud,getpid(),getppid());
     //printf("T%d:",noeud);
    
}

void generer_tache(char *exp,int op,int noeud,int j){
    
    char gauche[50];
    char droit [50]; 

    if(exp[op-1] ==')'){
   
          sprintf(gauche,"M%d",(noeud+1));} 
    
    else{
 
          sprintf(gauche,"%c",exp[op-1]);}
    
    if(exp[op+1] =='('){
    
          sprintf(droit,"M%d",(noeud+j+1));}
    
    else{
          sprintf(droit,"%c",exp[op+1]);}
          
    
    
    printf("M%d = %s %c %s\n",noeud,gauche,exp[op],droit);
   
    
    
}

void generer_precedence(int noeud,int pere){
	
	if(pere == 0){
        printf("\n");
        return;
    }

    else {printf("\nT%d < T%d\n", noeud,pere);}
	
}

void genere(char *exp,int noeud,int pere){

	
	int op_central = oper_central(exp);
    int i,id,id2,j=0,nb_op =0;


	genere_neoud(noeud);
	int taille= strlen(exp);
    char droit[taille] , gauche[taille];
	
	
	if(exp[op_central-1]==')'){
		j=0;
        // coté gauche de l'expression 
		for(i=1;i<op_central;i++){
		gauche[j]=exp[i];
		j=j+1;}
		nb_op =nbr_opr(gauche);
		id = fork();
		
		if (id==0){
			genere(gauche,(noeud+1),noeud);
			}
		
		}
	
  
	if(exp[op_central+1]=='('){
		j = 0 ;
		// coté droit de l'expression 
		for(i=op_central+1;i<strlen(exp)-1;i++){
		droit[j]=exp[i];
		j=j+1;
		}
		
		id2 = fork();
		if (id2==0){
		genere(droit,(noeud+nb_op+1),noeud);
			}
		}
		
		
	generer_tache(exp,op_central,noeud,nb_op);
    generer_precedence(noeud,pere);
	
	wait(0);
	wait(0);
	exit(0);
	
}




void main(){

	char T[50]="((A+B)*(C-(D/E)))";
    char T1[50]="(((A+B)*C)-(((D-(F/G))*(H+(K*L)))/((M-N)*O))))";

	genere(T1, 1, 0);
    //genere(T,1,0);
	
}
