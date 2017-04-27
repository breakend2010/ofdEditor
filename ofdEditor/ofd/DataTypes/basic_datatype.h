#ifndef COMMONDT_H
#define COMMONDT_H

//6种基本数据类型
class ST_Loc {

};

class ST_Array {

};

class ST_ID {
public:
    unsigned long id;
};

class ST_RefID {
public:
    unsigned long ref_id;
};

class ST_Pos {
public:
    double x, y;
};

class ST_Box {
public:
    double start_x, start_y, delta_x, delta_y;
};


class CT_PageArea {
public:
    ST_Box physical_box;
};


class CT_Color {
    //属性
    ST_Array value;
    int index;
    ST_RefID colorspace;
};
#endif // COMMONDT_H
