#include "attoLib.h"
#include "test.h"

int main(int argc,char** argv){
    I_init();
    struct headFile* lst;
    if(argc>1){
        lst = A_readFile(*(argv+1));
    }else{
        exit(1);
    }
    I_idle(lst);
    return 0;
}
