#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
class FileOpenException : public std::exception {
public:
    FileOpenException(const char* message) : m_message(message) {}

    virtual const char* what() const noexcept {
        return m_message;
    }

private:
    const char* m_message;
};

struct s_file
{
    std::string name;
    std::vector<char> bin;
};

struct Header
{
    char header[3] = { 'd', 'g', 'r' };
    size_t filecount;
};

class Packet
{
private:
    std::vector<s_file> files;
    std::string _filename;

    Header header;

    void writeBinaryFile(const s_file& f) {
        std::ofstream outFile(f.name, std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Failed to create file for writing binary data: " << f.name << "\n";
            
            throw FileOpenException("Failed to open file");
        }
        outFile.write(f.bin.data(), f.bin.size());
        outFile.close();
        printf("Binary data of %s written to file: _%s\n", f.name.c_str(), f.name.c_str());
    }

public:
    Packet(std::string filename) : _filename(filename) { };

    void addFile(s_file f) { files.push_back(f); }
    void writePacket() {
        std::ofstream file(_filename, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file for writing.\n";
            throw FileOpenException("Failed to open file");
        }

        header.filecount = files.size();
        printf("\nWriting packet HEADER at file: %s, total files packed: %zi\n", _filename.c_str(), header.filecount);

        file.write(reinterpret_cast<const char*>(&header), sizeof(header));

        for (const auto& f : files)
        {
            printf("\nWriting %s name in packet\n", f.name.c_str());

            size_t nameSize = f.name.size();
            file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
            file.write(f.name.data(), nameSize);

            printf("Writing %s binaries in packet\n", f.name.c_str());

            size_t dataSize = f.bin.size();
            file.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
            file.write(reinterpret_cast<const char*>(f.bin.data()), dataSize);
        }

        file.close();
    }
    void loadPacket()
    {
        header.filecount = 0;

        std::ifstream file(_filename, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file for reading.\n";
            throw FileOpenException("Failed to open file");
        }

        printf("\nReading packet HEADER from file: %s\n", _filename.c_str());

        // Read packet header
        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        printf("Packet has: %zi files packed.\n", header.filecount);
        // Read each file
        for (size_t i = 0; i < header.filecount; ++i)
        {
            printf("\nReading packet file: %zi/%zi\n", i + 1, header.filecount);

            std::string name;
            std::vector<char> bin;

            size_t nameSize;
            file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
            name.resize(nameSize);
            file.read(reinterpret_cast<char*>(&name[0]), nameSize);

            printf("Name: %s\n", name.c_str()); // Debugging

            size_t binSize;
            file.read(reinterpret_cast<char*>(&binSize), sizeof(binSize));
            bin.resize(binSize);
            file.read(reinterpret_cast<char*>(bin.data()), binSize);

            printf("Binary size: %zi\n", binSize); // Debugging
            writeBinaryFile({ name, bin });
        }

        file.close();
        return;
    }

};

s_file getFileBin(const std::string& dir, const std::string& name)
{
    s_file sf;
    sf.name = name;

    std::ifstream file(dir + name, std::ios_base::binary); // Open
    if (!file.is_open())
    {
        std::cerr << "Failed to open file for reading.\n"; // Corrected error message
        throw FileOpenException("Failed to open file");
    }

    // Get buffer size
    file.seekg(0, std::ios::end);
    int64_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    sf.bin.resize(size);

    // Write file bins in s_file buffer
    file.read(sf.bin.data(), size);
    file.close();

    printf("-> %s has %lli bytes\n", name.c_str(), size);

    return sf;
}

std::vector<std::string> getFiles(const std::string& dir) {
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(dir)) {
        if (fs::is_regular_file(entry.path())) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

/*
int main(int argc, char* argv[])
{
    Packet packet("test.pkg");

    int args = argc;
    if (args >= 3)
    {
        std::string cmd = argv[1];
        std::string path = argv[2];
        if (!path.ends_with('\\'))
            path.push_back('\\');

        if (cmd == "bake")
        {
            printf("Adding files to packet\n");

            try
            {
                auto files = getFiles(path);

                for (const auto& file : files) 
                {
                    packet.addFile(getFileBin(path, file));
                }

                packet.writePacket();
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                return-1;
            }
        }
    }
    else
    {      
        try
        {
            packet.loadPacket();
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return-1;
        }
    }

    return 0;
}
*/