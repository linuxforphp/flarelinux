#include "myqtbatchstart.h"

myQtBatchStart::myQtBatchStart() : QProcess() {}

myQtBatchStart::~myQtBatchStart() {
    delete pCwdPath;
}

void myQtBatchStart::startProcess(int option) {
    pCwdPath = new QDir();

#ifdef Q_OS_WIN

    if (option == 1) {
        batchFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-start.bat");
    } else {
        batchFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-stop.bat");
    }

    batchFileFullPath = QDir::toNativeSeparators(batchFileFullPath);

    this->start("cmd.exe", QStringList() << "/c" << batchFileFullPath);

#else

    if (option == 1) {
        batchFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-start.sh");
    } else {
        batchFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-stop.sh");
    }

    batchFileFullPath = QDir::toNativeSeparators(batchFileFullPath);

    this->start("bash", QStringList() << batchFileFullPath);

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
