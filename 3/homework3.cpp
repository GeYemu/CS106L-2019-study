#include <string>
#include <fstream>
#include <iostream>
using namespace std;

string promptUserForFile(ifstream& stream,
                         string prompt="",//默认值：当你为函数参数定义一个默认值时，如果调用者没有为该参数提供实参，函数就会使用这个默认值。
                         string reprompt="")                     
{
string line;//創建一個字符串為文件名字
reprompt="please input a right name of the file.\n";
prompt="please input the name of file.\n";
cout<<prompt;

while(getline(cin,line))//標準輸入
{
stream.open(line);//打開文件
if(stream)//如果能打開
{
return line;
}
cout<<reprompt;
stream.clear();//清除流狀態，然後回到循環
}

}
int main()
{
ifstream file;
string filename=promptUserForFile(file);
    if (!filename.empty()) {
        cout << "File '" << filename << "' opened successfully!" << endl;
    } else {
        cout << "Failed to open file or no valid input was provided." << endl;
    }
    return 0;

}