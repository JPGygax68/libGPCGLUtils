#pragma once

#include <array>
#include <gpc/gl/wrappers.hpp>
#include "utils.hpp" // TODO: replace with future type definition header


namespace gpc {

    namespace gl {
    
#ifdef _DEBUG
        inline void checkUniformLocation(const char *name, GLuint location) 
        {
            GLint program = 0;
            EXEC_GL(glGetIntegerv, GL_CURRENT_PROGRAM, &program);
            assert(program > 0);
            GLuint loc = CALL_GL(glGetUniformLocation, program, name);
            assert(loc == location);
        }
#else
        inline void checkUniformLocation(const char * /*name*/, GLuint /*index*/) {}
#endif

        // TODO: use perfect forwarding to call the normal setUniform() variants
        // from the name-checking ones ?
        
        // Simple integers ------------------------------------------

        inline void 
        setUniform(GLuint index, GLint value)
        {
            GL(Uniform1i, index, value);
        }

        inline void
        setUniform(GLuint index, GLuint value)
        {
            setUniform(index, GLint(value));
        }

        // Standard homogeneous 3D vector (x, y, z, w) --------------

        inline void 
        setUniform(GLuint index, const FloatVec4 &values)
        {
            GL(Uniform4fv, index, 1, values);
        }

        inline void 
        setUniform(GLuint index, const std::array<GLfloat, 4> &values)
        {
            GL(Uniform4fv, index, 1, &values[0]);
        }

        // Pixel-aligned (integer) coordinates ----------------------

        inline void
        setUniform(GLuint index, const IntVec2 &values)
        {
            GL(Uniform2iv, index, 1, values);
        }

        // Somewhat exotic: vector of 4 integers --------------------

        inline void
        setUniform(GLuint index, const IntVec4 &values)
        {
            GL(Uniform4iv, index, 1, values);
        }

        // 3x3 matrix (for 2D transforms) ---------------------------

        inline void
        setUniform(GLuint index, const Matrix3 &values)
        {
            GL(UniformMatrix3fv, index, 1, GL_FALSE, &values[0][0]);
        }

        inline void
        setUniformMatrix2(const char *name, GLuint index, const GLfloat *values)
        {
            checkUniformLocation(name, index);
            GL(UniformMatrix2fv, index, 1, GL_FALSE, values);
        }

        inline void
        setUniformMatrix3(const char *name, GLuint index, const GLfloat *values)
        {
            checkUniformLocation(name, index);
            GL(UniformMatrix3fv, index, 1, GL_FALSE, values);
        }

        inline void
        setUniformMatrix3(GLuint index, const GLfloat *values)
        {
            GL(UniformMatrix3fv, index, 1, GL_FALSE, values);
        }

        // Classic 4x4 matrix ---------------------------------------

        inline void
        setUniform(GLuint index, const Matrix4 &values)
        {
            GL(UniformMatrix4fv, index, 1, GL_FALSE, &values[0][0]);
        }

        inline void
        setUniformMatrix4(GLuint index, const GLfloat *values)
        {
            GL(UniformMatrix4fv, index, 1, GL_FALSE, values);
        }

        // Name-checking variants -----------------------------------

        template<typename... Args> inline void 
        setUniform(const char *name, GLuint index, Args&&... args)
        {
            checkUniformLocation(name, index);
            setUniform(index, std::forward<Args>(args)...);
        }

        template<typename... Args> inline void 
        setUniformMatrix3(const char *name, GLuint index, Args&&... args)
        {
            checkUniformLocation(name, index);
            setUniformMatrix3(index, std::forward<Args>(args)...);
        }

        template<typename... Args> inline void 
        setUniformMatrix4(const char *name, GLuint index, Args&&... args)
        {
            checkUniformLocation(name, index);
            setUniformMatrix4(index, std::forward<Args>(args)...);
        }

    } // ns gl

} // ns gpc