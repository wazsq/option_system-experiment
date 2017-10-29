#include <iostream>
//#include <string.h>
using namespace std;
class node
{
public:
    int name;
    int arrtime;
//int round;
//int cputime;
    int needtime;
//int count;
//char state;
    node& operator= (const node& s);
    bool operator<(const node &t) const
    {
        if (arrtime!= t.arrtime) return arrtime < t.arrtime;
        else return false;
    }
}PCB;
node& node::operator= (const node& s)
{
    name=s.name ;
    arrtime=s.arrtime;
    needtime=s.needtime;
    return *this;
}
class MinHeap
{
private:
    node *heapArray;//存放堆数据的数组
    int CurrentSize; //当前堆中元素的数目
    int MaxSize; //堆所能荣乃的最大元素数目
    void swap(int pos_x,int pos_y); //交换位置 x 和 y
    void BuildHeap(); //创建堆
public:
    MinHeap(node arr[], int n);
    MinHeap(int n);//构造函数 ，表示初始化堆的最大元素数目
    ~MinHeap(){delete [] heapArray;}
    bool isLeaf(int pos); //如果是叶节点 返回 true
    int leftchild(int pos);//返回左儿子的位置
    int rightchild(int pos); //返回右儿子的位置
    int parent(int pos); //返回父节点的位置
    bool Remove(int pos, node & node);//删除指定下标的元素
    bool Insert(node & newNode); //向堆中插入新元素 newNode
    node & RemoveMin(); //从堆顶删除最小值
    void SiftUp(int position); //从 position 向上开始调整，使序列成为堆
    void SiftDown(int left); //筛选法函数，参数 left 表示 开始处理的数组下标
    void scanHeap(); //浏览最小堆中的元素
};
//构造函数
MinHeap::MinHeap(int n)
{
    while(n<=0)
    {
        cout<<"输入错误,重输： ";
        cin>>n;
        cout<<endl;
    }
    CurrentSize=0;
    MaxSize=n; //初始化堆容量
    heapArray=new node[MaxSize]; //创建堆空间
    BuildHeap();
}
//判断指定位置的元素是否为叶子
bool MinHeap::isLeaf(int pos)
{
    return(pos>=CurrentSize/2)&&(pos<CurrentSize);
}
//交换堆顶和最后一个元素
void MinHeap::swap(int pos_x, int pos_y)
{
    node temp=heapArray[pos_x];
    heapArray[pos_x]=heapArray[pos_y];
    heapArray[pos_y]=temp;
}
//创建最小堆
void MinHeap::BuildHeap()
{
    for(int i=CurrentSize/2-1;i>=0;i--) //反复调用筛选函数
        SiftDown(i);
}
//返回左儿子的位置
int MinHeap::leftchild(int pos)
{
    return 2*pos+1;
}
//返回右儿子的位置
int MinHeap::rightchild(int pos)
{
    return 2*pos+2;
}
//返回父节点的位置
int MinHeap::parent(int pos)
{
    return (pos-1)/2;
}
//向堆中插入新元素 newNode
bool MinHeap::Insert(node &newNode)
{
    if(CurrentSize==MaxSize)
        return false;
    heapArray[CurrentSize]=newNode;
    SiftUp(CurrentSize);
    CurrentSize++;
    return true;
}
//从 position 向上开始调整，使序列成为堆
void MinHeap::SiftUp(int position)
{
    int temppos=position; //存储现在的位置
    node temp=heapArray[temppos]; //获得现在位置元素的值
    while((temppos>0)&&( temp<heapArray[parent(temppos)])) //现在位置大于 0 并且该元 素的父节点大于该节点
    {
        heapArray[temppos]=heapArray[parent(temppos)]; //将父节点值赋值给该结点
        temppos=parent(temppos); //将现在位置指向父节点位置
    }
    heapArray[temppos]=temp; //最后的父节点位置的值为 temp
}
//从堆顶删除最小值
node & MinHeap::RemoveMin()
{
/* if(CurrentSize==0) //堆中没有元素 退出
{
cout<<"无进程"<<endl;
exit(1);
}*/
    swap(0,--CurrentSize);//交换堆顶和最后一个元素 同时堆的现有大小减去 1
    if(CurrentSize>1)
        SiftDown(0); //从堆顶开始向下筛选
    return heapArray[CurrentSize]; //返回最后
}
//删除给定下标的元素
bool MinHeap::Remove(int pos, node & nod)
{
    if((pos<0)||(pos>=CurrentSize)) //如果下标越界 返回 false
        return false;
    node temp = heapArray[pos]; //暂存要删除的元素值
    heapArray[pos]=heapArray[--CurrentSize]; //将最后一个元素放在要删除的元素的位置上
    SiftUp(pos);
    SiftDown(pos);
    nod=temp;
    return true;
}
//向下筛选元素
void MinHeap::SiftDown(int left)
{
    int i=left;//标识父节点
    int j=leftchild(i); //标识关键值较小的子结点
    node temp=heapArray[i];
//过筛
    while(j<CurrentSize)
    {
        if((j<CurrentSize-1)&&(heapArray[j+1] < heapArray[j]))
            j++; //指向右儿子
        if(heapArray[j]<temp)
        {
            heapArray[i]=heapArray[j];
            i=j;
            j=leftchild(j);
        }
        else break;
    }
    heapArray[i]=temp;
}
//浏览最小堆中的所有元素
void MinHeap::scanHeap()
{
    for(int i=0;i<CurrentSize;i++)
        cout<<"进程： "<<heapArray[i].name<<' '<<heapArray[i].arrtime<<' '
            <<heapArray[i].needtime<<endl;
}
MinHeap::MinHeap(node arr[], int n)
{
    MaxSize = n;
    CurrentSize = n;
    heapArray = arr;
    int currentPos = (n-1)/2;
    while(currentPos>=0)
    {
        SiftDown(currentPos);
        currentPos--;
    }
}
int main()
{
    node *heap2,temp;
    int i,n,time=0,arrtime;
    char flag='y',aFlag;
    int name;
    while(flag=='y'||flag=='Y')
    {
        cout<<"输入进程数： ";
        cin>>n;
        heap2 = new node[n];
        for(i=0;i<n;i++)
        {
            cout<<"ID\\arrivetime\\needtime： ";
            cin>>heap2[i].name;
            cin>>heap2[i].arrtime;
            cin>>heap2[i].needtime;
        }
        MinHeap heap(heap2,n);
        heap.scanHeap();
        for(i=0;i<n;i++)
        {
            temp=heap.RemoveMin();
            cout<<time<<":"<<"进程"<<temp.name<<endl;
            time+=temp.needtime;
        }
        cout <<"是否改变到达时间<Y\\N>:";
        cin>>aFlag;
        while(aFlag=='y'||aFlag=='Y')
        {
            cout<<"输入要改变到达时间的进程号、到达时间： ";
            cin>>name;
            cin>>arrtime;
            for(i=0;i<n;i++)
            {
                if(heap2[i].name==name)
                {
                    heap2[i].arrtime=arrtime;
                }
            }
            cout<<"是否继续改变到达时间<Y\\N>:";
            cin>>aFlag;
        }
        if(i)
        {
            MinHeap heap1(heap2,n);
            heap1.scanHeap();
            for(i=0;i<n;i++)
            {
                temp=heap1.RemoveMin();
                cout<<time<<":"<<"进程"<<temp.name<<endl;
                time+=temp.needtime;
            }
        }
        cout<<"是否继续<Y\\N>:";
        cin>>flag;
    }
    return 0;
}