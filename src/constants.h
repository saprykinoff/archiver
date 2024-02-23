#pragma once
const int CHAR_SIZE = 8;
const int MY_SYMBOL_SIZE = 9;
const int FILENAME_END = 256;
const int ONE_MORE_FILE = 257;
const int ARCHIVE_END = 258;
const int MAX_CODE = 258;
const bool DEBUG_MODE = false;

#define DEBUG(x)      \
    if (DEBUG_MODE) { \
        x             \
    }
#define DEBUG_PRINT(x)  \
    if (DEBUG_MODE) {   \
        std::cout << x; \
    }
#define ASSERT_FILE_NOT_ENDED(x)                                                   \
    if (!(x)) {                                                                    \
        std::cerr << "File overflowed in " << __FILE__ << ":" << __LINE__ << '\n'; \
        exit(321);                                                                 \
    }
