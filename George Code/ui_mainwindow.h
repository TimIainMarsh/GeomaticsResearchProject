/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPoint_Cloud;
    QAction *actionSegmented_Point_Cloud;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLineEdit *txtCurvature;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *txtSmoothness;
    QLabel *label_5;
    QLineEdit *txtKNN;
    QLabel *label_2;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *txtMinClusterSize;
    QLineEdit *txtMaxClusterSize;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *btnSegment;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *txtFilename;
    QPushButton *btnFileBrowse;
    QPlainTextEdit *txtResults;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuViews;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(471, 531);
        actionPoint_Cloud = new QAction(MainWindow);
        actionPoint_Cloud->setObjectName(QStringLiteral("actionPoint_Cloud"));
        actionSegmented_Point_Cloud = new QAction(MainWindow);
        actionSegmented_Point_Cloud->setObjectName(QStringLiteral("actionSegmented_Point_Cloud"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        txtCurvature = new QLineEdit(groupBox);
        txtCurvature->setObjectName(QStringLiteral("txtCurvature"));

        gridLayout_3->addWidget(txtCurvature, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 2, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 1, 2, 1, 1);

        txtSmoothness = new QLineEdit(groupBox);
        txtSmoothness->setObjectName(QStringLiteral("txtSmoothness"));

        gridLayout_3->addWidget(txtSmoothness, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 1, 0, 1, 1);

        txtKNN = new QLineEdit(groupBox);
        txtKNN->setObjectName(QStringLiteral("txtKNN"));

        gridLayout_3->addWidget(txtKNN, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 3, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_3->addWidget(label_8, 4, 0, 1, 1);

        txtMinClusterSize = new QLineEdit(groupBox);
        txtMinClusterSize->setObjectName(QStringLiteral("txtMinClusterSize"));

        gridLayout_3->addWidget(txtMinClusterSize, 3, 1, 1, 1);

        txtMaxClusterSize = new QLineEdit(groupBox);
        txtMaxClusterSize->setObjectName(QStringLiteral("txtMaxClusterSize"));

        gridLayout_3->addWidget(txtMaxClusterSize, 4, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_3->addWidget(label_9, 3, 2, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_3->addWidget(label_10, 4, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 2);

        btnSegment = new QPushButton(centralWidget);
        btnSegment->setObjectName(QStringLiteral("btnSegment"));

        gridLayout_2->addWidget(btnSegment, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 1, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        txtFilename = new QLineEdit(frame);
        txtFilename->setObjectName(QStringLiteral("txtFilename"));

        gridLayout->addWidget(txtFilename, 0, 1, 1, 1);

        btnFileBrowse = new QPushButton(frame);
        btnFileBrowse->setObjectName(QStringLiteral("btnFileBrowse"));

        gridLayout->addWidget(btnFileBrowse, 0, 2, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 2);

        txtResults = new QPlainTextEdit(centralWidget);
        txtResults->setObjectName(QStringLiteral("txtResults"));

        gridLayout_2->addWidget(txtResults, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 471, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuViews = new QMenu(menuView);
        menuViews->setObjectName(QStringLiteral("menuViews"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuView->addAction(menuViews->menuAction());
        menuViews->addAction(actionPoint_Cloud);
        menuViews->addAction(actionSegmented_Point_Cloud);
        toolBar->addAction(actionPoint_Cloud);
        toolBar->addAction(actionSegmented_Point_Cloud);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionPoint_Cloud->setText(QApplication::translate("MainWindow", "Point Cloud", 0));
        actionSegmented_Point_Cloud->setText(QApplication::translate("MainWindow", "Segmented Point Cloud", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Parameters", 0));
        label_3->setText(QApplication::translate("MainWindow", "Curvature Threshold", 0));
        txtCurvature->setText(QApplication::translate("MainWindow", "5.0", 0));
        label_4->setText(QApplication::translate("MainWindow", "Degrees", 0));
        label_6->setText(QApplication::translate("MainWindow", "Degrees", 0));
        txtSmoothness->setText(QApplication::translate("MainWindow", "20.0", 0));
        label_5->setText(QApplication::translate("MainWindow", "Smoothness Threshold", 0));
        txtKNN->setText(QApplication::translate("MainWindow", "10", 0));
        label_2->setText(QApplication::translate("MainWindow", "KNN", 0));
        label_7->setText(QApplication::translate("MainWindow", "Min Cluster Size", 0));
        label_8->setText(QApplication::translate("MainWindow", "Max Cluster Size", 0));
        txtMinClusterSize->setText(QApplication::translate("MainWindow", "20", 0));
        txtMaxClusterSize->setText(QApplication::translate("MainWindow", "10000000", 0));
        label_9->setText(QApplication::translate("MainWindow", "Points", 0));
        label_10->setText(QApplication::translate("MainWindow", "Points", 0));
        btnSegment->setText(QApplication::translate("MainWindow", "Segment", 0));
        label->setText(QApplication::translate("MainWindow", "File name", 0));
        btnFileBrowse->setText(QApplication::translate("MainWindow", "Browse ...", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "Windows", 0));
        menuViews->setTitle(QApplication::translate("MainWindow", "Views ...", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
