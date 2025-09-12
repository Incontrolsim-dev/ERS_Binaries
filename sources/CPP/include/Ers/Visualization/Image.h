#pragma once

namespace Ers::Visualization
{
    struct Image
    {
      public:
        Image(void* coreInstance);
        Image()                        = delete;
        Image(const Image&)            = delete;
        Image(Image&&)                 = delete;
        Image& operator=(const Image&) = delete;
        Image& operator=(Image&&)      = delete;
        ~Image()                       = default;

        void* Data();
        const void* const Data() const;

      private:
        void* coreInstance;
    };
} // namespace Ers::Visualization
