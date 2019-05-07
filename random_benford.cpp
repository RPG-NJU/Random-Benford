#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime> // 用于获取时间的头文件
#include <cstdlib>
#include <sys/time.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::fstream;
using std::string;
using std::to_string;


#define GRPDEBUG
#define DATASIZE 1000000
#define RANGE 100000
#define MODE 3

int GetTimeSec()
{
    timeval time;
    gettimeofday(&time, nullptr);
    return time.tv_usec; // 返回微秒的数据
}

void GetRand(vector<int> &data);

string RandToFile(vector<int> &data, int &now_time);
string RandCompute(vector<int> &data, int &now_time);
int GetTheIntHead(int val);


int main()
{
    cout << "[in this PC, RAND_MAX = " << RAND_MAX << "]" << endl; // 确定当前环境下的随机范围

    int seed = time(nullptr);
    int now_time(0);
    srand(seed);
    vector<int> rand_data;

    cout << "[本次的随机种子为： " << seed << "]" << endl;
    // cout << rand() << endl;

    GetRand(rand_data);
    cout << "[总计随机数据： " << rand_data.size() << " 条]" << endl;
    
    string rand_filename = RandToFile(rand_data, now_time);
    cout << "[所有随机数据写入： " << rand_filename << "]" << endl;

    string analysis_filename = RandCompute(rand_data, now_time);
    cout << "[所有数据分析写入： " << analysis_filename << "]" << endl;

    return 0;
}

void GetRand(vector<int> &data)
{
    int randam(0);
    for (int i(0); i < DATASIZE; ++i)
    {
#if MODE == 1
        // randam = rand();
        data.push_back(rand() % RANGE);
        // data.push_back(random);
#endif

#if MODE == 2
        int x = rand() % (RANGE / 2);
        int y = rand() % (RANGE / 2);

        data.push_back(x + y);
#endif

#if MODE == 3
        int x = rand() % (RANGE);
        int y = rand() % (RANGE);

        data.push_back(x + y);
#endif
    }
    return;
}

string RandToFile(vector<int> &data, int &now_time)
{
    fstream file;
    now_time = (time(nullptr)); // 取当前时间作为文件名
    string filename("./Data/" + to_string(now_time) + "[" + to_string(RANGE) + "]"); // 变为string格式
    filename += "-" + to_string(DATASIZE);
    filename += ".txt";
    file.open(filename, std::ios::out);
    if (!file.is_open())
    {
        exit(-1);
    }
    for (const auto &x : data)
    {
        file << to_string(x) << " ";
    }
    file << endl;
    file.close();

    // 前面完成的是原始数据的写入

    return filename;
}

string RandCompute(vector<int> &data, int &now_time)
{
    fstream file;
    int anal[10] = {0};
    double anal_percent[10] = {0};
    string filename("./Analysis/" + to_string(now_time) + "[" + to_string(RANGE) + "]");
    filename += "-" + to_string(DATASIZE);
    filename += ".txt";
    
    for (const auto &x : data)
    {
        ++anal[GetTheIntHead(x)];
    }

    for (int i(0); i < 10; ++i)
    {
        anal_percent[i] = (double)anal[i] / (double)DATASIZE;
    }

    file.open(filename, std::ios::out);
    if (!file.is_open())
    {
        exit(-1);
    }

    for (int i(0); i < 10;  ++i)
    {
        file << to_string(i) << " : " << anal[i] << "  " << anal_percent[i] << endl;
    }
    file.close();


    return filename;
}

int GetTheIntHead(int val)
{
    int head(0);
    while (val != 0)
    {
        head = val % 10;
        val /= 10;
    }
    return head;
}