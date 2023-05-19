#include "CTreeLib.hpp"

class TProduct {
public:
    string Name;
    TProduct(string _name) :Name(_name) {}
    TProduct() :Name("NoN name") {}
    TProduct(TProduct& tmp) {
        Name = tmp.Name;
    }
    ~TProduct() {}
    friend ostream& operator<<(ostream& os, TProduct& tmp);
};
ostream& operator<<(ostream& os, TProduct& tmp) {
    os << "Product Name: " << tmp.Name << endl;
    return os;
}
int TProductCMP(TProduct& tmp1, TProduct& tmp2) {
    return (strcmp(tmp1.Name.c_str(), tmp2.Name.c_str()));
}

int main()
{
        TData d1(1, "caption - 1"), d2(2, "caption - 2"), d3(3, "caption - 3");
        TNode<TProduct> n1(TNodeCMP, TProductCMP, d1), n2(TNodeCMP, TProductCMP, d2), n3(TNodeCMP, TProductCMP, d3);
        TTree<TProduct> tree(TNodeCMP, TProductCMP, 0);

        TProduct p1("p1"), p2("p2"), p3("p3");

        TStringMass Parm1; string s1 = ("caption - 3"), s2 = ("caption - 2"), s3 = ("caption - 1");
        TStringMass Parm2; string s4 = ("No"), s5 = ("No"), s6 = ("No");
        TStringMass Parm3;
        Parm1.AddItem("ROOT");
        Parm1.AddItem("caption - 1");
        Parm1.AddItem("caption - 2");


        Parm2.AddItem("No");
        Parm2.AddItem("No");
        Parm2.AddItem("No");

        tree.AddNode(n1, Parm1, 0);
        tree.AddNode(n2, Parm1, 1);
        tree.AddNode(n3, Parm1, 2);
        tree.AddProduct(p1, Parm1, 0);
        tree.AddProduct(p2, Parm1, 1);
        tree.AddProduct(p3, Parm1, 2);

        cout << " --- 0 --- " << endl;
        cout << tree.FaindAllNode(Parm2, 0) << endl;
        cout << " --- 1 --- " << endl;
        cout << tree.FaindAllNode(Parm2, 1) << endl;
        cout << " --- 2 --- " << endl;
        cout << tree.FaindAllNode(Parm2, 2) << endl;
        cout << " --- 3 --- " << endl;
        cout << tree.FaindAllNode(Parm2, 3) << endl;
        cout << " --- end --- " << endl;
        cout << tree.FaindAllProduct(Parm2, 0) << endl;
        cout << " --- end --- " << endl;
}


