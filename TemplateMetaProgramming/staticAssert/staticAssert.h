#ifndef STATICASSERT_HXX
#define STATICASSERT_HXX
/*
 Lifted direct from:
 Modern C++ Design: Generic Programming and Design Patterns Applied
 Section 2.1
 by Andrei Alexandrescu
*/
//namespace ww
//{
    template<bool> class compile_time_check
    {
    public:
        compile_time_check(...) {}
    };

    template<> class compile_time_check<false>
    {
    };
//}

    /*
    Similiar to assert, StaticAssert is only in operation when NDEBUG is not
    defined. It will test its first argument at compile time and on failure
    report the error message of the second argument, which must be a valid c++
    classname. i.e. no spaces, punctuation or reserved keywords.
    */
#ifndef NDEBUG
#   define StaticAssert(test, errormsg)                         \
    do {                                                        \
        struct ERROR_##errormsg {};                             \
        typedef ww::compile_time_check< (test) != 0 > tmplimpl; \
        tmplimpl aTemp = tmplimpl(ERROR_##errormsg());          \
        sizeof(aTemp);                                          \
    } while (0)
#else
#   define StaticAssert(test, errormsg)                         \
    do {} while (0)
#endif

#endif