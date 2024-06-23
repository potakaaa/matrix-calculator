#ifndef ADD_TEXT_H
#define ADD_TEXT_H

#include <QString>

class spec_string {
private:
    QString text;
public:

    spec_string(QString txt=" ") {text = txt;}
    spec_string operator+(spec_string const& obj) {
        spec_string result;
        result = text + obj.text;
        return result;
    }
    QString to_qstring(spec_string s) {
        QString s1 = s.text;
        return s1;
    }
};


#endif // ADD_TEXT_H
