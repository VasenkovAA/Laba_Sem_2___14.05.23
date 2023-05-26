#pragma once
#include "CDataLib.h"
//T - TProduct
template<typename T >
class TNode {
public:
    TMass<TNode> SonMass;
    TMass<T> ItemMass;
    TData Data;
    TNode() {};
    TNode(int (*CmpTNode)(TNode<T>&, TNode<T>&), int (*CmpItem)(T&, T&), TData _Data);
    TNode(int (*CmpTNode)(TNode<T>&, TNode<T>&), int (*CmpItem)(T&, T&));
    TNode(TNode& tmp);
    ~TNode();
    template<typename T>
    friend std::ostream& operator<<(std::ostream& os, TNode<T>& tmp);
    template<typename T>
    friend class TTree;
};
template<typename T >
TNode<T>::TNode(int (*CmpTNode)(TNode<T>&, TNode<T>&), int (*CmpItem)(T&, T&), TData _Data) :Data(_Data) {
    SonMass.setCmp(CmpTNode);
    ItemMass.setCmp(CmpItem);
};
template<typename T >
TNode<T>::TNode(int (*CmpTNode)(TNode<T>&, TNode<T>&), int (*CmpItem)(T&, T&)) {
    SonMass.setCmp(CmpTNode);
    ItemMass.setCmp(CmpItem);
};
template<typename T >
TNode<T>::TNode(TNode& tmp) {
    SonMass = tmp.SonMass;
    ItemMass = tmp.ItemMass;
    Data = tmp.Data;
};
template<typename T >
TNode<T>::~TNode() {}
template<typename T>
std::ostream& operator<<(std::ostream& os, TNode<T>& tmp) {
    os << ORANGE << "Node addres:" << RESET << &tmp << std::endl;
    os << GREEN << "SonMassCount:" << RESET << tmp.SonMass.getCount() << std::endl;
    os << GREEN << "ItemMassCount:" << RESET << tmp.ItemMass.getCount() << std::endl;
    if (tmp.SonMass.getCount() != 0) { std::cout << ORANGE << "Son addres:" << RESET << std::endl; }
    for (int i = 0; i < tmp.SonMass.getCount(); i++) {
        os << "[" << i << "]\tAddres:" << RESET << std::endl;
        os << tmp.SonMass.getItem(i) << std::endl;
    }
    os << GREEN << "Data:" << RESET << std::endl;
    os << tmp.Data;
    return os;
}
template<typename T>
inline int TNodeCMP(TNode<T>& tmp1, TNode<T>& tmp2) {
    return TDataCMP(tmp1.Data, tmp2.Data);

}

template<typename T>
class TTree {
private:
    TNode<T> Root;
    int (*pCmpNode)(TNode<T>&, TNode<T>&);
    int (*pCmpItem)(T&, T&);
public:
    TTree();
    TTree(int (*_CmpNode)(TNode<T>&, TNode<T>&), int (*_CmpItem)(T&, T&),
        TData(*GetData)(T& tmp, int i) = nullptr, bool _CreateTmpNode = 0);
    TTree(TTree& tmp);
    ~TTree();
private:
    void createItem(TNode<T>& node, TStringMass& mass, int height, bool index = 0, T* product = nullptr);

    bool AddProduct(T& product, TStringMass& mass, TNode<T>& node, int index = 0, int height = 0);
    bool AddData(TNode<T>& NewNode, TStringMass& mass, TNode<T>& node, int index = 0, int height = 0);
    TMass<TNode<T>>& FaindAllData(TStringMass& mass, TNode<T>& node, int index = 0, int height = 0);
    TMass<T>& FaindAllProduct(TStringMass& mass, TNode<T>& node, int index = 0, int height = 0);
public:
    void setCmpNode(int (*_CmpNode)(TNode<T>&, TNode<T>&));
    void setCmpItem(int (*_CmpItem)(T&, T&));
    void setGetData(TData(*_GetData)(T& tmp, int i));
    int getMaxHeight();
    TMass<TNode<T>>& FaindAllData(TStringMass& mass, int index = -1);
    TMass<T>& FaindAllProduct(TStringMass& mass, int index = -1);
    bool AddData(TNode<T>& NewNode, TStringMass& mass, int index = -1);
    bool AddProduct(T& product, TStringMass& mass, int index = -1);
private:
    TData(*pGetData)(T& tmp, int i);
    TMass<TNode<T>> tmpNodeMass;
    int MaxHeight;
    bool CreateTmpNode;
};
template<typename T>
TTree<T>::TTree() : pCmpNode(nullptr), pCmpItem(nullptr), pGetData(nullptr) {

    Root.Data.Caption = "ROOT";
    CreateTmpNode = 0;
    MaxHeight = 0;
}
template<typename T>
TTree<T>::TTree(int (*_CmpNode)(TNode<T>&, TNode<T>&), int (*_CmpItem)(T&, T&),
    TData(*GetData)(T& tmp, int i), bool _CreateTmpNode) {
    pCmpNode = _CmpNode;
    pCmpItem = _CmpItem;
    Root.SonMass.setCmp(_CmpNode);
    Root.ItemMass.setCmp(_CmpItem);
    Root.Data.Caption = "ROOT";
    CreateTmpNode = _CreateTmpNode;
    tmpNodeMass.setCmp(_CmpNode);
    MaxHeight = 0;
}
template<typename T>
TTree<T>::TTree(TTree& tmp) {
    pGetData = tmp.pGetData;
    Root = tmp.Root;
    pCmpNode = tmp.pCmpNode;
    pCmpItem = tmp.pCmpItem;
    CreateTmpNode = tmp.CreateTmpNode;
    MaxHeight = tmp.MaxHeight;
}
template<typename T>
TTree<T>::~TTree() {
    for (int i = 0; i < tmpNodeMass.getCount(); i++) {
        delete (tmpNodeMass.getItem(i));
    }
}
template<typename T>
inline void TTree<T>::createItem(TNode<T>& node, TStringMass& mass, int height, bool index, T* product) {
    if (MaxHeight == height) { MaxHeight++; }
    if (index) {
        TData d1(pGetData(*product, height + 1));
        TNode<T>* tmpNode = new TNode<T>(pCmpNode, pCmpItem, d1);
        node.SonMass.AddItem(*tmpNode);
        tmpNodeMass.AddItem(*tmpNode);
    }
    else {
        TData* d1 = new TData(0, mass[height + 1]);
        TNode<T>* tmpNode = new TNode<T>(pCmpNode, pCmpItem, *d1);
        node.SonMass.AddItem(*tmpNode);
        tmpNodeMass.AddItem(*tmpNode);
    }

}
template<typename T>
bool TTree<T>::AddProduct(T& product, TStringMass& mass, TNode<T>& node, int index, int height) {
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
                if (AddProduct(product, mass, node.SonMass[i], index, height + 1)) {
                    return 1;
                }
                else tmp++;
            }if (CreateTmpNode) {
                if (tmp == node.SonMass.Count) {
                    createItem(node, mass, height, (tmp == node.SonMass.Count), &product);
                    return AddProduct(product, mass, node.SonMass[tmp], index, height + 1);
                }
                else {
                    std::cerr << "????????????????????????????????????? ERROR: " <<
                        "how did you get here you pervert????" << tmp << std::endl;
                }
            }
            else { throw; }

        }
        else {
            return 0;
        }
    }
}
template<typename T>
bool TTree<T>::AddData(TNode<T>& NewNode, TStringMass& mass, TNode<T>& node, int index, int height) {
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
                if (AddData(NewNode, mass, node.SonMass[i], index, height + 1)) {
                    return 1;
                }
                else tmp++;
            }if (CreateTmpNode) {
                if (tmp == node.SonMass.Count) {
                    createItem(node, mass, height, 0);
                    return AddData(NewNode, mass, node.SonMass[tmp], index, height + 1);
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
template<typename T>
TMass<TNode<T>>& TTree<T>::FaindAllData(TStringMass& mass, TNode<T>& node, int index, int height) {
    TMass<TNode<T>>* Out = new TMass<TNode<T>>;
    Out->cmp = TNodeCMP;
    if (index == height) {
        Out->AddItem(node);
        return *Out;
    }
    else {
        if (height > index) { std::cerr << "height > index index: " << index << "height: " << height << std::endl; }
        else {
            if ((mass[index - 1] == "No") || (TDataCMPstr(node.Data, mass[index]))) {
                for (int i = 0; i < node.SonMass.Count; i++) {
                    *Out += FaindAllData(mass, node.SonMass[i], index, height + 1);
                }
            }
            return *Out;
        }
    }
}
template<typename T>
TMass<T>& TTree<T>::FaindAllProduct(TStringMass& mass, TNode<T>& node, int index, int height) {
    TMass<T>* Out = new TMass<T>;
    Out->setCmp(pCmpItem);
    if (index == height) {
        *Out += node.ItemMass;
        return *Out;
    }
    else {
        if (height > index) { std::cerr << "height > index index: " << index << "height: " << height << std::endl; }
        else {
            if ((mass[index - 1] == "No") || (TDataCMPstr(node.Data, mass[index]))) {
                for (int i = 0; i < node.SonMass.Count; i++) {
                    *Out += FaindAllProduct(mass, node.SonMass[i], index, height + 1);
                }
            }
            return *Out;
        }
    }
}
template<typename T>
inline void TTree<T>::setCmpNode(int (*_CmpNode)(TNode<T>&, TNode<T>&)) { pCmpNode = _CmpNode; }
template<typename T>
inline void TTree<T>::setCmpItem(int (*_CmpItem)(T&, T&)) { pCmpItem = _CmpItem; }
template<typename T>
inline void TTree<T>::setGetData(TData(*_GetData)(T& tmp, int i)) {
    pGetData = _GetData;
}
template<typename T>
inline int TTree<T>::getMaxHeight() { return MaxHeight; }
template<typename T>
inline TMass<TNode<T>>& TTree<T>::FaindAllData(TStringMass& mass, int index) {
    if (index == -1) { index = mass.getCount(); }
    if (mass.getCount() == 0) { throw; }
    if (mass.getItem(0) != "ROOT" && mass.getItem(0) != "No") { throw; }
    return FaindAllData(mass, Root, index, 0);
}
template<typename T>
inline TMass<T>& TTree<T>::FaindAllProduct(TStringMass& mass, int index) {
    if (index == -1) { index = mass.getCount(); }
    if (mass.getCount() == 0) { throw; }
    if (mass.getItem(0) != "ROOT" && mass.getItem(0) != "No") { throw; }
    return FaindAllProduct(mass, Root, index, 0);
}
template<typename T>
inline bool TTree<T>::AddData(TNode<T>& NewNode, TStringMass& mass, int index) {
    if (index < -1) { throw; }
    if (index == -1) { index = mass.getCount() - 1; }
    if (mass.getCount() == 0) { throw; }
    if (mass.getItem(0) != "ROOT") { throw; }
    return AddData(NewNode, mass, Root, index, 0);
}
template<typename T>
inline bool TTree<T>::AddProduct(T& product, TStringMass& mass, int index) {
    if (index < -1) { throw; }
    if (index == -1) { index = mass.getCount() - 1; }
    if (mass.getCount() == 0) { throw; }
    if (mass.getItem(0) != "ROOT") { throw; }
    return AddProduct(product, mass, Root, index, 0);
}