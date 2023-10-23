#include<time.h>
#include<sys/times.h>
#include<sys/sysinfo.h>
#include<unistd.h>
#include<stdio.h>
#include<iostream>
#include<unordered_map>
#include <string>
using namespace std;

struct DLinkedNode {
    int value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode():value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _value): value(_value), prev(nullptr), next(nullptr) {}
};

unordered_map<std::string, std::string> ptrMap;
int main()
{
    DLinkedNode * ptr = new DLinkedNode();

    ptr->value = 100;

    // unsigned long numPtr = (unsigned long) ptr;
    
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%p", ptr);
    ptrMap["my"] = buffer;

    cout<<ptrMap["my"]<<endl;
    DLinkedNode * new_ptr = (DLinkedNode *)strtoul(ptrMap["my"].c_str(), NULL, 16);
    cout<<new_ptr->value<<endl;

    char myAddr[128];
    printf("%p \n", myAddr);
    auto ptrDLinkNode = new(myAddr)DLinkedNode();
    printf("%p \n", ptrDLinkNode);

    return 0;
}