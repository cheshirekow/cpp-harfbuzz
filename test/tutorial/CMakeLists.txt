find_package(Harfbuzz )
find_package(Tclap)
 
if( (Harfbuzz_FOUND) AND (Tclap_FOUND) )
                               
    include_directories(
        ${Harfbuzz_INCLUDE_DIRS}
        ${Tclap_INCLUDE_DIR}
    )
    
    add_executable( hb_view 
        main.cpp
        CommandLine.cpp )
    
    target_link_libraries( hb_view ${Harfbuzz_LIBRARIES} )
                                                                    
else()
    set( MISSING )
    if( NOT (Harfbuzz_FOUND) )
        set( MISSING ${MISSING} " harfbuzz " )
    endif()
    
    if( NOT (Tclap_FOUND) )
        set( MISSING ${MISSING} " tclap " )
    endif()

    message( WARNING 
        "harfbuzz was not found, disabling build of cppharfbuzz tutorial"
        "you may still build the doc target"  )  
endif()