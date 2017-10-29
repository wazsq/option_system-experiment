//
// Created by sce on 17-10-29.
//
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef FCFS_SCHEDULE_4_BASIC_H
#define FCFS_SCHEDULE_4_BASIC_H


struct pcb {
    int id; //进程id
    int cometime; //到达时间
    int servertime; //服务时间
    int starttime; //开始执行时间
    int finishtime; //完成时间
    int turtime; //周转时间
    int righttime; //带权周转时间
};

struct pnode {
    pcb *node;
    pnode *next;
};

/***
 *
 * @param err_code
 */
void throwerr(int err_code);

/***
 *
 * @param str 传入字符串
 * @return  判断是否是数字
 */
bool isnum(string str);

/***
 * 创建进程的命令
 */
void createprocess(vector<pcb> &list);

/**
 * 打印进程的详细情况
 * 支持在root下打印
 */
void showprocess(vector<pcb> &list);

/**
 *
 * @param p1 pcb
 * @param p2 pcb
 * @return true or false 比较pcb的到达时间，升序排列
 */
bool cmpfunc(pcb &p1, pcb &p2);

/**
 *  修改指定进程的到达时间
 * @param list 进程向量
 * @param id  要修改的进程id
 * @param cometime 修改的值
 */
void editpcbcometime(vector<pcb> &list, int id, int cometime);

/**
 * 进入修改进程的命令，在root下识别
 * @param list
 */
void editpcb(vector<pcb> &list);

/**
 * 对进程进行FCFS算法 并打印结果
 * @param list
 */
void FCFS(vector<pcb> &list);

/**
 * 输出制定长度的空格
 * @param len
 */
void printspace(int len);

/**
 * 打印经过算法调度后的结果
 * @param list
 */
void showpcresult(vector<pcb> &list);

const int INVALID_PROCESS = 0;
const int INVALID_SEMPHORE = 1;
const int INVALID_COMMAND = 2;
const int BUSY_PROCESS = 3;
const int INVALID_PARAMETER = 4;

void throwerr(int err_code) {
    string errormess[5];
    errormess[0] = "无效的进程id";
    errormess[1] = "无效的信号量名称";
    errormess[2] = "无效的命令";
    errormess[3] = "当前进程被占用或正在等待状态";
    errormess[4] = "无效的参数";
    cout << errormess[err_code] << endl;
}

bool isnum(string str) {
    stringstream sin(str);
    double d;
    char c;
    if (!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}


void createprocess(vector<pcb> &list) {

    while (true) {
        cout << "create pcb($id $cometime $servertime):";
        string comand[3];
        cin >> comand[0];
        if (comand[0] == "exit" || comand[0] == "end") {
            break;
        } else if (isnum(comand[0])) { //判断输入的参数是不是数字

            int id = stoi(comand[0]);
            int cometime;
            int servertime;
            cin >> comand[1];
            cin >> comand[2];
            if (isnum(comand[1]) && isnum(comand[2])) {
                cometime = stoi(comand[1]);
                servertime = stoi(comand[2]);
                pcb tmp;
                tmp.id = id;
                tmp.cometime = cometime;
                tmp.servertime = servertime;
                list.push_back(tmp);
            } else {
                throwerr(INVALID_PARAMETER);
                continue;
            }


        } else if (comand[0] == "showpc") {
            showprocess(list);
        } else {
            throwerr(INVALID_COMMAND);
        }
    }
}

void showprocess(vector<pcb> &list) {
    pcb tmp;
    for (vector<pcb>::iterator it = list.begin(); it < list.end(); ++it) {
        pcb tmp = *it;
        cout << tmp.id << ":(cometime: " << tmp.cometime << " ) (servertime: " << tmp.servertime << " )" << endl;
    }

}

bool cmpfunc(pcb &p1, pcb &p2) {
    return p1.cometime < p2.cometime;
}

void editpcbcometime(vector<pcb> &list, int id, int cometime) {
    for (vector<pcb>::iterator it = list.begin(); it < list.end(); ++it) {
        if ((*it).id == id) {
            (*it).cometime = cometime;
            return;
        }
    }
    throwerr(INVALID_PARAMETER);
}

void editpcb(vector<pcb> &list) {
    while (true) {
        cout << "editpcb($command):";
        string command[3];
        cin >> command[0];
        if (command[0] == "exit" || command[0] == "end") {
            break;
        } else if (command[0] == "cometime") {
            for (;;) {
                cout << "editpcb/cometime($id $cometime):";
                string com[2];
                cin >> com[0];
                if (com[0] == "exit" || com[0] == "end") {
                    break;
                } else if (isnum(com[0])) {
                    cin >> com[1];
                    if (isnum(com[1])) {
                        editpcbcometime(list, stoi(com[0]), stoi(com[1]));
                    } else {
                        throwerr(INVALID_PARAMETER);
                        continue;
                    }
                } else if (com[0] == "showpc") {
                    showprocess(list);
                } else {
                    throwerr(INVALID_COMMAND);
                    continue;
                }
            }
        } else if (command[0] == "showpc") {
            showprocess(list);
        }
    }
}

void printspace(int len) {
    for (int i = 0; i < len; i++) {
        cout << " ";
    }
}

void showpcresult(vector<pcb> &list) {
    cout << "进程号";
    printspace(10);
    cout << "到达时间";
    printspace(10);
    cout << "服务时间";
    printspace(10);
    cout << "开始执行时间" << endl;
    for (vector<pcb>::iterator it = list.begin(); it < list.end(); ++it) {
        cout << (*it).id;
        printspace(15 - (*it).id / 10);
        cout << (*it).cometime;
        printspace(15 - (*it).cometime / 10);
        cout << (*it).servertime;
        printspace(15 - (*it).servertime / 10);
        cout << (*it).starttime;
        cout << endl;
    }
}

void FCFS(vector<pcb> &list) {
    sort(list.begin(), list.end(), cmpfunc);
    int currtime = 0;//当前系统时间

    for (vector<pcb>::iterator it = list.begin(); it < list.end(); ++it) {
        if (currtime < (*it).cometime) {
            currtime = (*it).cometime;
        }
        (*it).starttime = currtime;
        (*it).finishtime = currtime + (*it).servertime;
        currtime += (*it).servertime;
    }
    showpcresult(list);
}

#endif //FCFS_SCHEDULE_4_BASIC_H
