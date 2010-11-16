add_definitions(${QT_DEFINITIONS})
include(${QT_USE_FILE})




include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_CURRENT_BINARY_DIR}
   ${Qt4_INCLUDES}
   ${QT_INCLUDES}
)

set(qwebyast_SRCS
	main.cpp
	yast.cpp
	yast.h
	constants.h
)

qt4_automoc(${qwebyast_SRCS})


set (BIN_INSTALL_DIR "/usr/bin" )

add_executable(qwebyast_bin ${qwebyast_SRCS})
set_target_properties( qwebyast_bin PROPERTIES OUTPUT_NAME qwebyast )
target_link_libraries( qwebyast_bin ${QT_LIBRARIES}  )

install(TARGETS qwebyast_bin DESTINATION ${BIN_INSTALL_DIR})


install(FILES qwebyast.desktop DESTINATION /usr/share/applications )
install(FILES qwebyast-autostart.desktop DESTINATION "/etc/xdg/autostart")

install( PROGRAMS webyast.sh DESTINATION /usr/bin)

