#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>
#include <vector>
#include <map>

class FileHandler
{
public:
    FileHandler(const std::string &m_filename);
    std::map<std::string, std::map<std::string, std::string>> readData();
    void writeData(const std::map<std::string, std::map<std::string, std::string>> &m_data);
    std::string getData(const std::string &key, const std::string &subkey);

private:
    std::string m_filename;
    std::map<std::string, std::map<std::string, std::string>> m_data;
};

#endif // FILEHANDLER_HPP