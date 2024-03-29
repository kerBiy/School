//
// Created by h on 3/8/24.
//

#include "tests.h"

#include "../Utility/Utility.h"
#include <stdlib.h>
#include <string.h>

void test_all() {
    test_domain();
    test_service();
}

void test_domain() {
    Medicament *m = createMedicament(1, "asdf", 2.5f, 30);
    Medicament *m3 = createMedicament(2, "hfg", 2.0f, 30);
    Medicament *m1 = createMedicament(1, "", 2.5f, 30);
    Medicament *m2 = createMedicament(1, "asdf", 200.0f, 30);
    assert(get_id(m) == 1);
    assert(strcmp(get_nume(m), "asdf") == 0);
    assert(get_concentratie(m) == 2.5);
    assert(get_cantitate(m) == 30);

    Lista *l = createLista();
    assert(get_len(l) == 0);
    assert(validator(m, l) == 1);
    assert(validator(m1, l) == 0);
    assert(validator(m2, l) == 0);
    assert(validator(m3, l) == 1);
    assert(get_len(l) == 0);
    push(l, m);
    assert(get_len(l) == 1);
    push(l, m3);
    pop(l, 1);
    assert(get_len(l) == 1);
    pop(l, 7);

    free(m1);
    free(m2);
    destructor(l);
}

void test_service() {
    // test ADD
    Lista *l = createLista();
    assert(get_len(l) == 0);
    assert(add_medicament(l, 1, "Nurofen", 2.5f, 50));
    assert(add_medicament(l, 1, "Nurofen", 2.5f, 30) == 0);
    assert(add_medicament(l, 2, "Nurofen", 2.5f, 50) == 0);
    assert(add_medicament(l, 2, "", 2.5f, 50) == 0);

    //TEST MODIFY
    assert(get_len(l) == 1);
    assert(modify_medicament(l, 1, "Ibuprofen", 3.0f) == 1);
    assert(get_concentratie(get_medicament(l, 0)) == 3.0f);
    assert(modify_medicament(l, 30, "asdf", 4.2f) == 0);
    assert(modify_quantity(l, 1, 30));
    assert(modify_quantity(l, 30, 30) == 0);
    assert(get_cantitate(get_medicament(l, 0)) == 30.0f);

    //TEST DELETE
    assert(delete_all_stock(l, 30) == 0);
    assert(delete_all_stock(l, 1) == 1);

    assert(get_cantitate(get_medicament(l, 0)) == 0);

    add_medicament(l, 2, "Nurofen", 3.2f, 50);
    assert(verify_existence(l, "Nurofen") == 2);
    assert(verify_existence(l, "Cauciuc") == -1);

    //sortari
    add_medicament(l, 3, "Penicilina", 2.5f, 42);
    add_medicament(l, 4, "Antibiotic", 87.5f, 21);

    assert(strcmp(get_nume(get_medicament(l, 0)), "Ibuprofen") == 0);
    sort(l, nume_cresc, 1);
    assert(strcmp(get_nume(get_medicament(l, 0)), "Antibiotic") == 0);
    assert(get_cantitate(get_medicament(l, 0)) == 21);
    sort(l, cantitate_crescator, 2);
    assert(get_cantitate(get_medicament(l, 0)) == 0);
    sort(l, cantitate_descrescator, 1);
    assert(get_cantitate(get_medicament(l, 0)) == 50);
    sort(l, nume_descresc, 2);
    assert(strcmp(get_nume(get_medicament(l, 0)), "Penicilina") == 0);

    //FILTRARI
    Lista *filtrate = filter_cantitate(l, 25);
    assert(get_len(filtrate) == 2);
    free(filtrate->items);
    free(filtrate);

    filtrate = filter_initiala(l, 'N');
    assert(get_len(filtrate) == 1);
    assert(strcmp(get_nume(get_medicament(filtrate, 0)), "Nurofen") == 0);
    modify_string(get_nume(get_medicament(filtrate, 0)));
    free(filtrate->items);
    free(filtrate);

    filtrate = filter_concentratie(l, 3.5f);
    assert(get_len(filtrate) == 1);
    free(filtrate->items);
    free(filtrate);

    //TODO teste undo

    Lista *history = createLista();
    Lista *empty = createLista();
    push(history, empty);

    assert(undo(history, &l) == 0);
    updateHistory(history, l);
    assert(history->len == 2);
    assert(undo(history, &l) == 1);
    assert(history->len == 1);

    for (int i = 0; i < history->len; ++i) {
        destructor(history->items[i]);
    }
    free(history->items);
    free(history);
    destructor(l);

    Lista *null = NULL;
    assert(destructor(null) == 0);
}