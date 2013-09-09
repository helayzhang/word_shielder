###利用Trie-Tree实现敏感词屏蔽功能.

####HOW TO USE:

1. 敏感词库，当前只支持一行一个词汇的文本文件作为屏蔽词库。

2. 使用示例(见example.cc):

    WordShielder myShielder("words_example.dat");
    
    std::string source("大家好,HelloWorld");
    
    myShielder.shield(source);