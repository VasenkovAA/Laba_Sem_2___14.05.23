#pragma once
#include <iostream>
using namespace std;
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
    bool LinkCheck(T& tmp) {
        for (int i = 0; i < Count; i++) {
            if (Item[i] == &tmp) { return 1; }

        }
        return 0;
    }
public:
    T* getItem(int Index) {
        if ((Index >= 0) && (Index < Count)) {
            return (Item[Index]);
        }
        else { throw; }//-----------------------------------------------------
    }

    int getCount() { return Count; }
    void setCmp(int (*_cmp)(T&, T&)) {
        cmp = _cmp;
    }
    bool AddItem(T& tmp, bool AddSame = 1) {
        if (cmp == nullptr) {
            cerr << typeid(*this).name() << "    (cmp) function == nullptr";
            throw logic_error("(cmp) function == nullptr");
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
    void Out() {
        if (Count == 0) { cout << "Mass count == 0" << endl; }
        else {
            for (int i = 0; i < Count; i++) {
                cout << "Ilement [" << i << "] = " << *Item[i] << endl;
            }
        }
    }
    void DeleteAllItemByType(T& tmp) {
        TMass<T>Faind = FaindAll(tmp);
        for (int i = 0; i < Faind.Count; i++) {
            DeleteItemByType(*Faind.Item[i]);
        }
    }
    void DeleteItemByType(T& tmp) {
        int Index = FaindFirst(tmp);
        DeleteItemByIndex(Index);
    }
    void DeleteItemByIndex(int Index1) {
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
                throw logic_error("Count == 0, can no deleted");
            }
            if ((Index1 > -1) && (Index1 < Count)) {
                throw logic_error("No index in mass");
            }
        }
    }
    int FaindFirst(T& tmp) {
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
    TMass<T>& FaindAll(T& tmp) {
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
    void Dispose() {
        delete Item;
        Item = nullptr;
        Count = 0;
    }

    TMass() :cmp(nullptr), Count(0), Item(nullptr) { }
    TMass(int (*_cmp)(T&, T&)) :cmp(nullptr), Count(0), Item(nullptr) {
        cmp = _cmp;
        Count = 0;
    }
    TMass(TMass& tmp) :cmp(nullptr), Count(tmp.Count), Item(nullptr) {
        Item = new T * [Count];
        for (int i = 0; i < Count; i++) {
            Item[i] = tmp.Item[i];
        }
        cmp = tmp.cmp;
    }
    ~TMass() {
        //cout << "co" << this->Count << endl;
        delete Item;
        //cout << "co" << this->Count << endl;
    }
    TMass<T>& operator+=(const TMass<T>& tmp) {
        for (int i = 0; i < tmp.Count; i++)
            AddItem(*tmp.Item[i]);
        return *this;
    }
    T& operator[](int index) {
        if (index > -1 && index < Count) {
            return *Item[index];
        }
        else throw logic_error("Index not faund");
    }

    template<typename T>
    friend ostream& operator<<(ostream& os, TMass<T>& tmp);
    template<typename T>
    friend class TTree;
    template<typename T>
    friend class TNode;
};
template<typename T>
ostream& operator<<(ostream& os, TMass<T>& tmp) {
    if (tmp.Count == 0) { os << ORANGE << "\tMass count == 0" << RESET << endl; }
    else {
        for (int i = 0; i < tmp.Count; i++) {
            os << BLUE << "\tIlement [" << i << "]" << endl << RESET << *tmp.Item[i] << endl;
        }
    }
    return os;

}

class TStringMass {
private:
    int Count;
    string* Item;
public:
    string getItem(int Index) {
        if ((Index >= 0) && (Index < Count)) {
            return (Item[Index]);
        }
        else { throw; }//-----------------------------------------------------
    }
    int getCount() { return Count; }
    bool AddItem(string tmp, bool AddSame = 0) {
        string* Item_tmp = new string[Count + 1];
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
    void Out() {
        if (Count == 0) { cout << "Mass count == 0" << endl; }
        else {
            for (int i = 0; i < Count; i++) {
                cout << "Ilement [" << i << "] = " << Item[i] << endl;
            }
        }
    }
    void DeleteItemByIndex(int Index1) {
        if ((Index1 > -1) && (Index1 < Count) && (Count > 0)) {
            string* Item_tmp = new string[Count - 1];
            int i = 0;
            for (i; i < Index1; i++) { Item_tmp[i] = Item[i]; }
            for (i; i < Count; i++) { Item_tmp[i] = Item[i + 1]; }
            delete Item;
            Item = Item_tmp;
            Count--;
        }
        else {
            if (Count == 0) {
                throw logic_error("Count == 0, can no deleted");
            }
            if ((Index1 > -1) && (Index1 < Count)) {
                throw logic_error("No index in mass");
            }
        }
    }
    void Dispose() {
        delete Item;
        Item = nullptr;
        Count = 0;
    }

    TStringMass() :Count(0), Item(nullptr) { }
    TStringMass(TStringMass& tmp) : Count(tmp.Count), Item(nullptr) {
        Item = new string[Count];
        for (int i = 0; i < Count; i++) {
            Item[i] = tmp.Item[i];
        }
    }
    ~TStringMass() {
        delete[] Item;
    }
    TStringMass& operator+=(const TStringMass& tmp) {
        for (int i = 0; i < tmp.Count; i++)
            AddItem(tmp.Item[i]);
        return *this;
    }
    string& operator[](int index) {
        if (index > -1 && index < Count) {
            return Item[index];
        }
        else throw logic_error("Index not faund");
    }

    template<typename T>
    friend ostream& operator<<(ostream& os, TMass<T>& tmp);
    template<typename T>
    friend class TTree;
};

class TData {
public:
    int id;
    string Caption;
    string Category;
    string ContextInfo;
    TData() :id(-1), Caption("No"), Category("No"), ContextInfo("No") {}
    TData(int _id, string _caption) :id(_id), Caption(_caption), Category("No"), ContextInfo("No") {}
    TData(const TData& tmp) {
        id = tmp.id;
        Caption = tmp.Caption;
        Category = tmp.Category;
        ContextInfo = tmp.ContextInfo;
    }
    ~TData() {}
    TData& operator=(const TData& tmp) {
        id = tmp.id;
        Caption = tmp.Caption;
        Category = tmp.Category;
        ContextInfo = tmp.ContextInfo;
        return *this;
    }
    friend ostream& operator<<(ostream& os, TData& tmp);
    friend bool TDataCMP(TData t, string str);
};
ostream& operator<<(ostream& os, TData& tmp) {
    os << tmp.id << " " << tmp.Caption << " " << tmp.Category<< " " << tmp.ContextInfo << "\n";
    return os;
}
bool TDataCMPstr(TData t, string str) {
    return ((t.Caption == str) || (t.Caption == "No"));
}
int TDataCMP(TData& tmp1, TData& tmp2) {
    return (strcmp(tmp1.Caption.c_str(), tmp2.Caption.c_str()));
}
template<typename T>
int TDataCMP(TData& tmp1, T& tmp2) {
    return ((tmp1.Caption == tmp2) || (tmp1.Caption == "No"));
}

int StrCMP(string& t1, string& t2) {
    return strcmp(t1.c_str(), t2.c_str());
}

class TSpecificationMass {
    TData* mass;
    int count;
public:
    int getCount() { return count; }
    TSpecificationMass(TSpecificationMass& tmp) {
        mass = new TData[tmp.count];
        for (int i = 0; i < tmp.count; i++) {
            mass[i] = tmp.mass[i];
        }
        count = tmp.count;
    }
    TSpecificationMass() :count(0), mass(nullptr) {}
    ~TSpecificationMass() {
        delete[] mass;
    }
    void add(TData& data) {
        count++;
        TData* NewMass = new TData[count];
        for (int i = 0; i < count - 1; i++) {
            NewMass[i] = mass[i];
        }
        NewMass[count - 1] = data;
        
        delete[]mass;
        mass = NewMass;
    }
    TData getData(int i) { if (i > -1 && i < count) { return mass[i]; } }
    friend ostream& operator<<(ostream& os, TSpecificationMass& tmp);
    TStringMass& getCaptionMass() {
        TStringMass* tmp = new TStringMass;
        for (int i = 0; i < count; i++) {
            tmp->AddItem(mass[i].Caption);
        }
        return *tmp;
    }
};
ostream& operator<<(ostream& os, TSpecificationMass& tmp)
{
    for (int i = 0; i < tmp.count; i++) {
        TData data = tmp.getData(i);
        os << data << endl;
    }
    return os;
}

//T - TProduct
template<typename T >
class TNode {
public:
    TMass<TNode> SonMass;
    TMass<T> ItemMass;
    TData Data;
    TNode() {};
    TNode(int (*CmpTNode)(TNode<T>&, TNode<T>&), int (*CmpItem)(T&, T&), TData _Data) :Data(_Data) {
        SonMass.setCmp(CmpTNode);
        ItemMass.setCmp(CmpItem);
    };
    TNode(int (*CmpTNode)(TNode<T>&, TNode<T>&), int (*CmpItem)(T&, T&)) {
        SonMass.setCmp(CmpTNode);
        ItemMass.setCmp(CmpItem);
    };
    TNode(TNode& tmp) {
        SonMass = tmp.SonMass;
        ItemMass = tmp.ItemMass;
        Data = tmp.Data;
    };
    ~TNode() {}
    template<typename T>
    friend ostream& operator<<(ostream& os, TNode<T>& tmp);
    template<typename T>
    friend class TTree;
};
template<typename T>
ostream& operator<<(ostream& os, TNode<T>& tmp) {
    os << ORANGE << "Addres:" << RESET << &tmp << endl;
    os << GREEN << "SonMassCount:" << RESET << tmp.SonMass.getCount() << endl;
    os << GREEN << "ItemMassCount:" << RESET << tmp.ItemMass.getCount() << endl;
    for (int i = 0; i < tmp.SonMass.getCount(); i++) {
        os << "[" << i << "]\tAddres:" << RESET << endl;
        os << tmp.SonMass.getItem(i) << endl;
    }
    os << GREEN << "Data:" << RESET << endl;
    os << tmp.Data;
    return os;
}
template<typename T>
int TNodeCMP(TNode<T>& tmp1, TNode<T>& tmp2) {
    return TDataCMP(tmp1.Data, tmp2.Data);

}

template<typename T>
class TTree {
private:
    TNode<T> Root;
    int (*pCmpNode)(TNode<T>&, TNode<T>&);
    int (*pCmpItem)(T&, T&);
public:
    TTree() : pCmpNode(nullptr), pCmpItem(nullptr), pGetData(nullptr){
        
        Root.Data.Caption = "ROOT";
        CreateTmpNode = 0;
        MaxHeight = 0;
    }
    TTree(int (*_CmpNode)(TNode<T>&, TNode<T>&), int (*_CmpItem)(T&, T&), 
            TData(*GetData)(T& tmp, int i) = nullptr, bool _CreateTmpNode = 0) {
        pCmpNode = _CmpNode;
        pCmpItem = _CmpItem;
        Root.SonMass.setCmp(_CmpNode);
        Root.ItemMass.setCmp(_CmpItem);
        Root.Data.Caption = "ROOT";
        CreateTmpNode = _CreateTmpNode;
        tmpNodeMass.setCmp(_CmpNode);
        MaxHeight = 0;
    }
    TTree(TTree& tmp) {
        pGetData = tmp.pGetData;
        Root = tmp.Root;
        pCmpNode = tmp.pCmpNode;
        pCmpItem = tmp.pCmpItem;
        CreateTmpNode = tmp.CreateTmpNode;
        MaxHeight = tmp.MaxHeight;
    }
    ~TTree() {
        for (int i = 0; i < tmpNodeMass.getCount(); i++) {
            delete (tmpNodeMass.getItem(i));
        }
    }
private:
    bool AddProduct_private(T& product, TStringMass& mass, TNode<T>& node, int index = 0, int height = 0) {
        if (index == height) {
            if (TDataCMPstr(node.Data, mass[height])) {
                node.ItemMass.AddItem(product);
            }
            else { return 0; }
        }
        else {
            if (TDataCMPstr(node.Data, mass[height])) {
                int tmp = 0;
                node.ItemMass.AddItem(product);
                for (int i = 0; i < node.SonMass.Count; i++) {
                    if (AddProduct_private(product, mass, node.SonMass[i], index, height + 1)) {
                        return 1;
                    }
                    else tmp++;
                }if (CreateTmpNode) {               
                    if (tmp == node.SonMass.Count) {           
                        if (pGetData==nullptr) {
                            if (MaxHeight == height) { MaxHeight++; }
                            TData* d1 = new TData(0, mass.getItem(height + 1));
                            TNode<T>* tmpNode = new TNode<T>(pCmpNode, pCmpItem, *d1);
                            node.SonMass.AddItem(*tmpNode);
                            tmpNodeMass.AddItem(*tmpNode);
                            return AddProduct_private(product, mass, node.SonMass[tmp], index, height + 1);
                        }
                        else {
                            if (MaxHeight == height) { MaxHeight++; }
                            TData d1(pGetData(product, height+1 ));
                            TNode<T>* tmpNode = new TNode<T>(pCmpNode, pCmpItem, d1);
                            node.SonMass.AddItem(*tmpNode);
                            tmpNodeMass.AddItem(*tmpNode);
                            return AddProduct_private(product, mass, node.SonMass[tmp], index, height + 1);
                            
                        }
                    }
                    else { cerr << "????????????????????????????????????? ERROR: " << tmp << endl; }
                }
                else { throw; }

            }
            else {
                 return 0;
            }
        }
    }
    bool AddNode_private(TNode<T>& NewNode, TStringMass& mass, TNode<T>& node, int index = 0, int height = 0) {
        if (index == height) {
            if (TDataCMPstr(node.Data, mass[height])) {
                node.SonMass.AddItem(NewNode);
            }
            else { return 0; }
        }
        else {
            if (TDataCMPstr(node.Data, mass[height])) {
                int tmp = 0;

                for (int i = 0; i < node.SonMass.Count; i++) {
                    if (AddNode_private(NewNode, mass, node.SonMass[i], index, height + 1)) {
                        return 1;
                    }
                    else tmp++;
                }if (CreateTmpNode) {
                    if (tmp == node.SonMass.Count) {
                        if (MaxHeight == height) { MaxHeight++; }
                        TData* d1 = new TData(0, mass[height + 1]);
                        TNode<T>* tmpNode = new TNode<T>(pCmpNode, pCmpItem, *d1);
                        node.SonMass.AddItem(*tmpNode);
                        tmpNodeMass.AddItem(*tmpNode);
                        AddNode_private(NewNode, mass, node.SonMass[tmp], index, height + 1);
                    }
                    else { return 0; }
                }
                else { throw; }

            }
            else {
                return 0;
            }
        }
    }
    TMass<TNode<T>>& FaindAllNode_private(TStringMass& mass, TNode<T>& node, int index = 0, int height = 0) {
        TMass<TNode<T>>* Out = new TMass<TNode<T>>;
        Out->cmp = TNodeCMP;
        if (index == height) {
            Out->AddItem(node);
            return *Out;
        }
        else {
            if (height > index) { cerr << "height > index index: " << index << "height: " << height << endl; }
            else {
                if ((mass[index - 1] == "No") || (TDataCMPstr(node.Data, mass[index]))) {
                    for (int i = 0; i < node.SonMass.Count; i++) {
                        *Out += FaindAllNode_private(mass, node.SonMass[i], index, height + 1);
                    }
                }
                return *Out;

            }
        }
    }
    TMass<T>& FaindAllProduct_private(TStringMass& mass, TNode<T>& node, int index = 0, int height = 0) {
        TMass<T>* Out = new TMass<T>;
        Out->setCmp(pCmpItem);
        if (index == height) {
            *Out += node.ItemMass;
            return *Out;
        }
        else {
            if (height > index) { cerr << "height > index index: " << index << "height: " << height << endl; }
            else {
                if ((mass[index - 1] == "No") || (TDataCMPstr(node.Data, mass[index]))) {
                    for (int i = 0; i < node.SonMass.Count; i++) {
                        *Out += FaindAllProduct_private(mass, node.SonMass[i], index, height + 1);
                    }
                }
                return *Out;

            }
        }
    }
public:
    void setCmpNode(int (*_CmpNode)(TNode<T>&, TNode<T>&)) { pCmpNode = _CmpNode; }
    void setCmpItem(int (*_CmpItem)(T&, T&)) { pCmpItem = _CmpItem; }
    void setGetData(TData(*_GetData)(T& tmp, int i)) {
        pGetData = _GetData;
    }
    int getMaxHeight() {return MaxHeight;}
    TMass<TNode<T>>& FaindAllNode(TStringMass& mass, int index = -1) {
        if (index == -1) { index = mass.getCount(); }
        if (mass.getCount() == 0) { throw; }
        if (mass.getItem(0) != "ROOT" && mass.getItem(0) != "No") { throw; }
        return FaindAllNode_private(mass, Root, index, 0);
    }
    TMass<T>& FaindAllProduct(TStringMass& mass, int index = -1) {
        if (index == -1) { index = mass.getCount(); }
        if (mass.getCount() == 0) { throw; }
        if (mass.getItem(0) != "ROOT" && mass.getItem(0) != "No") { throw; }
        return FaindAllProduct_private(mass, Root, index, 0);
    }
    bool AddNode(TNode<T>& NewNode, TStringMass& mass, int index = -1) {
        if (index < -1) { throw; }
        if (index == -1) { index = mass.getCount()-1; }
        if (mass.getCount() == 0) { throw; }
        if (mass.getItem(0) != "ROOT") { throw; }
        return AddNode_private(NewNode, mass, Root, index, 0);
    }
    bool AddProduct(T&product, TStringMass& mass, int index = -1) {
        if (index < -1) { throw; }
        if (index == -1) { index = mass.getCount()-1; }
        if (mass.getCount() == 0) { throw; }
        if (mass.getItem(0) != "ROOT") { throw; }
        return AddProduct_private(product, mass, Root, index, 0);
    }
private:    
    TData(*pGetData)(T& tmp, int i);
    TMass<TNode<T>> tmpNodeMass;
    int MaxHeight;
    bool CreateTmpNode;
};