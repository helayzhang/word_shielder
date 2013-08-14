/*******************************************************************************
 *
 *      @file: trie.hh
 *
 *      @brief: 
 *
 *      @author: Helay Zhang.
 *               helayzhang@gmail.com
 *
 *      COPYRIGHT (C) 2013.
 *
 ******************************************************************************/
#ifndef TRIE_hh_INCLUDED
#define TRIE_hh_INCLUDED

#include <functional>
#include <vector>
#include <cassert>

template< typename ValueType,
          typename EqualValue = std::equal_to<ValueType> >
class Trie {
private:
    class TrieNode;
    typedef typename std::vector<TrieNode*> TrieNodeVec;
    typedef typename TrieNodeVec::iterator  TrieNodeVecIterator;
    typedef void (*FUNC_PTR_TRAVERSAL_VISIT)(TrieNode *);
public:
    Trie():mRootNode() 
    {
        mRootNode = new TrieNode;
    }
    ~Trie() 
    {
        traversalPostOrder(mRootNode, freeNode);
    }

    void shield(std::vector<ValueType> &target, ValueType replace)
    {
        bool is_matched = false;
        TrieNode *t = NULL, *n = NULL;
        unsigned int i = 0, j = 0, k = 0;

        while (i < target.size()) {
            t = mRootNode;
            is_matched = false;

            j = 0;
            while ((n = nextNodeByValue(t, target[i+j])) and (i + j < target.size())) {
                j++;

                // matched a word
                if (n->isContentTail()) {
                    for (k = 0; k < j; ++k)
                        target[i+k] = replace;

                    is_matched = true;
                    break;
                }
                t = n;
            }

            if (is_matched) {
                i += j;
            }
            else {
                i++;
            }
        }
    }

private:
    class TrieNode {
    public:
        TrieNode():mIsContentTail(false), mParentNode(NULL), mNextNodes() {}
        TrieNode(ValueType v):mValue(v), mIsContentTail(false), mParentNode(NULL), mNextNodes() {}
        ~TrieNode() {}

        const ValueType& getValue() const { return mValue; }

        bool isContentTail() const { return mIsContentTail; }
        void setContentTail() { mIsContentTail = true; }

        void setParentNode(TrieNode* parentNode) { mParentNode = parentNode; }

        TrieNodeVecIterator nextNodesBegin() { return mNextNodes.begin(); }
        TrieNodeVecIterator nextNodesEnd() { return mNextNodes.end(); }
        TrieNodeVec* nextNodes() { return &mNextNodes; }
        
    private:
        ValueType mValue;
        bool mIsContentTail;
        TrieNode* mParentNode;
        TrieNodeVec mNextNodes;
    };

public:
    void insertContent(const std::vector<ValueType> &content)
    {
        TrieNode* t = mRootNode;
        for (unsigned int i = 0; i < content.size(); ++i) {
            const ValueType &value = content[i];
            TrieNodeVec* nexts = t->nextNodes();

            unsigned int j;
            for (j = 0; j < nexts->size(); ++j) {
                if (value == (*nexts)[j]->getValue()) {
                    break;
                }
            }

            if (j == nexts->size()) {
                TrieNode* newNode = new TrieNode(value);
                nexts->push_back(newNode);
                newNode->setParentNode(t);
                t = newNode;
            }
            else {
                t = (*nexts)[j];
            }

            if (i == content.size() - 1) {
                t->setContentTail();
            }
        }
    }

private:
    static void traversalPostOrder(TrieNode* node, FUNC_PTR_TRAVERSAL_VISIT visit) 
    {
        if (node == NULL) return;
        for (size_t i = 0; i < node->nextNodes()->size(); ++i) {
            traversalPostOrder(node->nextNodes()->at(i), visit);
        }
        visit(node);
    }

    static void freeNode(TrieNode* node) 
    {
        assert(node);
        delete node;
    }

    static TrieNode* nextNodeByValue(TrieNode* node, ValueType value)
    {
        for (unsigned int i = 0; i < node->nextNodes()->size(); ++i) {
            TrieNode* current = node->nextNodes()->at(i);
            if (current->getValue() == value)
                return current;
        }
        return NULL;
    }

private:
    TrieNode* mRootNode;
};

#endif
