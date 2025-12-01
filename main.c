#include <stdio.h>
#include <string.h>
#include <stdlib.h>           
#include <ctype.h>
#include <time.h>
#define memoire 50
#define memoire_chaine 100

//tableaux et matrices :
    //tableaux
long long int T_NLivre[memoire] = {};
char T_Titre[memoire][memoire_chaine] = {{""}};
int T_Nbr_exp[memoire] = {};
char T_livre_supprime_entregistre[memoire] = {'\0'}; // tableau livre supprimer E(entregistree) S(supprimee)
int taille_tableau_livre;
    
    //matrice
long long int M_eprunts_livre[memoire][8] = {};
char T_livre_retour[memoire] = {'\0'};  // tableau livre retour R(retourne) N(non retourne)
char T_emprunt_supprime[memoire] = {'\0'}; // tableau emprunt supprimer S(supprime) N(non supprime)
int taille_matrice_emprunts;

//----------------------------------------------------------//
// DATE COURANTE 
int jr_courant = 0;
int ms_courant = 0;
int an_courant = 0;

int est_bissextile(int annee) { // Fonction pour vérifier si une année est bissextile
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
        return 1; // L'année est bissextile
    }
    return 0;} // L'année n'est pas bissextile

void calculer_date_courante(char tampon[11]) {
    time_t temps_courant = time(NULL);
    struct tm *tm_info = localtime(&temps_courant);

    // Format texte jj/mm/aaaa
    snprintf(tampon, 11, "%02d/%02d/%04d",
             tm_info->tm_mday,
             tm_info->tm_mon + 1,
             tm_info->tm_year + 1900);

    // Mettre jour/mois/annee dans les variables globales
    jr_courant = tm_info->tm_mday;
    ms_courant = tm_info->tm_mon + 1;
    an_courant = tm_info->tm_year + 1900;}

int date_superieure(int jr1, int ms1, int an1, int jr2, int ms2, int an2) {
    if (an1 > an2) return 1;
    if (an1 < an2) return 0;

    if (ms1 > ms2) return 1;
    if (ms1 < ms2) return 0;

    if (jr1 > jr2) return 1;
    return 0;
}
int date_valide(int jr, int ms, int an) {
    if (an < 1900 || ms < 1 || ms > 12 || jr < 1) return 0;

    int jours_par_mois[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    // Ajuster février pour année bissextile
    if ((an % 4 == 0 && an % 100 != 0) || (an % 400 == 0)) jours_par_mois[1] = 29;

    if (jr > jours_par_mois[ms - 1]) return 0;
    return 1;
}

//----------------------------------------------------------//

int lire_entier() {
    int x;
    char buffer[100];
    int lu = 0;
    while (lu == 0) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &x) == 1) {
                lu = 1;
            } else {
                printf("Veuillez entrer un nombre : ");
            }
        }
    }
    return x;
}

//----------------------------------------------------------//
/*-------------MENUS-------------*/
void afficher_menu_principal(){
    //system("cls || clear");// pour vider le terminal
    printf("\nVEUILLEZ CHOISIR : ");
    printf("\n1. GESTION DE LA BIBLIOTHEQUE");
    printf("\n2. GESTION DES EMPRUNTS");        
    printf("\n3. STATISTIQUES");
    printf("\n4. QUITEER L'APPLICATION");
    printf("\nOPTION(1/2/3/4) = ");}

void afficher_menu_bibliotheque(){
    printf("GESTION DE LA BIBLIOTHEQUE");
    printf("\nVeuillez choisir");
    printf("\n1. AFFICHER TOUS LES LIVRES DE LA BIBLOTHEQUE");
    printf("\n2. AJOUTER UN NOUVEAU LIVRE");
    printf("\n3. SUPPRIMER UN LIVRE");
    printf("\n4. MODIFIER LE NOMBRE D'EXEMPLAIRES D'UN LIVRE");
    printf("\n5. RECHERCHER UN LIVRE");
    printf("\n6. AFFICHER LES LIVRES DISPONIBLES");
    printf("\n7. MENU PRINCIPAL");
    printf("\nOPTION(1/2/3/4/5/6/7) = ");}

void afficher_menu_emprunt(){
    printf("1. AJOUTER UN EMPRUNT\n");
    printf("2. CONSULTER LES EMPRUNTS D'UN ADHERENT\n");
    printf("3. ENREGISTRER LE RETOUR D'UN LIVRE\n");
    printf("4. AFFICHER LA LISTE DES EMPRUNTS EN COURS\n");
    printf("5. AFFICHER LES LIVRES EN RETARD DE RETOUR\n");
    printf("6. AFFICHER LES EMPRUNTS RELATIFS A UNE DATE DE RETOUR PREVUE\n");
    printf("7. SUPPRIMER UN ENSEMBLE D'EMPRUNTS\n");
    printf("8. MENU PRINCIPAL");
    printf("\nOPTION(1/2/3/4/5/6/7/8) = ");}

void afficher_menu_statistique(){
    printf("1. AFFICHER LE NOMBRE TOTAL DE LIVRES, D'ADHERENTS ET D'EMPRUNT\n");
    printf("2. AFFICHER LE(S) LIVRE(S) LE(S) PLUS EMPRUNTE(S)\n");
    printf("3. AFFICHER LE(S) LIVRE(S) JAMAIS EMPRUNTE(S)\n");
    printf("4. AFFICHER LE(S) LIVRE(S) LE(S) PLUS EMPRUNTE(S) DANS UNE PERIODE DONNEE\n");
    printf("5. AFFICHER LE(S) EMPRUNTEUR(S) LE(S) PLUS FREQUENT(S)\n");
    printf("6. MENU PRINCIPAL\n");
    printf("\nOPTION(1/2/3/4/5/6/7) = ");}

void Set_data_base(){
    //long long int T_NLivre[memoire],int T_Nbr_exp[memoire], char T_Titre[memoire][memoire_chaine],char M_eprunts_livre[memoire][8][memoire_chaine],char T_livre_retour[memoire],char T_livre_supprime_entregistre[memoire]
    
    //Tableaux des livres :
        //nombre livre called isbn
    T_NLivre[0] = 9780553897858;  T_Nbr_exp[0] = 5;  strcpy(T_Titre[0], "A Game of Thrones");     T_livre_supprime_entregistre[0] = 'E';
    T_NLivre[1] = 9780553579907;  T_Nbr_exp[1] = 2;  strcpy(T_Titre[1], "A Clash of Kings");      T_livre_supprime_entregistre[1] = 'E';
    T_NLivre[2] = 9780553573424;  T_Nbr_exp[2] = 6;  strcpy(T_Titre[2], "A Storm of Swords");     T_livre_supprime_entregistre[2] = 'E';  
    T_NLivre[3] = 9780553582024;  T_Nbr_exp[3] = 9;  strcpy(T_Titre[3], "A Feast for Crows");     T_livre_supprime_entregistre[3] = 'E';
    T_NLivre[4] = 9780553801477;  T_Nbr_exp[4] = 7;  strcpy(T_Titre[4], "A Dance with Dragons");  T_livre_supprime_entregistre[4] = 'E';

    //Matrice
    //1)
    M_eprunts_livre[0][0] = atoll("00123459");
    M_eprunts_livre[0][1] = atoll("9780553897858");
    M_eprunts_livre[0][2] = atoll("07");
    M_eprunts_livre[0][3] = atoll("11");
    M_eprunts_livre[0][4] = atoll("2025");
    M_eprunts_livre[0][5] = atoll("07");
    M_eprunts_livre[0][6] = atoll("12");
    M_eprunts_livre[0][7] = atoll("2025");
    T_livre_retour[0] = 'R';
    T_emprunt_supprime[0] = 'S';
    //2)
    M_eprunts_livre[1][0] = atoll("00123158");
    M_eprunts_livre[1][1] = atoll("9780553579907");
    M_eprunts_livre[1][2] = atoll("07");
    M_eprunts_livre[1][3] = atoll("12");
    M_eprunts_livre[1][4] = atoll("2025");
    M_eprunts_livre[1][5] = atoll("06");
    M_eprunts_livre[1][6] = atoll("01");
    M_eprunts_livre[1][7] = atoll("2026");
    T_livre_retour[1]='N';
    T_emprunt_supprime[1] = 'N';
    //3)
    M_eprunts_livre[2][0] = atoll("00123987");
    M_eprunts_livre[2][1] = atoll("9780553573424");
    M_eprunts_livre[2][2] = atoll("10");
    M_eprunts_livre[2][3] = atoll("10");
    M_eprunts_livre[2][4] = atoll("2025");
    M_eprunts_livre[2][5] = atoll("09");
    M_eprunts_livre[2][6] = atoll("11");
    M_eprunts_livre[2][7] = atoll("2025");
    T_livre_retour[2] = 'R';
    T_emprunt_supprime[2] = 'N';
    //4)
    M_eprunts_livre[3][0] = atoll("00124567");
    M_eprunts_livre[3][1] = atoll("9780553579907"); 
    M_eprunts_livre[3][2] = atoll("25");
    M_eprunts_livre[3][3] = atoll("11");
    M_eprunts_livre[3][4] = atoll("2025"); 
    M_eprunts_livre[3][5] = atoll("25");
    M_eprunts_livre[3][6] = atoll("12");
    M_eprunts_livre[3][7] = atoll("2025");
    T_livre_retour[3]='R';
    T_emprunt_supprime[3] = 'N';
    //5)
    M_eprunts_livre[4][0] = atoll("00125678");
    M_eprunts_livre[4][1] = atoll("9780553573424");
    M_eprunts_livre[4][2] = atoll("28");
    M_eprunts_livre[4][3] = atoll("12");
    M_eprunts_livre[4][4] = atoll("2025");
    M_eprunts_livre[4][5] = atoll("27");
    M_eprunts_livre[4][6] = atoll("01");
    M_eprunts_livre[4][7] = atoll("2026");
    T_livre_retour[4] = 'N';
    T_emprunt_supprime[4] = 'N';
    //6)
    M_eprunts_livre[5][0] = atoll("00129876");
    M_eprunts_livre[5][1] = atoll("9780553573424");
    M_eprunts_livre[5][2] = atoll("15");
    M_eprunts_livre[5][3] = atoll("09");
    M_eprunts_livre[5][4] = atoll("2025");
    M_eprunts_livre[5][5] = atoll("15");
    M_eprunts_livre[5][6] = atoll("10");
    M_eprunts_livre[5][7] = atoll("2025");
    T_livre_retour[5]='R';
    T_emprunt_supprime[5] = 'N';
    //7)
    M_eprunts_livre[6][0] = atoll("00127890");
    M_eprunts_livre[6][1] = atoll("9780553582024");
    M_eprunts_livre[6][2] = atoll("03");
    M_eprunts_livre[6][3] = atoll("10");
    M_eprunts_livre[6][4] = atoll("2025");
    M_eprunts_livre[6][5] = atoll("02");
    M_eprunts_livre[6][6] = atoll("11");
    M_eprunts_livre[6][7] = atoll("2025");
    T_livre_retour[6]='R';
    T_emprunt_supprime[6] = 'N';
    //8)
    M_eprunts_livre[7][0] = atoll("00129012");
    M_eprunts_livre[7][1] = atoll("9780553801477");
    M_eprunts_livre[7][2] = atoll("20");
    M_eprunts_livre[7][3] = atoll("11");
    M_eprunts_livre[7][4] = atoll("2025");
    M_eprunts_livre[7][5] = atoll("20");
    M_eprunts_livre[7][6] = atoll("12");
    M_eprunts_livre[7][7] = atoll("2025");
    T_livre_retour[7] = 'R';
    T_emprunt_supprime[7] = 'N';
    //9) this emprunts est en retard de retour
    M_eprunts_livre[8][0] = atoll("00129999");         
    M_eprunts_livre[8][1] = atoll("9780553582024");      
    M_eprunts_livre[8][2] = atoll("01");                
    M_eprunts_livre[8][3] = atoll("11");
    M_eprunts_livre[8][4] = atoll("2025");
    M_eprunts_livre[8][5] = atoll("20");                 
    M_eprunts_livre[8][6] = atoll("11");                 
    M_eprunts_livre[8][7] = atoll("2025");               
    T_livre_retour[8] = 'N';                             
    T_emprunt_supprime[8] = 'N';
}
//----------------------------------------------------------//


//----------------------------------------------------------//
/*-------------CALCULER_TABLEAUX & MATRICES-------------*/
int fonction_taille_tableau(char T_Titre[memoire][memoire_chaine]) {
    int compteur = 0;
    while( (compteur < memoire) && strcmp(T_Titre[compteur],"") != 0){compteur ++;}
    return compteur;
}
int fonction_taille_matrice_emprunts(long long int M_eprunts_livre[memoire][8]) {
    int compteur = 0;
    while (compteur < memoire && M_eprunts_livre[compteur][0] != 0) {
        compteur++;
    }
    return compteur;
}
//----------------------------------------------------------//

//----------------------------------------------------------//
/*-------------PART1-------------*/ //done
int existe_par_nom_livre(int taille_tableau, char T_Titre[memoire][memoire_chaine], char nom_livre[memoire_chaine]) {
    int i = 0;
    int position = -1;
    while (i < taille_tableau && position == -1) {
        if (strcmp(T_Titre[i], nom_livre) == 0) {
            position = i;
        } else {
            i = i + 1;
        }
    }
    return position;}

int existe_par_numero_livre(int taille_tableau,long long int T_NLivre[memoire],long long int numero_livre) {
    int i = 0;
    int position = -1;
    while (i < taille_tableau && position == -1) {
        if (T_NLivre[i] == numero_livre) {
            position = i;
        } 
        else {
            i = i + 1;
        }
    }
    return position;}

int existe_par_nombre_exemplaire(int taille_tableau,int T_Nbr_exp[memoire],int nombre_exemplaire){
    
    int test = -1;
    do{
        test ++;
    }
    while(test < taille_tableau && nombre_exemplaire != T_Nbr_exp[test]);
    if (test == taille_tableau){
        return -1;
    }
    else{
        return test;
    }
}
//Question 1 :
void afficher_tous_livres(int taille_tableau_livre,long long int T_NLivre[memoire],char T_Titre[memoire][memoire_chaine],int T_Nbr_exp[memoire]) {
    // En-tête du tableau
    printf("\n┌───────────────┬──────────────────────────────┬──────────────┐\n");
    printf("│  N°Livre      │ Titre                        │ Nbr Exempl   │\n");
    printf("├───────────────┼──────────────────────────────┼──────────────┤\n");

    int livres_affiches = 0;
    for (int i = 0; i < taille_tableau_livre; i++) {
        if (T_Titre[i][0] != '\0') { // Affiche seulement les livres valides
            
            printf("│ %08lld │ %-28s │ %-12d │\n", T_NLivre[i], T_Titre[i], T_Nbr_exp[i]);
            livres_affiches++;
        }
    }

    if (livres_affiches == 0)
        printf("│        Aucun livre enregistré          │              │\n");

    printf("└───────────────┴──────────────────────────────┴──────────────┘\n");
}
void afficher_livres_etats(int taille_tableau_livre, 
                           long long int T_NLivre[memoire], 
                           char T_Titre[memoire][memoire_chaine], 
                           int T_Nbr_exp[memoire], 
                           char T_livre_supprime_entregistre[memoire]) {

    // Affichage de l'en-tête du tableau
    printf("\n┌───────────────┬──────────────────────────────┬──────────────┬────────────┐\n");
    printf("│  N°Livre      │ Titre                        │ Nbr Exempl   │ Etat       │\n");
    printf("├───────────────┼──────────────────────────────┼──────────────┼────────────┤\n");

    int livres_affiches = 0;

    // Parcours de tous les livres
    for (int i = 0; i < taille_tableau_livre; i++) {
        if (T_Titre[i][0] != '\0') { // Si le livre existe
            char etat = T_livre_supprime_entregistre[i];

            // Si l'état est inconnu, considérer comme enregistré
            if (etat != 'E' && etat != 'S') {
                etat = 'E';
            }

            // Définir le texte à afficher selon l'état
            char etat_texte[12];
            if (etat == 'E') {
                strcpy(etat_texte, "Enregistré");
            } else if (etat == 'S') {
                strcpy(etat_texte, "Supprimé");
            }

            // Affichage de la ligne du livre
            printf("│ %08lld │ %-28s │ %-12d │ %-11s │\n",
                   T_NLivre[i], T_Titre[i], T_Nbr_exp[i], etat_texte);

            livres_affiches++;
        }
    }

    // Si aucun livre n'est enregistré
    if (livres_affiches == 0) {
        printf("│        Aucun livre enregistré          │              │            │\n");
    }

    // Bas du tableau
    printf("└───────────────┴──────────────────────────────┴──────────────┴────────────┘\n");
}
//Question 2 :
void ajouter_nouveau_livres( char T_Titre[memoire][memoire_chaine],long long int T_NLivre[memoire], int T_Nbr_exp[memoire]) {                 
    
    char nom_livre[memoire_chaine],continuer[memoire_chaine] = "O";
    int nombre_exemplaire_livre;
    long long int numero_livre;

    while (toupper(continuer[0]) == 'O') {
        if (taille_tableau_livre >= memoire) {printf("Mémoire pleine : impossible d’ajouter un nouveau livre.\n");strcpy(continuer, "N");}
        else {
            /* ---- Étape 1 : Saisie et validation du numéro ---- */
            do {
                printf("\nDonner le numéro du livre (13 chiffres) : ");
                scanf("%lld", &numero_livre);
                while(getchar() != '\n');
                if (!(9780000000000LL <= numero_livre && numero_livre <= 9789999999999LL)) {
                    printf("Numéro invalide ! Un numéro doit contenir exactement 13 chiffres.\n");
                    do {
                        printf("Voulez-vous retaper le numéro ? (O/N) : ");
                        fgets(continuer, memoire_chaine, stdin);
                        continuer[strcspn(continuer, "\n")] = '\0';
                    } while (toupper(continuer[0]) != 'O' && toupper(continuer[0]) != 'N');
                }
            } while (!(9780000000000LL <= numero_livre && numero_livre <= 9789999999999LL) && toupper(continuer[0]) == 'O');
                     
            if (toupper(continuer[0]) == 'O') {

                /* ---- Vérification si le livre existe déjà par numéro ---- */
                if (existe_par_numero_livre(taille_tableau_livre, T_NLivre, numero_livre) != -1) {
                    T_Nbr_exp[existe_par_numero_livre(taille_tableau_livre, T_NLivre, numero_livre)] += 1;
                    printf("Ce livre existe déjà — un exemplaire supplémentaire a été ajouté.\n");
                } 
                else {

                    /* ---- Étape 2 : Saisie du titre ---- */
                    do {
                        printf("Donner le titre du livre : ");
                        fgets(nom_livre, memoire_chaine, stdin);
                        nom_livre[strcspn(nom_livre, "\n")] = '\0';

                        if (strlen(nom_livre) == 0) {
                            printf("Titre invalide ! Vous devez entrer un titre non vide.\n");
                            do {
                                printf("Voulez-vous retaper le titre ? (O/N) : ");
                                fgets(continuer, memoire_chaine, stdin);
                                continuer[strcspn(continuer, "\n")] = '\0';
                            } while (toupper(continuer[0]) != 'O' && toupper(continuer[0]) != 'N');
                        }
                    } while (strlen(nom_livre) == 0 && toupper(continuer[0]) == 'O');

                    /* ---- Vérification doublon de titre ---- */
                    if (toupper(continuer[0]) == 'O') {
                        if (existe_par_nom_livre(taille_tableau_livre, T_Titre, nom_livre) != -1) {printf("Attention : un autre livre avec le même titre existe déjà.\n");}
                        /* ---- Étape 4 : Saisie du nombre d'exemplaires ---- */
                        do {
                            printf("Donner le nombre d'exemplaires : ");
                            nombre_exemplaire_livre = lire_entier();

                            if (nombre_exemplaire_livre <= 0) {
                                printf("Le nombre d'exemplaires doit être supérieur à 0.\n");
                                do {
                                    printf("Voulez-vous retaper ? (O/N) : ");
                                    fgets(continuer, memoire_chaine, stdin);
                                    continuer[strcspn(continuer, "\n")] = '\0';
                                } while (toupper(continuer[0]) != 'O' && toupper(continuer[0]) != 'N');
                            }
                        } while (nombre_exemplaire_livre <= 0 && toupper(continuer[0]) == 'O');

                        /* ---- Étape 5 : Enregistrement ---- */
                        if (toupper(continuer[0]) == 'O') {
                            T_NLivre[taille_tableau_livre]= numero_livre;
                            strcpy(T_Titre[taille_tableau_livre], nom_livre);
                            T_Nbr_exp[taille_tableau_livre] = nombre_exemplaire_livre;
                            T_livre_supprime_entregistre[taille_tableau_livre] = 'E';
                            taille_tableau_livre += 1;
                            printf("Livre ajouté avec succès : %s (%lld) - %d exemplaire(s).\n",nom_livre, numero_livre, nombre_exemplaire_livre);
                        }           
                    }
                }
            }
        }
        /* ---- Étape 6 : Continuer ou quitter ---- */
        if (toupper(continuer[0]) == 'O') {
            do {
                printf("\nVoulez-vous ajouter un autre livre ? (O/N) : ");
                fgets(continuer, memoire_chaine, stdin);
                continuer[strcspn(continuer, "\n")] = '\0';
            } while (toupper(continuer[0]) != 'O' && toupper(continuer[0]) != 'N');
        }
    }
    //return taille_tableau_livre;
}
//Question 3 :
void supprimer_livre(int taille_tableau_livre, 
                     long long int T_NLivre[memoire], 
                     char T_Titre[memoire][memoire_chaine], 
                     long long int M_eprunts_livre[memoire][8], 
                     int T_Nbr_exp[memoire]) {

    char continuer[2] = "O"; // variable pour continuer ou quitter la suppression

    // boucle principale pour continuer à supprimer tant que l'utilisateur le souhaite
    while (toupper(continuer[0]) == 'O') {
        int choix_valide = 0;
        int choix = 0;
        char buffer[100];

        // demander à l'utilisateur comment il veut supprimer le livre
        while (choix_valide == 0) {
            printf("\nChoisir l'option de suppression :\n");
            printf("1. Par numero\n");
            printf("2. Par titre\n");
            printf("3. Retourner au menu\n");
            printf("choix = ");
            fgets(buffer, sizeof(buffer), stdin);
            if (sscanf(buffer, "%d", &choix) == 1 && choix >= 1 && choix <= 3) {
                choix_valide = 1; // choix correct
            } else {
                printf("Choix invalide. Entrez 1, 2 ou 3.\n");
            }
        }

        // si l'utilisateur veut retourner au menu, on quitte la boucle
        if (choix == 3) {
            strcpy(continuer, "N");
        } else {
            int indice = -1;           // indice du livre à supprimer
            int sortir_fonction = 0;   // indicateur pour sortir si l'utilisateur abandonne

            // --------- Suppression par numéro ---------
            if (choix == 1 && taille_tableau_livre > 0 && sortir_fonction == 0) {
                long long int numero_livre = 0;
                int valide_numero = 0;

                // tant que le numéro n'est pas valide et qu'on ne quitte pas
                while (valide_numero == 0 && sortir_fonction == 0) {
                    printf("Donner le numéro du livre (13 chiffres) : ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if (sscanf(buffer, "%lld", &numero_livre) == 1 &&
                        numero_livre >= 9780000000000LL &&
                        numero_livre <= 9789999999999LL) 
                    {
                        valide_numero = 1; // numéro valide
                        indice = existe_par_numero_livre(taille_tableau_livre, T_NLivre, numero_livre); // chercher l'indice
                    } else {
                        char choix_numero[2] = "";
                        int valide_choix = 0;
                        printf("Numéro invalide !\n");
                        // demander si l'utilisateur veut retaper ou retourner au menu
                        while (valide_choix == 0) {
                            printf("Voulez-vous retaper le numéro ? (O/N) : ");
                            fgets(choix_numero, sizeof(choix_numero), stdin);
                            choix_numero[strcspn(choix_numero, "\n")] = '\0';
                            if (toupper(choix_numero[0]) == 'O') {
                                valide_choix = 1; // retaper
                            } else if (toupper(choix_numero[0]) == 'N') {
                                valide_choix = 1; 
                                sortir_fonction = 1; // abandonner
                            } else {
                                printf("Réponse invalide !\n");
                            }
                        }
                    }
                }
            }

            // --------- Suppression par titre ---------
            if (choix == 2 && taille_tableau_livre > 0 && sortir_fonction == 0) {
                char titre_livre[memoire_chaine] = ""; // variable pour stocker le titre
                int valide_titre = 0;

                // tant que le titre n'est pas valide et qu'on ne sort pas
                while (valide_titre == 0 && sortir_fonction == 0) {
                    printf("Donner le titre du livre (non vide) : ");
                    fgets(titre_livre, memoire_chaine, stdin);
                    titre_livre[strcspn(titre_livre, "\n")] = '\0';

                    if (strlen(titre_livre) > 0) {
                        valide_titre = 1; // titre valide
                        indice = existe_par_nom_livre(taille_tableau_livre, T_Titre, titre_livre); // chercher l'indice
                    } else {
                        char choix_titre[2] = "";
                        int valide_choix = 0;
                        printf("Titre invalide !\n");
                        // demander si l'utilisateur veut retaper ou retourner au menu
                        while (valide_choix == 0) {
                            printf("Voulez-vous retaper le titre ? (O/N) : ");
                            fgets(choix_titre, sizeof(choix_titre), stdin);
                            choix_titre[strcspn(choix_titre, "\n")] = '\0';
                            if (toupper(choix_titre[0]) == 'O') {
                                valide_choix = 1; // retaper
                            } else if (toupper(choix_titre[0]) == 'N') {
                                valide_choix = 1; 
                                sortir_fonction = 1; // abandonner
                            } else {
                                printf("Réponse invalide !\n");
                            }
                        }
                    }
                }
            }

            // --------- Vérification et suppression ---------
            if (indice == -1 && sortir_fonction == 0) {
                printf("Livre inexistant.\n");
            } else if (indice != -1 && sortir_fonction == 0) {
                int i = 0;
                int emprunte = 0;

                // vérifier si le livre est actuellement emprunté
                while (i < taille_matrice_emprunts && emprunte == 0) {
                    if (M_eprunts_livre[i][1] == T_NLivre[indice] && T_livre_retour[i] != 'R') {
                        emprunte = 1; // le livre est emprunté
                    }
                    i = i + 1;
                }

                if (emprunte == 1) {
                    printf("Ce livre est emprunte → suppression impossible.\n");
                } else {
                    T_livre_supprime_entregistre[indice] = 'S'; // marquer comme supprimé
                    printf("Suppression reussie : %s (%lld)\n", T_Titre[indice], T_NLivre[indice]);
                }
            }

            // --------- Continuer ou quitter ---------
            if (sortir_fonction == 0) {
                int valide_continue = 0;
                while (valide_continue == 0) {
                    printf("\nVoulez-vous supprimer un autre livre ? (O/N) : ");
                    fgets(continuer, sizeof(continuer), stdin);
                    continuer[strcspn(continuer, "\n")] = '\0';
                    if (toupper(continuer[0]) == 'O' || toupper(continuer[0]) == 'N') {
                        valide_continue = 1;
                    } else {
                        printf("Réponse invalide !\n");
                    }
                }
            }
        }
    }
}
//Question 4 :
void modifier_nombre_exemplaires(int taille_tableau_livre, 
                                 long long int T_NLivre[memoire], 
                                 char T_Titre[memoire][memoire_chaine], 
                                 int T_Nbr_exp[memoire]) {
    char continuer[2] = "O";
    char buffer[100];

    while (toupper(continuer[0]) == 'O') {
        int indice = -1;
        int abandon = 0;

        printf("\nVoulez-vous modifier le livre par :\n1. Numéro\n2. Titre\nVotre choix = ");
        fgets(buffer, sizeof(buffer), stdin);
        int choix = atoi(buffer);

        if (choix == 1) { // par numéro
            long long int numero_livre;
            while (abandon == 0 && indice == -1) {
                printf("Entrez le numéro du livre (13 chiffres) : ");
                fgets(buffer, sizeof(buffer), stdin);
                if (sscanf(buffer, "%lld", &numero_livre) != 1 || numero_livre < 9780000000000LL || numero_livre > 9789999999999LL) {
                    printf("Numéro invalide !\n");
                    do {
                        printf("Voulez-vous retaper le numéro ? (O/N) : ");
                        fgets(buffer, sizeof(buffer), stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        if (toupper(buffer[0]) == 'N') abandon = 1;
                        else if (toupper(buffer[0]) != 'O') printf("Réponse invalide !\n");
                    } while (toupper(buffer[0]) != 'O' && toupper(buffer[0]) != 'N');
                } else {
                    indice = existe_par_numero_livre(taille_tableau_livre, T_NLivre, numero_livre);
                    if (indice == -1) {
                        printf("Livre non trouvé.\n");
                        do {
                            printf("Voulez-vous retaper le numéro ? (O/N) : ");
                            fgets(buffer, sizeof(buffer), stdin);
                            buffer[strcspn(buffer, "\n")] = '\0';
                            if (toupper(buffer[0]) == 'N') abandon = 1;
                            else if (toupper(buffer[0]) != 'O') printf("Réponse invalide !\n");
                        } while (toupper(buffer[0]) != 'O' && toupper(buffer[0]) != 'N');
                        if (abandon == 0) indice = -1; // pour retaper
                    }
                }
            }

        } else if (choix == 2) { // par titre
            char nom_livre[memoire_chaine];
            while (abandon == 0 && indice == -1) {
                printf("Entrez le titre du livre : ");
                fgets(nom_livre, memoire_chaine, stdin);
                nom_livre[strcspn(nom_livre, "\n")] = '\0';

                if (strlen(nom_livre) == 0) {
                    printf("Titre vide !\n");
                } else {
                    indice = existe_par_nom_livre(taille_tableau_livre, T_Titre, nom_livre);
                    if (indice == -1) printf("Livre non trouvé.\n");
                }

                if (indice == -1) {
                    do {
                        printf("Voulez-vous retaper le titre ? (O/N) : ");
                        fgets(buffer, sizeof(buffer), stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        if (toupper(buffer[0]) == 'N') abandon = 1;
                        else if (toupper(buffer[0]) != 'O') printf("Réponse invalide !\n");
                    } while (toupper(buffer[0]) != 'O' && toupper(buffer[0]) != 'N');
                }
            }

        } else {
            printf("Choix invalide.\n");
            abandon = 1;
        }

        if (indice != -1 && abandon == 0) {
            int nouveau_nombre;
            do {
                printf("Nombre d'exemplaires actuel : %d\n", T_Nbr_exp[indice]);
                printf("Entrez le nouveau nombre d'exemplaires : ");
                nouveau_nombre = lire_entier();
                if (nouveau_nombre < 0) printf("Le nombre d'exemplaires doit être >= 0.\n");
            } while (nouveau_nombre < 0);

            T_Nbr_exp[indice] = nouveau_nombre;
            printf("Modification réussie. Nouveau nombre d'exemplaires : %d\n", T_Nbr_exp[indice]);
        }

        // Continuer ?
        printf("\nVoulez-vous modifier un autre livre ? (O/N) : ");
        fgets(continuer, sizeof(continuer), stdin);
        continuer[strcspn(continuer, "\n")] = '\0';
    }
}
// Question 5 : Rechercher un livre par son titre ou numéro
void rechercher_livre(int taille_tableau_livre,
                      long long int T_NLivre[memoire],
                      char T_Titre[memoire][memoire_chaine],
                      int T_Nbr_exp[memoire],
                      char T_livre_supprime_entregistre[memoire]) {
    char continuer[2] = "O";
    char buffer[100];

    while (toupper(continuer[0]) == 'O') {
        int indice = -1;
        int abandon = 0;

        int choix = 0;
        // Boucle pour choix valide
        do {
            printf("\nVoulez-vous rechercher le livre par :\n");
            printf("1. Numéro\n2. Titre\n3. Quitter\nVotre choix = ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (sscanf(buffer, "%d", &choix) != 1 || (choix < 1 || choix > 3)) {
                printf("Choix invalide ! Veuillez entrer 1, 2 ou 3.\n");
                choix = 0;
            }
        } while (choix != 1 && choix != 2 && choix != 3);

        if (choix == 3) { // Quitter la fonction
            
            continuer[0] = 'N';
            //break;
        }

        // Recherche par numéro
        if (choix == 1) {
            long long int numero_livre = -1;
            while (abandon == 0 && indice == -1) {
                printf("Entrez le numéro du livre (13 chiffres) : ");
                fgets(buffer, sizeof(buffer), stdin);
                if (sscanf(buffer, "%lld", &numero_livre) != 1 ||
                    numero_livre < 9780000000000LL || numero_livre > 9789999999999LL) {
                    printf("Numéro invalide !\n");
                    do {
                        printf("Voulez-vous retaper le numéro ? (O/N) : ");
                        fgets(buffer, sizeof(buffer), stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        if (toupper(buffer[0]) == 'N') abandon = 1;
                    } while (toupper(buffer[0]) != 'O' && toupper(buffer[0]) != 'N');
                } else {
                    indice = existe_par_numero_livre(taille_tableau_livre, T_NLivre, numero_livre);
                    if (indice == -1) printf("Livre non trouvé.\n");
                }
            }
        }

        // Recherche par titre
        else if (choix == 2) {
            char nom_livre[memoire_chaine];
            while (abandon == 0 && indice == -1) {
                printf("Entrez le titre du livre : ");
                fgets(nom_livre, memoire_chaine, stdin);
                nom_livre[strcspn(nom_livre, "\n")] = '\0';

                if (strlen(nom_livre) == 0) printf("Titre vide !\n");
                else {
                    indice = existe_par_nom_livre(taille_tableau_livre, T_Titre, nom_livre);
                    if (indice == -1) printf("Livre non trouvé.\n");
                }

                if (indice == -1) {
                    do {
                        printf("Voulez-vous retaper le titre ? (O/N) : ");
                        fgets(buffer, sizeof(buffer), stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        if (toupper(buffer[0]) == 'N') abandon = 1;
                    } while (toupper(buffer[0]) != 'O' && toupper(buffer[0]) != 'N');
                }
            }
        }

        // Affichage dans un tableau si livre trouvé
        if (indice != -1 && abandon == 0) {
            char etat_texte[12];
            if (T_livre_supprime_entregistre[indice] == 'E') strcpy(etat_texte, "Enregistré");
            else if (T_livre_supprime_entregistre[indice] == 'S') strcpy(etat_texte, "Supprimé");
            else strcpy(etat_texte, "Inconnu");

            // Table header
            printf("\n┌───────────────┬──────────────────────────────┬──────────────┬────────────┐\n");
            printf("│  N°Livre      │ Titre                        │ Nbr Exempl   │ Etat       │\n");
            printf("├───────────────┼──────────────────────────────┼──────────────┼────────────┤\n");

            // Table row
            printf("│ %08lld │ %-28s │ %-12d │ %-11s │\n",
                   T_NLivre[indice], T_Titre[indice], T_Nbr_exp[indice], etat_texte);

            // Table footer
            printf("└───────────────┴──────────────────────────────┴──────────────┴────────────┘\n");
        }

        // Continuer ?
        if (abandon == 0) {
            printf("\nVoulez-vous rechercher un autre livre ? (O/N) : ");
            fgets(continuer, sizeof(continuer), stdin);
            continuer[strcspn(continuer, "\n")] = '\0';
        } else {
            continuer[2] = 'N';
            //break;                                                                                                                                                                                                                                                       break; // revenir au menu
        }
    }}

//Question 6 :
void afficher_livres_disponibles(
        int taille_tableau_livre,
        long long int T_NLivre[memoire],
        char T_Titre[memoire][memoire_chaine],
        int T_Nbr_exp[memoire],
        long long int M_eprunts_livre[memoire][8],
        char T_livre_supprime_entregistre[memoire]){

    char tampon[11];
    calculer_date_courante(tampon);

    int emprunts_actifs[memoire] = {0};

    // Calculer les emprunts actifs (non retournés)
    for (int i = 0; i < memoire; i++) {
        long long int num = M_eprunts_livre[i][1];

        if (num != 0) {
            int jr_ret = M_eprunts_livre[i][5];
            int ms_ret = M_eprunts_livre[i][6];
            int an_ret = M_eprunts_livre[i][7];

            // Si date de retour > date courante → encore emprunté
            if (date_superieure(jr_ret, ms_ret, an_ret,
                                jr_courant, ms_courant, an_courant)) {
                for (int j = 0; j < taille_tableau_livre; j++) {
                    if (T_NLivre[j] == num) {
                        emprunts_actifs[j]++;
                    }
                }
            }
        }
    }

    // AFFICHAGE
    printf("\nLivres disponibles au : %s\n", tampon);
    printf("┌───────────────┬──────────────────────────────┬──────────────┐\n");
    printf("│  N°Livre      │ Titre                        │ Disponibles  │\n");
    printf("├───────────────┼──────────────────────────────┼──────────────┤\n");

    int aucun = 1;

    for (int i = 0; i < taille_tableau_livre; i++) {

        if (T_livre_supprime_entregistre[i] == 'E') {  // Livre non supprimé
            int en_emprunt = emprunts_actifs[i];
            int dispo = T_Nbr_exp[i] - en_emprunt;

            if (dispo > 0) {  // Disponible à l'emprunt
                printf("│ %lld │ %-28s │ %-12d │\n",
                       T_NLivre[i], T_Titre[i], dispo);
                aucun = 0;
            }
        }
    }

    if (aucun == 1) {
        printf("│ Aucun livre disponible actuellement              │\n");
    }

    printf("└───────────────┴──────────────────────────────┴──────────────┘\n");}

//----------------------------------------------------------//

//----------------------------------------------------------//
/*-------------PART2-------------*/
void afficher_toute_la_matrice(int taille_matrice_emprunts,long long int M_eprunts_livre[memoire][8]) {
    printf("\n┌────────────┬──────────────────────────────┬───────────────┬───────────────┐\n");
    printf("│  CIN       │ Numero livre                 │ Date emprunt  │ Date Retour   │\n");
    printf("├────────────┼──────────────────────────────┼───────────────┼───────────────┤\n");

    for (int i = 0; i < taille_matrice_emprunts; i++) {

        // Affichage des dates au format jj/mm/aaaa
        char date_emprunt[11], date_retour[11];
        snprintf(date_emprunt, sizeof(date_emprunt), "%lld/%lld/%lld",
                 M_eprunts_livre[i][2], M_eprunts_livre[i][3], M_eprunts_livre[i][4]);
        snprintf(date_retour, sizeof(date_retour), "%lld/%lld/%lld",
                 M_eprunts_livre[i][5], M_eprunts_livre[i][6], M_eprunts_livre[i][7]);

        // Ligne de données
        //printf("│ %-10lld │ %-28lld │ %-13s │ %-13s │\n",
        printf("│ %08lld   │ %-28lld │ %-13s │ %-13s │\n",
            M_eprunts_livre[i][0],
               M_eprunts_livre[i][1],
               date_emprunt,
               date_retour);

        // Ligne de séparation après chaque ligne sauf la dernière
        if (i != taille_matrice_emprunts - 1) {
            printf("├────────────┼──────────────────────────────┼───────────────┼───────────────┤\n");
        }
    }
    printf("└────────────┴──────────────────────────────┴───────────────┴───────────────┘");}

//Question 1 :
int ajouter_emprunt_effectif(
    long long int T_NLivre[memoire],
    char T_Titre[memoire][memoire_chaine],
    int T_Nbr_exp[memoire],
    char T_livre_supprime_entregistre[memoire],
    long long int M_eprunts_livre[memoire][8],
    char T_livre_retour[memoire],
    int taille_tableau_livre,
    int taille_matrice_emprunts) {

    char buffer[100];
    char reponse[10];
    long long int cin_adherent = 0;
    long long int numero_livre = 0;
    int indice_livre = -1;
    char continuer = 'O';

    while (continuer == 'O' && taille_matrice_emprunts < memoire) {

        // ---------------- CIN ----------------
        int cin_valide = 0;
        char cin_str[10];
        while (cin_valide == 0) {
            printf("Entrez le CIN de l'adhérent (8 chiffres) : ");
            fgets(cin_str, sizeof(cin_str), stdin);
            cin_str[strcspn(cin_str, "\n")] = '\0';

            int est_valide = (strlen(cin_str) == 8);
            for (int i = 0; i < 8 && est_valide; i++)
                if (!isdigit(cin_str[i])) est_valide = 0;

            if (est_valide) {
                sscanf(cin_str, "%lld", &cin_adherent);
                cin_valide = 1;
            } else {
                int valide = 0;
                while (valide == 0) {
                    printf("CIN invalide. Voulez-vous retaper ? (O/N) : ");
                    fgets(reponse, sizeof(reponse), stdin);
                    reponse[strcspn(reponse, "\n")] = '\0';
                    if (strlen(reponse) > 0) {
                        char c = toupper(reponse[0]);
                        if (c == 'O') valide = 1;
                        else if (c == 'N') valide = 2;
                        else printf("Réponse invalide !\n");
                    }
                }
                if (valide == 2) { // Exit the loop and go to next iteration
                    cin_valide = 1;
                }
            }
        }

        // ---------------- Vérifier max 7 emprunts ----------------
        int total_emprunts = 0;
        for (int i = 0; i < taille_matrice_emprunts; i++)
            if (M_eprunts_livre[i][0] == cin_adherent && T_livre_retour[i] != 'R') total_emprunts++;
        if (total_emprunts >= 7) {
            printf("Cet adhérent a déjà emprunté 7 livres.\n");
            continuer = 'N'; // Stop adding more emprunts
        }

        // ---------------- NUMERO LIVRE ----------------
        int livre_valide = 0;
        char livre_str[20];
        while (livre_valide == 0) {
            printf("Entrez le numéro du livre à emprunter (13 chiffres) : ");
            fgets(livre_str, sizeof(livre_str), stdin);
            livre_str[strcspn(livre_str, "\n")] = '\0';

            int est_valide = (strlen(livre_str) == 13);
            for (int i = 0; i < 13 && est_valide; i++)
                if (!isdigit(livre_str[i])) est_valide = 0;

            if (!est_valide) {
                int valide = 0;
                while (valide == 0) {
                    printf("Numéro invalide. Voulez-vous retaper ? (O/N) : ");
                    fgets(reponse, sizeof(reponse), stdin);
                    reponse[strcspn(reponse, "\n")] = '\0';
                    if (strlen(reponse) > 0) {
                        char c = toupper(reponse[0]);
                        if (c == 'O') valide = 1;
                        else if (c == 'N') valide = 2;
                        else printf("Réponse invalide !\n");
                    }
                }
                if (valide == 2) { // Skip current iteration
                    livre_valide = 1;
                }
            }

            sscanf(livre_str, "%lld", &numero_livre);
            indice_livre = existe_par_numero_livre(taille_tableau_livre, T_NLivre, numero_livre);

            // Check if the book is not deleted
            if (indice_livre == -1 || T_livre_supprime_entregistre[indice_livre] == 'S') {
                printf("Livre inexistant ou supprimé.\n");
            } else {
                int emprunts_actifs = 0;
                for (int i = 0; i < taille_matrice_emprunts; i++)
                    if (M_eprunts_livre[i][1] == numero_livre && T_livre_retour[i] != 'R') emprunts_actifs++;
                if ((T_Nbr_exp[indice_livre] - emprunts_actifs) <= 0) {
                    printf("Aucun exemplaire disponible.\n");
                } else {
                    livre_valide = 1;
                }
            }
        }

        // ---------------- AJOUT EMPRUNT ----------------
        if (livre_valide == 1) {
            char tampon[11];
            calculer_date_courante(tampon);
            int jr_debut = jr_courant, ms_debut = ms_courant, an_debut = an_courant;
            int jr_retour = jr_debut + 30, ms_retour = ms_debut, an_retour = an_debut;
            int jours_par_mois[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
            if (est_bissextile(an_retour)) jours_par_mois[1] = 29;
            while (jr_retour > jours_par_mois[ms_retour-1]) {
                jr_retour -= jours_par_mois[ms_retour-1];
                ms_retour++;
                if (ms_retour > 12) { ms_retour = 1; an_retour++; }
                if (est_bissextile(an_retour)) jours_par_mois[1] = 29; else jours_par_mois[1] = 28;
            }

            int i_emp = taille_matrice_emprunts;
            M_eprunts_livre[i_emp][0] = cin_adherent;
            M_eprunts_livre[i_emp][1] = numero_livre;
            M_eprunts_livre[i_emp][2] = jr_debut;
            M_eprunts_livre[i_emp][3] = ms_debut;
            M_eprunts_livre[i_emp][4] = an_debut;
            M_eprunts_livre[i_emp][5] = jr_retour;
            M_eprunts_livre[i_emp][6] = ms_retour;
            M_eprunts_livre[i_emp][7] = an_retour;
            T_livre_retour[i_emp] = 'N';
            T_livre_supprime_entregistre[indice_livre] = 'N'; // Mark the book as not deleted
            taille_matrice_emprunts++;

            printf("Emprunt ajouté : %s (%lld) pour l'adhérent %s. Retour prévu le %02d/%02d/%04d\n",
                   T_Titre[indice_livre], numero_livre, cin_str, jr_retour, ms_retour, an_retour);
        }

        // ---------------- CONTINUER ? ----------------
        int valide_continue = 0;
        while (valide_continue == 0) {
            printf("Voulez-vous ajouter un autre emprunt ? (O/N) : ");
            fgets(reponse, sizeof(reponse), stdin);
            reponse[strcspn(reponse, "\n")] = '\0';
            if (strlen(reponse) > 0 && (toupper(reponse[0]) == 'O' || toupper(reponse[0]) == 'N')) {
                continuer = toupper(reponse[0]);
                valide_continue = 1;
            }
        }
    }

    return taille_matrice_emprunts;  /* <- retourne maintenant la taille actuelle */}

//Question 2 :
void consulter_emprunts_adherent_tout_en_un(long long int M_eprunts_livre[memoire][8],char T_livre_retour[memoire],int taille_matrice_emprunts) {
                                             
                                             
    char buffer[100];
    char CIN_str[10]; // 8 chiffres + '\0'
    int valide = 0;

    // Saisie et validation du CIN
    while (valide == 0) {
        printf("Entrez le CIN de l'adhérent (8 chiffres) : ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0'; // retirer \n

            if (strlen(buffer) == 8) {
                int tous_chiffres = 1;
                for (int i = 0; i < 8; i++) {
                    if (!isdigit(buffer[i])) {
                        tous_chiffres = 0;
                    }
                }
                if (tous_chiffres == 1) {
                    strcpy(CIN_str, buffer);
                    valide = 1; // CIN valide
                } else {
                    printf("CIN invalide. Veuillez entrer uniquement des chiffres.\n");
                }
            } else {
                printf("CIN invalide. Il doit contenir exactement 8 chiffres.\n");
            }
        }
    }

    long long int CIN_adherent = atoll(CIN_str); // conversion pour comparaison

    // Affichage des emprunts
    int trouve = 0;
    printf("\nEmprunts de l'adhérent %s :\n", CIN_str);

    // Tableau : on n'affiche plus le CIN dans chaque ligne
    printf("┌──────────────────────────────┬───────────────┬───────────────┐\n");
    printf("│ Numero livre                 │ Date emprunt  │ Date Retour   │\n");
    printf("├──────────────────────────────┼───────────────┼───────────────┤\n");

    int i = 0;
    while (i < taille_matrice_emprunts) {
        if (M_eprunts_livre[i][0] == CIN_adherent) {
            char date_emprunt[11], date_retour[11];
            snprintf(date_emprunt, sizeof(date_emprunt), "%02lld/%02lld/%04lld",
                     M_eprunts_livre[i][2], M_eprunts_livre[i][3], M_eprunts_livre[i][4]);
            snprintf(date_retour, sizeof(date_retour), "%02lld/%02lld/%04lld",
                     M_eprunts_livre[i][5], M_eprunts_livre[i][6], M_eprunts_livre[i][7]);

            printf("│ %-28lld │ %-13s │ %-13s │\n",
                   M_eprunts_livre[i][1], date_emprunt, date_retour);
            trouve = 1;
        }
        i = i + 1;
    }

    if (trouve == 0) {
        printf("│      Aucun emprunt trouvé pour cet adhérent.                    │\n");
    }

    printf("└──────────────────────────────┴───────────────┴───────────────┘\n");}

//Question 3 : 
void enregistrer_retour_livre(
    long long int M_eprunts_livre[memoire][8],
    char T_livre_retour[memoire],
    int taille_matrice_emprunts) {

    char buffer[100];
    char reponse[10];
    long long int cin_adherent;
    long long int numero_livre;
    int emprunt_trouve;

    char continuer = 'O';
    while (toupper(continuer) == 'O' && taille_matrice_emprunts > 0) {

        // ---------------- CIN ----------------
        int cin_valide = 0;
        char cin_str[10];
        while (cin_valide == 0) {
            printf("Entrez le CIN de l'adhérent (8 chiffres) : ");
            fgets(cin_str, sizeof(cin_str), stdin);
            cin_str[strcspn(cin_str, "\n")] = '\0';

            int est_valide = 1;
            if (strlen(cin_str) != 8) est_valide = 0;
            int i;
            for (i = 0; i < 8 && est_valide != 0; i++)
                if (!isdigit(cin_str[i])) est_valide = 0;

            if (est_valide != 0) {
                sscanf(cin_str, "%lld", &cin_adherent);
                cin_valide = 1;
            } else {
                int valide = 0;
                while (valide == 0) {
                    printf("CIN invalide. Voulez-vous retaper ? (O/N) : ");
                    fgets(reponse, sizeof(reponse), stdin);
                    reponse[strcspn(reponse, "\n")] = '\0';
                    if (strlen(reponse) > 0) {
                        char c = toupper(reponse[0]);
                        if (c == 'O') { valide = 1; } // retaper
                        else if (c == 'N') continuer = 'N';//return;     // quitter
                        else printf("Réponse invalide !\n");
                    } else printf("Réponse invalide !\n");
                }
            }
        }

        // ---------------- NUMERO LIVRE ----------------
        int livre_valide = 0;
        char livre_str[20];
        while (livre_valide == 0) {
            printf("Entrez le numéro du livre à retourner (13 chiffres) : ");
            fgets(livre_str, sizeof(livre_str), stdin);
            livre_str[strcspn(livre_str, "\n")] = '\0';

            int est_valide = 1;
            if (strlen(livre_str) != 13) est_valide = 0;
            int j;
            for (j = 0; j < 13 && est_valide != 0; j++)
                if (!isdigit(livre_str[j])) est_valide = 0;

            if (est_valide != 0) {
                sscanf(livre_str, "%lld", &numero_livre);
                livre_valide = 1;
            } else {
                int valide = 0;
                while (valide == 0) {
                    printf("Numéro invalide. Voulez-vous retaper ? (O/N) : ");
                    fgets(reponse, sizeof(reponse), stdin);
                    reponse[strcspn(reponse, "\n")] = '\0';
                    if (strlen(reponse) > 0) {
                        char c = toupper(reponse[0]);
                        if (c == 'O') { valide = 1; } // retaper
                        else if (c == 'N') return;     // quitter
                        else printf("Réponse invalide !\n");
                    } else printf("Réponse invalide !\n");
                }
            }
        }

        // ---------------- TROUVER L'EMPRUNT ----------------
        emprunt_trouve = 0;
        int i;
        for (i = 0; i < taille_matrice_emprunts; i++) {
            if (M_eprunts_livre[i][0] == cin_adherent &&
                M_eprunts_livre[i][1] == numero_livre &&
                T_livre_retour[i] != 'R') {

                T_livre_retour[i] = 'R'; // enregistrer le retour
                printf("Retour enregistré pour le livre %lld de l'adhérent %08lld.\n", numero_livre, cin_adherent);
                emprunt_trouve = 1;
                //break;
            }
        }

        if (emprunt_trouve == 0) {
            printf("Aucun emprunt non retourné trouvé pour ce CIN et ce livre.\n");
        }

        // ---------------- CONTINUER ? ----------------
        int valide_continue = 0;
        while (valide_continue == 0) {
            printf("Voulez-vous enregistrer un autre retour ? (O/N) : ");
            fgets(reponse, sizeof(reponse), stdin);
            reponse[strcspn(reponse, "\n")] = '\0';
            if (strlen(reponse) > 0 && (toupper(reponse[0]) == 'O' || toupper(reponse[0]) == 'N')) {
                continuer = toupper(reponse[0]);
                valide_continue = 1;
            }
        }
    }}

void afficher_toute_la_matrice_etat(
    int taille_matrice_emprunts,
    long long int M_eprunts_livre[memoire][8],
    char T_livre_retour[memoire],
    long long int T_NLivre[memoire],
    char T_Titre[memoire][memoire_chaine]) {

    printf("\n┌────────────┬──────────────────────────────┬───────────────┬───────────────┬──────────────┐\n");
    printf("│  CIN       │ Numero livre                 │ Date emprunt  │ Date Retour   │ Etat         │\n");
    printf("├────────────┼──────────────────────────────┼───────────────┼───────────────┼──────────────┤\n");

    for (int i = 0; i < taille_matrice_emprunts; i++) {
        char date_emprunt[11], date_retour[11];
        char etat[20];   // safe size for "Non retourné"

        // Format date emprunt
        snprintf(date_emprunt, sizeof(date_emprunt), "%02lld/%02lld/%04lld",
                 M_eprunts_livre[i][2], M_eprunts_livre[i][3], M_eprunts_livre[i][4]);

        // Format date retour safely: if 0, print "-"
        if (M_eprunts_livre[i][5] == 0 && M_eprunts_livre[i][6] == 0 && M_eprunts_livre[i][7] == 0)
            strcpy(date_retour, "-");
        else
            snprintf(date_retour, sizeof(date_retour), "%02lld/%02lld/%04lld",
                     M_eprunts_livre[i][5], M_eprunts_livre[i][6], M_eprunts_livre[i][7]);

        // Etat
        if (T_livre_retour[i] == 'R') strcpy(etat, "Retourné");
        else strcpy(etat, "Non retourné");

        // Chercher le titre du livre
        int indice_livre = existe_par_numero_livre(taille_tableau_livre, T_NLivre, M_eprunts_livre[i][1]);
        char titre[100] = "";
        if (indice_livre != -1) strcpy(titre, T_Titre[indice_livre]);

        printf("│ %08lld   │ %-28s │ %-13s │ %-13s │ %-13s │\n",
               M_eprunts_livre[i][0],
               titre,
               date_emprunt,
               date_retour,
               etat);

        if (i != taille_matrice_emprunts - 1)
            printf("├────────────┼──────────────────────────────┼───────────────┼───────────────┼──────────────┤\n");
    }

    printf("└────────────┴──────────────────────────────┴───────────────┴───────────────┴──────────────┘\n");}

//Question 4 :
void afficher_emprunts_en_cours(
    int taille_matrice_emprunts,
    long long int M_eprunts_livre[memoire][8],
    char T_livre_retour[memoire],
    long long int T_NLivre[memoire],
    char T_Titre[memoire][memoire_chaine]) {

    char tampon[11];
    calculer_date_courante(tampon);

    printf("\nEmprunts en cours au %s :\n", tampon);
    printf("┌────────────┬──────────────────────────────┬───────────────┬───────────────┬──────────────┐\n");
    printf("│  CIN       │ Titre                        │ Date emprunt  │ Date retour   │ Etat         │\n");
    printf("├────────────┼──────────────────────────────┼───────────────┼───────────────┼──────────────┤\n");

    int compteur = 0;

    for (int i = 0; i < taille_matrice_emprunts; i++) {
        if (T_livre_retour[i] != 'R') {  // seulement les emprunts non retournés
            char date_emprunt[11], date_retour[11];
            snprintf(date_emprunt, sizeof(date_emprunt), "%02lld/%02lld/%04lld",
                     M_eprunts_livre[i][2], M_eprunts_livre[i][3], M_eprunts_livre[i][4]);
            snprintf(date_retour, sizeof(date_retour), "%02lld/%02lld/%04lld",
                     M_eprunts_livre[i][5], M_eprunts_livre[i][6], M_eprunts_livre[i][7]);

            int indice_livre = existe_par_numero_livre(taille_tableau_livre, T_NLivre, M_eprunts_livre[i][1]);
            char titre[100] = "";
            if (indice_livre != -1) strcpy(titre, T_Titre[indice_livre]);

            // Vérifier si le livre est en retard
            char etat[20];
            if (date_superieure(jr_courant, ms_courant, an_courant,
                                M_eprunts_livre[i][5], M_eprunts_livre[i][6], M_eprunts_livre[i][7])) {
                strcpy(etat, "En retard");
            } else {
                strcpy(etat, "En cours");
            }

            printf("│ %08lld   │ %-28s │ %-13s │ %-13s │ %-12s │\n",
                   M_eprunts_livre[i][0],
                   titre,
                   date_emprunt,
                   date_retour,
                   etat);
            compteur++;
        }
    }

    if (compteur == 0) {
        printf("│ Aucun emprunt en cours                                    │\n");
    }

    printf("└────────────┴──────────────────────────────┴───────────────┴───────────────┴──────────────┘\n");}


    //Question 5 : 
void afficher_livres_en_retard(
    int taille_matrice_emprunts,
    long long int M_eprunts_livre[memoire][8],
    char T_livre_retour[memoire],
    long long int T_NLivre[memoire],
    char T_Titre[memoire][memoire_chaine]) {

    char tampon[11];
    calculer_date_courante(tampon);  // date courante
    printf("\nLivres en retard au %s :\n", tampon);

    printf("┌────────────┬──────────────────────────────┬───────────────┬───────────────┬──────────────┐\n");
    printf("│  CIN       │ Titre                        │ Date emprunt  │ Date retour   │ Etat         │\n");
    printf("├────────────┼──────────────────────────────┼───────────────┼───────────────┼──────────────┤\n");

    int compteur = 0;

    for (int i = 0; i < taille_matrice_emprunts; i++) {
        if (T_livre_retour[i] != 'R') {  // seulement non retourné

            // vérifier si la date de retour est dépassée
            if (date_superieure(jr_courant, ms_courant, an_courant,
                                M_eprunts_livre[i][5], M_eprunts_livre[i][6], M_eprunts_livre[i][7])) {

                char date_emprunt[11], date_retour[11];
                snprintf(date_emprunt, sizeof(date_emprunt), "%02lld/%02lld/%04lld",
                         M_eprunts_livre[i][2], M_eprunts_livre[i][3], M_eprunts_livre[i][4]);
                snprintf(date_retour, sizeof(date_retour), "%02lld/%02lld/%04lld",
                         M_eprunts_livre[i][5], M_eprunts_livre[i][6], M_eprunts_livre[i][7]);

                int indice_livre = -1;
                int j = 0;
                while (j < taille_tableau_livre && indice_livre == -1) {
                    if (T_NLivre[j] == M_eprunts_livre[i][1]) {
                        indice_livre = j; // trouvé, juste changer la variable
                    }
                    j = j + 1;
                }

                char titre[100] = "";
                if (indice_livre != -1) strcpy(titre, T_Titre[indice_livre]);

                printf("│ %08lld   │ %-28s │ %-13s │ %-13s │ %-12s │\n",
                       M_eprunts_livre[i][0],
                       titre,
                       date_emprunt,
                       date_retour,
                       "En retard");
                compteur++;
            }
        }
    }

    if (compteur == 0) {
        printf("│ Aucun livre en retard actuellement                              │\n");
    }

    printf("└────────────┴──────────────────────────────┴───────────────┴───────────────┴──────────────┘\n");}

//Question 6 :
void afficher_emprunts_par_date_retour(
    int taille_matrice_emprunts,
    long long int M_eprunts_livre[memoire][8],
    char T_livre_retour[memoire],
    long long int T_NLivre[memoire],
    char T_Titre[memoire][memoire_chaine]) {

    char buffer[20], reponse[10];
    int jr_saisie, ms_saisie, an_saisie;
    int valide_date = 0;  // 0 = faux, 1 = vrai

    while (valide_date == 0) {
        printf("Entrez la date de retour prévue (jj/mm/aaaa) : ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (sscanf(buffer, "%d/%d/%d", &jr_saisie, &ms_saisie, &an_saisie) == 3) {
            if (date_valide(jr_saisie, ms_saisie, an_saisie) == 1) {
                valide_date = 1;  // date correcte
            } else {
                printf("Date invalide !\n");
            }
        } else {
            printf("Format invalide ! Utilisez jj/mm/aaaa.\n");
        }

        if (valide_date == 0) {
            int reponse_valide = 0;
            while (reponse_valide == 0) {
                printf("Voulez-vous retaper la date ? (O/N) : ");
                fgets(reponse, sizeof(reponse), stdin);
                reponse[strcspn(reponse, "\n")] = '\0';

                if (toupper(reponse[0]) == 'O') {
                    reponse_valide = 1;  // retaper
                } else if (toupper(reponse[0]) == 'N') {
                    return;  // quitter la fonction
                } else {
                    printf("Réponse invalide !\n");
                }
            }
        }
    }

    // Affichage des emprunts correspondant à la date
    printf("\nEmprunts avec date de retour prévue le %02d/%02d/%04d :\n",
           jr_saisie, ms_saisie, an_saisie);
    printf("┌────────────┬──────────────────────────────┬───────────────┬───────────────┬──────────────┐\n");
    printf("│  CIN       │ Titre                        │ Date emprunt  │ Date retour   │ Etat         │\n");
    printf("├────────────┼──────────────────────────────┼───────────────┼───────────────┼──────────────┤\n");

    int compteur = 0;

    int i = 0;
    while (i < taille_matrice_emprunts) {
        if (M_eprunts_livre[i][5] == jr_saisie &&
            M_eprunts_livre[i][6] == ms_saisie &&
            M_eprunts_livre[i][7] == an_saisie) {

            char date_emprunt[11], date_retour[11];
            snprintf(date_emprunt, sizeof(date_emprunt), "%02lld/%02lld/%04lld",
                     M_eprunts_livre[i][2], M_eprunts_livre[i][3], M_eprunts_livre[i][4]);
            snprintf(date_retour, sizeof(date_retour), "%02lld/%02lld/%04lld",
                     M_eprunts_livre[i][5], M_eprunts_livre[i][6], M_eprunts_livre[i][7]);

            int indice_livre = -1;
            int j = 0;
            while (j < taille_tableau_livre && indice_livre == -1) {
                if (T_NLivre[j] == M_eprunts_livre[i][1]) {
                    indice_livre = j;
                }
                j = j + 1;
            }

            char titre[100] = "";
            if (indice_livre != -1) {
                strcpy(titre, T_Titre[indice_livre]);
            }

            char etat[20];
            if (T_livre_retour[i] == 'R') strcpy(etat, "Retourné");
            else strcpy(etat, "Non retourné");

            printf("│ %08lld   │ %-28s │ %-13s │ %-13s │ %-13s │\n",
                   M_eprunts_livre[i][0],
                   titre,
                   date_emprunt,
                   date_retour,
                   etat);
            compteur = compteur + 1;
        }
        i = i + 1;
    }

    if (compteur == 0) {
        printf("│ Aucun emprunt trouvé pour cette date                              │\n");
    }

    printf("└────────────┴──────────────────────────────┴───────────────┴───────────────┴──────────────┘\n");}

//Question 7 : 
void afficher_matrice() {
    // Print header
    printf("\nMatrice des emprunts après modification:\n");
    printf("+------------+--------------------+-------------------+-------------------+------------+---------------------+\n");
    printf("| %-10s | %-18s | %-17s | %-17s | %-10s | %-19s |\n", 
           "CIN", "Numero Livre", "Date Emprunt", "Date Retour", "Etat Livre", "Etat Suppression");
    printf("+------------+--------------------+-------------------+-------------------+------------+---------------------+\n");

    // Iterate through the matrix and print the data
    for (int i = 0; i < memoire; i++) {
        if (M_eprunts_livre[i][0] != 0) {  // Only print valid entries (non-zero CIN)
            // Print each row of the matrix with proper formatting
            printf("| %-10lld | %-18lld | %-02d/%02d/%04d        | %-02d/%02d/%04d        | %-9s | %-19c |\n", 
                M_eprunts_livre[i][0],  // CIN
                M_eprunts_livre[i][1],  // Numero Livre
                M_eprunts_livre[i][2],  // Jour Emprunt
                M_eprunts_livre[i][3],  // Mois Emprunt
                M_eprunts_livre[i][4],  // Annee Emprunt
                M_eprunts_livre[i][5],  // Jour Retour
                M_eprunts_livre[i][6],  // Mois Retour
                M_eprunts_livre[i][7],  // Annee Retour
                (T_emprunt_supprime[i] == 'S' ? "Supprimé  " : "En cours  "),  // Etat Livre
                T_emprunt_supprime[i]   // Etat Suppression
            );
        }
    }
    printf("+------------+--------------------+-------------------+-------------------+------------+---------------------+\n");}

void supprimer_emprunt() {
    long long int cin;
    int jour_debut, mois_debut, annee_debut;
    int jour_fin, mois_fin, annee_fin;
    char reponse;
    int cin_valide = 0;   // 0 means invalid CIN, 1 means valid CIN
    int date_valide = 0;  // 0 means invalid date, 1 means valid date

    // Ask for CIN until valid
    while (cin_valide == 0) {
        // Ask for CIN
        printf("Entrez le CIN de l'adhérent (8 chiffres): ");
        if (scanf("%lld", &cin) != 1 || !((cin >= 100000 && cin <= 99999999))) {
            // If CIN is invalid, ask if the user wants to retype or leave
            printf("CIN invalide. Il doit contenir exactement 8 chiffres et être compris entre 10000000 et 99999999.\n");
            printf("Voulez-vous réessayer ? (O pour oui / N pour non): ");
            scanf(" %c", &reponse);  // " %c" to consume any previous newline character
            if (reponse == 'N' || reponse == 'n') {
                cin_valide = 1;  // Exit the loop by marking cin_valide as 1
            }
        } else {
            cin_valide = 1;  // Exit the loop if CIN is valid
        }
    }

    // Ask for date range until valid
    while (date_valide == 0) {
        // Ask for date range (start and end dates) in dd/mm/yyyy format
        printf("Entrez la date de début (jj/mm/aaaa): ");
        if (scanf("%d/%d/%d", &jour_debut, &mois_debut, &annee_debut) != 3) {
            // If date format is incorrect, ask if the user wants to retype or leave
            printf("Format de date invalide. Assurez-vous d'utiliser le format jj/mm/aaaa.\n");
            printf("Voulez-vous réessayer ? (O pour oui / N pour non): ");
            scanf(" %c", &reponse);  // " %c" to consume any previous newline character
            if (reponse == 'N' || reponse == 'n') {
                date_valide = 1;  // Exit the loop by marking date_valide as 1
            }
        } else {
            printf("Entrez la date de fin (jj/mm/aaaa): ");
            if (scanf("%d/%d/%d", &jour_fin, &mois_fin, &annee_fin) != 3) {
                // If end date format is incorrect, ask if the user wants to retype or leave
                printf("Format de date invalide. Assurez-vous d'utiliser le format jj/mm/aaaa.\n");
                printf("Voulez-vous réessayer ? (O pour oui / N pour non): ");
                scanf(" %c", &reponse);  // " %c" to consume any previous newline character
                if (reponse == 'N' || reponse == 'n') {
                    date_valide = 1;  // Exit the loop by marking date_valide as 1
                }
            } else {
                date_valide = 1;  // Exit the loop if the date is valid
            }
        }
    }

    // Loop through the matrix to find matching emprunts
    for (int i = 0; i < memoire; i++) {
        // Check if the CIN matches and the borrow date is within the specified range
        if (M_eprunts_livre[i][0] == cin) {
            // Compare the borrow date with the provided range
            int is_in_range = 0;
            if ((M_eprunts_livre[i][4] > annee_debut) || 
                (M_eprunts_livre[i][4] == annee_debut && M_eprunts_livre[i][3] > mois_debut) ||
                (M_eprunts_livre[i][4] == annee_debut && M_eprunts_livre[i][3] == mois_debut && M_eprunts_livre[i][2] >= jour_debut)) {
                
                if ((M_eprunts_livre[i][4] < annee_fin) ||
                    (M_eprunts_livre[i][4] == annee_fin && M_eprunts_livre[i][3] < mois_fin) ||
                    (M_eprunts_livre[i][4] == annee_fin && M_eprunts_livre[i][3] == mois_fin && M_eprunts_livre[i][2] <= jour_fin)) {
                    is_in_range = 1;
                }
            }

            // If the borrow date is within the range, mark it as supprimé
            if (is_in_range) {
                T_emprunt_supprime[i] = 'S';
                printf("Emprunt avec CIN %lld marqué comme supprimé.\n", cin);
            }
        }
    }
    afficher_matrice();}

//----------------------------------------------------------//

//----------------------------------------------------------//
/*-------------PART3-------------*/
//Question 1 :
void calculer_statistiques(int taille_matrice) {
    int total_livres = 0;
    int total_adhérents = 0;
    int total_emprunts = 0;
    
    int cin_comptes[memoire] = {};  // Tableau pour stocker les CIN déjà comptés
    int taille_comptes = 0;  // Compteur pour le nombre d'adhérents comptés

    // Calcul du total de livres (taille du tableau T_NLivre)
    for (int i = 0; i < memoire; i++) {
        if (T_NLivre[i] != 0) {  // Si le numéro du livre existe
            total_livres++;
        }
    }
    
    // Calcul du nombre d'adhérents distincts (CIN distincts dans M_eprunts_livre)
    for (int i = 0; i < taille_matrice; i++) {
        int cin = M_eprunts_livre[i][0];  // Récupérer le CIN de l'adhérent
        if (cin != 0) {  // Si CIN valide (non nul)
            // Vérifier si le CIN n'a pas déjà été compté
            int est_deja_compte = 0;
            for (int j = 0; j < taille_comptes; j++) {
                if (cin_comptes[j] == cin) {
                    est_deja_compte = 1;
                    //break;
                }
            }
            if (!est_deja_compte) {
                cin_comptes[taille_comptes++] = cin;  // Ajouter CIN à la liste des CIN comptés
                total_adhérents++;
            }
        }
    }
    
    // Calcul du nombre d'emprunts (nombre de lignes non vides dans M_eprunts_livre)
    for (int i = 0; i < taille_matrice; i++) {
        if (M_eprunts_livre[i][1] != 0) {  // Si un numéro de livre est présent
            total_emprunts++;
        }
    }

    // Affichage sous forme de tableau
    printf("\n+---------------------------------+\n");
    printf("| Statistiques de la bibliothèque |\n");
    printf("+---------------------------------+\n");
    printf("| Total de livres      : %d        |\n", total_livres);
    printf("| Nombre d'adhérents   : %d        |\n", total_adhérents);
    printf("| Nombre d'emprunts    : %d        |\n", total_emprunts);
    printf("+---------------------------------+\n");}


//Question 2 : 
void afficher_livres_plus_empruntes(int taille_matrice_emprunts, long long int T_NLivre[memoire], char T_Titre[memoire][memoire_chaine]) {
    int emprunts_count[memoire] = {0};  // Compteur d'emprunts pour chaque livre

    // Comptabiliser les emprunts pour chaque livre
    for (int i = 0; i < taille_matrice_emprunts; i++) {
        for (int j = 0; j < memoire; j++) {
            if (T_NLivre[j] == M_eprunts_livre[i][1]) {
                emprunts_count[j]++;
            }
        }
    }

    // Trouver le nombre maximal d'emprunts
    int max_emprunts = 0;
    for (int i = 0; i < memoire; i++) {
        if (emprunts_count[i] > max_emprunts) {
            max_emprunts = emprunts_count[i];
        }
    }

    // Afficher les livres ayant le nombre maximal d'emprunts
    printf("\n ----------------------------------------------------\n");
    printf("| %-30s | %-15s |\n", "Titre du Livre", "Nombre d'Emprunts");
    printf(" ----------------------------------------------------\n");

    for (int i = 0; i < memoire; i++) {
        if (emprunts_count[i] == max_emprunts) {
            printf("| %-30s | %-17d |\n", T_Titre[i], emprunts_count[i]);
        }
    }

    printf(" ----------------------------------------------------\n");}


//Question 3 : 
void afficher_livres_jamais_empruntes(
    int taille_matrice_emprunts, 
    long long int T_NLivre[memoire], 
    char T_Titre[memoire][memoire_chaine], 
    long long int M_eprunts_livre[memoire][8])  {

    int i;
    int livre_trouve = 0; // Flag for finding borrowed books
    printf("\nListe des livres jamais empruntés :\n");
    printf("+-------------------+-------------------+-------------------+\n");
    printf("| Numero Livre      | Titre             | Etat Emprunt      |\n");
    printf("+-------------------+-------------------+-------------------+\n");

    for (i = 0; i < taille_matrice_emprunts; i++) {
        // Check if the book has never been borrowed (return date is 0)
        if (M_eprunts_livre[i][5] == 0 && M_eprunts_livre[i][6] == 0 && M_eprunts_livre[i][7] == 0) {
            printf("| %-17lld | %-17s | Jamais emprunté   |\n", T_NLivre[i], T_Titre[i]);
            livre_trouve = 1;
        }
    }

    // If no book was found, print a message
    if (livre_trouve == 0) {
        printf("| Aucun livre jamais emprunté.                              |\n");
    }

    printf("+-------------------+-------------------+-------------------+\n");}


//Question 4 :
int est_dans_periode(int jour, int mois, int annee, int jour_debut, int mois_debut, int annee_debut, int jour_fin, int mois_fin, int annee_fin) {
    if (annee < annee_debut || annee > annee_fin) {
        return 0;  // La date est en dehors de la période
    }
    if (annee == annee_debut && (mois < mois_debut || (mois == mois_debut && jour < jour_debut))) {
        return 0;  // La date est avant le début de la période
    }
    if (annee == annee_fin && (mois > mois_fin || (mois == mois_fin && jour > jour_fin))) {
        return 0;  // La date est après la fin de la période
    }
    return 1;  /* La date est dans la période*/}

// Fonction pour afficher les livres les plus empruntés dans une période donnée
void afficher_livres_plus_empruntes_pour_periode(int taille_matrice_emprunts,long long int M_eprunts_livre[memoire][8]) {
    int jour_debut, mois_debut, annee_debut;
    int jour_fin, mois_fin, annee_fin;

    // Demander à l'utilisateur de saisir la période
    printf("Entrez la date de début (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &jour_debut, &mois_debut, &annee_debut);
    printf("Entrez la date de fin (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &jour_fin, &mois_fin, &annee_fin);

    // Si la date de début est après la date de fin, on inverse les dates
    if (annee_debut > annee_fin || (annee_debut == annee_fin && mois_debut > mois_fin) || (annee_debut == annee_fin && mois_debut == mois_fin && jour_debut > jour_fin)) {
        // Inverser les dates
        int temp_jour = jour_debut;
        int temp_mois = mois_debut;
        int temp_annee = annee_debut;
        jour_debut = jour_fin;
        mois_debut = mois_fin;
        annee_debut = annee_fin;
        jour_fin = temp_jour;
        mois_fin = temp_mois;
        annee_fin = temp_annee;
    }

    int i, j;
    int count[memoire] = {0};  // Tableau pour compter les emprunts par livre
    long long int Nlivre[memoire];  // Tableau pour stocker les numéros de livres uniques
    int taille_unique = 0;  // Nombre de livres uniques

    // Compter le nombre d'emprunts pour chaque livre pendant la période donnée
    for (i = 0; i < taille_matrice_emprunts; i++) {
        int jour = M_eprunts_livre[i][2];
        int mois = M_eprunts_livre[i][3];
        int annee = M_eprunts_livre[i][4];
        long long int numero_livre = M_eprunts_livre[i][1];

        // Vérifier si l'emprunt est dans la période donnée
        if (est_dans_periode(jour, mois, annee, jour_debut, mois_debut, annee_debut, jour_fin, mois_fin, annee_fin)) {
            int found = 0;

            // Chercher si le livre existe déjà dans Nlivre
            for (j = 0; j < taille_unique; j++) {
                if (Nlivre[j] == numero_livre) {
                    count[j]++;  // Incrémenter le compteur pour ce livre
                    found = 1;  // Livre trouvé, pas besoin de continuer cette boucle
                }
            }

            // Si le livre n'a pas encore été ajouté, l'ajouter dans le tableau Nlivre
            if (found == 0) {
                Nlivre[taille_unique] = numero_livre;
                count[taille_unique] = 1;  // Premier emprunt pour ce livre
                taille_unique++;
            }
        }
    }

    // Trouver le nombre maximum d'emprunts
    int max_emprunts = 0;
    for (i = 0; i < taille_unique; i++) {
        if (count[i] > max_emprunts) {
            max_emprunts = count[i];
        }
    }

    // Afficher les livres les plus empruntés pendant la période donnée
    printf("\nLes livres les plus empruntés pendant la période %02d/%02d/%d - %02d/%02d/%d sont :\n", 
            jour_debut, mois_debut, annee_debut, jour_fin, mois_fin, annee_fin);
    printf("+-------------------+-------------------+-------------------+\n");
    printf("| Numero Livre      | Titre             | Nombre d'Emprunts |\n");
    printf("+-------------------+-------------------+-------------------+\n");

    for (i = 0; i < taille_unique; i++) {
        if (count[i] == max_emprunts) {
            // Afficher le titre du livre avec son numéro (on suppose que vous avez un moyen de retrouver le titre à partir du numéro de livre)
            int index = -1;
            for (j = 0; j < taille_matrice_emprunts; j++) {
                if (T_NLivre[j] == Nlivre[i]) {
                    index = j;
                }
            }

            // Si le livre a été trouvé, afficher ses informations
            if (index != -1) {
                printf("| %-17lld | %-17s | %-17d |\n", Nlivre[i], T_Titre[index], count[i]);
            }
        }
    }

    printf("+-------------------+-------------------+-------------------+\n");}



//Question 5 :
void afficher_emprunteurs_frequents(int taille_matrice_emprunts,long long int M_eprunts_livre[memoire][8]) {
    int i, j;
    int count[memoire] = {0};  // Tableau pour compter les emprunts par CIN
    long long int CIN[memoire];  // Tableau pour stocker les CIN uniques
    int taille_unique = 0;  // Nombre de CIN uniques

    // Compter le nombre d'emprunts pour chaque CIN
    for (i = 0; i < taille_matrice_emprunts; i++) {
        long long int cin = M_eprunts_livre[i][0];  // CIN de l'emprunteur
        int found = 0;

        // Chercher si le CIN existe déjà dans CIN
        for (j = 0; j < taille_unique; j++) {
            if (CIN[j] == cin) {
                count[j]++;  // Incrémenter le compteur pour ce CIN
                found = 1;
            }
        }

        // Si le CIN n'a pas encore été ajouté, l'ajouter dans le tableau CIN
        if (found == 0) {
            CIN[taille_unique] = cin;
            count[taille_unique] = 1;  // Premier emprunt pour ce CIN
            taille_unique++;
        }
    }

    // Trouver le nombre maximum d'emprunts
    int max_emprunts = 0;
    for (i = 0; i < taille_unique; i++) {
        if (count[i] > max_emprunts) {
            max_emprunts = count[i];
        }
    }

    // Afficher les emprunteurs avec le plus grand nombre d'emprunts
    printf("\nLes emprunteurs les plus fréquents (avec %d emprunts) sont :\n", max_emprunts);
    printf("+-------------------+-------------------+\n");
    printf("| CIN               | Nombre d'Emprunts |\n");
    printf("+-------------------+-------------------+\n");

    for (i = 0; i < taille_unique; i++) {
        if (count[i] == max_emprunts) {
            printf("| %08lld          | %-17d |\n", CIN[i], count[i]);
        }
    }

    printf("+-------------------+-------------------+\n");}

//----------------------------------------------------------//


//----------------------------------------------------------//
/*-------------PROGRAMME_PRINCIPAL-------------*/
int main(){
    system("chcp 65001 > nul"); // pour accepter les caracters (┌, ┬, ┐, │, ─, etc.)
    char date_courante[11]; // Tampon pour contenir la date au format jj/mm/aaaa
    calculer_date_courante(date_courante);// Appeler la fonction pour calculer la date actuelle
    Set_data_base();//

    taille_tableau_livre = fonction_taille_tableau(T_Titre);
    printf("Taille des tableaux des livres = %d",taille_tableau_livre);

    taille_matrice_emprunts = fonction_taille_matrice_emprunts(M_eprunts_livre);
    printf("\nTaille matrice des emprunts = %d",taille_matrice_emprunts);
    

    int choix_menu_principale = 0;
    while (choix_menu_principale != 4)
    { 
       
        afficher_menu_principal();
        choix_menu_principale=lire_entier();
        switch (choix_menu_principale)
        {
            case 1 :
            {
                int choix_menu_biblio = 0;
                do {
                    afficher_menu_bibliotheque();
                    choix_menu_biblio = lire_entier();
                    switch(choix_menu_biblio)
                        {
                        case 1:
                            afficher_tous_livres(taille_tableau_livre,T_NLivre,T_Titre,T_Nbr_exp);
                            break;
                        case 2:
                            ajouter_nouveau_livres(T_Titre,T_NLivre,T_Nbr_exp);
                            break;
                        case 3:
                            supprimer_livre(taille_tableau_livre,T_NLivre,T_Titre,M_eprunts_livre,T_Nbr_exp);        
                            break;
                        case 4:
                            modifier_nombre_exemplaires(taille_tableau_livre, T_NLivre, T_Titre, T_Nbr_exp);
                            break;
                        case 5:
                            rechercher_livre(taille_tableau_livre, T_NLivre, T_Titre, T_Nbr_exp, T_livre_supprime_entregistre);
                            break;
                        case 6:
                            afficher_livres_disponibles(taille_tableau_livre,T_NLivre,T_Titre,T_Nbr_exp,M_eprunts_livre,T_livre_supprime_entregistre);
                            break;
                        case 7:
                            // Retour au menu principal
                            break;
                        default:
                            printf("Option invalide !\n");
                        }
                    } while(choix_menu_biblio != 7);
                break;
            }
            case 2: // Menu emprunt
            {
                int choix_menu_emprunt = 0;
                //afficher_toute_la_matrice(taille_matrice_emprunts, M_eprunts_livre);
                afficher_toute_la_matrice_etat(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
                
                printf("\n");
                do {
                    afficher_menu_emprunt();
                    choix_menu_emprunt = lire_entier();
                    
                    switch(choix_menu_emprunt)
                    {
        
                        case 1:
                            afficher_toute_la_matrice_etat(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
                            printf("\n");
                            taille_matrice_emprunts = ajouter_emprunt_effectif(T_NLivre, T_Titre, T_Nbr_exp, T_livre_supprime_entregistre, M_eprunts_livre, T_livre_retour, taille_tableau_livre, taille_matrice_emprunts);
                            break;
                        case 2:
                            afficher_toute_la_matrice_etat(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre); 
                            consulter_emprunts_adherent_tout_en_un(M_eprunts_livre, T_livre_retour, taille_matrice_emprunts);
                            break;
                        case 3:
                            afficher_toute_la_matrice_etat(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre); 
                            enregistrer_retour_livre(M_eprunts_livre, T_livre_retour, taille_matrice_emprunts);
                            break;
                        case 4: 
                            afficher_emprunts_en_cours(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
                            break;
                        case 5: 
                            afficher_livres_en_retard(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
                            break;
                        case 6: 
                            afficher_emprunts_par_date_retour(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
                            break;
                        case 7: 
                            supprimer_emprunt();
                            break;
                        case 8:
                            // Retour au menu principal
                            break; 
                        default: printf("Option invalide !\n"); 
                    }
                }while(choix_menu_emprunt != 8);
                break;
            }
            case 3: // Menu statistiques
            {
                int choix_menu_stat = 0;
                do {
                    afficher_menu_statistique();
                    choix_menu_stat = lire_entier();
                    switch(choix_menu_stat)
                    {
                        case 1:
                            calculer_statistiques(memoire);
                            break;
                        case 2:
                            afficher_livres_plus_empruntes(taille_matrice_emprunts, T_NLivre, T_Titre);
                            break;
                        case 3:
                            afficher_livres_jamais_empruntes(taille_matrice_emprunts, T_NLivre, T_Titre, M_eprunts_livre);
                            break;
                        case 4:
                            afficher_livres_plus_empruntes_pour_periode(taille_matrice_emprunts, M_eprunts_livre);
                            break;
                        case 5:
                            afficher_emprunteurs_frequents(taille_matrice_emprunts,M_eprunts_livre);
                            break;
                        case 6:
                            // Retour au menu principal
                            break;
                        default:
                            printf("Option invalide !\n");
                    }
                }while(choix_menu_stat != 6); // reste dans le menu statistiques jusqu'à ce que l'utilisateur choisisse 6
                break;
            }
            case 4 :
                printf("au revoir !");
                break;

            default :
                printf("veuillez entrer un entier entre 1 et 4 :");
            break;
        }
    }
















    /*
    afficher_tous_livres(taille_tableau_livre,T_NLivre,T_Titre,T_Nbr_exp);
    //ajouter_nouveau_livres(T_Titre,T_NLivre,T_Nbr_exp);
    //printf("Taille des tableaux des livres = %d",taille_tableau_livre);
    
    //modifier_nombre_exemplaires(taille_tableau_livre, T_NLivre, T_Titre, T_Nbr_exp);
    //rechercher_livre(taille_tableau_livre, T_NLivre, T_Titre, T_Nbr_exp, T_livre_supprime_entregistre);
    afficher_toute_la_matrice(taille_matrice_emprunts,M_eprunts_livre);
    //supprimer_livre(taille_tableau_livre,T_NLivre,T_Titre,M_eprunts_livre,T_Nbr_exp);
    //printf("Taille des tableaux des livres = %d",taille_tableau_livre);
    //afficher_tous_livres(taille_tableau_livre,T_NLivre,T_Titre,T_Nbr_exp);
    //afficher_livres_etats(taille_tableau_livre, T_NLivre, T_Titre, T_Nbr_exp, T_livre_supprime_entregistre);
    //afficher_livres_etats(taille_tableau_livre, T_NLivre, T_Titre, T_Nbr_exp, T_livre_supprime_entregistre);    
    //afficher_livres_disponibles(taille_tableau_livre,T_NLivre,T_Titre,T_Nbr_exp,M_eprunts_livre,T_livre_supprime_entregistre);
    printf("\n");
    //taille_matrice_emprunts = ajouter_emprunt_effectif(T_NLivre, T_Titre, T_Nbr_exp, T_livre_supprime_entregistre, M_eprunts_livre, T_livre_retour, taille_tableau_livre, taille_matrice_emprunts);
    //taille_matrice_emprunts = fonction_taille_matrice_emprunts(M_eprunts_livre);
    //afficher_toute_la_matrice(taille_matrice_emprunts,M_eprunts_livre);
    printf("\nTaille matrice des emprunts = %d\n",taille_matrice_emprunts);
    //consulter_emprunts_adherent_tout_en_un(M_eprunts_livre, T_livre_retour, taille_matrice_emprunts);
    afficher_toute_la_matrice_etat(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);

    //enregistrer_retour_livre(M_eprunts_livre, T_livre_retour, taille_matrice_emprunts);
    afficher_toute_la_matrice_etat(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
    afficher_toute_la_matrice(taille_matrice_emprunts, M_eprunts_livre);
    afficher_emprunts_en_cours(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
    afficher_livres_en_retard(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
    //afficher_emprunts_par_date_retour(taille_matrice_emprunts, M_eprunts_livre, T_livre_retour, T_NLivre, T_Titre);
    //supprimer_emprunt();
    calculer_statistiques(memoire);
    afficher_livres_plus_empruntes(taille_matrice_emprunts, T_NLivre, T_Titre);
    afficher_livres_jamais_empruntes(taille_matrice_emprunts, T_NLivre, T_Titre, M_eprunts_livre);
    afficher_emprunteurs_frequents(taille_matrice_emprunts,M_eprunts_livre);
    afficher_livres_plus_empruntes_pour_periode(taille_matrice_emprunts, M_eprunts_livre);
    */
    return 0;
}   






            


