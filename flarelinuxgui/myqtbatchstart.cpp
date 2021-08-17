#include "myqtbatchstart.h"

myQtBatchStart::myQtBatchStart() : QProcess() {}

myQtBatchStart::~myQtBatchStart() {
    delete pCwdPath;
}

void myQtBatchStart::startProcess(int option) {
    pCwdPath = new QDir();

#ifdef Q_OS_WIN

    if (option == 1) {
        scriptFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-start.bat");
    } else {
        scriptFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-stop.bat");
    }

    scriptFileFullPath = QDir::toNativeSeparators(scriptFileFullPath);

    this->start("cmd.exe", QStringList() << "/c" << scriptFileFullPath);

#else

    if (option == 1) {
        scriptFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-start.bash");
    } else {
        scriptFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-stop.bash");
    }

    scriptFileFullPath = QDir::toNativeSeparators(scriptFileFullPath);

    this->start("bash", QStringList() << scriptFileFullPath);

#endif

}

void myQtBatchStart::readOutput() {
    stdOut = this->readAllStandardOutput();

    emit sigStdOutToPost(stdOut);
}

void myQtBatchStart::slStartProcessStart() {
    this->startProcess(1);
}

void myQtBatchStart::slStartProcessStop() {
    this->startProcess(2);
}

void myQtBatchStart::slReadOutput() {
    this->readOutput();
}
