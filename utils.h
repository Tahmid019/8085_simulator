#pragma once
#include <iostream>

template<typename T, typename V>
void debug(T mn, V reg) {
    std::cerr << mn << " executed. [" << reg << "]" << std::endl;
}
