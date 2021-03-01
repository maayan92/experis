#ifndef FILE_LOG_HPP
#define FILE_LOG_HPP

#include <string>
#include <fstream>
#include "mutex.hpp"
#include "singleton.hpp"

#define LOGINFO(a_fileLog, a_logName, a_msg) a_fileLog.WriteToLog(__FILE__, __FUNCTION__, __LINE__, a_logName, a_msg)

namespace experis {

class FileLog : private Uncopyable {
    friend class advcpp::Singleton<FileLog>;
public:
    void WriteToLog(const char* a_module, const char* a_function, int a_lineNum, std::ofstream& a_logName, const std::string& a_msg);

private:
    FileLog();

private:
    experis::Mutex m_mtx;
};

} // experis

#endif