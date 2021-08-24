#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct  USER{
    char nume[51];
    char prenume[51];
    float scor;
} *cu;

typedef struct INTREBARE{
    char enunt[151];
    int dificultate;
    int raspunsCorect[4];
    char raspunsuri[4][31];
}*intrebaretest;

void waitForUser(){
    printf("Apasa ENTER pentru a continua ...");
    fflush(stdin);
    getchar();
    getchar();
}

void afiseazaMesajBunVenit(){
    system("clear");
    printf("Salutare! \nAici este locul in care iti poti verifica cultura generala \n\nMult succes!\n\n");
    waitForUser();
}

void getUsername(int *nrUtilizatorConectat, int *nrUtilizatori, int *utilizatorInregistrat, int *adminLogged, struct USER *utilizatori){
    system("clear");
    printf("Daca ai mai folosit aceasta aplicatie introdu acelasi Username.\nDaca este prima data cand incerci acest Quiz App introdu un Username. Acesta o sa fie salvat in baza de date impreuna cu scorul tau\n\n");

    char nume[100];
    char prenume[100];

    fflush(stdin);
    printf("Introdu numele: ");
    scanf("%s", nume);
    fflush(stdin);

    printf("Introdu prenumele: ");
    scanf("%s", prenume);
  
    if(strcmp(nume, "admin") == 0 && strcmp(prenume, "parola") == 0){
        *adminLogged = 1;
    }
    else{
        *adminLogged = 0;
        int gasit = 0, i = 0;
        while (gasit == 0 && i < *nrUtilizatori){
            if(strcmp(nume, utilizatori[i].nume)==0 && strcmp(prenume, utilizatori[i].prenume)==0){
                gasit = 1;
                printf("Contul tau a fost gasit! Punctele tale vor fi adaugate la cele deja existente\n");
                waitForUser();
                *nrUtilizatorConectat = i; 
            }
            i++;
        }

        if(gasit == 0){

            printf("Nu am gasit contul acesta! Un cont nou va fi creat folosind datele introduse \n");
            (*nrUtilizatori)++;
            int nr = (*(nrUtilizatori)) * (sizeof(struct USER));
            utilizatori = (struct USER *)realloc(utilizatori ,nr);
            nr = *(nrUtilizatori);
            nr--;

            strcpy(utilizatori[nr].nume, nume);
            strcpy(utilizatori[nr].prenume, prenume);
            utilizatori[nr].scor = 0;

            *nrUtilizatorConectat = nr;
        }
    }

    system("clear");
    
  
    waitForUser();

}

void afiseazaMeniu(int adminLogged){
    system("clear");
    printf("############\n");
    printf("# Quiz App #\n");
    printf("############\n\n");

    printf(" 1 -> Random Quiz \n");
    printf(" 2 -> Hard Quiz \n");
    printf(" 3 -> Afiseaza Clasament\n");
    printf(" 4 -> Iesire \n\n");
}

float startQuizRandom(struct INTREBARE *intrebari, int nrIntrebari){
    system("clear");
    printf("Random Quiz\n\n");

    int nrIntrebariAlese, r, raspunsAles, k, a, intrebariAlese[20] = {0}, ok = 0;
    float p, pAcumulate = 0;

    printf("Cate intrebari doriti sa primiti? 5 / 10 / 15\n");
    do{
        scanf("%d", &nrIntrebariAlese);
        if((nrIntrebariAlese ==5 || nrIntrebariAlese == 10 || nrIntrebariAlese == 15 )){
            ok = 1;
        }
        else{
            printf("Numar de intrebari invalid");
        }
    }while(ok == 0);


    // generez intrebarile
    time_t t;
    srand((unsigned) time(&t));
    
    
    k = nrIntrebariAlese;
    while (k != 0){
        do{
            a = rand() % nrIntrebari;
        }while(intrebariAlese[a]==1);

        intrebariAlese[a] = 1;

        k--;
    }
    k = nrIntrebariAlese;
    for(int i = 0; i < nrIntrebari; i++){
        system("clear");
        if(intrebariAlese[i] == 1){
            printf("Punctaj acumulat: %.2f\n\n", pAcumulate);
            printf("Intrebarea numarul %d:\n\n", nrIntrebariAlese - k + 1);
            k--;
            printf("%s\n", intrebari[i].enunt);
            for (int j = 0; j < 4; j++){
                printf("%d) %s\n", j+1, intrebari[i].raspunsuri[j]);
            }

            printf("\nRaspunsul tau: ");
            ok = 0;
            do{
                scanf("%d", &raspunsAles);
                if(raspunsAles > 4 || raspunsAles < 1){
                    printf("Alegere invalida!");
                }
                else{
                    ok = 1;
                }
            } while (ok == 0);
            if(intrebari[i].raspunsCorect[raspunsAles-1] == 1){
                p = intrebari[i].dificultate * 0.5;
                pAcumulate += p;
                printf("\nRaspuns corect! Ai acumulat inca %.2f puncte\n", p);
            }
            else{
                for (int s = 0; s < 4; s++){
                    if(intrebari[i].raspunsCorect[s] == 1)
                        r = s;
                }
                
                printf("Raspuns gresit!!! Raspunsul corect este: %d) %s\n",r+1, intrebari[i].raspunsuri[r]);
            }
            waitForUser();
        }
    }
    system("clear");
    printf("Ai acumulat %.2f puncte!\n\n", pAcumulate);
    waitForUser();

    return pAcumulate;
    
}

float startQuizDificil(struct INTREBARE *intrebari, int nrIntrebari){
    system("clear");
    printf("Hard Quiz\n\n");

    int nrIntrebariAlese, r, raspunsAles, k, a, intrebariAlese[20] = {0}, ok = 0;
    float p, pAcumulate = 0;

    printf("Atentie! Fiecare raspuns gresit este penalizat!\n\n");

    printf("Cate intrebari doriti sa primiti? 5 / 10\n");
    do{
        scanf("%d", &nrIntrebariAlese);
        if((nrIntrebariAlese == 5 || nrIntrebariAlese == 10)){
            ok = 1;
        }
        else{
            printf("Numar de intrebari invalid");
        }
    }while(ok == 0);


    // generez intrebarile
    time_t t;
    srand((unsigned) time(&t));
    
    
    k = nrIntrebariAlese;
    while (k != 0){
        do{
            a = rand() % nrIntrebari;
        }while(intrebariAlese[a]==1 && intrebari[a].dificultate != 3);
        intrebariAlese[a] = 1;

        k--;
    }

    k = nrIntrebariAlese;
    for(int i = 0; i < nrIntrebari; i++){
        system("clear");
        if(intrebariAlese[i] == 1){
            printf("Punctaj acumulat: %.2f\n\n", pAcumulate);
            printf("Intrebarea numarul %d:\n\n", nrIntrebariAlese - k + 1);
            k--;
            printf("%s\n", intrebari[i].enunt);
            for (int j = 0; j < 4; j++){
                printf("%d) %s\n", j+1, intrebari[i].raspunsuri[j]);
            }

            printf("\nRaspunsul tau: ");
            ok = 0;
            do{
                scanf("%d", &raspunsAles);
                if(raspunsAles > 4 || raspunsAles < 1){
                    printf("Alegere invalida!");
                }
                else{
                    ok = 1;
                }
            } while (ok == 0);
            if(intrebari[i].raspunsCorect[raspunsAles-1] == 1){
                p = intrebari[i].dificultate * 0.5;
                pAcumulate += p;
                printf("\nRaspuns corect! Ai acumulat inca %.2f puncte\n", p);
            }
            else{
                for (int s = 0; s < 4; s++){
                    if(intrebari[i].raspunsCorect[s] == 1)
                        r = s;
                }
                p = intrebari[i].dificultate * 0.5;
                pAcumulate -= p;
                printf("Raspuns gresit!!! Raspunsul corect este: %d) %s\n",r+1, intrebari[i].raspunsuri[r]);
                printf("\nAi pierdut %.2f puncte\n", p);
            }
            waitForUser();
        }

        
    }
    system("clear");
    if(pAcumulate > 0){
        printf("Ai acumulat %.2f puncte!\n\n", pAcumulate);
    }
    else{
        printf("Din pacate ai pierdut %.2f puncte!\n\n", -pAcumulate);
    }
    waitForUser();

    return pAcumulate;
    
    
    waitForUser();
}

void afiseazaClasament(struct USER *utilizatori, int nr){
    system("clear");
    printf("#####################\n");
    printf("Clasament Utilizatori\n");
    printf("#####################\n\n");

    printf("NUME    PRENUME     SCOR\n\n");

    for (int i = 0; i < nr; i++){
        printf("%s ", utilizatori[i].nume);
        printf("%s ", utilizatori[i].prenume);
        printf("%.2f \n", utilizatori[i].scor);
    }
    
    printf("\n");
    waitForUser();
}

void introduceAlegere(int *optiune){
    char a[51];
    int ok = 0;

    printf("\nAlege o optiune:");

    do{
        scanf("%s", a);
        
        if(strlen(a) > 1){
            printf("\nOptiunea introdusa este invalida! \nIntrodu optiunea aleasa:\n");
        }
        else if((int)a[0] < 49 || (int)a[0] > 52){
            printf("\nOptiunea introdusa este invalida! \nIntrodu optiunea aleasa:\n");
        }
        else 
            ok = 1;
    }while(!ok);
    
    *optiune = (int)a[0] - 48;
}

int main(){
    
    int optiune, nrUtilizatorConectat = 0, utilizatorInregistrat = 1, adminLogged, nrIntrebari, nrUtilizatori, ch;
    float p;
    FILE *finIntrebari;
    finIntrebari = fopen("intrebari.txt", "r");

    //citesc nr de intrebari
    fscanf(finIntrebari, "%d", &nrIntrebari);
 
    // declar vectorul de intrebari
    struct INTREBARE *intrebari;
    intrebari = (struct INTREBARE *)malloc(nrIntrebari * (sizeof(struct INTREBARE)));

     for (int j = 0; j < nrIntrebari; j++){
        ch = fgetc(finIntrebari);
        //enunt
        fscanf(finIntrebari, "%[^\n]", intrebari[j].enunt);
        
        //dificultate
        fscanf(finIntrebari, "%d", &intrebari[j].dificultate);

        //raspunsuri corecte
        for (int i = 0; i < 4; i++){
            fscanf(finIntrebari, "%d", &intrebari[j].raspunsCorect[i]);
        }
        
        // raspunsuri
        for (int i = 0; i < 4; i++){
            fscanf(finIntrebari, "%s", intrebari[j].raspunsuri[i]);
        }
    
    }

    fclose(finIntrebari);

    // am terminat de incarcat intrebarile

    // incarc utilizatorii  

    FILE *finUtilizatori;
    finUtilizatori = fopen("utilizatori.txt", "r");

    fscanf(finUtilizatori, "%d", &nrUtilizatori);

    // declar vectorul de utilizatori
    struct USER *utilizatori;
    utilizatori = (struct USER *)malloc(nrUtilizatori * (sizeof(struct USER)));

    for(int i = 0; i < nrUtilizatori; i++){

        fscanf(finUtilizatori, "%s", utilizatori[i].nume);

        fscanf(finUtilizatori, "%s", utilizatori[i].prenume);
        fscanf(finUtilizatori, "%f", &utilizatori[i].scor);
    }
    

    afiseazaMesajBunVenit();

//##################################
//##################################
//# Partea de logare #
//##################################
//##################################

    system("clear");
    printf("Daca ai mai folosit aceasta aplicatie introdu aceleasi nume si prenume.\nDaca este prima data cand incerci acest Quiz App introdu numele apoi prenumele. Acestea o sa fie salvate in baza de date impreuna cu scorul tau\n\n");

    char nume[100];
    char prenume[100];

    fflush(stdin);
    printf("Introdu numele: ");
    scanf("%s", nume);
    fflush(stdin);

    printf("Introdu prenumele: ");
    scanf("%s", prenume);
    int gasit = 0, i = 0;
    while (gasit == 0 && i < nrUtilizatori){
        if(strcmp(nume, utilizatori[i].nume)==0 && strcmp(prenume, utilizatori[i].prenume)==0){
            gasit = 1;
            printf("\nContul tau a fost gasit! Punctele tale vor fi adaugate la cele deja existente\n");
            waitForUser();
            nrUtilizatorConectat = i; 
        }
        i++;
    }

    if(gasit == 0){

        printf("\nNu am gasit contul acesta! Un cont nou va fi creat folosind datele introduse \n");
        nrUtilizatori++;
        int nr = (nrUtilizatori) * (sizeof(struct USER));
        utilizatori = (struct USER *)realloc(utilizatori ,nr);
        nr = nrUtilizatori;
        nr--;

        strcpy(utilizatori[nr].nume, nume);
        strcpy(utilizatori[nr].prenume, prenume);
        utilizatori[nr].scor = 0;

        nrUtilizatorConectat = nr;

        waitForUser();
    }

    fclose(finUtilizatori);

//####################################

    system("clear");

    printf("Bine ai venit, %s %s \nScorul tau actual este de %.2f puncte\n\n", utilizatori[nrUtilizatorConectat].nume, utilizatori[nrUtilizatorConectat].prenume, utilizatori[nrUtilizatorConectat].scor);

    waitForUser();
    if(utilizatorInregistrat){
        do{ 
            afiseazaMeniu(adminLogged);
            introduceAlegere(&optiune);

            switch (optiune){
                case 1:
                    //  quiz cu intrebari alese random din mai multe categorii
                    //  numar de intrebari la alegere -> 5 / 10 / 15 intrebari 
                    //  diferite niveluri de dificultate
                    p = utilizatori[nrUtilizatorConectat].scor;
                    p += startQuizRandom(intrebari, nrIntrebari);
                    utilizatori[nrUtilizatorConectat].scor = p;
                    break;
                case 2:
                    p = utilizatori[nrUtilizatorConectat].scor;
                    p += startQuizDificil(intrebari, nrIntrebari);
                    utilizatori[nrUtilizatorConectat].scor = p;
                    break;
                case 3:
                    afiseazaClasament(utilizatori, nrUtilizatori);
                    break;
                default:
                    break;
                }
        }while(optiune != 4 );
    }
    system("clear");

    FILE *finUtilizatori2;
    finUtilizatori2 = fopen("utilizatori.txt", "w");

    fprintf(finUtilizatori2, "%d\n", nrUtilizatori);

    for (int j = 0; j < nrUtilizatori; j++){
        fprintf(finUtilizatori2, "%s %s\n%.2f\n", utilizatori[j].nume, utilizatori[j].prenume, utilizatori[j].scor); 
    }
    
    fclose(finUtilizatori2);
    
    printf("\n\nLa revedere!\n\n");

}

