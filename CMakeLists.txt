cmake_minimum_required(VERSION 3.9)
project(Danla)

set(CMAKE_CXX_STANDARD 11)

add_executable(Danla Danla.cpp Danla.h Buffer.h Buffer.cpp Handle.cpp Handle.h Main.cpp Material.cpp Material.h Object.cpp
        Object.h OpenGL.cpp OpenGL.h Shader.cpp Shader.h ShaderPreProcessor.cpp ShaderPreProcessor.h Standard.h Uniform.cpp
        Uniform.h Vector.h Vector2.cpp Window.cpp AttributeBuffer.cpp AttributeBatch.cpp Time.h Time.cpp ChronoHelper.h ChronoHelper.cpp FrameBuffer.cpp Texture.cpp Texture.h RenderBufferTexture.cpp RenderBufferTexture.h UFloat.cpp UFloat.h Effect.cpp Effect.h PostProcessingStack.cpp PostProcessingStack.h Shapes.cpp Shapes.h)


target_link_libraries(Danla glfw3 glew32 opengl32 gdi32 kernel32)


