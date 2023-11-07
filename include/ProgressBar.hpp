#include <iostream>
#include <iomanip>
#include <chrono>
#include <atomic>

template<class T=int>
struct ProgressBar{
public:
    ProgressBar(T tot_=0)
        :tot(tot_),cur(0),timeUse(std::chrono::nanoseconds::zero()){
            beginTm=std::chrono::high_resolution_clock::now();
            width=100;
            prec=0.001;
            lstShowedPercentage=0;
            lstBarPos=0;
        }
    void inc(int p=1){
        while(lock.test_and_set(std::memory_order_acquire));
        cur+=p;
        lock.clear(std::memory_order_release);
    }
    void update(){
        while(lock.test_and_set(std::memory_order_acquire));
        show();
        lock.clear(std::memory_order_release);
    }
    void init(int tot_,float precSet=0){
        cur=0,tot=tot_;
        if(precSet>0) prec=precSet;
        beginTm=std::chrono::high_resolution_clock::now();
        lstShowedPercentage=0;
        lstBarPos=0;
        printf("[%s]  NA:NA:NA.NA <NA:NA:NA.NA   00.0%%\r",std::string(width,' ').c_str());
    }
    void setWidth(int width_){
        if(width_<=0) throw std::runtime_error("[ProgressBar Error]: Width must be positive.");
        width=width_;
    }
private:
    int width, lstBarPos;
    T tot, cur;
    float prec, lstShowedPercentage;
    std::atomic_flag lock=ATOMIC_FLAG_INIT;
    std::chrono::_V2::system_clock::time_point beginTm;
    std::chrono::duration<int64_t,std::nano> timeUse;
    inline void printX(std::string str, int x){
        printf("\033[%dG%s",x+1,str.c_str());
    }
    void show(){
        if(cur==0) return;
        if(tot==0) throw std::runtime_error("[ProgressBar Error]: Max Prograss cannot be zero.");
        float percentage=float(cur)/float(tot);
        int barLen=width*percentage;
        if(percentage<lstShowedPercentage+prec) return;
        else lstShowedPercentage=percentage;
        for(int i=lstBarPos;i<barLen;i++){
            printX("=",i+1);
        }
        if(barLen<width) printX(">",barLen+1);
        lstBarPos=barLen;
        timeUse=std::chrono::high_resolution_clock::now()-beginTm;
        auto resTime=timeUse/cur*(tot-cur);
        
        int timeUseMsecond=std::chrono::duration_cast<std::chrono::milliseconds>(timeUse).count();
        int resTimeMsecond=std::chrono::duration_cast<std::chrono::milliseconds>(resTime).count();
        
        int ms,ss,mm,hh;
        int rms,rss,rmm,rhh;

        ms=timeUseMsecond%1000, timeUseMsecond/=1000;
        ss=timeUseMsecond%60, timeUseMsecond/=60;
        mm=timeUseMsecond%60, timeUseMsecond/=60;
        hh=timeUseMsecond;

        rms=resTimeMsecond%1000, resTimeMsecond/=1000;
        rss=resTimeMsecond%60, resTimeMsecond/=60;
        rmm=resTimeMsecond%60, resTimeMsecond/=60;
        rhh=resTimeMsecond;

        printf("\033[%dG%02d:%02d:%02d.%03d<%02d:%02d:%02d.%03d  %.1f%%\r", width+5, hh, mm, ss, ms, rhh,
                rmm, rss, rms, percentage * 100);
        fflush(stdout);
    }
};
