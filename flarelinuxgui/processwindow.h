#ifndef PROCESSWINDOW_H
#define PROCESSWINDOW_H

#include <QObject>
#include <QDialog>
#include <QPixmap>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTextEdit>
#include <QPushButton>
#include <QByteArray>
#include <QStringList>
#include <QString>

class processWindow : public QDialog
{
    Q_OBJECT

public:
    processWindow(int);

    ~processWindow();

    void incrementBar(int percent);

    void postStdOutput(QByteArray);


private:
    QVBoxLayout *pProcessVLayout;

    QLabel *pProcessLabel;

    QProgressBar *pProcessProgress;

    QTextEdit *pProcessDialogRO;

    QWidget *pProcessControls;

    QHBoxLayout *pProcessHLayout;

    QPushButton *pOkButton;

    QPushButton *pCancelButton;

    QStringList lines;
    
signals:
    void sigAbort();
    
public slots:
    void slShowDialog();

    void slPostStdOutput(QByteArray);

    void slStartDone(int);

    void slStopDone(int);
    
};

#endif // PROCESSWINDOW_H
