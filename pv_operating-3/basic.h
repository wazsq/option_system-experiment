//
// Created by sce on 17-10-28.
//
#include <iostream>
#include <string>
using namespace std;

#ifndef PV_OPERATING_3_BASIC_H
#define PV_OPERATING_3_BASIC_H

struct pcb{
    int id; //进程id
    int pid; //父进程id
    string name; //进程名称
    int priority; //优先级
    int status;//状态
    int lasttime; //last execute time
    int tottime; //totle execute time
};

struct pnode{
    pcb *node;
    pnode *next;
    pnode *sub;
    pnode *brother;
};

struct semphore{
    string name; //名称
    int count;//默认为1
    int curid;//当前进程id
    pnode *wlist;//等待进程链表
};
const int INVALID_PROCESS = 0;
const int INVALID_SEMPHORE = 1;
const int INVALID_COMMAND = 2;
const int BUSY_PROCESS = 3;
const int INVALID_PARAMETER = 4;

void throwerr(int err_code){
    string errormess[5];
    errormess[0] = "无效的进程id";
    errormess[1] = "无效的信号量名称";
    errormess[2] = "无效的命令";
    errormess[3] =  "当前进程被占用或正在等待状态";
    errormess[4] = "无效的参数";
    cout << errormess[err_code] << endl;
}

pnode* findpnode(pnode *link[], int len, int id){
    for(int i = 0; i< len; i++){
        if(link[i]->node->id == id){
            return  link[i];
        }
    }
    return NULL;
}

int findsemphore(semphore list[],int len, string name){
    for(int i = 0; i < len; i ++){
        if(list[i].name == name){
            return i;
        }
    }
    return -1;
}

string substr_index(string s,int start, int end){
    if(start>end){
        cout << "请输入正确的参数"<<endl;
        return "";
    }
    string result = "";
    end = end>s.length()?s.length():end;

    for(int i = start; i< end;i++){
        result += s[i];
    }
    return result;
}




#endif //PV_OPERATING_3_BASIC_H
