# Exploration 2: WebAssembly + AJAX + History.js
David Auger

---
### About
This exploration is about expanding on what I learned from the previous exploration with regard to [WebAssembly](http://webassembly.org/) and the [Emscripten LLVM](http://kripken.github.io/emscripten-site/index.html) to JavaScript compiler. For this exploration I decided to incorporate AJAX and History.js so that I can load a WebAssembly app without redirecting to a different page.

**My git repo:** https://github.com/deayqf/WebAssembly-AJAX.git

**My instance:** http://davidauger.tech/wasm/

---
### Setup
** If you follow the README in my first [WebAssembly repo](https://github.com/deayqf/WebAssembly) it walks through how to get Emscripten set up.**

**1. In your home directory, clone the [SDL-emscripten repo](https://github.com/gsathya/SDL-emscripten.git)**

**2. Just like in class, clone the [History.js repo](https://github.com/browserstate/history.js/) into your home directory**

**3. Thats it for setup**

---
### Printing Hello World
**1. `cd` into your Apache document root:** `cd /var/www/html`**

**2. Once you are in your document root, run these commands:**
  - `chmod 777` seems unnecessary but Emscripten has issues with permissions.
```bash
sudo mkdir hello
sudo chmod 777 hello
cd hello
```
**3. Now you are going to create a `hello.c` file: `sudo vim hello.c`**
  - The contents should look like this:
```c
#include <stdio.h>

int main( int argc, char** argv )
{
    printf( "Hello, World!\n" );
}
```
**4. When your file looks like mine, save and close the file and then run these commands:**
```bash
sudo chmod 777 hello.c
emcc hello.c -s WASM=1 -o hello.html
```
  - If the compilation was successful there should be no output to the terminal, if you see a bunch of Python printed on the screen then re-run the `chmod 777` commands from above.

**5. If your file compiled then you can now go to your browser and navigate to your hello directory. You should see the Emscripten default page with a simulated terminal that says, "Hello, World!**

---
### Calling C functions with JavaScript
**1. This tutorial can be followed [here](https://tutorialzine.com/2017/06/getting-started-with-web-assembly)**

**2. Make a file called `roll.c`, open it with `vim`, and make its contents like this:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten.h>

int main( int argc, char** argv )
{
    srand( ( unsigned )time( NULL ) );
    printf( "WebAssembly module loaded\n" );
    return 0;
}

int EMSCRIPTEN_KEEPALIVE roll_dice()
{
    return rand() % 6 + 1;
}
```

**3. Now compile that file with this command:**
```bash
emcc roll.c -s WASM=1 -O3 -o dice.js
```
  - After compiling, you should now see `index.js index.wasm` along with the original `roll.c`
  - Unlike the Hello, World example, there is no generated HTML file, so we have to make that

**4. Make an `index.html` file and paste the contents from the example file in the tutorial linked at point 1**

**5. The most important part is the JavaScript, as you are calling C functions from it:**
```javascript
var dice = document.querySelector( '.dice' );
dice.addEventListener( 'click', function() {
    var result = _roll_dice();
    dice.className = "dice dice-" + result;
});
```

**6. Now if you open that `dice.html` page in the browser you should be able to click the die and have its face change.**

---
### Rendering geometry to the screen with [SDL](https://www.libsdl.org/)
**1. Start by making a `main.c` file and open it with `vim`, contents:**
```c
#include <stdio.h>
#include <SDL/SDL.h>
#include <emscripten.h>

static const int SCREEN_W = 400;
static const int SCREEN_H = 400;

typedef struct _bool
{
    false = 0, true = 1
} bool;

SDL_Surface* surface = NULL;
SDL_Rect square;
bool quit = false;

void loop();

int main( int argc, char* args[] ) 
{
    printf( "SDL Loaded through Emscripten\n" );
    
    SDL_Init( SDL_INIT_VIDEO );
    surface = SDL_SetVideoMode( SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE );
    square = ( SDL_Rect ){ 20, 20, 50, 50 };
    
    #ifdef EMSCRIPTEN
        emscripten_set_main_loop( loop, 0, 1 );
    #else
        while( !quit )
        {
            loop();
        }
    #endif
    
    SDL_Quit();
    return 0;
}

void loop()
{
    static SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.key.keysym.sym == SDL_QUIT)
        {
            quit = true;
        }
    }
    SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0x00, 0x00, 0x00 ) );
    SDL_FillRect( surface, &square, SDL_MapRGB( surface->format, 0xFF, 0x00, 0x00 ) );
    SDL_Flip( surface );
}
```
**2. Now compile the file with this command:**
```bash
emcc -O2 --js-opts 0 -g4 main.c -I/home/your_username/SDL-emscripten/include -I/home/your_username/SDL-emscripten/build/.libs/libSDL2.a -o cube.html && sudo chmod 777 *
```
**3. After compiling, if you open the index file in your browser you should see a 400x400 black square with a 50x50 red square at (20,20)**

---
### Loading with AJAX
**1. Start by making an `index.html` file in the same directory as all of the other files that have been made.**
  - Include History.js and jQuery/AJAX in the `<head>`
```HTML
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
<script src="http://your_public_dns/history.js/scripts/bundled/html4+html5/jquery.history.js"></script>
```
  - Copy the `<body>` from your historynav project and modify the `href` attributes to match those of `hello.html dice.html cube.html`
  - Make a `<script>` in the `<head>` which will have this content
```javascript
$( function() {
    let History = window.History;
    var request = location.pathname;
    evaluate_path( request );

    $( 'nav[ rol="navigation" ] a' ).click( function( e ) {
        e.preventDefault();
        var href = $( this ).attr( 'href' );
        History.pushState( { data: 'WASM+AJAX' }, 'WASM+AJAX', href );
        evaluate_path( href );
    });
});

window.onpopstate = function( e ) {
    evaluate_path( location.pathname );
}

History.Adapter.bind( window, 'statechange', function() {
    var State = History.getState();
    History.log( State.data, State.title, State.url );
});

function evaluate_path( path ) {
    var page = path.split( '/' ).pop();
    document.title = page;

    if( page != 'dice' ) {
        $( '#stage' ).load( page + '.html', function( content ) {
            $( this ).children().not( '.emscripten_border, #output' ).hide();
        });
    } else {
        $.get( page + '.html', function( content ) {
            $( '#stage' ).html( content );
        });
    }
    $( 'body' ).css( 'font-family', 'Verdana' );
}
```
**2. Now if you were to open your index page in the browser, you should only see the screen and the terminal for each page except for the dice roll page because it doesn't have a terminal or a screen.**

---
### Journal
I learned a lot from this Exploration by moving towards a more real life use of WebAssembly by loading things via AJAX.

The biggest hurdle for this exploration was parsing the html files to hide the elements that weren't the screen or terminal.

My instance is [here](http://davidauger.tech/wasm/) and my repo is [here](https://github.com/deayqf/WebAssembly-AJAX/).
