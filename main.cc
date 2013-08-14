#include "word_shielder.hh"

int main()
{
    WordShielder myShielder("words_example.dat");
    std::string aaa("大家好哈哈哈111");
    myShielder.shield(aaa);
    std::cout << aaa << std::endl;
    return 0;
}
