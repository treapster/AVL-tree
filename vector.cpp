#pragma once
#include <stdexcept>

template <typename T>
void TVector<T>::Init0() {
    Size = 0;
    Capacity = 0;
    Data = nullptr;
}
template <typename T>
TVector<T>::TVector() {
    Init0();
}
template <typename T>
TVector<T>::TVector(unsigned long long size) {
    if (size == 0) {
        Init0();
        return;
    }
    this -> Size = size;
    Capacity = size;
    Data = new T[Capacity];
}
template <typename T>
TVector<T>::TVector(unsigned long long size, T value) {
    if (size == 0) {
        Init0();
        return;
    }
    this -> Size = size;
    Capacity = size;
    Data = new T[Capacity];
    for (unsigned long long i = 0; i < size; i++) {
        Data[i] = value;
    }
}

template <typename T>
void TVector<T>::Assign(T value) {
    for (unsigned long long i = 0; i < Size; ++i) {
        Data[i] = value;
    }
}

template <typename T>
void TVector<T>::Reallocate(unsigned long long newcapacity) {
    T * newdata = new T[newcapacity];
    for (unsigned long long i = 0; i < Size; ++i) {
        newdata[i] = Data[i];
    }
    if (Data != nullptr) {
        delete[] Data;
    }

    Data = newdata;
    Capacity = newcapacity;

}
template <typename T>
void TVector<T>::PushBack(T value) {
    if (Size == Capacity) {
        if (Size != 0)
            Reallocate(Size * 2);
        else
            Reallocate(1);
    }
    Data[Size] = value;
    ++Size;
}
template <typename T>
T & TVector<T>::operator[](unsigned long long index) {
    if (index >= Size) {
        throw std::out_of_range("Vector outside of range!");
    } else {
        return Data[index];
    }
}
template <typename T>
void TVector<T>::PopBack() {
    if (Size != 0) {
        Size--;
        if (Size * 4 < Capacity) {
            Reallocate(Size * 2);
        }
    }
    return;
}
template <typename T>
void TVector<T>::Swap(TVector & other) {
    T * tempdata = Data;
    int tempsize = Size;
    int tempcap = Capacity;
    Data = other.Data;
    Size = other.Size;
    Capacity = other.Capacity;
    other.Data = tempdata;
    other.Size = tempsize;
    other.Capacity = tempcap;
}
template <typename T>
unsigned long long TVector<T>::Length() const {
    return Size;
}
template <typename T>
void TVector<T>::Clear() {
    if (Data != nullptr) {
        delete[] Data;
    }
    Size = 0;
    Capacity = 0;
    Data = nullptr;
}
template <typename T>
TVector<T>::~TVector() {
    Clear();
}
template <>
TVector<char>::TVector(unsigned long long size) {
    if (size == 0) {
        Init0();
        return;
    }
    this -> Size = size;
    Capacity = size + 1;
    Data = new char[Capacity];

}
template <>
void TVector<char>::Reallocate(unsigned long long newcapacity) {
    char * newdata = new char[newcapacity];
    for (unsigned long long i = 0; i < Size; ++i) {
        newdata[i] = Data[i];
    }
    if (Data != nullptr) {
        delete[] Data;
    }

    Data = newdata;
    Capacity = newcapacity;
}
template <>
void TVector<char>::PushBack(char value) {
    if (Size + 1 >= Capacity) {
        if (Capacity > 0)
            Reallocate(Capacity * 2);
        else
            Reallocate(2);
    }
    Data[Size] = value;
    Data[Size + 1] = 0;
    ++Size;
}
template <>
void TVector<char>::PopBack() {
    if (Size != 0) {
        --Size;
        if (Size * 4 < Capacity) {
            Reallocate(Size * 2);
        }
        Data[Size] = 0;
    }
    return;
}
template <>
char & TVector<char>::operator[](unsigned long long index) {
    if (index > Capacity) {
        throw std::out_of_range("String outside of allocated space!");
    } else {
        return Data[index];
    }
}
template <>
TVector<char>::TVector(unsigned long long size, char value) {
    if (size == 0) {
        Init0();
        return;
    }
    this -> Size = size;
    Capacity = size + 1;
    Data = new char[Capacity];
    for (unsigned long long i = 0; i < size; i++) {
        Data[i] = value;
    }
    Data[Size] = 0;
}