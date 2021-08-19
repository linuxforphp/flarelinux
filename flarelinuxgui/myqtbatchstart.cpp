#include "myqtbatchstart.h"

myQtBatchStart::myQtBatchStart(int flareMode) : QProcess() {
    if (flareMode == 1) {
        this->flareMode = "--local";
    } else if (flareMode == 2) {
        this->flareMode = "--existing";
    } else if (flareMode == 3) {
        this->flareMode = "--single";
    } else if (flareMode == 4) {
        this->flareMode = "--coston";
    } else {
        this->flareMode = "--coston";
    }
}

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

    this->start("cmd.exe", QStringList() << "/c" << scriptFileFullPath << this->flareMode);

#else

    if (option == 1) {
        scriptFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-start.bash");
    } else {
        scriptFileFullPath = pCwdPath->absoluteFilePath("flarelinux-server_docker-stop.bash");
    }

    scriptFileFullPath = QDir::toNativeSeparators(scriptFileFullPath);

    this->start("bash", QStringList() << scriptFileFullPath << this->flareMode);

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
