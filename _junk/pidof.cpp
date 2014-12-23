#include <iostream>
#include <string>
#include <vector>

#if defined ( __unix__ )
#include <err.h>
#include <fcntl.h>
#include <sys/sysctl.h>
#include <sys/user.h>
#endif // defined (__unix__)

#if defined (__FreeBSD__)
#include <kvm.h>
#endif // defined (__FreeBSD__)

std::string GetProcessNameFromPath(const std::string &fullPath)
{
    return fullPath.substr(fullPath.rfind("/") + 1);
}

bool GetPidsOfProcess(const std::string &processName, std::vector<int> &out_pids)
{
    static kvm_t *kd = NULL;
    struct kinfo_proc *p;
    int i;
    int nProcesses;
    bool processesFound = false;

    if ((kd = kvm_open("/dev/null", "/dev/null", "/dev/null", O_RDONLY, "kvm_open")) == NULL) {
        (void)errx(1, "%s", kvm_geterr(kd));
    } else {
        p = kvm_getprocs(kd, KERN_PROC_PROC, 0, &nProcesses);
        for (i = 0; i < nProcesses; ++i)
            if (strncmp(processName.c_str(), p[i].ki_comm, COMMLEN + 1) == 0) {
                out_pids.push_back((int)p[i].ki_pid);
                std::cout << (int)p[i].ki_pid << "  : size: " << out_pids.size() << std::endl;
                processesFound = true;
            }

        kvm_close(kd);
    }

    return processesFound;
}

int main(int argc, char **argv)
{
    if (argc <= 1) {
        std::cout << "pidof process_name_or_path" << std::endl;
    }

    std::vector<int> pids;

    for (size_t i = 1; i < argc; ++i) {
        bool rc = GetPidsOfProcess(GetProcessNameFromPath(std::string(argv[i])), pids);
        if (rc) {
            for (std::vector<int>::const_iterator it =
                 pids.begin(); it != pids.end(); ++it) {
                std::cout << *it << std::endl;
            }
        }
    }

    return 0;
}

