#pragma once

namespace Ers
{
    struct Font
    {
      public:
        Font(void* corePtr);
        Font()                       = delete;
        Font(const Font&)            = delete;
        Font(Font&&)                 = delete;
        Font& operator=(const Font&) = delete;
        Font& operator=(Font&&)      = delete;
        ~Font()                      = default;

        void* CorePtr();
        const void* const CorePtr() const;

      private:
        void* corePtr;
    };
} // namespace Ers
