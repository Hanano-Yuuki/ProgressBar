#include <iostream>
#include "PrograssBar.hpp"

int main(){
    PrograssBar<size_t> pg(5000);
    pg.setWidth(50);
    for(int i=0;i<5000;i++){
        pg.inc();
        pg.update();
        system("sleep 0.02s");
    }
    puts("");
    return 0;
}