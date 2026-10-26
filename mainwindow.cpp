#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <lm.h>
#include <TlHelp32.h>
#include <dsgetdc.h>
#include <winldap.h>
#include <winternl.h>
#include <iostream>
#include <chrono>
#include <locale.h>
#include <codecvt>
#include <DSRole.h>
#include <filesystem>
#include <lmapibuf.h>
#include <wbemcli.h>
#include <netioapi.h>
#include <comdef.h>
#include <taskschd.h>
#include "mainwindow.h"
#include <iphlpapi.h>
#include "ui_mainwindow.h"
#include "tabfadeanimation.h"
#include <QTimer>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QShowEvent>
#include <Wbemidl.h>
#include <thread>
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Netapi32.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Iphlpapi.lib")

const char* errorExtention = "\nI'am aware of this possible error. Please open an issue on my GitHub so I can help!";

QString whichStatus(DWORD statusCode){
    switch (statusCode){
    case SERVICE_CONTINUE_PENDING:
        return "SERVICE_CONTINUE_PENDING";
        break;
    case SERVICE_PAUSE_PENDING:
        return "SERVICE_PAUSE_PENDING";
        break;
    case SERVICE_PAUSED:
        return "SERVICE_PAUSED";
        break;
    case SERVICE_RUNNING:
        return "SERVICE_RUNNING";
        break;
    case SERVICE_START_PENDING:
        return "SERVICE_START_PENDING";
        break;
    case SERVICE_STOP_PENDING:
        return "SERVICE_STOP_PENDING";
        break;
    case SERVICE_STOPPED:
        return "SERVICE_STOPPED";
        break;
    }
    return "N/A";
}


std::string RunPowerShell(const std::string& psCommand) {
    std::string result;


    std::wstring cmdLine = L"powershell.exe -NoProfile -Command \"";
    for (char c : psCommand) cmdLine += (wchar_t)c;
    cmdLine += L"\"";


    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE };
    HANDLE hStdOutRead = nullptr, hStdOutWrite = nullptr;
    CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0);
    SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0);


    STARTUPINFOW si = {};
    si.cb = sizeof(STARTUPINFOW);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdOutput = hStdOutWrite;
    si.hStdError  = hStdOutWrite;
    si.hStdInput  = nullptr;


    PROCESS_INFORMATION pi = {};
    std::vector<wchar_t> commandLine(cmdLine.begin(), cmdLine.end());
    commandLine.push_back(L'\0');
    BOOL ok = CreateProcessW(
        L"C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe",
        commandLine.data(),
        nullptr,
        nullptr,
        TRUE,
        CREATE_NO_WINDOW,
        nullptr,
        nullptr,
        &si,
        &pi
        );

    if (!ok) {
        CloseHandle(hStdOutRead);
        CloseHandle(hStdOutWrite);
        throw std::runtime_error("CreateProcess failed");
    }


    CloseHandle(hStdOutWrite);
    CloseHandle(pi.hThread);


    char buf[4096];
    DWORD bytesRead;
    while (ReadFile(hStdOutRead, buf, sizeof(buf) - 1, &bytesRead, nullptr) && bytesRead > 0) {
        buf[bytesRead] = '\0';
        result += buf;
    }


    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(hStdOutRead);

    return result;
}
std::string GetTcpStateName(DWORD state)
{
    switch (state)
    {
    case MIB_TCP_STATE_CLOSED:     return "CLOSED";
    case MIB_TCP_STATE_LISTEN:     return "LISTEN";
    case MIB_TCP_STATE_SYN_SENT:   return "SYN_SENT";
    case MIB_TCP_STATE_SYN_RCVD:   return "SYN_RECEIVED";
    case MIB_TCP_STATE_ESTAB:      return "ESTABLISHED";
    case MIB_TCP_STATE_FIN_WAIT1:  return "FIN_WAIT_1";
    case MIB_TCP_STATE_FIN_WAIT2:  return "FIN_WAIT_2";
    case MIB_TCP_STATE_CLOSE_WAIT: return "CLOSE_WAIT";
    case MIB_TCP_STATE_CLOSING:    return "CLOSING";
    case MIB_TCP_STATE_LAST_ACK:   return "LAST_ACK";
    case MIB_TCP_STATE_TIME_WAIT:  return "TIME_WAIT";
    case MIB_TCP_STATE_DELETE_TCB: return "DELETE_TCB";
    default:                       return "UNKNOWN";
    }
}

using RtlGetVersionCopy = NTSTATUS (*)(PRTL_OSVERSIONINFOW);

static void EnableDebugPrivilege()
{
    HANDLE token = NULL;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) {
        return;
    }
    TOKEN_PRIVILEGES tp = {};
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if (LookupPrivilegeValueW(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
        AdjustTokenPrivileges(token, FALSE, &tp, sizeof(tp), NULL, NULL);
    }
    CloseHandle(token);
}

std::wstring GetServiceTypeString(DWORD type) {
    std::wstring result;

    if (type & SERVICE_KERNEL_DRIVER)
        result += L"Kernel Driver ";
    if (type & SERVICE_FILE_SYSTEM_DRIVER)
        result += L"File System Driver ";
    if (type & SERVICE_WIN32_OWN_PROCESS)
        result += L"Win32 Own Process ";
    if (type & SERVICE_WIN32_SHARE_PROCESS)
        result += L"Win32 Share Process ";
    if (type & SERVICE_INTERACTIVE_PROCESS)
        result += L"Interactive ";

    return result.empty() ? L"Unknown" : result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    new TabFadeAnimation(ui->tabWidget, this);
    new TabFadeAnimation(ui->tabWidget_2, this);

    ui->tableWidget_2->setColumnCount(3);
    ui->tableWidget_2->setColumnWidth(0, 200);
    ui->tableWidget_2->setColumnWidth(1, 80);

    QTreeWidget* tw = ui->treeWidget;

    tw->setColumnWidth(0, 180); // Process
    tw->setColumnWidth(1, 60);  // PID
    tw->setColumnWidth(2, 160); // SeImpersonatePrivilege?
    tw->setColumnWidth(3, 140); // SeDebugPrivilege?
    tw->setColumnWidth(4, 180); // Token-Owner
    tw->setColumnWidth(5, 110); // Integrity Level
    tw->header()->setStretchLastSection(true);

    // Refresh-Button rechts neben den Tabs (neben "Persistence")
    QPushButton* refreshButton = new QPushButton("⟳  Aktualisieren", this);
    refreshButton->setObjectName("refreshButton");
    refreshButton->setCursor(Qt::PointingHandCursor);
    connect(refreshButton, &QPushButton::clicked, this, [this, refreshButton]()
            {
                refreshButton->setEnabled(false);
                refreshButton->setText("Aktualisiere...");
                setCursor(Qt::WaitCursor);

                refreshAllData();

                unsetCursor();
                refreshButton->setText("⟳  Aktualisieren");
                refreshButton->setEnabled(true);
            });
    ui->tabWidget->setCornerWidget(refreshButton, Qt::TopRightCorner);

    QTimer* timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this]()
            {
                quint64 uptimeMs = GetTickCount64();
                quint64 totalSeconds = uptimeMs / 1000;

                quint64 hours = totalSeconds / 3600;
                quint64 minutes = (totalSeconds % 3600) / 60;
                quint64 seconds = totalSeconds % 60;

                QString uptime = QString("%1:%2:%3")
                                     .arg(hours, 2, 10, QChar('0'))
                                     .arg(minutes, 2, 10, QChar('0'))
                                     .arg(seconds, 2, 10, QChar('0'));

                QTableWidgetItem* item = ui->tableWidget->item(0, 5);

                if (!item) {
                    item = new QTableWidgetItem();
                    ui->tableWidget->setItem(0, 5, item);
                }

                item->setText(uptime);
            });

    timer->start(1000);

    EnableDebugPrivilege();

    refreshAllData();
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    if (m_firstShowDone)
        return;

    m_firstShowDone = true;

    setWindowOpacity(0.0);

    auto* fadeIn = new QPropertyAnimation(this, "windowOpacity", this);
    fadeIn->setDuration(650);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::OutCubic);
    fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::refreshAllData()
{
    // Alle Listen leeren, damit ein erneuter Aufruf nicht dupliziert
    ui->treeWidget->clear();
    ui->tableWidget_2->clear();
    ui->treeWidget_2->clear();
    ui->treeWidget_3->clear();
    ui->treeWidget_4->clear();
    ui->treeWidget_5->clear();
    ui->treeWidget_6->clear();
    ui->plainTextEdit->clear();

    QTableWidgetItem * o = ui->tableWidget->item(0,0);
    QTableWidgetItem * oVersion = ui->tableWidget->item(0, 1);
    if(o){
        char compName[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD size = sizeof(compName);
        int ret = GetComputerNameA(compName, &size);
        if (ret != 0){
            QString stringToInput;
            std::string temp = compName;
            stringToInput = QString::fromStdString(temp);
            o->setText(stringToInput);
        }
        else{
            o->setText("Lookup failed");
        }
    }
    HMODULE dllHandle = LoadLibraryA("Ntdll.dll");
    if (!dllHandle){
        char buff[5096 ];
        sprintf(buff, "LoadLibrary function failed with error code -> %lu", GetLastError());
        MessageBoxA(NULL, buff, "Warning", MB_OK);
        exit(0);
    }
    else{

        RtlGetVersionCopy RtlGetVersion = reinterpret_cast<RtlGetVersionCopy>(GetProcAddress(dllHandle, "RtlGetVersion"));

        if (!RtlGetVersion){
            char buff[5096 ];
            sprintf(buff, "RtlGetVersion was not found. Error code -> %lu", GetLastError());
            MessageBoxA(NULL, buff, "Warning", MB_OK);
            exit(0);
        }

        RTL_OSVERSIONINFOW buildInfo = {0};
        NTSTATUS status = RtlGetVersion(&buildInfo);

        if (!NT_SUCCESS(status)){
            char buff[5096 ];
            sprintf(buff, "RtlGetVersion failed. Error code -> %lu", GetLastError());
            MessageBoxA(NULL, buff, "Warning", MB_OK);
            exit(0);
        }

        if (buildInfo.dwMajorVersion == 10 && buildInfo.dwBuildNumber >= 22000){
            std::string versionToCpy = "Windows 11 Build " + std::to_string(buildInfo.dwBuildNumber);
            oVersion->setText(QString::fromStdString(versionToCpy));
        }else if (buildInfo.dwMajorVersion == 10){
            std::string versionToCpy = "Windows 10 Build " + std::to_string(buildInfo.dwBuildNumber);
            oVersion->setText(QString::fromStdString(versionToCpy));
        }

        //hier als nächsteas architecture
        SYSTEM_INFO sysInfo = {0};
        GetNativeSystemInfo(&sysInfo);
        QTableWidgetItem* arch = ui->tableWidget->item(0, 2);
        if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64){
            if (arch != NULL){
                arch->setText("x64");
            }
        }else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL){
            if (arch != NULL){
                arch->setText("x32");
            }
        }else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64){
            if (arch != NULL){
                arch->setText("ARM64");
            }
        }

        QTableWidgetItem* DomainWorkGroup = ui->tableWidget->item(0,3);

        PDSROLE_PRIMARY_DOMAIN_INFO_BASIC domainNamestruct = nullptr;

        DWORD res = DsRoleGetPrimaryDomainInformation(
            nullptr,
            DsRolePrimaryDomainInfoBasic,
            reinterpret_cast<PBYTE*>(&domainNamestruct)
            );

        if (res == ERROR_SUCCESS && domainNamestruct)
        {
            QString domainName =
                QString::fromWCharArray(domainNamestruct->DomainNameDns);

            if (domainName.isEmpty()) {
                if (DomainWorkGroup) DomainWorkGroup->setText("No Domain found!");
            } else {
                if (DomainWorkGroup) DomainWorkGroup->setText(domainName);
            }

            DsRoleFreeMemory(domainNamestruct);
        }
        else if (DomainWorkGroup) {
            DomainWorkGroup->setText("No Domain found!");
        }

        PDOMAIN_CONTROLLER_INFOW domainInfo = nullptr;

        DWORD res1 = DsGetDcNameW(NULL, NULL, NULL, NULL, DS_DIRECTORY_SERVICE_REQUIRED, &domainInfo);

        bool haveDomainInfo = (res1 == ERROR_SUCCESS && domainInfo != nullptr);

        if (haveDomainInfo){
            wprintf(L"DC: %s\n", domainInfo->DomainControllerName);
            wprintf(L"Domain: %s\n", domainInfo->DomainName);
        }


        if (haveDomainInfo){

            LDAP* connectLdap = ldap_initW(NULL, LDAP_PORT);

            if (!connectLdap){
                if (ui->tableWidget->item(0,4)) ui->tableWidget->item(0,4)->setText("LDAP init failed");
            }
            else{
                ULONG version = LDAP_VERSION3;
                ldap_set_optionW(connectLdap, LDAP_OPT_PROTOCOL_VERSION, &version);
                ULONG result = ldap_bind_sW(
                    connectLdap,
                    nullptr,
                    nullptr,
                    LDAP_AUTH_NEGOTIATE
                    );
                if (result != LDAP_SUCCESS) {
                    qDebug() << "LDAP bind result:" << result;
                    qDebug() << "LDAP error:"
                             << QString::fromWCharArray(ldap_err2stringW(result));
                    if (ui->tableWidget->item(0,4)) ui->tableWidget->item(0,4)->setText("No Users found! Domain may be down");
                    ldap_unbind(connectLdap);
                } else {
                    qDebug() << "LDAP bind successful";
                    QString domain = QString::fromWCharArray(domainInfo->DomainName);
                    QString dc = QString::fromWCharArray(domainInfo->DomainControllerName);
                    qDebug() << domain;

                    // DN aus Domainnamen bauen, z.B. corp.local -> DC=corp,DC=local
                    QStringList parts = domain.split('.', Qt::SkipEmptyParts);
                    QStringList dcParts;
                    for (const QString& part : parts) {
                        dcParts << ("DC=" + part);
                    }
                    QString baseDn = dcParts.join(",");

                    PWCHAR userAttributes[] = {
                        const_cast<PWCHAR>(L"sAMAccountName"),
                        const_cast<PWCHAR>(L"userPrincipalName"),
                        const_cast<PWCHAR>(L"displayName"),
                        nullptr
                    };
                    LDAPMessage* searchResult = nullptr;
                    QString filter = "(&(objectCategory=person)(objectClass=user))";
                    std::wstring baseDnW = baseDn.toStdWString();
                    std::wstring filterW = filter.toStdWString();
                    ULONG result_query = ldap_search_sW(connectLdap, const_cast<PWSTR>(baseDnW.c_str()), LDAP_SCOPE_SUBTREE, const_cast<PWSTR>(filterW.c_str()), userAttributes, 0, &searchResult);

                    if (result_query != LDAP_SUCCESS){
                        qDebug() << "LDAP search failed:" << QString::fromWCharArray(ldap_err2stringW(result_query));
                        if (ui->tableWidget->item(0,4)) ui->tableWidget->item(0,4)->setText("LDAP search failed");
                    }
                    else{
                        int roww = 0;
                        for (LDAPMessage* user = ldap_first_entry(connectLdap, searchResult); user != nullptr; user = ldap_next_entry(connectLdap, user)){
                            PWCHAR attr = const_cast<PWCHAR>(L"sAMAccountName");
                            PWSTR* usernames = ldap_get_valuesW(connectLdap, user, attr);
                            if (usernames && usernames[0]){
                                QTableWidgetItem* userItem = ui->tableWidget->item(roww, 4);
                                if (!userItem){
                                    userItem = new QTableWidgetItem();
                                    ui->tableWidget->setItem(roww, 4, userItem);
                                }
                                userItem->setText(QString::fromWCharArray(usernames[0]));
                                ldap_value_freeW(usernames);
                            }
                            roww++;
                        }
                        if (roww == 0 && ui->tableWidget->item(0, 4)){
                            ui->tableWidget->item(0, 4)->setText("No Users found!");
                        }
                        if (searchResult) ldap_msgfree(searchResult);
                    }
                    ldap_unbind(connectLdap);
                }
            }
        }
        else if (ui->tableWidget->item(0,4)) {
            ui->tableWidget->item(0,4)->setText("No Domain found!");
        }

        if (domainInfo){
            NetApiBufferFree(domainInfo);
        }

        FreeLibrary(dllHandle);
    }
    std::vector<std::string> processNames;
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS,
        0
        );

    if (snapshotHandle == INVALID_HANDLE_VALUE){
        MessageBoxA(
            NULL,
            "Processes couldn't be listed. Try running the tool with administrator privileges.\n"
            "If the problem still remains, open an Issue on my GitHub.",
            "Warning",
            NULL
            );
        return;
    }

    PROCESSENTRY32W processEntryStruct = {};
    processEntryStruct.dwSize = sizeof(PROCESSENTRY32W);

    BOOL ret = Process32FirstW(snapshotHandle, &processEntryStruct);
    std::vector<DWORD> pids;
    if (!ret) {
        MessageBoxA(
            NULL,
            "Processes couldn't be listed. Try running the tool with administrator privileges.\n"
            "If the problem still remains, open an Issue on my GitHub.",
            "Warning",
            NULL
            );
    }
    else {

        do {

            DWORD pid = processEntryStruct.th32ProcessID;

            std::string pid_conv = std::to_string(pid);
            std::wstring processName_conv = processEntryStruct.szExeFile;

            using convert_type = std::codecvt_utf8<wchar_t>;

            std::wstring_convert<convert_type, wchar_t> converter;
            std::string processNameFullStdString = converter.to_bytes(processEntryStruct.szExeFile);

            processNames.push_back(processNameFullStdString);
            pids.push_back(pid);
            QTreeWidgetItem* processItem = new QTreeWidgetItem(ui->tableWidget_2);
            processItem->setText(0, QString::fromStdWString(processName_conv));
            processItem->setText(1, QString::fromStdString(pid_conv));

            if (pid == 0){
                processItem->setText(2, "-");
            }
            else{
                HANDLE moduleHandle = CreateToolhelp32Snapshot(
                    TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,
                    pid
                    );

                if (moduleHandle != INVALID_HANDLE_VALUE) {

                    MODULEENTRY32W modules = {};
                    modules.dwSize = sizeof(MODULEENTRY32W);

                    int dllCount = 0;

                    BOOL ret_mod1 = Module32FirstW(
                        moduleHandle,
                        &modules
                        );

                    if (ret_mod1) {

                        do {
                            QTreeWidgetItem* dllChild = new QTreeWidgetItem(processItem);
                            dllChild->setText(2, QString::fromWCharArray(modules.szModule));
                            dllCount++;

                        } while (Module32NextW(
                            moduleHandle,
                            &modules
                            ));
                    }

                    processItem->setText(2, QString("%1 DLL's (click to expand)").arg(dllCount));

                    CloseHandle(moduleHandle);
                }
                else{
                    DWORD err = GetLastError();
                    processItem->setText(2,
                                         err == ERROR_ACCESS_DENIED ? "Access denied (protected?)" : QString("Error %1").arg(err)
                                         );
                }
            }

        } while (Process32NextW(
            snapshotHandle,
            &processEntryStruct
            ));
    }

    CloseHandle(snapshotHandle);

    for (int i = 0; i < ui->tableWidget_2->columnCount(); i++){
        ui->tableWidget_2->resizeColumnToContents(i);
    }

    DWORD size = 0;
    GetExtendedTcpTable(nullptr, &size, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
    std::vector<BYTE> buf(size);
    MIB_TCPTABLE_OWNER_PID* pTcpTable = reinterpret_cast<MIB_TCPTABLE_OWNER_PID*>(buf.data());
    DWORD ret5 = GetExtendedTcpTable(pTcpTable, &size, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);

    for (int i = 0; i < pids.size(); i++){
        HANDLE procH = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pids[i]);


        DWORD retLength = 0;

        if (procH == NULL){
            continue;
        }

        HANDLE tokenHandle = nullptr;;

        if (OpenProcessToken(procH, TOKEN_QUERY, &tokenHandle)){
            if (tokenHandle != INVALID_HANDLE_VALUE){
                retLength = 0;
                GetTokenInformation(tokenHandle, TokenPrivileges, nullptr, 0, &retLength);
                std::vector<BYTE> privBuf(retLength);
                TOKEN_PRIVILEGES* privStruct = reinterpret_cast<TOKEN_PRIVILEGES*>(privBuf.data());
                BOOL ret1 = GetTokenInformation(tokenHandle, TokenPrivileges, privStruct, retLength, &retLength);

                retLength = 0;
                GetTokenInformation(tokenHandle, TokenUser, nullptr, 0, &retLength);
                std::vector<BYTE> userBuf(retLength);
                TOKEN_USER* userStruct = reinterpret_cast<TOKEN_USER*>(userBuf.data());
                BOOL ret2 = GetTokenInformation(tokenHandle, TokenUser, userStruct, retLength, &retLength);
                if (!ret1 || !ret2 || privBuf.empty() || userBuf.empty()){
                    CloseHandle(tokenHandle);
                    continue;
                }


                retLength = 0;
                GetTokenInformation(tokenHandle, TokenIntegrityLevel, nullptr, 0, &retLength);
                std::vector<BYTE> intBuf(retLength);
                TOKEN_MANDATORY_LABEL* integrityStruct = reinterpret_cast<TOKEN_MANDATORY_LABEL*>(intBuf.data());
                BOOL ret3 = GetTokenInformation(tokenHandle, TokenIntegrityLevel, integrityStruct, retLength, &retLength);


                TOKEN_ELEVATION elevStruct = {0};
                DWORD elevLen = sizeof(TOKEN_ELEVATION);
                BOOL ret4 = GetTokenInformation(tokenHandle, TokenElevation, &elevStruct, elevLen, &elevLen);

                LUID luidImpersonate = {0};
                LUID luidDebug = {0};
                LookupPrivilegeValueW(NULL, SE_IMPERSONATE_NAME, &luidImpersonate);
                LookupPrivilegeValueW(NULL, SE_DEBUG_NAME, &luidDebug);
                bool hasImpersonate = false;
                bool hasDebug = false;
                for (DWORD j = 0; j < privStruct->PrivilegeCount; ++j){

                    LUID localLuid = privStruct->Privileges[j].Luid;
                    DWORD attr = privStruct->Privileges[j].Attributes;

                    if (localLuid.LowPart == luidImpersonate.LowPart && localLuid.HighPart == luidImpersonate.HighPart){
                        hasImpersonate = (attr & SE_PRIVILEGE_ENABLED) != 0;
                    }
                    if (localLuid.LowPart == luidDebug.LowPart && localLuid.HighPart == luidDebug.HighPart){
                        hasDebug = (attr & SE_PRIVILEGE_ENABLED) != 0;
                    }
                }

                char szName[256] = {0};
                char szDomain[256] = {0};
                DWORD cchName = 256, cchDomain = 256;
                SID_NAME_USE snu;
                char fullOwner[6000] = {0};

                if (LookupAccountSidA(NULL, userStruct->User.Sid, szName, &cchName, szDomain, &cchDomain, &snu)){
                    snprintf(fullOwner, sizeof(fullOwner), "%s/%s", szName, szDomain);
                }

                std::string fullOwnerStdStr = fullOwner;

                QString hasImpersonateInsert = "FALSE";
                QString hasDebugInsert = "FALSE";

                if (hasImpersonate){
                    hasImpersonateInsert = "TRUE";
                }
                if (hasDebug){
                    hasDebugInsert = "TRUE";
                }
                QString integrityLevel = "Unknown";
                if (ret3){
                    DWORD level = *GetSidSubAuthority(integrityStruct->Label.Sid, *GetSidSubAuthorityCount(integrityStruct->Label.Sid) - 1);
                    if      (level < SECURITY_MANDATORY_MEDIUM_RID) integrityLevel = "Low";
                    else if (level < SECURITY_MANDATORY_HIGH_RID)   integrityLevel = "Medium";
                    else if (level < SECURITY_MANDATORY_SYSTEM_RID) integrityLevel = "High";
                    else                                             integrityLevel = "System";
                }
                QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
                item->setText(0, QString::fromStdString(processNames[i]));
                QTreeWidgetItem* item2 = new QTreeWidgetItem(ui->treeWidget_2);
                item2->setText(5, QString::fromStdString(processNames[i]));
                item2->setText(6, QString::fromStdString(std::to_string(pids[i])));
                item->setText(1, QString::fromStdString(std::to_string(pids[i])));
                item->setText(2, hasImpersonateInsert);
                item->setText(3, hasDebugInsert);
                item->setText(4, QString::fromStdString(fullOwnerStdStr));
                item->setText(5, integrityLevel);

                CloseHandle(procH);
                CloseHandle(tokenHandle);
            }
        }



        //Network Discovery

        DWORD bytesRequired = 0;
        GetExtendedTcpTable(nullptr, &bytesRequired, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
        std::vector<BYTE> heapLocationForTable(bytesRequired);
        MIB_TCPTABLE_OWNER_PID* pTcpTableNet = reinterpret_cast<MIB_TCPTABLE_OWNER_PID*>(heapLocationForTable.data());
        GetExtendedTcpTable(pTcpTableNet, &bytesRequired, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);

        for (DWORD i = 0; i < pTcpTableNet->dwNumEntries; ++i){
            MIB_TCPROW_OWNER_PID row = pTcpTableNet->table[i];

            in_addr localAddr{};
            localAddr.S_un.S_addr = row.dwLocalAddr;
            char localBuf[64]{};
            InetNtopA(AF_INET, &localAddr, localBuf, sizeof(localBuf));

            in_addr remoteAddr{};
            remoteAddr.S_un.S_addr = row.dwRemoteAddr;
            char remoteBuf[64]{};
            InetNtopA(AF_INET, &remoteAddr, remoteBuf, sizeof(remoteBuf));

            DWORD localPort = ntohs((u_short)row.dwLocalPort);
            DWORD remotePort = ntohs((u_short)row.dwRemotePort);

            QString procName = "Unknown";
            for (int x = 0; x < (int)pids.size(); x++){
                if (pids[x] == row.dwOwningPid){
                    procName = QString::fromStdString(processNames[x]);
                    break;
                }
            }

            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget_2);
            item->setText(0, QString::fromLocal8Bit(localBuf));
            item->setText(1, QString::number(localPort));
            item->setText(2, QString::fromLocal8Bit(remoteBuf));
            item->setText(3, QString::number(remotePort));
            item->setText(5, procName);
            item->setText(6, QString::number(row.dwOwningPid));

            std::vector<DWORD> vectorForState = {MIB_TCP_STATE_CLOSED, MIB_TCP_STATE_LISTEN, MIB_TCP_STATE_SYN_SENT, MIB_TCP_STATE_SYN_RCVD, MIB_TCP_STATE_ESTAB, MIB_TCP_STATE_FIN_WAIT1, MIB_TCP_STATE_FIN_WAIT2, MIB_TCP_STATE_CLOSE_WAIT, MIB_TCP_STATE_CLOSING, MIB_TCP_STATE_LAST_ACK, MIB_TCP_STATE_TIME_WAIT, MIB_TCP_STATE_DELETE_TCB};
            int count = 0;

            for (DWORD entry : vectorForState){
                if (entry == pTcpTableNet->table[i].dwState){
                    std::string tcpName = GetTcpStateName(entry);
                    item->setText(4, QString::fromStdString(tcpName));
                }
                count++;
            }

        }

    }
    std::string returnDnsCache = RunPowerShell("Get-DnsClientCache");
    QString dnsC_conv = QString::fromStdString(returnDnsCache);
    ui->plainTextEdit->setPlainText(dnsC_conv);

    MIB_IPFORWARD_TABLE2 *ipForwardTableStruct{};
    NTSTATUS retVal_SubnetScrape = GetIpForwardTable2(AF_INET, &ipForwardTableStruct);

    if (retVal_SubnetScrape != NO_ERROR){
        switch (retVal_SubnetScrape){
        case ERROR_INVALID_PARAMETER:
            MessageBoxA(NULL, "Invalid Param in GetIpForwardTable2", "Error", MB_OK);
            break;

        case ERROR_NOT_ENOUGH_MEMORY:
            MessageBoxA(NULL, "Insufficient memory resources are available to complete the operation.", "Error", MB_OK);
            break;
        case ERROR_NOT_FOUND:
            MessageBoxA(NULL, "No IP route entries as specified in the Family parameter were found.", "Error", MB_OK);
            break;
        case ERROR_NOT_SUPPORTED:
            MessageBoxA(NULL, "	The request is not supported.", "Error", MB_OK);
            break;
        }
    }else{

        for (ULONG entry = 0; entry < ipForwardTableStruct->NumEntries; entry++){

            MIB_IPFORWARD_ROW2 currentEntry = ipForwardTableStruct->Table[entry];

            SOCKADDR_INET Destinationn = currentEntry.DestinationPrefix.Prefix;
            UINT8  PrefixLength = currentEntry.DestinationPrefix.PrefixLength;
            SOCKADDR_INET Gatewayy = currentEntry.NextHop;
            ULONG metricc = currentEntry.Metric;

            QTreeWidgetItem* itemmm = new QTreeWidgetItem(ui->treeWidget_3);

            SOCKADDR_IN IpAddrr = Destinationn.Ipv4;
            char ipAddressFullConverted[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET, &IpAddrr.sin_addr, ipAddressFullConverted, sizeof(ipAddressFullConverted));
            std::string intoStdStringIpAddr = ipAddressFullConverted;

            itemmm->setText(0, QString::fromStdString(intoStdStringIpAddr));

            std::string prefixStdStr = std::to_string(PrefixLength);

            itemmm->setText(1, "/" + QString::fromStdString(prefixStdStr));

            char gateWayFullConverted[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET, &Gatewayy.Ipv4.sin_addr, gateWayFullConverted, sizeof(gateWayFullConverted));
            std::string intoStdStringGateWay = gateWayFullConverted;

            itemmm->setText(2, QString::fromStdString(intoStdStringGateWay));

            itemmm->setText(3, QString::fromStdString(std::to_string(metricc)));

        }

    }



    ULONG bytesReqAddresses = 0;

    PIP_ADAPTER_ADDRESSES adapterStruct = {0};

    ULONG retAddresses = GetAdaptersAddresses(AF_INET, 0, nullptr, nullptr, &bytesReqAddresses);
    if (retAddresses == ERROR_BUFFER_OVERFLOW){
        adapterStruct = (PIP_ADAPTER_ADDRESSES)malloc(bytesReqAddresses);
        retAddresses = GetAdaptersAddresses(AF_INET, 0, NULL, adapterStruct, &bytesReqAddresses);
    }
    if (retAddresses == NO_ERROR){


        PIP_ADAPTER_ADDRESSES adapterssss = adapterStruct;
        while (adapterssss){
            PWCHAR adapterName = adapterssss->FriendlyName;
            wchar_t* description = adapterssss->Description;
            IF_OPER_STATUS operstatus = adapterssss->OperStatus;


            QTreeWidgetItem* table4 = new QTreeWidgetItem(ui->treeWidget_4);

            table4->setText(0, QString::fromStdWString(std::wstring(adapterName)));
            table4->setText(1, QString::fromStdWString(std::wstring(description)));


            switch (operstatus){
            case IfOperStatusUp:
                table4->setText(2, "1 (ACTIVE)");
                break;
            case IfOperStatusDown:
                table4->setText(2, "2 (NOT ACTIVE)");
                break;
            case IfOperStatusTesting:
                table4->setText(2, "3 (TESTING-MODE)");
                break;
            case IfOperStatusUnknown:
                table4->setText(2, "4 (UNKNOWN)");
                break;
            case IfOperStatusDormant:
                table4->setText(2, "5 (ACTIVE/WAITING FOR EVENT)");
                break;
            case IfOperStatusNotPresent:
                table4->setText(2, "6 (HARDWARE-COMPONENT MISSING)");
                break;
            case IfOperStatusLowerLayerDown:
                table4->setText(2, "7 (LOWER LAYER DOWN)");
                break;
            }

            PIP_ADAPTER_UNICAST_ADDRESS addresses = adapterssss->FirstUnicastAddress;
            while (addresses){

                char AddrIp[INET6_ADDRSTRLEN] = {};

                inet_ntop(addresses->Address.lpSockaddr->sa_family,
                          addresses->Address.lpSockaddr->sa_family == AF_INET ?
                              (const void*)&((sockaddr_in*)addresses->Address.lpSockaddr)->sin_addr :
                              (const void*)&((sockaddr_in6*)addresses->Address.lpSockaddr)->sin6_addr,
                          AddrIp, INET6_ADDRSTRLEN);

                table4->setText(3, QString::fromStdString(std::string(AddrIp)));

                addresses = addresses->Next;
            }

            adapterssss = adapterssss->Next;
        }
        free(adapterStruct);

    }


    SC_HANDLE scm_handle = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    DWORD bytesNeeded = 0;
    DWORD      resumeHandle = 0;
    DWORD servicesReturned = 0;


    EnumServicesStatusEx(scm_handle, SC_ENUM_PROCESS_INFO,
                         SERVICE_DRIVER | SERVICE_WIN32, SERVICE_STATE_ALL,
                         nullptr, 0, &bytesNeeded, &servicesReturned, &resumeHandle, nullptr);

    std::vector<BYTE> buffer(bytesNeeded);
    auto services = reinterpret_cast<ENUM_SERVICE_STATUS_PROCESS*>(buffer.data());
    if (!EnumServicesStatusEx(scm_handle, SC_ENUM_PROCESS_INFO,
                              SERVICE_DRIVER | SERVICE_WIN32, SERVICE_STATE_ALL,
                              reinterpret_cast<LPBYTE>(services), bytesNeeded,
                              &bytesNeeded, &servicesReturned, &resumeHandle, nullptr)) {
        DWORD lastErr = GetLastError();
        char errMsg[5000];
        sprintf(errMsg, "Error Code for Service Enumeration -> %ld", lastErr);
        MessageBoxA(NULL, errMsg, "Warning", NULL);
    }

    for (int x = 0; x < servicesReturned; x++){

        wchar_t* displayName = services[x].lpDisplayName;
        wchar_t* realName = services[x].lpServiceName;
        std::wstring fullIt = std::wstring(displayName) + L" / " + realName;
        DWORD type = services[x].ServiceStatusProcess.dwServiceType;
        DWORD status = services[x].ServiceStatusProcess.dwCurrentState;
        QString status_conv = whichStatus(status);
        char serviceNameANSI[3500];
        QUERY_SERVICE_CONFIG service_configStr = {0};
        QTreeWidgetItem* itemServices = new QTreeWidgetItem(ui->treeWidget_5);
        itemServices->setText(0, QString::fromStdWString(fullIt));
        itemServices->setText(1, status_conv);
        itemServices->setText(2, QString::fromStdWString(GetServiceTypeString(type)));

        wcstombs(serviceNameANSI, services[x].lpServiceName, sizeof(serviceNameANSI));

        SC_HANDLE db_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);

        SC_HANDLE services_handle = OpenServiceA(db_handle, serviceNameANSI, SERVICE_QUERY_CONFIG);
        if (services_handle != NULL){
            DWORD bytesNeededQueryService = 0;
            if (QueryServiceConfigA(services_handle, nullptr, 0, &bytesNeededQueryService) == 0)
            {
                std::vector<BYTE> bytesNeededStruct(bytesNeededQueryService);
                auto queryServiceStructBuffer = reinterpret_cast<QUERY_SERVICE_CONFIGA*>(bytesNeededStruct.data());
                QueryServiceConfigA(services_handle, queryServiceStructBuffer, bytesNeededQueryService, &bytesNeededQueryService);

                switch (queryServiceStructBuffer->dwStartType){
                case SERVICE_AUTO_START:
                    itemServices->setText(3, "SERVICE_AUTO_START");
                    break;
                case SERVICE_BOOT_START:
                    itemServices->setText(3, "SERVICE_BOOT_START");
                    break;
                case SERVICE_DEMAND_START:
                    itemServices->setText(3, "SERVICE_DEMAND_START");
                    break;
                case SERVICE_DISABLED:
                    itemServices->setText(3, "SERVICE_DISABLED");
                    break;
                case SERVICE_SYSTEM_START:
                    itemServices->setText(3, "SERVICE_SYSTEM_START");
                    break;
                }

                itemServices->setText(4, queryServiceStructBuffer->lpBinaryPathName ? QString::fromStdString(std::string(queryServiceStructBuffer->lpBinaryPathName)) : "-");
                itemServices->setText(5, queryServiceStructBuffer->lpServiceStartName ? QString::fromStdString(std::string(queryServiceStructBuffer->lpServiceStartName)) : "-");

                DWORD bytesForTwo = 0;
                if (QueryServiceConfig2W(services_handle, SERVICE_CONFIG_DESCRIPTION,nullptr, 0, &bytesForTwo) == 0){

                    std::vector<BYTE> heapAllocated2(bytesForTwo);
                    auto descriptionBuffer = reinterpret_cast<SERVICE_DESCRIPTION*>(heapAllocated2.data());
                    QueryServiceConfig2W(services_handle, SERVICE_CONFIG_DESCRIPTION, heapAllocated2.data(), bytesForTwo, &bytesForTwo);
                    if (descriptionBuffer->lpDescription != nullptr){
                        itemServices->setText(6, QString::fromStdWString(std::wstring(descriptionBuffer->lpDescription)));
                    }else{
                        itemServices->setText(6, "-");
                    }
                }
                CloseServiceHandle(services_handle);
            }
            CloseServiceHandle(db_handle);

        }

    }

    //Persistence next here
    //1. Run Keys
    HKEY runKeyHandle;
    std::vector<QTreeWidgetItem*> runKeyItems;
    LONG openResult = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &runKeyHandle);
    int countr = 0;
    bool showedWarning = false;
    if (openResult == ERROR_SUCCESS){
        while (true){

            WCHAR valueName[2560];
            DWORD valueNameSize = 256;
            WCHAR dataRet[10240] = {0};
            DWORD dataRetSize = sizeof(dataRet);
            DWORD type = 0;

            LONG retValues = RegEnumValueW(
                runKeyHandle,
                countr,
                valueName,
                &valueNameSize,
                nullptr,
                &type,
                reinterpret_cast<LPBYTE>(dataRet),
                &dataRetSize
                );

            if (retValues == ERROR_NO_MORE_ITEMS){
                break;
            }

            if (retValues != ERROR_SUCCESS && !showedWarning){
                MessageBoxA(NULL, "Couldn't obtain all Run-Key entries\nfor some Users", "Warning", NULL);
                showedWarning = true;
            }

            std::wstring valuePathAllUsers = dataRet;
            std::wstring entryName(valueName, valueNameSize);

            QTreeWidgetItem *itemLast = new QTreeWidgetItem(ui->treeWidget_6);
            itemLast->setText(0, QString::fromStdWString(entryName));
            itemLast->setToolTip(0, QString::fromStdWString(valuePathAllUsers));
            runKeyItems.push_back(itemLast);
            countr++;

        }
        RegCloseKey(runKeyHandle);
    }else{
        MessageBoxA(NULL, "Run-Key Lookup for all users failed", "Warning", MB_OK);
    }

    HKEY runKeyHandle2;
    LONG openResult2 = RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &runKeyHandle2);
    int countr2 = 0;
    if (openResult2 == ERROR_SUCCESS){
        while (true){

            WCHAR valueName[2560];
            DWORD valueNameSize = 256;
            WCHAR dataRet[10240] = {0};
            DWORD dataRetSize = sizeof(dataRet);
            DWORD type = 0;

            LONG retValues = RegEnumValueW(
                runKeyHandle2,
                countr2,
                valueName,
                &valueNameSize,
                nullptr,
                &type,
                reinterpret_cast<LPBYTE>(dataRet),
                &dataRetSize
                );

            if (retValues == ERROR_NO_MORE_ITEMS){
                break;
            }

            if (retValues != ERROR_SUCCESS && !showedWarning){
                MessageBoxA(NULL, "Couldn't obtain all Run-Key entries\nfor some Users", "Warning", NULL);
                showedWarning = true;
            }

            std::wstring valuePathAllUsers = dataRet;
            std::wstring entryName(valueName, valueNameSize);

            if (countr2 < (int)runKeyItems.size()){
                runKeyItems[countr2]->setText(1, QString::fromStdWString(entryName));
                runKeyItems[countr2]->setToolTip(1, QString::fromStdWString(valuePathAllUsers));
            } else {
                QTreeWidgetItem *itemLast = new QTreeWidgetItem(ui->treeWidget_6);
                itemLast->setText(1, QString::fromStdWString(entryName));
                itemLast->setToolTip(1, QString::fromStdWString(valuePathAllUsers));
            }
            countr2++;

        }
        RegCloseKey(runKeyHandle2);

    }
    else{
        MessageBoxA(NULL, "Run-Key Lookup for all users failed", "Warning", MB_OK);
    }

    //Schedules Tasks

    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);


    if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) {
        char msg[64];
        sprintf_s(msg, "CoInitializeEx failed: 0x%08X", hr);
        MessageBoxA(NULL, msg, "Warning", MB_OK);
    }

    ITaskService* pService = nullptr;
    hr = CoCreateInstance(CLSID_TaskScheduler, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskService, reinterpret_cast<void**>(&pService));


    if (FAILED(hr)){
        char fullIt[2400];
        sprintf(fullIt, "CoCreateInstance failed. %s", errorExtention);
        MessageBoxA(nullptr, fullIt, "Warning", MB_OK);

    }else{
        hr = pService->Connect(_variant_t(), _variant_t(), _variant_t(), _variant_t());
        if (FAILED(hr)){
            char fullIt[2400];
            sprintf(fullIt, "ITaskService::Connect failed. %s", errorExtention);
            MessageBoxA(nullptr, fullIt, "Warning", MB_OK);
        }else{
            ITaskFolder* rootFolder = nullptr;
            hr = pService->GetFolder(_bstr_t(L"\\"), &rootFolder);

            if (FAILED(hr)){
                char fullIt[2400];
                sprintf(fullIt, "ITaskService::GetFolder failed. %s", errorExtention);
                MessageBoxA(nullptr, fullIt, "Warning", MB_OK);
            }else{
                IRegisteredTaskCollection* pTasks = nullptr;
                hr = rootFolder->GetTasks(TASK_ENUM_HIDDEN, &pTasks);
                if (FAILED(hr)){
                    char fullIt[2400];
                    sprintf(fullIt, "ITaskService::GetTasks failed. %s", errorExtention);
                    MessageBoxA(nullptr, fullIt, "Warning", MB_OK);
                }else{
                    LONG count = 0;
                    pTasks->get_Count(&count);
                    for (LONG i = 1; i <= count; i++)
                    {
                        IRegisteredTask* pTask = nullptr;
                        if (SUCCEEDED(pTasks->get_Item(_variant_t(i), &pTask)))
                        {
                            BSTR name = nullptr;
                            if (SUCCEEDED(pTask->get_Name(&name)))
                            {
                                int row = i - 1;
                                QTreeWidgetItem* item = (row < ui->treeWidget_6->topLevelItemCount())
                                                            ? ui->treeWidget_6->topLevelItem(row)
                                                            : new QTreeWidgetItem(ui->treeWidget_6);

                                item->setText(2, QString::fromWCharArray(name));
                                SysFreeString(name);
                            }
                            pTask->Release();
                        }
                    }
                    pTasks->Release();
                }
                rootFolder->Release();
            }
        }
        pService->Release();
    }

    //Startup Folder implemenntation

    TCHAR userName[256];
    DWORD userLengtsh = 256;
    BOOL userNameIsSet = FALSE;

    if (GetUserName(userName, &userLengtsh)){
        userNameIsSet = TRUE;
    }else{
        MessageBoxA(NULL, "cannot get username!", "Warning", NULL);
        userNameIsSet = FALSE;
    }

    if (userNameIsSet == TRUE){

        char FullPathForStartup[2560];
        char fullUsernameConv[250 + 1];

        WideCharToMultiByte(CP_UTF8, 0, userName, -1, fullUsernameConv, 256, NULL, NULL);
        sprintf(FullPathForStartup, "C:\\Users\\%s\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup", fullUsernameConv);

        try{
            int rowStartup = 0;
            for (const auto& entry : std::filesystem::directory_iterator(FullPathForStartup)){
                if (std::filesystem::is_regular_file(entry.path())){

                    QString fileName = QString::fromStdWString(entry.path().filename().wstring());
                    QString fullPath = QString::fromStdWString(entry.path().wstring());

                    QTreeWidgetItem* item = (rowStartup < ui->treeWidget_6->topLevelItemCount())
                                                ? ui->treeWidget_6->topLevelItem(rowStartup)
                                                : new QTreeWidgetItem(ui->treeWidget_6);

                    item->setText(3, fileName);
                    item->setToolTip(3, fullPath);

                    rowStartup++;
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e){
            MessageBoxA(NULL, e.what(), "Warning", MB_OK);
        }

    }


    HRESULT resultWmiSub = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    resultWmiSub = CoInitializeSecurity(nullptr, -1, nullptr, nullptr,
                                        RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
                                        nullptr, EOAC_NONE, nullptr);

    if (FAILED(resultWmiSub) && resultWmiSub != RPC_E_TOO_LATE) {
        char msg[128];
        sprintf_s(msg, "CoInitializeSecurity failed: 0x%08X", resultWmiSub);
        MessageBoxA(NULL, msg, "Warning", MB_OK);
    }
    else {
        IWbemLocator* locator = nullptr;
        resultWmiSub = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast<void**>(&locator));

        if (FAILED(resultWmiSub) || !locator) {
            char msg[128];
            sprintf_s(msg, "CoCreateInstance (WbemLocator) failed: 0x%08X", resultWmiSub);
            MessageBoxA(NULL, msg, "Warning", MB_OK);
        }
        else {
            IWbemServices* services2 = nullptr;
            resultWmiSub = locator->ConnectServer(
                _bstr_t(L"ROOT\\subscription"),
                nullptr, nullptr, nullptr,
                0, nullptr, nullptr,
                &services2
                );

            if (FAILED(resultWmiSub) || !services2) {
                char msg[128];
                sprintf_s(msg, "ConnectServer failed: 0x%08X", resultWmiSub);
                MessageBoxA(NULL, msg, "Warning", MB_OK);
            }
            else {
                IEnumWbemClassObject* enumerator = nullptr;
                resultWmiSub = services2->ExecQuery(
                    _bstr_t(L"WQL"),
                    _bstr_t(L"SELECT * FROM __EventFilter"),
                    WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                    nullptr,
                    &enumerator
                    );

                if (FAILED(resultWmiSub) || !enumerator) {
                    char msg[128];
                    sprintf_s(msg, "ExecQuery failed: 0x%08X", resultWmiSub);
                    MessageBoxA(NULL, msg, "Warning", MB_OK);
                }
                else {
                    IWbemClassObject* classObject = nullptr;
                    ULONG returnedCount = 0;
                    int rowWmi = 0;

                    while (true)
                    {
                        HRESULT hrNext = enumerator->Next(WBEM_INFINITE, 1, &classObject, &returnedCount);

                        if (hrNext != WBEM_S_NO_ERROR || returnedCount == 0)
                            break;

                        VARIANT nameVar;
                        VariantInit(&nameVar);
                        classObject->Get(L"Name", 0, &nameVar, nullptr, nullptr);

                        VARIANT queryVar;
                        VariantInit(&queryVar);
                        classObject->Get(L"Query", 0, &queryVar, nullptr, nullptr);

                        QString filterName = (nameVar.vt == VT_BSTR) ? QString::fromWCharArray(nameVar.bstrVal) : "Unknown";
                        QString filterQuery = (queryVar.vt == VT_BSTR) ? QString::fromWCharArray(queryVar.bstrVal) : "-";

                        QTreeWidgetItem* item = (rowWmi < ui->treeWidget_6->topLevelItemCount())
                                                    ? ui->treeWidget_6->topLevelItem(rowWmi)
                                                    : new QTreeWidgetItem(ui->treeWidget_6);

                        item->setText(4, filterName);
                        item->setToolTip(4, filterQuery);
                        rowWmi++;

                        VariantClear(&nameVar);
                        VariantClear(&queryVar);

                        classObject->Release();
                        classObject = nullptr;
                    }

                    if (rowWmi == 0) {
                        QTreeWidgetItem* item = (ui->treeWidget_6->topLevelItemCount() > 0)
                        ? ui->treeWidget_6->topLevelItem(0)
                        : new QTreeWidgetItem(ui->treeWidget_6);
                        item->setText(4, "No Event Filters found");
                    }

                    enumerator->Release();
                }
                services2->Release();
            }
            locator->Release();


        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}