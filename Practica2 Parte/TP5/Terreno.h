template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int str_to_int(string s)
{

    string str = s;
    istringstream buffer(str);
    int value;
    buffer >> value;
    return value;
}


typedef struct // Definicion de un punto del terreno
{
    GLfloat s, t; // Coordenadas de texturas dividir entre 101
    GLfloat nx, ny, nz; // Coordenadas de la normal   tengo que calcular
    GLfloat x, y, z; // posición del vértice    coordenadas que voy a leer
} PuntoTerreno;


class Terreno
{
    public :
        Terreno(){}
        void load(string filename) ; // carga de un archivo de modelo digital de terreno
        void display(); // Visualizacion del terreno
        void computeNormals(); // calcula las normales de cada vertice
        void display_dots();
        void display_no_texture();
        void display_no_texture_normal();
    private:
        int nb_pt_x, nb_pt_z; // quantidad de punto en X y Z
        float dist_x, dist_z; // distancia entre dos puntos segun X y    Z
        int coord_x, coord_y;//coordenada lambert
        //PuntoTerreno *lista_puntos; // Tabla que contiene los puntos del terreno
        GLfloat Modulo(GLfloat N[]);
        GLvoid Normaliza(GLfloat []);
        vector<GLuint> lista_indices;
        vector<GLfloat> lista_normales;
        vector<PuntoTerreno> lista_puntos;
            //	void calcularNormal(GLfloat p1x, GLfloat p1y, GLfloat p1z, GLfloat p2x, GLfloat p2y, GLfloat p2z,
            //GLfloat p3x, GLfloat p3y, GLfloat p3z, GLfloat &nx,GLfloat &ny,GLfloat &nz);
          //  void calcularNormal();


};

void Terreno::load(string filename){

    std::ifstream input(filename);
    string input_text;
    int n_line=0;

    //contadores de la malla
    int cont = 0;
    int cont_x = -2525,cont_z = 2525;
    float cont_s = 0.0, cont_t = 0.0;
    int ii=0;
    static const char white_space[] = " ";

    while (std::getline(input, input_text)){

        if(n_line==0)//averiguar coordenada en x ,en y y el numero de puntos 
        {
            n_line=1;
            int position = input_text.find_first_not_of(white_space, 0);

            if ((position == std::string::npos))
            {
                continue;
            }
            vector<string> valores = split(input_text,'\t');
           
            /* for(int i=0;i<valores.size();i++)
             {
                cout<<valores[i]<<endl;
             }*/

            coord_x=str_to_int(valores[5]);
            coord_y=str_to_int(valores[6]);
            dist_x=str_to_int(valores[7]);//distancia en x
            dist_z=str_to_int(valores[8]);//distancia en z
            nb_pt_x=str_to_int(valores[9]);//cantidad de puntos 101 x
            nb_pt_z=str_to_int(valores[10]);//cantidad de punteros 101 zi
            //lista_puntos = new PuntoTerreno[nb_pt_x*nb_pt_z];
        }
        else
        {
            istringstream iss(input_text);
            string word;

            while(iss>>word)
            {
//                cout<<word<<" ";
                //              lista_indices[ii]=ii;
                cout<<word<<endl;
                if(cont==nb_pt_x)//sumo altura
                {
                    cont_z += dist_z;
                    cont_t += 0.0099;
                    cont_s = 0.0;
                    cont_x = -2525;
                    cont = 0;

                }
                PuntoTerreno point;

                point.x = cont_x;
                point.y = str_to_int(word)*2;
                point.z = cont_z;

                point.s = cont_s;
                point.t = cont_t;

                //lista_puntos[ii]=point;
                lista_puntos.push_back(point);
                cont+=1;
                cont_x+=dist_x;//distancia x
                cont_s+=1.0f/101.0f;
                ii++;

            }
        }
        cout<<endl;
    }
    input.close();
    int r=0;
    lista_indices.reserve(100*100*6);
    for(int i=0; i<nb_pt_z-1; i++)
    {
        //formando triangulos
        for(int j=0; j<nb_pt_x-1; j++)
        {
            //primer triangulo
            lista_indices[r]=(i+1)*nb_pt_z+(j+1);    
            r++;
            lista_indices[r]=(i+1)*nb_pt_z+j;
            r++;
            lista_indices[r]=i*nb_pt_z+j;
            r++;
           /* lista_indices[r]=(i+1)*nb_pt_z+j;
            r++;
            lista_indices[r]=(i+1)*nb_pt_z+(j+1);
            r++;*/
            //segundo triangulo
            lista_indices[r]=i*nb_pt_z+(j+1);
            r++;
            lista_indices[r]=(i+1)*nb_pt_z+(j+1);
            r++;
            lista_indices[r]=i*nb_pt_z+j;
            r++;
           /* lista_indices[r]=(i+1)*nb_pt_z+(j+1);
            r++;
            lista_indices[r]=i*nb_pt_z+(j+1);
            r++;*/
        }
    }
    cout<<"Imprimiendo los puntos"<<endl;
    for(int i=0;i<100;i++)
    {
       cout<<"("<<lista_puntos[i].x <<" , "<< lista_puntos[i].y <<","<<lista_puntos[i].z<<")"<<endl;
    }
}

void Terreno::display()
{
//    GLfloat MatAmbient[4] = {0.0f, 0.5f, 0.0f, 1.0f};
//    GLfloat MatDiffuse[4] = {0.0f, 0.8f, 0.0f, 1.0f};
//    GLfloat MatSpecular[4] = {0.2f,0.2f, 0.2f, 1.0f};
//    GLfloat MatShininess[] = { 5.0F };
//    glMaterialfv(GL_FRONT, GL_AMBIENT , MatAmbient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE , MatDiffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(PuntoTerreno),&lista_puntos[0].s);
    glDrawElements(GL_TRIANGLES,100*100*6, GL_UNSIGNED_INT,(void*)&lista_indices[0]);
}
void Terreno::display_dots()
{
	glBegin(GL_POINTS);
	   // glColor3f(1.5f,0.0f,0.0f);
	    	
	    for(int i=0;i<lista_puntos.size();i++)
	    	glVertex3f(lista_puntos[i].x, lista_puntos[i].y,lista_puntos[i].z);
	glEnd();
}
void Terreno::display_no_texture()
{
    glInterleavedArrays(GL_V3F, sizeof(PuntoTerreno),&lista_puntos[0].x);
    glDrawElements(GL_TRIANGLES,100*100*6, GL_UNSIGNED_INT,(void*)&lista_indices[0]);
}
void Terreno::display_no_texture_normal()
{
    glInterleavedArrays(GL_N3F_V3F, sizeof(PuntoTerreno),&lista_puntos[0].nx);
    glDrawElements(GL_TRIANGLES,100*100*6, GL_UNSIGNED_INT,(void*)&lista_indices[0]);
}
GLfloat Terreno::Modulo(GLfloat N[])
{
    GLfloat len;
    len = N[0]*N[0]+ N[1]*N[1] + N[2]*N[2];
    return (sqrt(len));
}

GLvoid Terreno::Normaliza(GLfloat N[])
{
    GLfloat len;
    len = Modulo(N);
    //i//len = 1.0/len;
    N[0] /= len;
    N[1] /= len;
    N[2] /= len;
}

void Terreno::computeNormals()
{
    GLfloat V1x;
    GLfloat V1y;
    GLfloat V1z;

    GLfloat V2x;
    GLfloat V2y;
    GLfloat V2z;
    int cnt=0;
    for(int i=0;i<nb_pt_z;i++)
    {
        for(int j=0;j<nb_pt_x;j++)
        {
            int posicion=i*nb_pt_z+j;
            if(j+1<nb_pt_x && i+1<nb_pt_z)
            {
                V1x=lista_puntos[posicion+1].x-lista_puntos[posicion].x;
                V1y=lista_puntos[posicion+1].y-lista_puntos[posicion].y;
                V1z=lista_puntos[posicion+1].z-lista_puntos[posicion].z;

                V2x=lista_puntos[posicion+nb_pt_x+1].x-lista_puntos[posicion].x;
                V2y=lista_puntos[posicion+nb_pt_x+1].y-lista_puntos[posicion].y;
                V2z=lista_puntos[posicion+nb_pt_x+1].z-lista_puntos[posicion].z;

                lista_puntos[posicion].nx=V1y*V2z-V1z*V2y;
                lista_puntos[posicion].ny=V1z*V2x-V1x*V2z;
                lista_puntos[posicion].nz=V1x*V2y-V1y*V2x;

                V1x=lista_puntos[posicion+nb_pt_x].x-lista_puntos[posicion].x;
                V1y=lista_puntos[posicion+nb_pt_x].y-lista_puntos[posicion].y;
                V1z=lista_puntos[posicion+nb_pt_x].z-lista_puntos[posicion].z;

                V2x=lista_puntos[posicion+nb_pt_x+1].x-lista_puntos[posicion].x;
                V2y=lista_puntos[posicion+nb_pt_x+1].y-lista_puntos[posicion].y;
                V2z=lista_puntos[posicion+nb_pt_x+1].z-lista_puntos[posicion].z;

                lista_puntos[posicion].nx=V1y*V2z-V1z*V2y;
                lista_puntos[posicion].ny=V1z*V2x-V1x*V2z;
                lista_puntos[posicion].nz=V1x*V2y-V1y*V2x;
                cnt+=2;
            }
            if(j-1>=0 && i+1<nb_pt_z)
            {
                V1x=lista_puntos[posicion-1].x-lista_puntos[posicion].x;
                V1y=lista_puntos[posicion-1].y-lista_puntos[posicion].y;
                V1z=lista_puntos[posicion-1].z-lista_puntos[posicion].z;

                V2x=lista_puntos[posicion+nb_pt_x].x-lista_puntos[posicion].x;
                V2y=lista_puntos[posicion+nb_pt_x].y-lista_puntos[posicion].y;
                V2z=lista_puntos[posicion+nb_pt_x].z-lista_puntos[posicion].z;
                lista_puntos[posicion].nx=V1y*V2z-V1z*V2y;
                lista_puntos[posicion].ny=V1z*V2x-V1x*V2z;
                lista_puntos[posicion].nz=V1x*V2y-V1y*V2x;
                cnt+=1;
            }
            if(j-1>=0 && i-1>=0)
            {
                V1x=lista_puntos[posicion-1].x-lista_puntos[posicion].x;
                V1y=lista_puntos[posicion-1].y-lista_puntos[posicion].y;
                V1z=lista_puntos[posicion-1].z-lista_puntos[posicion].z;

                V2x=lista_puntos[posicion-nb_pt_x-1].x-lista_puntos[posicion].x;
                V2y=lista_puntos[posicion-nb_pt_x-1].y-lista_puntos[posicion].y;
                V2z=lista_puntos[posicion-nb_pt_x-1].z-lista_puntos[posicion].z;
                lista_puntos[posicion].nx=V1y*V2z-V1z*V2y;
                lista_puntos[posicion].ny=V1z*V2x-V1x*V2z;
                lista_puntos[posicion].nz=V1x*V2y-V1y*V2x;

                V1x=lista_puntos[posicion-nb_pt_x].x-lista_puntos[posicion].x;
                V1y=lista_puntos[posicion-nb_pt_x].y-lista_puntos[posicion].y;
                V1z=lista_puntos[posicion-nb_pt_x].z-lista_puntos[posicion].z;

                V2x=lista_puntos[posicion-nb_pt_x-1].x-lista_puntos[posicion].x;
                V2y=lista_puntos[posicion-nb_pt_x-1].y-lista_puntos[posicion].y;
                V2z=lista_puntos[posicion-nb_pt_x-1].z-lista_puntos[posicion].z;
                lista_puntos[posicion].nx=V1y*V2z-V1z*V2y;
                lista_puntos[posicion].ny=V1z*V2x-V1x*V2z;
                lista_puntos[posicion].nz=V1x*V2y-V1y*V2x;
                cnt+=2;
            }
            if(j+1<nb_pt_x && i-1>=0)
            {
                V1x=lista_puntos[posicion+1].x-lista_puntos[posicion].x;
                V1y=lista_puntos[posicion+1].y-lista_puntos[posicion].y;
                V1z=lista_puntos[posicion+1].z-lista_puntos[posicion].z;

                V2x=lista_puntos[posicion-nb_pt_x].x-lista_puntos[posicion].x;
                V2y=lista_puntos[posicion-nb_pt_x].y-lista_puntos[posicion].y;
                V2z=lista_puntos[posicion-nb_pt_x].z-lista_puntos[posicion].z;
                lista_puntos[posicion].nx=V1y*V2z-V1z*V2y;
                lista_puntos[posicion].ny=V1z*V2x-V1x*V2z;
                lista_puntos[posicion].nz=V1x*V2y-V1y*V2x;
                cnt+=1;
            }
            lista_puntos[posicion].nx/=cnt;
            lista_puntos[posicion].ny/=cnt;
            lista_puntos[posicion].nz/=cnt;

            float X=lista_puntos[posicion].nx;
            float Y=lista_puntos[posicion].ny;
            float Z=lista_puntos[posicion].nz;
            double distancia=sqrt(X*X+Y*Y+Z*Z);
            lista_puntos[posicion].nx/=distancia;
            lista_puntos[posicion].ny/=distancia;
            lista_puntos[posicion].nz/=distancia;
        }
    }
}
