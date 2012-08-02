find_package(Harfbuzz )
 
if( Harfbuzz_FOUND )
                               
include_directories(
    ${Harfbuzz_INCLUDE_DIRS}
)
                                                                    
else()
    message( WARNING 
        "harfbuzz was not found, disabling build of cppharfbuzz tutorial"
        "you may still build the doc target"  )  
endif()