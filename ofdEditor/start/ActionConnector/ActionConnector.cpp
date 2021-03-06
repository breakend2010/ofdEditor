#include "ActionConnector.h"
#include "Doc/DocPassage.h"
#include "ui/PassageMainWindow.h"
#include "Doc/DocPage.h"
#include "DataTypes/document/ct_docinfo.h"
#include "Widget/InsertTableDialog.h"
#include "Widget/DocInfoDialog.h"
#include <QDebug>
#include <QMetaObject>


ActionConnector::ActionConnector()
{
    init();
}

ActionConnector::ActionConnector(PassageMainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    init();
}

DocPassage *ActionConnector::getActivePassage()
{
    return this->passage;
}

void ActionConnector::showAttribute()
{
    if(this->passage == NULL)
    {
        qDebug() << "show attribute this->passage == NULL";
        return;
    }

    CT_DocInfo * docInfo = this->passage->getDocInfo();
    DocInfoDialog* dialog = DocInfoDialog::getInstance();   // 获得实例
    dialog->init(docInfo);                                  // 设置窗口
    dialog->exec();                  // 运行

}

void ActionConnector::setMainWindow(PassageMainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    init();
}


/**
 * @Author Chaoqun
 * @brief  为页面增加一个空白页，默认加在最后一页
 * @param  参数
 * @return 返回值
 * @date   2017/05/15
 */
void ActionConnector::addNewPage()
{

    if(this->passage == NULL)
        return;
    this->passage->appendNewPage();     // 在队尾增加一页

}

/**
 *@Author Chaoqun
 *@brief  增加一个新块
 *@param  参数
 *@return 返回值
 *@date   2017/05/15
 */
void ActionConnector::addNewBlock(InsertBlockInfo blockInfo)
{
    if(this->passage == NULL)
    {
        return;
    }

//    this->updateActivePassage();    // 更新文章
    DocPage *page = this->passage->getLastedActivedPage();      // 获得最近操作过的页面
    if(page == NULL)
    {
        qDebug() <<"NO Last actived page";
        return;
    }
    else
    {

        if (blockInfo.type == DocPage::text)
        {
            //插入文本框
//            qDebug() << "get Focus Sucess";
            page->setBlockFlag(DocPage::draw);              // 进入绘画状态
            page->setInsertBlockType(blockInfo);            // 设置插入文本框信息
            page->viewport()->setCursor(Qt::CrossCursor);   // 将鼠标设置为加号形状
        }
        else if (blockInfo.type == DocPage::image)
        {
            //插入图片框
            page->setInsertBlockType(blockInfo);            // 设置插入文本框信息
            page->addImage();
        }
        else if( blockInfo.type == DocPage::table )
        {
            // 插入表格
            page->setInsertBlockType(blockInfo);            // 设置插入为表格
            page->addTable();                               // 从对话框来设置
        }
    }
}

void ActionConnector::addTextBlock()
{
    if(this->passage == NULL)
        return;
    InsertBlockInfo blockInfo(this->defaultLayer,DocPage::text);  // 设置插入文本框信息
    this->addNewBlock(blockInfo);
}

void ActionConnector::addImageBlock()
{
    if(this->passage == NULL)
        return;
    InsertBlockInfo blockInfo(this->defaultLayer,DocPage::image);  // 设置插入文本框信息
//    qDebug() << "add imageBlock";
    this->addNewBlock(blockInfo);
}

void ActionConnector::addTableBlock()
{
    if(this->passage == NULL)
        return;

    InsertBlockInfo blockInfo(this->defaultLayer,DocPage::table);  // 设置插入文本框信息
    this->addNewBlock(blockInfo);
//    InsertTableDialog * tableDialog = new InsertTableDialog(0);
//    tableDialog->exec();
}

void ActionConnector::undo()
{
    qDebug() <<"undo";
    this->passage->undoStack->undo();
}

void ActionConnector::redo()
{
    qDebug() <<"redo";
    this->passage->undoStack->redo();
}

void ActionConnector::setDocPassage(DocPassage *passage)
{
    this->passage = passage;
}

void ActionConnector::updateActivePassage(DocPassage *passage)
{
    this->passage = passage;
}

void ActionConnector::startFindAndReplace()
{
    mainWindow->activateFindAndReplaceDock();

}

DocPage *ActionConnector::getActivePage()
{
    return qobject_cast<DocPage *>(this->passage->focusWidget());
}

void ActionConnector::init()
{
    this->defaultLayer = DocPage::Body;
    this->passage = NULL;   // 初始化为空

}
