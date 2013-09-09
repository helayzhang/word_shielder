###利用Trie-Tree实现敏感词屏蔽功能.

####HOW TO USE:

目前只支持一行一个词汇的文本文件作为屏蔽词库。使用示例(见example.cc):

    WordShielder myShielder("words_example.dat");
    std::string source("大家好,HelloWorld");
    myShielder.shield(source);
    
####NOTE:

代码中需要依赖utf8和unicode互转，本repo中使用的是本人另一个repo提供的代码，见[utf8unicode](https://github.com/helayzhang/utf8unicode)