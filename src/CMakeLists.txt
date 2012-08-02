find_package(Harfbuzz )
 
if( Harfbuzz_FOUND )
                               
include_directories(
    ${Harfbuzz_INCLUDE_DIRS}
)
                                                                    
add_library( ${CMAKE_PROJECT_NAME}
                Blob.cpp
                Direction.cpp
                #Font.cpp
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
    message( WARNING 
        "harfbuzz was not found, disabling build of cppharfbuzz library"
        "you may still build the doc target"  )  
endif()