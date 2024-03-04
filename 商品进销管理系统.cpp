#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
#include <bits/stdc++.h>
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
    string price; // 家电单价
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

        cout << char_array_3[0] << char_array_3[1] << char_array_3[2] << endl;

        for (int i = 0; i < 4; i++)
        {
            out += base64_chars[char_array_4[i]];
        }
    }
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
LinkList displayinfo(LinkList head)
{
    FILE *fp;                  // 定义文件指针变量fp
    house *s;                  // 定义house结构体指针变量s
    LNode *p, *q;              // 定义LNode结构体指针变量p和q
    p = head;                  // 将head赋值给p
    fp = fopen("1.txt", "rb"); // 打开名为"1.txt"的文件，以二进制只读方式打开，并将文件指针赋值给fp
    if (!fp)                   // 如果文件打开失败
    {
        printf("没有相应的家电信息！"); // 输出提示信息
    }
    else // 如果文件打开成功
    {
        s = (house *)malloc(sizeof(house));                           // 分配一个house结构体大小的内存空间，并将其地址赋值给s
        printf("家电编号\t家电名称\t家电品牌\t家电价格\t家电数量\n"); // 输出表头信息
        while (!feof(fp))                                             // 当文件指针未到达文件末尾时循环执行
        {
            memset(s, 0, sizeof(house));
            if (fread(s, sizeof(struct houses), 1, fp) != 0) // 从文件中读取一个house大小的数据到s所指向的内存空间，并返回成功读取的数据个数，如果读取成功
            {
                printf("%d\t%s\t%s\t", s->id, base64_decode(s->name1).c_str(), base64_decode(s->name2).c_str()); // 输出家电信息
                cout << s -> price << "\t" << s->count <<  endl;
                q = (LNode *)malloc(sizeof(LNode));                                                                                          // 分配一个LNode结构体大小的内存空间，并将其地址赋值给q
                q->data.id = s->id;                                                                                                          // 将s的id赋值给q的data的id
                // cout << 333 << endl;
                q->data.name1 = base64_decode(s->name1).c_str(); // 将s的name1复制给q的data的name1
                q->data.name2 = base64_decode(s->name2).c_str(); // 将s的name2复制给q的data的name2
                // cout << 444 << endl;
                q->data.price = s->price; // 将s的price复制给q的data的price
                q->data.count = s->count;                        // 将s的count赋值给q的data的count
                // cout << "这是" << q->data.name1 << endl;

                // cout << s -> name1 << ' ' << q->data.name1 << endl;
                // cout << 222 << endl;
                // q->data.name1 = base64_decode(q->data.name1).c_str();
                // q->data.name2 = base64_decode(q->data.name2).c_str();
                // q->data.price = base64_decode(q->data.price).c_str();
                p->next = q; // 将q赋值给p的next指针
                p = p->next; // 将p指向下一个节点
            }
        }
        fclose(fp); // 关闭文件
    }
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
void sortByPrice(LinkList &L)
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
            if (p->data.price > p->next->data.price)
            {
                swapNodeData(p, p->next);
                swapped = true;
            }
            p = p->next;
        }
        q = p;
    } while (swapped);
}

// 主函数
int main()
{
    int choose, i;
    LinkList L, p;
    LNode *head;
    cout << " 欢迎来到商品管理系统!!!!!" << endl;
    cout << " 请与使用前输入1开启系统，并于退出前输入9进行文件的更新以及备份操作" << endl;
    cout << " 请按以下数字操作" << endl;
    cout << "----------------------------------1.建立商品链表(初始化）--------------------------------------" << endl;
    cout << "----------------------------------2.打开链表--------------------------------------" << endl;
    cout << "----------------------------------3.查找商品--------------------------------------" << endl;
    cout << "----------------------------------4.插入商品--------------------------------------" << endl;
    cout << "----------------------------------5.删除商品--------------------------------------" << endl;
    cout << "----------------------------------6.输出--------------------------------------" << endl;
    cout << "----------------------------------7.更新商品--------------------------------------" << endl;
    cout << "----------------------------------8.文件输入（保存）----------------------------------" << endl;
    cout << "----------------------------------9.文件输出----------------------------------" << endl;
    cout << "---------------------------------10.商品出库--------------------------------------" << endl;
    cout << "----------------------------------0.退出系统--------------------------------------" << endl
         << endl;
    cout << "----------------------------------11.按价格排序----------------------------------" << endl;

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
            break;
        case 1:
            if (InitList_L(L))
                cout << "线性链式表已成功建立！" << endl;
            else
                cout << "线性链式表建立失败！" << endl;
            break;
        case 2: // 输入
            if (CreateList_L(L))
                cout << "家电信息存储文件已经成功打开！" << endl;
            else
                cout << "家电信息存储文件打开失败！" << endl;
            break;
        case 3: // 查找
            int i;
            cout << "请您输入将要查找的家电编号" << endl;
            cin >> i;
            cout << "您要查找编号为" << i << "的家电信息如下:" << endl
                 << endl;
            GetElem(L, i);
            cout << "----------------------------------------------------------------------" << endl;
            break;
        case 4: // 插入
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
            break;
        case 5: // 删除
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
            break;
        case 6: // 输出
            LinkList p;
            cout << "家电信息如下:" << endl
                 << endl;
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
            break;
        case 7: // 更新
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
            break;
        case 8: // 文件输入
            FILE *fp;
            house *s;
            fp = fopen("1.txt", "wb");
            if (!fp)
                printf("打开文件失败！");
            else
            {
                LinkList p;
                s = (houses *)malloc(sizeof(houses));
                p = L->next;
                while (p)
                {
                    memset(s, 0, sizeof(house));
                    s->id = p->data.id;
                    // s->name1=p->data.name1;
                    // s->name2=(p->data.name2);
                    // s->price=(p->data.price);

                    s->name1 = base64_encode(p->data.name1).c_str();
                    s->name2 = base64_encode(p->data.name2).c_str();
                    s->price = p->data.price;
                    s->count = p->data.count;
                    fwrite(s, sizeof(struct houses), 1, fp);
                    p = p->next;
                }
                printf("存储数据成功！\n");
            }
            fclose(fp);
            break;
        case 9: // 文件输出
            LinkList head;
            printf("文件信息提取成功！\n");
            head = createNullList_link();
            displayinfo(head);
            break;
        case 10: // 出库
            int id, count;
            cout << "请输入要出库的家电编号：" << endl;
            cin >> id;
            cout << "请输入出库数量：" << endl;
            cin >> count;
            Outbound(L, id, count);
            break;
        case 11: // 按价格排序
            sortByPrice(L);
            cout << "按价格排序完成！" << endl;
            break;
        }
    }
    return 0;
}
