#include <emu.hpp>


int main(int argc, char** argv) {
    if(argc != 2) {
        throw std::runtime_error("Wrong command line parameters");
    }

    Emu emu = Emu();
    const char* filePath = argv[1]; 
    emu.run(filePath);
    return 0;
}