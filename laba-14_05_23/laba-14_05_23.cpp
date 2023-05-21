#include "CTreeLib.hpp"
#include "CListLib.hpp"




class TProduct {
public:
    string Name;
    TSpecificationMass Spec;
    TProduct(string _name) :Name(_name) {}
    TProduct() :Name("NoN name") {}
    TProduct(TProduct& tmp) {
        Name = tmp.Name;
    }
    ~TProduct() {
        cout << "Deleted: "<<Name<<endl;
    }
    friend ostream& operator<<(ostream& os, TProduct& tmp);
    friend TData CMP(TProduct& tmp);
};
TData CMP(TProduct& tmp,int i) {
    
    TData t = tmp.Spec.getData(i);
    
    return (tmp.Spec.getData(i));
}
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
    //TProduct* p = new TProduct("123"), *p2 = new TProduct("123-1");
    //TList<TProduct> l;

    //l.add(*p);
    //l.add(*p2);
    //l.add(*p);
    //l.print();
    //
    //TSpecificationMass tmp;
    //tmp.add(d1);
    //tmp.add(d2);
    //tmp.add(d3);
    //cout << tmp;

        TNode<TProduct> n1(TNodeCMP, TProductCMP, d1), n2(TNodeCMP, TProductCMP, d2), n3(TNodeCMP, TProductCMP, d3);
        
        TTree<TProduct> tree(TNodeCMP, TProductCMP, CMP, 1);

        TProduct p_1("p1");
        TProduct p_2("p2");
        TProduct p_3("p3");

        TStringMass Parm1; string s1 = ("caption - 3"), s2 = ("caption - 2"), s3 = ("caption - 1");
        TStringMass Parm2; string s4 = ("No"), s5 = ("No"), s6 = ("No");
        //TStringMass Parm3;
        Parm1.AddItem("ROOT");
        Parm1.AddItem("caption - 1");
        Parm1.AddItem("caption - 2");

        Parm2.AddItem("No");
        Parm2.AddItem("No");
        Parm2.AddItem("No");

        TData tmp1(-1,"ROOT");
        TData tmp2(75, "v1");
        TData tmp3(75, "v2");

        p_1.Spec.add(tmp1);
        p_1.Spec.add(tmp2);
        p_1.Spec.add(tmp3);

        p_2.Spec.add(tmp1);
        p_2.Spec.add(tmp2);
        p_2.Spec.add(tmp3);

        p_3.Spec.add(tmp1);
        p_3.Spec.add(tmp2);
        p_3.Spec.add(tmp3);

        tree.setGetData(CMP);

        tree.AddNode(n1, Parm1, 0);
        tree.AddNode(n2, Parm1, 1);
        tree.AddNode(n3, Parm1, 2);
        cout << tree.AddProduct(p_1, p_1.Spec.getCaptionMass(), 0) << endl;
        cout << tree.AddProduct(p_2, p_2.Spec.getCaptionMass(), 1) << endl;
        cout << tree.AddProduct(p_3, p_3.Spec.getCaptionMass(), 2) << endl;

        cout << " --- 0 --- " << endl;
        cout << tree.FaindAllNode(Parm2, 0) << endl;
        cout << " --- 1 --- " << endl;
        cout << tree.FaindAllNode(Parm2, 1) << endl;
        cout << " --- 2 --- " << endl;
        cout << tree.FaindAllNode(Parm2, 2) << endl;
        cout << " --- 3 --- " << endl;
        cout << tree.FaindAllNode(Parm2, 3) << endl;
        cout << " --- end --- " << endl;
        cout << tree.FaindAllProduct(Parm2, 2) << endl;
        cout << " --- end --- " << endl;
        cout << tree.getMaxHeight() << endl;
        cout << " --- end --- " << endl;
}