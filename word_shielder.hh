/*******************************************************************************
 *
 *      @file: word_shielder.hh
 *
 *      @brief: 
 *
 *      @author: Helay Zhang.
 *               helayzhang@gmail.com
 *
 *      COPYRIGHT (C) 2013.
 *
 ******************************************************************************/
#ifndef WORD_SHIELDER_hh_INCLUDED
#define WORD_SHIELDER_hh_INCLUDED

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "trie.hh"
#include "utf8unicode.hh"

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

class WordShielder {
private:
    static const unsigned int DEFAULT_REPLACE_WORD = 0x0000002A;
public:
    /* Create a WordShielder, you need a file which contain all the word you need to shield,
     * NOTICE: Now we can only support one word per line in the file. */
    WordShielder(const char* filePath, unsigned int replaceWord = DEFAULT_REPLACE_WORD)
        : mReplaceWord(replaceWord), mWordFilePath(filePath), mWordDict() 
    { 
        createDict(); 
    }
    WordShielder(const std::string& filePath, unsigned int replaceWord = DEFAULT_REPLACE_WORD)
        : mReplaceWord(replaceWord), mWordFilePath(filePath), mWordDict() 
    { 
        createDict(); 
    }
    ~WordShielder() {}

    void setReplaceWord(unsigned int replaceWord) { mReplaceWord = replaceWord; }
    unsigned int getReplaceWord() const { return mReplaceWord; }

    void shield(std::string &word)
    {
        std::vector<unsigned int> unicodeWord;
        if (Utf8Unicode::utf8_to_unicode(word, unicodeWord)) {
            mWordDict.shield(unicodeWord, mReplaceWord);
            Utf8Unicode::unicode_to_utf8(unicodeWord, word);
        }
    }
private:
    void createDict()
    {
        std::ifstream wordFile(mWordFilePath);
        std::string line;
        while (std::getline(wordFile, line)) {
            trim(line);
            if (not line.empty()) {
                std::vector<unsigned int> unicodeLine;
                if (Utf8Unicode::utf8_to_unicode(line, unicodeLine)) {
                    mWordDict.insertContent(unicodeLine);
                }
            }
        }
    }

private:
    unsigned int mReplaceWord;
    std::string mWordFilePath;
    Trie<unsigned int> mWordDict;
};

#endif
