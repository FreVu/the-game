#include "FileSystemHelper.hpp"

#include <algorithm>
#include <cctype>

namespace FileSystemHelper
{

std::vector<std::filesystem::directory_entry> getSubDirectories(const std::filesystem::path& directoryPath)
{
    std::vector<std::filesystem::directory_entry> directories;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        if (entry.is_directory())
        {
            directories.emplace_back(entry);
        }
    }
    return directories;
}

std::string getRandomPng(const std::string& directoryPath)
{
    std::vector<std::string> pngFiles;

    // Collect all .png files
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".png")
        {
            pngFiles.push_back(entry.path().string());
        }
    }

    if (pngFiles.empty())
    {
        return "";
    }

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, pngFiles.size() - 1);

    // Pick random index
    return pngFiles[dist(gen)];
}

std::vector<std::filesystem::directory_entry> getRandomDirectories(const std::string& directoryPath, std::size_t count)
{
    if (count == 0)
    {
        return {};
    }

    auto directories = getSubDirectories(directoryPath);

    if (directories.empty())
    {
        return {};
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(directories.begin(), directories.end(), gen);

    if (count < directories.size())
    {
        directories.resize(count);
    }

    return directories;
}

std::filesystem::directory_entry getRandomDirectory(const std::string& directoryPath)
{
    auto directories = getRandomDirectories(directoryPath, 1);
    if (directories.empty())
    {
        return std::filesystem::directory_entry();
    }
    return directories.front();
}

std::string getFileContent(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the entire file into the buffer
    file.close();

    return buffer.str();
}

std::vector<std::string> readLines(const std::string& filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return lines;  // empty vector
    }

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

int getRandomNumberFromSection(const std::string& filepath, int sectionId)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        return -1;
    }

    auto section = std::to_string(std::abs(sectionId) % 1000);
    if (section.size() < 3)
    {
        section = std::string(3 - section.size(), '0') + section;
    }

    const std::string targetHeader = "[" + section + "]";
    std::vector<int> numbers;
    std::string line;
    bool inSection = false;

    const auto trim = [](std::string& value)
    {
        auto notSpace = [](int ch) { return !std::isspace(ch); };
        value.erase(value.begin(), std::find_if(value.begin(), value.end(), notSpace));
        value.erase(std::find_if(value.rbegin(), value.rend(), notSpace).base(), value.end());
    };

    while (std::getline(file, line))
    {
        trim(line);

        if (line.empty())
        {
            if (inSection && !numbers.empty())
            {
                break;
            }
            continue;
        }

        if (line.front() == '[' && line.back() == ']')
        {
            if (inSection && !numbers.empty())
            {
                break;
            }
            inSection = (line == targetHeader);
            continue;
        }

        if (inSection)
        {
            try
            {
                numbers.push_back(std::stoi(line));
            }
            catch (const std::exception&)
            {
                // Ignore lines that cannot be parsed as integers
            }
        }
    }

    file.close();

    if (numbers.empty())
    {
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dist(0, numbers.size() - 1);
    return numbers[dist(gen)];
}

}  // namespace FileSystem
