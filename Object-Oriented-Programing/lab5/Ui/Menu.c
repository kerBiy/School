//
// Created by h on 3/10/24.
//
#include "Menu.h"

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void print_main_menu() {
    printf("Meniu Principal\n");
    printf("1. Adauga Medicament\n");
    printf("2. Modifica Medicament\n");
    printf("3. Sterge stoc Medicament\n");
    printf("4. Afisare Medicamente Sortate\n");
    printf("5. Filtreaza Medicamente\n");
    printf("q. Iesire\n");

}

void print_sortare_menu() {
    printf("Meniu Sortari\n");
    printf("1.Sortare dupa nume crescator\n");
    printf("2.Sortare dupa nume Descrescator\n");
    printf("3. Sosrtare dupa cantitate Crescator\n");
    printf("4. Sosrtare dupa cantitate Descrescator\n");
}

void print_filtrare_menu() {
    printf("Meniu Filtrari\n");
    printf("1. Filtrare dupa cantitate\n");
    printf("2. FIltrare dupa Initiala\n");
    printf("3. Filtrare dupa concentratie\n");
}

void clear(void) {
    while (getchar() != '\n');
}

///  UI ADAUGARE MEDICAMENT
/// @param lista LISTA DE MEDICAMENTE
void adauga_medicament_ui(Lista *history, Lista *lista) {
    int id, cantitate;
    char nume[50];
    float concentratie;
    printf("id:");
    if (scanf("%d", &id) != 1) {
        printf("Inalid Input!\n");
        return;
    }
    clear();
    printf("nume:");
    scanf("%s", nume);
    getchar();
    modify_string(nume);
    int exist = verify_existence(lista, nume);
    if (exist == -1) {
        printf("concentratie:");
        if (scanf("%f", &concentratie) != 1) {
            printf("Inalid Input!\n");
            return;
        }
        printf("Cantitate:");
        if (scanf("%d", &cantitate) != 1) {
            printf("Inalid Input!\n");
            return;
        }
        if (add_medicament(lista, id, nume, concentratie, cantitate)) {
            printf("Medicament Adaugat cu succes!\n");
            updateHistory(history, lista);
        } else {
            printf("Medicamentul nu a fost adaugat!\n");
        }
    } else {
        printf("Medicamentul exista deja!\nModificati cantitatea:");
        if (scanf("%d", &cantitate) != 1) {
            printf("Inalid Input!\n");
            return;
        }
        modify_quantity(lista, exist, cantitate);

    }

}

/// UI MODIFICARE MEDICAMENT
/// @param lista de items
void modifica_medicament_ui(Lista *history, Lista *lista) {
    int id;
    char nume[50];
    float concentratie;
    printf("id:");
    if (scanf("%d", &id) != 1) {
        printf("INVALID INPUT\n");
        return;
    }
    clear();
    printf("nume:");
    scanf("%s", nume);
    getchar();
    modify_string(nume);
    printf("concentratie:");
    if (scanf("%f", &concentratie) != 1) {
        printf("INVALID INPUT\n");
        return;
    }
    if (modify_medicament(lista, id, nume, concentratie)) {
        printf("Medicament Modificat cu succes!\n");
        updateHistory(history, lista);
    } else {
        printf("Medicamentu nu a putut fi modificat!\n");
    }
}

/// UI STERGERE MEDICAMENT
/// @param lista lista de items
void sterge_medicament_ui(Lista *history, Lista *lista) {
    int id;
    printf("Id:");
    if (scanf("%d", &id) != 1) {
        printf("INVALID INPUT\n");
        return;
    }
    if (delete_all_stock(lista, id)) {
        printf("Stocul Medicamentului a fost Eliminat cu succes!\n");
        updateHistory(history, lista);
    } else {
        printf("Stocul Medicamentului nu a fost eliminat!\n");
    }
}

/// Afiseaza lista de items furnizata
/// @param lista lista de items
void afisare_lista(Lista *lista) {
    int len = get_len(lista);

    for (int i = 0; i < len; i++) {
        int id = get_id(get_medicament(lista, i));
        char *nume = get_nume(get_medicament(lista, i));
        float concentratie = get_concentratie(get_medicament(lista, i));
        int cantitate = get_cantitate(get_medicament(lista, i));
        printf("%d %s %.2f%% %d\n", id, nume, concentratie, cantitate);
    }
}

/// UI AFISARI CU SORTARI
/// @param lista lista de items
void afisare_medicament_ui(Lista *lista) {
    int loop = 1;
    char choice;
    int sort_alg;

    print_sortare_menu();
    while (loop) {
        printf(":");
        choice = getchar();

        if (choice == '1') {
            printf("Enter the sorting alg:\n");
            printf("Enter 1 for buble sort\n");
            printf("Enter 2 for selection sort\n");
            printf(":");
            scanf("%d", &sort_alg);

            sort(lista, nume_cresc, sort_alg);
            loop = 0;
        } else if (choice == '2') {
            printf("Enter the sorting alg:\n");
            printf("Enter 1 for buble sort\n");
            printf("Enter 2 for selection sort\n");
            printf(":");
            scanf("%d", &sort_alg);

            sort(lista, nume_descresc, sort_alg);
            loop = 0;
        } else if (choice == '3') {
            printf("Enter the sorting alg:\n");
            printf("Enter 1 for buble sort\n");
            printf("Enter 2 for selection sort\n");
            printf(":");
            scanf("%d", &sort_alg);

            sort(lista, cantitate_crescator, sort_alg);
            loop = 0;
        } else if (choice == '4') {
            printf("Enter the sorting alg:\n");
            printf("Enter 1 for buble sort\n");
            printf("Enter 2 for selection sort\n");
            printf(":");
            scanf("%d", &sort_alg);

            sort(lista, cantitate_descrescator, sort_alg);
            loop = 0;
        }

    }
    afisare_lista(lista);

}

/// UI FILTRARE MEDICAMENT CU AFISARE
/// @param lista lista de items
void filtreaza_medicament_ui(Lista *lista) {
    char choice;
    int loop = 1;
    print_filtrare_menu();
    while (loop) {
        choice = getchar();
        if (choice == '1') {
            int cantitate;
            printf("Cantitate:");
            scanf("%d", &cantitate);
            Lista *list = filter_cantitate(lista, cantitate);
            afisare_lista(list);
            free(list->items);
            free(list);
            loop = 0;
        } else if (choice == '2') {
            char initiala;
            printf("initiala:");
            clear();
            initiala = tolower(getchar());
            Lista *list = filter_initiala(lista, initiala);
            afisare_lista(list);
            free(list->items);
            free(list);
            loop = 0;
        } else if (choice == '3') {
            float concentratie;
            printf("Concentratie: ");
            scanf("%f", &concentratie);
            Lista *list = filter_concentratie(lista, concentratie);
            afisare_lista(list);
            free(list->items);
            free(list);
            loop = 0;
        }
    }
}

int main_menu() {
    Lista *history = createLista();
    Lista *empty = createLista();
    push(history, empty);

    Lista *lista = createLista();

    char choice;
    print_main_menu();
    while (1) {
        choice = getchar();
        if (choice == '1') {
            adauga_medicament_ui(history, lista);
            print_main_menu();
        } else if (choice == '2') {
            modifica_medicament_ui(history, lista);
            print_main_menu();
        } else if (choice == '3') {
            sterge_medicament_ui(history, lista);
            print_main_menu();
        } else if (choice == '4') {
            afisare_medicament_ui(lista);
            print_main_menu();
        } else if (choice == '5') {
            filtreaza_medicament_ui(lista);
            print_main_menu();
        } else if (choice == 'q') {
            for (int i = 0; i < history->len; ++i) {
                destructor(history->items[i]);
            }
            free(history->items);
            free(history);
            destructor(lista);
            return 0;
        } else if (choice == '0') {
            if (undo(history, &lista) == 1) {
                printf("The last operation was undone...\n");
            } else {
                printf("You can't undo any further.\n");
            }
            print_main_menu();
        } else if (choice == 'p') {
            afisare_lista(lista);
            print_main_menu();
        }
    }
}