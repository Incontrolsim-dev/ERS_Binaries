#include "LogWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    LogWidget::LogWidget()
    {
        corePtr = Ers::Engine::ERS_LogWidget_Create();
    }

    LogWidget::~LogWidget()
    {
        Ers::Engine::ERS_LogWidget_Destroy(corePtr);
    }

    Logger::LogLevel LogWidget::GetSelectedLogLevel() const
    {
        return static_cast<Logger::LogLevel>(Ers::Engine::ERS_LogWidget_Get_SelectedLogLevel(corePtr));
    }

    bool LogWidget::GetAutoScroll() const
    {
        return Ers::Engine::ERS_LogWidget_Get_AutoScroll(corePtr);
    }

    void LogWidget::SetAutoScroll(bool value)
    {
        return Ers::Engine::ERS_LogWidget_Set_AutoScroll(corePtr, value);
    }

    void LogWidget::SetSelectedLogLevel(Logger::LogLevel level)
    {
        Ers::Engine::ERS_LogWidget_Set_SelectedLogLevel(corePtr, static_cast<int>(level));
    }

    void LogWidget::Window(const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_LogWidget_Window(corePtr, name, open, flags);
    }

    void LogWidget::Widget()
    {
        Ers::Engine::ERS_LogWidget_Widget(corePtr);
    }
} // namespace Ers
