#ifndef CHARACTER_DEF_H_INCLUDED
#define CHARACTER_DEF_H_INCLUDED

#define MAX_CHR_SFX     0x100

#include "bullets.h"
#include "weather.h"
#include "cards.h"
#include "input.h"

enum CHAR_ID
{
    CHAR_ID_REIMU  = 0,
    CHAR_ID_MARISA = 1,
    CHAR_ID_SAKUYA = 2,
    CHAR_ID_ALICE  = 3,
    CHAR_ID_PACHOU = 4,
    CHAR_ID_YOUMU  = 5,
    CHAR_ID_REMI   = 6,
    CHAR_ID_YUYUKO = 7,
    CHAR_ID_YUKARI = 8,
    CHAR_ID_SUIKA  = 9,
    CHAR_ID_REISEN = 10,
    CHAR_ID_AYA    = 11,
    CHAR_ID_KOMACHI= 12,
    CHAR_ID_IKU    = 13,
    CHAR_ID_TENSHI = 14,
    CHAR_ID_SANAE  = 15,
    CHAR_ID_CIRNO  = 16,
    CHAR_ID_MEILING= 17,
    CHAR_ID_UTSUHO = 18,
    CHAR_ID_SUWAKO = 19,
    CHAR_ID_NAMAZU = 21
};

class c_bullet;

class char_c : public c_meta
{
private:

    protected:

    inp_ab      *input;
    virtual void set_seq_params(); //func15


    public:

    int8_t input_function;//HACK



    sfxc *sfx[MAX_CHR_SFX];

    char_c(inp_ab *func);



//-------------------------------------------

    //character_ID
    CHAR_ID char_id = CHAR_ID_REIMU;  //0x34C
    int8_t  player_index;       //0x350
    //char pallete_number;
    //char field_352;
    //char field_353;
    gr_tex *player_face_tex;    //0x354
    gr_sprite *player_face;        //0x358 + 0x90
    //stand_gfx stand_graph     //0x3EC + 0xA0
    //int   field_48C
    //int   field_490;
    //int   field_494;
    int16_t health_prev;    //0x498
    int8_t  field_49A;
    int8_t  air_dash_cnt;   //0x49B
    //char  field_49C;
    int8_t  field_49D;
    int16_t spell_energy;       //0x49E
    int16_t max_spell_energy;   //0x4A0
    int16_t spell_energy_stop;  //0x4A2
    int16_t crshd_sp_brdrs_timer;   //0x4A4
    int16_t field_4A6;
    int16_t time_stop;  //0x4A8
    int16_t field_4AA;
    int8_t  field_4AC;
    int8_t  correction; //0x4AD
    //char field_4AE;
    //char field_4AF;
    float combo_rate;   //0x4B0
    int16_t combo_count;    //0x4B4
    int16_t combo_damage;   //0x4B6
    int16_t combo_limit;    //0x4B8
    int16_t field_4BA;
    int16_t field_4BC;
    int16_t field_4BE;
    int16_t field_4C0;
    int16_t field_4C2;
    int8_t  field_4C4; //char suwako_not_on_ground_flag?;
    //char field_4C5;
    int16_t field_4C6;
    int32_t field_4C8;
    int8_t  field_4CC;
    int8_t  field_4CD;
    int8_t  field_4CE;
    float   speed_mult; //0x4D0
    int16_t field_4D4;
    int8_t  field_4D8;
    //char field_4D9;
    //char field_4DA;
    //char field_4DB;
    //int field_4DC;
    //int field_4E0;
    //int field_4E4;
    //int field_4E8;
    //int field_4EC;
    //int field_4F0;
    //int field_4F4;
    //int field_4F8;
    //int field_4FC;
    //int field_500;
    //int field_504;
    //int field_508;
    //int field_50C;
    //int field_510;
    //int field_514;
    //int field_518;
    int16_t field_51C;
    int16_t field_51E;
    int16_t field_520;
    int16_t field_522;
    int16_t field_524;
    int16_t field_526;
    int16_t life_recovery;  //0x528
    int16_t field_52A;
    //char field_52B;
    //int weather_var ?;     //0x52C
    float   field_530;
    float   field_534;
    int32_t field_538;
    int32_t field_53C;
    int32_t field_540;
    int32_t field_544;
    int32_t field_548;
    float   field_54C;
    float   field_550;
    float   field_554;
    float   field_558;
    //float field_55C;
    int16_t field_560;
    float   field_564;
    float   field_568;
    int8_t  field_56C;
    int8_t  field_56D;
    int8_t  field_56E;
    int8_t  field_56F;
    int8_t  field_570;
    int8_t  field_571;
    int8_t  field_572;
    int8_t  win_count;  //0x573
    int8_t  field_574;
    int8_t  field_575;
    int8_t  field_576;
    int8_t  field_577;
    int8_t  field_578;
    //char field_579;
    //char field_57A;
    //char field_57B;

    //######0x57C###### //player_cards_map_deque
    //cards holder
    s_cards chr_cards;
    //Contain cards deck
    card_deq cards_deck;
    //Contain shuffled deck
    card_deq cards_shuffle;
    //######0x57C END######

    int16_t current_card_energy;    //0x5E4
    int8_t  cards_added;        //0x5E6
    int8_t  card_slots;         //0x5E7
    //Contain added cards to hand
    card_deq cards_active;      //0x5E8 + 0x14
    //Contain used cards
    card_deq cards_used;        //0x5FC + 0x14
    //graph_2dui graph_3;       //0x610 + 0x94
    int8_t  skills_1[32];       //0x6A4 - 0x6C3
    int8_t  skills_2[32];       //0x6C4 - 0x6E3
    //int field_6E4;
    //int field_6E8;
    int32_t field_6EC;
    //int field_6F0;
    //char field_6F4;
    //char field_6F5;
    //char field_6F6;
    //char field_6F7;
    bullist     bullets;    //0x6F8
    //mmm mmm_;             //0x6FC + 0x14
    int32_t field_710;
    //struc_714 struc714;   //0x714 + 0x10
    //int field_724;
    //char field_728;
    //char field_729;
    //char field_72A;
    //char field_72B;
    //int spell_images__vector_list;    //0x72C
    //int field_730;
    //int field_734;
    //int field_738;
    //int field_73C;
    int16_t field_740;
    //char field_742;
    //char field_743;
    float   field_744;
    //float field_748;
    float   field_74C;
    //input_structure *input_function;  //0x750
    //int pressed_x_axis;   //0x754
    //int pressed_y_axis;   //0x758
    //int pressed_A;        //0x75C
    //int pressed_B;        //0x760
    //int pressed_C;        //0x764
    //int pressed_D;        //0x768
    //int pressed_AB;       //0x76C
    //int pressed_BC;       //0x770
    //int is_pressed_X_axis;    //0x774
    //int is_pressed_Y_axis;    //0x778
    //int is_pressed_A_1;       //0x77C
    //int is_pressed_B_1;       //0x780
    //int is_pressed_C_1;       //0x784
    //int is_pressed_D_1;       //0x788
    //int is_pressed_AB_1;      //0x78C
    //int is_pressed_BC_1;      //0x790
    //int keyup_A;              //0x794
    //int keyup_B;              //0x798
    //int keyup_C;              //0x79C
    //int keyup_D;              //0x7A0
    //int keyup_AB;             //0x7A4
    //int keyup_BC;             //0x7A8
    //char some_input_var;      //0x7AC
    //char field_7AD;
    //char field_7AE;
    //char field_7AF;
    //def_deque input__input__deque;    //0x7B0 + 0x14
    uint32_t pres_move;             //0x7C4
    uint32_t pres_comb;             //0x7C8
    int8_t  controlling_type;       //0x7CC
    int16_t field_7D0;
    int16_t field_7D2;
    int16_t field_7D4;
    int16_t field_7D6;
    int16_t field_7D8;
    float   field_7DC;
    float   dash_angle; //0x7E0
    float   field_7E4;
    float   field_7E8;
    float   field_7EC;
    float   field_7F0;
    int8_t  not_charge_attack;  //0x7F4
    bool    bbarrier_show;  //if true - block barrier showing  0x7F5
    //char field_7F6;
    int8_t  field_7F7;
    int16_t field_7F8;
    //__int16 field_7FA;
    //float field_7FC;
    int8_t  field_800;
    int8_t  field_801;
    int8_t  field_802;
    int8_t  field_803;
    int8_t  field_804;
    //char field_805;
    //char field_806;
    //char field_807;
    int32_t field_808;
    int8_t  field_80C;
    int8_t  field_80D;
    int8_t  field_80E;
    //char field_80F;
    int32_t field_810;
    int32_t field_814;
    //__int16 field_818;
    //__int16 field_81A;
    //__int16 field_81C;
    //__int16 field_81E;
    //__int16 field_820;
    //__int16 field_822;
    //__int16 field_824;
    //__int16 field_826;
    //__int16 field_828;
    int16_t field_82A;
    //int field_82C;
    //int field_830;
    int16_t tengu_fan;  //by system spell card  //0x834
    int16_t field_836;
    int32_t field_838;
    int8_t  field_83C;
    //char field_83D;
    //__int16 field_83E;
    int32_t field_840;
    float   field_844;
    float   field_848;
    int16_t field_84C;
    int16_t field_84E;
    int16_t field_850;
    int16_t field_852;
    float   field_854;
    float   field_858;
    float   field_85C;
    float   field_860;
    float   field_864;
    int8_t  field_880;
    //char field_881;
    int16_t field_882;
    //__int16 field_884;
    //__int16 field_886;
    //__int16 field_888;
    //__int16 field_88A;
    int16_t x_delta; //x_offset     //0x88C
    int16_t y_delta; //y_offset     //0x89E
    int16_t field_890;
    int16_t field_892;
    int16_t field_894;
    //__int16 field_896;
    float   field_898;
    float   field_89C;
    //__int16 field_8A0;
    //int field_8A2;
    //int field_8A6;
    //int field_8AA;
    //int field_8AE;
    //__int16 field_8B2;
    //int field_8B4;
    //int field_8B8;
    //int field_8BC;
    //int field_8C0;
    //int field_8C4;
    //float field_8C8;
    //int field_8CC;
    //int field_8D0;
    //int field_8D4;
    //int field_8D8;
    //int field_8DC;
    //int field_8E0;
    //int field_8E4;
    //int field_8E8;
    //int field_8EC;
    //int field_8F0;
    //int field_8F4;
    //int field_8F8;
    //int field_8FC;
    //int field_900;
    //int field_904;
    //int field_908;
    //int field_90C;
    //int field_910;
    //int field_914;
    //int field_918;
    //float field_91C;
    //int field_920;

//-------------------------------------------







    //Sets deck from profile
    void set_cards_deck(s_profile *prof, uint32_t deck_id);

    void load_face(const char *name);

    void sub_486FD0(float p1, float p2);

    bullist *get_bullets();

    void set_seq(uint32_t idx);

    void input_update();
    virtual void draw_shadow(shd_trans *trans, gr_shader *shader = NULL);
    virtual void draw(gr_shader *shader = NULL);

    virtual void check_seq_input();

    void stopping(float p);
    void stopping_posit(float p);

    bool flip_to_enemy();
    bool field_sq_check();
    void flip_with_force();
    void reset_forces();
    void health_to_max();

    void play_sfx(uint32_t idx);

    virtual void func10();
    virtual void func16();
    virtual void func18();
    virtual void func20();

    virtual c_bullet *new_bullet() ;

    //input functions
    bool keyDown(inp_keys key);
    bool keyHit(inp_keys key);
    int8_t gX(int8_t dir);
    int8_t gY();
    void   setgX(int8_t dir);
    void   setgY(int8_t dir);
    void set_input_profile(s_profile *prof);
};

typedef list<char_c *> charlist;
typedef list<char_c *>::iterator charlist_iter;



bool char_idle_or_move(char_c *chr);
bool char_is_shock(char_c *chr);
bool char_is_block_knock(char_c *chr);
void char_h_move(char_c *chr, float move);
bool sub10func(char_c *chr);
void char_loadsfx(char_c *chr, const char *name);



bool hi_jump_after_move(char_c *chr);
bool border_escape_ground(char_c *chr);
bool hi_jump(char_c *chr, uint16_t cprior, uint32_t hjc);
bool fw_bk_dash_ground(char_c *chr, uint16_t cprior, uint32_t hjc);
bool border_escape_air(char_c *chr);
bool fwd_dash_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash, uint16_t subse);
bool bkg_dash_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash, uint16_t subse);
bool flying_air(char_c *chr, uint16_t cprior, uint32_t hjc, int8_t max_dash);

bool spell200_seq299_300_field190_0_3(char_c *chr);

void spell_energy_spend(char_c *chr, int32_t energy, int32_t stop_time);
void crash_spell_borders(char_c *chr, int8_t num);

void sub_4689D0(char_c *, int32_t);

void add_card_energy(char_c *chr, int32_t energy);
void add_card_energy2(char_c *chr, int32_t energy);
void add_card(char_c *chr);

bool check_AB_pressed(char_c *chr);

#endif // CHARACTER_DEF_H_INCLUDED
