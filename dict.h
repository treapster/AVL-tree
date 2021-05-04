#pragma once
#include <iostream>
#include <fstream>


template<typename T1, typename T2>
struct TPair{
    T1 first;
    T2 second;
};
template<typename Key, typename Val> struct TNode{
    TNode(){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        data = new TPair<Key, Val>;
        balance = 0;
    }
    ~TNode(){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        if(data != nullptr) {
            delete data;
        }
    }
    TNode<Key, Val>* parent;
    TNode<Key, Val>* left;
    TNode<Key, Val>* right;
    TPair<Key, Val>* data;
    char balance;
};
template<typename Key, typename Val>
class TDictIterator{
public:
    TDictIterator(){
        to=nullptr;
    }
    TDictIterator(TNode<Key,Val>* node):to(node){}
    TPair<const Key, Val>& operator*(){
        return (TPair<const Key, Val>&)*(to->data);
    }
    TPair<const Key, Val>* operator->() {
        return  (TPair<const Key, Val>*)to->data;
    }
    bool operator==(const TDictIterator& other){
        return to==other.to;
    }
private:
    TNode<Key,Val>* to;
};
template<typename Key, typename Val>
class TDict{
public:
    TDict();
    ~TDict();
    TDictIterator<Key, Val> begin();
    TDictIterator<Key, Val> end();
    TDictIterator<Key, Val> Find(const Key& key);
    TDictIterator<Key, Val> FindOrCreate(const Key& key);
    Val& operator[](const Key& key);
    bool Erase(const Key& key);
    bool Save(const char* path);
    bool Load(const char* path);
    void PrintTree();
    void Clear();
    int Size();
private:
    void FixRRDisbalance(TNode<Key, Val>* node);
    void FixRLDisbalance(TNode<Key, Val>* node);
    void FixLRDisbalance(TNode<Key, Val>* node);
    void FixLLDisbalance(TNode<Key, Val>* node);
    void Balance(TNode<Key, Val>* node);
    void DeleteNode(TNode<Key, Val>* node);
    void EraseNode(TNode<Key, Val>* node);
    void BalanceAfterDeletion(TNode<Key, Val>* node);
    void PrintNode(TNode<Key, Val>* node, int depth);
    void WriteNode(TNode<Key, Val>* node, std::ostream& file);
    void WriteHeader(std::ostream& file);
    bool HeaderGood(std::istream& file);
    TNode<Key, Val>* ReadNode(TNode<Key, Val>* parent, std::istream& file);
    TNode<Key, Val>* FindNode(TNode<Key, Val>* node,const Key& key);
    TNode<Key, Val>* Insert(TNode<Key, Val>* node,const Key& key);
    const static char* FileHeader;
    TNode<Key, Val>* root;
    int Size_;
};
template<typename Key, typename Val> const char* TDict<Key, Val>::FileHeader = "treapster";
#include "dict.cpp"
