#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{file, directory} type;
typedef enum{ok, no} ceck;
char percorsi[200][255*256];
int z;
struct node{
            char name[256];
            type tipo;       
            char dati[256];
            struct node *discendenti[1024];
            };

void libera_ric(struct node* nodo)  //funzione ricorsiva che elimina il nodo passato come paramentro e tutti i suoi discendenti
    {
    int i;
    if(nodo->discendenti[0]==NULL) free(nodo);  
    else{
        for(i=0; (nodo->discendenti[i]!=NULL)&&(i<1024); i++)
          {
          libera_ric(nodo->discendenti[i]);
          }
        }
    }
    
    
void find_ric(struct node* nodo, char *nome, char *path, int *trovato)
    {
    int i,j; 
    if(strcmp(nodo->name, "root")!=0)
        {
        strcat(path, "/");
        strcat(path, nodo->name);
        }
    if(strcmp(nodo->name, nome)==0) 
        {
        //printf("ok %s\n", path);
        strcpy(percorsi[z], path);
        z++;
        *trovato=1;
        }
    for(i=0; (i<1024)&&(nodo->discendenti[i]!=NULL); i++)
        {
        find_ric(nodo->discendenti[i], nome, path, trovato);
        }
    j=strlen(path)-1;
    while((j>0)&&(path[j]!='/'))
        {
        path[j]=(char)NULL;
        j--;    
        }
    path[j]=(char)NULL;
    }
    
int main(void)
    {
     //freopen("output.txt", "w", stdout);
     /*SEZIONE DICHIARATIVA*/
     //FILE *fp;     
     int i,j,k,p;
     int controllo_find;    
     char operation[11], path[256*255], node_name[256], next_node_name[256];
     struct node *new_node=NULL;
     struct node *current_node=NULL;
     struct node *father=NULL;
     struct node *root=NULL;
     ceck inserimento;
     int trovato;
     char frase[256], empty[256], carattere;
     for(i=0; i<256; i++) empty[i]=(char)NULL;
     /*fine sezione dichiarativa*/
     
     
     /*Radide del file system*/
     root=malloc(sizeof(struct node));                //da liberare
     strcpy((char *)root->name,"root");
     root->tipo=directory;
     root->dati[0]=(char)NULL;
     for(i=0; i<1024; i++) root->discendenti[i]=NULL; //**
     
     
     //fp=fopen("Task/vines.in", "r");
     //fscanf(fp, "%s", operation);
     scanf("%s", operation);
     while(/*(!feof(fp))&&(*/strcmp((char *)operation, "exit")!=0/*)*/){
                      
     /*Gestione della CREATE*/
                if(strcmp((char *)operation, "create")==0)
                          {
                          inserimento=ok;
                          current_node=root;
                          //fscanf(fp, "%s", path);
                          scanf("%s", path);
                          next_node_name[0]=(char)'a';
                          i=0;
                          j=0;
                          for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)          //la variabile i è riservata 'a scorrere tutto il path'
                                {
                                node_name[j]=path[i];
                                j++;
                                }   //node_name contiene il primo nome nel path
                          node_name[j]=(char)NULL;      //terminatore di stringa
                          
                          
                          
                          while((next_node_name[0]!=(char)NULL)&&(inserimento==ok))
                                {                      
                                if(path[i]=='/')
                                        {
                                        j=0;
                                        for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)
                                                {
                                                next_node_name[j]=path[i];
                                                j++;
                                                }
                                        next_node_name[j]=(char)NULL;    //terminatore di stringa
                                        }            //next_node_name contiene il secondo nome del path
                                        else next_node_name[0]=(char)NULL;
                               
                               
                               
                               
                                if(next_node_name[0]!=(char)NULL)     //aggiorna current_node
                                        {
                                        trovato=1;
                                        for(k=0;((current_node->discendenti[k]!=NULL)&&(k<1024)&&trovato); k++) 
                                                {
                                                if((strcmp(current_node->discendenti[k]->name,node_name)==0)&&(current_node->discendenti[k]->tipo==directory)) trovato=0;  
                                                }
                                        if(trovato==0) 
                                                current_node=current_node->discendenti[k-1]; 
                                                else 
                                                        inserimento=no;   //percorso non valido(o non esiste oppure si eccedono i limiti)
                                        } 
                                        
                                        
                                        
                                       else        //allocazione del nuovo nodo e aggancio nel giusto percorso
                                                    {                       
                                                    for(k=0; (k<1024)&&(current_node->discendenti[k]!=NULL)&&(inserimento==ok);k++)
                                                        {
                                                        if(!strcmp(current_node->discendenti[k]->name, node_name)&&current_node->discendenti[k]->tipo==file) inserimento=no;  //cotrolla che non ci sia una directory con lo stesso nome nella posizione da inserire
                                                        } 
                                                    if(k>=1024) inserimento=no;
                                                    if(inserimento==ok)
                                                       {
                                                        new_node=malloc(sizeof(struct node));                //da liberare
                                                        if (new_node==NULL) inserimento=no;
                                                        if(inserimento==ok)
                                                            {
                                                            strcpy((char *)new_node->name,node_name);
                                                            new_node->tipo=file;
                                                            new_node->dati[0]=(char)NULL;
                                                            for(i=0; i<1024; i++) new_node->discendenti[i]=NULL; 
                                                            if(k<1024) current_node->discendenti[k]=new_node;               
                                                            }
                                                        }
                                                     }                       
                              
                              
                              
                                if(next_node_name[0]!=(char)NULL) strcpy(node_name, next_node_name);
                                }
                                
                                
                          if(inserimento==no) printf("no\n");
                              else printf("ok\n");                          
                          }
     /*fine create*/
     
     /*Gestione della CREATE_dir*/
                if(strcmp((char *)operation, "create_dir")==0)
                          {
                          inserimento=ok;
                          current_node=root;
                          //fscanf(fp, "%s", path);
                          scanf("%s", path);
                          next_node_name[0]=(char)'a';
                          i=0;
                          j=0;
                          for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)          //la variabile i è riservata 'a scorrere tutto il path'
                                {
                                node_name[j]=path[i];
                                j++;
                                }   //node_name contiene il primo nome nel path
                          node_name[j]=(char)NULL;      //terminatore di stringa
                          
                          
                          while((next_node_name[0]!=(char)NULL)&&(inserimento==ok))
                                {                      
                                if(path[i]=='/')
                                        {
                                        j=0;
                                        for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)
                                                {
                                                next_node_name[j]=path[i];
                                                j++;
                                                }
                                        next_node_name[j]=(char)NULL;    //terminatore di stringa
                                        }            //next_node_name contienre il secondo nome del path
                                        else next_node_name[0]=(char)NULL;
                               
                                
                                
                                
                                if(next_node_name[0]!=(char)NULL)     //aggiorna current_node 
                                        {
                                        trovato=1;
                                        for(k=0;((current_node->discendenti[k]!=NULL)&&(k<1024)&&trovato); k++) 
                                                {
                                                if((strcmp(current_node->discendenti[k]->name,node_name)==0)&&(current_node->discendenti[k]->tipo==directory)) trovato=0;  
                                                }
                                        if(trovato==0) 
                                                current_node=current_node->discendenti[k-1]; 
                                                else 
                                                        inserimento=no;   //percorso non valido
                                        }
                                        
                                        
                                         
                                       else          //allocazione del nuovo nodo e aggancio nel giusto percorso
                                             {                      
                                              for(k=0; (k<1024)&&(current_node->discendenti[k]!=NULL)&&(inserimento==ok);k++)
                                                        {
                                                        if(!strcmp(current_node->discendenti[k]->name, node_name)&&current_node->discendenti[k]->tipo==directory) inserimento=no;  //cotrolla che non ci sia una directory con lo stesso nome nella posizione da inserire
                                                        } 
                                              if(k>=1024) inserimento=no;
                                              if(inserimento==ok)
                                                       {
                                                        new_node=malloc(sizeof(struct node));                //da liberare
                                                        if (new_node==NULL) inserimento=no;     //controlla che la malloc sia andata a buon fine
                                                        if(inserimento==ok)
                                                            {
                                                            strcpy((char *)new_node->name,node_name);
                                                            new_node->tipo=directory;
                                                            new_node->dati[0]=(char)NULL;
                                                            for(i=0; i<1024; i++) new_node->discendenti[i]=NULL; 
                                                            current_node->discendenti[k]=new_node;               
                                                            }
                                                        }
                                              }
                                                     
                                                     
                                                                              
                                if(next_node_name[0]!=(char)NULL) strcpy(node_name, next_node_name);
                                }
                                
                                
                          if(inserimento==no) printf("no\n");
                              else printf("ok\n");
                          }
     /*fine create_dir*/
     
     /*Gestione della read  */
                      if(strcmp((char *)operation, "read")==0)
                          {
                          inserimento=ok;
                          current_node=root;
                          //fscanf(fp, "%s", path);
                          scanf("%s", path);
                          next_node_name[0]=(char)'a';
                          i=0;
                          j=0;
                          for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)          //la variabile i è riservata 'a scorrere tutto il path'
                                {
                                node_name[j]=path[i];
                                j++;
                                }   //node_name contiene il primo nome nel path
                          node_name[j]=(char)NULL;      //terminatore di stringa
                          
                          
                          
                          while((next_node_name[0]!=(char)NULL)&&(inserimento==ok))
                                {                      
                                if(path[i]=='/')
                                        {
                                        j=0;
                                        for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)
                                                {
                                                next_node_name[j]=path[i];
                                                j++;
                                                }
                                        next_node_name[j]=(char)NULL;    //terminatore di stringa
                                        }            //next_node_name contiene il secondo nome del path
                                        else next_node_name[0]=(char)NULL;
                               
                                
                                
                                
                                if(next_node_name[0]!=(char)NULL)     //aggiorna current_node
                                        {
                                        trovato=1;
                                        for(k=0;((current_node->discendenti[k]!=NULL)&&(k<1024)&&trovato); k++) 
                                                {
                                                if((strcmp(current_node->discendenti[k]->name,node_name)==0)&&(current_node->discendenti[k]->tipo==directory)) trovato=0;  
                                                }
                                        if(trovato==0) 
                                                current_node=current_node->discendenti[k-1]; 
                                                else 
                                                        inserimento=no;   //percorso non valido(o non esiste oppure si eccedono i limiti)
                                        } 
                                        
                                        
                                        
                                       else    //lettura dal file
                                           {
                                           trovato=1;
                                           for(k=0; (k<1024)&&(current_node->discendenti[k]!=NULL)&&(inserimento==ok)&&(trovato);k++)
                                                {
                                                if(!strcmp(current_node->discendenti[k]->name, node_name)&&(current_node->discendenti[k]->tipo==file)) trovato=0; 
                                                } 
                                           if(trovato==0) current_node=current_node->discendenti[k-1];        
                                           }
                                           
                                           
                                                                 
                                if(next_node_name[0]!=(char)NULL) strcpy(node_name, next_node_name);
                                }
                                
                                
                                
                          //current_node qua è il file dal quale si vuole leggere
                          if((inserimento==ok)&&(trovato==0))
                              {
                              printf("contenuto %s\n", current_node->dati);  
                              }
                              else 
                                   printf("no\n");
                          }
    /*fine read*/
                      
    /*Gestione della write*/
                      if(strcmp((char *)operation, "write")==0)
                          {
                          inserimento=ok;
                          current_node=root;
                          //fscanf(fp, "%s", path);
                          scanf("%s", path);
                          next_node_name[0]=(char)'a';
                          i=0;
                          j=0;
                          for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)          //la variabile i è riservata 'a scorrere tutto il path'
                                {
                                node_name[j]=path[i];
                                j++;
                                }   //node_name contiene il primo nome nel path
                          node_name[j]=(char)NULL;      //terminatore di stringa
                          
                          
                          
                          
                          while((next_node_name[0]!=(char)NULL)&&(inserimento==ok))
                                {                      
                                if(path[i]=='/')
                                        {
                                        j=0;
                                        for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)
                                                {
                                                next_node_name[j]=path[i];
                                                j++;
                                                }
                                        next_node_name[j]=(char)NULL;    //terminatore di stringa
                                        }            //next_node_name contiene il secondo nome del path
                                        else next_node_name[0]=(char)NULL;
                               
                               
                               
                               
                                
                                if(next_node_name[0]!=(char)NULL)     //aggiorna current_node
                                        {
                                        trovato=1;
                                        for(k=0;((current_node->discendenti[k]!=NULL)&&(k<1024)&&trovato); k++) 
                                                {
                                                if((strcmp(current_node->discendenti[k]->name,node_name)==0)&&(current_node->discendenti[k]->tipo==directory)) trovato=0;  
                                                }
                                        if(trovato==0) 
                                                current_node=current_node->discendenti[k-1]; 
                                                else 
                                                        inserimento=no;   //percorso non valido(o non esiste oppure si eccedono i limiti)
                                        } 
                                        
                                        
                                        
                                       else             //current_node qua diventa il file nel quale si vuole scrivere
                                           {
                                           trovato=1;
                                           for(k=0; (k<1024)&&(current_node->discendenti[k]!=NULL)&&(inserimento==ok)&&trovato;k++)
                                                {
                                                if(!strcmp(current_node->discendenti[k]->name, node_name)&&(current_node->discendenti[k]->tipo==file)) trovato=0; 
                                                } 
                                           if(trovato==0)  current_node=current_node->discendenti[k-1];        
                                           }          
                                           
                                           
                                                       
                                if(next_node_name[0]!=(char)NULL) strcpy(node_name, next_node_name);
                                }
                                
                                
                          
                          //inserimento dei dati in current_node->dati   
                          if((inserimento==ok)&&(trovato==0))
                              {
                              //fscanf(fp, "%c%c%c", &carattere, &carattere, &carattere);
                              scanf("%c%c%c", &carattere, &carattere, &carattere);
                              i=0;
                              strcpy(frase, empty);
                              while(carattere!='"')
                                  {
                                  frase[i]=carattere;
                                  i++;
                                  //fscanf(fp, "%c", &carattere);
                                  scanf("%c", &carattere);
                                  }
                              strcpy(current_node->dati, empty);
                              strcpy(current_node->dati, frase);
                              printf("ok %d\n", strlen(frase));
                              }
                              else {
                                    printf("no\n");
                                   }                                              
                          }
    /*fine write*/
    
            
    /*Gestione della delete */
                      if(strcmp((char *)operation, "delete")==0)
                        {
                        inserimento=ok;
                        current_node=root;
                        father=NULL;
                        //fscanf(fp, "%s", path);
                        scanf("%s", path);
                        next_node_name[0]=(char)'a';
                        i=0;
                        j=0;
                        for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)          //la variabile i è riservata 'a scorrere tutto il path'
                                {
                                node_name[j]=path[i];
                                j++;
                                }   //node_name contiene il primo nome nel path
                        node_name[j]=(char)NULL;      //terminatore di stringa
                          
                          
                          
                          
                        while((next_node_name[0]!=(char)NULL)&&(inserimento==ok))
                                {                      
                                if(path[i]=='/')
                                        {
                                        j=0;
                                        for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)
                                                {
                                                next_node_name[j]=path[i];
                                                j++;
                                                }
                                        next_node_name[j]=(char)NULL;    //terminatore di stringa
                                        }            //next_node_name contiene il secondo nome del path
                                        else next_node_name[0]=(char)NULL;
                               
                               
                               
                               
                                
                                if(next_node_name[0]!=(char)NULL)     //aggiorna current_node
                                        {
                                        trovato=1;
                                        for(k=0;((current_node->discendenti[k]!=NULL)&&(k<1024)&&trovato); k++) 
                                                {
                                                if((strcmp(current_node->discendenti[k]->name,node_name)==0)&&(current_node->discendenti[k]->tipo==directory)) trovato=0;  
                                                }
                                        if(trovato==0) 
                                                {
                                                father=current_node;    
                                                current_node=current_node->discendenti[k-1];
                                                }
                                                
                                                else 
                                                        inserimento=no;   //percorso non valido(o non esiste oppure si eccedono i limiti)
                                        } 
                                        
                                        
                                        
                                       else             //current_node qua diventa il nodo che si vuole cancellare
                                           {
                                           if(father==NULL)
                                               {
                                               for(k=0; (k<1024)&&(current_node->discendenti[k]!=NULL)&&trovato;k++)
                                                        {
                                                         if(!strcmp(current_node->discendenti[k]->name, node_name)) trovato=0;
                                                        }
                                               if(trovato==0) 
                                                                {
                                                                current_node=current_node->discendenti[k-1];
                                                                father=root;
                                                                }
                                                                else inserimento=no;
                                               }
                                               else
                                                    {
                                                    trovato=1;
                                                    for(k=0; (k<1024)&&(current_node->discendenti[k]!=NULL)&&trovato;k++)
                                                        {
                                                         if(!strcmp(current_node->discendenti[k]->name, node_name)) trovato=0; //non serve specificare il tipo perchè la delete cancella una risorsa qualunque
                                                        } 
                                                    if(trovato==0)  
                                                        {
                                                        father=current_node;
                                                        current_node=current_node->discendenti[k-1];
                                                        }
                                                        else 
                                                             inserimento=no; 
                                                    }
                                                  
                                           }          
                                           
                                           
                                                       
                                if(next_node_name[0]!=(char)NULL) strcpy(node_name, next_node_name);
                                }
                                
                                
                          
                        //cancellazione di current_node(se non ha figli)
                        if(inserimento==no)
                            {
                            printf("no\n");
                            }
                            else
                                {
                                if(current_node->tipo==file)   //"compatto a sx il vettore 'discendenti' del padre del nodo cancellato(current)
                                    {
                                    free(current_node);
                                    for(j=k-1; ((j<1024)&&(father->discendenti[j+1]!=NULL));j++)
                                        {
                                        father->discendenti[j]=father->discendenti[j+1];
                                        }
                                    father->discendenti[j]=NULL;
                                    printf("ok\n");
                                    }
                                    else //il nodo da cancellare è una directory e quindi devo controllare che non abbia figli
                                        {
                                        if(current_node->discendenti[0]==NULL)  //cancello la directory perchè non ha figli
                                            {
                                            free(current_node);
                                            for(j=k-1; ((j<1024)&&(father->discendenti[j+1]!=NULL));j++)
                                                {
                                                father->discendenti[j]=father->discendenti[j+1];
                                                }
                                            father->discendenti[j]=NULL;
                                            printf("ok\n");
                                            }
                                            else printf("no\n");
                                        }
                                }
                        }
    /*fine delete*/    
    
    
    
    
    /*Gestione della delete_r */            
                      if(strcmp((char *)operation, "delete_r")==0)
                        {
                        inserimento=ok;
                        current_node=root;
                        father=NULL;
                        //fscanf(fp, "%s", path);
                        scanf("%s", path);
                        next_node_name[0]=(char)'a';
                        i=0;
                        j=0;
                        for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)          //la variabile i è riservata 'a scorrere tutto il path'
                                {
                                node_name[j]=path[i];
                                j++;
                                }   //node_name contiene il primo nome nel path
                        node_name[j]=(char)NULL;      //terminatore di stringa
                          
                          
                          
                          
                        while((next_node_name[0]!=(char)NULL)&&(inserimento==ok))
                                {                      
                                if(path[i]=='/')
                                        {
                                        j=0;
                                        for(i++;((path[i]!='/')&&(path[i]!=(char)NULL)); i++)
                                                {
                                                next_node_name[j]=path[i];
                                                j++;
                                                }
                                        next_node_name[j]=(char)NULL;    //terminatore di stringa
                                        }            //next_node_name contienre il secondo nome del path
                                        else next_node_name[0]=(char)NULL;
                               
                               
                               
                               
                                
                                if(next_node_name[0]!=(char)NULL)     //aggiorna current_node
                                        {
                                        trovato=1;
                                        for(k=0;((current_node->discendenti[k]!=NULL)&&(k<1024)&&trovato); k++) 
                                                {
                                                if((strcmp(current_node->discendenti[k]->name,node_name)==0)&&(current_node->discendenti[k]->tipo==directory)) trovato=0;  
                                                }
                                        if(trovato==0) 
                                                {
                                                father=current_node;    
                                                current_node=current_node->discendenti[k-1];
                                                }
                                                
                                                else 
                                                        inserimento=no;   //percorso non valido(o non esiste oppure si eccedono i limiti)
                                        } 
                                        
                                        
                                        
                                       else             //current_node qua diventa il nodo che si vuole cancellare
                                           {
                                           if(father==NULL)
                                               {
                                               trovato=1;
                                               for(k=0; (k<1024)&&(current_node->discendenti[k]!=NULL)&&trovato;k++)
                                                        {
                                                         if(!strcmp(current_node->discendenti[k]->name, node_name)) trovato=0;
                                                        }
                                               if(trovato==0) 
                                                                {
                                                                current_node=current_node->discendenti[k-1];
                                                                father=root;
                                                                }
                                                                else inserimento=no;
                                               }
                                               else
                                                    {
                                                    trovato=1;
                                                    for(k=0; (k<1024)&&(current_node->discendenti[k]!=NULL)&&(inserimento==ok)&&trovato;k++)
                                                        {
                                                        if(!strcmp(current_node->discendenti[k]->name, node_name)) trovato=0; //non serve specificare il tipo perchè la delete cancella una risorsa qualunque
                                                        } 
                                                    if(trovato==0)  
                                                        {
                                                        father=current_node;
                                                        current_node=current_node->discendenti[k-1];
                                                        }
                                                        else 
                                                            inserimento=no;  
                                                    } 
                                                 
                                           }          
                                           
                                           
                                                       
                                if(next_node_name[0]!=(char)NULL) strcpy(node_name, next_node_name);
                                }
                                
                                
                          
                        //cancellazione di current_node(se non ha figli) e di TUTTI I SUOI DISCENDENTI
                        if(inserimento==no)
                            {
                            printf("no\n");
                            }
                            else
                                {
                                for(j=k-1; ((j<1024)&&(father->discendenti[j+1]!=NULL));j++)  //compatto a sx il vettore father->discendenti
                                    {
                                    father->discendenti[j]=father->discendenti[j+1];
                                    }
                                    father->discendenti[j]=NULL;
                                libera_ric(current_node);
                                printf("ok\n");
                                }
                        }
    /*fine delete_r*/ 
    
    
    /*Gestione della find*/ 
                      if(strcmp((char *)operation, "find")==0)
                        {
                        controllo_find=0;
                        //fscanf(fp, "%s", node_name);
                        scanf("%s", node_name);
                        for(i=0; i<(255*256); i++) path[i]=(char)NULL;
                        for(i=0; i<200; i++) *percorsi[i]=(char)NULL;
                        z=0;
                        find_ric(root, node_name, path, &controllo_find);
                        
                        
                        /*stampa in ordine lesicografico i percorsi trovati dalla find*/
                        for(i=0; *percorsi[i]!=(char)NULL; i++)
                            {
                            for(j=i; *percorsi[j]!=(char)NULL; j++)
                                {
                                if(strcmp(percorsi[i], percorsi[j])>0)
                                    {
                                    strcpy(path, percorsi[i]);
                                    strcpy(percorsi[i], percorsi[j]);
                                    strcpy(percorsi[j], path);
                                    }    
                                }    
                            }
                        for(i=0; *percorsi[i]!=(char)NULL; i++) printf("ok %s\n", percorsi[i]);
                        
                        /*fine stampa*/
                        
                        
                        if(controllo_find==0) printf("no\n");
                        }
    /*fine find*/ 
    
    
    
                      //fscanf(fp, "%s", operation);
                      scanf("%s", operation);                  
                      }  //fine del file in input

     
     //fclose(fp);  
     //scanf("%d");
     }
