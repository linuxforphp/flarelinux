#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QByteArray>

#include "myqtbatchstart.h"
#include "processwindow.h"

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    mainWindow();

    ~mainWindow();

private:

    myQtBatchStart *pMyQtBatchProcess;

    processWindow *pProcessProgressWindow;

    QVBoxLayout *pVLayout;

    QHBoxLayout *pHLayout;

    QWidget *pTitle;

    QLabel *pLabelIcon;

    QLabel *pLabel;

    QPushButton *pStartButton;

    QPushButton *pStopButton;

    QPushButton *pQuitButton;

    QLabel *pCopyright;

    int initObjects;
    
signals:
    void sigCallBackAndFrontForSubprocessStart();

    void sigCallBackAndFrontForSubprocessStop();

    void sigKill();

    void sigSignalEnd();
    
public slots:
    void slMainStartProcessStart();

    void slMainStartProcessStop();

};

#endif // MAINWINDOW_H
