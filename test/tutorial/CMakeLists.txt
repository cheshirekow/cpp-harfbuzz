find_package(Harfbuzz )
find_package(CppFreetype)
find_package(Freetype2)
find_package(SigC++)
find_package(Tclap)
find_package(Cairomm)
 
if( (Harfbuzz_FOUND) 
        AND (Tclap_FOUND) 
        AND (CppFreetype_FOUND)
        AND (Freetype2_FOUND)
        AND (SigC++_FOUND)
        AND (Cairomm_FOUND) )
                               
    include_directories(
        ${Harfbuzz_INCLUDE_DIRS}
        ${CppFreetype_INCLUDE_DIRS}
        ${SigC++_INCLUDE_DIRS}
        ${Tclap_INCLUDE_DIR}
        ${Cairomm_INCLUDE_DIRS}
    )
    
    add_executable( hb_view 
        main.cpp
        CairoOutput.cpp
        CommandLine.cpp
        FontReader.cpp
        InputReader.cpp
        Shaper.cpp
         )
    
    target_link_libraries( hb_view 
        ${CMAKE_PROJECT_NAME}
        ${Harfbuzz_LIBRARIES}
        ${CppFreetype_LIBRARIES}
        ${SigC++_LIBRARIES}
        ${Freetype2_LIBRARIES}
        ${Cairomm_LIBRARIES} )
                                                                    
else() 
    set( MISSING )
    if( NOT (Harfbuzz_FOUND) )
        set( MISSING ${MISSING} " harfbuzz " )
    endif()
    
    if( NOT (Tclap_FOUND) )
        set( MISSING ${MISSING} " tclap " )
    endif()
    
     if( NOT (CppFreetype_FOUND) )
        set( MISSING ${MISSING} " cppfreetype " )
    endif()
    
     if( NOT (Freetype2_FOUND) )
        set( MISSING ${MISSING} " freetype2 " )
    endif()
    
    if( NOT (Sig_C++FOUND) )
        set( MISSING ${MISSING} " sigc++ " )
    endif()
    
    if( NOT (Cairomm_FOUND ) )
        set( MISSING ${MISSING} " cairomm " )
    endif()

    message( WARNING 
        "harfbuzz was not found, disabling build of cppharfbuzz tutorial"
        "you may still build the doc target"  )  
endif()