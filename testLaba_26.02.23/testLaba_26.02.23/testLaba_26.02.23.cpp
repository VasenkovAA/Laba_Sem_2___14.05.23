
#include <iostream>
//#include "CMass.h"
//#include "CDataLib.h"
#include "CTreeLib.h"
#include "CProduct.h"
using namespace std;
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED   "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[33m"
#define BLUE "\033[34m"

int main()
{
    //создаем данные(параметры каждого продукта)(сейчас меняется только Caption, но можно и все менять)
    TData d1(1, "caption - 1"), d2(2, "caption - 2"), d3(3, "caption - 3");
    //создаем записи в дереве(пока мы их туда не добавили)
    TNode<TProduct> n1(TNodeCMP, TProductCMP, d1), n2(TNodeCMP, TProductCMP, d2), n3(TNodeCMP, TProductCMP, d3);
    //инициализируем дерево
    TTree<TProduct> tree(TNodeCMP, TProductCMP, CMP, 1);
    //создаем три продукта
    TProduct p_1("product - 1");
    TProduct p_2("product - 2");
    TProduct p_3("product - 3");
    //Строки параметров для поиска в дереве или добавления туда элементов
    TStringMass Parm1;
    TStringMass Parm2;
    //добавляем пораметры
    Parm1.AddItem("ROOT");
    Parm1.AddItem("caption - 1");
    Parm1.AddItem("caption - 2");
    //добавили параметры поиска по всему дереву
    Parm2.AddItem("No");
    Parm2.AddItem("No");
    Parm2.AddItem("No");

    //создаем Data(данные) для продуктов
    TData tmp1(-1, "ROOT");
    TData tmp2(75, "v1");
    TData tmp3(75, "v2");

    //заполняем продукты данными
    p_1.Spec.add(tmp1);
    p_1.Spec.add(tmp2);
    p_1.Spec.add(tmp3);

    p_2.Spec.add(tmp1);
    p_2.Spec.add(tmp2);
    p_2.Spec.add(tmp3);

    p_3.Spec.add(tmp1);
    p_3.Spec.add(tmp2);
    p_3.Spec.add(tmp3);
    //устанавливаем функцию поиска параметров у продуктов для дерева
    tree.setGetData(CMP);
    //добавляем ветки по списку параметров Parm1
    tree.AddData(n1, Parm1, 0);
    tree.AddData(n2, Parm1, 1);
    tree.AddData(n3, Parm1, 2);
    //добавляем продукты по их внутреннему списку параметров(характеристик продкта)
    cout << tree.AddProduct(p_1, p_1.Spec.getCaptionMass(), 0) << endl;
    cout << tree.AddProduct(p_2, p_2.Spec.getCaptionMass(), 1) << endl;
    cout << tree.AddProduct(p_3, p_3.Spec.getCaptionMass(), 2) << endl;

    //Вывод всех уровней дерева
    cout << " --- 0 --- " << endl;
    cout << tree.FaindAllData(Parm2, 0) << endl;
    cout << " --- 1 --- " << endl;
    cout << tree.FaindAllData(Parm2, 1) << endl;
    cout << " --- 2 --- " << endl;
    cout << tree.FaindAllData(Parm2, 2) << endl;
    cout << " --- 3 --- " << endl;
    cout << tree.FaindAllData(Parm2, 3) << endl;
    cout << " --- end --- " << endl;
    //Вывод всех продуктов для третьего уровня
    cout << tree.FaindAllProduct(Parm2, 2) << endl;
    cout << " --- end --- " << endl;
}