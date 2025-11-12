#pragma once

#include <vector>
#include <string>
#include <random>

#include <filesystem>
#include <fstream>

namespace FileSystemHelper
{

std::vector<std::filesystem::directory_entry> getSubDirectories(const std::filesystem::path& directoryPath);

std::string getRandomPng(const std::string& directoryPath);

std::vector<std::filesystem::directory_entry> getRandomDirectories(const std::string& directoryPath, std::size_t count);

std::filesystem::directory_entry getRandomDirectory(const std::string& directoryPath);

std::string getFileContent(const std::string& filepath);

std::vector<std::string> readLines(const std::string& filename);

int getRandomNumberFromSection(const std::string& filepath, int sectionId);

}  // namespace FileSystem
