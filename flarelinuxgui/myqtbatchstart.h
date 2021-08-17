#ifndef MYQTBATCHSTART_H
#define MYQTBATCHSTART_H

#include <QObject>
#include <QProcess>
#include <QByteArray>
#include <QDir>
#include <QString>

class myQtBatchStart : public QProcess
{
    Q_OBJECT

public:
    myQtBatchStart();

    ~myQtBatchStart();

    void startProcess(int);

    void readOutput();

private:
    QByteArray stdOut;

    QDir *pCwdPath;

    QString scriptFileFullPath;

signals:
    void sigStdOutToPost(QByteArray);
    
public slots:
    void slStartProcessStart();

    void slStartProcessStop();

    void slReadOutput();

};

#endif // MYQTBATCHSTART_H
