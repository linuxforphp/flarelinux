#include "mainwindow.h"

mainWindow::mainWindow() : QWidget() {
    initObjects = 0;

    setFixedSize(500, 300);

    pVLayout = new QVBoxLayout();

    pTitle = new QWidget();

    pHLayout = new QHBoxLayout();

    pLabelIcon = new QLabel();
    QPixmap pPm("favicon.png");
    pLabelIcon->setPixmap(pPm);
    pLabelIcon->setAlignment(Qt::AlignLeft);

    pLabel = new QLabel("Flare Linux GUI Client");
    pLabel->setAlignment(Qt::AlignVCenter);
    pLabel->setFont(QFont("Arial", 24));

    pHLayout->addWidget(pLabelIcon);
    pHLayout->addWidget(pLabel);

    pTitle->setLayout(pHLayout);

    // Build buttons
    pStartButton = new QPushButton("Start");

    pStartButton->setToolTip("Start the Flare Linux Docker container.");
    pStartButton->setFont(QFont("Arial", 10));
    pStartButton->setCursor(Qt::PointingHandCursor);

    pStopButton = new QPushButton("Stop");

    pStopButton->setToolTip("Stop the the Flare Linux Docker container.");
    pStopButton->setFont(QFont("Arial", 10));
    pStopButton->setCursor(Qt::PointingHandCursor);

    pQuitButton = new QPushButton("Quit");

    pQuitButton->setToolTip("Quit the Flare Linux GUI client.");
    pQuitButton->setFont(QFont("Arial", 10));
    pQuitButton->setCursor(Qt::PointingHandCursor);

    pCopyright = new QLabel("©2021, Foreach Code Factory. All Rights Reserved.");
    pCopyright->setAlignment(Qt::AlignHCenter);
    pCopyright->setFont(QFont("Arial", 8));

    pVLayout->addWidget(pTitle);
    pVLayout->addWidget(pStartButton);
    pVLayout->addWidget(pStopButton);
    pVLayout->addWidget(pQuitButton);
    pVLayout->addWidget(pCopyright);

    this->setLayout(pVLayout);

    // Connexions
    QObject::connect(pStartButton, SIGNAL(clicked()), this, SLOT(slMainStartProcessStart()));
    QObject::connect(pStopButton, SIGNAL(clicked()), this, SLOT(slMainStartProcessStop()));
    QObject::connect(pQuitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

mainWindow::~mainWindow() {

    delete pStartButton;

    delete pStopButton;

    delete pQuitButton;

    delete pCopyright;

    delete pLabel;

    delete pLabelIcon;

    delete pHLayout;

    delete pTitle;

    delete pVLayout;

    delete pMyQtBatchProcess;

    delete pProcessProgressWindow;
}

void mainWindow::slMainStartProcessStart() {

    if (initObjects == 1) {
        delete pMyQtBatchProcess;

        delete pProcessProgressWindow;

        initObjects = 0;
    }

    pMyQtBatchProcess = new myQtBatchStart();

    pProcessProgressWindow = new processWindow(1);

    initObjects = 1;

    QObject::connect(pMyQtBatchProcess, SIGNAL(readyReadStandardOutput()), pMyQtBatchProcess, SLOT(slReadOutput()));
    QObject::connect(pMyQtBatchProcess, SIGNAL(readyReadStandardError()), pMyQtBatchProcess, SLOT(slReadOutput()));
    QObject::connect(pMyQtBatchProcess, SIGNAL(sigStdOutToPost(QByteArray)), pProcessProgressWindow, SLOT(slPostStdOutput(QByteArray)));
    QObject::connect(pMyQtBatchProcess, SIGNAL(finished(int)), pProcessProgressWindow, SLOT(slStartDone(int)));
    QObject::connect(this, SIGNAL(sigKill()), pMyQtBatchProcess, SLOT(kill()));
    QObject::connect(this, SIGNAL(sigSignalEnd()), pProcessProgressWindow, SLOT(reject()));
    QObject::connect(this, SIGNAL(sigCallBackAndFrontForSubprocessStart()), pMyQtBatchProcess, SLOT(slStartProcessStart()));
    QObject::connect(this, SIGNAL(sigCallBackAndFrontForSubprocessStart()), pProcessProgressWindow, SLOT(slShowDialog()));

    emit sigCallBackAndFrontForSubprocessStart();
}

void mainWindow::slMainStartProcessStop() {

    if (initObjects == 1) {
        delete pMyQtBatchProcess;

        delete pProcessProgressWindow;

        initObjects = 0;
    }

    pMyQtBatchProcess = new myQtBatchStart();

    pProcessProgressWindow = new processWindow(2);

    initObjects = 1;

    QObject::connect(pMyQtBatchProcess, SIGNAL(readyReadStandardOutput()), pMyQtBatchProcess, SLOT(slReadOutput()));
    QObject::connect(pMyQtBatchProcess, SIGNAL(sigStdOutToPost(QByteArray)), pProcessProgressWindow, SLOT(slPostStdOutput(QByteArray)));
    QObject::connect(pMyQtBatchProcess, SIGNAL(finished(int)), pProcessProgressWindow, SLOT(slStopDone(int)));
    QObject::connect(this, SIGNAL(sigKill()), pMyQtBatchProcess, SLOT(kill()));
    QObject::connect(this, SIGNAL(sigSignalEnd()), pProcessProgressWindow, SLOT(reject()));
    QObject::connect(this, SIGNAL(sigCallBackAndFrontForSubprocessStop()), pMyQtBatchProcess, SLOT(slStartProcessStop()));
    QObject::connect(this, SIGNAL(sigCallBackAndFrontForSubprocessStop()), pProcessProgressWindow, SLOT(slShowDialog()));

    emit sigCallBackAndFrontForSubprocessStop();
}
