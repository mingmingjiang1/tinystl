#ifndef POOL_H
#define POOL_H

#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>
using namespace std;

template <int ObjectSize, int NumofObjects = 20>
class MemPool
{
private:
    pthread_mutex_t mutex; // 注意如果是多线程需要加锁
    // memory block内存块结构体
    struct MemBlock
    {
        MemBlock *pNext;
        FreeNode data[NumofObjects];
    };

    // freeNode空闲节点结
    struct FreeNode
    {
        FreeNode *pNext;
        char data[ObjectSize];
    };

    FreeNode *freeNodeHeader;
    MemBlock *memBlockHeader;

public:
    MemPool()
    {
        freeNodeHeader = NULL;
        memBlockHeader = NULL;
    }

    // 内存池析构函数，删除每一个内存块节点
    ~MemPool()
    {
        MemBlock *ptr;
        while (memBlockHeader)
        {
            ptr = memBlockHeader->pNext;
            delete memBlockHeader;
            memBlockHeader = ptr;
        }
    }
    // 用于分配一个可用的空闲结点
    void *malloc();
    // 回收一个空闲结点
    void free(void *);
};

// 分配空闲的节点
template <int ObjectSize, int NumofObjects>
void *MemPool<ObjectSize, NumofObjects>::malloc()
{
    // 加锁
    pthread_mutex_lock(&mutex);
    // 无空闲节点，可能是第一次申请，也可能是之前申请的都用完了
    if (freeNodeHeader == NULL)
    {
        MemBlock *newBlock = new MemBlock;
        newBlock->pNext = NULL;
        // freeNodeHeader指向内存块的第一个空闲区
        freeNodeHeader = &newBlock->data[0];
        // 将这个内存块的所有空闲结点串起来
        for (int i = 1; i < NumofObjects; ++i)
        {
            newBlock->data[i - 1].pNext = &newBlock->data[i];
        }
        newBlock->data[NumofObjects - 1].pNext = NULL;

        // 首次申请内存块，那么他就是第一块
        if (memBlockHeader == NULL)
        {
            memBlockHeader = newBlock;
        }
        else
        {
            // 将新内存块加入到内存块链表头部
            // 其实插入尾部也可以，本身看有没有空闲内存块只要看FreeNodeHeader是不是空就行，所以对于menBlockHeader并没有前后之分
            newBlock->pNext = memBlockHeader;
            memBlockHeader = newBlock;
        }
    }
    // 返回空节点闲链表的第一个节点
    void *freeNode = freeNodeHeader;
    freeNodeHeader = freeNodeHeader->pNext;
    // 去锁
    pthread_mutex_unlock(&mutex);
    return freeNode;
}

// 释放已经分配的节点，直接插入freeNode队首即可
template <int ObjectSize, int NumofObjects>
void MemPool<ObjectSize, NumofObjects>::free(void *p)
{
    // 先加锁
    pthread_mutex_lock(&mutex);

    FreeNode *pNode = (FreeNode *)p;
    pNode->pNext = freeNodeHeader; // 将释放的节点插入空闲节点头部
    freeNodeHeader = pNode;

    pthread_mutex_unlock(&mutex);
}

// 我们用到的用于向内存池申请空间的类
class ActualClass
{
    static int count;
    int No;

public:
    ActualClass()
    {
        No = count;
        count++;
    }

    void print()
    {
        cout << this << ": ";
        cout << "the " << No << "th object" << endl;
    }
    // 向内存池申请和删除空间的方法
    void *operator new(size_t size);
    void operator delete(void *p);
};

// 定义内存池对象
MemPool<sizeof(ActualClass), 2> mp;

// 申请一块大小为sizeof(ActualClass)大小的空间，返回指针指向这块空间
void *ActualClass::operator new(size_t size)
{
    return mp.malloc();
}

// 删除这块申请的空间
void ActualClass::operator delete(void *p)
{
    mp.free(p);
}

int ActualClass::count = 0;

// 测试内存池的函数
void AchieveMemPool()
{
    // 申请一块sizeof(ActualClass)大小的内存空间，指针p1指向这块空间
    ActualClass *p1 = new ActualClass;
    p1->print();

    // 同样申请一块sizeof(ActualClass)大小的内存空间
    ActualClass *p2 = new ActualClass;
    p2->print();
    delete p1;

    p1 = new ActualClass;
    p1->print();

    delete p1;
    delete p2;
}


#endif // POOL_H

/* 
usage:
 定义内存池对象
    MemPool<sizeof(ActualClass), 2> mp; // 每个内存池的大小，多少个内存池
 分配内存
    ActualClass *p1 = new ActualClass; //
 释放内存
    delete p1
*/
