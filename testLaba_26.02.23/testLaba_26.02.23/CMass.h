#pragma once
#include <iostream>
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED   "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[33m"
#define BLUE "\033[34m"

template<typename T>
class TMass {
private:
    int Count;
    T** Item;
    int (*cmp)(T&, T&);
    bool LinkCheck(T& tmp);
public:
    T* getItem(int Index);
    int getCount();
    void setCmp(int (*_cmp)(T&, T&));
    bool AddItem(T& tmp, bool AddSame = 1);
    void Out();
    void DeleteAllItemByType(T& tmp);
    void DeleteItemByType(T& tmp);
    void DeleteItemByIndex(int Index1);
    int FaindFirst(T& tmp);
    TMass<T>& FaindAll(T& tmp);
    void Dispose();

    TMass();
    TMass(int (*_cmp)(T&, T&));
    TMass(TMass& tmp);
    ~TMass();
    TMass<T>& operator+=(const TMass<T>& tmp);
    T& operator[](int index);

    template<typename T>
    friend std::ostream& operator<<(std::ostream& os, TMass<T>& tmp);
    template<typename T>
    friend class TTree;
    template<typename T>
    friend class TNode;
};
template<typename T>
bool TMass<T>::LinkCheck(T& tmp) {
    for (int i = 0; i < Count; i++) {
        if (Item[i] == &tmp) { return 1; }

    }
    return 0;
}
template<typename T>
T* TMass<T>::getItem(int Index) {
    if ((Index >= 0) && (Index < Count)) {
        return (Item[Index]);
    }
    else { throw; }//-----------------------------------------------------
}
template<typename T>
int TMass<T>::getCount() { return Count; }
template<typename T>
void TMass<T>::setCmp(int (*_cmp)(T&, T&)) {
    cmp = _cmp;
}
template<typename T>
bool TMass<T>::AddItem(T& tmp, bool AddSame) {
    if (cmp == nullptr) {
        std::cerr << typeid(*this).name() << "    (cmp) function == nullptr";
        throw std::logic_error("(cmp) function == nullptr");
    }
    if (AddSame == 0) { if (FaindFirst(tmp) > -1) { return 0; } }
    T** Item_tmp = new T * [Count + 1];
    int i = 0;
    for (i; i < Count; i++) {
        if (cmp(*Item[i], tmp) < 0) { Item_tmp[i] = Item[i]; }
        else break;
    }
    Item_tmp[i] = &tmp;
    for (i; i < Count; i++) { Item_tmp[i + 1] = Item[i]; }
    delete Item;
    Item = Item_tmp;
    Count++;
    return true;
}
template<typename T>
void TMass<T>::Out() {
    if (Count == 0) { std::cout << "Mass count == 0" << std::endl; }
    else {
        for (int i = 0; i < Count; i++) {
            std::cout << "Ilement [" << i << "] = " << *Item[i] << std::endl;
        }
    }
}
template<typename T>
void TMass<T>::DeleteAllItemByType(T& tmp) {
    TMass<T>Faind = FaindAll(tmp);
    for (int i = 0; i < Faind.Count; i++) {
        DeleteItemByType(*Faind.Item[i]);
    }
}
template<typename T>
void TMass<T>::DeleteItemByType(T& tmp) {
    int Index = FaindFirst(tmp);
    DeleteItemByIndex(Index);
}
template<typename T>
void TMass<T>::DeleteItemByIndex(int Index1) {
    if ((Index1 > -1) && (Index1 < Count) && (Count > 0)) {
        T** Item_tmp = new T * [Count - 1];
        int i = 0;
        for (i; i < Index1; i++) { Item_tmp[i] = Item[i]; }
        for (i; i < Count; i++) { Item_tmp[i] = Item[i + 1]; }
        delete Item;
        Item = Item_tmp;
        Count--;
    }
    else {
        if (Count == 0) {
            throw std::logic_error("Count == 0, can no deleted");
        }
        if ((Index1 > -1) && (Index1 < Count)) {
            throw std::logic_error("No index in mass");
        }
    }
}
template<typename T>
int TMass<T>::FaindFirst(T& tmp) {
    int left = 0;
    int right = Count;
    int search = -1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (cmp(*Item[mid], tmp) == 0) {
            search = mid;
            break;
        }
        if (cmp(*Item[mid], tmp) > 0)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return search;
}
template<typename T>
TMass<T>& TMass<T>::FaindAll(T& tmp) {
    int n = FaindFirst(tmp);
    int i = n;
    TMass<T>* out = new TMass<T>;
    out->cmp = cmp;
    while (1) {
        if ((i >= 0) && (i < Count)) {
            if (cmp(*Item[i], tmp) == 0) {
                out->AddItem(*Item[i], 1);
                i++;
            }
            else { break; }
        }
        else { break; }
    }
    i = n - 1;
    while (1) {
        if ((i >= 0) && (i < Count)) {
            if (cmp(*Item[i], tmp) == 0) {
                out->AddItem(*(Item[i]));
                i--;
            }
            else { break; }
        }
        else { break; }
    }
    return *out;
}
template<typename T>
T& TMass<T>::operator[](int index) {
    if (index > -1 && index < Count) {
        return *Item[index];
    }
    else throw std::logic_error("Index not faund");
}
template<typename T>
TMass<T>::TMass() :cmp(nullptr), Count(0), Item(nullptr) { }
template<typename T>
TMass<T>::TMass(int (*_cmp)(T&, T&)) :cmp(nullptr), Count(0), Item(nullptr) {
    cmp = _cmp;
    Count = 0;
}
template<typename T>
TMass<T>::TMass(TMass& tmp) :cmp(nullptr), Count(tmp.Count), Item(nullptr) {
    Item = new T * [Count];
    for (int i = 0; i < Count; i++) {
        Item[i] = tmp.Item[i];
    }
    cmp = tmp.cmp;
}
template<typename T>
TMass<T>::~TMass() {
    //cout << "co" << this->Count << endl;
    delete Item;
    //cout << "co" << this->Count << endl;
}
template<typename T>
TMass<T>& TMass<T>::operator+=(const TMass<T>& tmp) {
    for (int i = 0; i < tmp.Count; i++)
        AddItem(*tmp.Item[i]);
    return *this;
}
template<typename T>
void TMass<T>::Dispose() {
    delete Item;
    Item = nullptr;
    Count = 0;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, TMass<T>& tmp) {
    if (tmp.Count == 0) { os << ORANGE << "\tMass count == 0" << RESET << std::endl; }
    else {
        for (int i = 0; i < tmp.Count; i++) {
            os << BLUE << "\tIlement [" << i << "]" << std::endl << RESET << *tmp.Item[i] << std::endl;
        }
    }
    return os;

}
