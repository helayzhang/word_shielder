利用Trie-Tree实现敏感词屏蔽功能, C++独立模块.

使用向导：

1. 敏感词库，当前只支持一行一个词汇的文本。

2. 使用示例(见main.cc):

    std::string aaa("大家好哈哈哈111");
    
    WordShielder myShielder("words_example.dat");
    
    myShielder.shield(aaa);
    
    std::cout << aaa << std::endl; // Out put: 大家好***111
