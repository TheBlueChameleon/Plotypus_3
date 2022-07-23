#ifndef REPORT_TXX
#define REPORT_TXX

template<class T>
T& Plotypus::Report::sheetAs(const size_t i)
{
    return dynamic_cast<T&>(sheet(i));
}

#endif // REPORT_TXX
