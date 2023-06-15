#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QTest>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

private slots:
    void test();

};

#endif // TEST_H
