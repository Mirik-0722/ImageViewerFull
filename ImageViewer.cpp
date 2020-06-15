#include "ImageViewer.h"
#include "ui_ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    init();
    initConnections();
}

ImageViewer::~ImageViewer()
{
    delete ui;
}
void ImageViewer::init(){
    label = new QLabel;
    label->setBackgroundRole(QPalette::Base);
    label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    label->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(label);
    setCentralWidget(scrollArea);
    setWindowTitle(tr("Image Viewer"));
    resize(500,400);

//File menu
    fileMenu = new QMenu(tr("File"),this);

    openAction = new QAction(tr("Open..."),this);
    openAction->setShortcut(tr("Ctrl+O"));

    printAction = new QAction(tr("Print..."),this);
    printAction->setShortcut(tr("Ctrl+P"));
    printAction->setEnabled(false);

    exitAction = new QAction(tr("Exit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));

    fileMenu->addAction(openAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
//View Menu
    viewMenu = new QMenu(tr("View"),this);

    zoomInAction = new QAction(tr("Zoom In (25%)"),this);
    zoomInAction->setShortcut(tr("Ctrl+="));
    zoomInAction->setEnabled(false);

    zoomOutAction = new QAction(tr("Zoom Out (25%"),this);
    zoomOutAction->setShortcut(tr("Ctrl+-"));
    zoomOutAction->setEnabled(false);

    normalSizeAction = new QAction(tr("Normal Size"),this);
    normalSizeAction->setShortcut(tr("Ctrl+S"));
    normalSizeAction->setEnabled(false);

    fitToWindowAction = new QAction(tr("Fit to Window"),this);
    fitToWindowAction->setShortcut(tr("Ctrl+F"));
    fitToWindowAction->setEnabled(false);
    fitToWindowAction->setCheckable(true);

    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(normalSizeAction);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAction);

//Help Menu
    helpMenu = new QMenu(tr("Help"),this);

    aboutAction = new QAction(tr("About"),this);

    aboutQtAction = new QAction(tr("About Qt"));

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);

}
void ImageViewer::open(){
    qDebug() << "Open";
    QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Open File"),
                    QDir::currentPath()
                );
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(
                            this,
                            tr("Image Viewer"),
                            tr("Cannot load 1%.").arg(fileName)
                        );
            return;
        }
        label->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        printAction->setEnabled(true);
        fitToWindowAction->setEnabled(true);

        updateActions();

        if (!fitToWindowAction->isChecked()) {
            label->adjustSize();
        }
    }

}

void ImageViewer::updateActions(){
    zoomInAction->setEnabled(!fitToWindowAction->isChecked());
    zoomOutAction->setEnabled(!fitToWindowAction->isChecked());
    normalSizeAction->setEnabled(!fitToWindowAction->isChecked());

}

void ImageViewer::scaleImage(double factor){
    Q_ASSERT(label->pixmap());
    scaleFactor *= factor;
    label->resize(scaleFactor * label->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAction->setEnabled(scaleFactor < 3.0);
    zoomOutAction->setEnabled(scaleFactor >0.333);

}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor){
    scrollBar->setValue(int(factor * scrollBar->value() +
                            ((factor - 1) * scrollBar->pageStep()/2)));

}

void ImageViewer::zoomIn(){
    scaleImage(1.25);
}

void ImageViewer::zoomOut(){
    scaleImage(0.8);
}

void ImageViewer::normalSize(){
    label->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::fitToWindow(){
    bool fitToWindow =  fitToWindowAction->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void ImageViewer::about(){
    QMessageBox::about(
                this,
                tr("About Image Viewer"),
                tr("<b>Image Viewer</b> example.")
           );
}

void ImageViewer::close(){

    qDebug() << "Close.......";
    QApplication::exit();
}

void ImageViewer::initConnections(){
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(zoomOut()));
    connect(normalSizeAction,SIGNAL(triggered()),this,SLOT(zoomOut()));
    connect(fitToWindowAction,SIGNAL(triggered()),this,SLOT(fitToWindow()));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));
    connect(aboutQtAction,SIGNAL(triggered()),this,SLOT(aboutQt()));


}

void ImageViewer::aboutQt(){
    QApplication::aboutQt();
}









