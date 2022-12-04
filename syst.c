#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

// retourner nombrre operation 
int nbr_op(char c[])
{   
    int nbr=0 ;
    for (int i=0;i<strlen(c);i++)
    {   
        if (c[i]=='(')
            {nbr=nbr + 2;}
        else {
             if (c[i]==')')
             {nbr=nbr-1;}}  
    }

    return nbr;
}

// retourner l'indice de l'operateur centrale 
int op_central(char op[]) 
{  
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
// generer noeud 

void generer_noeud(int noeud) { 
    printf(" \n T%d:M%d:= ", noeud, noeud );}

// generer precedence 
void generer_precedence(int noeud, int pere) {
    if(pere == 0){
        printf("\n");
        return ;
    }

    printf("\nT%d < T%d\n", pere, noeud);
}

// retourner coté gauche de l'expression 
void cote_gauche(char op[],char s[])
{
int j=0;  
if (strlen(op)>4)
{ 
for (int i=1;i<strlen(op)-1; i++)
{
    if (i<op_central(op))
        {
            s[j]=op[i];
            j=j+1;
        }
}
printf("%s \n",s);
}
}


int cote_droit(char op[],char s[])
{
int j=0;  
if (strlen(op)>4)
{ 
for (int i=1;i<strlen(op)-1; i++)
{
    if (i>op_central(op))
        {
            s[j]=op[i];
            j=j+1;
        }
}
return 1;
}
else {return 0;}
}


void genere_tache(char exp[] ,int noeud, int j)
{
char cote_gauche[100];
char cote_droit[100];
int cg=0 ;
int cd=0;
int x=0,i;

for (i=1;i<j;i++)
   {
    cote_gauche[cg]=exp[i];
    cg=cg+1;
   }


for (int x=j+1;x< strlen(exp)-1;x++)
   {
    cote_droit[cd]=exp[x];
    cd=cd+1;
   }

  if ((strlen(cote_gauche)>1) & (strlen(cote_droit)==1))
     {generer_noeud(noeud); printf("M%d %c %s" ,noeud+1,exp[j],cote_droit);} 

  if ((strlen(cote_gauche)>1) & (strlen(cote_droit)>1))
         {generer_noeud(noeud); printf("M%d %c M%d" ,noeud+1,exp[j],noeud+2);}

  if ((strlen(cote_gauche)==1) & (strlen(cote_droit)>1))
     {generer_noeud(noeud); printf("%s %cM%d " ,cote_gauche,exp[j],noeud+1);}
 
  if ((strlen(cote_gauche)==1) & (strlen(cote_droit)==1))
     {generer_noeud(noeud); printf("%s %c %s" ,cote_gauche,exp[j],cote_droit);}


for (i = strlen(cote_droit); i>=0; i--)
       {cote_droit[i] = cote_droit[i+1];}  


for (i = strlen(cote_gauche); i>=0; i--)
       {cote_gauche[i] = cote_gauche[i+1];} 
 
       

}

// genere 
void genere (char exp [],int noeud, int pere)

{   
    char cote_gauche[100];
    char cote_droit[100];
    int cg=0,i=0 ;
    int cd=0;
    int nbr=nbr_op(exp);

   
    genere_tache(exp,noeud,op_central(exp));
    generer_precedence(noeud,pere);
    

    for (int i=1;i<op_central(exp);i++)
    {
    cote_gauche[cg]=exp[i];
    cg=cg+1;
    }
    
   

    for (int i=op_central(exp)+1;i< strlen(exp)-1;i++)
    {
    cote_droit[cd]=exp[i];
    cd=cd+1;
    }
    
    

    if (strlen(cote_gauche)>5)
       {
        
        genere(cote_gauche,noeud+1,noeud);
       }
    else {
        genere_tache(cote_gauche,noeud,op_central(cote_gauche));
         }   

       if (strlen(cote_droit)>5)
        {
        genere(cote_droit,noeud+1,noeud) ;
        }
    else {
        genere_tache(cote_droit,noeud,op_central(cote_droit));
        }      

    for (i = strlen(cote_droit); i>=0; i--)
       {cote_droit[i] = cote_droit[i+1];}  

    for (i = strlen(cote_gauche); i>=0; i--)
       {cote_gauche[i] = cote_gauche[i+1];}  

 }





void main ()
{
char s[50];     
char T[50]="((A+B)*(C-(D/E)))";
char T1[30]="(A+B)";
char exp[50];
char noeud[50];
genere(T,1,0);
}