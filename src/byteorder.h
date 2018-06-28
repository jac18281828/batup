#pragma once

#include <type_traits>

namespace batup {

    /**
     * @return bool - True if this machine is big endian
     */
    inline bool is_big_endian() {
        // requires c++ 20: std::endian::native == std::endian::little
        return __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__;
    };
    
    /**
     * given a parameter encoded as a big endian integer
     * type convert to the native endian format
     *
     * @param t
     */
    template <typename T>
    inline T native_endian(const T t) {
        if(!is_big_endian()) {
            T result = (T)0;
            for(unsigned int i=0; i<sizeof(T); i++) {
                T bytefield = (t >> (sizeof(T) - i - 1)*8)&0xFFu;
                result |= bytefield << i*8;
            }
            return result;
        } else {
            return t;
        }
    };

    /**
     * given a parameter encoded as a native integer
     * return a big endian integer
     */
    template <typename T>
    inline T big_endian(const T t) {
        return native_endian<T>(t);
    };
    
}
