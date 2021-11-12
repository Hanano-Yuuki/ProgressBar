#include <iostream>
#include <iomanip>
#include <chrono>

template<class T=int>
struct PrograssBar{
public:
    PrograssBar(T tot_=0)
        :tot(tot_),cur(0),timeUse(std::chrono::nanoseconds::zero()){
            nw=std::chrono::high_resolution_clock::now();
            width=100;
        }
    void inc(int p=1){
        cur+=p;
    }
    void update(){
        show();
    }
    void init(int tot_){
        cur=0,tot=tot_;
        timeUse=std::chrono::nanoseconds::zero();
    }
    void setWidth(int width_){
        if(width_<=0) throw std::runtime_error("[PrograssBar Error]: Width must be positive.");
        width=width_;
    }
private:
    int width;
    T cur,tot;
    std::chrono::_V2::system_clock::time_point lst,nw;
    std::chrono::duration<int64_t,std::nano> timeUse;
    void show(){
        if(tot==0) throw std::runtime_error("[PrograssBar Error]: Max Prograss not set or be zero.");
        printf("[");
        int percentage=cur*width/tot;
        for(int i=1;i<=width;i++){
            char ch;
            if(i<percentage) ch='=';
            else if(i==percentage) ch='>';
            else ch=' ';
            printf("%c",ch);
        }
        lst=nw;
        nw=std::chrono::high_resolution_clock::now();
        timeUse+=nw-lst;
        decltype(timeUse) resTime=std::chrono::nanoseconds::zero();
        if(cur!=0) resTime=timeUse/cur*(tot-cur);
        int ss=int(timeUse.count()/1e9)%60;
        int mm=int(timeUse.count()/1e9)/60%60;
        int hh=int(timeUse.count()/1e9)/60/60;
        int rss=int(resTime.count()/1e9)%60;
        int rmm=int(resTime.count()/1e9)/60%60;
        int rhh=int(resTime.count()/1e9)/60/60;
        if(cur!=0){
            // printf("]  %03d:%02d:%02d<%03d:%02d:%02d  %.1f\r",
            //                 hh,mm,ss,rhh,rmm,rss,float(cur)/float(tot));
            std::cout<<"]  "
                     <<std::setw(2)<<std::setfill('0')<<hh<<':'
                     <<std::setw(2)<<std::setfill('0')<<mm<<':'
                     <<std::setw(2)<<std::setfill('0')<<ss<<'<'
                     <<std::setw(2)<<std::setfill('0')<<rhh<<':'
                     <<std::setw(2)<<std::setfill('0')<<rmm<<':'
                     <<std::setw(2)<<std::setfill('0')<<rss<<"  ";
            std::cout<<std::fixed<<std::setprecision(1)<<float(cur)/float(tot)*100<<"%\r";
        }
        else {
            // printf("]  NA:NA:NA<NA:NA:NA  %.1f\r",float(cur)/float(tot));
            std::cout<<"]  NA:NA:NA<NA:NA:NA  ";
            std::cout<<std::fixed<<std::setprecision(1)<<float(cur)/float(tot)*100<<"%\r";
        }
        std::cout.flush();
    }
};