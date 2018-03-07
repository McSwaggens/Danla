cmake_minimum_required(VERSION 3.9)
project(Danla)

set(CMAKE_CXX_STANDARD 11)

add_executable(Danla Danla.cpp Danla.h Buffer.h Buffer.cpp Handle.cpp Handle.h Main.cpp Material.cpp Material.h Object.cpp
        Object.h OpenGL.cpp OpenGL.h Shader.cpp Shader.h ShaderPreProcessor.cpp ShaderPreProcessor.h Standard.h Uniform.cpp
        Uniform.h Vector2.cpp Window.cpp AttributeBuffer.cpp AttributeBatch.cpp Time.h Time.cpp SystemTime.h
        SystemTime.cpp FrameBuffer.cpp Texture.cpp Texture.h RenderBufferTexture.cpp RenderBufferTexture.h UFloat.cpp
        UFloat.h Effect.cpp Effect.h PostProcessingStack.cpp PostProcessingStack.h Shapes.cpp Shapes.h Color.cpp Color.h
        Math.h PostProcessing.h PostProcessing.cpp TextureUnit.cpp TextureUnit.h Input.h Input.cpp Keys.h MouseKeys.h
        IVector2.h IVector2.cpp SafeList.cpp SafeList.h Entity.cpp Entity.h Actor.cpp Actor.h World.cpp World.h
        RenderGroup.cpp RenderGroup.h TestActor.cpp TestActor.h Transform.h Transform.cpp Vector3.h Vector3.cpp Camera.cpp Camera.h Matrix4.h Matrix4.cpp Matrix2D.cpp Matrix2D.h Laser.cpp Laser.h)

message(${CMAKE_BUILD_TYPE})

#set(CMAKE_CXX_FLAGS "-Ofast")

target_link_libraries(Danla glfw3 glew32 SOIL opengl32 gdi32)


