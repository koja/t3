#ifndef exception_intf_4543541514
#define exception_intf_4543541514

/** interface for all custom exceptions */
struct exception_intf {
    virtual const char* what() const = 0;
    exception_intf() { }
    exception_intf(const exception_intf&) = default;
    virtual ~exception_intf() = default;
};

#endif
