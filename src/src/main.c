#include <genesis.h>
#include <resources.h>

#define gravidade 1
#define asas 1
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 300;
const int TOP_EDGE = 0;
const int BOTTOM_EDGE = 160;
volatile int countVsincs= 0;


struct{
    int posx;
    int posy;
    Sprite* bird;
    bool isDead;
}flappy;



void controleJoystick( u16 joy, u16 changed, u16 state){

    if (changed & state & BUTTON_UP)
		{
			flappy.posy -= asas;
		} 
}


int main()
{
    JOY_init();
    JOY_setEventHandler( &controleJoystick );
    VDP_setScreenWidth320();
    VDP_setScreenHeight240();
    SPR_init(0,0,0);
    initBird();

    while(1)
    {
        
        if (countVsincs >= 3){
             updatePosition();
        }
        SPR_update();

        countVsincs++;
        VDP_waitVSync();
    }
    return (0);
}


void selectBird(){
    int value  = (random()%3-1)+1;;
    switch (value)
    {
    case 1:
        flappy.bird = SPR_addSprite(&blueBird,flappy.posx,flappy.posy,PAL0);
        VDP_setPalette(PAL0,blueBird.palette->data);
    break;
    case 2:
        flappy.bird = SPR_addSprite(&redBird,flappy.posx,flappy.posy,PAL0);
        VDP_setPalette(PAL0,redBird.palette->data);
    break;
    case 3:
        flappy.bird = SPR_addSprite(&yellowBird,flappy.posx,flappy.posy,PAL0);
        VDP_setPalette(PAL0,yellowBird.palette->data);
    break;
    default:
        break;
    }
}

void initBird(){
    flappy.posx=100;
    flappy.posy=100;
    flappy.isDead = 0;
    selectBird();

}
void updatePosition(){
        countVsincs=0;

        if (flappy.posy <= TOP_EDGE){
            flappy.posy = TOP_EDGE;
            flappy.isDead = 1;
        }

        if (flappy.posy >= BOTTOM_EDGE){
            flappy.posy = BOTTOM_EDGE;
            flappy.isDead = 1;
        }
        flappy.posy += gravidade;
    	SPR_setPosition(flappy.bird,flappy.posx,flappy.posy);
}




