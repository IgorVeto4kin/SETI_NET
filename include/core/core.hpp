#pragma once

namespace core {

class Core {
public:
    Core();
    void test();
    int publicCoreMethod();
    void fuzzMeCore(const char* input) const;
};

} // namespace core