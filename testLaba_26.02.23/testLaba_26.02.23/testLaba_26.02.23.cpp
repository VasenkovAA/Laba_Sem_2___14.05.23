
#include <iostream>
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
    //инициализируем дерево
    TTree<TProduct> tree(TNodeCMP, TProductCMP, CMP, 1);
    //создаем продукт - шкаф
    TProduct product_closet("closet");

    //Создаем список параметров для поиска элементов в дереве
    TStringMass parm_list_for_search;
    //добавили параметры поиска по всему дереву - No потому что мы хотим искать все записи в дереве на каждом уровне
    parm_list_for_search.AddItem("No");
    parm_list_for_search.AddItem("No");
    parm_list_for_search.AddItem("No");

    //создаем Data(данные) для для продукта(шкафа)
    TData parametr_1_ROOT(-1, "ROOT","ROOT","ROOT");
    TData parametr_2_color(0, "Color","Red","color of product");
    TData parametr_3_window(0,"the presence of a window", "with a window",
        "parameter that determines the presence of a window in the cabinet");

    //заполняем массив спецификаций продукта(его данные и характеристики)
    product_closet.Spec.add(parametr_1_ROOT);
    product_closet.Spec.add(parametr_2_color);
    product_closet.Spec.add(parametr_3_window);

    //устанавливаем функцию поиска параметров у продуктов для дерева
    tree.setGetData(CMP);
    //добавляем продукт по их внутреннему списку параметров(характеристик продкта)
    cout<<"result of adding a product (whether a product was added): " 
        << tree.AddProduct(product_closet, product_closet.Spec.getCaptionMass(), 2) << endl;

    //Вывод перывй четырех уровней дерева
    cout << " --- 0 --- " << endl;
    cout << tree.FaindAllData(parm_list_for_search, 0) << endl;
    cout << " --- 1 --- " << endl;
    cout << tree.FaindAllData(parm_list_for_search, 1) << endl;
    cout << " --- 2 --- " << endl;
    cout << tree.FaindAllData(parm_list_for_search, 2) << endl;
    cout << " --- 3 --- " << endl;
    cout << tree.FaindAllData(parm_list_for_search, 3) << endl;
    cout << " --- end --- " << endl;
}