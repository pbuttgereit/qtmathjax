
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define HT 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->centralWidget->layout()->addWidget( engine.webView() );
    svg = new QSvgWidget( ui->widget );
    svg->setMinimumSize( 0, HT );
    ui->widget->setLayout( new QHBoxLayout( ui->widget ) );
    ui->widget->layout()->addWidget( svg );
    connect( ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(runMathJax()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runMathJax ()
{
    QString svgCode = engine.TeX2SVG( ui->lineEdit->text() );
    if ( engine.error().isEmpty() ) {
        svg->load( svgCode.toUtf8() );
        ui->plainTextEdit->setPlainText( svgCode );
    } else {
//        svg->load( QString( "<svg></svg>" ).toUtf8() );
        ui->plainTextEdit->setPlainText( engine.error() );
    }
    QSize s = svg->sizeHint();
    ui->widget->setMinimumSize( QSize( s.width()*HT/s.height(), HT*1.2 ) );
    ui->widget->setMaximumSize( QSize( s.width()*HT/s.height(), HT*1.2 ) );
    ui->widget->layout()->update();
}
