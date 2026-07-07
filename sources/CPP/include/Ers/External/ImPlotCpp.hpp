// C++ convenience layer over cimplot (ImPlot C API). Mirrors the public ImPlot 0.17 C++ API
// from External/Include/implot/implot.h: default arguments, templates, and overload names.
// Include this instead of calling ImPlot_* directly when using Dear ImGui through cimgui.
#pragma once

#include <cstdarg>
#include <type_traits>

#include "Ers/External/cimplot/cimplot.h"

#ifndef IMPLOT_AUTO
#define IMPLOT_AUTO (-1)
#endif
#ifndef IMPLOT_AUTO_COL
#define IMPLOT_AUTO_COL ImVec4{0.0f, 0.0f, 0.0f, -1.0f}
#endif

namespace ImPlotCppBindings
{

    inline thread_local ImPlotGetter s_LineG = nullptr;
    inline void* LineGThunk(void* data, int idx, ImPlotPoint_c* pt)
    {
        ImPlotPoint_c r = s_LineG(idx, data);
        *pt             = r;
        return nullptr;
    }

    inline thread_local ImPlotGetter s_ScatterG = nullptr;
    inline void* ScatterGThunk(void* data, int idx, ImPlotPoint_c* pt)
    {
        ImPlotPoint_c r = s_ScatterG(idx, data);
        *pt             = r;
        return nullptr;
    }

    inline thread_local ImPlotGetter s_StairsG = nullptr;
    inline void* StairsGThunk(void* data, int idx, ImPlotPoint_c* pt)
    {
        ImPlotPoint_c r = s_StairsG(idx, data);
        *pt             = r;
        return nullptr;
    }

    inline thread_local ImPlotGetter s_BarsG = nullptr;
    inline void* BarsGThunk(void* data, int idx, ImPlotPoint_c* pt)
    {
        ImPlotPoint_c r = s_BarsG(idx, data);
        *pt             = r;
        return nullptr;
    }

    inline thread_local ImPlotGetter s_DigitalG = nullptr;
    inline void* DigitalGThunk(void* data, int idx, ImPlotPoint_c* pt)
    {
        ImPlotPoint_c r = s_DigitalG(idx, data);
        *pt             = r;
        return nullptr;
    }

    inline thread_local ImPlotGetter s_ShadedG1 = nullptr;
    inline thread_local ImPlotGetter s_ShadedG2 = nullptr;
    inline void* ShadedGThunk1(void* data, int idx, ImPlotPoint_c* pt)
    {
        ImPlotPoint_c r = s_ShadedG1(idx, data);
        *pt             = r;
        return nullptr;
    }
    inline void* ShadedGThunk2(void* data, int idx, ImPlotPoint_c* pt)
    {
        ImPlotPoint_c r = s_ShadedG2(idx, data);
        *pt             = r;
        return nullptr;
    }

// Columns: SufShadedXYInt = xs/ys + yref (two Ptr segments + Int). SufErrBarsInt = xs/ys/err + Int (three Ptr + Int).
#define ERS_IMPLOT_FOREACH_SCALAR_TYPE(X)                                                                                           \
    X(float, FloatPtrInt, FloatPtrFloatPtr, FloatPtrFloatPtrInt, FloatPtrFloatPtrFloatPtr, FloatPtrFloatPtrFloatPtrInt, FloatPtr,   \
      PlotFormatter, Str)                                                                                                           \
    X(double, doublePtrInt, doublePtrdoublePtr, doublePtrdoublePtrInt, doublePtrdoublePtrdoublePtr, doublePtrdoublePtrdoublePtrInt, \
      doublePtr, PlotFormatter, Str)                                                                                                \
    X(ImS8, S8PtrInt, S8PtrS8Ptr, S8PtrS8PtrInt, S8PtrS8PtrS8Ptr, S8PtrS8PtrS8PtrInt, S8Ptr, PlotFormatter, Str)                    \
    X(ImU8, U8PtrInt, U8PtrU8Ptr, U8PtrU8PtrInt, U8PtrU8PtrU8Ptr, U8PtrU8PtrU8PtrInt, U8Ptr, PlotFormatter, Str)                    \
    X(ImS16, S16PtrInt, S16PtrS16Ptr, S16PtrS16PtrInt, S16PtrS16PtrS16Ptr, S16PtrS16PtrS16PtrInt, S16Ptr, PlotFormatter, Str)       \
    X(ImU16, U16PtrInt, U16PtrU16Ptr, U16PtrU16PtrInt, U16PtrU16PtrU16Ptr, U16PtrU16PtrU16PtrInt, U16Ptr, PlotFormatter, Str)       \
    X(ImS32, S32PtrInt, S32PtrS32Ptr, S32PtrS32PtrInt, S32PtrS32PtrS32Ptr, S32PtrS32PtrS32PtrInt, S32Ptr, PlotFormatter, Str)       \
    X(ImU32, U32PtrInt, U32PtrU32Ptr, U32PtrU32PtrInt, U32PtrU32PtrU32Ptr, U32PtrU32PtrU32PtrInt, U32Ptr, PlotFormatter, Str)       \
    X(ImS64, S64PtrInt, S64PtrS64Ptr, S64PtrS64PtrInt, S64PtrS64PtrS64Ptr, S64PtrS64PtrS64PtrInt, S64Ptr, PlotFormatter, Str)       \
    X(ImU64, U64PtrInt, U64PtrU64Ptr, U64PtrU64PtrInt, U64PtrU64PtrU64Ptr, U64PtrU64PtrU64PtrInt, U64Ptr, PlotFormatter, Str)

    template <typename T> struct PlotDispatch
    {
    };

#define ERS_IMPLOT_DEFINE_DISPATCH(T, SufInt, SufXY, SufShadedXYInt, SufXY12, SufErrBarsInt, SufInf, PieFmt, PieStr)                       \
    template <> struct PlotDispatch<T>                                                                                                     \
    {                                                                                                                                      \
        static void PlotLineValues(                                                                                                        \
            const char* label_id, const T* values, int count, double xscale, double xstart, ImPlotLineFlags flags, int offset, int stride) \
        {                                                                                                                                  \
            ImPlot_PlotLine_##SufInt(label_id, values, count, xscale, xstart, flags, offset, stride);                                      \
        }                                                                                                                                  \
        static void PlotLineXY(const char* label_id, const T* xs, const T* ys, int count, ImPlotLineFlags flags, int offset, int stride)   \
        {                                                                                                                                  \
            ImPlot_PlotLine_##SufXY(label_id, xs, ys, count, flags, offset, stride);                                                       \
        }                                                                                                                                  \
        static void PlotScatterValues(                                                                                                     \
            const char* label_id,                                                                                                          \
            const T* values,                                                                                                               \
            int count,                                                                                                                     \
            double xscale,                                                                                                                 \
            double xstart,                                                                                                                 \
            ImPlotScatterFlags flags,                                                                                                      \
            int offset,                                                                                                                    \
            int stride)                                                                                                                    \
        {                                                                                                                                  \
            ImPlot_PlotScatter_##SufInt(label_id, values, count, xscale, xstart, flags, offset, stride);                                   \
        }                                                                                                                                  \
        static void                                                                                                                        \
        PlotScatterXY(const char* label_id, const T* xs, const T* ys, int count, ImPlotScatterFlags flags, int offset, int stride)         \
        {                                                                                                                                  \
            ImPlot_PlotScatter_##SufXY(label_id, xs, ys, count, flags, offset, stride);                                                    \
        }                                                                                                                                  \
        static void PlotStairsValues(                                                                                                      \
            const char* label_id,                                                                                                          \
            const T* values,                                                                                                               \
            int count,                                                                                                                     \
            double xscale,                                                                                                                 \
            double xstart,                                                                                                                 \
            ImPlotStairsFlags flags,                                                                                                       \
            int offset,                                                                                                                    \
            int stride)                                                                                                                    \
        {                                                                                                                                  \
            ImPlot_PlotStairs_##SufInt(label_id, values, count, xscale, xstart, flags, offset, stride);                                    \
        }                                                                                                                                  \
        static void                                                                                                                        \
        PlotStairsXY(const char* label_id, const T* xs, const T* ys, int count, ImPlotStairsFlags flags, int offset, int stride)           \
        {                                                                                                                                  \
            ImPlot_PlotStairs_##SufXY(label_id, xs, ys, count, flags, offset, stride);                                                     \
        }                                                                                                                                  \
        static void PlotShadedValues(                                                                                                      \
            const char* label_id,                                                                                                          \
            const T* values,                                                                                                               \
            int count,                                                                                                                     \
            double yref,                                                                                                                   \
            double xscale,                                                                                                                 \
            double xstart,                                                                                                                 \
            ImPlotShadedFlags flags,                                                                                                       \
            int offset,                                                                                                                    \
            int stride)                                                                                                                    \
        {                                                                                                                                  \
            ImPlot_PlotShaded_##SufInt(label_id, values, count, yref, xscale, xstart, flags, offset, stride);                              \
        }                                                                                                                                  \
        static void PlotShadedXY(                                                                                                          \
            const char* label_id, const T* xs, const T* ys, int count, double yref, ImPlotShadedFlags flags, int offset, int stride)       \
        {                                                                                                                                  \
            ImPlot_PlotShaded_##SufShadedXYInt(label_id, xs, ys, count, yref, flags, offset, stride);                                      \
        }                                                                                                                                  \
        static void PlotShadedXY12(                                                                                                        \
            const char* label_id, const T* xs, const T* ys1, const T* ys2, int count, ImPlotShadedFlags flags, int offset, int stride)     \
        {                                                                                                                                  \
            ImPlot_PlotShaded_##SufXY12(label_id, xs, ys1, ys2, count, flags, offset, stride);                                             \
        }                                                                                                                                  \
        static void PlotBarsValues(                                                                                                        \
            const char* label_id,                                                                                                          \
            const T* values,                                                                                                               \
            int count,                                                                                                                     \
            double bar_size,                                                                                                               \
            double shift,                                                                                                                  \
            ImPlotBarsFlags flags,                                                                                                         \
            int offset,                                                                                                                    \
            int stride)                                                                                                                    \
        {                                                                                                                                  \
            ImPlot_PlotBars_##SufInt(label_id, values, count, bar_size, shift, flags, offset, stride);                                     \
        }                                                                                                                                  \
        static void PlotBarsXY(                                                                                                            \
            const char* label_id, const T* xs, const T* ys, int count, double bar_size, ImPlotBarsFlags flags, int offset, int stride)     \
        {                                                                                                                                  \
            ImPlot_PlotBars_##SufXY(label_id, xs, ys, count, bar_size, flags, offset, stride);                                             \
        }                                                                                                                                  \
        static void PlotBarGroups(                                                                                                         \
            const char* const label_ids[],                                                                                                 \
            const T* values,                                                                                                               \
            int item_count,                                                                                                                \
            int group_count,                                                                                                               \
            double group_size,                                                                                                             \
            double shift,                                                                                                                  \
            ImPlotBarGroupsFlags flags)                                                                                                    \
        {                                                                                                                                  \
            ImPlot_PlotBarGroups_##SufInf(label_ids, values, item_count, group_count, group_size, shift, flags);                           \
        }                                                                                                                                  \
        static void PlotErrorBars(                                                                                                         \
            const char* label_id, const T* xs, const T* ys, const T* err, int count, ImPlotErrorBarsFlags flags, int offset, int stride)   \
        {                                                                                                                                  \
            ImPlot_PlotErrorBars_##SufErrBarsInt(label_id, xs, ys, err, count, flags, offset, stride);                                     \
        }                                                                                                                                  \
        static void PlotErrorBarsSplit(                                                                                                    \
            const char* label_id,                                                                                                          \
            const T* xs,                                                                                                                   \
            const T* ys,                                                                                                                   \
            const T* neg,                                                                                                                  \
            const T* pos,                                                                                                                  \
            int count,                                                                                                                     \
            ImPlotErrorBarsFlags flags,                                                                                                    \
            int offset,                                                                                                                    \
            int stride)                                                                                                                    \
        {                                                                                                                                  \
            ImPlot_PlotErrorBars_##SufXY##SufXY(label_id, xs, ys, neg, pos, count, flags, offset, stride);                                 \
        }                                                                                                                                  \
        static void PlotStemsValues(                                                                                                       \
            const char* label_id,                                                                                                          \
            const T* values,                                                                                                               \
            int count,                                                                                                                     \
            double ref,                                                                                                                    \
            double scale,                                                                                                                  \
            double start,                                                                                                                  \
            ImPlotStemsFlags flags,                                                                                                        \
            int offset,                                                                                                                    \
            int stride)                                                                                                                    \
        {                                                                                                                                  \
            ImPlot_PlotStems_##SufInt(label_id, values, count, ref, scale, start, flags, offset, stride);                                  \
        }                                                                                                                                  \
        static void                                                                                                                        \
        PlotStemsXY(const char* label_id, const T* xs, const T* ys, int count, double ref, ImPlotStemsFlags flags, int offset, int stride) \
        {                                                                                                                                  \
            ImPlot_PlotStems_##SufXY(label_id, xs, ys, count, ref, flags, offset, stride);                                                 \
        }                                                                                                                                  \
        static void PlotInfLines(const char* label_id, const T* values, int count, ImPlotInfLinesFlags flags, int offset, int stride)      \
        {                                                                                                                                  \
            ImPlot_PlotInfLines_##SufInf(label_id, values, count, flags, offset, stride);                                                  \
        }                                                                                                                                  \
        static void PlotPieChartFmt(                                                                                                       \
            const char* const label_ids[],                                                                                                 \
            const T* values,                                                                                                               \
            int count,                                                                                                                     \
            double x,                                                                                                                      \
            double y,                                                                                                                      \
            double radius,                                                                                                                 \
            ImPlotFormatter fmt,                                                                                                           \
            void* fmt_data,                                                                                                                \
            double angle0,                                                                                                                 \
            ImPlotPieChartFlags flags)                                                                                                     \
        {                                                                                                                                  \
            ImPlot_PlotPieChart_##SufInf##PieFmt(label_ids, values, count, x, y, radius, fmt, fmt_data, angle0, flags);                    \
        }                                                                                                                                  \
        static void PlotPieChartStr(                                                                                                       \
            const char* const label_ids[],                                                                                                 \
            const T* values,                                                                                                               \
            int count,                                                                                                                     \
            double x,                                                                                                                      \
            double y,                                                                                                                      \
            double radius,                                                                                                                 \
            const char* label_fmt,                                                                                                         \
            double angle0,                                                                                                                 \
            ImPlotPieChartFlags flags)                                                                                                     \
        {                                                                                                                                  \
            ImPlot_PlotPieChart_##SufInf##PieStr(label_ids, values, count, x, y, radius, label_fmt, angle0, flags);                        \
        }                                                                                                                                  \
        static void PlotHeatmap(                                                                                                           \
            const char* label_id,                                                                                                          \
            const T* values,                                                                                                               \
            int rows,                                                                                                                      \
            int cols,                                                                                                                      \
            double scale_min,                                                                                                              \
            double scale_max,                                                                                                              \
            const char* label_fmt,                                                                                                         \
            const ImPlotPoint_c& bounds_min,                                                                                               \
            const ImPlotPoint_c& bounds_max,                                                                                               \
            ImPlotHeatmapFlags flags)                                                                                                      \
        {                                                                                                                                  \
            ImPlot_PlotHeatmap_##SufInf(label_id, values, rows, cols, scale_min, scale_max, label_fmt, bounds_min, bounds_max, flags);     \
        }                                                                                                                                  \
        static double PlotHistogram(                                                                                                       \
            const char* label_id, const T* values, int count, int bins, double bar_scale, ImPlotRange_c range, ImPlotHistogramFlags flags) \
        {                                                                                                                                  \
            return ImPlot_PlotHistogram_##SufInf(label_id, values, count, bins, bar_scale, range, flags);                                  \
        }                                                                                                                                  \
        static double PlotHistogram2D(                                                                                                     \
            const char* label_id,                                                                                                          \
            const T* xs,                                                                                                                   \
            const T* ys,                                                                                                                   \
            int count,                                                                                                                     \
            int x_bins,                                                                                                                    \
            int y_bins,                                                                                                                    \
            ImPlotRect_c range,                                                                                                            \
            ImPlotHistogramFlags flags)                                                                                                    \
        {                                                                                                                                  \
            return ImPlot_PlotHistogram2D_##SufInf(label_id, xs, ys, count, x_bins, y_bins, range, flags);                                 \
        }                                                                                                                                  \
        static void                                                                                                                        \
        PlotDigital(const char* label_id, const T* xs, const T* ys, int count, ImPlotDigitalFlags flags, int offset, int stride)           \
        {                                                                                                                                  \
            ImPlot_PlotDigital_##SufInf(label_id, xs, ys, count, flags, offset, stride);                                                   \
        }                                                                                                                                  \
    };

    ERS_IMPLOT_FOREACH_SCALAR_TYPE(ERS_IMPLOT_DEFINE_DISPATCH)
#undef ERS_IMPLOT_DEFINE_DISPATCH

    template <typename T>
    constexpr bool SupportedPlotScalar =
        std::is_same_v<T, float> || std::is_same_v<T, double> || std::is_same_v<T, ImS8> || std::is_same_v<T, ImU8> ||
        std::is_same_v<T, ImS16> || std::is_same_v<T, ImU16> || std::is_same_v<T, ImS32> || std::is_same_v<T, ImU32> ||
        std::is_same_v<T, ImS64> || std::is_same_v<T, ImU64>;

} // namespace ImPlotCppBindings

namespace ImPlot
{

    // --- Contexts ---
    inline ImPlotContext* CreateContext()
    {
        return ImPlot_CreateContext();
    }
    inline void DestroyContext(ImPlotContext* ctx = nullptr)
    {
        ImPlot_DestroyContext(ctx);
    }
    inline ImPlotContext* GetCurrentContext()
    {
        return ImPlot_GetCurrentContext();
    }
    inline void SetCurrentContext(ImPlotContext* ctx)
    {
        ImPlot_SetCurrentContext(ctx);
    }
    inline void SetImGuiContext(ImGuiContext* ctx)
    {
        ImPlot_SetImGuiContext(ctx);
    }

    // --- Begin/End Plot ---
    inline bool BeginPlot(const char* title_id, const ImVec2& size = ImVec2{-1, 0}, ImPlotFlags flags = 0)
    {
        return ImPlot_BeginPlot(title_id, size, flags);
    }
    inline void EndPlot()
    {
        ImPlot_EndPlot();
    }

    inline bool BeginSubplots(
        const char* title_id,
        int rows,
        int cols,
        const ImVec2& size,
        ImPlotSubplotFlags flags = 0,
        float* row_ratios        = nullptr,
        float* col_ratios        = nullptr)
    {
        return ImPlot_BeginSubplots(title_id, rows, cols, size, flags, row_ratios, col_ratios);
    }
    inline void EndSubplots()
    {
        ImPlot_EndSubplots();
    }

    // --- Setup ---
    inline void SetupAxis(ImAxis axis, const char* label = nullptr, ImPlotAxisFlags flags = 0)
    {
        ImPlot_SetupAxis(axis, label, flags);
    }
    inline void SetupAxisLimits(ImAxis axis, double v_min, double v_max, ImPlotCond cond = ImPlotCond_Once)
    {
        ImPlot_SetupAxisLimits(axis, v_min, v_max, cond);
    }
    inline void SetupAxisLinks(ImAxis axis, double* link_min, double* link_max)
    {
        ImPlot_SetupAxisLinks(axis, link_min, link_max);
    }
    inline void SetupAxisFormat(ImAxis axis, const char* fmt)
    {
        ImPlot_SetupAxisFormat_Str(axis, fmt);
    }
    inline void SetupAxisFormat(ImAxis axis, ImPlotFormatter formatter, void* data = nullptr)
    {
        ImPlot_SetupAxisFormat_PlotFormatter(axis, formatter, data);
    }
    inline void
    SetupAxisTicks(ImAxis axis, const double* values, int n_ticks, const char* const labels[] = nullptr, bool keep_default = false)
    {
        ImPlot_SetupAxisTicks_doublePtr(axis, values, n_ticks, labels, keep_default);
    }
    inline void
    SetupAxisTicks(ImAxis axis, double v_min, double v_max, int n_ticks, const char* const labels[] = nullptr, bool keep_default = false)
    {
        ImPlot_SetupAxisTicks_double(axis, v_min, v_max, n_ticks, labels, keep_default);
    }
    inline void SetupAxisScale(ImAxis axis, ImPlotScale scale)
    {
        ImPlot_SetupAxisScale_PlotScale(axis, scale);
    }
    inline void SetupAxisScale(ImAxis axis, ImPlotTransform forward, ImPlotTransform inverse, void* data = nullptr)
    {
        ImPlot_SetupAxisScale_PlotTransform(axis, forward, inverse, data);
    }
    inline void SetupAxisLimitsConstraints(ImAxis axis, double v_min, double v_max)
    {
        ImPlot_SetupAxisLimitsConstraints(axis, v_min, v_max);
    }
    inline void SetupAxisZoomConstraints(ImAxis axis, double z_min, double z_max)
    {
        ImPlot_SetupAxisZoomConstraints(axis, z_min, z_max);
    }
    inline void SetupAxes(const char* x_label, const char* y_label, ImPlotAxisFlags x_flags = 0, ImPlotAxisFlags y_flags = 0)
    {
        ImPlot_SetupAxes(x_label, y_label, x_flags, y_flags);
    }
    inline void SetupAxesLimits(double x_min, double x_max, double y_min, double y_max, ImPlotCond cond = ImPlotCond_Once)
    {
        ImPlot_SetupAxesLimits(x_min, x_max, y_min, y_max, cond);
    }
    inline void SetupLegend(ImPlotLocation location, ImPlotLegendFlags flags = 0)
    {
        ImPlot_SetupLegend(location, flags);
    }
    inline void SetupMouseText(ImPlotLocation location, ImPlotMouseTextFlags flags = 0)
    {
        ImPlot_SetupMouseText(location, flags);
    }
    inline void SetupFinish()
    {
        ImPlot_SetupFinish();
    }

    // --- SetNext ---
    inline void SetNextAxisLimits(ImAxis axis, double v_min, double v_max, ImPlotCond cond = ImPlotCond_Once)
    {
        ImPlot_SetNextAxisLimits(axis, v_min, v_max, cond);
    }
    inline void SetNextAxisLinks(ImAxis axis, double* link_min, double* link_max)
    {
        ImPlot_SetNextAxisLinks(axis, link_min, link_max);
    }
    inline void SetNextAxisToFit(ImAxis axis)
    {
        ImPlot_SetNextAxisToFit(axis);
    }
    inline void SetNextAxesLimits(double x_min, double x_max, double y_min, double y_max, ImPlotCond cond = ImPlotCond_Once)
    {
        ImPlot_SetNextAxesLimits(x_min, x_max, y_min, y_max, cond);
    }
    inline void SetNextAxesToFit()
    {
        ImPlot_SetNextAxesToFit();
    }

    // --- Plot items (templates) ---
    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotLine(
        const char* label_id,
        const T* values,
        int count,
        double xscale         = 1,
        double xstart         = 0,
        ImPlotLineFlags flags = 0,
        int offset            = 0,
        int stride            = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotLineValues(label_id, values, count, xscale, xstart, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>>
    PlotLine(const char* label_id, const T* xs, const T* ys, int count, ImPlotLineFlags flags = 0, int offset = 0, int stride = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotLineXY(label_id, xs, ys, count, flags, offset, stride);
    }

    inline void PlotLineG(const char* label_id, ImPlotGetter getter, void* data, int count, ImPlotLineFlags flags = 0)
    {
        ImPlotGetter prev          = ImPlotCppBindings::s_LineG;
        ImPlotCppBindings::s_LineG = getter;
        ImPlot_PlotLineG(label_id, ImPlotCppBindings::LineGThunk, data, count, flags);
        ImPlotCppBindings::s_LineG = prev;
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotScatter(
        const char* label_id,
        const T* values,
        int count,
        double xscale            = 1,
        double xstart            = 0,
        ImPlotScatterFlags flags = 0,
        int offset               = 0,
        int stride               = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotScatterValues(label_id, values, count, xscale, xstart, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotScatter(
        const char* label_id, const T* xs, const T* ys, int count, ImPlotScatterFlags flags = 0, int offset = 0, int stride = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotScatterXY(label_id, xs, ys, count, flags, offset, stride);
    }

    inline void PlotScatterG(const char* label_id, ImPlotGetter getter, void* data, int count, ImPlotScatterFlags flags = 0)
    {
        ImPlotGetter prev             = ImPlotCppBindings::s_ScatterG;
        ImPlotCppBindings::s_ScatterG = getter;
        ImPlot_PlotScatterG(label_id, ImPlotCppBindings::ScatterGThunk, data, count, flags);
        ImPlotCppBindings::s_ScatterG = prev;
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotStairs(
        const char* label_id,
        const T* values,
        int count,
        double xscale           = 1,
        double xstart           = 0,
        ImPlotStairsFlags flags = 0,
        int offset              = 0,
        int stride              = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotStairsValues(label_id, values, count, xscale, xstart, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotStairs(
        const char* label_id, const T* xs, const T* ys, int count, ImPlotStairsFlags flags = 0, int offset = 0, int stride = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotStairsXY(label_id, xs, ys, count, flags, offset, stride);
    }

    inline void PlotStairsG(const char* label_id, ImPlotGetter getter, void* data, int count, ImPlotStairsFlags flags = 0)
    {
        ImPlotGetter prev            = ImPlotCppBindings::s_StairsG;
        ImPlotCppBindings::s_StairsG = getter;
        ImPlot_PlotStairsG(label_id, ImPlotCppBindings::StairsGThunk, data, count, flags);
        ImPlotCppBindings::s_StairsG = prev;
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotShaded(
        const char* label_id,
        const T* values,
        int count,
        double yref             = 0,
        double xscale           = 1,
        double xstart           = 0,
        ImPlotShadedFlags flags = 0,
        int offset              = 0,
        int stride              = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotShadedValues(label_id, values, count, yref, xscale, xstart, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotShaded(
        const char* label_id,
        const T* xs,
        const T* ys,
        int count,
        double yref             = 0,
        ImPlotShadedFlags flags = 0,
        int offset              = 0,
        int stride              = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotShadedXY(label_id, xs, ys, count, yref, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotShaded(
        const char* label_id,
        const T* xs,
        const T* ys1,
        const T* ys2,
        int count,
        ImPlotShadedFlags flags = 0,
        int offset              = 0,
        int stride              = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotShadedXY12(label_id, xs, ys1, ys2, count, flags, offset, stride);
    }

    inline void PlotShadedG(
        const char* label_id, ImPlotGetter getter1, void* data1, ImPlotGetter getter2, void* data2, int count, ImPlotShadedFlags flags = 0)
    {
        ImPlotGetter p1               = ImPlotCppBindings::s_ShadedG1;
        ImPlotGetter p2               = ImPlotCppBindings::s_ShadedG2;
        ImPlotCppBindings::s_ShadedG1 = getter1;
        ImPlotCppBindings::s_ShadedG2 = getter2;
        ImPlot_PlotShadedG(label_id, ImPlotCppBindings::ShadedGThunk1, data1, ImPlotCppBindings::ShadedGThunk2, data2, count, flags);
        ImPlotCppBindings::s_ShadedG1 = p1;
        ImPlotCppBindings::s_ShadedG2 = p2;
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotBars(
        const char* label_id,
        const T* values,
        int count,
        double bar_size       = 0.67,
        double shift          = 0,
        ImPlotBarsFlags flags = 0,
        int offset            = 0,
        int stride            = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotBarsValues(label_id, values, count, bar_size, shift, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotBars(
        const char* label_id,
        const T* xs,
        const T* ys,
        int count,
        double bar_size,
        ImPlotBarsFlags flags = 0,
        int offset            = 0,
        int stride            = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotBarsXY(label_id, xs, ys, count, bar_size, flags, offset, stride);
    }

    inline void PlotBarsG(const char* label_id, ImPlotGetter getter, void* data, int count, double bar_size, ImPlotBarsFlags flags = 0)
    {
        ImPlotGetter prev          = ImPlotCppBindings::s_BarsG;
        ImPlotCppBindings::s_BarsG = getter;
        ImPlot_PlotBarsG(label_id, ImPlotCppBindings::BarsGThunk, data, count, bar_size, flags);
        ImPlotCppBindings::s_BarsG = prev;
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotBarGroups(
        const char* const label_ids[],
        const T* values,
        int item_count,
        int group_count,
        double group_size          = 0.67,
        double shift               = 0,
        ImPlotBarGroupsFlags flags = 0)
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotBarGroups(label_ids, values, item_count, group_count, group_size, shift, flags);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotErrorBars(
        const char* label_id,
        const T* xs,
        const T* ys,
        const T* err,
        int count,
        ImPlotErrorBarsFlags flags = 0,
        int offset                 = 0,
        int stride                 = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotErrorBars(label_id, xs, ys, err, count, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotErrorBars(
        const char* label_id,
        const T* xs,
        const T* ys,
        const T* neg,
        const T* pos,
        int count,
        ImPlotErrorBarsFlags flags = 0,
        int offset                 = 0,
        int stride                 = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotErrorBarsSplit(label_id, xs, ys, neg, pos, count, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotStems(
        const char* label_id,
        const T* values,
        int count,
        double ref             = 0,
        double scale           = 1,
        double start           = 0,
        ImPlotStemsFlags flags = 0,
        int offset             = 0,
        int stride             = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotStemsValues(label_id, values, count, ref, scale, start, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotStems(
        const char* label_id,
        const T* xs,
        const T* ys,
        int count,
        double ref             = 0,
        ImPlotStemsFlags flags = 0,
        int offset             = 0,
        int stride             = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotStemsXY(label_id, xs, ys, count, ref, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>>
    PlotInfLines(const char* label_id, const T* values, int count, ImPlotInfLinesFlags flags = 0, int offset = 0, int stride = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotInfLines(label_id, values, count, flags, offset, stride);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotPieChart(
        const char* const label_ids[],
        const T* values,
        int count,
        double x,
        double y,
        double radius,
        ImPlotFormatter fmt,
        void* fmt_data            = nullptr,
        double angle0             = 90,
        ImPlotPieChartFlags flags = 0)
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotPieChartFmt(label_ids, values, count, x, y, radius, fmt, fmt_data, angle0, flags);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotPieChart(
        const char* const label_ids[],
        const T* values,
        int count,
        double x,
        double y,
        double radius,
        const char* label_fmt     = "%.1f",
        double angle0             = 90,
        ImPlotPieChartFlags flags = 0)
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotPieChartStr(label_ids, values, count, x, y, radius, label_fmt, angle0, flags);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotHeatmap(
        const char* label_id,
        const T* values,
        int rows,
        int cols,
        double scale_min              = 0,
        double scale_max              = 0,
        const char* label_fmt         = "%.1f",
        const ImPlotPoint& bounds_min = ImPlotPoint{0, 0},
        const ImPlotPoint& bounds_max = ImPlotPoint{1, 1},
        ImPlotHeatmapFlags flags      = 0)
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotHeatmap(
            label_id, values, rows, cols, scale_min, scale_max, label_fmt, bounds_min, bounds_max, flags);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotHistogram(
        const char* label_id,
        const T* values,
        int count,
        int bins                   = ImPlotBin_Sturges,
        double bar_scale           = 1.0,
        ImPlotRange range          = ImPlotRange{},
        ImPlotHistogramFlags flags = 0)
    {
        return ImPlotCppBindings::PlotDispatch<T>::PlotHistogram(label_id, values, count, bins, bar_scale, range, flags);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotHistogram2D(
        const char* label_id,
        const T* xs,
        const T* ys,
        int count,
        int x_bins                 = ImPlotBin_Sturges,
        int y_bins                 = ImPlotBin_Sturges,
        ImPlotRect range           = ImPlotRect{},
        ImPlotHistogramFlags flags = 0)
    {
        return ImPlotCppBindings::PlotDispatch<T>::PlotHistogram2D(label_id, xs, ys, count, x_bins, y_bins, range, flags);
    }

    template <typename T>
    inline std::enable_if_t<ImPlotCppBindings::SupportedPlotScalar<T>> PlotDigital(
        const char* label_id, const T* xs, const T* ys, int count, ImPlotDigitalFlags flags = 0, int offset = 0, int stride = sizeof(T))
    {
        ImPlotCppBindings::PlotDispatch<T>::PlotDigital(label_id, xs, ys, count, flags, offset, stride);
    }

    inline void PlotDigitalG(const char* label_id, ImPlotGetter getter, void* data, int count, ImPlotDigitalFlags flags = 0)
    {
        ImPlotGetter prev             = ImPlotCppBindings::s_DigitalG;
        ImPlotCppBindings::s_DigitalG = getter;
        ImPlot_PlotDigitalG(label_id, ImPlotCppBindings::DigitalGThunk, data, count, flags);
        ImPlotCppBindings::s_DigitalG = prev;
    }

    inline void PlotImage(
        const char* label_id,
        ImTextureRef tex_ref,
        const ImPlotPoint& bounds_min,
        const ImPlotPoint& bounds_max,
        const ImVec2& uv0      = ImVec2{0, 0},
        const ImVec2& uv1      = ImVec2{1, 1},
        const ImVec4& tint_col = ImVec4{1, 1, 1, 1},
        ImPlotImageFlags flags = 0)
    {
        ImPlot_PlotImage(label_id, tex_ref, bounds_min, bounds_max, uv0, uv1, tint_col, flags);
    }

    inline void PlotText(const char* text, double x, double y, const ImVec2& pix_offset = ImVec2{0, 0}, ImPlotTextFlags flags = 0)
    {
        ImPlot_PlotText(text, x, y, pix_offset, flags);
    }

    inline void PlotDummy(const char* label_id, ImPlotDummyFlags flags = 0)
    {
        ImPlot_PlotDummy(label_id, flags);
    }

    // --- Plot tools ---
    inline bool DragPoint(
        int id,
        double* x,
        double* y,
        const ImVec4& col,
        float size                = 4,
        ImPlotDragToolFlags flags = 0,
        bool* out_clicked         = nullptr,
        bool* out_hovered         = nullptr,
        bool* out_held            = nullptr)
    {
        return ImPlot_DragPoint(id, x, y, col, size, flags, out_clicked, out_hovered, out_held);
    }
    inline bool DragLineX(
        int id,
        double* x,
        const ImVec4& col,
        float thickness           = 1,
        ImPlotDragToolFlags flags = 0,
        bool* out_clicked         = nullptr,
        bool* out_hovered         = nullptr,
        bool* out_held            = nullptr)
    {
        return ImPlot_DragLineX(id, x, col, thickness, flags, out_clicked, out_hovered, out_held);
    }
    inline bool DragLineY(
        int id,
        double* y,
        const ImVec4& col,
        float thickness           = 1,
        ImPlotDragToolFlags flags = 0,
        bool* out_clicked         = nullptr,
        bool* out_hovered         = nullptr,
        bool* out_held            = nullptr)
    {
        return ImPlot_DragLineY(id, y, col, thickness, flags, out_clicked, out_hovered, out_held);
    }
    inline bool DragRect(
        int id,
        double* x1,
        double* y1,
        double* x2,
        double* y2,
        const ImVec4& col,
        ImPlotDragToolFlags flags = 0,
        bool* out_clicked         = nullptr,
        bool* out_hovered         = nullptr,
        bool* out_held            = nullptr)
    {
        return ImPlot_DragRect(id, x1, y1, x2, y2, col, flags, out_clicked, out_hovered, out_held);
    }

    inline void Annotation(double x, double y, const ImVec4& col, const ImVec2& pix_offset, bool clamp, bool round = false)
    {
        ImPlot_Annotation_Bool(x, y, col, pix_offset, clamp, round);
    }
    inline void Annotation(double x, double y, const ImVec4& col, const ImVec2& pix_offset, bool clamp, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImPlot_AnnotationV(x, y, col, pix_offset, clamp, fmt, args);
        va_end(args);
    }

    inline void TagX(double x, const ImVec4& col, bool round = false)
    {
        ImPlot_TagX_Bool(x, col, round);
    }
    inline void TagX(double x, const ImVec4& col, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImPlot_TagXV(x, col, fmt, args);
        va_end(args);
    }
    inline void TagY(double y, const ImVec4& col, bool round = false)
    {
        ImPlot_TagY_Bool(y, col, round);
    }
    inline void TagY(double y, const ImVec4& col, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImPlot_TagYV(y, col, fmt, args);
        va_end(args);
    }

    // --- Plot utils ---
    inline void SetAxis(ImAxis axis)
    {
        ImPlot_SetAxis(axis);
    }
    inline void SetAxes(ImAxis x_axis, ImAxis y_axis)
    {
        ImPlot_SetAxes(x_axis, y_axis);
    }

    inline ImPlotPoint PixelsToPlot(const ImVec2& pix, ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO)
    {
        return ImPlot_PixelsToPlot_Vec2(pix, x_axis, y_axis);
    }
    inline ImPlotPoint PixelsToPlot(float x, float y, ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO)
    {
        return ImPlot_PixelsToPlot_Float(x, y, x_axis, y_axis);
    }
    inline ImVec2 PlotToPixels(const ImPlotPoint& plt, ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO)
    {
        return ImPlot_PlotToPixels_PlotPoInt(plt, x_axis, y_axis);
    }
    inline ImVec2 PlotToPixels(double x, double y, ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO)
    {
        return ImPlot_PlotToPixels_double(x, y, x_axis, y_axis);
    }
    inline ImVec2 GetPlotPos()
    {
        return ImPlot_GetPlotPos();
    }
    inline ImVec2 GetPlotSize()
    {
        return ImPlot_GetPlotSize();
    }
    inline ImPlotPoint GetPlotMousePos(ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO)
    {
        return ImPlot_GetPlotMousePos(x_axis, y_axis);
    }
    inline ImPlotRect GetPlotLimits(ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO)
    {
        return ImPlot_GetPlotLimits(x_axis, y_axis);
    }
    inline bool IsPlotHovered()
    {
        return ImPlot_IsPlotHovered();
    }
    inline bool IsAxisHovered(ImAxis axis)
    {
        return ImPlot_IsAxisHovered(axis);
    }
    inline bool IsSubplotsHovered()
    {
        return ImPlot_IsSubplotsHovered();
    }
    inline bool IsPlotSelected()
    {
        return ImPlot_IsPlotSelected();
    }
    inline ImPlotRect GetPlotSelection(ImAxis x_axis = IMPLOT_AUTO, ImAxis y_axis = IMPLOT_AUTO)
    {
        return ImPlot_GetPlotSelection(x_axis, y_axis);
    }
    inline void CancelPlotSelection()
    {
        ImPlot_CancelPlotSelection();
    }
    inline void HideNextItem(bool hidden = true, ImPlotCond cond = ImPlotCond_Once)
    {
        ImPlot_HideNextItem(hidden, cond);
    }

    inline bool BeginAlignedPlots(const char* group_id, bool vertical = true)
    {
        return ImPlot_BeginAlignedPlots(group_id, vertical);
    }
    inline void EndAlignedPlots()
    {
        ImPlot_EndAlignedPlots();
    }

    // --- Legend ---
    inline bool BeginLegendPopup(const char* label_id, ImGuiMouseButton mouse_button = 1)
    {
        return ImPlot_BeginLegendPopup(label_id, mouse_button);
    }
    inline void EndLegendPopup()
    {
        ImPlot_EndLegendPopup();
    }
    inline bool IsLegendEntryHovered(const char* label_id)
    {
        return ImPlot_IsLegendEntryHovered(label_id);
    }

    // --- Drag and drop ---
    inline bool BeginDragDropTargetPlot()
    {
        return ImPlot_BeginDragDropTargetPlot();
    }
    inline bool BeginDragDropTargetAxis(ImAxis axis)
    {
        return ImPlot_BeginDragDropTargetAxis(axis);
    }
    inline bool BeginDragDropTargetLegend()
    {
        return ImPlot_BeginDragDropTargetLegend();
    }
    inline void EndDragDropTarget()
    {
        ImPlot_EndDragDropTarget();
    }
    inline bool BeginDragDropSourcePlot(ImGuiDragDropFlags flags = 0)
    {
        return ImPlot_BeginDragDropSourcePlot(flags);
    }
    inline bool BeginDragDropSourceAxis(ImAxis axis, ImGuiDragDropFlags flags = 0)
    {
        return ImPlot_BeginDragDropSourceAxis(axis, flags);
    }
    inline bool BeginDragDropSourceItem(const char* label_id, ImGuiDragDropFlags flags = 0)
    {
        return ImPlot_BeginDragDropSourceItem(label_id, flags);
    }
    inline void EndDragDropSource()
    {
        ImPlot_EndDragDropSource();
    }

    // --- Styling ---
    inline ImPlotStyle& GetStyle()
    {
        return *ImPlot_GetStyle();
    }
    inline void StyleColorsAuto(ImPlotStyle* dst = nullptr)
    {
        ImPlot_StyleColorsAuto(dst);
    }
    inline void StyleColorsClassic(ImPlotStyle* dst = nullptr)
    {
        ImPlot_StyleColorsClassic(dst);
    }
    inline void StyleColorsDark(ImPlotStyle* dst = nullptr)
    {
        ImPlot_StyleColorsDark(dst);
    }
    inline void StyleColorsLight(ImPlotStyle* dst = nullptr)
    {
        ImPlot_StyleColorsLight(dst);
    }

    inline void PushStyleColor(ImPlotCol idx, ImU32 col)
    {
        ImPlot_PushStyleColor_U32(idx, col);
    }
    inline void PushStyleColor(ImPlotCol idx, const ImVec4& col)
    {
        ImPlot_PushStyleColor_Vec4(idx, col);
    }
    inline void PopStyleColor(int count = 1)
    {
        ImPlot_PopStyleColor(count);
    }
    inline void PushStyleVar(ImPlotStyleVar idx, float val)
    {
        ImPlot_PushStyleVar_Float(idx, val);
    }
    inline void PushStyleVar(ImPlotStyleVar idx, int val)
    {
        ImPlot_PushStyleVar_Int(idx, val);
    }
    inline void PushStyleVar(ImPlotStyleVar idx, const ImVec2& val)
    {
        ImPlot_PushStyleVar_Vec2(idx, val);
    }
    inline void PopStyleVar(int count = 1)
    {
        ImPlot_PopStyleVar(count);
    }

    inline void SetNextLineStyle(const ImVec4& col = IMPLOT_AUTO_COL, float weight = IMPLOT_AUTO)
    {
        ImPlot_SetNextLineStyle(col, weight);
    }
    inline void SetNextFillStyle(const ImVec4& col = IMPLOT_AUTO_COL, float alpha_mod = IMPLOT_AUTO)
    {
        ImPlot_SetNextFillStyle(col, alpha_mod);
    }
    inline void SetNextMarkerStyle(
        ImPlotMarker marker   = IMPLOT_AUTO,
        float size            = IMPLOT_AUTO,
        const ImVec4& fill    = IMPLOT_AUTO_COL,
        float weight          = IMPLOT_AUTO,
        const ImVec4& outline = IMPLOT_AUTO_COL)
    {
        ImPlot_SetNextMarkerStyle(marker, size, fill, weight, outline);
    }
    inline void SetNextErrorBarStyle(const ImVec4& col = IMPLOT_AUTO_COL, float size = IMPLOT_AUTO, float weight = IMPLOT_AUTO)
    {
        ImPlot_SetNextErrorBarStyle(col, size, weight);
    }

    inline ImVec4 GetLastItemColor()
    {
        return ImPlot_GetLastItemColor();
    }
    inline const char* GetStyleColorName(ImPlotCol idx)
    {
        return ImPlot_GetStyleColorName(idx);
    }
    inline const char* GetMarkerName(ImPlotMarker idx)
    {
        return ImPlot_GetMarkerName(idx);
    }

    // --- Colormaps ---
    inline ImPlotColormap AddColormap(const char* name, const ImVec4* cols, int size, bool qual = true)
    {
        return ImPlot_AddColormap_Vec4Ptr(name, cols, size, qual);
    }
    inline ImPlotColormap AddColormap(const char* name, const ImU32* cols, int size, bool qual = true)
    {
        return ImPlot_AddColormap_U32Ptr(name, cols, size, qual);
    }
    inline int GetColormapCount()
    {
        return ImPlot_GetColormapCount();
    }
    inline const char* GetColormapName(ImPlotColormap cmap)
    {
        return ImPlot_GetColormapName(cmap);
    }
    inline ImPlotColormap GetColormapIndex(const char* name)
    {
        return ImPlot_GetColormapIndex(name);
    }
    inline void PushColormap(ImPlotColormap cmap)
    {
        ImPlot_PushColormap_PlotColormap(cmap);
    }
    inline void PushColormap(const char* name)
    {
        ImPlot_PushColormap_Str(name);
    }
    inline void PopColormap(int count = 1)
    {
        ImPlot_PopColormap(count);
    }
    inline ImVec4 NextColormapColor()
    {
        return ImPlot_NextColormapColor();
    }
    inline int GetColormapSize(ImPlotColormap cmap = IMPLOT_AUTO)
    {
        return ImPlot_GetColormapSize(cmap);
    }
    inline ImVec4 GetColormapColor(int idx, ImPlotColormap cmap = IMPLOT_AUTO)
    {
        return ImPlot_GetColormapColor(idx, cmap);
    }
    inline ImVec4 SampleColormap(float t, ImPlotColormap cmap = IMPLOT_AUTO)
    {
        return ImPlot_SampleColormap(t, cmap);
    }
    inline void ColormapScale(
        const char* label,
        double scale_min,
        double scale_max,
        const ImVec2& size             = ImVec2{0, 0},
        const char* format             = "%g",
        ImPlotColormapScaleFlags flags = 0,
        ImPlotColormap cmap            = IMPLOT_AUTO)
    {
        ImPlot_ColormapScale(label, scale_min, scale_max, size, format, flags, cmap);
    }
    inline bool
    ColormapSlider(const char* label, float* t, ImVec4* out = nullptr, const char* format = "", ImPlotColormap cmap = IMPLOT_AUTO)
    {
        return ImPlot_ColormapSlider(label, t, out, format, cmap);
    }
    inline bool ColormapButton(const char* label, const ImVec2& size = ImVec2{0, 0}, ImPlotColormap cmap = IMPLOT_AUTO)
    {
        return ImPlot_ColormapButton(label, size, cmap);
    }
    inline void BustColorCache(const char* plot_title_id = nullptr)
    {
        ImPlot_BustColorCache(plot_title_id);
    }

    // --- Input mapping ---
    inline ImPlotInputMap& GetInputMap()
    {
        return *ImPlot_GetInputMap();
    }
    inline void MapInputDefault(ImPlotInputMap* dst = nullptr)
    {
        ImPlot_MapInputDefault(dst);
    }
    inline void MapInputReverse(ImPlotInputMap* dst = nullptr)
    {
        ImPlot_MapInputReverse(dst);
    }

    // --- Miscellaneous ---
    inline void ItemIcon(const ImVec4& col)
    {
        ImPlot_ItemIcon_Vec4(col);
    }
    inline void ItemIcon(ImU32 col)
    {
        ImPlot_ItemIcon_U32(col);
    }
    inline void ColormapIcon(ImPlotColormap cmap)
    {
        ImPlot_ColormapIcon(cmap);
    }
    inline ImDrawList* GetPlotDrawList()
    {
        return ImPlot_GetPlotDrawList();
    }
    inline void PushPlotClipRect(float expand = 0)
    {
        ImPlot_PushPlotClipRect(expand);
    }
    inline void PopPlotClipRect()
    {
        ImPlot_PopPlotClipRect();
    }
    inline bool ShowStyleSelector(const char* label)
    {
        return ImPlot_ShowStyleSelector(label);
    }
    inline bool ShowColormapSelector(const char* label)
    {
        return ImPlot_ShowColormapSelector(label);
    }
    inline bool ShowInputMapSelector(const char* label)
    {
        return ImPlot_ShowInputMapSelector(label);
    }
    inline void ShowStyleEditor(ImPlotStyle* ref = nullptr)
    {
        ImPlot_ShowStyleEditor(ref);
    }
    inline void ShowUserGuide()
    {
        ImPlot_ShowUserGuide();
    }
    inline void ShowMetricsWindow(bool* p_popen = nullptr)
    {
        ImPlot_ShowMetricsWindow(p_popen);
    }
    inline void ShowDemoWindow(bool* p_open = nullptr)
    {
        ImPlot_ShowDemoWindow(p_open);
    }

} // namespace ImPlot

#undef ERS_IMPLOT_FOREACH_SCALAR_TYPE
