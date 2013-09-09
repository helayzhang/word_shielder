#include "word_shielder.hh"

int main()
{
    WordShielder myShielder("words_example.dat");
    std::string source("大家好,HelloWorld");
    myShielder.shield(source);
    std::cout << source << std::endl;
    return 0;
}
