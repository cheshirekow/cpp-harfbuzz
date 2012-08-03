find_package( Harfbuzz )
find_package( CppFreetype )
find_package( Freetype2 )
find_package( SigC++ )
 
if( (Harfbuzz_FOUND) 
    AND (CppFreetype_FOUND)
    AND (Freetype2_FOUND) 
    AND (SigC++_FOUND) )
                               
include_directories(
    ${Harfbuzz_INCLUDE_DIRS}
    ${CppFreetype_INCLUDE_DIRS}
    ${SigC++_INCLUDE_DIRS}
)
                                                                    
add_library( ${CMAKE_PROJECT_NAME}
                shape.cpp
                Blob.cpp
                Buffer.cpp
                Direction.cpp
                Face.cpp
                Feature.cpp
                Font.cpp
                GlyphInfo.cpp
                GlyphExtents.cpp
                GlyphPosition.cpp
                Handle.cpp
                Language.cpp
                Script.cpp
                Tag.cpp
                UserData.cpp  )
 
INSTALL( TARGETS ${CMAKE_PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

else()
    set( MISSING )

    if( NOT (Harfbuzz_FOUND) )
        set( MISSING ${MISSING} harfbuzz )
    endif()
    
    if( NOT (CppFreetype_FOUND) )
        set( MISSING ${MISSING} cppfreetype )
    endif()
    
    if( NOT (Freetype2_FOUND) )
        set( MISSING ${MISSING} freetype2 )
    endif()
    
    if( NOT (SigC++_FOUND) )
        set( MISSING ${MISSING} sigc++ )
    endif()
    
    message( WARNING
            "The following packages are missing: ${MISSING}"
            "disabling build of cppharfbuzz library "
            "you may still build the doc target "  )
endif()