#pragma once

#include <string>

namespace Ers
{
    class LibraryCollection
    {
      public:
        explicit LibraryCollection(void* instance);

        LibraryCollection()                                    = delete;
        LibraryCollection(const LibraryCollection&)            = delete;
        LibraryCollection(LibraryCollection&&)                 = delete;
        LibraryCollection& operator=(const LibraryCollection&) = delete;
        LibraryCollection& operator=(LibraryCollection&&)      = delete;

        // The destructor explicitly doesn't have to free memory as this is managed within ers-core
        ~LibraryCollection() = default;

        // Library functions
        [[nodiscard]] bool OpenLibrary(const std::string& libraryPath) const;
        [[nodiscard]] bool IsLibraryOpen(const std::string& libraryPath) const;

        [[nodiscard]] void* GetFunctionRaw(const std::string& libraryPath, const std::string& functionName) const;

        template <typename FunctionSignature>
        FunctionSignature* GetFunction(const std::string& libraryPath, const std::string& functionName) const
        {
            return reinterpret_cast<FunctionSignature*>(GetFunctionRaw(libraryPath, functionName));
        }

        [[nodiscard]] void* GetLibraryHandle(const std::string& libraryPath) const;

      private:
        void* libraryCoreInstance;
    };
} // namespace Ers
