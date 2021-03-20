#pragma once
#include <iostream>
#include "vector.h"
class TString: public TVector<char>{
public:
    TString(){}
    TString(unsigned long long size):TVector(size, 0){}
    TString(unsigned long long size, char value):TVector(size, value){}
    TString(const char* str);
    TString(const TString& other);
    TString(TString&& other);
    ~TString(){}
    TString& operator=(const TString& other);
    TString& operator=(TString&& other);
    TString& operator=(const char* other);
    bool operator==(const char* str) const;
    bool operator==(const char c) const;
    bool operator<(const TString& other)const;
    bool operator==(const TString& other) const;
    operator char*() const;
    const char* CString() const;
    char* Buffer();
    void ToLower();
    void UpdateSize();
    friend std::ostream& operator<<(std::ostream& os, const TString& str);
    friend std::istream& operator>>(std::istream& is,TString& str);
};
#include "string.cpp"