#add_custom_target(
#        test_archiver
#        WORKING_DIRECTORY
#        DEPENDS archiver
#        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/test.py ${CMAKE_BINARY_DIR}/archiver ${CMAKE_CURRENT_SOURCE_DIR}/data
#)

add_catch(my_test_cpp my_test.cpp)
add_catch(unit_testing
        ../src/ArgParser.cpp ../src/common.cpp ../src/decoder.cpp ../src/encoder.cpp ../src/MySymbol.cpp ../src/Reader.cpp ../src/TrieBase.cpp ../src/Tries.cpp ../src/Writer.cpp
        unit_tests/bits_io.cpp
        unit_tests/queue_tests.cpp
        unit_tests/archiver.cpp
        unit_tests/arg_parser.cpp
        )