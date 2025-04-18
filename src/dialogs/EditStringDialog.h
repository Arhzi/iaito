#ifndef EDITSTRINGDIALOG_H
#define EDITSTRINGDIALOG_H

#include <memory>
#include <QDialog>

namespace Ui {
class EditStringDialog;
}

class EditStringDialog : public QDialog
{
    Q_OBJECT

public:
    enum class StringType { s_Auto, s_ASCII_LATIN1, s_UTF8, s_UTF16, s_PASCAL };
    explicit EditStringDialog(QWidget *parent = nullptr);
    ~EditStringDialog();

    /**
     * @brief Sets the address of the first byte of potential string in the
     * dialog
     *
     * @param address The address of the bytearray where string is located
     */
    void setStringStartAddress(uint64_t address);
    /**
     * @brief Returns the address of the first byte of potential string in the
     * dialog
     *
     * @param[out] returnValue The address of the bytearray where string is
     * located
     * @return whether the call successful or not
     */
    bool getStringStartAddress(uint64_t &returnValue) const;

    /**
     * @brief Sets the size of string in the dialog
     *
     * @param size The size of string in the dialog
     */
    void setStringSizeValue(uint32_t size);
    /**
     * @brief Returns the size of string in the dialog
     *
     * @return -1 on error otherwise the size of string from the dialog
     */
    int getStringSizeValue() const;

    /**
     * @brief Returns the type of string from the dialog
     *
     * @return The type of string from the dialog
     */
    StringType getStringType() const;

private:
    std::unique_ptr<Ui::EditStringDialog> ui;
};

#endif // EDITSTRINGDIALOG_H
