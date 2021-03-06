#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "framedata.h"

static const uint8_t color_v_to_viii [32] =
{
    0, 8, 16, 24, 32, 41, 49, 57, 65, 74, 82, 90, 98, 106, 115, 123,
    131, 139, 148, 156, 164, 172, 180, 189, 197, 205, 213, 222, 230, 238, 246, 255
};

static void delete_seq(seq *sq)
{
    if (sq->refcount > 0)
    {
        sq->refcount--;
        return;
    }

    for(uint32_t i = 0; i < sq->subseqs.size(); i++)
    {
        for (uint32_t j = 0; j < sq->subseqs[i].frames.size(); j++)
        {
            for (uint32_t k = 0; k < sq->subseqs[i].frames[j]->box_unk_atk.size(); k++)
                if (sq->subseqs[i].frames[j]->box_unk_atk[k])
                    delete sq->subseqs[i].frames[j]->box_unk_atk[k];

            delete sq->subseqs[i].frames[j];
        }
    }

    delete sq;
}

bool char_graph::load_dat(const char *name, uint8_t pal, char pal_rev)
{
    char buf[CHRBUF];

    if (pal_rev)
        sprintf(buf, "data/character/%s/palette%3.3d%c.pal", name, pal, pal_rev);
    else
        sprintf(buf, "data/character/%s/palette%3.3d.pal", name, pal);

    uint32_t plt[256];

    if (!load_pal_pal(buf,plt))
        return false;

    sprintf(buf, "data/character/%s/%s.pat", name, name);

    filehandle *f = arc_get_file(buf);

    if (!f)
        return false;

    uint16_t pat_count = 0;

    uint8_t pat_version = 0;

    f->read(1, &pat_version);

    /*if (pat_version != 5)
    {
        delete f;
        return false;
    }*/

    f->read(2, &pat_count);

    imgs.resize(pat_count);

    for (uint32_t i = 0; i < pat_count; i++)
    {
        f->read(0x80, buf);

        uint8_t slen = strlen(buf);

        buf[slen-1] = '2';
        buf[slen-2] = 'v';
        buf[slen-3] = 'c';

        char buf2[CHRBUF];
        sprintf(buf2,"data/character/%s/%s",name,buf);

        gr_tex *tex = gr_load_cv2(buf2, plt);

        imgs[i] = tex;
    }

    uint32_t num_seq = 0;

    f->read(4, &num_seq);

    int32_t lastid = -1;

    for (uint32_t i=0; i < num_seq && !f->eof(); i++)
    {
        int32_t id = 0;

        f->read(4, &id);

        if (id == -1) // mapping
        {
            uint32_t seq_new  = 0;
            uint32_t seq_maps = 0;
            f->read(4, &seq_new);
            f->read(4, &seq_maps);

            mapseq::iterator tmp = seqs.find(seq_maps);

            if (tmp != seqs.end())
            {
                tmp->second->refcount++;
                seqs[seq_new] = tmp->second;
            }
        }
        else
        {
            seq *sq         = NULL;

            if (id != -2) // new sequences
            {
                mapseq::iterator tmp = seqs.find(id);

                if (tmp != seqs.end())
                {
                    delete_seq(tmp->second);
                }


                sq = new seq;

                sq->refcount = 0;

                seqs[id] = sq;

                sq->id = id;

                lastid = id;
            }
            else if (lastid >= 0) //it's new part of current
            {
                sq = seqs[lastid];
            }
            else
            {
                delete f;
                return false;
            }
            if (sq == NULL)
            {
                delete f;
                return false;
            }

            subseq ssq;

            f->read(2, &ssq.prior);
            f->read(2, &ssq.prior_for_cancel);
            f->read(1, &ssq.looped);

            if (id != -2)
            {
                sq->prior = ssq.prior;
                sq->prior_for_cancel = ssq.prior_for_cancel;
            }

            uint32_t nframes = 0;

            f->read(4, &nframes);

            ssq.frames.resize(nframes);

            for (uint32_t j = 0; j < nframes; j++)
            {

                char_frame *frm = new char_frame;

                frm->angle_z = 0;
                frm->angle_x = 0;
                frm->angle_y = 0;
                frm->scale_x = 2.0;
                frm->scale_y = 2.0;
                frm->c_A = 255;
                frm->c_R = 255;
                frm->c_G = 255;
                frm->c_B = 255;
                frm->blend_mode = 0;

                int32_t frame = 0;
                f->read(4, &frame);

                if (frame >= 0 && (uint32_t)frame < imgs.size())
                    frm->img = imgs[frame];
                else
                    frm->img = NULL;

                f->read(2, &frm->unk1); //tex_x
                f->read(2, &frm->unk2); //tex_y

                f->read(2, &frm->tx_width);
                f->read(2, &frm->tx_height);
                f->read(2, &frm->x_offset);
                f->read(2, &frm->y_offset);
                f->read(2, &frm->durate);

                f->read(1, &frm->type);

                if (frm->type == 2)
                {
                    f->read(2, &frm->blend_mode);

                    f->read(1, &frm->c_A);
                    f->read(1, &frm->c_R);
                    f->read(1, &frm->c_G);
                    f->read(1, &frm->c_B);

                    if (pat_version < 5) //th105
                    {
                        int16_t tscale = 0;
                        f->read(2, &tscale);
                        frm->scale_y = frm->scale_x = tscale / 100.0;
                    }
                    else
                    {
                        int16_t tscale = 0;
                        f->read(2, &tscale);
                        frm->scale_x = tscale / 100.0;

                        tscale = 0;
                        f->read(2, &tscale);
                        frm->scale_y = tscale / 100.0;
                    }

                    f->read(2, &frm->angle_x);
                    f->read(2, &frm->angle_y);
                    f->read(2, &frm->angle_z);

                    if (frm->angle_x == 0 && frm->angle_y == 180 && frm->angle_z == 0)
                    {
                        frm->angle_x = 0;
                        frm->angle_y = 0;
                        frm->angle_z = 0;
                        frm->scale_x *= -1;
                    }
                }
                else
                {
                    frm->x_offset /= frm->scale_x;
                    frm->y_offset /= frm->scale_y;
                }

                f->read(2, &frm->damage);
                f->read(2, &frm->proration);
                f->read(2, &frm->health_smval);
                f->read(2, &frm->sp_smval);
                f->read(2, &frm->untech);
                f->read(2, &frm->unk9);
                f->read(2, &frm->limit);
                f->read(2, &frm->flag196_char);
                f->read(2, &frm->flag196_enemy);
                f->read(2, &frm->flag196_char2);
                f->read(2, &frm->flag196_enemy2);
                f->read(2, &frm->card_energy);
                f->read(2, &frm->card_energy2);
                f->read(2, &frm->fall_seq);
                f->read(2, &frm->fall_seq2);

                int16_t tvel = 0;

                f->read(2, &tvel);
                frm->velocity_x = tvel/ 100.0;

                f->read(2, &tvel);
                frm->velocity_y = tvel / 100.0;

                f->read(2, &frm->hit_sfx); //global sound, played then hit
                f->read(2, &frm->unk19);
                f->read(2, &frm->attack_type);
                f->read(1, &frm->unk20);
                f->read(4, &frm->fflags);
                f->read(4, &frm->aflags);

                uint8_t nb = 0;
                f->read(1, &nb);

                frm->box_coll = NULL;
                if (nb > 0)
                {
                    frame_box box;
                    f->read(4, &box.x1);
                    f->read(4, &box.y1);
                    f->read(4, &box.x2);
                    f->read(4, &box.y2);

                    frm->box_coll = new frame_box;
                    *frm->box_coll = box;
                }


                nb = 0;
                f->read(1, &nb);

                for (uint32_t k = 0; k < nb; k++)
                {
                    frame_box box;
                    f->read(4, &box.x1);
                    f->read(4, &box.y1);
                    f->read(4, &box.x2);
                    f->read(4, &box.y2);

                    frm->box_hit.push_back(box);
                }

                nb = 0;
                f->read(1, &nb);

                for (uint32_t k = 0; k < nb; k++)
                {
                    frame_box box;
                    f->read(4, &box.x1);
                    f->read(4, &box.y1);
                    f->read(4, &box.x2);
                    f->read(4, &box.y2);

                    frm->box_atk.push_back(box);

                    uint8_t s = 0;
                    f->read(1 , &s);
                    if (s) // not found in files
                    {
                        frame_box *bx = new frame_box;
                        f->read(4, &bx->x1);
                        f->read(4, &bx->y1);
                        f->read(4, &bx->x2);
                        f->read(4, &bx->y2);
                        frm->box_unk_atk.push_back(bx);
                    }
                    else
                        frm->box_unk_atk.push_back(NULL);

                }

                if ( frm->fflags & FF_ATK_AS_HIT )
                    frm->box_hit = frm->box_atk;

                if (pat_version == 5)
                {
                    for(int8_t k=0; k<6; k++)
                        f->read(4, &frm->extra1[k]);
                    for(int8_t k=0; k<3; k++)
                        f->read(2, &frm->unk22[k]);
                }

                ssq.frames[j] = frm;
            }

            sq->subseqs.push_back(ssq);
        }
    }


    delete f;
    return true;
}



bool char_graph::load_pal_pal(const char *file,uint32_t *pal)
{
    filehandle *f = arc_get_file(file);

    if (f)
    {
        uint8_t bits;

        f->read(1,&bits);

        if (bits == 16)
        {
            uint16_t temppal[256];
            f->read(0x200, temppal);
            pal[0] = 0;
            for (uint32_t i = 1; i < 256; i++)
                pal[i] = 0xFF000000 |
                         color_v_to_viii[temppal[i] & 0x1F] << 16          |
                         (color_v_to_viii[(temppal[i] >> 5) & 0x1F] << 8 ) |
                         (color_v_to_viii[(temppal[i] >> 10) & 0x1F] );
        }
        else if (bits == 24 || bits == 32)
            f->read(0x400, pal);
        else
        {
            delete f;
            return false;
        }



        delete f;
        return true;
    }
    return false;
}

//char_graph::char_graph()
//{
//    index = -1;
//}

char_graph::~char_graph()
{
    for(uint32_t i=0; i<imgs.size(); i++)
        gr_delete_tex(imgs[i]);

    imgs.clear();

    for(mapseq::iterator tmp = seqs.begin(); tmp != seqs.end(); tmp++)
        delete_seq(tmp->second);

    seqs.clear();
}

//void char_graph::set_seq(uint32_t idx)
//{
//    mapseq::iterator tmp = seqs.find(idx);
//    if (tmp != seqs.end())
//    {
//        index = idx;
//       sprite.set_seq(tmp->second);
//    }
//
//}

seq *char_graph::get_seq(uint32_t idx)
{
    mapseq::iterator tmp = seqs.find(idx);
    if (tmp != seqs.end())
        return(tmp->second);

    return NULL;
}

uint16_t char_graph::get_prior(uint32_t idx)
{
    seq *tmp = get_seq(idx);
    if (tmp)
        return tmp->prior;
    return 0xFFFF;
}
uint16_t char_graph::get_cprior(uint32_t idx)
{
    seq *tmp = get_seq(idx);
    if (tmp)
        return tmp->prior_for_cancel;
    return 0xFFFF;
}
