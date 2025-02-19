#include <emu.hpp>


int main(int argc, char** argv) {
    if(argc != 2) {
        throw std::runtime_error("Wrong command line parameters");
    }

    const char* filePath = argv[1]; 

    Emu emu = Emu();
    emu.run(filePath);
    return 0;
}