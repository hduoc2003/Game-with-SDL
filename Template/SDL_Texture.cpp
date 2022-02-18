#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "WELCOME TO MY EMPIRE";

namespace create_window
{
    void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
    {
        os << msg << " Error: " << SDL_GetError() << std::endl;
        if (fatal)
        {
            SDL_Quit();
            exit(1);
        }
    }

    void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logSDLError(std::cout, "SDL_Init", true);

        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        ///window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        ///  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


        ///Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                      SDL_RENDERER_PRESENTVSYNC);
        ///Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
        ///renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void waitUntilKeyPressed()
    {
        SDL_Event e;
        while (true)
        {
            if ( SDL_WaitEvent(&e) != 0 &&
                    (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
                return;
            SDL_Delay(100);
        }
    }
}

namespace ns_SDL_Texture
{
    SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
    {
        SDL_Texture* newTexture = nullptr;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == nullptr)
            cout << "Unable to load image " << path << " SDL_image Error: "
                 << IMG_GetError() << '\n';
        else
        {
            newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            if (newTexture == nullptr)
                cout << "Unable to load texture from " << path << " SDL Error: "
                     << SDL_GetError() << '\n';
            SDL_FreeSurface(loadedSurface);
        }
        return newTexture;
    }

    void DestroyTexture(SDL_Texture* texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

using namespace create_window;
using namespace ns_SDL_Texture;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    /// Your drawing code here
    /// use SDL_RenderPresent(renderer) to show it

    SDL_Texture* background = loadTexture("test_texture.png", renderer);
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    /**
        RenderCopy explain:
        3th argument: react on the image you want to show
        4th argument: react on the background you want to put the image in

    SDL_Texture* cat = loadTexture("cute_gangster_cat.jpg", renderer);
    SDL_Rect cat_rect;
    SDL_QueryTexture(cat, nullptr, nullptr, &cat_rect.w, &cat_rect.h);
    cat_rect.x = 100;
    cat_rect.y = 100;
    cat_rect.w /= 2;
    cat_rect.h /= 2;
    SDL_Rect sr_cat;
    sr_cat.x = sr_cat.y = 0;
    sr_cat.w = cat_rect.w / 2;
    sr_cat.h = cat_rect.h / 2;
    SDL_RenderCopy(renderer, cat, &sr_cat, &cat_rect);
    DestroyTexture(background);
    DestroyTexture(cat);
    **/
   ///Khi thông thường chạy với môi trường bình thường ở nhà

    SDL_RenderPresent(renderer);
   ///Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   ///SDL_UpdateWindowSurface(window);


    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
