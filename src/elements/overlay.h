#ifndef OVERLAY_H
#define OVERLAY_H

namespace Plotypus
{
    class Overlay
    {
        private:
            size_t tag = 0;

        public:
            Overlay();

            virtual void writeTxt   () const = 0;
            virtual void writeScript() const = 0;
    };
}

#endif // OVERLAY_H
