#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>

const char* exeNames[] =
{
    "KeyRemapChild-x86",
    "KeyRemapChild-x64"
};

HANDLE createKillJob();
bool assignKillJob(HANDLE job, PROCESS_INFORMATION pi);
PROCESS_INFORMATION launchChild(const char* filename);

#ifdef _WIN64
    #define PROCESS_COUNT 2
#else
    #define PROCESS_COUNT 1
#endif

int main(int argc, char** argv)
{
    // Kill job handle
    HANDLE jobObject;

    // Child process information
    PROCESS_INFORMATION processes[PROCESS_COUNT];

    // Create a kill job to clean up child processes
    jobObject = createKillJob();

    if (jobObject == NULL)
        return 1;

    // Launch child processes (32-bit and, if in 64-bit mode, 64-bit too)
    bool success = true;
    for (int i = 0; i < PROCESS_COUNT; ++i)
    {
        processes[i] = launchChild(exeNames[i]);
        success = success && assignKillJob(jobObject, processes[i]);

        if (!success)
            break;
    }

    // Wait until child process exits
    if (success)
    {
        for (int i = 0; i < PROCESS_COUNT; ++i)
        {
            WaitForSingleObject(processes[i].hProcess, INFINITE);
        }
    }

    // Close process and thread handles.
    for (int i = 0; i < PROCESS_COUNT; ++i)
    {
        CloseHandle(processes[i].hProcess);
    }
}

HANDLE createKillJob()
{
    HANDLE ghJob = CreateJobObject(NULL, NULL); // GLOBAL

    if (ghJob == NULL)
    {
        MessageBox(0, "Could not create job object", "ERROR", MB_OK);
    }
    else
    {
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };

        // Configure all child processes associated with the job to terminate
        jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
        if (!SetInformationJobObject(ghJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli)))
        {
            MessageBox(0, "Failed to create kill job", "ERROR", MB_OK);
        }
    }

    return ghJob;
}

bool assignKillJob(HANDLE job, PROCESS_INFORMATION pi)
{
    if (!AssignProcessToJobObject(job, pi.hProcess))
    {
        MessageBox(0, "Could not assign job to process", "ERROR", MB_OK);
        return false;
    }

    return true;
}

PROCESS_INFORMATION launchChild(const char* filename)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process. 
    if (!CreateProcess(
        NULL,                   // No module name (use command line)
        (char*)filename,        // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to U
        0,                      // No creation flags
        NULL,                   // Use parent's environment block
        NULL,                   // Use parent's starting directory 
        &si,                    // Pointer to STARTUPINFO structure
        &pi))                   // Pointer to PROCESS_INFORMATION structure
    {
        printf("CreateProcess failed (%d)\n", GetLastError());
    }

    return pi;
}