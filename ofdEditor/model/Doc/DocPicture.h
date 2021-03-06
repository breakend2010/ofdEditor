#ifndef DOCPICTURE_H
#define DOCPICTURE_H

#include "model_global.h"       // 导出lib使用
#include "Doc/DocBasicTypes.h"
#include "Doc/DocImageBlock.h"


// 这个类应该只用来放图片，所以不需要鼠标光标编辑，直接通过菜单进行编辑
class MODELSHARED_EXPORT DocPicture
{
public:
    DocPicture();
    ~DocPicture();
};

#endif // DOCPICTURE_H
