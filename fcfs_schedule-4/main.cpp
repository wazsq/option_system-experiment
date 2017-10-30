#include "basic.h"

int main() {
    vector<pcb> pcblist;
    while (true) {
        cout << "root:";
        string comand;
        cin >> comand;
        if(comand == "exit"){
            break;
        }
        //进入生成进程命令
        if(comand == "createpc"){
            createprocess(pcblist);
        }else if(comand == "showpc"){ //打印所有进程信息
            showprocess(pcblist);
        }else if(comand == "editpc"){
            editpcb(pcblist);
        }else if(comand == "fcfs" || comand == "FCFS"){
            FCFS(pcblist);
        }else{
            throwerr(INVALID_COMMAND);
        }
    }
    return 0;
}