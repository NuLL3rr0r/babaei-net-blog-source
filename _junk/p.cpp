#include <iostream>
#include <string>
#include <vector>

/*#if defined ( __unix__ )
#include <err.h>
#include <fcntl.h>
#include <sys/sysctl.h>
#include <sys/user.h>
#endif // defined ( __unix__ )*/

#if defined ( __FreeBSD__ )
#include <kvm.h>
#include <err.h>
#include <fcntl.h>
#include <sys/sysctl.h>
#include <sys/user.h>
#endif // defined ( __FreeBSD__ )

#if defined ( __linux )
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <dirent.h>
#endif // defined ( __linux )

#if defined ( _WIN32 )
#include <windows.h>
#include <tlhelp32.h>
#endif // defined ( _WIN32 )

std::string GetProcessNameFromPath(const std::string &path)
{
#if defined ( __unix__ )
    return path.substr(path.rfind("/") + 1);
#elif defined ( __win32__ )
#endif // defined ( __unix__ )*/
}

bool GetProcessIds(const std::string &process, std::vector<int> &out_pids)
{
    out_pids.clear();

#if defined (__FreeBSD__)
    kvm_t *kd = kvm_open("/dev/null", "/dev/null", "/dev/null", O_RDONLY, "kvm_open");

    if (kd != NULL) {
        int cnt;
        struct kinfo_proc *p = kvm_getprocs(kd, KERN_PROC_PROC, 0, &cnt);
        for (int i = 0; i < cnt; ++i) {
            if (process.compare(p[i].ki_comm) == 0) {
                out_pids.push_back((int)p[i].ki_pid);
            }
        }

        kvm_close(kd);
    }
#endif // defined ( __FreeBSD__ )

#if defined ( __linux )
    DIR *dp = opendir("/proc");
    if (dp != NULL) {
        struct dirent *dir = readdir(dp);
        while (dir != NULL) {
            int pid = atoi(dir->d_name);
            if (pid > 0) {
                std::stringstream ss;
                ss << "/proc/";
                ss << dir->d_name;
                ss << "/cmdline";
                std::ifstream cmdFile(ss.str().c_str());
                std::string cmdLine;
                getline(cmdFile, cmdLine);
                if (!cmdLine.empty()) {
                    size_t pos = cmdLine.find('\0');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(0, pos);
                    pos = cmdLine.rfind('/');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(pos + 1);
                    if (process.compare(cmdLine) == 0) {
                        out_pids.push_back(pid);
                    }
                }
            }
            dir = readdir(dp);
        }
    }
#endif // defined ( __linux )

#if defined ( _WIN32 )
    PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(hSnapshot, &pe32)) {
        do{
            if (process.compare(pe32.szExeFile) == 0) {
                out_pids.push_back(pe32.th32ProcessID);
            }
        } while (Process32Next(hSnapshot,&pe32));
    }

    if(hSnapshot != INVALID_HANDLE_VALUE)
        CloseHandle(hSnapshot);
#endif // defined ( _WIN32 )

    if (out_pids.size() > 0)
        return true;
    else
        return false;
}

int main(int argc, char **argv)
{
    if (argc <= 1) {
        std::cout << "pidof process_name_or_path" << std::endl;
    }

    std::vector<int> pids;

    for (size_t i = 1; i < argc; ++i) {
        bool rc = GetProcessIds(std::string(argv[i]), pids);
        if (rc) {
            for (std::vector<int>::const_iterator it =
                pids.begin(); it != pids.end(); ++it) {
                std::cout << *it << std::endl;
            }
        }
    }

    return 0;
}


