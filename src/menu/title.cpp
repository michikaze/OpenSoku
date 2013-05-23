#include "../global_types.h"
#include "../input.h"
#include "../gui.h"
#include "title.h"

bool is_load = false;

gui_holder *title = NULL;

gui_el_t1 *bkg[5];
gr_tex    *bkg_imgs[5];

static int32_t t_frms = 0;

float  bkgs[3];

int8_t title_punkt = 0;
int8_t title_stage = 1;
int8_t menu_frames = 0;
float menu_pos = 0;

gr_tex *moji1_tex;
gr_tex *moji2_tex;

gui_el_t1 *moji1;
gui_el_t1 moji2;

gui_el_t0 *men_bkg;
gui_el_t0 *cop;
gui_el_t0 *titl;

static gr_tex *gear_tex;
static gui_el_t1 *gear;
static gui_el_t0 *cursor;

float cur_pos = 0;

inp_kb kb;

void init_menu()
{
    title = new gui_holder;
    title->load_dat("data/scene/title","title.dat");

    for (int8_t i=0; i<5; i++)
    {
        char bf[CHRBUF];
        sprintf(bf,"data/scene/title/%02d_back.cv2",15-i);
        bkg_imgs[i] = gr_load_cv2(bf, NULL);

        gr_set_repeate(bkg_imgs[i],true);
        gr_set_smoth(bkg_imgs[i],true);

        bkg[i] = title->get_gui_t1((15-i)*10);
        bkg[i]->setTexture(bkg_imgs[i]);
        if (i == 2)
            bkg[i]->setOrigin(20,128);
    }

    moji1_tex = gr_load_cv2("data/scene/title/2_menu_moji1.cv2",NULL);
    moji2_tex = gr_load_cv2("data/scene/title/2_menu_moji2.cv2",NULL);

    moji1 = title->get_gui_t1(300);
    moji2.setXY(moji1->getX(),moji1->getY());

    moji1->setTextureFramed(moji1_tex,108,24);
    moji2.setTextureFramed(moji2_tex,108,24);

    bkgs[0] = 0;
    bkgs[1] = 0;
    bkgs[2] = 0;

    men_bkg = title->get_gui_t0(420);

    gear_tex = gr_load_cv2("data/scene/title/2_menu_gear.cv2",NULL);
    cursor = title->get_gui_t0(210);

    gear = title->get_gui_t1(200);
    gear->setTexture(gear_tex);
    gear->setOrigin(48,48);

    titl = title->get_gui_t0(400);
    cop = title->get_gui_t0(410);

    is_load = true;
}

void draw_title()
{
    t_frms++;

    if (title_stage == 2)
    {
        if (menu_frames < 16)
        {
            menu_pos = (menu_frames * menu_frames * 0.004);
            menu_frames++;
        }
        else
            menu_pos = 1.0;

        cur_pos = 24 * title_punkt * 0.2 + cur_pos * 0.8;
    }
    if (title_stage > 0)
    {
        men_bkg->renderable = true;
        titl->renderable = true;
        cop->renderable = true;
    }

    men_bkg->setDXDY((menu_pos - 1.0) * 160,0);
    titl->setDXDY(menu_pos * 80,0);
    cop->setDXDY(menu_pos * 80,0);


    bkgs[0] += 0.05;
    if (bkgs[0] > 512)
        bkgs[0] -= 512;

    bkgs[1] += 0.1;
    if (bkgs[1] > 640)
        bkgs[1] -= 640;

    bkgs[2] += 0.2;
    if (bkgs[2] > 768)
        bkgs[2] -= 768;

    bkg[0]->draw(0);

    if (bkgs[0] < 128)
        bkg[1]->draw(bkgs[0] + 512,0,0);
    bkg[1]->draw(bkgs[0],0,0);
    bkg[1]->draw(bkgs[0]-512,0,0);

    bkg[2]->setRotate(cos_deg(t_frms) * 3.0);
    bkg[2]->draw(0,fabs(cos_deg(t_frms) * 3.0),0);

    bkg[3]->draw(bkgs[1],0,0);
    bkg[3]->draw(bkgs[1]-640,0,0);

    bkg[4]->draw(bkgs[2],0,0);
    bkg[4]->draw(bkgs[2]-768,0,0);


    gear->setRotate(cur_pos * 1.2);
    gear->setColor(255,0,0,0);
    gear->draw((menu_pos - 1.0) * 160 + 4,cur_pos + 4,0);
    gear->setColor(255,255,255,255);
    gear->draw((menu_pos - 1.0) * 160,cur_pos,0);

    title->draw_all(0);

    cursor->draw((menu_pos - 1.0) * 160,cur_pos,0);

    for (int8_t i=0; i<12; i++)
        moji1->draw_frame((menu_pos - 1.0) * 160,i * 24, 0,i,0);

    moji2.draw_frame((menu_pos - 1.0) * 160,title_punkt * 24, 0,title_punkt,0);
}

void menu_title_call()
{
    if (!is_load)
        init_menu();

    kb.update();

    if (kb.keyHit(INP_DOWN))
        title_punkt++;
    if (kb.keyHit(INP_UP))
        title_punkt--;

    if (kb.keyHit(INP_A))
        if (title_stage < 2)
            title_stage++;

    if (title_punkt < 0)
        title_punkt +=12;
    else if (title_punkt >= 12)
        title_punkt %= 12;

    draw_title();

}