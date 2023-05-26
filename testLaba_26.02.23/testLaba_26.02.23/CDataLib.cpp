#include "CDataLib.h"

std::string TStringMass::getItem(int Index) {
    if ((Index >= 0) && (Index < Count)) {
        return (Item[Index]);
    }
    else { throw; }//-----------------------------------------------------
}
int TStringMass::getCount() { return Count; }
bool TStringMass::AddItem(std::string tmp, bool AddSame) {
    std::string* Item_tmp = new std::string[Count + 1];
    int i = 0;
    for (i; i < Count; i++) {
        Item_tmp[i] = Item[i];
    }
    Item_tmp[Count] = tmp;
    delete[] Item;
    Item = Item_tmp;
    Count++;
    return true;
}
void TStringMass::Out() {
    if (Count == 0) { std::cout << "Mass count == 0" << std::endl; }
    else {
        for (int i = 0; i < Count; i++) {
            std::cout << "Ilement [" << i << "] = " << Item[i] << std::endl;
        }
    }
}
void TStringMass::DeleteItemByIndex(int Index1) {
    if ((Index1 > -1) && (Index1 < Count) && (Count > 0)) {
        std::string* Item_tmp = new std::string[Count - 1];
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
void TStringMass::Dispose() {
    delete Item;
    Item = nullptr;
    Count = 0;
}
TStringMass::TStringMass() :Count(0), Item(nullptr) { }
TStringMass::TStringMass(TStringMass& tmp) : Count(tmp.Count), Item(nullptr) {
    Item = new std::string[Count];
    for (int i = 0; i < Count; i++) {
        Item[i] = tmp.Item[i];
    }
}
TStringMass::~TStringMass() {
    delete[] Item;
}
TStringMass& TStringMass::operator+=(const TStringMass& tmp) {
    for (int i = 0; i < tmp.Count; i++)
        AddItem(tmp.Item[i]);
    return *this;
}
std::string& TStringMass::operator[](int index) {
    if (index > -1 && index < Count) {
        return Item[index];
    }
    else throw std::logic_error("Index not faund");
}

TData::TData() :id(-1), Caption("No"), Category("No"), ContextInfo("No") {}
TData::TData(int _id, std::string _caption) :id(_id), Caption(_caption), Category("No"), ContextInfo("No") {}
TData::TData(const TData& tmp) {
    id = tmp.id;
    Caption = tmp.Caption;
    Category = tmp.Category;
    ContextInfo = tmp.ContextInfo;
}
TData::~TData() {}
TData& TData::operator=(const TData& tmp) {
    id = tmp.id;
    Caption = tmp.Caption;
    Category = tmp.Category;
    ContextInfo = tmp.ContextInfo;
    return *this;
}
std::ostream& operator<<(std::ostream& os, TData& tmp) {
    os << tmp.id << " " << tmp.Caption << " " << tmp.Category << " " << tmp.ContextInfo << "\n";
    return os;
}
bool TDataCMPstr(TData t, std::string str) {
    return ((t.Caption == str) || (t.Caption == "No"));
}
int TDataCMP(TData& tmp1, TData& tmp2) {
    return (strcmp(tmp1.Caption.c_str(), tmp2.Caption.c_str()));
}
int StrCMP(std::string& t1, std::string& t2) {
    return strcmp(t1.c_str(), t2.c_str());
}

int TSpecificationMass::getCount() { return count; }
TSpecificationMass::TSpecificationMass(TSpecificationMass& tmp) {
    mass = new TData[tmp.count];
    for (int i = 0; i < tmp.count; i++) {
        mass[i] = tmp.mass[i];
    }
    count = tmp.count;
}
TSpecificationMass::TSpecificationMass() :count(0), mass(nullptr) {}
TSpecificationMass::~TSpecificationMass() {
    delete[] mass;
}
void TSpecificationMass::add(TData& data) {
    count++;
    TData* NewMass = new TData[count];
    for (int i = 0; i < count - 1; i++) {
        NewMass[i] = mass[i];
    }
    NewMass[count - 1] = data;

    delete[]mass;
    mass = NewMass;
}
TData TSpecificationMass::getData(int i) { if (i > -1 && i < count) { return mass[i]; } }
TStringMass& TSpecificationMass::getCaptionMass() {
    TStringMass* tmp = new TStringMass;
    for (int i = 0; i < count; i++) {
        tmp->AddItem(mass[i].Caption);
    }
    return *tmp;
}
std::ostream& operator<<(std::ostream& os, TSpecificationMass& tmp)
{
    for (int i = 0; i < tmp.count; i++) {
        TData data = tmp.getData(i);
        os << data << std::endl;
    }
    return os;
}