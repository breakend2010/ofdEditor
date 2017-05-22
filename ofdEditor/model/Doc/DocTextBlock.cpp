#include "DocTextBlock.h"
#include "Doc/DocParagraph.h"
#include "Widget/ParagraphFormatDialog.h"

#include <QTextCursor>
#include <QPalette>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QDebug>
#include <QFontDialog>


DocTextBlock::DocTextBlock(QWidget *parent)
    :QTextEdit(parent)
{
//    QTextCursor cursor(this->textCursor());
//    cursor.insertText(tr("testsesetstsetestes"));

//    this->setBackgroundRole(QPalette::Dark);
    this->init();   // 调用初始化函数

}

DocTextBlock::~DocTextBlock()
{

}

/**
 * @Author Chaoqun
 * @brief  设置文本内容
 * @param  QString str
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::setContent(QString str)
{
    QTextCursor cursor(this->textCursor());
    cursor.insertText(str);
}

/**
 * @Author Chaoqun
 * @brief  用来合并格式
 * @param  const QTextCharFormat &format
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::mergeFormatOnWordOrSelection(
        const QTextCharFormat &format)
{
    QTextCursor cursor = this->textCursor(); // 新建光标
    if(!cursor.hasSelection())
    {
        // 如果没有选择文字段落
        cursor.select(QTextCursor::WordUnderCursor);
        qDebug() << "cursor has no selection!";
    }
    cursor.mergeCharFormat(format);         // 合并光标下的 QTextCharFormat
    this->mergeCurrentCharFormat(format);   // 合并当前的 QTextCharFormat

}

/**
 * @Author Chaoqun
 * @brief  当前CharFormat样式发上改变的响应函数，
 *         当增加了一个字体控制的widget时，可以使用
 * @param  const QTextCharFormat &format
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::currentCharFormatChangedEvent(
        const QTextCharFormat &format)
{

}

/**
 * @Author Chaoqun
 * @brief  光标位置发生改变时的响应函数
 * @param  void
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::cursorPositionChangedEvent()
{
    //    qDebug() << "Cursor Position Changed!";
}

void DocTextBlock::setFont(const QFont &font)
{
    QTextCharFormat currentFormat =
            this->currentCharFormat();      // 当前选择文字的样式
    currentFormat.setFont(font);            // 设置字体

    mergeCurrentCharFormat(currentFormat);
}



/**
 * @Author Chaoqun
 * @brief  文字加粗
 * @param  void
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::textBold()
{
    QTextCharFormat fmt;
    QTextCharFormat currentFormat = this->currentCharFormat();      // 当前选择文字的样式
    fmt.setFontWeight(currentFormat.fontWeight() != QFont::Bold ?   // 设置粗细
                          QFont::Bold : QFont::Normal);

    mergeFormatOnWordOrSelection(fmt);      // 合并格式

}

/**
 * @Author Chaoqun
 * @brief  设置下划线
 * @param  void
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::textUnderline()
{
    QTextCharFormat fmt;
    QTextCharFormat currentFormat = this->currentCharFormat();      // 当前选择文字的样式

    fmt.setFontUnderline(currentFormat.fontUnderline()?
                             false:true);

    mergeFormatOnWordOrSelection(fmt);      // 合并格式
}

/**
 * @Author Chaoqun
 * @brief  设置斜体
 * @param  void
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::textItalic()
{
    QTextCharFormat fmt;
    QTextCharFormat currentFormat = this->currentCharFormat();      // 当前选择文字的样式
    fmt.setFontItalic(currentFormat.fontItalic() == true?                  // 设置斜体
                          false:true);

    mergeFormatOnWordOrSelection(fmt);      // 合并格式
}

/**
 * @Author Chaoqun
 * @brief  弹出一个段落属性设置的QDialog，设置好了后，
 *          将该属性应用在选中的段落上
 * @param  void
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::textParagraph()
{
    ParagraphFormatDialog * para = new ParagraphFormatDialog();

    para->exec();
}

/**
 * @Author Chaoqun
 * @brief  通过字体小窗口设置字体
 * @param  void
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::textFontDialog()
{
    bool btn_ok;    // 确认按键
    QTextCharFormat currentFormat =
            this->currentCharFormat();      // 当前选择文字的样式
    QFont oldFont = currentFormat.font();   // 获取之前的字体样式

    QFont newFont = QFontDialog::getFont(
                &btn_ok, oldFont,NULL,tr("Set the font"),
                QFontDialog::ScalableFonts);    // 选择字体框

    if(btn_ok)
    {
        this->setFont(newFont);     // 设置字体
    }
    else
    {
        // 用户取消了操作，不做处理
        qDebug() << "Cancel select Font!";
    }


}

/**
 * @Author Chaoqun
 * @brief  设置当前选中的段落的格式
 * @param  参数
 * @return 返回值
 * @date   2017/05/22
 */
void DocTextBlock::setTextBlockFormat(
        const QTextBlockFormat &blockFormat)
{
    QTextCursor cursor = this->textCursor(); // 新建光标
    if(!cursor.hasSelection())
    {
        // 如果没有选择文字段落
        cursor.select(QTextCursor::WordUnderCursor);
        qDebug() << "cursor has no selection!";
    }

    cursor.setBlockFormat(blockFormat);
    qDebug()<<"Change the selected QTextBlock' Format. Test";


}

/**
 * @Author Chaoqun
 * @brief  显示右键菜单
 * @param  QContextMenuEvent *event
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::contextMenuEvent(QContextMenuEvent *event)
{

    // 展示菜单
    this->ContextMenu->exec(event->globalPos());

}

/**
 * @Author Chaoqun
 * @brief  初始化函数
 * @param  void
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::init()
{
    this->setMinimumSize(15,15);        // 为了正确显示缩放标识

    this->currentTextCharFormat = new QTextCharFormat();        // 初始化


    // 连接当前charFormat改变函数
    connect(this, &DocTextBlock::currentCharFormatChanged,
            this, &DocTextBlock::currentCharFormatChangedEvent);

    // 连接当前光标位置改变事件
    connect(this, &DocTextBlock::cursorPositionChanged,
            this, &DocTextBlock::cursorPositionChangedEvent);

    this->initAcitons();    // 初始化QAction相关
}

/**
 * @Author Chaoqun
 * @brief  初始化按钮 ， QAction
 * @param  void
 * @return 返回值
 * @date   2017/05/21
 */
void DocTextBlock::initAcitons()
{
    // 粗体
    this->actionBold = new QAction(tr("Bold"));
    this->actionBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    this->actionBold->setFont(bold);

    this->connect(this->actionBold,&QAction::triggered,
                  this,&DocTextBlock::textBold);

    // 斜体
    this->actionItalic = new QAction(tr("Italic"));
    this->actionItalic->setPriority(QAction::LowPriority);
    QFont italic;
    italic.setItalic(true);
    this->actionItalic->setFont(italic);

    this->connect(this->actionItalic,&QAction::triggered,
                  this,&DocTextBlock::textItalic);

    // 下划线
    this->actionUnderline = new QAction(tr("Underline"));
    this->actionUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    this->actionUnderline->setFont(underline);

    this->connect(this->actionUnderline, &QAction::triggered,
                  this,&DocTextBlock::textUnderline);

    // 字体
    this->actionFontSet = new QAction(tr("Font"));
    this->actionFontSet->setPriority(QAction::LowPriority);

    this->connect(this->actionFontSet,&QAction::triggered,
                  this,&DocTextBlock::textFontDialog);

    this->actionParagraph = new QAction(tr("Font"));

    this->connect(this->actionParagraph,&QAction::triggered,
                  this,&DocTextBlock::textParagraphWidget);

    // 右键菜单
    this->ContextMenu = createStandardContextMenu();     // 拓展标准菜单
    this->ContextMenu->addAction(this->actionBold);
    this->ContextMenu->addAction(this->actionItalic);
    this->ContextMenu->addAction(this->actionUnderline);
    this->ContextMenu->addSeparator();
    this->ContextMenu->addAction(this->actionFontSet);
    this->ContextMenu->addAction(this->actionParagraph);
}
