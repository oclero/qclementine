#include <QApplication>

#include <oclero/qlementine/style/QlementineStyle.hpp>
#include <oclero/qlementine/icons/QlementineIcons.hpp>

#include "ShowcaseWindow.hpp"

#define USE_CUSTOM_STYLE 1

int main(int argc, char* argv[]) {
  // Must be set before creating a QApplication.
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif

  QApplication qApplication(argc, argv);

  // Must be set after creating a QApplication.
  QGuiApplication::setApplicationDisplayName("Showcase");
  QCoreApplication::setApplicationName("Showcase");
  QGuiApplication::setDesktopFileName("Showcase");
  QCoreApplication::setOrganizationName("oclero");
  QCoreApplication::setOrganizationDomain("olivierclero.com");
  QCoreApplication::setApplicationVersion("1.0.0");
  QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
  QApplication::setWindowIcon(QIcon(QStringLiteral(":/showcase/qlementine_icon.ico")));

  // Custom icon theme.
  oclero::qlementine::icons::initializeIconTheme();
  QIcon::setThemeName("qlementine");

  // Set custom QStyle.
#if USE_CUSTOM_STYLE
  auto* const style = new oclero::qlementine::QlementineStyle(&qApplication);
  style->setAnimationsEnabled(true);
  style->setUseMenuForComboBoxPopup(false);
  style->setAutoIconColor(oclero::qlementine::AutoIconColor::TextColor);
  style->setThemeJsonPath(QStringLiteral(":/light.json"));
  qApplication.setStyle(style);
#endif

  auto window = std::make_unique<oclero::qlementine::showcase::ShowcaseWindow>();
#if USE_CUSTOM_STYLE
  window->setCustomStyle(style);
#endif

  window->show();

  return qApplication.exec();
}