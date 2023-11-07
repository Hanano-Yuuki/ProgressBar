#include <iostream>
#include <thread>
#include <chrono>
#include <array>
#include <atomic>
#include "ProgressBar.hpp"

int main(){
    constexpr int NUMTHREADS=128;
    constexpr int ITERATION=5000;
    std::atomic<int> cnt(0);
    std::array<std::thread,NUMTHREADS> t;
    ProgressBar<size_t> pg(ITERATION);
    pg.setWidth(50);
    pg.init(ITERATION);
    for(int i=0;i<NUMTHREADS;i++){
        t[i]=std::move(std::thread([&cnt, &pg]{
            while(true){
                if(int exp=cnt.load();exp<ITERATION){
                    bool status=cnt.compare_exchange_weak(exp,exp+1);
                    if(!status) continue;
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                    pg.inc(), pg.update();
                }
                else break;;
            }
        }));
    }
    for(int i=0;i<NUMTHREADS;i++) t[i].join();
    puts("");
    return 0;
}
