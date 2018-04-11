#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

const int FONT_SIZE = 20;

class SDLInit {
public:
    SDLInit()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Initialze SDL");
        }
    }

    SDLInit(const SDLInit& other) = delete;

    SDLInit& operator=(const SDLInit& other) = delete;

    ~SDLInit()
    {
        SDL_Quit();
    }
};

class SDLWindow {
    SDL_Window* mWindow = nullptr;

public:
    SDLWindow()
        : SDLWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, SDL_WINDOW_SHOWN){};

    SDLWindow(const std::string& title, int x, int y, int w, int h, Uint32 flags)
    {
        mWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
        if (mWindow == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Create SDL_Window");
        }
    }

    SDLWindow(const SDLWindow& other) = delete;

    SDLWindow& operator=(const SDLWindow& other) = delete;

    SDL_Window* getWindow() { return mWindow; }

    ~SDLWindow()
    {
        if (mWindow != nullptr)
            SDL_DestroyWindow(mWindow);
    };
};

class SDLRenderer {
    SDL_Renderer* mRenderer = nullptr;

public:
    SDLRenderer(SDLWindow& window)
        : SDLRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC){};

    SDLRenderer(SDLWindow& window, int index, Uint32 flags)
    {
        mRenderer = SDL_CreateRenderer(window.getWindow(), index, flags);
        if (mRenderer == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Create SDL_Renderer");
        }
    };

    SDLRenderer(const SDLRenderer& other) = delete;

    SDLRenderer& operator=(const SDLRenderer& other) = delete;

    SDL_Renderer* getRenderer() { return mRenderer; }

    ~SDLRenderer()
    {
        if (mRenderer != nullptr)
            SDL_DestroyRenderer(mRenderer);
    };
};

class TTFInit {
public:
    TTFInit()
    {
        if (TTF_Init() == -1) {
            std::cerr << TTF_GetError() << std::endl;
            throw std::runtime_error("Initialize TTF");
        }
    }

    TTFInit(const TTFInit& other) = delete;

    TTFInit& operator=(const TTFInit& other) = delete;

    ~TTFInit()
    {
        TTF_Quit();
    }
};

class TTFFont {
    TTF_Font* mFont = nullptr;

public:
    TTFFont(const std::string& path)
    {
        mFont = TTF_OpenFont(path.c_str(), FONT_SIZE);
        if (mFont == nullptr) {
            std::cerr << TTF_GetError() << std::endl;
            throw std::runtime_error("Open TTF");
        }
    };

    TTFFont(const TTFFont& other) = delete;

    TTFFont& operator=(const TTFFont& other) = delete;

    TTF_Font* getFont() const { return mFont; };

    ~TTFFont()
    {
        if (mFont != nullptr)
            TTF_CloseFont(mFont);
    };
};