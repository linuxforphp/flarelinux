#include "mainwindow.h"

mainWindow::mainWindow() : QWidget() {
    int windowX = dw.width() * 0.3;

    int windowY = dw.height() * 0.35;

    setFixedSize(windowX, windowY);

    initObjects = 0;

    pVLayout = new QVBoxLayout();

    pTitle = new QWidget();

    pHLayout = new QHBoxLayout();

    pLabelIcon = new QLabel();
    QPixmap pPm("favicon.png");
    pLabelIcon->setPixmap(pPm);
    pLabelIcon->setAlignment(Qt::AlignLeft);

    pLabel = new QLabel("Flare Linux GUI Client");
    pLabel->setAlignment(Qt::AlignVCenter);
    pLabel->setFont(QFont("Arial", 12));

    pHLayout->addWidget(pLabelIcon);
    pHLayout->addWidget(pLabel);

    pTitle->setLayout(pHLayout);

    // Build radio buttons
    pRadioButtons = new QWidget();

    pRadioButtonsHLayout = new QHBoxLayout();

    pRadioButton1 = new QRadioButton("Local", this);
    pRadioButton2 = new QRadioButton("Existing", this);
    pRadioButton3 = new QRadioButton("Single", this);
    pRadioButton4 = new QRadioButton("Coston", this);

    pRadioButtonsHLayout->addWidget(pRadioButton1);
    pRadioButtonsHLayout->addWidget(pRadioButton2);
    pRadioButtonsHLayout->addWidget(pRadioButton3);
    pRadioButtonsHLayout->addWidget(pRadioButton4);

    pRadioButtons->setLayout(pRadioButtonsHLayout);

    // Build push buttons
    pPushButtons = new QWidget();

    pPushButtonsHLayout = new QHBoxLayout();

    pStartButton = new QPushButton("Start");
    pStartButton->setToolTip("Start the Flare Linux Docker container.");
    pStartButton->setFont(QFont("Arial", 10));
    pStartButton->setMaximumWidth(windowX * 0.2);
    pStartButton->setCursor(Qt::PointingHandCursor);

    pStopButton = new QPushButton("Stop");
    pStopButton->setToolTip("Stop the the Flare Linux Docker container.");
    pStopButton->setFont(QFont("Arial", 10));
    pStopButton->setMaximumWidth(windowX * 0.2);
    pStopButton->setCursor(Qt::PointingHandCursor);

    pQuitButton = new QPushButton("Quit");
    pQuitButton->setToolTip("Quit the Flare Linux GUI client.");
    pQuitButton->setFont(QFont("Arial", 10));
    pQuitButton->setMaximumWidth(windowX * 0.2);
    pQuitButton->setCursor(Qt::PointingHandCursor);

    pPushButtonsHLayout->addWidget(pStartButton);
    pPushButtonsHLayout->addWidget(pStopButton);
    pPushButtonsHLayout->addWidget(pQuitButton);

    pPushButtons->setLayout(pPushButtonsHLayout);

    pCopyright = new QLabel("©2021, Foreach Code Factory. All Rights Reserved.");
    pCopyright->setAlignment(Qt::AlignHCenter);
    pCopyright->setFont(QFont("Arial", 8));
    pCopyright->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    pCopyright->setFont(QFont("Arial", 8, 0, true));

    pVLayout->addWidget(pTitle);
    pVLayout->addWidget(pRadioButtons);
    pVLayout->addWidget(pPushButtons);
    pVLayout->addWidget(pCopyright);

    this->setLayout(pVLayout);

    // Connexions
    QObject::connect(pStartButton, SIGNAL(clicked()), this, SLOT(slMainStartProcessStart()));
    QObject::connect(pStopButton, SIGNAL(clicked()), this, SLOT(slMainStartProcessStop()));
    QObject::connect(pQuitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

mainWindow::~mainWindow() {
    delete pRadioButton1;

    delete pRadioButton2;

    delete pRadioButton3;

    delete pRadioButton4;

    delete pStartButton;

    delete pStopButton;

    delete pQuitButton;

    delete pCopyright;

    delete pLabel;

    delete pLabelIcon;

    delete pPushButtonsHLayout;

    delete pRadioButtonsHLayout;

    delete pPushButtons;

    delete pRadioButtons;

    delete pHLayout;

    delete pTitle;

    delete pVLayout;

    if (initObjects == 1) {
        delete pMyQtBatchProcess;

        delete pProcessProgressWindow;
    }
}

void mainWindow::slMainStartProcessStart() {
    if (initObjects == 1) {
        delete pMyQtBatchProcess;

        delete pProcessProgressWindow;

        initObjects = 0;
    }

    int flareMode = 4;

    if (pRadioButton1->isChecked()) {
        flareMode = 1;
    } else if (pRadioButton2->isChecked()) {
        flareMode = 2;
    } else if (pRadioButton3->isChecked()) {
        flareMode = 3;
    } else if (pRadioButton4->isChecked()) {
        flareMode = 4;
    }

    pMyQtBatchProcess = new myQtBatchStart(flareMode);

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

    pMyQtBatchProcess = new myQtBatchStart(0);

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
