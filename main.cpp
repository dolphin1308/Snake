#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/exception.h>
#include "jdbc/mysql_driver.h"


#define U 1
#define D 2
#define L 3 
#define R 4       //蛇的状态，U：上 ；D：下；L:左 R：右

typedef struct SNAKE //蛇身的一个节点
{
    int x;
    int y;
    struct SNAKE* next;
}snake;

//全局变量//
int score = 0, add = 10;//总得分与每次吃食物得分。
int status, sleeptime = 200;//每次运行的时间间隔
snake* head, * food;//蛇头指针，食物指针
snake* q;//遍历蛇的时候用到的指针
int endgamestatus = 0; //游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。

// 数据库连接
sql::mysql::MySQL_Driver* driver;
sql::Connection* con;
bool isLoggedI = false; // 登录状态
std::string currentUser; //用户名
time_t gameStartTime; //游戏开始时间

// 新增功能

// 创建用户表和游戏日志表
void createTables() {
    try {
        sql::Statement* stmt = con->createStatement();

        // 创建用户表
        std::string createUserTableSQL = "CREATE TABLE IF NOT EXISTS users ("
            "id INT AUTO_INCREMENT PRIMARY KEY,"
            "username VARCHAR(50) NOT NULL UNIQUE,"
            "password VARCHAR(50) NOT NULL)";
        stmt->execute(createUserTableSQL);

        // 创建游戏日志表
        std::string createGameLogTableSQL = "CREATE TABLE IF NOT EXISTS game_logs ("
            "id INT AUTO_INCREMENT PRIMARY KEY,"
            "user_id INT NOT NULL,"
            "username VARCHAR(50) NOT NULL,"
            "start_time DATETIME NOT NULL,"
            "duration INT NOT NULL,"
            "score INT NOT NULL,"
            "FOREIGN KEY (user_id) REFERENCES users(id))";
        stmt->execute(createGameLogTableSQL);

        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "创建表失败: " << e.what() << std::endl;
    }
}

// 用户注册函数
bool registerUser() {
    try {
        std::string username, password;
        std::cout << "请输入用户名: ";
        std::cin >> username;
        std::cout << "请输入密码: ";
        std::cin >> password;
        sql::Statement* stmt = con->createStatement();
        std::string checkSQL = "SELECT * FROM users WHERE username = '" + username + "'";
        sql::ResultSet* res = stmt->executeQuery(checkSQL);

        if (res->next()) {
            std::cout << "用户名已存在，请重新注册！" << std::endl;
            delete res;
            delete stmt;
            return false;
        }

        std::string insertSQL = "INSERT INTO users (username, password) VALUES ('" +
            username + "', '" + password + "')";
        stmt->execute(insertSQL);

        delete stmt;
        std::cout << "注册成功！" << std::endl;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cout << "注册失败: " << e.what() << std::endl;
        return false;
    }
}

// 用户登录函数
bool loginUser() {
    try {
        std::string username, password;
        std::cout << "请输入用户名: ";
        std::cin >> username;
        std::cout << "请输入密码: ";
        std::cin >> password;

        sql::Statement* stmt = con->createStatement();
        std::string loginSQL = "SELECT * FROM users WHERE username = '" + username +
            "' AND password = '" + password + "'";
        sql::ResultSet* res = stmt->executeQuery(loginSQL);

        bool success = res->next();
        if (success) {
            isLoggedI = true;
            currentUser = username;
            std::cout << "登录成功！" << std::endl;
        }
        else {
            std::cout << "用户名或密码错误！" << std::endl;
        }

        delete res;
        delete stmt;
        return success;
    }
    catch (sql::SQLException& e) {
        std::cout << "登录失败: " << e.what() << std::endl;
        return false;
    }
}

// 记录游戏日志
void recordGameLog(int score) {
    try {
        time_t endTime = time(NULL);
        int duration = (int)difftime(endTime, gameStartTime);

        sql::Statement* stmt = con->createStatement();
        std::string getUserIdSQL = "SELECT id FROM users WHERE username = '" + currentUser + "'";
        sql::ResultSet* res = stmt->executeQuery(getUserIdSQL);

        if (res->next()) {
            int userId = res->getInt("id");
            std::string insertLogSQL = "INSERT INTO game_logs (user_id, username, start_time, duration, score) "
                "VALUES (" + std::to_string(userId) + ", '" + currentUser + "', "
                "FROM_UNIXTIME(" + std::to_string(gameStartTime) + "), "
                + std::to_string(duration) + ", " + std::to_string(score) + ")";
            stmt->execute(insertLogSQL);
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cout << "记录游戏日志失败: " << e.what() << std::endl;
    }
}

// 显示游戏日志
void showGameLogs() {
    try {
        system("cls");
        std::cout << "游戏日志记录：" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        sql::Statement* stmt = con->createStatement();
        std::string getLogsSQL = "SELECT username, start_time, duration, score FROM game_logs "
            "ORDER BY start_time DESC LIMIT 10";
        sql::ResultSet* res = stmt->executeQuery(getLogsSQL);

        while (res->next()) {
            std::cout << "用户名: " << res->getString("username") << std::endl;
            std::cout << "开始时间: " << res->getString("start_time") << std::endl;
            std::cout << "游戏时长: " << res->getInt("duration") << "秒" << std::endl;
            std::cout << "得分: " << res->getInt("score") << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }

        delete res;
        delete stmt;
        system("pause");
    }
    catch (sql::SQLException& e) {
        std::cout << "获取游戏日志失败: " << e.what() << std::endl;
        system("pause");
    }
}

// 初始化数据库连接
bool initDatabase() {
    try {
        // 注册MySQL驱动
        driver = sql::mysql::get_mysql_driver_instance();

        // 获取数据库连接对象
        con = driver->connect("tcp://localhost:3306", "root", "pxx10086");

        // 选择数据库
        con->setSchema("software");

        // 创建用户表和游戏日志表
        createTables();
        return true;
    }
    catch (sql::SQLException& e) {
        std::cout << "数据库连接失败: " << e.what() << std::endl;
        return false;
    }
}

//声明全部函数//
void Pos();
void creatMap();
void initsnake();
int biteself();
void createfood();
void cantcrosswall();
void snakemove();
void pause();
void gamecircle();
void welcometogame();
void endgame();
void gamestart();

void Pos(int x, int y)//设置光标位置
{
    COORD pos;
    HANDLE hOutput;
    pos.X = x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, pos);
}

void creatMap()//创建地图
{
    int i;
    for (i = 0; i < 58; i += 2)//打印上下边框
    {
        Pos(i, 0);
        printf("■");
        Pos(i, 26);
        printf("■");
    }
    for (i = 1; i < 26; i++)//打印左右边框
    {
        Pos(0, i);
        printf("■");
        Pos(56, i);
        printf("■");
    }
}

void initsnake()//初始化蛇身
{
    snake* tail;
    int i;
    tail = (snake*)malloc(sizeof(snake));//从蛇尾开始，头插法，以x,y设定开始的位置//
    tail->x = 24;
    tail->y = 5;
    tail->next = NULL;
    for (i = 1; i <= 4; i++)
    {
        head = (snake*)malloc(sizeof(snake));
        head->next = tail;
        head->x = 24 + 2 * i;
        head->y = 5;
        tail = head;
    }
    while (tail != NULL)//从头到为，输出蛇身
    {
        Pos(tail->x, tail->y);
        printf("■");
        tail = tail->next;
    }
}

int biteself()//判断是否咬到了自己
{
    snake* self;
    self = head->next;
    while (self != NULL)
    {
        if (self->x == head->x && self->y == head->y)
        {
            return 1;
        }
        self = self->next;
    }
    return 0;
}

void createfood()//随机出现食物
{
    snake* food_1;
    srand((unsigned)time(NULL));
    food_1 = (snake*)malloc(sizeof(snake));
    while ((food_1->x % 2) != 0)    //保证其为偶数，使得食物能与蛇头对其
    {
        food_1->x = rand() % 52 + 2;
    }
    food_1->y = rand() % 24 + 1;
    q = head;
    while (q->next == NULL)
    {
        if (q->x == food_1->x && q->y == food_1->y) //判断蛇身是否与食物重合
        {
            free(food_1);
            createfood();
        }
        q = q->next;
    }
    Pos(food_1->x, food_1->y);
    food = food_1;
    printf("■");
}

void cantcrosswall()//不能穿墙
{
    if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
    {
        endgamestatus = 1;
        endgame();
    }
}

void snakemove()//蛇前进,上U,下D,左L,右R
{
    snake* nexthead;
    cantcrosswall();

    nexthead = (snake*)malloc(sizeof(snake));
    if (status == U)
    {
        nexthead->x = head->x;
        nexthead->y = head->y - 1;
        if (nexthead->x == food->x && nexthead->y == food->y)//如果下一个有食物//
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("■");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
        else                                               //如果没有食物//
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q->next->next != NULL)
            {
                Pos(q->x, q->y);
                printf("■");
                q = q->next;
            }
            Pos(q->next->x, q->next->y);
            printf("  ");
            free(q->next);
            q->next = NULL;
        }
    }
    if (status == D)
    {
        nexthead->x = head->x;
        nexthead->y = head->y + 1;
        if (nexthead->x == food->x && nexthead->y == food->y)  //有食物
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("■");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
        else                               //没有食物
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q->next->next != NULL)
            {
                Pos(q->x, q->y);
                printf("■");
                q = q->next;
            }
            Pos(q->next->x, q->next->y);
            printf("  ");
            free(q->next);
            q->next = NULL;
        }
    }
    if (status == L)
    {
        nexthead->x = head->x - 2;
        nexthead->y = head->y;
        if (nexthead->x == food->x && nexthead->y == food->y)//有食物
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("■");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
        else                                //没有食物
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q->next->next != NULL)
            {
                Pos(q->x, q->y);
                printf("■");
                q = q->next;
            }
            Pos(q->next->x, q->next->y);
            printf("  ");
            free(q->next);
            q->next = NULL;
        }
    }
    if (status == R)
    {
        nexthead->x = head->x + 2;
        nexthead->y = head->y;
        if (nexthead->x == food->x && nexthead->y == food->y)//有食物
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("■");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
        else                                         //没有食物
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q->next->next != NULL)
            {
                Pos(q->x, q->y);
                printf("■");
                q = q->next;
            }
            Pos(q->next->x, q->next->y);
            printf("  ");
            free(q->next);
            q->next = NULL;
        }
    }
    if (biteself() == 1)       //判断是否会咬到自己
    {
        endgamestatus = 2;
        endgame();
    }
}

void pause()//暂停
{
    while (1)
    {
        Sleep(300);
        if (GetAsyncKeyState(VK_SPACE))
        {
            break;
        }

    }
}

void gamecircle()//控制游戏        
{
    Pos(64, 14);
    printf("*** %s 正在游戏中 ***", currentUser.c_str());
    Pos(64, 15);
    printf("不能穿墙，不能咬到自己\n");
    Pos(64, 16);
    printf("用↑.↓.←.→分别控制蛇的移动.");
    Pos(64, 17);
    printf("F1 为加速，F2 为减速, F5 显示用户日志\n");
    Pos(64, 18);
    printf("ESC ：退出游戏.space：暂停游戏.");
    status = R;
    while (1)
    {
        Pos(64, 10);
        printf("得分：%d  ", score);
        Pos(64, 11);
        printf("每个食物得分：%d分", add);
        if (GetAsyncKeyState(VK_UP) && status != D)
        {
            status = U;
        }
        else if (GetAsyncKeyState(VK_DOWN) && status != U)
        {
            status = D;
        }
        else if (GetAsyncKeyState(VK_LEFT) && status != R)
        {
            status = L;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && status != L)
        {
            status = R;
        }
        else if (GetAsyncKeyState(VK_SPACE))
        {
            pause();
        }
        else if (GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus = 3;
            break;
        }
        else if (GetAsyncKeyState(VK_F1))
        {
            if (sleeptime >= 50)
            {
                sleeptime = sleeptime - 30;
                add = add + 2;
                if (sleeptime == 320)
                {
                    add = 2;//防止减到1之后再加回来有错
                }
            }
        }
        else if (GetAsyncKeyState(VK_F2))
        {
            if (sleeptime < 350)
            {
                sleeptime = sleeptime + 30;
                add = add - 2;
                if (sleeptime == 350)
                {
                    add = 1;  //保证最低分为1
                }
            }
        }
        else if (GetAsyncKeyState(VK_F5))
        {
            showGameLogs();
            system("cls");
            creatMap();
            initsnake();
            Pos(food->x, food->y);
            printf("■");
            Pos(64, 14);
            printf("*** %s 正在游戏中 ***", currentUser.c_str());
            Pos(64, 15);
            printf("不能穿墙，不能咬到自己\n");
            Pos(64, 16);
            printf("用↑.↓.←.→分别控制蛇的移动.");
            Pos(64, 17);
            printf("F1 为加速，F2 为减速, F5 显示用户日志\n");
            Pos(64, 18);
            printf("ESC ：退出游戏.space：暂停游戏.");
        }
        Sleep(sleeptime);
        snakemove();
    }
}

void welcometogame()//开始界面
{
    Pos(40, 12);
    printf("欢迎来到贪食蛇游戏！");
    Pos(40, 25);
    system("pause");
    system("cls");
    Pos(25, 12);
    printf("用↑.↓.←.→分别控制蛇的移动， F1 为加速，2 为减速\n");
    Pos(25, 13);
    printf("加速将能得到更高的分数。\n");
    system("pause");
    system("cls");
}

void endgame()//结束游戏
{

    system("cls");
    Pos(24, 12);
    if (endgamestatus == 1)
    {
        printf("对不起，您撞到墙了。游戏结束!");
    }
    else if (endgamestatus == 2)
    {
        printf("对不起，您咬到自己了。游戏结束!");
    }
    else if (endgamestatus == 3)
    {
        printf("您已经结束了游戏。");
    }
    Pos(24, 13);
    printf("您的得分是%d\n", score);
    exit(0);
}

void gamestart()//游戏初始化
{
    system("mode con cols=100 lines=30");
    welcometogame();
    creatMap();
    initsnake();
    createfood();
}

int main()
{
    // 数据库连接
    if (!initDatabase()) {
        std::cout << "无法连接数据库" << std::endl;
        return 1;
    }
    while (true) {
        system("cls");
        std::cout << "欢迎来到贪吃蛇游戏！" << std::endl;
        std::cout << "1. 注册" << std::endl;
        std::cout << "2. 登录" << std::endl;
        std::cout << "3. 退出" << std::endl;
        std::cout << "输入选择" << std::endl;

        int choices;
        std::cin >> choices;

        switch (choices)
        {
            case 1:
                if (registerUser()) {
                    system("pause");
                }
                break;
            case 2:
                if (loginUser()) {
                    system("pause");
                    system("cls");
                    gamestart();
                    gamecircle();
                    endgame();
                    return 0;
                }
                system("pause");
                break;
            case 3:
                std::cout << "结束游戏" << std::endl;
                delete con;//释放数据库连接·
                return 0;
            default:
                std::cout << "选择无效，重新选择" << std::endl;
                system("pause");
                break;
        }
    }

    delete con;  //释放数据库连接
    //gamestart();
    //gamecircle();
    //endgame();
    return 0;
}
