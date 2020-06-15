#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QScrollArea>
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QScrollBar>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageViewer; }
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();
public:
    void init();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void initConnections();
public slots:
    void open();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void aboutQt();
    void close();

private:
    Ui::ImageViewer *ui;

    //main
    QScrollArea *scrollArea;
    QLabel *label;


    //menus
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    //actions for File Menu
    QAction *openAction;
    QAction *printAction;
    QAction *exitAction;

    //actions for View Menu
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *normalSizeAction;
    QAction *fitToWindowAction;

    //actions for Help Menu
    QAction *aboutAction;
    QAction *aboutQtAction;

    double scaleFactor;


};
#endif // IMAGEVIEWER_H
