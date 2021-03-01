#include "fileLog.hpp"
#include "mutexLocker.hpp"
#include <fstream>
using namespace std;

namespace experis {

FileLog::FileLog()
: m_mtx()
{}

void FileLog::WriteToLog(const char* a_module, const char* a_function, int a_lineNum, std::ofstream& a_logName, const std::string& a_msg)
{
	MutexLocker locker(m_mtx);
    
    char buffer[20];
	time_t cuurentTime = time(NULL);
 	strftime(buffer, sizeof(buffer), "%H:%M:%S %d-%m-%Y", localtime(&cuurentTime));
 	
    a_logName << "Current time: " << buffer;
    a_logName << "\nModule name: " << a_module;
    a_logName << "\nFunction name: " << a_function;
    a_logName << "\nLine number: " << a_lineNum;
    a_logName << "\nMessage: " << a_msg;
    a_logName << "\n\n";

    a_logName.flush();
}

} // experis