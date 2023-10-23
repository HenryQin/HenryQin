#include<iostream>
#include<sys/file.h>
#include<unistd.h>
#include<stdio.h>
#include<vector>
using namespace std;
#define QUE_SHM_LOCK_FILE "/dev/shm."
#define SHM_NAME "shm_init_lock"
class FileLock
{
public:
    FileLock():iLockFd(-1)
    {
    }

    int Init()
    {
        if(iLockFd >= 0)
        {
            return 0;
        }

        char szLockFile[256];
        snprintf(szLockFile, sizeof(szLockFile), "%s_%s_lock", QUE_SHM_LOCK_FILE, SHM_NAME);
        int fd = open(szLockFile, O_RDONLY | O_CREAT, 0644);
        if(0 > fd)
        {
            return -1;
        }
        iLockFd = fd;

        return 0;
    }

    int Lock()
    {
        return flock(iLockFd, LOCK_EX) == 0 ? 0 : -1;
    }

    int LockNb()
    {
        return flock(iLockFd, LOCK_EX|LOCK_NB) == 0 ? 0 : -1;
    }
    
    int UnLock()
    {   
        return flock(iLockFd, LOCK_UN) == 0 ? 0 : -1;
    }

    ~FileLock()
    {
        cout<<"process_id:"<<getpid()<<endl;
        cout<<"iLockFd:"<<iLockFd<<endl;

        if( iLockFd > 0)
        {   
            flock(iLockFd, LOCK_UN) == 0 ? 0 : -1;
            close(iLockFd);
        }
    }

private:
int iLockFd;
};

int main()
{
    FileLock oFileLock;
    
    cout<<"Init():"<<oFileLock.Init()<<endl;

    cout<<"UnLock():"<<oFileLock.UnLock()<<endl;
    
    cout<<"LockNb():"<<oFileLock.LockNb()<<endl;
    
    int* my_array = new int[10];
    std::vector<int>vNum(10,10);

    // for(int idx = 0; idx <= 2000; idx++)
    //     my_array[idx] = 12;

    // cout<<my_array[20000]<<endl;

    pid_t pid = fork();
    if( pid == 0 )
    {
        cout<< "child process:"<<getpid()<<endl;
        return 0;
    }
    else if ( pid > 0 )
    {
        while(true) {}   
    }

    //sleep(600);
   
    return 0;
}