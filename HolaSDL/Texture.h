
#ifndef TextureH
#define TextureH

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows

#include <string>

using namespace std;

typedef unsigned int uint;

class Texture {
    private:
        //puntero a la textura SDL
        SDL_Texture* texture = nullptr;
        SDL_Renderer* renderer = nullptr;
        //info sobre su tamaño total
        uint w = 0;
        uint h = 0;
        //tamaños de sus frames
        uint fw = 0; // Frame width
        uint fh = 0; // Frame height
        uint numCols = 1;
        uint numRows = 1;

    public:
        //dependiendo de los valores  o argumentos que pase llama a una constructora u otra
        Texture(SDL_Renderer* r) : renderer(r) {};
        Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer(r) { load(filename, numRows, numCols); };

        //~~es la destructora que llama a free para liberar codigo
        virtual ~Texture() { _freeTexture(); };
        void _freeTexture();
        //devuelve la anchura de la textura, weights
        int getW() const { return w; };
        //devuelve la altura de la textura , height
        int getH() const { return h; }
        //devuelve frame width
        int getFw() const { return fw; };
        //devuelve frame height
        int getFh() const { return fh; };
        //numero de columnas
        uint getNumCols() const { return numCols; };
        //numero de columnas
        uint getNumFils() const { return numRows; };
        //devuelve textura
        SDL_Texture* getTexture() const { return texture; };
        //devuelve renderer
        SDL_Renderer* getRenderer() const { return renderer; };
        //carga la textura
        void load(string filename, uint numRows = 1, uint numCols = 1);
        //renderiza la textura
        void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
        //renderiza la textura en la posicion de la fila y la columna
        void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    

};

#endif}
