#pragma once
TString::TString(const char *str) {
    if (str == nullptr) {
        return;
    }
    unsigned long long size = 0;
    while (str[size] != 0) {
        ++size;
    }
    Data = new char[size + 1];
    Size = size;
    Capacity = size + 1;
    for (unsigned long long i = 0; i < Size; ++i) {
        Data[i] = str[i];
    }
    Data[size] = 0;
}
TString::TString(const TString& other) {
    Data = new char[other.Size + 1];
    Size = other.Size;
    Capacity = Size + 1;
    for (unsigned long long i = 0; i < other.Size; ++i) {
        Data[i] = other.Data[i];
    }
    Data[Size] = 0;
}
bool TString::operator < (const TString& other) const {
    unsigned long long i = 0;
    while (i < other.Size && i < Size) {
        if (Data[i] < other.Data[i]) {
            return true;
        }
        if (Data[i] > other.Data[i]) {
            return false;
        }
        ++i;
    }
    return Size < other.Size;
}
TString& TString::operator = (const TString& other) {
    if (Data != nullptr) {
        delete[] Data;
    }
    Data = new char[other.Size + 1];
    Size = other.Size;
    Capacity = Size + 1;
    for (unsigned long long i = 0; i < other.Size; ++i) {
        Data[i] = other.Data[i];
    }
    Data[Size] = 0;
    return *this;
}

TString& TString::operator = (TString&& other) {
    if (this == & other) {
        return *this;
    }
    if (Data != nullptr) {
        delete[] Data;
    }
    Data = other.Data;
    Size = other.Size;
    Capacity = other.Capacity;
    other.Data = nullptr;
    other.Size = 0;
    other.Capacity = 0;
    return *this;
}

TString::TString(TString&& other) {
    Data = other.Data;
    Size = other.Size;
    Capacity = other.Capacity;
    other.Data = nullptr;
    other.Size = 0;
    other.Capacity = 0;
}
TString& TString::operator = (const char *str) {
    if (str == nullptr) {
        Clear();
        return *this;
    }
    unsigned long long size = 0;
    while (str[size] != 0) {
        ++size;
    }
    if (Capacity > size) {
        for (unsigned long long i = 0; i < size; ++i) {
            Data[i] = str[i];
        }
        Data[size] = 0;
        Size = size;
        return *this;
    }
    if (Data != nullptr) {
        delete[] Data;
    }
    Data = new char[size + 1];
    Capacity = size + 1;
    Size = size;
    for (unsigned long long i = 0; i < size; ++i) {
        Data[i] = str[i];
    }
    Data[size] = 0;
    return *this;
}
char* TString::Buffer() {
    return Data;
}
bool TString::operator == (const char *str) const {
    unsigned long long i = 0;
    if (str == nullptr) {
        return false;
    }
    while (i < Size && str[i] != 0) {
        if (str[i] != Data[i]) {
            return false;
        }
        ++i;
    }
    return Size == i;
}

bool TString::operator == (const char c) const {
    if (Size == 1 && Data[0] == c) {
        return true;
    }
    return false;
}

TString::operator char* () const {
    char * res = new char[Size + 1];
    for (unsigned long long i = 0; i < Size; ++i) {
        res[i] = Data[i];
    }
    res[Size] = 0;
    return res;
}

bool TString::operator == (const TString& other) const {
    if (other.Size != Size) {
        return false;
    }
    for (unsigned long long i = 0; i < Size; ++i) {
        if (Data[i] != other.Data[i]) {
            return false;
        }
    }
    return true;
}
void TString::UpdateSize() {
    if (Data == nullptr) {
        Size = 0;
        return;
    }
    Size = 0;
    while (Data[Size] != 0) {
        ++Size;
    }
    return;
}
std::ostream& operator << (std::ostream& os, const TString& str) {
    if (str.Data != nullptr) {
        os << str.Data;
    }
    return os;
}
/*
// slow, but dynamic realization of operator >>
std::istream& operator >> (std::istream& is, TString& str) {
    char c;
    str.Size = 0;
    bool got_input = false;
    while (is.read(&c,1)) { // i thought is.read will be faster than is.get, but seems like they both are pretty slow compared to is >> char*
        if (c == ' ' || c == '\n' || c == 0) {
            if (got_input) {
                break;
            } else {
                continue;
            }
        }
        str.PushBack(c);
        got_input = true;
    }
    return is;
}
*/
// static operator>> : if input size increases str.Capacity, segfault occurs

std::istream& operator >> (std::istream& is, TString& str) {
    static const int BUFF_SIZE = 256;
    if (str.Data == nullptr) {
        str.Reallocate(BUFF_SIZE+1);
    }
    is >> str.Buffer();
    str.UpdateSize();
    return is;
}

const char* TString::CString() const {
    return Data;
}

void TString::ToLower() {
    if(Data == nullptr) {
        return;
    }
    int diff = 'a' - 'A';
    for (unsigned long long i = 0; i< Size; ++i) {
        if (Data[i] >= 'A' && Data[i] <= 'Z') {
            Data[i] += diff;
        }
    }
    return;
}