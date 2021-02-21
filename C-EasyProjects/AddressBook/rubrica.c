#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200

char* ricercanumber(char *nome, char *cognome,FILE* irub);
char* ricercanominativo(char* number, FILE* irub);
void displaylist(FILE* irub);
void deletecontact(char *nome, char *cognome, FILE* irub, FILE* tmp);


int main(int argc, char const *argv[])
{
    FILE *irub, *orub;
    int op,verify1,verify2;
    char nome[SIZE],cognome[SIZE],number[11];
    char* buffer;
    while(1) 
    {
    printf("0) EXIT \n1) Inserire nuovo contatto \n2) Cercare un numero \n3) Cercare un nominativo \n4) Stampa rubrica \n5) Elimina contatto\nQuale operazione vuoi eseguire? ");
    scanf("%d",&op);
    if (op==0) return 0; //Close program
    if (op==1) //Insert the new contact
    {
        printf("Nome da inserire "); scanf("%s",nome);
        printf("Cognome da inserire "); scanf("%s",cognome);
        printf ("Numero da inserire "); scanf("%s",number);
        orub = fopen("rubrica.txt","a"); //Open the file in append mode for not overwrite the contacts and add the new contact.
        irub = fopen("rubrica.txt","r");
        verify1=(strcmp(ricercanumber(nome,cognome,irub),"0")==0);
        verify2=(strcmp(ricercanominativo(number,irub),"0")==0);
        printf("%d\n",verify1);
        printf("%d\n",verify2);
        /*if (verify)
        {
        fseek(orub,0,SEEK_END); //The pointer of the file goes to the end of the file
        fprintf(orub, "%s %s %s\n",nome, cognome, number); //Writes on the file the new contact
        printf("CONTATTO INSERITO CON SUCCESSO \n\n");
        }
        else printf("Contatto già esistente \n");
        printf("----------------------------------------------------------------------------------------------------\n");*/
        fclose(orub);
        fclose(irub);
        
    }
    if (op==2) //Search the number of a contact by name and surname
    {
        printf("Nome del numero da cercare "); scanf("%s",nome);
        printf("Cognome del numero da cercare "); scanf("%s",cognome);
        irub= fopen("rubrica.txt","r");
        strcpy(number,ricercanumber(nome,cognome,irub));
        if (strcmp(number,"0")==0) printf("Numero non trovato \n");
        else printf("Numero: %s\n\n",number);
        printf("----------------------------------------------------------------------------------------------------\n");
        fclose(irub);
    }
    if (op==3) //Search the nominative of a contact by number
    {
        printf("Numero da cercare "); scanf("%s",number);
        irub=fopen("rubrica.txt","r");
        buffer=(char*) malloc(((SIZE*2)+2)*sizeof(char));
        strcpy(buffer,ricercanominativo(number,irub));
        if (strcmp(buffer,"0")==0) printf("Nome e cognome non esistenti associati al numero\n");
        else printf("Nominativo: %s\n\n",buffer);
        printf("----------------------------------------------------------------------------------------------------\n");
        fclose(irub);
    }
    if (op==4) //Display the full list of contacts
    {
        printf("Questa è la lista dei contatti in rubrica:\n");
        irub=fopen("rubrica.txt","r");
        displaylist(irub);
        fclose(irub);
        printf("----------------------------------------------------------------------------------------------------\n");
    }
    if (op==5) //Delete a contact
    {   printf("Nome del numero da eliminare "); scanf("%s",nome);
        printf("Cognome del numero da eliminare "); scanf("%s",cognome);
        FILE *tmp = fopen("tmpfile.txt","w");
        irub = fopen("rubrica.txt","r");
        deletecontact(nome,cognome,irub,tmp);
        fclose(irub);
        fclose(tmp);
        remove("rubrica.txt");
        rename("tmpfile.txt","rubrica.txt");
    }   
    }
}

char* ricercanumber(char *nome, char *cognome,FILE* irub)
{
   
    char line[SIZE*3];
    char *word;
    while (fgets(line,SIZE*3,irub)) //Takes one by one the rows of the file
    {
        word=strtok(line," "); //Strtok --> Takes characters until doesnt find the delimiter. In this case it takes the name of the contact
        if (strcmp(nome,word)==0 && strcmp(cognome,strtok(NULL," "))==0) return strtok(NULL,"\n"); //Compare if name and surname are the same and returns the number.
    }
    printf("ciao");
    return "0";
}

char* ricercanominativo(char* number, FILE* irub)
{
    char line[SIZE*3];
    char *word; char nome[SIZE]; char cognome[SIZE]; char *num;
    while (fgets(line,SIZE*3,irub)) //Takes one by one the rows of the file
    {
        word=strtok(line," "); 
        strcpy(nome,word);
        strcpy(cognome,strtok(NULL," "));
        word=malloc(strlen(nome)+strlen(cognome)+2); //Allocates space for the nominative (+2 because it contains the " " and the \0)
        strcpy(word,nome); strcat(word," "); strcat(word,cognome); //Build the string nominative = name + surname
        if (strcmp(number,strtok(NULL,"\n"))==0) {return word;} //if the number are the same returns the nominative string
    }
    return "0";
}

void displaylist(FILE* irub) 
{
    int i=1;
    char line[SIZE*3];
    while((fgets(line,SIZE*3,irub)))
    {
        printf("%d) %s",i,line);
        i++;
    }
}

void deletecontact(char *name, char *surname, FILE* irub, FILE* tmp)
{
    char line[SIZE*3];
    char *word; char nome[SIZE]; char cognome[SIZE]; char num[SIZE];
    while (fgets(line,SIZE*3,irub)) //Takes one by one the rows of the file
    {
        word=strtok(line," "); 
        strcpy(nome,word);
        strcpy(cognome,strtok(NULL," "));
        strcpy(num,strtok(NULL,"\n"));
        word=malloc(strlen(nome)+strlen(cognome)+strlen(num)+3); //Allocates space for the nominative (+2 because it contains the " " and the \0)
        strcpy(word,nome); strcat(word," "); strcat(word,cognome); strcat(word," "); strcat(word,num); //Build the string nominative = name + surname
        if (strcmp(name,nome)!=0 || strcmp(cognome,surname)) fprintf(tmp,"%s %s %s\n",nome,cognome,num);
    }
}
