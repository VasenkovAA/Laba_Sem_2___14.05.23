#pragma once
#include "CMass.h"

class TStringMass {
private:
    int Count;
    std::string* Item;
public:
    std::string getItem(int Index);
    int getCount();
    bool AddItem(std::string tmp, bool AddSame = 0);
    void Out();
    void DeleteItemByIndex(int Index1);
    void Dispose();
    TStringMass();
    TStringMass(TStringMass& tmp);
    ~TStringMass();
    TStringMass& operator+=(const TStringMass& tmp);
    std::string& operator[](int index);
    template<typename T>
    friend std::ostream& operator<<(std::ostream& os, TMass<T>& tmp);
    template<typename T>
    friend class TTree;
};

class TData {
public:
    int id;
    std::string Caption;
    std::string Category;
    std::string ContextInfo;
    TData();
    TData(int _id, std::string _caption);
    TData(const TData& tmp);
    ~TData();
    TData& operator=(const TData& tmp);
    friend std::ostream& operator<<(std::ostream& os, TData& tmp);
    friend bool TDataCMP(TData t, std::string str);
    friend class TSpecificationMass;
};

bool TDataCMPstr(TData t, std::string str);
int TDataCMP(TData& tmp1, TData& tmp2);
int StrCMP(std::string& t1, std::string& t2);

template<typename T>
int TDataCMP(TData& tmp1, T& tmp2) {
    return ((tmp1.Caption == tmp2) || (tmp1.Caption == "No"));
}

class TSpecificationMass {
    TData* mass;
    int count;
public:
    int getCount();
    TSpecificationMass(TSpecificationMass& tmp);
    TSpecificationMass();
    ~TSpecificationMass();
    void add(TData& data);
    TData getData(int i);    
    TStringMass& getCaptionMass();
    friend std::ostream& operator<<(std::ostream& os, TSpecificationMass& tmp);
};
