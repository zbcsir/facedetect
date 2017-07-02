/*
 * Time : 2017-5-7
 * Author : zbc
 * Function : to output the errors to Log
*/


#include <log.h>
#include <time.h>

string getTime(){
    time_t seconds = time(NULL);    //获取时间
    struct tm *p;
    p = localtime(&seconds);//获取本地时间
    char strTime[100] = {0};
    sprintf(strTime,"%4d-%2d-%2d %2d:%2d:%2d",1900+p->tm_year,
            1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
    return string(strTime) ;
}

void addLog(string message){
    string timeCurrent = getTime();
    char* logFile = "errorLog.txt" ;
    ofstream out ;
    out.open(logFile ,ios::out|ios::app);
    if(out.is_open()){
        out<<"["<<timeCurrent<<"] : "<<message<<"\n" ;
        out.close();
    }
}

void addDebugLog(string message){
    string timeCurrent = getTime();
    char* logFile = "debugLog.txt" ;
    ofstream out ;
    out.open(logFile ,ios::out|ios::app);
    if(out.is_open()){
        out<<"["<<timeCurrent<<"] : "<<message<<"\n" ;
        out.close();
    }
}
