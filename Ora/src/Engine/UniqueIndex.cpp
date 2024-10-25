#include "Engine/UniqueIndex.hpp"

namespace ora {

Index get_unique() {
    static Index s_current(0);
    ++s_current;
    return s_current;
}

}