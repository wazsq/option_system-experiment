#include "basic.h"

const int PLINK_LEN = 20;
const int SEMLIST_LEN = 5;
pnode *plink[PLINK_LEN];
semphore semlist[SEMLIST_LEN];
void wait(string sem_name, int id){
    pnode *p;
    semphore *sem;
    p = findpnode(plink, PLINK_LEN, id);
    int sem_index = findsemphore(semlist, SEMLIST_LEN, sem_name);
    if(sem_index == -1){
        throwerr(INVALID_SEMPHORE);
        return;
    }
    if(!p){
        throwerr(INVALID_PROCESS);
        return;
    }
    if(p->node->status != 1){
        throwerr(BUSY_PROCESS);
        return;;
    }
    sem = &semlist[sem_index];
    //没有进程占用的时候

    sem->count --;
    p->node->status = 0;
    if(sem->count == 0){
        sem->curid = id;
    }
    else if(sem->count == -1){
        sem->wlist = p;
    }else if(sem->count < -1){
        pnode *wait;
        for(wait = sem->wlist; wait->next;wait = wait->next);
        wait->next = p;
    }
}

void signal(string sem_name){
    semphore *sem;
    pnode *p;
    int sem_index = findsemphore(semlist, SEMLIST_LEN, sem_name);
    if(sem_index == -1){
        throwerr(INVALID_SEMPHORE);
        return;
    }
    sem = &semlist[sem_index];
    if(sem->count == 1){
        cout << "当前信号量无进程等待" << endl;
        return;
    }
    p = findpnode(plink, PLINK_LEN, sem->curid);
    p->node->status = 1;
    if(sem->wlist){
        sem->curid = sem->wlist->node->id;
        sem->wlist = sem->wlist->next;
    }
    sem->count ++;
}

void showdetail(){
    pnode *tmp;
    for(int i =0; i < SEMLIST_LEN; i++){
        if(semlist[i].count <= 0){
            cout << semlist[i].name<< ":(currid  "<<semlist[i].curid << ") ";
            if(semlist[i].wlist){
                cout << " (wlist_id  ";
                tmp = semlist[i].wlist;
                for(; tmp; tmp = tmp->next){
                    cout << tmp->node->id<< " ";
                }
                cout<<")";
            }
        }else{
            cout << semlist[i].name<< ":";
        }
        cout<<"\n";
    }


}

void initData(){
    string tmp = "s";
    for(int i = 0; i< SEMLIST_LEN;i ++){
        semlist[i].name = tmp + to_string(i);
        semlist[i].count = 1;
        semlist[i].wlist = NULL;
    }
    for(int j = 0; j < PLINK_LEN; j++){
        plink[j] = new pnode;
        plink[j]->node =new pcb;
        plink[j]->node->id = j;
        plink[j]->node->status = 1;
        plink[j]->next = NULL;
        plink[j]->brother = NULL;
        plink[j]->sub = NULL;
    }
}


int main() {
    string s;
    initData();
    string command;
    string para[2];
    while (true){
        cout<< "cmd:";
        cin >> command;
        if(command == "exit"){
            break;
        }else if(command == "showdetail"){
            showdetail();
        }else if(command.find("wait") == 0){
            para[0] = substr_index(command, command.find('(') +1, command.find(','));
            para[1] = substr_index(command,command.find(',')+1,command.find(')'));
            if(para[0] != "" && para[1] != ""){
                wait(para[0],stoi(para[1]));
            }else{
                throwerr(INVALID_PARAMETER);
            }
        }else if(command.find("signal") == 0){
            para[0] = substr_index(command, command.find('(') +1, command.find(')'));
            if(para[0] != ""){
                signal(para[0]);
            }else{
                throwerr(INVALID_PARAMETER);
            }
        }else{
            throwerr(INVALID_COMMAND);
        }
    }
    return 0;
}