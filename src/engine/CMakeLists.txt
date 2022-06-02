cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(engine)

set(SOURCES parserXML/tinyxml2.cpp parserXML/tinyxml2.h parserXML/XMLDocReader.cpp parserXML/XMLDocReader.h parserXML/Transformacao/Transformacao.h 
	parserXML/Transformacao/Escala.cpp parserXML/Transformacao/Escala.h parserXML/Transformacao/TranslacaoEstatica.cpp parserXML/Transformacao/TranslacaoEstatica.h parserXML/Transformacao/RotacaoEstatica.cpp parserXML/Transformacao/RotacaoEstatica.h
	parserXML/Transformacao/TranslacaoTemporizada.cpp parserXML/Transformacao/TranslacaoTemporizada.h parserXML/Transformacao/RotacaoTemporizada.cpp parserXML/Transformacao/RotacaoTemporizada.h 
	parserXML/Camara.cpp parserXML/Camara.h parserXML/Grupo.cpp parserXML/Grupo.h
	parserXML/Luz/Luz.h parserXML/Luz/LuzPosicional.h parserXML/Luz/LuzDirecional.h parserXML/Luz/LuzSpot.h parserXML/Luz/LuzPosicional.cpp parserXML/Luz/LuzDirecional.cpp parserXML/Luz/LuzSpot.cpp
	parserXML/Figura.h parserXML/Figura.cpp parserXML/Cor.h parserXML/Cor.cpp)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (NOT APPLE)
	if (WIN32)
		set(TOOLKITS_FOLDER "" CACHE PATH "Path to toolkits folder")
		include_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut
			${TOOLKITS_FOLDER}/devil)
		link_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut
			${TOOLKITS_FOLDER}/devil)
	else(WIN32)
		find_package(GLEW REQUIRED)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif(WIN32)
endif(NOT APPLE)

if (NOT WIN32)
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	find_package(DevIL REQUIRED)
	link_libraries(${IL_LIBRARIES} )
	include_directories(ยง{IL_INCLUDE_DIR})
endif(NOT WIN32)	
	
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})


if (WIN32)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glut32 glew32 DevIL)
	file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY ${TOOLKITS_FOLDER}/devil/DevIL.dll DESTINATION ${CMAKE_BINARY_DIR})

else(WIN32)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif (WIN32)









