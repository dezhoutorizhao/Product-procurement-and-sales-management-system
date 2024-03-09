#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
using namespace std;

#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define Max 100
typedef int Status;
int length = 0;

typedef struct houses
{
    int id;       // 家电编号
    string name1; // 家电名称
    string name2; // 家电品牌
    int price;    // 家电单价
    int count;    // 家电数量
} house;

typedef struct LNode
{
    house data;         // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList;

// base64编码函数
string base64_encode(const string &in)
{
    string out;

    string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int i = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (i < in.size())
    {
        char_array_3[0] = in[i++];
        char_array_3[1] = (i < in.size()) ? in[i++] : 0;
        char_array_3[2] = (i < in.size()) ? in[i++] : 0;

        char_array_4[0] = (char_array_3[0] & 0xFC) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xF0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0F) << 2) + ((char_array_3[2] & 0xC0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3F;

        // cout << char_array_3[0] << char_array_3[1] << char_array_3[2] << endl;

        for (int i = 0; i < 4; i++)
        {
            out += base64_chars[char_array_4[i]];
        }
    }

    // cout << out << endl;

    return out;
}

// base64解码函数
string base64_decode(const string &encoded_string)
{
    string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string decoded_string = "";

    int i = 0;
    unsigned char char_array_4[4];
    unsigned char char_array_3[3];

    while (i < encoded_string.size())
    {
        for (int j = 0; j < 4; j++)
        {
            char_array_4[j] = base64_chars.find(encoded_string[i++]);
        }

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (int j = 0; j < 3; j++)
        {
            if (char_array_4[j + 1] == 64)
            {
                break;
            }
            decoded_string += char_array_3[j];
        }
    }
    // cout << decoded_string << "123" <<  endl;

    return decoded_string;
}
// 创建空链表
LinkList createNullList_link()
{
    LinkList llist = new LNode;
    if (llist)
        llist->next = NULL;
    else
        cout << "越界警告!\n";
    return llist;
}

// 初始化链表
Status InitList_L(LinkList &L)
{
    L = new LNode;
    L->next = NULL;
    return OK;
}

// 从文件中创建链表
Status CreateList_L(LinkList &L)
{
    LinkList p, r;
    r = L;
    fstream file;
    file.open("1.txt");
    if (!file)
    {
        cout << "没有找到该文件，文件打开失败！" << endl;
        exit(ERROR);
    }
    while (file >> r->data.id >> r->data.name1 >> r->data.name2 >> r->data.price >> r->data.count)
    {
        p = new LNode;
        p->next = NULL;
        r->next = p;
        r = p;
        length++;
    }
    file.close();
    return OK;
}

// 查找元素
Status GetElem(LinkList &L, int i)
{
    LinkList p = L->next;
    while (p)
    {
        if (p->data.id == i)
        {
            cout << p->data.id << "\t\t" << p->data.name1 << "\t\t" << p->data.name2 << "\t\t" << p->data.price << "\t\t" << p->data.count << endl;
            return OK;
        }
        else
        {
            p = p->next;
        }
    }
    cout << "没有查找到家电信息！" << endl;
    return ERROR;
}

// 插入元素
Status ListInsert_L(LinkList &L)
{
    int j;
    LinkList p, q, s;
    p = L;
    q = NULL;
    while (p != NULL)
    {
        q = p;
        p = p->next;
    }
    s = new LNode;
    cout << "请依次输入家电编号、家电名称、家电品牌、家电价格、家电数量：（以空格分隔）" << endl;
    cin >> s->data.id >> s->data.name1 >> s->data.name2 >> s->data.price >> s->data.count;
    s->next = p;
    if (q == NULL)
        L = s;
    else
        q->next = s;
    return OK;
}

// 删除元素
Status ListDelete_L(LinkList L, int i)
{
    int j;
    LinkList p, r;
    p = L;
    j = 1;
    if (L == NULL)
    {
        cout << "无信息！已返回主界面" << endl;
        return ERROR;
    }
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p == NULL || p->next == NULL)
    {
        cout << "无信息！已返回主界面" << endl;
        return ERROR;
    }
    r = p->next;
    p->next = r->next;
    free(r);
    cout << "您已经成功删除第" << i << "个数据" << endl;
    return OK;
}

// 更新元素
Status ListUpdate_L(LinkList &L, int i)
{
    int j;
    LinkList p, s, r;
    p = L;
    j = 1;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
    {
        return ERROR;
    }
    s = new LNode;
    cout << "请依次输入家电编号、家电名称、家电品牌、家电价格、家电数量：" << endl;
    cin >> s->data.id >> s->data.name1 >> s->data.name2 >> s->data.price >> s->data.count;
    r = p->next;
    p->next = r->next;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 从文件中读取家电信息并显示
// 从文件中读取家电信息并显示
LinkList displayinfo(LinkList head)
{
    std::ifstream fin("1.txt", std::ios::in); // 以输入模式打开文件
    if (!fin.is_open())                       // 如果文件打开失败
    {
        std::cout << "没有相应的家电信息！" << std::endl; // 输出提示信息
        return head;                                       // 返回原链表
    }

    LNode *p, *q;      // 定义LNode结构体指针变量p和q
    p = head;          // 将head赋值给p

    std::cout << "家电编号\t家电名称\t家电品牌\t家电价格\t家电数量" << std::endl; // 输出表头信息

    while (!fin.eof()) // 当文件指针未到达文件末尾时循环执行
    {
        house *s = new house; // 分配一个house结构体大小的内存空间，并将其地址赋值给s
        fin >> s->id >> s->name1 >> s->name2 >> s->price >> s->count; // 从文件中读取家电信息

        if (fin.eof()) { // 如果已经到达文件末尾，则释放内存并跳出循环
            delete s;
            break;
        }

        std::cout << s->id << "\t" << base64_decode(s->name1) << "\t" << base64_decode(s->name2) << "\t" << s->price << "\t" << s->count << std::endl; // 输出家电信息

        q = new LNode; // 分配一个LNode结构体大小的内存空间，并将其地址赋值给q
        q->data = *s;  // 将s所指向的内存中的数据复制到q的data中
        p->next = q;   // 将q赋值给p的next指针
        p = p->next;   // 将p指向下一个节点

        delete s; // 释放s所指向的内存空间
    }

    fin.close(); // 关闭文件
    return head; // 返回head
}


// 家电出库
Status Outbound(LinkList &L, int id, int count)
{
    LinkList p = L->next; // 创建指向链表头结点的指针p，指向第一个节点
    while (p)             // 循环遍历链表
    {
        if (p->data.id == id) // 判断当前节点的id是否与传入的id相等
        {
            if (p->data.count >= count) // 判断当前节点的库存是否大于等于出库数量
            {
                p->data.count -= count;       // 减去出库数量
                cout << "出库成功！" << endl; // 输出出库成功信息
                return OK;                    // 返回操作成功状态
            }
            else
            {
                cout << "库存不足，出库失败！" << endl; // 输出库存不足信息
                return ERROR;                           // 返回操作失败状态
            }
        }
        p = p->next; // 指针p指向下一个节点
    }
    cout << "未找到对应编号的家电，出库失败！" << endl; // 输出未找到对应编号的家电信息
    return ERROR;                                       // 返回操作失败状态
}

// 交换两个节点的数据
void swapNodeData(LNode *a, LNode *b)
{
    house temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// 价格排序
void sortByID(LinkList &L)
{
    if (L == NULL || L->next == NULL)
        return;

    LNode *p;
    LNode *q = NULL;
    bool swapped;
    do
    {
        swapped = false;
        p = L->next;
        while (p->next != q)
        {
            if (p->data.id > p->next->data.id)
            {
                swapNodeData(p, p->next);
                swapped = true;
            }
            p = p->next;
        }
        q = p;
    } while (swapped);
}

//编号排序
void sortByPrice(LinkList &L)
{
    if (L == NULL || L->next == NULL)
        return;

    LNode *p;
    LNode *q = NULL;
    bool id_swapped;
    do
    {
        id_swapped = false;
        p = L->next;
        while (p->next != q)
        {
            if (p->data.price > p->next->data.price)
            {
                swapNodeData(p, p->next);
                id_swapped = true;
            }
            p = p->next;
        }
        q = p;
    } while (id_swapped);
}

void Save(LinkList &L)
{
    std::ofstream fout("1.txt", std::ios::out); // 以输出模式打开文件，会自动创建文件
    if (!fout.is_open())
    {
        std::cout << "打开文件失败！" << std::endl;
        return;
    }

    LinkList p = L->next;
    while (p)
    {
        // 将数据以 UTF-8 编码保存到文件中
        fout << p->data.id << " " << base64_encode(p->data.name1) << " " << base64_encode(p->data.name2) << " " << p->data.price << " " << p->data.count << std::endl;
        p = p->next;
    }

    fout.close();
    std::cout << "存储数据成功！" << std::endl;
}

int main()
{
    int choose, i;
    LinkList L, p;
    LNode *head;
    InitList_L(L);
    cout << " 欢迎来到商品管理系统!!!!!" << endl;
    cout << " " << endl;
    cout << " 请按以下数字操作" << endl;
    // cout << "----------------------------------1.建立商品链(初始化）--------------------------------------" << endl;
    // cout << "----------------------------------2.打开链表--------------------------------------" << endl;
    cout << "----------------------------------1.插入商品--------------------------------------" << endl;
    cout << "----------------------------------2.查找商品--------------------------------------" << endl;
    cout << "----------------------------------3.删除商品--------------------------------------" << endl;
    cout << "----------------------------------4.输出全部商品-----------------------------------" << endl;
    cout << "----------------------------------5.更新个别商品--------------------------------------" << endl;
    // cout << "----------------------------------8.文件输入（保存）----------------------------------" << endl;
    // cout << "----------------------------------6.全部商品信息查看--------------------------------" << endl;
    cout << "--------------------------------- 6.商品出库登记--------------------------------------" << endl;
    cout << "----------------------------------7.商品信息排序----------------------------------" << endl;
    cout << "----------------------------------0.退出系统--------------------------------------" << endl;
    choose = -1;
    while (choose != 0)
    {
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "请选择:" << endl;
        cin >> choose;
        switch (choose)
        {
        case 0:
            cout << "您已经成功退出系统，欢迎您的到来！" << endl;
            Save(L);
            break;
        case 1: // 插入
            ListInsert_L(L);
            cout << "家电信息，如下所示:" << endl
                 << endl;
            cout << "家电编号-------家电名称-------家电品牌-------家电价格-------家电数量:" << endl;
            p = L->next;
            while (p)
            {
                cout << left << setw(15) << p->data.id << left << setw(15) << p->data.name1 << left << setw(15) << p->data.name2 << left << setw(15) << p->data.price << left << setw(15) << p->data.count << endl;
                p = p->next;
            }
            cout << "---------------------------------------------------------------------" << endl;
            Save(L);
            break;
        case 2: // 查找
            int i;
            cout << "请您输入将要查找的家电编号" << endl;
            cin >> i;
            cout << "您要查找编号为" << i << "的家电信息如下:" << endl
                 << endl;
            GetElem(L, i);
            cout << "----------------------------------------------------------------------" << endl;
            break;
        case 3: // 删除
            cout << "请您输入将要删除家电的位置:" << endl;
            cin >> i;
            ListDelete_L(L, i);
            // cout << "您已经成功删除第" << i << "个数据" << endl;
            cout << "家电信息，如下所示:" << endl
                 << endl;
            cout << "家电编号-------家电名称-------家电品牌-------家电价格-------家电数量:" << endl;
            p = L->next;
            while (p)
            {
                cout << left << setw(15) << p->data.id << left << setw(15) << p->data.name1 << left << setw(15) << p->data.name2 << left << setw(15) << p->data.price << left << setw(15) << p->data.count << endl;
                p = p->next;
            }
            cout << "---------------------------------------------------------------------" << endl;
            Save(L);
            break;
        case 4: // 文件输出
            LinkList head;
            printf("文件信息提取成功！\n");
            head = createNullList_link();
            displayinfo(head);
            break;
        case 5: // 更新
            cout << "请您输入在第几个位置更新家电:" << endl;
            cin >> i;
            ListUpdate_L(L, i);
            cout << "家电信息，如下所示:" << endl
                 << endl;
            cout << "家电编号-------家电名称-------家电品牌-------家电价格-------家电数量:" << endl;
            p = L->next;
            while (p)
            {
                cout << left << setw(15) << p->data.id << left << setw(15) << p->data.name1 << left << setw(15) << p->data.name2 << left << setw(15) << p->data.price << left << setw(15) << p->data.count << endl;
                p = p->next;
            }
            cout << "---------------------------------------------------------------------" << endl;
            Save(L);
            break;
        case 6: // 出库
            int id, count;
            cout << "请输入要出库的家电编号：" << endl;
            cin >> id;
            cout << "请输入出库数量：" << endl;
            cin >> count;
            Outbound(L, id, count);
            Save(L);
            break;
        case 7: // 商品排序
            int sub_option;
            cout << "请选择排序方式：" << endl;
            cout << "1. 按商品编号排序" << endl;
            cout << "2. 按商品价格排序" << endl;
            cin >> sub_option;
            switch (sub_option)
            {
            case 1:
                cout << "按商品编号排序：" << endl;
                sortByID(L);
                Save(L);
                // 执行按商品编号排序的操作
                break;
            case 2:
                cout << "按商品价格排序：" << endl;
                sortByPrice(L);
                Save(L);
                // 执行按商品价格排序的操作
                break;
            default:
                cout << "无效选项！" << endl;
                break;
            }
            break;
        default:
            cout << "请输入有效数字！" << endl;
            break;
        }
    }
}