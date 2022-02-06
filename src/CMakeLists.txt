add_library(myvector vector.cpp ../include/myvector/vector.hpp)
target_include_directories(myvector PUBLIC ../include)
target_compile_features(myvector PUBLIC cxx_std_17)