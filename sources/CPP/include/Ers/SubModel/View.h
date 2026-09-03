#pragma once
#include "BaseView.h"

#include "Ers/SubModel/Component/GlobalComponentTypes.h"
#include "Ers/SubModel/Entity.h"

#include <array>
#include <tuple>
#include <type_traits>

namespace Ers
{
    // Primary template: Not found
    template <typename T, typename... Types> struct IndexOf;

    // Specialization: Found at index 0
    template <typename T, typename... Types> struct IndexOf<T, T, Types...> : std::integral_constant<uint32_t, 0>
    {
    };

    // Recursion: Search in the remaining types, incrementing the index
    template <typename T, typename U, typename... Types>
    struct IndexOf<T, U, Types...> : std::integral_constant<uint32_t, 1 + IndexOf<T, Types...>::value>
    {
    };

    /// @brief Creates a static array that maps component types to type ids.
    /// @tparam ...Types Component types
    /// @return reference to a std::array of integers which represent the type ids for these components.
    template <typename... Types> std::array<ComponentID, sizeof...(Types)>& GetComponentArray()
    {
        // Cant be done at compile time so instead one array is generated at
        // runtime, but only once for each combination of types.
        static auto arr = []() -> std::array<ComponentID, sizeof...(Types)>
        {
            int index = 0;
            std::array<ComponentID, sizeof...(Types)> array;
            ((array[index++] = GetComponentTypeID<Types>()), ...);
            return array;
        }
        ();
        return arr;
    }

    // Helper struct for exclude types. Without this struct the typenames of View() will be ambiguous.
    template <typename... Types> struct ExcludedTypes
    {
    };

    /// @brief This class is the way users interact with views of the core, it allows specialization of the Included components as well as
    /// the /// excluded components. It takes care of type identification and passing to the core, conversions handle at compile-time.
    /// Please note
    template <typename... Types> class View : public BaseView
    {
      public:
        explicit View(void* submodel, uint32_t* excluded = nullptr, uint32_t excludedSize = 0) :
            BaseView(submodel, GetComponentArray<Types...>().data(), GetComponentArray<Types...>().size(), excluded, excludedSize)
        {
        }
        View(const View&)                = delete;
        View(View&&)                     = default;
        View& operator=(const View&)     = delete;
        View& operator=(View&&) noexcept = default;
        ~View() override                 = default;

        inline std::tuple<Entity, Types&...> Get() { return GetHelper(std::index_sequence_for<Types...>{}); }

        template <typename T> inline T& GetComponent()
        {
            uint32_t index     = IndexOf<T, Types...>::value;
            void* componentPtr = BaseView::GetComponent(index);
            return *static_cast<T*>(componentPtr);
        }

        class ViewIterator;

        /// @brief Get the enumerator at the first matching entity and its component(s).
        ViewIterator begin();

        /// @brief Get the enumerator at the last matching entity and its component(s).
        ViewIterator end();

      private:
        template <std::size_t... Is> inline std::tuple<EntityID, Types&...> GetHelper(std::index_sequence<Is...>)
        {
            void** components = Ers::Engine::ERS_Submodel_View_GetComponents(corePtr);
            Entity entity     = Ers::Engine::ERS_Submodel_View_GetEntity(corePtr);
            return std::forward_as_tuple(entity, (*reinterpret_cast<Types*>(components[Is]))...);
        }
    };

    /// @brief Allows for enumeration over entities in a view. Becomes invalid once the view advances past the end or is destroyed.
    template <typename... Types> class View<Types...>::ViewIterator
    {
      public:
        ViewIterator() :
            view(nullptr),
            atEnd(true)
        {
        }

        explicit ViewIterator(View* view) :
            view(view),
            atEnd(!view->Next())
        {
        }

        std::tuple<Entity, Types&...> operator*() const { return view->Get(); }

        ViewIterator& operator++()
        {
            atEnd = !view->Next();
            return *this;
        }

        bool operator==(const ViewIterator& other) const { return atEnd == other.atEnd; }

        bool operator!=(const ViewIterator& other) const { return !(*this == other); }

      private:
        View* view;
        bool atEnd;
    };

    template <typename... Types> typename View<Types...>::ViewIterator View<Types...>::begin()
    {
        return ViewIterator(this);
    }

    template <typename... Types> typename View<Types...>::ViewIterator View<Types...>::end()
    {
        return ViewIterator();
    }
} // namespace Ers
