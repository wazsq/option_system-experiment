#include "basic.h"

int M; //总进程数
int N; //资源种类
int All[W];//各种资源的数目总和
int Max[W][R]; //M个进程对N类资源最大资源需求量
int Available[R]; //系统可用资源数
int Allocation[W][R]; //M个进程已经得到N类资源的资源量
int Need[W][R]; //M个进程还需要N类资源的资源量
int Request[R]; //请求资源个数

void output() //输出资源分配情况
{
    int i, j;
    cout << endl;
    cout << "各种资源的总数量:" << endl;
    for (j = 0; j < N; j++)
        cout << " 资源" << j << ": " << All[j] << endl;
    cout << endl;
    cout << "目前各种资源可利用的数量为:" << endl;
    for (j = 0; j < N; j++)
        cout << "    资源" << j << ": " << Available[j] << endl;
    cout << endl << endl;
    cout << "各进程还需要的资源数量:" << endl;
    for (j = 0; j < N; j++) { cout << "     资源" << j << "  "; }
    cout << endl;
    for (i = 0; i < M; i++) {
        cout << "进程" << i << ":   ";
        for (j = 0; j < N; j++)
            cout << Need[i][j] << "           ";;
        cout << endl;
    }
    cout << endl;
    cout << "各进程已经分配得到的资源量: " << endl << endl;
    for (j = 0; j < N; j++) { cout << "       资源" << j << "  "; }
    cout << endl;
    for (i = 0; i < M; i++) {
        cout << "进程" << i << ":    ";
        for (j = 0; j < N; j++)
            cout << Allocation[i][j] << "           ";
        cout << endl;
    }
    cout << endl;
}

/**
 * 分配资源
 * @param k
 */
void distribute(int k) {
    int j;
    for (j = 0; j < N; j++) {
        Available[j] = Available[j] - Request[j];
        Allocation[k][j] = Allocation[k][j] + Request[j];
        Need[k][j] = Need[k][j] - Request[j];//第k个进程对第j中资源还需要的资源量
    }
}

/**
 * 回滚函数
 * @param k
 */
void restore(int k) {
    int j;
    for (j = 0; j < N; j++) {
        Available[j] = Available[j] + Request[j];
        Allocation[k][j] = Allocation[k][j] - Request[j];
        Need[k][j] = Need[k][j] + Request[j];
    }
}

/**
 * 检查安全性
 * @return
 */
int check() {
    int WORK[R], FINISH[W];//WORK[R]是系统可提供给进程继续运行所需的各类资源数目
    int i, j;
    for (j = 0; j < N; j++) WORK[j] = Available[j];//刚开始 系统可提供给进程继续运行所需的j类资源数目 等于j类可用资源数目
    for (i = 0; i < M; i++) FINISH[i] = FALSE;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (FINISH[i] == FALSE && Need[i][j] <= WORK[j]) {
                WORK[j] = WORK[i] + Allocation[i][j];
            }
        }
        FINISH[i] = TRUE;
    }

    for (i = 0; i < M; i++) {
        if (FINISH[i] == FALSE) {
            cout << endl;
            cout << " 系统不安全! 本次资源申请不成功!!!" << endl;
            cout << endl;
            return 1;
        } else {
            cout << endl;
            cout << " 经安全性检查，系统安全，本次分配成功。" << endl;
            cout << endl;

        }
    }
    return 0;
}

/**
 * 银行家算法
 */
void bank() {
    int i = 0, j = 0;
    char flag = 'Y';
    while (flag == 'Y' || flag == 'y') {
        i = -1;
        while (i < 0 || i >= M) {
            cout << endl << " 请输入需申请资源的进程号:";
            cin >> i;
            if (i < 0 || i >= M) cout << " 输入的进程号不存在，重新输入!" << endl;
        }
        for (j = 0; j < N; j++) {
            cout << " 资源" << j << ": ";
            cin >> Request[j];
            if (Request[j] > Need[i][j]) //若请求的资源数大于进程还需要i类资源的资源量j
            {
                cout << endl << " 进程" << i << "申请的资源数大于进程  " << i << "   还需要" << j << "类资源的数量!";
                cout << " 若继续执行系统将处于不安全状态!" << endl;
                flag = 'N';
                break;
            } else {
                if (Request[j] > Available[j]) //若请求的资源数大于可用资源数
                {
                    cout << endl << " 进程" << i << "申请的资源数大于系统可用" << j << "类资源的数量!";
                    cout << " 若继续执行系统将处于不安全状态!" << endl;
                    flag = 'N';
                    break;
                }
            }
        }
        if (flag == 'Y' || flag == 'y') {
            distribute(i); //调用change(i)函数，改变资源数
            if (check()) //若系统安全
            {
                restore(i); //调用restore(i)函数，恢复资源数
                output();   //输出资源分配情况
            } else       //若系统不安全
                output(); //输出资源分配情况
        } else      //若flag=N||flag=n
            cout << endl;
        cout << " 是否继续银行家算法演示,按'Y'或'y'键继续,按'N'或'n'键退出演示: ";
        cin >> flag;
    }
}

int main() //主函数
{
    int i = 0, j = 0, p;
    cout << endl << "请输入总进程数:";
    cin >> M;
    cout << "请输入总资源种类:";
    cin >> N;
    cout << "请输入各类资源总数:";
    for (i = 0; i < N; i++)
        cin >> All[i];
    cout << "输入各进程所需要的各类资源的最大数量:" << endl;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            do {
                cin >> Max[i][j];
                if (Max[i][j] > All[j])
                    cout << endl << "占有资源超过了声明的该资源总数,请重新输入" << endl;
            } while (Max[i][j] > All[j]);
        }
    }
    cout << "输入各进程已经分配的各类资源的数量:" << endl;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            do {
                cin >> Allocation[i][j];
                if (Allocation[i][j] > Max[i][j])
                    cout << endl << "超过了最大资源数,请重新输入" << endl;
            } while (Allocation[i][j] > Max[i][j]);
        }
    }
    for (j = 0; j < N; j++)  //初始化资源数量
    {
        p = All[j];
        for (i = 0; i < M; i++) {
            p = p - Allocation[i][j];//减去已经被占据的资源
            Available[j] = p;
            if (Available[j] < 0)
                Available[j] = 0;
        }
    }
    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
    output();
    bank();
    return 0;
}