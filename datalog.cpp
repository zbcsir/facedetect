#include "datalog.h"

DataLog::DataLog(string strDir,string filename,int maxsize,int filecount,int timeFormat)
{
    m_strDir = strDir;
    m_LogFileName = m_strDir+string("\\")+filename;
    m_MaxFileSize = maxsize;
    m_FileCount = filecount;
    m_timeFormat = timeFormat;

    //判断日志目录是否存在
    if(!checkFolderExist(m_strDir.c_str()))
    {
        _mkdir(m_strDir.c_str());
    }
    m_outputFile = new fstream;
    string strname = m_LogFileName+".txt";
//    m_outputFile->open(strname, ofstream::out|ofstream::app);
//    m_outputFile->open(strname, ios::out|ios::app);
    bool b=m_outputFile->is_open();
    if(b == true){

    }

}
DataLog::~DataLog()
{
    if(m_outputFile)
        delete m_outputFile;
}
//********************************
//函数名：DataLog::checkFolderExist
//描  述：测试目录是否存在
//参  数：strPath 目录名
//返回值：存在返回真
//*************************************
bool DataLog::checkFolderExist( const string  & strPath)
{
    if(_access(strPath.data(),0) == 0)
        return true;
    else
        return false;
}
//********************************
//函数名：DataLog::addLog
//描  述：向文件中添加日志信息
//参  数 log 为信息内容
//返回值：void
//*************************************
void DataLog::addLog(string log)
{
    string currentTime = getCurrentTime(); //获取本地时间
    if(m_timeFormat == NETLOG)
        *m_outputFile<<"["<<currentTime<<"] "<<log<<endl;
    else
        *m_outputFile<<currentTime<<" "<<log<<endl;
    //判断文件大小
    fileSizeLimit();
}
//********************************
//函数名：DataLog::fileSizeLimit
//描  述：判断文件大小是否达到最大值
//参  数：无
//返回值：void
//*************************************
void DataLog::fileSizeLimit()
{
    int filesize = getCurrentLogFileSize();
    if(filesize>=m_MaxFileSize*1024)
        fileOffset();

}
//********************************
//函数名：DataLog::fileOffset
//描  述：实现文件名的偏移
//参  数：无
//返回值：void
//*************************************
void DataLog::fileOffset()
{
    m_outputFile->close();   //关闭当前文件
    char filename[100]={0};
    char newfilename[100] = {0};
    for(int i = m_FileCount-1;i > 0;i--)
    {
        memset(filename,0,100);
        sprintf(filename,"%s%d.txt",m_LogFileName.data(),i);
        if(checkFolderExist(filename))  //存在
        {
            if(i == m_FileCount-1)
            {
                remove(filename);//删除文件
                continue;
            }
            //文件名序号向后偏移
            memset(newfilename,0,100);
            sprintf(newfilename,"%s%d.txt",m_LogFileName.data(),i+1);
            rename(filename,newfilename);
        }
    }
    memset(filename,0,100);
    sprintf(filename,"%s.txt",m_LogFileName.data());
    sprintf(newfilename,"%s%d.txt",m_LogFileName.data(),1);
    rename(filename,newfilename);
    m_outputFile->open(filename,ofstream::out|ofstream::app);    //打开日志文件
 }

//********************************
//函数名：DataLog::getCurrentLogFileSize
//描  述：计算当前日记文件的大小
//参  数：无
//返回值：文件大小（KB）
//*************************************
int DataLog::getCurrentLogFileSize()
{
    long long filepos = m_outputFile->tellp(); //保存当前文件位置
    m_outputFile->seekp(0,ios_base::end);            //移动到文件尾
    long long filesize = m_outputFile->tellp();
    m_outputFile->seekp(filepos,ios_base::beg);      //恢复文件位置
    return filesize/1024;

}
//获取文件名
string DataLog::getLogFileName()
{
    return m_LogFileName+".txt";
}
//设置文件个数
void DataLog::setFileCount(int count)
{
    m_FileCount = count;
}
//设置文件名
void DataLog::setFileName(string filename)
{
    m_LogFileName = m_strDir+string("\\")+filename;
}
//设置文件大小
void DataLog::setMaxFileSize(int maxsize)
{
    m_MaxFileSize = maxsize;
}

//********************************
//函数名：DataLog::getCurrentTime
//描  述：获取本地时间
//返回值：时间字符串
//*************************************
string DataLog::getCurrentTime()
{
    time_t seconds = time(NULL);    //获取时间
    struct tm *p;
    p = localtime(&seconds);//获取本地时间
    char strTime[100] = {0};
    if(m_timeFormat == NETLOG)
        sprintf(strTime,"%d\\%d\\%d %d.%d.%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
    else
        sprintf(strTime,"%02d-%02d %02d:%02d:%02d",1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
    return string(strTime);
}

