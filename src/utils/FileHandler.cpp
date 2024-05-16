#include "FileHandler.hpp"
#include <fstream>
#include <sstream>

FileHandler::FileHandler(const std::string &m_filename) : m_filename(m_filename)
{
    m_data = readData();
}

std::map<std::string, std::map<std::string, std::string>> FileHandler::readData()
{
    std::ifstream file(m_filename);
    std::string line;
    std::map<std::string, std::map<std::string, std::string>> m_data;
    std::vector<std::string> headers;

    if (std::getline(file, line))
    {
        std::stringstream s(line);
        std::string field;
        while (std::getline(s, field, ','))
        {
            headers.push_back(field);
        }
    }

    while (std::getline(file, line))
    {
        std::vector<std::string> row;
        std::stringstream s(line);
        std::string field;
        while (std::getline(s, field, ','))
        {
            row.push_back(field);
        }
        for (size_t i = 1; i < row.size(); ++i)
        {
            m_data[row[0]][headers[i]] = row[i];
        }
    }

    file.close();
    return m_data;
}

void FileHandler::writeData(const std::map<std::string, std::map<std::string, std::string>> &m_data)
{
    std::ofstream file(m_filename);

    for (const auto &row : m_data)
    {
        file << row.first;
        for (const auto &field : row.second)
        {
            file << "," << field.second;
        }
        file << "\n";
    }

    file.close();
}

std::string FileHandler::getData(const std::string &key, const std::string &subkey)
{
    return m_data[key][subkey];
}
