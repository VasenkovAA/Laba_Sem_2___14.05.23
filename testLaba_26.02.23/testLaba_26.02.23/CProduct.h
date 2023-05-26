#pragma once
#include<iostream>
#include "CTreeLib.h"
class TProduct {
public:
    std::string Name;
    TSpecificationMass Spec;
    TProduct(std::string _name) :Name(_name) {}
    TProduct() :Name("NoN name") {}
    TProduct(TProduct& tmp) {
        Name = tmp.Name;
    }
    ~TProduct() {
        //cout << "Deleted: "<<Name<<endl;
    }
    friend std::ostream& operator<<(std::ostream& os, TProduct& tmp);
    friend TData CMP(TProduct& tmp,int i);
};
TData CMP(TProduct& tmp, int i) {
    return (tmp.Spec.getData(i));
}
std::ostream& operator<<(std::ostream& os, TProduct& tmp) {
    os << ORANGE << "Product Name: " << RESET << tmp.Name
        << "\tSpecification mass count = " << tmp.Spec.getCount() << std::endl;
    return os;
}
int TProductCMP(TProduct& tmp1, TProduct& tmp2) {
    return (strcmp(tmp1.Name.c_str(), tmp2.Name.c_str()));
}
