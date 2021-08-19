#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QRadioButton>
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

    QDesktopWidget dw;

    myQtBatchStart *pMyQtBatchProcess;

    processWindow *pProcessProgressWindow;

    QVBoxLayout *pVLayout;

    QHBoxLayout *pHLayout;

    QWidget *pRadioButtons;

    QWidget *pPushButtons;

    QHBoxLayout *pRadioButtonsHLayout;

    QHBoxLayout *pPushButtonsHLayout;

    QWidget *pTitle;

    QLabel *pLabelIcon;

    QLabel *pLabel;

    QRadioButton *pRadioButton1;

    QRadioButton *pRadioButton2;

    QRadioButton *pRadioButton3;

    QRadioButton *pRadioButton4;

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
