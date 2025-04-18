#include "DebugOptionsWidget.h"
#include "PreferencesDialog.h"
#include "ui_DebugOptionsWidget.h"
#include <QComboBox>
#include <QFontDialog>
#include <QLabel>
#include <QShortcut>
#include <QTimer>

#include "common/Configuration.h"
#include "common/Helpers.h"

DebugOptionsWidget::DebugOptionsWidget(PreferencesDialog *dialog)
    : QDialog(dialog)
    , ui(new Ui::DebugOptionsWidget)
{
    ui->setupUi(this);

    updateDebugPlugin();

    connect(
        ui->pluginComboBox,
        &QComboBox::currentTextChanged,
        this,
        &DebugOptionsWidget::onDebugPluginChanged);
}

DebugOptionsWidget::~DebugOptionsWidget() {}

void DebugOptionsWidget::updateDebugPlugin()
{
    ui->esilBreakOnInvalid->setChecked(Config()->getConfigBool("esil.breakoninvalid"));
    disconnect(
        ui->pluginComboBox,
        &QComboBox::currentTextChanged,
        this,
        &DebugOptionsWidget::onDebugPluginChanged);

    QStringList plugins = Core()->getDebugPlugins();
    for (const QString &str : plugins)
        ui->pluginComboBox->addItem(str);

    QString plugin = Core()->getActiveDebugPlugin();
    ui->pluginComboBox->setCurrentText(plugin);

    connect(
        ui->pluginComboBox,
        &QComboBox::currentTextChanged,
        this,
        &DebugOptionsWidget::onDebugPluginChanged);

    QString stackSize = Core()->getConfig("esil.stack.size");
    ui->stackSize->setText(stackSize);
    ui->stackSize->setPlaceholderText(stackSize);
    QString stackAddr = Core()->getConfig("esil.stack.addr");
    ui->stackAddr->setText(stackAddr);
    ui->stackAddr->setPlaceholderText(stackAddr);
    connect(ui->stackAddr, &QLineEdit::editingFinished, this, &DebugOptionsWidget::updateStackAddr);
    connect(ui->stackSize, &QLineEdit::editingFinished, this, &DebugOptionsWidget::updateStackSize);
}

void DebugOptionsWidget::onDebugPluginChanged(const QString &plugin)
{
    Core()->setDebugPlugin(plugin);
}

void DebugOptionsWidget::updateStackSize()
{
    QString newSize = ui->stackSize->text();
    Core()->setConfig("esil.stack.size", newSize);
    ui->stackSize->setPlaceholderText(newSize);
}

void DebugOptionsWidget::updateStackAddr()
{
    QString newAddr = ui->stackAddr->text();
    Core()->setConfig("esil.stack.addr", newAddr);
    ui->stackAddr->setPlaceholderText(newAddr);
}

void DebugOptionsWidget::on_esilBreakOnInvalid_toggled(bool checked)
{
    Config()->setConfig("esil.breakoninvalid", checked);
}
