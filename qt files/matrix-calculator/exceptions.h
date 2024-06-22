#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>
#include <QString>

class GeneralException : public std::exception {
public:
    explicit GeneralException(const QString& message) noexcept
        : m_message(message.toUtf8()) {}

    explicit GeneralException(const char* message) noexcept
        : m_message(message) {}

    virtual const char* what() const noexcept override {
        return m_message.c_str();
    }

    QString message() const noexcept {
        return QString::fromUtf8(m_message.c_str());
    }

private:
    std::string m_message;
};

class NonNumericException : public GeneralException {
public:
    explicit NonNumericException(const QString& message) noexcept
        : GeneralException(message) {}
};

class SizeTooLargeException : public GeneralException {
public:
    explicit SizeTooLargeException(const QString& message) noexcept
        : GeneralException(message) {}
};

#endif // CUSTOMEXCEPTIONS_H
