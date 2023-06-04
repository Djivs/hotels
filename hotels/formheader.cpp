#include "formheader.h"

FormHeader::FormHeader(QWidget *parent) :
    QWidget(parent) {
    exitButton = new QPushButton("Обратно");
    prevButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ArrowLeft), "");
    nextButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ArrowRight), "");
    printButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon), "");

    titleLabel = new QLabel("");
    titleLabel->setFont(QFont("Consolas", 15, QFont::Bold));

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(exitButton);
    buttonsLayout->addWidget(prevButton);
    buttonsLayout->addWidget(nextButton);
    buttonsLayout->addWidget(printButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(buttonsLayout);


    connect(exitButton, &QPushButton::clicked, this, [this] {emit exit();});
    connect(prevButton, &QPushButton::clicked, this, [this] {emit prev();});
    connect(nextButton, &QPushButton::clicked, this, [this] {emit next();});
    connect(printButton, &QPushButton::clicked, this, [this] {emit print();});

}

FormHeader::~FormHeader() {
}
