# NB: Append here when adding sources
set(fEEGA_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Analysis/fft.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Communication/TCPclient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Communication/serialCom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Communication/ring_buffer.cpp
  PARENT_SCOPE
)
