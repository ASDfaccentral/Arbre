
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <limits.h> 

typedef int bool;
#define true 1
#define false 0


typedef struct node
{
int info;
struct node * left;
struct node * right;
}tree;

typedef struct sNode 
{ 
  tree *t; 
  struct sNode *next; 
}pile; 

/******************************************************************************

                            Fonctions de bases sur pile pour entier
                            Cette déclaration est prise du Site 
                                Geeks for geeks 

*******************************************************************************/
// A structure to represent a stack 
struct IStack 
{ 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct IStack* IcreateStack(unsigned capacity) 
{ 
    struct IStack* stack = (struct IStack*) malloc(sizeof(struct IStack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*) malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 
  
// Stack is full when top is equal to the last index 
int IisFull(struct IStack* stack) 
{   return stack->top == stack->capacity - 1; } 
  
// Stack is empty when top is equal to -1 
int IisEmpty(struct IStack* stack) 
{   return stack->top == -1;  } 
 // Function to add an item to stack.  It increases top by 1 
void Ipush(struct IStack* stack, int item) 
{ 
    if (IisFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    //printf("%d pushed to stack\n", item); 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
int Ipop(struct IStack* stack) 
{ 
    if (IisEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 






/******************************************************************************

                            Fonctions de bases sur pile pour arbre 

*******************************************************************************/

/* initialiser la pile */ 

void Init_stack(pile **p)
{
    (*p)=NULL;
}

/* vérifier si la pile est vide */ 

bool PisEmpty (pile *p)
{
    if (p==NULL) return (true); else return (false);
}



/* Fonction qui Empile un élement dans la pile */

void push(pile ** Sommet, tree *t) 
{ 
  /* allocate tNode */
  pile * new_tNode = 
            (pile *) malloc(sizeof(pile)); 
  
  if(new_tNode == NULL) 
  { 
     printf("Stack Overflow \n"); 
     getchar(); 
     exit(0); 
  }   
 /* mettre l'@ de l'arbre  */
  new_tNode->t  = t; 
  
  /* faire le chainage dans la pile  */
  new_tNode->next = (*Sommet);    
  
  /* changer le sommet  */
  (*Sommet)    = new_tNode; 
} 

/* Fonction qui depiler une élement de la pile*/
tree *pop(pile ** Sommet) 
{ 
  tree *res; 
  pile *top; 
  
  /*si la pile est vide afficher une erreur */
  if(PisEmpty(*Sommet)) 
  { 
     printf("Stack Underflow \n"); 
     getchar(); 
     exit(0); 
  } 
  else
  { 
     top = *Sommet; 
     res = (*Sommet)->t; 
     *Sommet = top->next; 
     free(top); 
     return res; 
  } 
} 
 
/******************************************************************************

                            Fonctions de bases sur arbre

*******************************************************************************/


bool IsEmpty( tree *T)
{
   if (T==NULL) return (true);
   return (false);
}


tree * Left( tree *T)
{
if ( IsEmpty(T) )
return NULL;
else
return T->left;
}

tree * Right( tree *T)
{
if ( IsEmpty(T) )
return NULL;
else
return T->right;
}

bool IsLeave(tree *T)
{
if (IsEmpty(T))
return false;
else if ((IsEmpty(Left(T))) && (IsEmpty(Right(T))))
return true;
else
return false;
}


bool IsInternalNode(tree *T)
{
return (! IsLeave(T) );
}





/******************************************************************************

                            Fonctions serie du TD.

*******************************************************************************/

unsigned max(unsigned a,unsigned b)
{
return (a>b)? a : b ;
}

unsigned Height (tree *T)
{
if ( IsEmpty(T) )
return 0;
else
return 1 + max( Height(Left(T) ) , Height(Right(T) ) );
}

unsigned NbNode(tree *T)
{
if( IsEmpty(T) )
return 0;
else
return 1 + NbNode(Left(T)) + NbNode(Right(T));
}

unsigned NbLeaves( tree *T)
{
if( IsEmpty(T) )
return 0;
else if ( IsLeave(T) )
return 1;
else
return NbLeaves(Left(T)) + NbLeaves(Right(T));
}

unsigned Somme (tree *T)
{
if ( IsEmpty(T) )
return 0;
else
return T->info +  Somme(Left(T) ) + Somme(Right(T) ) ;
}

tree * Rand_Tree(int i)
{   tree *T;
   // time_t t;
    
   // srand((unsigned) time(&t));  // Initialization, should only be called once.
    if (i==0) return NULL;
         else { T=(tree *)malloc (sizeof(tree));
                //if (i%2==0) {T->info= rand()%20; T->left=NULL; T->right=Rand_Tree(i-1);}
                    // else {
                    T->info= rand()%20; T->left=NULL; T->right=Rand_Tree(i-1); T->left=Rand_Tree(i-1);//}
                      return (T);
                  }
    
}

void afficher (tree *T)
{
    if (!IsEmpty (T)) { printf ("%d  ", T->info );
                        afficher(T->right);
                        afficher(T->left);
                              }
}


tree * Supprimer (tree *T)
{
    if (!IsEmpty (T)) { T->right= Supprimer(T->right);
                        T->left= Supprimer(T->left);
                        free(T);
                        return (NULL);
                              }
}

tree * Rechercher (tree *T, int var)
{
    if (IsEmpty(T)) return (NULL);
               else if (T->info ==var) return (T);
                                  else { tree * R= Rechercher(T->right, var);
                                         tree * L= Rechercher(T->left, var);
                                         if (!IsEmpty(R)) return R;
                                         if (!IsEmpty(L)) return L;
                                         return(NULL);
                                      
                                         }
}

tree * Miroir (tree *T)
{
   tree * MABR;
   if (!IsEmpty(T)) {MABR =(tree *) malloc (sizeof(tree));
                     MABR->info = T->info;
                     MABR->left=Miroir(T->right);
                     MABR->right=Miroir(T->left);
                     return (MABR);
                     }
                else return (NULL);     
}


bool ABR_check(tree * T)
{   bool FG,FD;
    if (IsEmpty(T)) return (true);
                else { FG= ABR_check(Left(T));
                       FD = ABR_check(Right(T));
                       if ((FG==false) || (FD==false)) return (false);
                                                else if ((IsEmpty(Left(T)))&& (IsEmpty(Right(T)))) return (true);
                                                          else {if (IsEmpty(Left(T))) {if (Right(T)->info < T->info) return (false); else return (true);}
                                                                if (IsEmpty(Right(T))) {if (Left(T)->info > T->info) return (false); else return (true);}
                                                                if ((Left(T)->info < T->info) && (Right(T)->info > T->info)) return (true); else return (false);
                                                                } 
                      } 
}


unsigned Taille_iter (tree *T)
{
  unsigned var=0;
  pile *p;
  tree *ABR;
  
  ABR =T;
  
  Init_stack(&p);
  push (&p, ABR); 
  
  while  (!PisEmpty(p))
  {
      ABR = pop (&p);
      var ++;
      if (!IsEmpty(ABR->left)) push (&p, ABR->left); 
      if (!IsEmpty(ABR->right)) push (&p, ABR->right); 
      
  }
  
  return (var);
}

 
unsigned Height_iter (tree *T)
{
  unsigned var, max;
  pile *p;
  tree *ABR;
  struct IStack* Ip;
  
  max =0;
  ABR =T;
  Ip=IcreateStack (100);
  Ipush(Ip,1);
  
  Init_stack(&p);
  push (&p, ABR); 
  
  while  (!PisEmpty(p))
  {
      ABR = pop (&p);
      var = Ipop(Ip);
      
      if ((IsEmpty(ABR->left)) && (IsEmpty(ABR->right))) {if (max < var) max=var;}
      var ++;
      if (!IsEmpty(ABR->left)) {push (&p, ABR->left); Ipush(Ip,var); }
      if (!IsEmpty(ABR->right)) {push (&p, ABR->right); Ipush(Ip,var);} 
      
  }
  
  return (max);
}
 
 

tree * Maximal ( tree *T)
{
     tree *FG, *FD;
    if (IsEmpty(T)) return (NULL);
                else { FG=  Maximal(Left(T));
                       FD =  Maximal(Right(T));
                       if ((FG==NULL) && (FD==NULL)) return (T);
                                                else {if (IsEmpty(Left(T))) {if (FD->info > T->info) return (FD); else return (T);}
                                                      if (IsEmpty(Right(T))) {if (FG->info > T->info) return (FG); else return (T);}
                                                      if ((FG->info <= T->info) && (FD->info <= T->info)) return (T); 
                                                           else if ((FG->info >= T->info) && (FD->info <= FG->info )) return (FG);
                                                                else return (FD);
                                                                } 
                      } 
}





int main()
{
    
    tree *T, *R;
    int option;
    bool check;
    
    T= Rand_Tree(5);
    afficher (T);
clrscr();
do
{
printf("\n\n *****MENU PRINCIPALE *****");
printf("\n 1: Trouver la taille d'un arbre binaire(récursive)");
printf("\n 2: Trouver la hauteur d’un arbre binaire(récursive)");
printf("\n 3: Trouver le nombre de feuilles d’un arbre binaire");
printf("\n 4: Calculer la somme de tous les noeuds d’un arbre binaire");
printf("\n 5: Trouver la taille d'un arbre binaire(itérative)");
printf("\n 6: Supprime un arbre binaire.");
printf("\n 7: Trouver l'élément max dans un arbre binaire ");
printf("\n 8: Rechercher un élément dans un arbre binaire ");
printf("\n 9: Trouver la hauteur d’un arbre binaire(itérative) ");
printf("\n 10: ");
printf("\n 11: Convertir un arbre à son miroir.");
printf("\n 12: ");
printf("\n 13: Vérifier si un arbre est un arbre binaire de recherche");
printf("\n 14: Sortir");
printf("\n\n Entez votre choix : ");
scanf("%d", &option);
switch(option)
{
case 1: printf("La taille de l'arbre est de : %u \n",NbNode(T));
break;
case 2: printf("L'hauteur de l'arbre est de : %u \n",Height(T));
break;
case 3: printf("Le nombre de feuilles de l'arbre est de : %u \n",NbLeaves(T));
break;
case 4: printf("Le Somme d'élement de l'arbre est de : %u \n",Somme(T));
break;
case 5:printf("La taille de l'arbre est de : %u \n",Taille_iter(T));
break;
case 6: T=Supprimer(T); printf("Arbre Supprimer \n"); afficher (T);
break;
case 7: R = Maximal (T); printf("L'élément maximal est %d\n", R->info);
break;
case 8: R= Rechercher(T,30); if (IsEmpty(R)) printf("N'existe pas"); else printf("existe");
break;
case 9: printf("L'hauteur de l'arbre est de : %u \n",Height_iter(T));
break;
case 10: 
break;
case 11: R=Miroir(T); printf("Le miroir de votre arbre est le suivant :"); afficher(R);
break;

case 12: 
break;
case 13: check=ABR_check(T); if (check==true) printf ("C'est bien un arbre binaire de recherche"); else printf ("Ce n'ai pas un arbre binaire de recherche");
break;
}
}while(option != 14);
getch();
    return 0;
}
