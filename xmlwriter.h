#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QXmlStreamWriter>

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class XmlWriter {

public:

    XmlWriter(QTreeWidget *treeWidget);
    bool writeFile(QIODevice *device);

private:

    void writeItem(QTreeWidgetItem *item);

    QXmlStreamWriter xml;
    QTreeWidget *treeWidget;
};


#endif // XMLWRITER_H

