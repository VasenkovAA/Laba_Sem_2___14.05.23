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
    //template<typename T>
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
    //template<typename T>
};

class TData {
public:
    int id;
    string Caption;
    string Category;
    string ContextInfo;
    TData() :id(-1), Caption("No"), Category("No"), ContextInfo("No") {}
    TData(int _id, string _caption) :id(_id), Caption(_caption), Category("No"), ContextInfo("No") {}
    TData(TData& tmp) {
        id = tmp.id;
        Caption = tmp.Caption;
        Category = tmp.Category;
        ContextInfo = tmp.ContextInfo;
    }
    ~TData() {}
    friend ostream& operator<<(ostream& os, TData& tmp);
    friend bool TDataCMP(TData t, string str);
};
ostream& operator<<(ostream& os, TData& tmp) {
    os << "\tid: " << tmp.id << "\n\tCaption: " << tmp.Caption << "\n\tCategory: " << tmp.Category
        << "\n\tContextInfo: " << tmp.ContextInfo << "  END" << endl;
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
    int (*CmpNode)(TNode<T>&, TNode<T>&);
    int (*CmpItem)(T&, T&);
    TMass<TNode<T>> tmpNodeMass;
    bool CreateTmpNode;
public:
    TTree() : CmpNode(nullptr), CmpItem(nullptr) {
        //Root.SonMass.setCmp();
        Root.Data.Caption = "ROOT";
        CreateTmpNode = 0;
    }
    TTree(int (*_CmpNode)(TNode<T>&, TNode<T>&), int (*_CmpItem)(T&, T&), bool _CreateTmpNode = 0) {
        CmpNode = _CmpNode;
        CmpItem = _CmpItem;
        Root.SonMass.setCmp(_CmpNode);
        Root.ItemMass.setCmp(_CmpItem);
        Root.Data.Caption = "ROOT";
        CreateTmpNode = _CreateTmpNode;
        tmpNodeMass.setCmp(_CmpNode);
    }
    TTree(TTree& tmp) {
        Root = tmp.Root;
        CmpNode = tmp.CmpNode;
        CmpItem = tmp.CmpItem;
        CreateTmpNode = tmp.CreateTmpNode;
    }
    ~TTree() {
        for (int i = 0; i < tmpNodeMass.getCount(); i++) {
            delete (tmpNodeMass.getItem(i));
        }
    }
private:
    bool AddProduct_private(T& product, TStringMass& mass, TNode<T>& node, int index = 0, int height = 0) {
        if (index == height) {
            if (TDataCMPstr(node.Data, mass.getItem(height))) {
                node.ItemMass.AddItem(product);
            }
            else { cerr << "no node: " << height << " " << mass.getItem(height) << " " << node.Data << endl; }
        }
        else {
            if (TDataCMPstr(node.Data, mass.getItem(height))) {
                int tmp = 0;
                node.ItemMass.AddItem(product);
                for (int i = 0; i < node.SonMass.getCount(); i++) {
                    if (AddProduct_private(product, mass, *node.SonMass.getItem(i), index, height + 1)) {
                        return 1;
                    }
                    else tmp++;
                }if (CreateTmpNode) {
                    if (tmp == node.SonMass.getCount()) {
                        TData* d1 = new TData(0, mass.getItem(height + 1));
                        TNode<T>* tmpNode = new TNode<T>(CmpNode, CmpItem, *d1);
                        node.SonMass.AddItem(*tmpNode);
                        tmpNodeMass.AddItem(*tmpNode);
                        AddProduct_private(product, mass, *node.SonMass.getItem(tmp), index, height + 1);
                    }
                    else { cerr << "tmp: " << tmp << endl; }
                }
                else { throw; }

            }
            else {
                cerr << "err: " << mass.getItem(height) << "\t" << node.Data << endl;
            }
        }
    }
    bool AddNode_private(TNode<T>& NewNode, TStringMass& mass, TNode<T>& node, int index = 0, int height = 0) {
        if (index == height) {
            if (TDataCMPstr(node.Data, mass.getItem(height))) {
                node.SonMass.AddItem(NewNode);
            }
            else { cerr << "no node: " << height << " " << mass.getItem(height) << " " << node.Data << endl; }
        }
        else {
            if (TDataCMPstr(node.Data, mass.getItem(height))) {
                int tmp = 0;

                for (int i = 0; i < node.SonMass.getCount(); i++) {
                    if (AddNode_private(NewNode, mass, *node.SonMass.getItem(i), index, height + 1)) {
                        return 1;
                    }
                    else tmp++;
                }if (CreateTmpNode) {
                    if (tmp == node.SonMass.getCount()) {
                        TData* d1 = new TData(0, mass.getItem(height + 1));
                        TNode<T>* tmpNode = new TNode<T>(CmpNode, CmpItem, *d1);
                        node.SonMass.AddItem(*tmpNode);
                        tmpNodeMass.AddItem(*tmpNode);
                        AddNode_private(NewNode, mass, *node.SonMass.getItem(tmp), index, height + 1);
                    }
                    else { cerr << "tmp: " << tmp << endl; }
                }
                else { throw; }

            }
            else {
                cerr << "err: " << mass.getItem(height) << "\t" << node.Data << endl;
            }
        }
    }
    TMass<TNode<T>>& FaindAllNode_private(TStringMass& mass, TNode<T>& node, int index = 0, int height = 0) {
        TMass<TNode<T>>* Out = new TMass<TNode<T>>;
        Out->setCmp(TNodeCMP);
        if (index == height) {
            Out->AddItem(node);
            return *Out;
        }
        else {
            if (height > index) { cerr << "height > index index: " << index << "height: " << height << endl; }
            else {
                if ((mass.getItem(index - 1) == "No") || (TDataCMPstr(node.Data, mass.getItem(index)))) {
                    for (int i = 0; i < node.SonMass.getCount(); i++) {
                        *Out += FaindAllNode_private(mass, *node.SonMass.getItem(i), index, height + 1);
                    }
                }
                return *Out;

            }
        }
    }
    TMass<T>& FaindAllProduct_private(TStringMass& mass, TNode<T>& node, int index = 0, int height = 0) {
        TMass<T>* Out = new TMass<T>;
        Out->setCmp(CmpItem);
        if (index == height) {
            *Out += node.ItemMass;
            return *Out;
        }
        else {
            if (height > index) { cerr << "height > index index: " << index << "height: " << height << endl; }
            else {
                if ((mass.getItem(index - 1) == "No") || (TDataCMPstr(node.Data, mass.getItem(index)))) {
                    for (int i = 0; i < node.SonMass.getCount(); i++) {
                        *Out += FaindAllProduct_private(mass, *node.SonMass.getItem(i), index, height + 1);
                    }
                }
                return *Out;

            }
        }
    }
public:
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
        if (index == -1) { index = mass.getCount(); }
        if (mass.getCount() == 0) { throw; }
        if (mass.getItem(0) != "ROOT") { throw; }
        AddNode_private(NewNode, mass, Root, index, 0);
    }
    bool AddProduct(T product, TStringMass& mass, int index = -1) {
        if (index == -1) { index = mass.getCount(); }
        if (mass.getCount() == 0) { throw; }
        if (mass.getItem(0) != "ROOT") { throw; }
        AddProduct_private(product, mass, Root, index, 0);
    }
};