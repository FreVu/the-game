#include <string>
#include <filesystem>

class Outfit
{
public:

    explicit Outfit(std::filesystem::directory_entry directory);

    std::string getDescription() const;
    std::string getCurrentFile() const;

    void flip();
    void undress();

private:

    std::filesystem::directory_entry _directory;
    int _currentStep = 0;
    bool _front      = true;
};
