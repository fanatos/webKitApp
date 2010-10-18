#include <QtGui>

#include "xmlwriter.h"

XmlWriter::XmlWriter(QTreeWidget *treeWidget)
     : treeWidget(treeWidget)
{
    xml.setAutoFormatting(true);
}


bool XmlWriter::writeFile(QIODevice *device)
{
    xml.setDevice(device);

    xml.writeStartDocument();
    //xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xml");
    xml.writeAttribute("version", "1.0");
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)

        // returns the top level item at the given index
        writeItem(treeWidget->topLevelItem(i));

    xml.writeEndDocument();
    return true;
}

void XmlWriter::writeItem(QTreeWidgetItem *item)
{
    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == "folder") {
        bool folded = !treeWidget->isItemExpanded(item);
        xml.writeStartElement(tagName);
        xml.writeAttribute("folded", folded ? "yes" : "no");
        xml.writeTextElement("title", item->text(0));
        for (int i = 0; i < item->childCount(); ++i)
            writeItem(item->child(i));
        xml.writeEndElement();
    } else if (tagName == "bookmark") {
        xml.writeStartElement(tagName);
        if (!item->text(1).isEmpty())
            xml.writeAttribute("href", item->text(1));
        xml.writeTextElement("title", item->text(0));
        xml.writeEndElement();
    } else if (tagName == "separator") {
        xml.writeEmptyElement(tagName);
    }
}
