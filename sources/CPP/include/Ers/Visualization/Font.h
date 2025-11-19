#pragma once

namespace Ers
{
    struct Font
    {
      public:
        Font(void* coreInstance);
        Font()                       = delete;
        Font(const Font&)            = delete;
        Font(Font&&)                 = delete;
        Font& operator=(const Font&) = delete;
        Font& operator=(Font&&)      = delete;
        ~Font()                      = default;

        void* Data();
        const void* const Data() const;

      private:
        void* coreInstance;
    };
} // namespace Ers
