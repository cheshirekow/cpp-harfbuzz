find_package(Harfbuzz )
find_package(CppFreetype )
 
if( (Harfbuzz_FOUND) AND (CppFreetype_FOUND) )
                               
include_directories(
    ${Harfbuzz_INCLUDE_DIRS}
)
                                                                    
add_library( ${CMAKE_PROJECT_NAME}
                Blob.cpp
                Direction.cpp
                #Font.cpp
                Handle.cpp
                Language.cpp
                #Object.cpp
                Script.cpp
                Tag.cpp
                UserData.cpp  )
 
INSTALL( TARGETS ${CMAKE_PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

else()
    if( NOT (Harfbuzz_FOUND) )
        message( WARNING 
            "harfbuzz was not found, disabling build of cppharfbuzz library"
            "you may still build the doc target"  )  
    endif()
    
    if( NOT( CppFreetype_FOUND ) )
        message( WARNING 
            "cppfreetype was not found, disabling build of cppharfbuzz library"
            "you may still build the doc target"  )
    endif()
endif()