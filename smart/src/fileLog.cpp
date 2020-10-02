#include "fileLog.hpp"

namespace experis {

FileLog::FileLog(const std::string& a_fileName)
: m_logFile(a_fileName.c_str())
{}

FileLog::~FileLog()
{
    m_logFile.close();
}

void FileLog::WriteToLog(const char* a_module, const char* a_function, int a_lineNum, const std::string& a_msg)
{
	char buffer[20];
	time_t cuurentTime = time(NULL);
 	strftime(buffer, sizeof(buffer), "%H:%M:%S %d-%m-%Y", localtime(&cuurentTime));
 	
    m_logFile << "Current time: " << buffer;
    m_logFile << "\nModule name: " << a_module;
    m_logFile << "\nFunction name: " << a_function;
    m_logFile << "\nLine number: " << a_lineNum;
    m_logFile << "\nMessage: " << a_msg;
    m_logFile << "\n\n";

    m_logFile.flush();
}

} // experis