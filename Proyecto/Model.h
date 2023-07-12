//
// Created by Jose Antonio on 8/10/21.
//

#ifndef PRACTICA5_PAG_MODEL_H
#define PRACTICA5_PAG_MODEL_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace AG {
    //Enum con los tipos de modelos
    enum class TIPO_MODELO{
        LINE,
        POINT,
        POLYGON,
        WIREFRAME,
        PLAIN,
        SLINE
    };

    struct TypeColor{
        float R,G,B;
        TypeColor (): R(0), G(0), B(0){}
        bool operator==(const TypeColor & color){ return (this->R == color.R && this->G == color.G && this->B == color.B);}
        TypeColor (float RR, float  GG, float BB): R(RR), G(GG), B(BB){}
        TypeColor (glm::vec4 col): R(col[0]), G(col[1]), B(col[2]) {}
        glm::vec4 getVec4 (){ return glm::vec4(R,G,B,1.0);}
    };

    class Model {
        protected:
            TIPO_MODELO modelo;//Modelo
            GLuint idVAO = 0; // Identificador del vertex array object
            GLuint idVBO = 0; // Identificador del vertex buffer object
            GLuint idIBO = 0; // Identificador del index buffer object
            GLuint idVBOEnla[2];//Se crea un id del buffer object para los id de ambos vectores
            glm::mat4 matrizModelado = glm::mat4(1.f);
            TypeColor color = TypeColor();
            std::vector<glm::vec3> vertices;
            std::vector<GLuint> indices;
            void setColor(TypeColor t);
            void buildVAO();

        public:
            Model(TIPO_MODELO modelo);
            virtual ~Model();
            Model(const Model& orig);
            void activarProgram();
            TIPO_MODELO getTipoModelo();
            GLuint getIndexNumber();
            TypeColor getColor();
            glm::mat4 getMatrizModelado();
            void setMatrizModelado(glm::mat4 matriz);
            void setTypeModel(TIPO_MODELO type);

    };
}
#endif //PRACTICA5_PAG_MODEL_H
