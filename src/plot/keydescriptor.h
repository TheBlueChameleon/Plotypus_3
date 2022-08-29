#ifndef KEYDESCRIPTOR_H
#define KEYDESCRIPTOR_H

namespace Plotypus
{
    class KeyDescriptor
    {
        private:
            bool on;
            // enums for position: marginPos (4), xPos (3), yPos(3), inOut(2)
            // enums for element stacking: horizontal/vertical
            // enums for justification: left/right

            bool opaque = true;
            // optional string forecolor
            bool inverseOrder;
            bool reverseSymbol;

            // optional string title

            bool boxed;
            // optional int LineStyle
            // optional int maxCols, maxRows

        public:
            KeyDescriptor();


            // void write(std::ostream& hFile);
    };
}

#endif // KEYDESCRIPTOR_H
