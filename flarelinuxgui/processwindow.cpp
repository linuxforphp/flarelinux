#include "processwindow.h"

processWindow::processWindow(int option) : QDialog() {
    int windowX = dw.width() * 0.3;
    int windowY = dw.height() * 0.5;

    setFixedSize(windowX, windowY);

    QPixmap pPm("favicon.png");
    this->setWindowIcon(pPm);

    pProcessVLayout = new QVBoxLayout();

    if (option == 1){
        this->setWindowTitle("Starting the Flare Linux container...");

        pProcessLabel = new QLabel("Starting the Flare Linux container...");
    } else {
        this->setWindowTitle("Stopping the Flare Linux container...");

        pProcessLabel = new QLabel("Stopping the Flare Linux container...");
    }

    pProcessProgress = new QProgressBar();

    pProcessDialogRO = new QTextEdit();

    pProcessDialogRO->setReadOnly(true);

    pProcessControls = new QWidget();

    pProcessHLayout = new QHBoxLayout();

    pOkButton = new QPushButton("OK");
    pOkButton->setFont(QFont("Arial", 12));
    pOkButton->setCursor(Qt::PointingHandCursor);
    pOkButton->setMaximumWidth(windowX * 0.2);
    pOkButton->setEnabled(false);

    pProcessHLayout->addWidget(pOkButton);

    pProcessControls->setLayout(pProcessHLayout);

    pProcessVLayout->addWidget(pProcessLabel);
    pProcessVLayout->addWidget(pProcessProgress);
    pProcessVLayout->addWidget(pProcessDialogRO);
    pProcessVLayout->addWidget(pProcessControls);
    pProcessVLayout->addWidget(pProcessControls);

    this->setLayout(pProcessVLayout);

    QObject::connect(pOkButton, SIGNAL(clicked()), this, SLOT(accept()));
}

processWindow::~processWindow() {
    delete pProcessLabel;

    delete pProcessProgress;

    delete pProcessDialogRO;

    delete pOkButton;

    delete pProcessHLayout;

    delete pProcessVLayout;

    delete pProcessControls;
}

void processWindow::incrementBar(int percent) {
    pProcessProgress->setValue(percent);
}

void processWindow::postStdOutput (QByteArray stdOut) {
    lines = QString(stdOut).split("\n");

    foreach (QString line, lines) {
        if (line[0] == '2') {
            this->incrementBar(20);
        }
        else if (line[0] == '4') {
            this->incrementBar(40);
        }
        else if (line[0] == '6') {
            this->incrementBar(60);
        }
        else if (line[0] == '8') {
            this->incrementBar(80);
        }
        else {
            displayedLine.append(line.trimmed());
            pProcessDialogRO->setText(displayedLine);
        }
    }
}

void processWindow::slShowDialog() {
    this->setModal(true);

    this->show();
}

void processWindow::slPostStdOutput(QByteArray stdOut) {
    this->postStdOutput(stdOut);
}

void processWindow::slStartDone(int returnBatch) {
    if (pProcessProgress->value() != 100) {
        this->incrementBar(100);
    }

    this->setWindowTitle("Flare Linux Container Report");

    pProcessLabel->setText("The bootstapping of the Flare Linux container is done.");

    pOkButton->setEnabled(true);

    if (returnBatch == 0) {
        pProcessDialogRO->append(tr("SUCCESS! The Flare server nodes will soon be available."));
    } else {
        pProcessDialogRO->append(tr("ERROR! The Flare server nodes could not be started."));
    }
}

void processWindow::slStopDone(int returnBatch) {
    if (pProcessProgress->value() != 100) {
        this->incrementBar(100);
    }

    this->setWindowTitle("Flare Linux Container Report");

    pProcessLabel->setText("The shut down of the Flare Linux container is done.");

    pOkButton->setEnabled(true);

    if (returnBatch == 0) {
        pProcessDialogRO->append(tr("SUCCESS! The Flare server nodes have been stopped."));
    }
    else {
        pProcessDialogRO->append(tr("WARNING! The Flare server nodes could not be stopped."));
    }
}
