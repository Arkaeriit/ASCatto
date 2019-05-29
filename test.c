#include "test.h"

void test1(){
    struct headFile* test=A_initialisation();
    printf("%i\n",test->nLignes);
    A_insertion(test,1);
    printf("lolo\n");
    printf("%i\n",test->nLignes);
    A_insertion(test,1);
    printf("%i\n",test->nLignes);
    A_append(test);
    printf("%i\n",test->nLignes);
    A_supression(test,1);
    printf("%i\n",test->nLignes);
}

void test2(){
    struct headFile* test=A_readFile("/home/maxime/test");
    printf("%i\n%s  \n%s\n",test->nLignes,A_readListe(test,1),test->next->next->next->ligne);
}

void test3(){
    struct headFile* test=A_initialisation();
    printf("%i\n",test->nLignes);
    A_insertion(test,1);
    printf("000\n");
    A_writeListe(test,1,"Lalala\n");
    printf("111\n");
    A_insertion(test,1);
    A_writeListe(test,1,"prrr\n");
    A_append(test);
    A_writeListe(test,3,"trrrr\n");
    A_writeFile(test,"/home/maxime/testwr");
}

void test4(){
    struct headFile* test=A_initialisation();
    A_append(test);
    A_writeListe(test,1,"1");
    A_append(test);
    A_writeListe(test,2,"2");
    A_append(test);
    A_writeListe(test,3,"3");
    A_append(test);
    A_writeListe(test,4,"4");
    A_insertion(test,3);
    A_insertion(test,1);
    A_supression(test,1);
    int i=3;
    i++;
}

void test5(){
    struct headFile* test=A_readFile("/home/maxime/test");
    A_writeFile(test,"/home/maxime/testwr");
}

void test6(){
     struct headFile* test=A_readFile("/home/maxime/test");       
     I_init();
     I_redraw(test,2,"testTest");
     getchar();
     endwin();
}
