# Laba_Sem_2___14.05.23

В папке Laba_with_GUI_CLR содержит неготовый проект графической формы. Нету связи с библиотекой, только графическая оболочка. В будующем может быть доделаю, а мб и хрен забью.
В папке testLaba_26.02.23 содержатся файлыт  библиотеки и пример кода с ее использованием.

Короткий гайд по использованию библиотеки
файлы фиблиотеки находятся по адресу \..\testLaba_26.02.23\testLaba_26.02.23\
CMass.h - файл с классом TMass он содержит в себе массив ссылок и и процедуры для работы с ним.
  TMass хранит в себе ссылки на какие-либо обьекты в БИНАРНОМ порядке(по алфавиту). Для этого в нем есть функция cmp, которая назначается динамически в конструкторе или отдельно через сеттор.
CDataLib.h и CDataLib.cpp - файлы с классами TStringMass, TData, TSpecificationMass,  а также функции:
StrCMP - сравнивает две строки в алфавитном порядке. подробнее сожете узнать http://cppstudio.com/post/707/
TDataCMP - сравнивает два TData, пока только по Caption, но вы можете добавить и name.
TDataCMPstr - сравнивает Caption обьекта TData и std::string. Нужно для бинарного поиска в дереве.

CTreeLib.h - файл с классом TTree и вспомогательными к нему классами.
TTree - класс дерева. Как использовать - описано в функции main в testLaba_26.02.23.cpp.

```c
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
    TData parametr_1_ROOT(-1, "ROOT");
    TData parametr_2_color(0, "Color","Red","color of product");
    TData parametr_3_window(0,"the presence of a window", "with a window","parameter that determines the presence of a window in the cabinet");

    //заполняем массив спецификаций продукта(его данные и характеристики)
    product_closet.Spec.add(parametr_1_ROOT);
    product_closet.Spec.add(parametr_2_color);
    product_closet.Spec.add(parametr_3_window);

    //устанавливаем функцию поиска параметров у продуктов для дерева
    tree.setGetData(CMP);
    //добавляем продукт по их внутреннему списку параметров(характеристик продкта)
    cout << tree.AddProduct(product_closet, product_closet.Spec.getCaptionMass(), 2) << endl;

    //Вывод всех уровней дерева
    cout << " --- 0 --- " << endl;
    cout << tree.FaindAllData(parm_list_for_search, 0) << endl;
    cout << " --- 1 --- " << endl;
    cout << tree.FaindAllData(parm_list_for_search, 1) << endl;
    cout << " --- 2 --- " << endl;
    cout << tree.FaindAllData(parm_list_for_search, 2) << endl;
    cout << " --- 3 --- " << endl;
    cout << tree.FaindAllData(parm_list_for_search, 3) << endl;
    cout << " --- end --- " << endl;
```