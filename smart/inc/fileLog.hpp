#ifndef FILE_LOG_HPP
#define FILE_LOG_HPP

#include <string>
#include <fstream>

#define LOGINFO(a_fileLog, a_msg) a_fileLog.WriteToLog(__FILE__, __FUNCTION__, __LINE__, a_msg)

namespace experis {

class FileLog {
public:
    FileLog(const std::string& a_fileName);
    ~FileLog();

    void WriteToLog(const char* a_module, const char* a_function, int a_lineNum, const std::string& a_msg);

private:
    std::ofstream m_logFile;
};

} // experis

#endif