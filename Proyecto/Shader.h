//
// Created by Jose Antonio on 1/10/21.
//

#ifndef PRACTICA4_PAG_SHADER_H
#define PRACTICA4_PAG_SHADER_H

#include <QOpenGLFunctions>
#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>

namespace AG {
    class Shader {
        private:
            //Identificadores de la geometria y los shaders
            GLuint idVS = 0; // Identificador del vertex shader
            GLuint idFS = 0; // Identificador del fragment shader
            GLuint idSP = 0; // Identificador del shader program

            std::string miVertexShader;
            std::string miFragmentShader;

            std::string ficheroVS;
            std::string ficheroFS;


            void creaShaderProgram();
            void cargaShaders(std::string vsFile, std::string fsFile);
            void errorShaders();
            void errorCompilacionShader(GLuint idShader);

        public:
            Shader(std::string vsFile, std::string fsFile);
            virtual ~Shader();
            Shader(const Shader& orig);
            void activarShader();
            std::string getFicheroVS();
            std::string getFicheroFS();
            GLuint getSP();


    };
}

#endif //PRACTICA4_PAG_SHADER_H
