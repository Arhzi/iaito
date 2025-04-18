#include "FlagDialog.h"
#include "ui_FlagDialog.h"

#include "core/Iaito.h"
#include <QIntValidator>

FlagDialog::FlagDialog(RVA offset, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FlagDialog)
    , offset(offset)
    , flagName("")
    , flagOffset(RVA_INVALID)
{
    // Setup UI
    ui->setupUi(this);
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));
    RFlagItem *flag = r_flag_get_i(Core()->core()->flags, offset);
    if (flag) {
        flagName = QString(flag->name);
#if R2_VERSION_NUMBER >= 50909
        flagOffset = flag->addr;
#else
        flagOffset = flag->offset;
#endif
    }

    auto size_validator = new QIntValidator(ui->sizeEdit);
    size_validator->setBottom(1);
    ui->sizeEdit->setValidator(size_validator);
    if (flag) {
        ui->nameEdit->setText(flag->name);
        ui->labelAction->setText(tr("Edit flag at %1").arg(RAddressString(offset)));
    } else {
        ui->labelAction->setText(tr("Add flag at %1").arg(RAddressString(offset)));
    }

    // Connect slots
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &FlagDialog::buttonBoxAccepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &FlagDialog::buttonBoxRejected);
}

FlagDialog::~FlagDialog() {}

void FlagDialog::buttonBoxAccepted()
{
    RVA size = ui->sizeEdit->text().toULongLong();
    QString name = ui->nameEdit->text();
    if (name.isEmpty()) {
        if (flagOffset != RVA_INVALID) {
            // Empty name and flag exists -> delete the flag
            Core()->delFlag(flagOffset);
        } else {
            // Flag was not existing and we gave an empty name, do nothing
        }
    } else {
        if (flagOffset != RVA_INVALID) {
            // Name provided and flag exists -> rename the flag
            Core()->renameFlag(flagName, name);
        } else {
            auto comment = ui->commentEdit->text();
            auto color = ui->colorEdit->text();
            // Name provided and flag does not exist -> create the flag
            Core()->addFlag(offset, name, size, color, comment);
        }
    }
    close();
    this->setResult(QDialog::Accepted);
}

void FlagDialog::buttonBoxRejected()
{
    close();
    this->setResult(QDialog::Rejected);
}
